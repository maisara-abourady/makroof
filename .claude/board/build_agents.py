#!/usr/bin/env python3
"""Generate the nine seat agents of the board from their persona files.

Each `.claude/agents/seat<n>-*.md` is: a frontmatter block (name, description, tools) + the shared
board protocol (`docs/board/seat-protocol.md`) + the persona's runnable part, which is everything in
`docs/board/seat-<n>-*.md` before its `## 19` heading (sections 0 to 18; sections 19 and 20 and the
appendices are the audit trail and stay in docs/board only, as each persona's own instructions say).

The persona files are Maisara's build artefacts and are never edited; change the protocol or this
table and regenerate. Run after any change to a persona, the protocol or this file:

    python3 .claude/board/build_agents.py            # write the agent files
    python3 .claude/board/build_agents.py --check    # exit 1 if any agent file is stale

This script lives under .claude/ (inert for the CI fingerprint) and is run by hand, so that no CI
step reads the agent prompts (tools/ci/ci_fingerprint.py explains the rule).
"""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
BOARD_DIR = REPO / "docs" / "board"
AGENTS_DIR = REPO / ".claude" / "agents"
PROTOCOL = BOARD_DIR / "seat-protocol.md"
CUT_HEADING = "## 19"  # first line starting with this ends the runnable part of a persona
TOOLS = "Read, Grep, Glob"

# (agent name, persona file, description). The description is what the orchestrator and the decider
# read when they choose whom to convene, so it lists the seat's subject matters (from its §18).
SEATS: list[tuple[str, str, str]] = [
    (
        "seat1-perceptual-gatekeeper",
        "seat-1-limen-the-perceptual-gatekeeper.md",
        "Seat 1 of the board: Limen, the perceptual gatekeeper. Convened by the decider when a subject "
        "matter rests on what the target listener can hear or prefers: audibility of a detail or "
        "parameter, JNDs and the conditions they hold under, blind-test paradigm, listeners, signals and "
        "strictness, keep/cut/test decisions, acceptance tests for the other seats, any claim of realism, "
        "plausibility or preference. Gives its ranking, present and future tension ratings, evidence, "
        "conditions of acceptance and hand-offs; argues its own case; never decides or edits.",
    ),
    (
        "seat2-engine-architect",
        "seat-2-scene-to-response-architect.md",
        "Seat 2 of the board: the scene-to-response architect. Convened when a subject matter touches how "
        "the simulator turns geometry and materials into a room response: geometric, wave or hybrid "
        "methods and the Schroeder-frequency split, image-source order, scattering, diffraction, late-tail "
        "statistics, material words to coefficient ranges, validation against measured rooms (BRAS, round "
        "robins, the circularity trap), the representation handed to the renderer, the simulator's compute "
        "budget and recompute time. Gives its ranking, present and future tension ratings, evidence, "
        "conditions of acceptance and hand-offs; argues its own case; never decides or edits.",
    ),
    (
        "seat3-reverb-renderer",
        "seat-3-the-reverb-renderer.md",
        "Seat 3 of the board: the reverb renderer. Convened for turning a computed response into audio at "
        "the listener: FDN, convolution or hybrid architecture, decay matching, early-reflection rendering, "
        "time variance under motion and automation (crossfades, zipper, clicks, metallic tails), coloration, "
        "channel spreading, per-instance CPU cost, and the listening validation of a rendering design. "
        "Gives its ranking, present and future tension ratings, evidence, conditions of acceptance and "
        "hand-offs; argues its own case; never decides or edits.",
    ),
    (
        "seat4-chain-keeper",
        "seat-4-the-chain-keeper.md",
        "Seat 4 of the board: the chain keeper (delivery to the ear). Convened for how the render reaches "
        "the real listener: binaural rendering, HRTF dataset choice and licence, headphone compensation, "
        "externalisation, head tracking and its latency, loudspeaker decoding and layouts, Ambisonics order "
        "budgets, object and scene export formats, cross-format loudness and timbre parity, and the "
        "listening tests that prove them. Gives its ranking, present and future tension ratings, evidence, "
        "conditions of acceptance and hand-offs; argues its own case; never decides or edits.",
    ),
    (
        "seat5-deadline-keeper",
        "seat-5-the-deadline-keeper.md",
        "Seat 5 of the board: the deadline keeper (real-time plugin architect). Convened for anything on or "
        "beside the audio thread: real-time safety, lock-free hand-off, worst-case callback time, threading "
        "topology, host conformance (pluginval, auval, state, automation, undo, bus layouts), offline equals "
        "real-time, framework and plugin-format choices, CI gates and sanitizers, platform transitions, and "
        "review of real-time code. Gives its ranking, present and future tension ratings, evidence, "
        "conditions of acceptance and hand-offs; argues its own case; never decides or edits.",
    ),
    (
        "seat6-canvas-designer",
        "seat-6-the-canvas-designer.md",
        "Seat 6 of the board: the canvas designer. Convened for anything user-facing: which controls exist "
        "and which stay hidden, their names, ranges, defaults and couplings, the canvas metaphor and "
        "interaction logic, presets and profiles, the automation and motion model, DAW workflow, "
        "time-to-first-plausible-scene, and competitor teardowns on the same dimensions. Gives its ranking, "
        "present and future tension ratings, evidence, conditions of acceptance and hand-offs; argues its "
        "own case; never decides or edits.",
    ),
    (
        "seat7-founder",
        "seat-7-keel-the-indie-deep-tech-founder.md",
        "Seat 7 of the board: Keel, the indie deep-tech founder. Convened for the business of the product and "
        "the founder's capacity: price and tiers, free product, copy protection, channels and partnerships, "
        "licensing, platform order, release cadence, cost floor and runway, capital and exit, public wording "
        "and marketing claims, what one founder can sustain, and the schedule and complexity cost of an "
        "option. Gives its ranking, present and future tension ratings, evidence, conditions of acceptance "
        "and hand-offs; argues its own case; never decides or edits.",
    ),
    (
        "seat8-storyteller",
        "seat-8-vantage-the-spatial-storyteller.md",
        "Seat 8 of the board: Vantage, the spatial storyteller (the expert user). Convened when a decision "
        "shapes what a producer or sound designer does with the product: whose ears the audience hears "
        "through, point of view, anchor, depth, density, contrast, transitions, translation to the "
        "listener's chain, workflow requirements, and which features serve storytellers and which will "
        "never be used. Critiques first, advises on workflow second. Gives its ranking, present and future "
        "tension ratings, evidence, conditions of acceptance and hand-offs; argues its own case; never "
        "decides or edits.",
    ),
    (
        "seat9-room-acoustician",
        "seat-9-the-audible-room.md",
        "Seat 9 of the board: the audible room (room acoustician). Convened for real rooms as references: "
        "which geometry and material choices are audible at a listening position and by how much, early "
        "structure versus decay, occupancy, bass and seat-dip, material-library provenance and uncertainty "
        "bounds, preset validation against measured rooms, diagnosing complaints, and which room and "
        "material controls are worth exposing. Gives its ranking, present and future tension ratings, "
        "evidence, conditions of acceptance and hand-offs; argues its own case; never decides or edits.",
    ),
]


def runnable_part(persona: str, source: Path) -> str:
    lines = persona.splitlines()
    for i, line in enumerate(lines):
        if line.startswith(CUT_HEADING):
            return "\n".join(lines[:i]).rstrip() + "\n"
    raise SystemExit(f"{source}: no '{CUT_HEADING}' heading; cannot find the end of sections 0-18")


def render(name: str, description: str, protocol: str, persona_runnable: str, seat_no: int, source: Path) -> str:
    front = (
        "---\n"
        f"name: {name}\n"
        f"description: {description}\n"
        f"tools: {TOOLS}\n"
        "---\n"
    )
    note = (
        f"<!-- Generated by .claude/board/build_agents.py from docs/board/{source.name} (sections 0-18) and\n"
        "     docs/board/seat-protocol.md. Do not edit by hand: change the source and regenerate. -->\n\n"
    )
    bridge = (
        "\n---\n\n"
        f"# Your persona: Seat {seat_no}\n\n"
        "Everything below is the persona built for your seat. Its sections 19 and 20 and its appendices "
        f"(the evidence register in full, the test log, the research trail) are in `docs/board/{source.name}`; "
        "read them there when you need a source expanded.\n\n"
    )
    return front + note + protocol.rstrip() + "\n" + bridge + persona_runnable


def build() -> dict[Path, str]:
    protocol = PROTOCOL.read_text(encoding="utf-8")
    out: dict[Path, str] = {}
    for seat_no, (name, persona_file, description) in enumerate(SEATS, start=1):
        source = BOARD_DIR / persona_file
        persona = source.read_text(encoding="utf-8")
        out[AGENTS_DIR / f"{name}.md"] = render(name, description, protocol, runnable_part(persona, source), seat_no, source)
    return out


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--check", action="store_true", help="report stale agent files instead of writing them")
    args = parser.parse_args(argv)
    generated = build()
    stale = [p for p, text in generated.items() if not p.exists() or p.read_text(encoding="utf-8") != text]
    if args.check:
        for p in stale:
            print(f"stale: {p.relative_to(REPO)}")
        print("ok" if not stale else f"{len(stale)} agent file(s) stale; run build_agents.py")
        return 1 if stale else 0
    AGENTS_DIR.mkdir(parents=True, exist_ok=True)
    for p, text in generated.items():
        p.write_text(text, encoding="utf-8")
        print(f"wrote {p.relative_to(REPO)} ({len(text.encode('utf-8'))} bytes)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
