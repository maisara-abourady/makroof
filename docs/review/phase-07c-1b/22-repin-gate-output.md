# 22 — repin_gate output: phase-07c-1b condition 7 S2 re-pin

- Date: 2026-11-13
- Runs (green S2 CI runs, all on code 9717a58; run heads 9717a58, ccd6f2d, 3dd196b differ from it only in prose
  that no build or test reads): 43389296112, 43402114873, 43412038058
- Inputs: the job logs of "build (linux)", "build (macos)" and "build (windows)" of each run (nine logs,
  downloaded through the GitHub job-logs URL), saved as `<run>-<os>.log`
- Command:

```
python tools/ci/repin_gate.py \
  green=43389296112-linux.log green=43389296112-macos.log green=43389296112-windows.log \
  green=43402114873-linux.log green=43402114873-macos.log green=43402114873-windows.log \
  green=43412038058-linux.log green=43412038058-macos.log green=43412038058-windows.log
```

## Output (verbatim but for the log directory `/tmp/claude-0/s/repin/` removed from the run labels; exit code 0)

```
# AX38 4c restore gate: proposed S2 pin (tools/ci/repin_gate.py)

## Linux: 3 green run(s)
  runs: 43389296112-linux.log [Linux]; 43402114873-linux.log [Linux]; 43412038058-linux.log [Linux]
  r-bar 2.3963; ratios 2.691, 2.531, 1.967; max/min 1.3681; r/r-bar 1.1230, 1.0562, 0.8208
  ratio check: PRINT-ONLY (max/min > 1.10)
  F-bar (flutter reference) 552.3 ms; k 1.2225
  cube100_flutter_fallback: baseline median 552.3 ms; solveRefMs 130.8; 14 x worst per run [5.95, 7.33, 10.31] s; <= 30 s on every run: yes
  cube100_lowalpha0.05_s0.3: baseline median 1282.7 ms; solveRefMs 80.7; 14 x worst per run [16.27, 18.72, 20.24] s; <= 30 s on every run: yes
  ns-per-eval ratio (low-alpha / flutter) per run [0.5773, 0.5814, 0.5849]; G9 exit (>= 3 runs within 1.05 of the mean): met
  stage split (3 run(s)): s_L 0.8688, s_F 0.3507; s_L > 1.10 s_F: yes; max/min <= 1.10: NO; f = x1.207

## macOS: 3 green run(s)
  runs: 43389296112-macos.log [macOS]; 43402114873-macos.log [macOS]; 43412038058-macos.log [macOS]
  r-bar 3.1203; ratios 2.880, 3.135, 3.346; max/min 1.1618; r/r-bar 0.9230, 1.0047, 1.0723
  ratio check: PRINT-ONLY (macOS, until Phase 13)
  F-bar (flutter reference) 475.3 ms; k 1.1127
  cube100_flutter_fallback: baseline median 475.3 ms; solveRefMs 110.6; 14 x worst per run [9.96, 6.48, 7.89] s; <= 30 s on every run: yes
  cube100_lowalpha0.05_s0.3: baseline median 1481.0 ms; solveRefMs 78.1; 14 x worst per run [23.46, 22.44, 24.08] s; <= 30 s on every run: yes
  E1 (cube100_lowalpha0.05_s0.3 macOS register entry): closes under 4c (c) (14 x worst <= 30 s on every S2 run)
  ns-per-eval ratio (low-alpha / flutter) per run [0.5038, 0.7250, 0.7892]; G9 exit (>= 3 runs within 1.05 of the mean): not met
  stage split (3 run(s)): s_L 0.8984, s_F 0.4179; s_L > 1.10 s_F: yes; max/min <= 1.10: NO; f = x1.228
  macOS trigger detects x1.167 (1 + 0.15 / s_L)

## Windows: 3 green run(s)
  runs: 43389296112-windows.log [Windows]; 43402114873-windows.log [Windows]; 43412038058-windows.log [Windows]
  r-bar 2.5297; ratios 2.585, 2.455, 2.549; max/min 1.0530; r/r-bar 1.0219, 0.9705, 1.0076
  ratio check: ASSERTED (r <= 1.10 x r-bar)
  F-bar (flutter reference) 496.3 ms; k 1.0846
  cube100_flutter_fallback: baseline median 496.3 ms; solveRefMs 106.0; 14 x worst per run [8.34, 6.42, 7.62] s; <= 30 s on every run: yes
  cube100_lowalpha0.05_s0.3: baseline median 1258.3 ms; solveRefMs 66.2; 14 x worst per run [20.24, 15.96, 19.59] s; <= 30 s on every run: yes
  E1 (cube100_lowalpha0.05_s0.3 Windows register entry): closes under 4c (c) (14 x worst <= 30 s on every S2 run)
  ns-per-eval ratio (low-alpha / flutter) per run [0.5879, 0.5866, 0.5916]; G9 exit (>= 3 runs within 1.05 of the mean): met
  stage split (3 run(s)): s_L 0.8755, s_F 0.3866; s_L > 1.10 s_F: yes; max/min <= 1.10: yes; f = x1.222

## macOS trigger: kMacGrowthTriggerMs = floor(1.15 x mean of 3 macOS low-alpha medians) = 1703 ms
  no S2 run exceeds the computed trigger
  runs above the trigger in force (2172 ms): none

## Constants for tests/unit/test_diffuse_records.cpp (the S2Pin of each kGateRegister entry)
  // {ratioRef, ratioMaxOverMin, flutterRefMs, baselineMedianMs, solveRefMs, solveK, runs}
  cube100_flutter_fallback   Linux    {0.0000, 0.0000, 552.3, 552.3, 130.8, 1.2225, 3}
  cube100_lowalpha0.05_s0.3  Linux    {2.3963, 1.3681, 552.3, 1282.7, 80.7, 1.2225, 3}
  cube100_flutter_fallback   macOS    {0.0000, 0.0000, 475.3, 475.3, 110.6, 1.1127, 3}
  cube100_lowalpha0.05_s0.3  macOS    {3.1203, 1.1618, 475.3, 1481.0, 78.1, 1.1127, 3}
  cube100_flutter_fallback   Windows  {0.0000, 0.0000, 496.3, 496.3, 106.0, 1.0846, 3}
  cube100_lowalpha0.05_s0.3  Windows  {2.5297, 1.0530, 496.3, 1258.3, 66.2, 1.0846, 3}
  constexpr double kMacGrowthTriggerMs = 1703.0;
  constexpr int kMacGrowthTriggerS2Runs = 3;
```

## Addendum (2026-11-13): re-run after the G9 flag (`solveExitMet`, commit 5753896)

Same command and the same nine logs (run 43389296112 logs re-downloaded through the job-logs URL: build (linux) 131765177649,
build (macos) 131765177268, build (windows) 131765177289). Exit code 0. The six printed initializers equal the six `S2Pin{…}` in
`tests/unit/test_diffuse_records.cpp` character for character (sorted `diff`: identical); trigger unchanged.

```
## macOS trigger: kMacGrowthTriggerMs = floor(1.15 x mean of 3 macOS low-alpha medians) = 1703 ms
  no S2 run exceeds the computed trigger
  runs above the trigger in force (2172 ms): none

## Constants for tests/unit/test_diffuse_records.cpp (the S2Pin of each kGateRegister entry)
  // {ratioRef, ratioMaxOverMin, flutterRefMs, baselineMedianMs, solveRefMs, solveK, runs, solveExitMet}
  // solveExitMet: the OS's G9 exit (true: solve basis S2-PINNED; false: S2-PROVISIONAL)
  cube100_flutter_fallback   Linux    {0.0000, 0.0000, 552.3, 552.3, 130.8, 1.2225, 3, true}
  cube100_lowalpha0.05_s0.3  Linux    {2.3963, 1.3681, 552.3, 1282.7, 80.7, 1.2225, 3, true}
  cube100_flutter_fallback   macOS    {0.0000, 0.0000, 475.3, 475.3, 110.6, 1.1127, 3, false}
  cube100_lowalpha0.05_s0.3  macOS    {3.1203, 1.1618, 475.3, 1481.0, 78.1, 1.1127, 3, false}
  cube100_flutter_fallback   Windows  {0.0000, 0.0000, 496.3, 496.3, 106.0, 1.0846, 3, true}
  cube100_lowalpha0.05_s0.3  Windows  {2.5297, 1.0530, 496.3, 1258.3, 66.2, 1.0846, 3, true}
  constexpr double kMacGrowthTriggerMs = 1703.0;
  constexpr int kMacGrowthTriggerS2Runs = 3;
```
