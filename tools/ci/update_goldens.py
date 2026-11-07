#!/usr/bin/env python3
"""The only way to update golden files in tests/golden/ (CLAUDE.md "Tests and golden files").

    python tools/ci/update_goldens.py --reason "Phase 04: tail now includes air absorption" \
        tools/acoustics/tests/test_something.py -k medium_room

Reruns the given pytest selection with golden update mode switched on (tools/acoustics/golden.py),
so every ``check_golden`` call rewrites its golden's metrics instead of comparing. Then it appends
an entry to tests/golden/CHANGELOG.md with the date, the reason, and each golden that was
created or changed (with the values that moved out of tolerance). Goldens whose values all stayed
within tolerance are listed as "rewritten, within tolerance".

Never use it to make a failing test pass unless the change in behaviour is intended; explain why in
the PR and add a change-log row to docs/BUILD_PLAN.md §6. Refused when the CI variable is set.
"""

from __future__ import annotations

import argparse
import datetime
import json
import os
import pathlib
import subprocess
import sys
import tempfile

REPO = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO))

from tools.acoustics import golden  # noqa: E402


def changelog_entry(reason: str, entries: list[dict], today: str) -> str:
    lines = [f"## {today}", "", f"Reason: {reason}", ""]
    for e in entries:
        if e.get("added"):
            lines.append(f"- `{e['name']}`: extended by {len(e['added'])} new key(s): "
                         + ", ".join(f"`{p}`" for p in e["added"][:40]) + (" …" if len(e["added"]) > 40 else ""))
        if e["created"]:
            lines.append(f"- `{e['name']}`: created")
        elif e["changed"]:
            moved = ", ".join(f"`{p}`" for p in e["changed"])
            lines.append(f"- `{e['name']}`: changed {moved}")
        else:
            lines.append(f"- `{e['name']}`: rewritten, " + ("pinned values within tolerance" if e.get("added") else "within tolerance"))
    return "\n".join(lines) + "\n\n"


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--reason", required=True, help="why the goldens change (goes into CHANGELOG.md)")
    parser.add_argument(
        "--changelog",
        type=pathlib.Path,
        default=None,
        help="changelog file (default: <golden dir>/CHANGELOG.md)",
    )
    parser.add_argument(
        "--extend",
        action="store_true",
        help="also pin keys the goldens do not have yet (e.g. a validation room added); pinned keys are never dropped",
    )
    parser.add_argument(
        "pytest_args",
        nargs=argparse.REMAINDER,
        help="tests to rerun in update mode: everything after the first path (or after --) goes to pytest",
    )
    args = parser.parse_args(argv)
    pytest_args = [a for a in args.pytest_args if a != "--"] if args.pytest_args[:1] == ["--"] else args.pytest_args
    if not pytest_args:
        parser.error("give the tests to rerun (pytest arguments)")

    reason = " ".join(args.reason.split())
    if len(reason) < 10:
        parser.error("--reason must explain the change (at least 10 characters)")
    if os.environ.get("CI"):
        print("update_goldens.py: refusing to update goldens in CI", file=sys.stderr)
        return 2

    changelog = args.changelog or (golden.golden_dir() / "CHANGELOG.md")
    with tempfile.TemporaryDirectory() as tmp:
        log_path = pathlib.Path(tmp) / "updates.jsonl"
        log_path.touch()
        env = dict(os.environ, **{golden.ENV_UPDATE_REASON: reason, golden.ENV_UPDATE_LOG: str(log_path)})
        if args.extend:
            env[golden.ENV_UPDATE_EXTEND] = "1"
        result = subprocess.run([sys.executable, "-m", "pytest", *pytest_args], cwd=REPO, env=env, check=False)
        entries = [json.loads(line) for line in log_path.read_text(encoding="utf-8").splitlines() if line.strip()]

    if result.returncode != 0:
        print(
            f"update_goldens.py: pytest exited with {result.returncode}; goldens it reached were still rewritten "
            "(see git diff). CHANGELOG.md not updated.",
            file=sys.stderr,
        )
        return result.returncode

    if not entries:
        print("update_goldens.py: the selected tests checked no golden; nothing updated", file=sys.stderr)
        return 1

    today = datetime.date.today().isoformat()
    text = changelog.read_text(encoding="utf-8") if changelog.is_file() else "# Golden file change log\n\n"
    changelog.parent.mkdir(parents=True, exist_ok=True)
    changelog.write_text(text + changelog_entry(reason, entries, today), encoding="utf-8")
    print(f"update_goldens.py: {len(entries)} golden(s) updated; logged in {changelog}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
