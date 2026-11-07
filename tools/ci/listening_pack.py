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


# Phases whose pack is not "every test scene through render_cli": the builder is called instead.
# phase-05e: the BRAS A/B pack (tools/validation/ab_pack.py; measured vs simulated, loudness-matched,
# key in key.txt; needs the BRAS RIRs, fetched by checksum by tools/validation/fetch_bras.py).
def _phase_05e(pack: pathlib.Path, binary: pathlib.Path) -> None:
    from tools.validation import ab_pack

    ab_pack.build(pack, binary=binary)


# phase-06: the real-time engine. A drum loop through medium_room (Phase 04 hybrid IR) rendered
# offline and through render_cli --realtime-emulation (random host blocks), which CI has already
# nulled; and a tone through an IR that switches every 0.5 s between living_room and
# concert_hall_box (30 ms equal-power crossfades, AQ4 / AX18).
PHASE_06_NOTES = (
    "Phase 06: the REAL-TIME convolution engine (what the plugin will run from Phase 07). Still the "
    "mono omni room preview of Phase 04 (both ears the same). (1) drums_medium_room_offline.wav and "
    "drums_medium_room_realtime.wav are the same drum loop through medium_room, rendered by the "
    "offline reference and by the real-time engine in random host block sizes. They must sound "
    "IDENTICAL: CI has already measured the difference (table below), so this is a sanity listen. "
    "(2) ir_switch_demo.wav is a steady low tone in a room that switches every 0.5 s between "
    "living_room (short decay, close) and concert_hall_box (long decay; its emitters are much "
    "farther away, so it is also about 29 dB quieter, AX2), starting with living_room. You should hear "
    "the room and the level change every half second, smoothly over 30 ms, with NO clicks, ticks or "
    "pops at the switch points. Both drum files share one playback gain, so they stay comparable."
)


def _phase_06(pack: pathlib.Path, binary: pathlib.Path, log=print) -> None:
    from tools.acoustics import clicks

    pack.mkdir(parents=True, exist_ok=True)
    dry_dir = pack / "dry"
    dry_dir.mkdir(exist_ok=True)
    drums = signals.to_stereo(*signals.drum_loop(FS))
    tone = signals.to_stereo(signals.sustained_tone(FS, 6.0))
    wav.write_float32(dry_dir / "drums.wav", drums.astype(np.float32), FS)
    wav.write_float32(dry_dir / "tone.wav", tone.astype(np.float32), FS)
    room = SCENES_DIR / "medium_room.json"

    def render(out: pathlib.Path, *args) -> np.ndarray:
        result = render_cli.run(binary, *args, "--out", out)
        if result.returncode != 0:
            raise RuntimeError(f"render_cli failed for {out.name}:\n{result.stderr}")
        data, _ = wav.read_float32(out)
        return data

    offline = render(pack / "drums_medium_room_offline.wav", "--scene", room, "--mode", "omni", "--in", dry_dir / "drums.wav")
    realtime = render(
        pack / "drums_medium_room_realtime.wav",
        "--scene", room, "--mode", "omni", "--in", dry_dir / "drums.wav", "--realtime-emulation", "--block", "random",
    )
    if offline.shape != realtime.shape:
        raise RuntimeError(f"offline {offline.shape} and realtime {realtime.shape} renders differ in shape")
    ref = offline.astype(np.float64)
    residual_db = 10 * np.log10(np.sum((realtime - ref) ** 2) / np.sum(ref**2))
    switch = render(
        pack / "ir_switch_demo.wav",
        "--scene", SCENES_DIR / "living_room.json", "--switch-scene", SCENES_DIR / "concert_hall_box.json",
        "--switch-every", "0.5", "--mode", "omni", "--in", dry_dir / "tone.wav", "--realtime-emulation",
    )
    found = clicks.detect_clicks(switch[:, 0].astype(np.float64), FS)

    rows = []
    # Playback safety (as the other packs): one common gain for the two drum files, its own for the demo.
    drum_peak = max(float(np.max(np.abs(offline))), float(np.max(np.abs(realtime))))
    for name, data, peak in (
        ("drums_medium_room_offline.wav", offline, drum_peak),
        ("drums_medium_room_realtime.wav", realtime, drum_peak),
        ("ir_switch_demo.wav", switch, float(np.max(np.abs(switch)))),
    ):
        if peak > 10 ** (PEAK_LIMIT_DBFS / 20):
            gain_db = PEAK_LIMIT_DBFS - 20 * np.log10(peak)
            wav.write_float32(pack / name, (data.astype(np.float64) * 10 ** (gain_db / 20)).astype(np.float32), FS)
            rows.append(f"{name}: SCALED by {gain_db:.1f} dB for playback (peak {20 * np.log10(peak):+.1f} dBFS)")
        else:
            rows.append(f"{name}: not scaled (peak {20 * np.log10(peak):+.1f} dBFS)")
    log(f"phase-06: realtime vs offline residual {residual_db:.1f} dB; click detector on ir_switch_demo: "
        f"{len(found['events'])} events, max {found['max_frame_dbfs']:.1f} dBFS")

    events = ", ".join(f"{e['time_s']:.3f} s ({e['level_dbfs']:.0f} dBFS)" for e in found["events"]) or "none"
    lines = [
        "SPATIAL SCENE LISTENING PACK - phase-06",
        "=" * 60,
        "",
        textwrap.fill(PHASE_06_NOTES, 78),
        "",
        "FILES",
        "-----",
        "dry/drums.wav          the dry drum loop (synthetic: kick, snare left, hi-hat right, 100 bpm)",
        "dry/tone.wav           the dry tone (110 + 220 + 330 Hz, 6 s, slow fades)",
        "drums_medium_room_offline.wav   offline reference render (Phase 04 room IR)",
        "drums_medium_room_realtime.wav  real-time engine, random host blocks of 1..2048 samples",
        "ir_switch_demo.wav     tone, room switches every 0.5 s (living_room <-> concert_hall_box)",
        "",
        "MEASURED",
        "--------",
        f"realtime vs offline: residual energy {residual_db:.1f} dB relative to the render (CI gate: -120 dB)",
        textwrap.fill(
            f"ir_switch_demo.wav, click detector (left channel; high-pass 2 kHz, 2 ms frames, floor -90 dBFS): "
            f"{len(found['events'])} event(s): {events}. Information, not a gate: a 30 ms crossfade has slope "
            "corners at its ends, whose high-frequency splatter for this tone is estimated at about -77 dBFS in a "
            "2 ms frame (about 74 dB below the tone), right at the switch times. A real click (a step or a spike) "
            "would show as a much louder event or one away from the switch times. Your ears decide.",
            78,
        ),
        "",
    ] + rows
    (pack / "README.txt").write_text("\n".join(lines) + "\n", encoding="utf-8")


SPECIAL_BUILDERS = {"phase-05e": _phase_05e, "phase-06": _phase_06}


def build(out_root: pathlib.Path, phase: str, binary: pathlib.Path, log=print) -> pathlib.Path:
    pack = out_root / phase
    if phase in SPECIAL_BUILDERS:
        SPECIAL_BUILDERS[phase](pack, binary)
        return pack
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
