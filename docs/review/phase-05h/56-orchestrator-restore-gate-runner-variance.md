# 56 — Orchestrator: the restore-gate register form against shared-runner variance (CI runs 9 and 10; D-H1 (v) returned to the board)

## What happened

- CI run 42942694523 (run 9, cb7effb): `build (windows)` failed the **strict** Windows entry (14 × worst 36.73 s;
  median 2 589 ms). Applied under D-H1 (v)(d): no re-run; the entry listed with that run's median as its baseline
  (file 53, interrogator file 54; plan cad4506; tests 314f7b0).
- CI run 42949252041 (run 10, 314f7b0, the register in that form): `build (linux)` failed the **listed** Linux
  entry's growth bound: median 2 716 ms > 1.10 × 2 043 = 2 247 ms (14 × worst 41.67 s). On the same run the macOS
  entry read 27.33 s and the Windows entry 25.57 s, both printing the §5 (c) "passes 30 s" warning. Nightly green;
  every other job green (the `open-field-validation` job included).
- CI run 42954077281 (run 11, b83c49d: a comment fix) is in flight; its lines are appended below when it lands.

D-H1 (v)(d) says of this case: "a listed entry breaking its growth bound, is a defect: no re-run, no W_max cut
after pinning, no room-range narrowing, no formulation seam; it enters the register with its remedy". The Linux
entry is already in the register with its remedy (phase-07c conditions 9–10). The rule has no further step for an
entry that is in the register and breaks its bound again: the gate stays red until the remedy lands in 07c, which
blocks `ci ok` on every PR of 05i, 07b, 07c (and this one) whenever the shared runner is slow. That contradicts
the register's stated purpose (D-H1 (v), decider file 19: the gate "never red by runner speed, the defect never
hidden") and CLAUDE.md's verification culture (a red-by-design gate is a defect of the gate). So the form goes back
to the board; nothing is widened or re-run meanwhile.

## The data (every CI run of the records test at the pinned W_max; the flutter scene's restore on the same run is a
runner-speed reference: its solve is the pilot only, no cap, the same W_max rule)

| run | OS | low-α restore min / median / worst ms | 14 × worst s | flutter restore median ms | low-α full rebuild median ms | low-α / flutter median ratio |
|---|---|---|---|---|---|---|
| 42909003931 (records) | Linux | 2008 / 2043 / 2116 | 29.62 | 716 | 2152 | 2.85 |
| 42909003931 | macOS | 1840 / 2106 / 2669 | 37.37 | (file 31: 7.52 s / 14 = 537) | 1928 | 3.92 |
| 42909003931 | Windows | 1981 / 2000 / 2075 | 29.04 | 757 | 1948 | 2.64 |
| 42924781618 | Linux | 1961 / 2092 / 2155 | 30.18 | 693 | 2130 | 3.02 |
| 42924781618 | macOS | 1665 / 1849 / 2231 | 31.23 | 474 | 1898 | 3.90 |
| 42924781618 | Windows | 2011 / 2056 / 2107 | 29.50 | 752 | 2001 | 2.73 |
| 42935789745 | Linux | 1586 / 1666 / 1736 | 24.31 | 514 | 1640 | 3.24 |
| 42935789745 | macOS | 1768 / 1887 / 2265 | 31.71 | 494 | 1841 | 3.82 |
| 42935789745 | Windows | 1898 / 1926 / 2041 | 28.57 | 626 | 1934 | 3.08 |
| 42942694523 | Windows | 2476 / 2589 / 2624 | **36.73 (strict, failed)** | 927 | 2555 | 2.79 |
| 42949252041 | Linux | 2546 / 2716 / 2977 | **41.67 (listed; median 2 716 > 2 247, failed)** | 880 | 2690 | 3.09 |
| 42949252041 | macOS | 1503 / 1715 / 1952 | 27.33 | 484 | 1523 | 3.54 |
| 42949252041 | Windows | 1764 / 1811 / 1827 | 25.57 | 622 | 1753 | 2.91 |
| 42954077281 (b83c49d, green) | Linux | 1755 / 1879 / 1986 | 27.81 | 583 | — | 3.22 |
| 42954077281 | macOS | 1715 / 1967 / 2122 | 29.70 | 501 | — | 3.93 |
| 42954077281 | Windows | 1317 / 1341 / 1428 | 19.99 | 488 | — | 2.75 |
| 42964823518 (67f13f3, RG-1 form, green) | Linux | 1698 / 1759 / 1806 | 25.29 (not evaluated: flutter −16.8 %) | 583 | 1707 | 3.02 |
| 42964823518 | macOS | 1926 / 2069 / 2273 | 31.82 (reported only; GROWTH, OVER30S; < 2 172) | 533 | 1878 | 3.88 |
| 42964823518 | Windows | 1989 / 2005 / 2108 | 29.51 (asserted in-window: 2 005 ≤ 2 231) | 744 | 2020 | 2.70 |

(The macOS flutter median of the records run is read from file 31's 14 × worst line, 7.52 s, as a worst, not a
median: the ratio for that row is approximate.) Within one OS the low-α restore median moves by a factor 1.63 on
Linux (1 666 → 2 716 ms), 1.93 on Windows (1 341 → 2 589 ms, with run 42954077281 added on 2026-11-11), 1.23 on
macOS (1 715 → 2 106 ms) between runs on identical code: shared-runner speed. The ratio low-α / flutter on the same run moves far less: Linux 2.85–3.24
(±6 %), Windows 2.64–3.08 (±8 %), macOS 3.54–3.92 (±5 %). The 1.10 × growth bound on an absolute median is inside
the runner's own spread; the strict 30 s line (≈ 2 143 ms worst) sits in the middle of the observed Windows and
Linux ranges.

## Question (to the decider; Seat 5 is the CI-gate seat, Seat 3 owns the restore cost reading of D-H1 (v))

How is D-H1 (v)'s blocking restore gate to be asserted so that it is never red by runner speed and never hides the
defect (its own purpose), at the pinned W_max, inside D-H1 (v)(d) (no W_max cut, no range change, no seam)? Options
the orchestrator sees (the seats rank, add, or strike):

- (a) keep the form as it is: the gate is red whenever a shared runner is ≥ 10 % slower than the baseline run; a
  red run is a defect "no re-run" → every PR until phase-07c lands waits on runner luck (the data: 2 of the last
  5 runs red);
- (b) a runner-normalised growth bound: assert median(low-α restore) / median(flutter restore on the same run)
  ≤ 1.10 × the recorded ratio (baselines Linux 2.85–3.24, macOS 3.5–3.9, Windows 2.6–3.1 from the five runs; the
  pinned baseline = the records run's ratio or the mean of the runs on file), alongside the absolute figures
  printed as records and the 30 s line reported, never asserted, on shared runners; the strict form kept for
  Phase 13's release machines;
- (c) the absolute bound with a baseline pinned per OS from the slowest green run on file (Linux 2 716 would then
  be the baseline, bound 2 988 ms), which makes the gate a one-sided detector of a further 10 % growth above the
  slowest runner seen: weak;
- (d) the growth bound measured on a dedicated or self-hosted runner (none exists; Seat 7's cost; not 05h's);
- (e) the bound kept absolute but asserted only when the run's flutter median is within ±10 % of its recorded
  value (a runner-speed guard: the gate is "not evaluated (runner slow)" otherwise and the run prints it), with
  the §0 note recording how often it was not evaluated.

Facts for the seats: the restore time's cause is known and remedied in phase-07c conditions 9–10 (the unit-decay
synthesis 95.5 % of the non-diffuse restore; the solve ≈ 0.1 s); the gate's job until then is to catch a
regression of the solve or the build, not the runner; the per-run ratio (b) is blind to a regression that scales
the flutter scene's restore equally (a global slowdown of the synthesis), which the full-rebuild records and the
AQ4 intervals still show as records; Phase 13 re-measures on release machines (AX38 4c macOS entry; phase-13
Raise items). AX38 4c's register text, phase-05h §5 (a)–(d) and `kGateRegister` carry the current form.

## Constraints

PRD NFR-1, NFR-2 (L101: the previous IR keeps playing; heavy latency acceptable where it buys accuracy), NFR-6;
D-H1 (v) as decided for Maisara (decider file 19, interrogator file 21; her acceptance 2026-11-10); D-H1 (v)(d);
AX38 4c; CLAUDE.md's verification culture and the one-phase rule (a form change is a test and plan edit of 05h's
own gate; a new runner is not 05h's). The decider decides at minimum tension; the answer is for Maisara (a reading
or an amendment of D-H1 (v)) unless it is one of the three NEEDS MAISARA cases; the interrogator checks; the
plan-editor and the orchestrator apply; CI run 12 verifies on the head. Until then the branch's last green run on
the head's code is run 42935789745 (b8b3c6d, before the CI-job commit); runs 9 and 10 each failed one build job on
the restore gate only.

## Measured: the split timer of the flutter scene (Seat 3's hand-off; probe `[probe-restore-split]` extended to both scenes, Release, this 4-core Linux box, median of 5; 2026-11-11)

```
probe-split lowalpha0.05_s0.3 fs 96000: T60max 50.5 s, unit decay 1152000 samples; full build (no diffuse) median 3339 ms; generator ctor 942 ms; make x2 2425 ms; position-only build (cached decays) 136 ms
probe-split lowalpha0.05_s0.3 fs 48000: T60max 50.5 s, unit decay 576000 samples; full build (no diffuse) median 1224 ms; generator ctor 313 ms; make x2 801 ms; position-only build (cached decays) 57 ms
probe-split flutter_fallback fs 96000: T60max 2.6 s, unit decay 377517 samples; full build (no diffuse) median 889 ms; generator ctor 148 ms; make x2 388 ms; position-only build (cached decays) 332 ms
probe-split flutter_fallback fs 48000: T60max 2.6 s, unit decay 188759 samples; full build (no diffuse) median 328 ms; generator ctor 55 ms; make x2 145 ms; position-only build (cached decays) 122 ms
```

At 96 kHz the flutter scene's non-diffuse build is 889 ms: the unit-decay synthesis (ctor 148 + make 388 = 536 ms) is
≈ 60 % of it, the position-only part (the AX22-fallback ISM list, the matching and the mix) ≈ 37 % (332 ms, against
136 ms at the low-α cube: the fallback's image list is the difference); the low-α cube's synthesis is ≈ 95 % of its
3 339 ms. Seat 3's inference (file 58: flutter ≈ 60 % synthesis) is confirmed by measurement; the flutter restore
with the solve on CI (≈ 0.5–0.9 s) adds its pilot-only solve (≈ 0.16 s) to this.


## Added 2026-11-11: CI run 42954077281 (b83c49d, the pre-RG-1 form) green on three OSes

Appended to the table above (the rows marked 42954077281; full-rebuild medians not extracted). Every listed entry
sat inside its bound on normal runners (Linux 27.81 s, macOS 29.70 s, Windows 19.99 s, all three printing the
§5 (c) 'passes 30 s' warning). Windows' low-α median 1 341 ms against 2 589 ms two runs earlier (×1.93) widens
the observed spread; the ratios stay in their bands (Linux 3.22, macOS 3.93, Windows 2.75).
