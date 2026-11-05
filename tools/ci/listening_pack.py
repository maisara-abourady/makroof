#!/usr/bin/env python3
"""Build the listening pack: fixed test signals (and your own WAVs) rendered through every scene in
tests/scenes/valid/ with render_cli, plus a README.txt that says what each file should sound like.

    python tools/ci/listening_pack.py [--phase phase-02] [--out build/listening-pack] [--render-cli PATH]

Output: <out>/<phase>/dry/<signal>.wav (the inputs), <out>/<phase>/<scene>/<signal>.wav (renders),
<out>/<phase>/README.txt. CI uploads <out> as the `listening-pack` artifact.

Your own material: put stereo (or mono, duplicated to both sides) WAVs at 44.1/48/88.2/96 kHz in
tools/ci/listening_inputs/ (gitignored, never committed) and rerun locally.

Later phases: add the phase's expectations to PHASE_NOTES, its render_cli mode to PHASE_MODES if
it isn't the scene's own outputMode (and signals to SIGNALS if needed).
"""

from __future__ import annotations

import argparse
import pathlib
import sys
import textwrap

import numpy as np

REPO = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO))

from tools.acoustics import render_cli, signals, wav  # noqa: E402

FS = 48000
SCENES_DIR = REPO / "tests" / "scenes" / "valid"
INPUTS_DIR = REPO / "tools" / "ci" / "listening_inputs"
SUPPORTED_RATES = (44100, 48000, 88200, 96000)
# Renders that peak above this are scaled down to it, and the README says so.
PEAK_LIMIT_DBFS = -1.0


def _pink_bursts() -> np.ndarray:
    # Four 0.5 s bursts: left only, right only, both, both.
    mono = signals.pink_bursts(FS, burst_s=0.5, gap_s=0.5, count=4, level_dbfs=-12.0, seed=11)
    seg = FS  # one burst + gap
    left, right = mono.copy(), mono.copy()
    right[:seg] = 0.0
    left[seg : 2 * seg] = 0.0
    return signals.to_stereo(left, right)


def _clicks() -> np.ndarray:
    # Eight clicks every 0.5 s, alternating left, right, left, right ...
    mono = signals.clicks(FS, interval_s=0.5, count=8, level_dbfs=-6.0)
    left, right = mono.copy(), mono.copy()
    for i, p in enumerate(signals.click_positions(FS, interval_s=0.5, count=8)):
        (right if i % 2 == 0 else left)[p] = 0.0
    return signals.to_stereo(left, right)


def _sweep() -> np.ndarray:
    s = signals.exp_sine_sweep(FS, 20.0, 20000.0, 5.0) * 10 ** (-12 / 20)
    return signals.to_stereo(np.concatenate([s, np.zeros(FS // 2)]))


def _tone() -> np.ndarray:
    return signals.to_stereo(signals.sustained_tone(FS, 6.0))


# name -> (generator, description of the dry signal)
SIGNALS = {
    "pink_bursts": (
        _pink_bursts,
        "Four half-second bursts of pink noise (a soft 'shhh'), one per second: the first from the "
        "LEFT only, the second from the RIGHT only, then two from both sides. Smooth edges, no clicks.",
    ),
    "clicks": (
        _clicks,
        "Eight sharp single-sample clicks every half second, alternating LEFT, RIGHT, LEFT, RIGHT...",
    ),
    "sweep": (
        _sweep,
        "A 5-second sine sweep from a deep 20 Hz rumble up to 20 kHz (inaudible at the very top), "
        "same in both ears, then half a second of silence. Rises smoothly without warbles or crackle.",
    ),
    "tone": (
        _tone,
        "Six seconds of a steady low hum (110 + 220 + 330 Hz) in both ears, fading in and out over "
        "half a second. It must be perfectly steady: no clicks, ticks or level wobble.",
    ),
}

# render_cli --mode per phase (default: the scene's own outputMode).
PHASE_MODES = {
    "phase-03": "omni-early",
    "phase-04": "omni",
}

PHASE_NOTES = {
    "phase-02": (
        "Phase 02: the engine is a STUB (dry pass-through). Every rendered file must sound IDENTICAL "
        "to its dry version in dry/, for every scene: no room, no echo, no level change, left stays "
        "left and right stays right. The table at the end lists the measured difference (it should "
        "say 'bit-identical' everywhere)."
    ),
    "phase-03": (
        "Phase 03: EARLY REFLECTIONS ONLY (image-source model, omni receiver). Both ears get the same "
        "signal (a mono room preview): left and right inputs are rendered from where the L and R "
        "emitters stand, but you hear them through one omni microphone, so the stereo image "
        "collapses to the centre. There is no reverberant tail yet (Phase 04), so every sound "
        "stops abruptly after its last echo; that is expected. What to listen for: on the clicks, a "
        "dense cluster of echoes right after each click in small_room, spreading out and arriving "
        "later in medium_room and large_hall; asymmetric_materials duller than medium_room; "
        "open_field a dry click with a single ground reflection right after it; on pink_bursts no "
        "pitched ringing, except a flutter (a rapid repeating echo) between hard parallel walls, "
        "which is physically correct. Level follows distance (AX2): far scenes are quieter."
    ),
    "phase-04": (
        "Phase 04: the FULL ROOM (early reflections + statistical late tail), still a mono omni "
        "preview: both ears get the same signal, so the stereo image collapses to the centre. What to "
        "listen for: (1) decays sound SMOOTH, not grainy, metallic or fluttery in the tail; "
        "(2) the six test rooms dead_booth, living_room, classroom, club, concert_hall_box and "
        "stone_box are clearly ordered from dead (about 0.2 s) to very reverberant (about 6 s); "
        "(3) on clicks, no audible 'seam' where the early echoes hand over to the tail (a few tens of "
        "ms after each click in small rooms, up to ~160 ms in concert_hall_box); (4) stone_box (hard "
        "surfaces) sounds brighter in the tail than concert_hall_box (audience floor). open_field "
        "has no tail (a dry click and its ground reflection). edge_values is a contract-limits "
        "test scene (absorption alternating 0.01 / 1.0 between bands): expect an odd, uneven tail."
    ),
}


def _user_inputs(log) -> dict[str, tuple[np.ndarray, int]]:
    found = {}
    if not INPUTS_DIR.is_dir():
        return found
    for path in sorted(INPUTS_DIR.glob("*.wav")):
        data, fs = wav.read(path)
        if fs not in SUPPORTED_RATES:
            log(f"skipping {path.name}: sample rate {fs} Hz is not supported")
            continue
        if data.shape[1] == 1:
            data = np.repeat(data, 2, axis=1)
        elif data.shape[1] != 2:
            log(f"skipping {path.name}: {data.shape[1]} channels (need mono or stereo)")
            continue
        found[f"user_{path.stem}"] = (data, fs)
    return found


def build(out_root: pathlib.Path, phase: str, binary: pathlib.Path, log=print) -> pathlib.Path:
    pack = out_root / phase
    dry_dir = pack / "dry"
    dry_dir.mkdir(parents=True, exist_ok=True)
    scenes = sorted(p for p in SCENES_DIR.glob("*.json") if not p.name.startswith("_"))
    if not scenes:
        raise RuntimeError(f"no scenes in {SCENES_DIR}")

    inputs: dict[str, tuple[np.ndarray, int, str]] = {}
    for name, (make, description) in SIGNALS.items():
        inputs[name] = (make(), FS, description)
    for name, (data, fs) in _user_inputs(log).items():
        inputs[name] = (data, fs, "Your own file from tools/ci/listening_inputs/.")

    rows = []
    for name, (data, fs, _) in inputs.items():
        dry_path = dry_dir / f"{name}.wav"
        wav.write_float32(dry_path, data, fs)
        dry, _ = wav.read_float32(dry_path)
        for scene in scenes:
            out_path = pack / scene.stem / f"{name}.wav"
            out_path.parent.mkdir(parents=True, exist_ok=True)
            mode = ("--mode", PHASE_MODES[phase]) if phase in PHASE_MODES else ()
            result = render_cli.run(binary, "--scene", scene, "--in", dry_path, "--out", out_path, *mode)
            if result.returncode != 0:
                raise RuntimeError(f"render_cli failed for {scene.name} / {name}:\n{result.stderr}")
            rendered, _ = wav.read_float32(out_path)
            # Playback safety, not part of the render: a file peaking above PEAK_LIMIT_DBFS is scaled
            # down to it (AX2 keeps the engine's level physical, and a reflective room can sum
            # well above 0 dBFS). The table says how much.
            peak = float(np.max(np.abs(rendered))) if rendered.size else 0.0
            scaled = ""
            if peak > 10 ** (PEAK_LIMIT_DBFS / 20):
                gain_db = PEAK_LIMIT_DBFS - 20 * np.log10(peak)
                rendered = (rendered.astype(np.float64) * 10 ** (gain_db / 20)).astype(np.float32)
                wav.write_float32(out_path, rendered, fs)
                scaled = f"; SCALED by {gain_db:.1f} dB for playback (render peaked at {20 * np.log10(peak):+.1f} dBFS)"
            if rendered.shape == dry.shape and rendered.tobytes() == dry.tobytes():
                diff = "bit-identical"
            else:
                n = min(len(rendered), len(dry))
                residual = np.max(np.abs(rendered[:n].astype(np.float64) - dry[:n])) if n else 0.0
                level = 20 * np.log10(residual) if residual > 0 else -np.inf
                diff = f"differs: max |render - dry| = {level:.1f} dBFS, length {len(rendered)} vs {len(dry)}"
            diff += scaled
            rows.append((scene.stem, name, diff))
            log(f"{scene.stem}/{name}.wav: {diff}")

    lines = [
        f"SPATIAL SCENE LISTENING PACK - {phase}",
        "=" * 60,
        "",
        textwrap.fill(PHASE_NOTES.get(phase, f"{phase}: see the phase's listening checklist in its PR."), 78),
        "",
        "Folders: dry/ holds the input signals. Every other folder is one scene from",
        "tests/scenes/valid/ and holds the same signals rendered through that scene.",
        "All files are 32-bit float WAV. Listen on headphones at a moderate level",
        "(the clicks are loud and sharp; the sweep's top end is inaudible).",
        f"A render that would peak above {PEAK_LIMIT_DBFS:g} dBFS is scaled down to that peak, so",
        "nothing clips; the table at the end lists each such file and the gain applied.",
        "",
        "SIGNALS",
        "-------",
    ]
    for name, (_, fs, description) in inputs.items():
        lines += [f"{name}.wav ({fs} Hz)", textwrap.fill(description, 78, initial_indent="    ", subsequent_indent="    "), ""]
    lines += ["SCENES", "------"] + [f"{s.stem}/" for s in scenes] + ["", "MEASURED DIFFERENCE TO DRY", "--------------------------"]
    lines += [f"{scene}/{name}.wav: {diff}" for scene, name, diff in rows]
    (pack / "README.txt").write_text("\n".join(lines) + "\n", encoding="utf-8")
    return pack


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--phase", default="phase-02")
    parser.add_argument("--out", type=pathlib.Path, default=REPO / "build" / "listening-pack")
    parser.add_argument("--render-cli", type=pathlib.Path, default=None)
    args = parser.parse_args(argv)
    binary = args.render_cli or render_cli.find_render_cli()
    if binary is None or not binary.is_file():
        print("listening_pack.py: render_cli not found (build it: cmake --preset cli && cmake --build --preset cli)", file=sys.stderr)
        return 1
    pack = build(args.out, args.phase, binary)
    print(f"listening pack written to {pack}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
