# 47 — Orchestrator: the AX37 (5.4) validation-N check's cost on the python CI job (the QA board-return trigger fired)

Decision P05H-QA (decider files 42/44, interrogator files 43/45; applied in b8b3c6d / e71bb88) ends: "If the two
2^23 renders add more than 10 min to the python job on any OS, the clause returns to the board (Seat 5 convened;
the nightly is Linux-only and does not run `test_tail.py`), never a loosened τ." CI run 42935789745 (b8b3c6d,
green on three OSes) is the first run with the form. Measured from the job logs' timestamps (the time between
the last smoke case's PASSED line and the two 2^23 cases' PASSED lines):

| OS | 2^23, s 0.4 | 2^23, s 0.5 | both | python job, run 7 → run 8 |
|---|---|---|---|---|
| Linux (ubuntu-24.04) | 386 s | 386 s | **12.9 min** | 10.5 → 22.1 min |
| macOS (macos-15) | 227 s | 246 s | 7.9 min | 10.7 → 16.6 min |
| Windows (windows-2022) | 265 s | 265 s | 8.8 min | 10.1 → 16.6 min |

Linux exceeds the 10 min trigger (the Linux runner's render_cli is the slowest of the three here; the local dev
box took 213 s per s value). The check itself is green on three OSes with identical numbers (bit-identical
estimator, AX5): 4–8 kHz deviation −0.020 / +0.005 dB, SE 0.073 / 0.076 dB, z −0.27 / +0.06; bands 0–5 |dev| ≤
0.002 dB; s 0.4 and s 0.5 identical to the printed precision on every OS (the single-scatter ratio cancels s:
Lambert re-radiation into the half-space above the floor, every other face absorbing, so no second bounce;
Kuttruff Eq. 4.24; file 43).

## Question (to the decider; Seat 5 convened per the clause)

What form keeps AX37 (5.4)'s check operative at τ on three OSes within the CI budget Seat 5 holds? Options the
orchestrator sees (Seat 5 ranks and may add):

- (a) keep both s values at 2^23 in PR CI as they are (python job 16.6–22.1 min; the job's own timeout and the
  `ci ok` wall clock are the costs; nothing else changes);
- (b) one s value (0.4) at 2^23 in PR CI, the other (0.5) in the labelled smoke form only, on the measured and
  derived s-independence of the ratio (the check loses no statistical power: the two cases are the same test of
  the same ratio; 6.4 min on Linux);
- (c) (b) plus s 0.5 at 2^23 as a nightly case: needs a `nightly.yml` edit (the nightly is Linux-only and runs
  `tools/validation` and `test_radiosity.py -m slow`; the `nightly` marker is registered in
  `tools/validation/tests/conftest.py`) and a `tools/acoustics` marker registration; a change to the CI shape
  Seat 5 owns;
- (d) run the two 2^23 renders concurrently inside the test (two `render_cli` processes; the runners have 4 vCPU
  on Linux/Windows, 3 on macOS; the solve is itself multi-threaded through the pool, so the gain is uncertain
  and would need measuring);
- (e) one emitter instead of two per render? Not available: `render_cli` renders the scene's two emitters in one
  solve (one solve per scene, D4), and the per-emitter cost is the solve's, not the render's.

Not options: τ + SE (struck), a smaller N (3·SE ≤ τ fails at 4–8 kHz below 2^23: SE ∝ 1/√N, 0.073 dB × √2 = 0.10 dB
→ 3·SE 0.31 dB > τ), dropping the check (NFR-1), a Linux-only exemption (AX37 (5.4): "PR CI on three OSes").

Constraints: AX37 (5.4) as amended (file 44 QA, file 45); AX42; NFR-1; NFR-6 / AX5 (the three-OS identity of the
numbers is itself evidence for (b)); Seat 5's CI-gate mandate (`docs/board/README.md`); D-H1 (v)(d) (no cut, no
seam); the one-phase rule (a `nightly.yml` redesign is not 05h's). The decider decides at minimum tension; the
answer is for Maisara (a reading of her AX37 (5.4) at the budget), with the AMENDS line if the clause text changes,
and the exact plan text and test form.
