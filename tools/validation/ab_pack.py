"""Phase-05 A/B listening pack (scope 5): self-generated dry material convolved with the measured
BRAS RIR and with the simulated IR of the same pair, loudness-matched (ITU-R BS.1770-4), named
A_*/B_* in a seeded random order, with the key in key.txt.

    python tools/validation/ab_pack.py [--out build/listening-pack/phase-05]

Omni IRs, so only monaural attributes can be compared (reverberance, clarity, coloration); level
is removed by the loudness matching. One pair per room (LS1, MP1; initial α). The offset removed
per item (dB) is written to key.txt as a property of the playback; it is not a G error (G is not
evaluable on BRAS: levels manually corrected by 6 dB).
"""

from __future__ import annotations

import argparse
import pathlib
import sys

import numpy as np
import scipy.signal as sg

HERE = pathlib.Path(__file__).resolve().parent
REPO = HERE.parents[1]
sys.path.insert(0, str(REPO))

from tools.acoustics import loudness, render_cli, signals, wav  # noqa: E402
from tools.validation import fetch_bras, run_validation as rv  # noqa: E402

FS = rv.FS
TARGET_LKFS = -23.0
PAIRS = (("CR2", "LS1", "MP1"), ("CR3", "LS1", "MP1"), ("CR4", "LS1", "MP1"))


def plucked_melody(fs: float, seed: int = 3) -> np.ndarray:
    """A short self-generated melody (Karplus-Strong plucks): transient, tonal, sparse."""
    rng = np.random.default_rng(seed)
    notes = [220.0, 277.18, 329.63, 440.0, 329.63, 277.18, 246.94, 293.66]
    out = np.zeros(int(4.5 * fs))
    for k, f0 in enumerate(notes):
        n = int(fs / f0)
        buf = rng.uniform(-1, 1, n)
        dur = int(0.9 * fs)
        y = np.zeros(dur)
        for i in range(dur):
            y[i] = buf[i % n]
            buf[i % n] = 0.996 * 0.5 * (buf[i % n] + buf[(i + 1) % n])
        s = int(k * 0.5 * fs)
        out[s : s + dur] += y[: max(0, min(dur, out.size - s))]
    return 0.5 * out / np.max(np.abs(out))


def materials(fs: float) -> dict:
    # short bursts with long gaps expose the decay; plucks expose clarity and coloration
    return {"plucks": plucked_melody(fs), "noisebursts": signals.pink_bursts(fs, burst_s=0.25, gap_s=1.75, count=2)}


def matched(x: np.ndarray) -> tuple[np.ndarray, float]:
    lk = loudness.integrated_loudness(x, FS)
    g = TARGET_LKFS - lk
    return x * 10 ** (g / 20), g


def build(out: pathlib.Path, seed: int = 2026, binary=None) -> None:
    binary = binary or render_cli.find_render_cli()
    if binary is None:
        raise SystemExit("render_cli not found")
    cache = fetch_bras.cache_dir()
    fetch_bras.fetch(["rirs"], cache)
    out.mkdir(parents=True, exist_ok=True)
    rng = np.random.default_rng(seed)
    key = ["Phase 05 A/B key (do not open before listening). Offsets: gain applied for -23 LKFS (BS.1770-4).", ""]
    for room, s, r in PAIRS:
        scene = rv.SCENES / f"bras_{room.lower()}_{s.lower()}_{r.lower()}.json"
        if not scene.exists():  # no valid reduction for this room yet (bras_mapping.md §5)
            key.append(f"{room}_{s}_{r}: no scene yet (geometry not accepted by bras_mapping.md §2; the room stays selected)")
            continue
        h_sim = rv.render(binary, scene)
        h_meas = rv.measured(cache, room, s, r)
        for mname, dry in materials(FS).items():
            ys = sg.fftconvolve(dry, h_sim)
            ym = sg.fftconvolve(dry, h_meas)
            (ys, gs), (ym, gm) = matched(ys), matched(ym)
            peak = max(np.max(np.abs(ys)), np.max(np.abs(ym)))
            if peak > 0.99:  # common attenuation keeps the match
                ys, ym = ys * 0.99 / peak, ym * 0.99 / peak
            first_is_sim = bool(rng.integers(0, 2))
            a, b = (ys, ym) if first_is_sim else (ym, ys)
            tag = f"{room}_{s}_{r}_{mname}"
            wav.write_float32(out / f"A_{tag}.wav", a.astype(np.float32)[:, None], FS)
            wav.write_float32(out / f"B_{tag}.wav", b.astype(np.float32)[:, None], FS)
            key.append(f"{tag}: A = {'simulated' if first_is_sim else 'measured'}, B = {'measured' if first_is_sim else 'simulated'}; "
                       f"offset removed: simulated {gs:+.1f} dB, measured {gm:+.1f} dB (difference {gs - gm:+.1f} dB)")
    (out / "key.txt").write_text("\n".join(key) + "\n")
    (out / "README.txt").write_text(
        "Phase 05 A/B pack. Headphones. For each A/B pair: can you tell which is the real room? Note what differs\n"
        "(brightness, decay length, early 'slap', graininess) before opening key.txt. Omni IRs: compare reverberance,\n"
        "clarity and coloration only (monaural listening exaggerates reflection coloration, Blauert §4.4.2).\n"
        "Measured IRs: BRAS (CC BY-SA 4.0, DOI 10.14279/depositonce-6726.3). Dry material is self-generated.\n")
    print("wrote", out)


def main(argv=None):
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", default=str(REPO / "build" / "listening-pack" / "phase-05e"))
    a = ap.parse_args(argv)
    build(pathlib.Path(a.out))


if __name__ == "__main__":
    main()
