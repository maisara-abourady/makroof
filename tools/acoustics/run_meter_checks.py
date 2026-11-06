"""Run the phase-05 scope 7 meter checks and write tools/acoustics/data/phase05_meter_checks.json
(leak calibration, paired noise test cases A and B, simulated-EDC check). Deterministic (seeded).

    python -m tools.acoustics.run_meter_checks            # everything (leak calibration takes minutes)
    python -m tools.acoustics.run_meter_checks --no-leak  # noise test and EDC check only
"""

import argparse
import json
import pathlib

from . import meter_checks as m

OUT = pathlib.Path(__file__).resolve().parent / "data" / "phase05_meter_checks.json"


def main(argv=None):
    ap = argparse.ArgumentParser()
    ap.add_argument("--no-leak", action="store_true")
    ap.add_argument("--out", default=str(OUT))
    a = ap.parse_args(argv)
    res = {"simulated_edc": m.simulated_edc_check(),
           "paired_noise_case_A": m.paired_noise_test(m.CASE_A, log=print),
           "paired_noise_case_B": m.paired_noise_test(m.CASE_B, seed=8080, log=print, r_max=200)}
    if not a.no_leak:
        res["leak_calibration"] = m.leak_calibration(log=print)
    pathlib.Path(a.out).write_text(json.dumps(res, indent=1) + "\n")
    print("wrote", a.out)


if __name__ == "__main__":
    main()
