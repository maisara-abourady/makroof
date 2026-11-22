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

## Run 45045891476 (1b2f700, the final code tree): the run of record
Every job green on Linux, macOS and Windows; TSan (linux, 137280981452) runs `[conv],[pipeline],[diffuse]`, which
includes the H-2c stress and the new deterministic "running inside the solve" teardown section (review M2). The M7
test code is unchanged since 79564bb (`git diff 79564bb 1b2f700 -- tests/unit/test_m7_hold.cpp` is empty).

**M7, mid-solve hold** (ms, median / worst, n = 10 edits per point, 48 kHz; bound ≤ 700 on the worst OS, flat in m):

| OS (job) | scene | m=1 | m=4 | m=5 | m=6 | m=8 |
|---|---|---|---|---|---|---|
| Linux (137280981529), pool 4, share 3 | layout4_s1/listener_corner | 31.2 / 47.2 | 44.7 / 61.1 | 43.7 / 47.2 | 46.3 / 48.3 | 45.8 / 55.9 |
| | cube100_lowalpha0.05_s1 | 71.7 / 78.2 | 71.7 / 88.0 | 69.2 / 80.3 | 73.8 / 81.0 | 70.8 / 79.6 |
| | solve median (layout / cube) | 188 / 126 | 587 / 486 | 732 / 602 | 855 / 726 | 1125 / 964 |
| macOS (137280981562), pool 3, share 2 | layout4_s1/listener_corner | 34.9 / 111.6 | 36.9 / 46.9 | 39.5 / 50.0 | 41.0 / 45.5 | 37.5 / 49.8 |
| | cube100_lowalpha0.05_s1 | 69.8 / 86.4 | 86.8 / 198.9 | 67.3 / 73.5 | 64.7 / 81.1 | 61.5 / 68.1 |
| | solve median (layout / cube) | 125 / 104 | 455 / 388 | 574 / 491 | 634 / 584 | 874 / 800 |
| Windows (137280981614) | | WINDOWS_ROWS | | | | |

Reading: the worst over both OSes is 198.9 ms (macOS, cube, m = 4), against 700. The medians are flat in m (Linux
31–46 ms layout, 69–74 ms cube; macOS 35–41 ms layout, 62–87 ms cube) while the solve grows 6–8× over the same
range; the macOS worst-case outliers (111.6 at m = 1, 198.9 at m = 4) are single-edit p95 = worst points on a shared
runner at n = 10, not a trend in m. No numeric flatness rule is pinned (review Q1): "flat" is read as the medians
staying within the same band while the solve scales with m.

**M7b, continuous automation** (edit → solve end, worst, ms, m = 1 / 4 / 5 / 6 / 8):
- Linux: layout 243 / 644 / 795 / 941 / 1181; cube 225 / 585 / 704 / 826 / 1061.
- macOS: layout 263 / 663 / 828 / 788 / 1080; cube 225 / 532 / 719 / 900 / 959.
- Both: with an edit every 100 ms, 0 % of solves complete before the next edit at every m (each is cancelled and
  the latest edit's solve is the one adopted); with an edit every 5 s, 100 % complete.

**M7b, AX38 (iv) patterns** (L = load, J = joint step; N = 1, 4, 8; m = 1, 6), Linux and macOS: discardedMidDrag 0
and completed fraction 100 % in every row. Load pattern length at m = 6, N = 8: Linux 11.99 s (layout) / 15.27 s
(cube); macOS 7.71 s / 11.37 s.

**B1-b solve duration** (0 / 1 / 2 / 4 / 8 churned builders at 100 m; recorded only):
- Linux: solves 0 / 1 / 1 / 2 / 4; mean solve — / 121 / 122 / 120 / 127 ms; mean gate wait 0 / 0 / 0 / 37 / 71 ms.
- macOS: solves 0 / 2 / 1 / 4 / 7; mean solve — / 108 / 109 / 79 / 72 ms; mean gate wait 0 / 0 / 0 / 0 / 20 ms.

