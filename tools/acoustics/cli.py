"""Command line for the analysis tools (prints JSON to stdout):

    python -m tools.acoustics metrics ir.wav [--channel N]
    python -m tools.acoustics compare reference.wav test.wav [--channel N] [--peaks 20]
    python -m tools.acoustics clicks render.wav [--threshold-db 20]

``metrics`` and ``compare`` analyse one channel (default 0; render_cli --ir files have
emitter x output channels, so channel 0 is L -> output 0). ``clicks`` checks every channel and
exits with status 1 when any click is found, so scripts can use it as a gate.
"""

from __future__ import annotations

import argparse
import json
import sys

from . import clicks as _clicks
from . import compare as _compare
from . import metrics as _metrics
from . import wav as _wav


def _channel(path: str, channel: int):
    data, fs = _wav.read(path)
    if not 0 <= channel < data.shape[1]:
        raise SystemExit(f"{path}: has {data.shape[1]} channel(s), no channel {channel}")
    return data[:, channel], fs


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(prog="python -m tools.acoustics", description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="command", required=True)

    p = sub.add_parser("metrics", help="ISO 3382-1 metrics of an IR")
    p.add_argument("ir")
    p.add_argument("--channel", type=int, default=0)

    p = sub.add_parser("compare", help="compare two IRs")
    p.add_argument("reference")
    p.add_argument("test")
    p.add_argument("--channel", type=int, default=0)
    p.add_argument("--peaks", type=int, default=20)

    p = sub.add_parser("clicks", help="click detector for sustained-tone renders")
    p.add_argument("wav")
    p.add_argument("--threshold-db", type=float, default=_clicks.DEFAULT_THRESHOLD_DB)

    args = parser.parse_args(argv)
    status = 0
    if args.command == "metrics":
        h, fs = _channel(args.ir, args.channel)
        result = _metrics.room_metrics(h, fs)
    elif args.command == "compare":
        a, fs_a = _channel(args.reference, args.channel)
        b, fs_b = _channel(args.test, args.channel)
        if fs_a != fs_b:
            raise SystemExit(f"sample rates differ: {fs_a} vs {fs_b}")
        result = _compare.compare_irs(a, b, fs_a, peaks=args.peaks)
    else:
        data, fs = _wav.read(args.wav)
        result = _clicks.detect_clicks_multi(data, fs, threshold_db=args.threshold_db)
        if any(ch["events"] for ch in result["channels"]):
            status = 1
    json.dump(result, sys.stdout, indent=2)
    sys.stdout.write("\n")
    return status


if __name__ == "__main__":
    sys.exit(main())
