# As-run scripts for `phase05b2_dt1.json` sections without a step in `phase05b2_dt1.py`

During phase 05b session 2, seven sections of `tools/validation/data/phase05b2_dt1.json` were written by ad-hoc session
commands, not by a step of `tools/validation/phase05b2_dt1.py`. This was flagged by the branch review (major 3). The
commands are committed here verbatim, extracted from the session transcript, so every recorded number has its
producing code.

| file | JSON section(s) | used by |
|---|---|---|
| `open_boxes.sh` | `open_boxes` | AX37 (5.4) (open-field / open boxes) |
| `c8_c10.sh` | `c8`, `c10` | D-T5 / D-T4 evidence (files 9, 10) |
| `band_correlation.sh` | `band_correlation` | 19 §3 (cross-band correlation) |
| `c6b.sh` | `c6b` | 19 §4, AX44 |
| `seat9_checks.sh` | `seat9_checks` | 19 §2, §6 (small-room ladder; absorbing-face NW-3 shift) |
| `c18.sh` | `c18` | file 46 (C18), J1 / phase-12 Trigger 2 |

They are records, not CI steps:
- Some import helpers from `/tmp` scratch files that no longer exist (`c6b.sh` ran `/tmp/claude-0/c6b.py`; its body is
  included).
- They need numba (`tools/validation/requirements-offline.txt`).
- To re-run one, port it into a `phase05b2_dt1.py` step. The C++ phase (05h) re-measures everything it relies on.
`tools/validation/tests/test_phase05b2_data.py` checks the numbers the AX rows quote against the committed JSON.
