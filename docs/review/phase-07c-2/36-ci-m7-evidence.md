# 36 — M7 / M7b / B1-b under H-2c: CI evidence

## Run 45023654411 (87a62d5), Windows only
Linux and macOS failed to build in this run because of `-Wfloat-equal` in `test_m7_hold.cpp`, which was fixed in
582e485. The contract-tools jobs failed because the abx kit test imported numpy, also fixed in 582e485. The
`build (windows)` job (137211972832) passed in full: debug tests, release build, benchmarks, pluginval.

**M7, mid-solve hold** (ms, n = 10 edits per point, pool 4 with builder-class share 3, 48 kHz; bound ≤ 700 on the
worst OS and flat in m):

| scene | m=1 | m=4 | m=5 | m=6 | m=8 |
|---|---|---|---|---|---|
| layout4_s1/listener_corner, median / worst | 36.8 / 45.0 | 39.0 / 43.0 | 42.0 / 48.0 | 37.5 / 43.0 | 33.4 / 42.0 |
| cube100_lowalpha0.05_s1, median / worst | 70.2 / 77.1 | 73.6 / 81.1 | 72.1 / 76.0 | 72.0 / 76.2 | 71.5 / 79.1 |
| solve median (layout / cube) | 142 / 85 | 389 / 320 | 485 / 396 | 572 / 472 | 732 / 631 |

The hold is flat in m, while the solve grows by 5–7× over the same range. The worst value is 81.1 ms against 700.

**M7b, continuous automation:**
- With an edit every 100 ms, 0 % of solves complete before the next edit at every m; with an edit every 5 s,
  100 % complete.
- Edit → solve end: worst 213 / 453 / 540 / 641 / 793 ms (layout) and 179 / 448 / 505 / 568 / 747 ms (cube) at
  m = 1 / 4 / 5 / 6 / 8.

**M7b, AX38 (iv) patterns** (L = load, J = joint step; N = 1, 4, 8; m = 1, 6):
- discardedMidDrag is 0 in every row, and the completed fraction is 100 % in every row. This matches H-0 by
  construction.
- Load pattern lengths at m = 6, N = 8: 8.39 s (layout) and 13.33 s (cube).

**B1-b solve duration** (0 / 1 / 2 / 4 / 8 churned builders at 100 m):
- solves completed: 0 / 1 / 1 / 2 / 22;
- mean solve: — / 75 / 84 / 88 / 96 ms;
- mean gate wait: 0 / 0 / 0 / 16 / 10 ms.

Linux, macOS and TSan come from the next manual three-OS run on the final tree; that run is cited below when green.
