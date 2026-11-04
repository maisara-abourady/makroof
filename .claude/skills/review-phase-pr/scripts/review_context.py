#!/usr/bin/env python3
"""Gather the mechanical context a reviewer needs before reading a makroof PR diff.

Usage:
    python3 review_context.py --base <ref> --head <ref> [--repo <path>] [--json]

Typical:
    python3 review_context.py --base origin/main --head origin/claude/some-branch

Everything here is derived from git alone (no network, no GitHub API), so it works in CI, in a
cloud session and on a laptop. It prints a report with these sections:

  1. Phase detection      from commit subjects (`phase-XX:`) and the BUILD_PLAN status-table diff
  2. Changed files        grouped by repository area, with +/- counts
  3. Process signals      goldens, assumptions/change-log, THIRD_PARTY, pins, contract version,
                          parameter freeze file, schema, listening pack
  4. Boundary check       includes crossing src/sim <-> src/module3d, JUCE in contract/sim
  5. NFR-8 scan           preset/scene/material names or the word "preset" inside src/sim
  6. Audio-thread scan    heuristic red flags in files that plausibly run on the audio thread
  7. Determinism scan     unseeded randomness, time-based seeds, unordered iteration into output
  8. Test-hygiene scan    tolerances, skips, pre-ticked listening checklists, duplicated band table
  9. Dependency pins      unpinned FetchContent, floating GitHub Actions, unpinned Python packages

Each scan lists lines to *inspect*; it never claims a verdict. The reviewer decides.
"""
from __future__ import annotations

import argparse
import json
import os
import re
import subprocess
import sys
from collections import defaultdict

AREAS = [
    ("src/contract", "contract"),
    ("src/sim", "sim"),
    ("src/module3d", "module3d"),
    ("src/plugin", "plugin"),
    ("src/cli", "cli"),
    ("tests/unit", "tests/unit"),
    ("tests/scenes", "tests/scenes"),
    ("tests/golden", "tests/golden"),
    ("tests/state", "tests/state"),
    ("tests/automation", "tests/automation"),
    ("tests", "tests/other"),
    ("tools/acoustics", "tools/acoustics"),
    ("tools/ci", "tools/ci"),
    ("tools/hrtf", "tools/hrtf"),
    ("tools/validation", "tools/validation"),
    ("tools", "tools/other"),
    ("resources", "resources"),
    ("docs/phases", "docs/phases"),
    ("docs/contract", "docs/contract"),
    ("docs", "docs/other"),
    (".github", "ci"),
    ("cmake", "cmake"),
    (".claude", "claude-config"),
]

CPP_EXT = (".cpp", ".h", ".hpp", ".cc", ".mm")

# Files whose code plausibly runs on the audio thread. The scan is a heuristic: it flags lines to
# read, it does not prove a violation. (processBlock and everything it calls: CLAUDE.md.)
AUDIO_THREAD_PATH_HINTS = ("src/plugin/", "src/sim/conv/", "src/sim/RealtimeEngine", "src/sim/realtime")
AUDIO_THREAD_RED_FLAGS = [
    (r"\bnew\b(?!\s*\()", "heap allocation (new)"),
    (r"\bmake_(shared|unique)\b", "heap allocation (make_shared/make_unique)"),
    (r"\bmalloc\b|\bcalloc\b|\brealloc\b", "heap allocation (malloc)"),
    (r"\.push_back\(|\.emplace_back\(|\.resize\(|\.reserve\(|\.insert\(", "container growth"),
    (r"\bstd::vector<[^;]*>\s*\w+\s*[({]", "vector constructed in function scope"),
    (r"\bstd::string\b|\bjuce::String\b|std::to_string|\.toStdString\(", "string construction"),
    (r"\bstd::(mutex|recursive_mutex|shared_mutex|lock_guard|unique_lock|scoped_lock|condition_variable)\b",
     "lock"),
    (r"\bjuce::(CriticalSection|ScopedLock|SpinLock|WaitableEvent)\b", "JUCE lock/wait"),
    (r"\bDBG\s*\(|\bjuce::Logger\b|\bprintf\s*\(|\bstd::cout\b|\bstd::cerr\b|\bfprintf\s*\(", "logging / I/O"),
    (r"\bthrow\b|\btry\b\s*\{", "exception"),
    (r"\bstd::function\b", "std::function (may allocate on assignment)"),
    (r"\bstd::shared_ptr<[^>]*>\s+\w+\s*=|std::shared_ptr<[^>]*>\s+\w+\s*\(", "shared_ptr copy (atomic refcount)"),
    (r"\bstd::(ifstream|ofstream|fstream)\b|\bfopen\s*\(|\bjuce::File\b", "file I/O"),
    (r"\bsleep\b|\bstd::this_thread\b|\bjuce::Thread::sleep\b", "sleep / blocking"),
    (r"\bsetSize\s*\(|\bAudioBuffer<[^>]*>\s+\w+\s*\(", "AudioBuffer (re)allocation"),
    (r"\bMessageManager\b|\bcallAsync\b|\bAsyncUpdater\b", "message-thread interaction"),
    (r"\bsetLatencySamples\s*\(", "latency change (host restart; must not be per-block)"),
]

DETERMINISM_RED_FLAGS = [
    (r"\bstd::random_device\b", "non-deterministic seed"),
    (r"\brand\s*\(|\bsrand\s*\(", "C rand (platform-dependent)"),
    (r"\bstd::(normal|uniform_real|uniform_int|exponential)_distribution\b",
     "std distribution (results differ between standard libraries; AX5/Phase 04)"),
    (r"\bstd::chrono::(system_clock|steady_clock|high_resolution_clock)::now\b|\btime\s*\(\s*(nullptr|NULL|0)?\s*\)",
     "time-based value (seed or scheduling)"),
    (r"\bstd::unordered_(map|set)\b", "unordered container (iteration order not stable across platforms)"),
    (r"\bnp\.random\.(rand|randn|random|normal|uniform)\b", "numpy global RNG (use np.random.default_rng(seed))"),
    (r"\bthread_local\b", "thread-local state (check it cannot change results)"),
    (r"\bstd::mt19937(_64)?\b", "std::mt19937 (engine is portable; seed source and any distribution are not)"),
]

TEST_HYGIENE_FLAGS = [
    (r"\.margin\s*\(|\.epsilon\s*\(|WithinAbs\s*\(|WithinRel\s*\(|WithinULP\s*\(|Approx\s*\(", "C++ tolerance"),
    (r"\bpytest\.approx\b|\batol\s*=|\brtol\s*=|\bnp\.allclose\b|\bassert_allclose\b", "Python tolerance"),
    (r"\bSKIP\s*\(|\bSUCCEED\s*\(|\bpytest\.mark\.skip|\bpytest\.skip\b|\bxfail\b", "skipped / vacuous test"),
    (r"#\s*if(n?def)?\s*.*(_WIN32|__APPLE__|__linux__|JUCE_WINDOWS|JUCE_MAC|JUCE_LINUX)", "per-OS test branch (if it wraps a TEST_CASE, a whole test vanishes on one OS)"),
    (r"^\+.*\[\s*[xX]\s*\].*", "pre-ticked checkbox in a document (listening checklist is Maisara's)"),
    (r"63\s*,\s*125\s*,\s*250\s*,\s*500", "octave band table literal (should come from contract::kOctaveBandsHz)"),
    (r"\b(TODO|FIXME|XXX|HACK)\b", "TODO/FIXME left in diff"),
]

PIN_FLAGS = [
    (r"(GIT_TAG|_TAG|_REF|_BRANCH)\s+\"?(main|master|develop|devel|HEAD|trunk|latest)\"?", "FetchContent not pinned to a tag or commit"),
    (r"uses:\s*[\w\-./]+@(main|master|v\d+)\s*$", "GitHub Action on a floating ref (branch or major-only tag)"),
    (r"^\+\s*[A-Za-z0-9_.\-]+\s*(>=|~=|>|<|$)", "Python requirement not pinned with =="),
    (r"pip install (?!-r)", "ad-hoc pip install in CI"),
]

# Scene/preset names the phase files promise (tests/scenes/valid, resources/presets). Kept here so
# the scan works before those files exist; names found in the head tree are added at run time.
PRESET_WORDS = [
    "preset", "small_room", "medium_room", "large_hall", "open_field", "asymmetric_materials",
    "dead_booth", "living_room", "classroom", "club", "concert_hall_box", "stone_box", "club_small",
    "warehouse", "chapel_box", "courtyard", "car_cabin_box",
]
SIM_STRING_LOGIC = r"strcmp\s*\(|==\s*\"|!=\s*\"|\.compare\s*\(|std::string_view\s*\w+\s*==|contains\s*\(\s*\""


def run(cmd, cwd):
    return subprocess.run(cmd, cwd=cwd, text=True, capture_output=True, check=False)


def git(repo, *args):
    r = run(["git", *args], repo)
    if r.returncode != 0:
        raise SystemExit(f"git {' '.join(args)} failed:\n{r.stderr}")
    return r.stdout


def area_of(path):
    for prefix, name in AREAS:
        if path.startswith(prefix):
            return name
    return "root"


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--base", required=True, help="base ref, e.g. origin/main")
    ap.add_argument("--head", required=True, help="head ref, e.g. origin/claude/branch or a SHA")
    ap.add_argument("--repo", default=os.getcwd())
    ap.add_argument("--json", action="store_true", help="emit JSON instead of text")
    args = ap.parse_args()
    repo = os.path.abspath(args.repo)

    merge_base = git(repo, "merge-base", args.base, args.head).strip()
    rng = f"{merge_base}..{args.head}"
    report = {"base": args.base, "head": args.head, "merge_base": merge_base}

    # 1. Phase detection
    subjects = [s for s in git(repo, "log", "--format=%s", rng).splitlines() if s]
    phases = sorted({m.group(1) for s in subjects for m in [re.match(r"phase-(\d\d[a-z]?)\s*:", s)] if m})
    off_pattern = [s for s in subjects if not re.match(r"(phase-\d\d[a-z]?:|Merge )", s)]
    status_diff = run(["git", "diff", rng, "--", "docs/BUILD_PLAN.md"], repo).stdout
    status_rows = [l for l in status_diff.splitlines() if l.startswith(("+|", "-|")) and re.match(r"[+-]\|\s*\d\d", l)]
    report["phase"] = {
        "from_commits": phases,
        "commit_subjects": subjects,
        "subjects_not_following_convention": off_pattern,
        "build_plan_status_rows_changed": status_rows,
        "build_plan_section2_or_6_touched": any(
            re.search(r"^[+-]\|\s*\*\*A[QX]\d+\*\*|^[+-]\| 20\d\d-", l) for l in status_diff.splitlines()),
    }

    # 2. Changed files
    numstat = git(repo, "diff", "--numstat", rng).splitlines()
    files = []
    by_area = defaultdict(list)
    for line in numstat:
        parts = line.split("\t")
        if len(parts) != 3:
            continue
        add, dele, path = parts
        entry = {"path": path, "added": add, "deleted": dele, "area": area_of(path)}
        files.append(entry)
        by_area[entry["area"]].append(entry)
    report["files"] = files
    report["by_area"] = {k: [f["path"] for f in v] for k, v in by_area.items()}
    paths = [f["path"] for f in files]

    # 3. Process signals
    def touched(prefix_or_regex):
        return [p for p in paths if re.search(prefix_or_regex, p)]

    report["signals"] = {
        "goldens_changed": touched(r"^tests/golden/"),
        "golden_changelog_touched": touched(r"^tests/golden/CHANGELOG\.md$"),
        "build_plan_touched": touched(r"^docs/BUILD_PLAN\.md$"),
        "third_party_touched": touched(r"^docs/THIRD_PARTY\.md$"),
        "dependency_pins_touched": touched(r"^(cmake/SpatialDependencies\.cmake|.*requirements.*\.txt|tools/ci/run_pluginval\.sh|\.github/workflows/.*\.ya?ml)$"),
        "contract_sources_touched": touched(r"^src/contract/"),
        "contract_version_touched": touched(r"^src/contract/Version\.h$"),
        "contract_schema_or_readme_touched": touched(r"^docs/contract/"),
        "contract_fixtures_touched": touched(r"^tests/scenes/"),
        "parameter_freeze_touched": touched(r"^tests/state/parameter_ids"),
        "state_fixtures_touched": touched(r"^tests/state/"),
        "listening_pack_touched": touched(r"^tools/ci/listening_pack\.py$"),
        "phase_files_touched": touched(r"^docs/phases/"),
        "claude_md_touched": touched(r"^CLAUDE\.md$"),
        "sim_touched": touched(r"^src/sim/"),
        "plugin_touched": touched(r"^src/plugin/"),
        "wav_files_added": touched(r"\.wav$"),
        "large_binaries": [],
    }
    for p in paths:
        full = os.path.join(repo, p)
        # Size at head, via git cat-file to avoid depending on the checkout.
        r = run(["git", "cat-file", "-s", f"{args.head}:{p}"], repo)
        if r.returncode == 0 and r.stdout.strip().isdigit() and int(r.stdout) > 512 * 1024:
            report["signals"]["large_binaries"].append({"path": p, "bytes": int(r.stdout)})

    # Derived warnings for the reviewer (still not verdicts).
    warnings = []
    s = report["signals"]
    if s["goldens_changed"] and not s["golden_changelog_touched"]:
        warnings.append("Golden files changed without tests/golden/CHANGELOG.md: needs update_goldens.py --reason and a BUILD_PLAN §6 row.")
    if s["goldens_changed"] and not report["phase"]["build_plan_section2_or_6_touched"]:
        warnings.append("Golden files changed but BUILD_PLAN §6 change log has no new row.")
    if s["dependency_pins_touched"] and not s["third_party_touched"]:
        warnings.append("Dependency pins or CI actions changed without docs/THIRD_PARTY.md.")
    if (s["contract_sources_touched"] or s["contract_schema_or_readme_touched"]) and not s["contract_version_touched"]:
        warnings.append("Contract sources/schema touched; check whether contractVersion needed a bump (src/contract/Version.h unchanged).")
    tree = git(repo, "ls-tree", "-r", "--name-only", args.head).splitlines()
    fixtures_exist = any(p.startswith("tests/scenes/") for p in tree)
    if s["contract_sources_touched"] and fixtures_exist and not s["contract_fixtures_touched"]:
        warnings.append("Contract sources touched without fixture changes in tests/scenes/.")
    if s["parameter_freeze_touched"]:
        warnings.append("Parameter freeze file touched: IDs are frozen once released; only additions are allowed.")
    if s["wav_files_added"] and any(not p.startswith("tests/golden/") for p in s["wav_files_added"]):
        warnings.append("WAV files added outside tests/golden/: CLAUDE.md forbids committing renders/datasets.")
    if s["large_binaries"]:
        warnings.append("Large binaries in diff: check they are not downloaded datasets (BRAS, SOFA originals).")
    for row in status_rows:
        if not row.startswith("+|"):
            continue
        cells = [c.strip() for c in row[1:].strip("|").split("|")]
        # | Phase | Title | Size | Status | PR | Date | Notes |
        if len(cells) >= 5 and cells[3].startswith("done") and not cells[4]:
            warnings.append(f"BUILD_PLAN row {cells[0]} set to `done` with an empty PR column.")
        if len(cells) >= 4 and cells[3].startswith("done"):
            plan_log = run(["git", "log", "-p", "--format=%H", rng, "--", "docs/BUILD_PLAN.md"], repo).stdout
            if not re.search(r"^\+\|\s*" + re.escape(cells[0]) + r"\s*\|.*\|\s*in progress\s*\|", plan_log, re.M):
                warnings.append(f"BUILD_PLAN row {cells[0]} reaches `done` without an `in progress` commit first (CLAUDE.md step 3).")
    if s["contract_sources_touched"]:
        def version_at(ref):
            txt = run(["git", "show", f"{ref}:src/contract/Version.h"], repo).stdout
            return re.findall(r"(kContractVersion\w*\s*=\s*[^;]+;)", txt)
        non_build = [f for f in s["contract_sources_touched"] if not f.endswith("CMakeLists.txt")]
        if version_at(merge_base) == version_at(args.head) and non_build:
            warnings.append("src/contract changed but the contract version constants in Version.h are unchanged: additive change needs a minor bump, breaking change a major bump.")
    bodies = git(repo, "log", "--format=%b%x00", rng).split("\x00")
    if subjects and all(not b.strip() for b in bodies):
        warnings.append("No commit in the range has a body; the PR description must carry the rationale instead.")
    if len(phases) > 1:
        warnings.append(f"Commits mention more than one phase: {phases}. One phase = one PR.")
    if not phases:
        warnings.append("No commit subject follows `phase-XX:`; cannot tell which phase this PR executes.")
    if s["claude_md_touched"]:
        warnings.append("CLAUDE.md changed: verify the build/test section stays accurate and no rule was weakened.")
    if s["phase_files_touched"]:
        warnings.append("A phase file changed: a session editing its own acceptance criteria is a red flag unless it only adds a split phase-XXb.")
    report["warnings"] = warnings

    # Helper: added lines per file from the diff.
    diff_text = git(repo, "diff", "--unified=0", rng)
    added_by_file = defaultdict(list)  # path -> [(line_no, text)]
    cur = None
    new_line = 0
    for line in diff_text.splitlines():
        if line.startswith("+++ "):
            cur = line[4:].strip()
            cur = cur[2:] if cur.startswith("b/") else cur
            continue
        m = re.match(r"^@@ -\d+(?:,\d+)? \+(\d+)(?:,\d+)? @@", line)
        if m:
            new_line = int(m.group(1))
            continue
        if cur is None or line.startswith("---"):
            continue
        if line.startswith("+"):
            added_by_file[cur].append((new_line, line[1:]))
            new_line += 1

    head_file_cache = {}

    def head_lines(path):
        if path not in head_file_cache:
            head_file_cache[path] = run(["git", "show", f"{args.head}:{path}"], repo).stdout.splitlines()
        return head_file_cache[path]

    func_re = re.compile(r"^(?:[A-Za-z_][\w:<>,\s\*&]*\s+)?([A-Za-z_][\w:~]*)\s*\([^;]*\)\s*(const)?\s*(noexcept)?\s*(override)?\s*\{?\s*$")

    def enclosing_function(path, line_no):
        """Best-effort name of the function containing line_no in the head version of a C++ file."""
        if not path.endswith(CPP_EXT):
            return ""
        lines = head_lines(path)
        for i in range(min(line_no, len(lines)) - 1, -1, -1):
            text = lines[i]
            if text.startswith((" ", "\t")) or not text.strip():
                continue
            if text.lstrip().startswith(("//", "#", "}", "namespace", "class ", "struct ", "template")):
                continue
            m = func_re.match(text.strip())
            if m:
                return m.group(1)
        return ""

    def scan(flags, path_filter, include_full_line=True):
        hits = []
        for path, lines in added_by_file.items():
            if not path_filter(path):
                continue
            for n, text in lines:
                stripped = text.strip()
                if stripped.startswith("//") or (stripped.startswith("#include") and path.endswith(CPP_EXT)):
                    continue
                for pat, why in flags:
                    if re.search(pat, text):
                        fn = enclosing_function(path, n)
                        # prepareToPlay / releaseResources / createEditor / constructors may allocate.
                        hot = bool(fn and re.search(r"processBlock|processBlockBypassed|::process\b|^process\b|render|IOCallback", fn)
                                   and not re.search(r"prepare|release|create|Editor", fn))
                        hits.append({"path": path, "line": n, "why": why, "text": text.strip()[:160],
                                     "function": fn, "likely_audio_thread": hot})
        return hits

    # 4. Boundary check on the head tree (not only the diff): includes crossing the contract boundary.
    boundary = []
    boundary_files_scanned = 0
    for p in tree:
        if not p.endswith(CPP_EXT):
            continue
        rules = []
        if p.startswith("src/sim/"):
            rules = [(r'#\s*include\s*[<"](module3d/|plugin/|juce_|juce/|JuceHeader)', "src/sim includes module3d/plugin/JUCE")]
        elif p.startswith("src/module3d/"):
            rules = [(r'#\s*include\s*[<"](sim/|plugin/|juce_|juce/|JuceHeader)', "src/module3d includes sim/plugin/JUCE")]
        elif p.startswith("src/contract/"):
            rules = [(r'#\s*include\s*[<"](sim/|module3d/|plugin/|juce_|juce/|JuceHeader)', "src/contract includes sim/module3d/plugin/JUCE")]
        elif p.startswith("src/cli/"):
            rules = [(r'#\s*include\s*[<"](plugin/|juce_|juce/|JuceHeader)', "src/cli includes plugin/JUCE (CLI must stay JUCE-free)")]
        if not rules:
            continue
        boundary_files_scanned += 1
        content = run(["git", "show", f"{args.head}:{p}"], repo).stdout
        for i, line in enumerate(content.splitlines(), 1):
            for pat, why in rules:
                if re.search(pat, line):
                    boundary.append({"path": p, "line": i, "why": why, "text": line.strip()})
    report["boundary_violations"] = boundary
    report["boundary_files_scanned"] = boundary_files_scanned

    # 5. NFR-8 scan: scene/preset/material identifiers inside src/sim at head.
    names = set(PRESET_WORDS)
    for p in tree:
        m = re.match(r"^(tests/scenes/(valid|validation)|resources/presets)/([A-Za-z0-9_\-]+)\.json$", p)
        if m:
            names.add(m.group(3))
    # material ids, if a library exists
    mat_path = "resources/materials.json"
    if mat_path in tree:
        try:
            mats = json.loads(run(["git", "show", f"{args.head}:{mat_path}"], repo).stdout)
            items = mats.get("materials", mats) if isinstance(mats, dict) else mats
            for item in items if isinstance(items, list) else []:
                if isinstance(item, dict) and "id" in item:
                    names.add(str(item["id"]))
        except Exception:  # noqa: BLE001 - best effort
            pass
    nfr8 = []
    nfr8_files_scanned = 0
    name_re = re.compile(r"(" + "|".join(re.escape(n) for n in sorted(names, key=len, reverse=True)) + r")", re.IGNORECASE)
    string_logic_re = re.compile(SIM_STRING_LOGIC)
    for p in tree:
        if not p.startswith("src/sim/") or not p.endswith(CPP_EXT):
            continue
        nfr8_files_scanned += 1
        content = run(["git", "show", f"{args.head}:{p}"], repo).stdout
        for i, line in enumerate(content.splitlines(), 1):
            if name_re.search(line):
                nfr8.append({"path": p, "line": i, "why": "scene/preset/material name", "text": line.strip()[:160]})
            elif string_logic_re.search(line):
                nfr8.append({"path": p, "line": i, "why": "string-keyed logic in sim (what is it keyed on?)", "text": line.strip()[:160]})
    report["nfr8_hits_in_sim"] = nfr8
    report["nfr8_files_scanned"] = nfr8_files_scanned
    report["nfr8_names_scanned"] = sorted(names)

    # 6. Audio-thread scan (added lines in audio-thread-adjacent files).
    report["audio_thread_scan"] = scan(
        AUDIO_THREAD_RED_FLAGS,
        lambda p: p.endswith(CPP_EXT) and (p.startswith(AUDIO_THREAD_PATH_HINTS) or "Convol" in p or "Realtime" in p),
    )

    # 7. Determinism scan (all added C++ and Python lines under src/ and tools/).
    report["determinism_scan"] = scan(
        DETERMINISM_RED_FLAGS,
        lambda p: (p.endswith(CPP_EXT) or p.endswith(".py")) and (p.startswith("src/") or p.startswith("tools/")),
    )

    # 8. Test-hygiene scan (tests, tools, docs).
    report["test_hygiene_scan"] = scan(
        TEST_HYGIENE_FLAGS,
        lambda p: p.startswith(("tests/", "tools/", "docs/", "src/")) and not p.endswith((".wav", ".bin", ".json")),
    )

    # 8b. Whole tests disabled per OS at head: a preprocessor guard immediately before TEST_CASE/SECTION.
    disabled = []
    for p in tree:
        if not (p.startswith("tests/") and p.endswith(CPP_EXT)):
            continue
        lines = head_lines(p)
        for i, line in enumerate(lines):
            if re.match(r"\s*#\s*if", line):
                look = " ".join(l.strip() for l in lines[i + 1:i + 4])
                if re.search(r"\bTEST_CASE\b|\bTEMPLATE_TEST_CASE\b|\bSCENARIO\b", look):
                    disabled.append({"path": p, "line": i + 1, "text": line.strip()})
    report["tests_guarded_by_preprocessor"] = disabled
    if disabled:
        warnings.append("A TEST_CASE sits directly under a preprocessor guard; phase criteria say tests run on 3 OSes.")

    # 9. Dependency pins (added lines in cmake, workflows, requirements).
    report["pin_scan"] = scan(
        PIN_FLAGS,
        lambda p: p.startswith(("cmake/", ".github/", "CMakeLists.txt")) or "requirements" in p,
    )

    if args.json:
        print(json.dumps(report, indent=2))
        return

    # ---- Text report ----
    def h(title):
        print(f"\n== {title} ==")

    print(f"review_context: {args.base}..{args.head} (merge-base {merge_base[:12]})")
    h("1. Phase")
    print(f"phases from commit subjects: {phases or 'none'}")
    for sline in subjects:
        print(f"  - {sline}")
    if off_pattern:
        print("subjects not following `phase-XX: ...`:")
        for sline in off_pattern:
            print(f"  ! {sline}")
    print("BUILD_PLAN status rows changed:")
    for l in status_rows or ["  (none)"]:
        print(f"  {l}")
    print(f"BUILD_PLAN §2/§6 rows touched: {report['phase']['build_plan_section2_or_6_touched']}")

    h("2. Changed files by area")
    for area in sorted(by_area):
        print(f"[{area}]")
        for f in by_area[area]:
            print(f"  +{f['added']:>5} -{f['deleted']:>5}  {f['path']}")

    h("3. Process signals")
    for k, v in report["signals"].items():
        if v:
            print(f"{k}: {v}")
    if warnings:
        print("warnings:")
        for w in warnings:
            print(f"  ! {w}")

    h("4. Boundary check (head tree)")
    print(f"  scanned {boundary_files_scanned} C++ files under src/contract, src/sim, src/module3d, src/cli")
    for b in boundary or [{"path": "(no violations)", "line": "", "why": "", "text": ""}]:
        print(f"  {b['path']}:{b['line']} {b['why']} {b['text']}")

    h("5. NFR-8: preset/scene/material names or string-keyed logic inside src/sim (head tree)")
    print(f"  scanned {nfr8_files_scanned} C++ files for {len(names)} names (fixtures, presets, materials, 'preset')")
    for x in nfr8 or [{"path": "(no hits)", "line": "", "why": "", "text": ""}]:
        print(f"  {x['path']}:{x['line']} [{x.get('why','')}] {x['text']}")

    h("6. Audio-thread red flags on added lines (inspect, not verdicts)")
    hot_hits = [x for x in report["audio_thread_scan"] if x.get("likely_audio_thread")]
    ctx_hits = [x for x in report["audio_thread_scan"] if not x.get("likely_audio_thread")]
    if not hot_hits:
        print("  (none in functions that look like audio callbacks)")
    for x in hot_hits:
        print(f"  {x['path']}:{x['line']} in {x['function']}() [{x['why']}] {x['text']}  <-- likely audio-thread function")
    if ctx_hits:
        print(f"  context only ({len(ctx_hits)} hits in prepareToPlay/constructors/editor/accessors or unknown functions; allocation is normal there):")
        for x in ctx_hits:
            where = f" in {x['function']}()" if x.get("function") else ""
            print(f"    {x['path']}:{x['line']}{where} [{x['why']}] {x['text']}")

    if disabled:
        h("8b. Tests under a preprocessor guard (head tree)")
        for x in disabled:
            print(f"  {x['path']}:{x['line']} {x['text']}")

    for title, key in [
        ("7. Determinism red flags (added lines)", "determinism_scan"),
        ("8. Test hygiene (added lines)", "test_hygiene_scan"),
        ("9. Dependency pin red flags (added lines; floating refs and unpinned requirements only)", "pin_scan"),
    ]:
        h(title)
        hits = report[key]
        if not hits:
            print("  (none)")
        for x in hits:
            where = f" in {x['function']}()" if x.get("function") else ""
            hot = "  <-- likely audio-thread function" if x.get("likely_audio_thread") else ""
            print(f"  {x['path']}:{x['line']}{where} [{x['why']}] {x['text']}{hot}")


if __name__ == "__main__":
    sys.exit(main())
