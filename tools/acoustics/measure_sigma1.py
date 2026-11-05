"""Measure sigma1(EDT) and sigma1(C80) of the Phase 04 hybrid IR (BUILD_PLAN AX19).

For each of the six Phase 04 test rooms at 44.1 and 96 kHz: n >= 51 realisations (consecutive tail
seeds) of the full hybrid omni IR (emitter 0, output 0), each analysed on its own with
``metrics.room_metrics``; sigma1(EDT) is the sample standard deviation in % of the mean, sigma1(C80) in
dB (T30 is recorded too, as information). With n = 51 the relative standard error of a sigma1
estimate, ~1 / sqrt(2 (n - 1)), is 10 %. The result is committed as
``tools/acoustics/data/phase04_sigma1.json`` and sets R of the sample-rate EDT/C80 gates.

    python -m tools.acoustics.measure_sigma1 [--n 51] [--out tools/acoustics/data/phase04_sigma1.json]
"""

from __future__ import annotations

import argparse
import json
import pathlib
import sys

from . import bands, ensembles, metrics, render_cli

REPO = pathlib.Path(__file__).resolve().parents[2]
ROOMS = ("dead_booth", "living_room", "classroom", "club", "concert_hall_box", "stone_box")
RATES = (44100, 96000)
FIRST_SEED = 9_000_000
DEFAULT_OUT = REPO / "tools" / "acoustics" / "data" / "phase04_sigma1.json"


def measure(binary: pathlib.Path, room: str, rate: int, n: int) -> dict:
    scene = REPO / "tests" / "scenes" / "valid" / f"{room}.json"
    per_metric: dict[str, dict[str, list]] = {m: {bands.band_key(f): [] for f in bands.OCTAVE_BANDS_HZ} for m in ("EDT", "C80", "T30")}
    for first in range(0, n, 32):
        count = min(32, n - first)
        irs, fs = ensembles.render_ensemble(binary, scene, FIRST_SEED + first, count, rate)
        for h in irs[:, 0, :]:
            m = metrics.room_metrics(h, fs)
            for name in per_metric:
                for key in per_metric[name]:
                    per_metric[name][key].append(m["bands"][key][name])
    return {
        "n": n,
        "EDT_pct": {k: ensembles.sigma1(v, True) for k, v in per_metric["EDT"].items()},
        "C80_dB": {k: ensembles.sigma1(v, False) for k, v in per_metric["C80"].items()},
        "T30_pct": {k: ensembles.sigma1(v, True) for k, v in per_metric["T30"].items()},
    }


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--n", type=int, default=51)
    parser.add_argument("--out", type=pathlib.Path, default=DEFAULT_OUT)
    args = parser.parse_args(argv)
    binary = render_cli.find_render_cli()
    if binary is None:
        print("render_cli not found (set RENDER_CLI or build the cli preset)", file=sys.stderr)
        return 1
    result = {
        "description": "AX19: single-realisation scatter of EDT (% of the mean) and C80 (dB) of the Phase 04 "
        "hybrid omni IR (emitter 0, output 0), metrics.room_metrics per realisation, consecutive tail seeds "
        f"from {FIRST_SEED}. Measured by tools/acoustics/measure_sigma1.py.",
        "rooms": {},
    }
    for room in ROOMS:
        result["rooms"][room] = {}
        for rate in RATES:
            result["rooms"][room][str(rate)] = measure(binary, room, rate, args.n)
            print(room, rate, json.dumps(result["rooms"][room][str(rate)]["EDT_pct"]), flush=True)
    args.out.parent.mkdir(parents=True, exist_ok=True)
    args.out.write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    print(f"wrote {args.out}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
