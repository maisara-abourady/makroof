# Phase 05i: CI records (orchestrator, 2026-11-11)

CI run [43007183782](https://github.com/maisara-abourady/makroof/actions/runs/43007183782) (manual dispatch on b94e14f; every job green on Linux, macOS, Windows, ASan + UBSan, TSan, python, tail gates, open-field) and nightly BRAS validation [43007188366](https://github.com/maisara-abourady/makroof/actions/runs/43007188366) (green). Lines copied verbatim from the build jobs' Benchmark step (job ids: Linux 130477545194, macOS 130477545158, Windows 130477545065; the same lines are in each job's summary by the new 'Records to the job summary' step). The later commits on the branch change no record code except the K-e12 per-run in-flight print and the (iv) wording (b83345c); the PR's CI run is the run of record and is appended below when it lands.

## linux

```
05h-records GATE os=Linux scene=cube100_flutter_fallback x14worst=9.59 median=675 fullRebuildMedian=664 solveMedianMs=131.2 nsPerEval=11.51 status=asserted(30s) flutterRef=701 flutterDev=-3.7%
05h-records GATE os=Linux scene=cube100_lowalpha0.05_s0.3 ratio=2.803 ratioWarnAt=3.660 solveMedianMs=80.9 nsPerEval=6.69 x14worst=27.61 median=1892 growthBound=2275 fullRebuildMedian=1870 status=asserted trigger=0 warnings=PASSES30S 
05i-records (iv) AQ10 room                   48000 Hz, 1 inst: load until the last is audible 451 ms; per instance (load order) prepare [296] ms, restore [155] ms
05i-records (iv) AQ10 room                   48000 Hz, 1 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 166 median 166 max 166 ms
05i-records (iv) AQ10 room                   48000 Hz, 1 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 156 median 156 max 156 ms
05i-records (iv) AQ10 room                   48000 Hz, 1 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 290 median 290 max 290 ms
05i-records (iv) AQ10 room                   48000 Hz, 1 inst: worst host-thread wait of one instance while the other 0 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 159 ms, restore 156 ms, offline switch + first block after a room-size edit 141 ms
05i-records (iv) AQ10 room                   48000 Hz, 4 inst: load until the last is audible 1720 ms; per instance (load order) prepare [284 274 278 276] ms, restore [152 151 150 154] ms
05i-records (iv) AQ10 room                   48000 Hz, 4 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 167 median 415 max 656 ms
05i-records (iv) AQ10 room                   48000 Hz, 4 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 155 median 383 max 612 ms
05i-records (iv) AQ10 room                   48000 Hz, 4 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 6 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 288 median 719 max 1161 ms
05i-records (iv) AQ10 room                   48000 Hz, 4 inst: worst host-thread wait of one instance while the other 3 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 287 ms, restore 299 ms, offline switch + first block after a room-size edit 285 ms
05i-records (iv) AQ10 room                   48000 Hz, 8 inst: load until the last is audible 3485 ms; per instance (load order) prepare [291 275 274 279 300 278 281 278] ms, restore [153 152 152 153 154 150 156 158] ms
05i-records (iv) AQ10 room                   48000 Hz, 8 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 163 median 711 max 1280 ms
05i-records (iv) AQ10 room                   48000 Hz, 8 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 155 median 687 max 1221 ms
05i-records (iv) AQ10 room                   48000 Hz, 8 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 10 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 282 median 1290 max 2302 ms
05i-records (iv) AQ10 room                   48000 Hz, 8 inst: worst host-thread wait of one instance while the other 7 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 301 ms, restore 298 ms, offline switch + first block after a room-size edit 291 ms
05i-records (iv) AQ10 room                   96000 Hz, 1 inst: load until the last is audible 769 ms; per instance (load order) prepare [444] ms, restore [325] ms
05i-records (iv) AQ10 room                   96000 Hz, 1 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 356 median 356 max 356 ms
05i-records (iv) AQ10 room                   96000 Hz, 1 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 340 median 340 max 340 ms
05i-records (iv) AQ10 room                   96000 Hz, 1 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 633 median 633 max 633 ms
05i-records (iv) AQ10 room                   96000 Hz, 1 inst: worst host-thread wait of one instance while the other 0 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 320 ms, restore 330 ms, offline switch + first block after a room-size edit 312 ms
05i-records (iv) AQ10 room                   96000 Hz, 4 inst: load until the last is audible 3334 ms; per instance (load order) prepare [505 468 465 469] ms, restore [357 343 385 342] ms
05i-records (iv) AQ10 room                   96000 Hz, 4 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 363 median 896 max 1443 ms
05i-records (iv) AQ10 room                   96000 Hz, 4 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 323 median 808 max 1319 ms
05i-records (iv) AQ10 room                   96000 Hz, 4 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 6 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 622 median 1546 max 2493 ms
05i-records (iv) AQ10 room                   96000 Hz, 4 inst: worst host-thread wait of one instance while the other 3 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 636 ms, restore 652 ms, offline switch + first block after a room-size edit 615 ms
05i-records (iv) AQ10 room                   96000 Hz, 8 inst: load until the last is audible 6463 ms; per instance (load order) prepare [463 470 476 472 486 457 459 459] ms, restore [335 341 348 354 338 334 335 335] ms
05i-records (iv) AQ10 room                   96000 Hz, 8 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 361 median 1540 max 2776 ms
05i-records (iv) AQ10 room                   96000 Hz, 8 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 346 median 1498 max 2634 ms
05i-records (iv) AQ10 room                   96000 Hz, 8 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 10 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 656 median 2860 max 5130 ms
05i-records (iv) AQ10 room                   96000 Hz, 8 inst: worst host-thread wait of one instance while the other 7 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 641 ms, restore 650 ms, offline switch + first block after a room-size edit 618 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst: load until the last is audible 1083 ms; per instance (load order) prepare [278] ms, restore [805] ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 780 median 780 max 780 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 725 median 725 max 725 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 1422 median 1422 max 1422 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst: worst host-thread wait of one instance while the other 0 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 781 ms, restore 772 ms, offline switch + first block after a room-size edit 781 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst: load until the last is audible 4152 ms; per instance (load order) prepare [275 274 278 270] ms, restore [795 749 733 777] ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 812 median 1990 max 3240 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 805 median 1931 max 3072 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 6 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 1423 median 3541 max 5730 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst: worst host-thread wait of one instance while the other 3 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 1505 ms, restore 1508 ms, offline switch + first block after a room-size edit 1518 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst: load until the last is audible 8337 ms; per instance (load order) prepare [273 281 283 272 281 281 270 276] ms, restore [750 765 725 720 750 807 801 801] ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 793 median 3565 max 6340 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 773 median 3456 max 6126 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 10 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 1411 median 6365 max 11522 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst: worst host-thread wait of one instance while the other 7 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 1524 ms, restore 1499 ms, offline switch + first block after a room-size edit 1517 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst: load until the last is audible 2469 ms; per instance (load order) prepare [464] ms, restore [2005] ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 1894 median 1894 max 1894 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 1812 median 1812 max 1812 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 3572 median 3572 max 3572 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst: worst host-thread wait of one instance while the other 0 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 1986 ms, restore 1977 ms, offline switch + first block after a room-size edit 1913 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst: load until the last is audible 9406 ms; per instance (load order) prepare [450 447 447 448] ms, restore [1984 1811 1877 1941] ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 2042 median 4925 max 7775 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 1869 median 4816 max 7729 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 6 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 3638 median 9171 max 14656 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst: worst host-thread wait of one instance while the other 3 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 3778 ms, restore 3771 ms, offline switch + first block after a room-size edit 3714 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst: load until the last is audible 19523 ms; per instance (load order) prepare [456 450 449 441 474 456 437 439] ms, restore [1982 1864 2008 1957 1953 2071 2060 2028] ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 1963 median 9199 max 16304 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 2015 median 8986 max 15705 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 10 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 3512 median 16471 max 29412 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst: worst host-thread wait of one instance while the other 7 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 3803 ms, restore 3681 ms, offline switch + first block after a room-size edit 3607 ms
05i-records K-e12 os=Linux cube100_flutter_fallback   96 kHz: restore with a room edit in flight (room size -1/-2 m in w/d/h, restore of a new room size at a random point of the 658 ms rebuild), 10 runs: min 572 median 668 worst 793 ms (idle restore of a new state median 575 ms, 3 runs); per-restore budget 2143 ms: within
05i-records K-e12 os=Linux cube100_flutter_fallback   run  0: restore at 177 ms of 658 -> host thread 671 ms
05i-records K-e12 os=Linux cube100_flutter_fallback   run  1: restore at 650 ms of 658 -> host thread 572 ms
05i-records K-e12 os=Linux cube100_flutter_fallback   run  2: restore at 61 ms of 658 -> host thread 793 ms
05i-records K-e12 os=Linux cube100_flutter_fallback   run  3: restore at 516 ms of 658 -> host thread 666 ms
05i-records K-e12 os=Linux cube100_flutter_fallback   run  4: restore at 319 ms of 658 -> host thread 621 ms
05i-records K-e12 os=Linux cube100_flutter_fallback   run  5: restore at 349 ms of 658 -> host thread 598 ms
05i-records K-e12 os=Linux cube100_flutter_fallback   run  6: restore at 185 ms of 658 -> host thread 671 ms
05i-records K-e12 os=Linux cube100_flutter_fallback   run  7: restore at 149 ms of 658 -> host thread 694 ms
05i-records K-e12 os=Linux cube100_flutter_fallback   run  8: restore at 242 ms of 658 -> host thread 612 ms
05i-records K-e12 os=Linux cube100_flutter_fallback   run  9: restore at 53 ms of 658 -> host thread 788 ms
05i-records K-e12 os=Linux cube100_lowalpha0.05_s0.3  96 kHz: restore with a room edit in flight (room size -1/-2 m in w/d/h, restore of a new room size at a random point of the 1976 ms rebuild), 10 runs: min 1850 median 2370 worst 3276 ms (idle restore of a new state median 1799 ms, 3 runs); per-restore budget 2143 ms: FINDING (worst above the budget; register form, remedy phase-07c conditions 9-10)
05i-records K-e12 os=Linux cube100_lowalpha0.05_s0.3  run  0: restore at 1481 ms of 1976 -> host thread 2477 ms
05i-records K-e12 os=Linux cube100_lowalpha0.05_s0.3  run  1: restore at 162 ms of 1976 -> host thread 2346 ms
05i-records K-e12 os=Linux cube100_lowalpha0.05_s0.3  run  2: restore at 1867 ms of 1976 -> host thread 1850 ms
05i-records K-e12 os=Linux cube100_lowalpha0.05_s0.3  run  3: restore at 1915 ms of 1976 -> host thread 1960 ms
05i-records K-e12 os=Linux cube100_lowalpha0.05_s0.3  run  4: restore at 1379 ms of 1976 -> host thread 2581 ms
05i-records K-e12 os=Linux cube100_lowalpha0.05_s0.3  run  5: restore at 218 ms of 1976 -> host thread 2098 ms
05i-records K-e12 os=Linux cube100_lowalpha0.05_s0.3  run  6: restore at 785 ms of 1976 -> host thread 3276 ms
05i-records K-e12 os=Linux cube100_lowalpha0.05_s0.3  run  7: restore at 1430 ms of 1976 -> host thread 2394 ms
05i-records K-e12 os=Linux cube100_lowalpha0.05_s0.3  run  8: restore at 1027 ms of 1976 -> host thread 2778 ms
05i-records K-e12 os=Linux cube100_lowalpha0.05_s0.3  run  9: restore at 580 ms of 1976 -> host thread 1908 ms
05i-records (iv) offline AQ10 room                   48000 Hz, 1 offline instance in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 144 median 147 worst 151 ms; first build (after restore) worst 169 ms; wall 757 ms
05i-records (iv) offline AQ10 room                   48000 Hz, 4 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 549 median 579 worst 643 ms; first build (after restore) worst 662 ms; wall 2956 ms
05i-records (iv) offline AQ10 room                   48000 Hz, 8 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 1130 median 1172 worst 1263 ms; first build (after restore) worst 1272 ms; wall 5925 ms
05i-records (iv) offline AQ10 room                   96000 Hz, 1 offline instance in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 312 median 318 worst 349 ms; first build (after restore) worst 377 ms; wall 1674 ms
05i-records (iv) offline AQ10 room                   96000 Hz, 4 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 1245 median 1284 worst 1400 ms; first build (after restore) worst 1426 ms; wall 6565 ms
05i-records (iv) offline AQ10 room                   96000 Hz, 8 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 2442 median 2535 worst 2823 ms; first build (after restore) worst 2779 ms; wall 12905 ms
05i-records (iv) offline cube100_lowalpha0.05_s0.3   48000 Hz, 1 offline instance in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 767 median 781 worst 797 ms; first build (after restore) worst 797 ms; wall 3922 ms
05i-records (iv) offline cube100_lowalpha0.05_s0.3   48000 Hz, 4 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 3098 median 3172 worst 3278 ms; first build (after restore) worst 3359 ms; wall 16001 ms
05i-records (iv) offline cube100_lowalpha0.05_s0.3   48000 Hz, 8 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 6135 median 6505 worst 7089 ms; first build (after restore) worst 6587 ms; wall 32712 ms
05i-records (iv) offline cube100_lowalpha0.05_s0.3   96000 Hz, 1 offline instance in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 1913 median 1994 worst 2041 ms; first build (after restore) worst 2064 ms; wall 10005 ms
05i-records (iv) offline cube100_lowalpha0.05_s0.3   96000 Hz, 4 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 7829 median 7932 worst 8241 ms; first build (after restore) worst 8179 ms; wall 40003 ms
05i-records (iv) offline cube100_lowalpha0.05_s0.3   96000 Hz, 8 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 15288 median 15470 worst 16270 ms; first build (after restore) worst 16087 ms; wall 78287 ms
agree-full pooled bias band 0 [CHECK, additive]: mean (C++ - ref) -0.0008 dB over 70 case-bands; bound 3 SE_pool + mean l_ref = 0.0035 + 0.0044 = 0.0079 dB (within)
agree-full pooled bias band 0 [record, per reference room, z']: mean over 26 rooms -0.132 (3/sqrt(M_rooms) 0.588); rooms +/- 10 / 16
agree-full pooled bias band 1 [CHECK, additive]: mean (C++ - ref) -0.0009 dB over 70 case-bands; bound 3 SE_pool + mean l_ref = 0.0035 + 0.0045 = 0.0080 dB (within)
agree-full pooled bias band 1 [record, per reference room, z']: mean over 26 rooms -0.135 (3/sqrt(M_rooms) 0.588); rooms +/- 10 / 16
agree-full pooled bias band 2 [CHECK, additive]: mean (C++ - ref) -0.0009 dB over 70 case-bands; bound 3 SE_pool + mean l_ref = 0.0035 + 0.0045 = 0.0080 dB (within)
agree-full pooled bias band 2 [record, per reference room, z']: mean over 26 rooms -0.138 (3/sqrt(M_rooms) 0.588); rooms +/- 10 / 16
agree-full pooled bias band 3 [CHECK, additive]: mean (C++ - ref) -0.0009 dB over 70 case-bands; bound 3 SE_pool + mean l_ref = 0.0034 + 0.0046 = 0.0080 dB (within)
agree-full pooled bias band 3 [record, per reference room, z']: mean over 26 rooms -0.139 (3/sqrt(M_rooms) 0.588); rooms +/- 10 / 16
agree-full pooled bias band 4 [CHECK, additive]: mean (C++ - ref) -0.0011 dB over 70 case-bands; bound 3 SE_pool + mean l_ref = 0.0034 + 0.0046 = 0.0080 dB (within)
agree-full pooled bias band 4 [record, per reference room, z']: mean over 26 rooms -0.139 (3/sqrt(M_rooms) 0.588); rooms +/- 11 / 15
agree-full pooled bias band 5 [CHECK, additive]: mean (C++ - ref) -0.0012 dB over 70 case-bands; bound 3 SE_pool + mean l_ref = 0.0034 + 0.0046 = 0.0080 dB (within)
agree-full pooled bias band 5 [record, per reference room, z']: mean over 26 rooms -0.137 (3/sqrt(M_rooms) 0.588); rooms +/- 11 / 15
agree-full pooled bias band 6 [CHECK, additive]: mean (C++ - ref) -0.0012 dB over 70 case-bands; bound 3 SE_pool + mean l_ref = 0.0034 + 0.0046 = 0.0080 dB (within)
agree-full pooled bias band 6 [record, per reference room, z']: mean over 26 rooms -0.130 (3/sqrt(M_rooms) 0.588); rooms +/- 11 / 15
agree-full pooled bias band 7 [CHECK, additive]: mean (C++ - ref) -0.0009 dB over 70 case-bands; bound 3 SE_pool + mean l_ref = 0.0034 + 0.0047 = 0.0081 dB (within)
agree-full pooled bias band 7 [record, per reference room, z']: mean over 26 rooms -0.125 (3/sqrt(M_rooms) 0.588); rooms +/- 11 / 15
agree-full gated: 560 of 560 AX43 case-bands gated (0 reported, reference pending); 72 of 72 AX45 case-bands gated
agree-full summary: 560 gated AX43 case-bands, 72 gated AX45 case-bands, 0 reported (uncertified), 0 without reference; max |C++ - ref| 0.0460 dB over the gated set; 0 stage-2 runs; 0 failures (N_test 65536)
[36;1m    grep -E "^(05h|05i)-records|^agree-full (gated|summary)|^agree-full pooled bias band [0-9] \[(CHECK, additive|record, per reference room)" build/benchmark.log || echo "(no record lines)"[0m
```

## macos

```
agree-full pooled bias band 0 [CHECK, additive]: mean (C++ - ref) -0.0008 dB over 70 case-bands; bound 3 SE_pool + mean l_ref = 0.0035 + 0.0044 = 0.0079 dB (within)
agree-full pooled bias band 0 [record, per reference room, z']: mean over 26 rooms -0.132 (3/sqrt(M_rooms) 0.588); rooms +/- 10 / 16
agree-full pooled bias band 1 [CHECK, additive]: mean (C++ - ref) -0.0009 dB over 70 case-bands; bound 3 SE_pool + mean l_ref = 0.0035 + 0.0045 = 0.0080 dB (within)
agree-full pooled bias band 1 [record, per reference room, z']: mean over 26 rooms -0.135 (3/sqrt(M_rooms) 0.588); rooms +/- 10 / 16
agree-full pooled bias band 2 [CHECK, additive]: mean (C++ - ref) -0.0009 dB over 70 case-bands; bound 3 SE_pool + mean l_ref = 0.0035 + 0.0045 = 0.0080 dB (within)
agree-full pooled bias band 2 [record, per reference room, z']: mean over 26 rooms -0.138 (3/sqrt(M_rooms) 0.588); rooms +/- 10 / 16
agree-full pooled bias band 3 [CHECK, additive]: mean (C++ - ref) -0.0009 dB over 70 case-bands; bound 3 SE_pool + mean l_ref = 0.0034 + 0.0046 = 0.0080 dB (within)
agree-full pooled bias band 3 [record, per reference room, z']: mean over 26 rooms -0.139 (3/sqrt(M_rooms) 0.588); rooms +/- 10 / 16
agree-full pooled bias band 4 [CHECK, additive]: mean (C++ - ref) -0.0011 dB over 70 case-bands; bound 3 SE_pool + mean l_ref = 0.0034 + 0.0046 = 0.0080 dB (within)
agree-full pooled bias band 4 [record, per reference room, z']: mean over 26 rooms -0.139 (3/sqrt(M_rooms) 0.588); rooms +/- 11 / 15
agree-full pooled bias band 5 [CHECK, additive]: mean (C++ - ref) -0.0012 dB over 70 case-bands; bound 3 SE_pool + mean l_ref = 0.0034 + 0.0046 = 0.0080 dB (within)
agree-full pooled bias band 5 [record, per reference room, z']: mean over 26 rooms -0.137 (3/sqrt(M_rooms) 0.588); rooms +/- 11 / 15
agree-full pooled bias band 6 [CHECK, additive]: mean (C++ - ref) -0.0012 dB over 70 case-bands; bound 3 SE_pool + mean l_ref = 0.0034 + 0.0046 = 0.0080 dB (within)
agree-full pooled bias band 6 [record, per reference room, z']: mean over 26 rooms -0.130 (3/sqrt(M_rooms) 0.588); rooms +/- 11 / 15
agree-full pooled bias band 7 [CHECK, additive]: mean (C++ - ref) -0.0009 dB over 70 case-bands; bound 3 SE_pool + mean l_ref = 0.0034 + 0.0047 = 0.0081 dB (within)
agree-full pooled bias band 7 [record, per reference room, z']: mean over 26 rooms -0.125 (3/sqrt(M_rooms) 0.588); rooms +/- 11 / 15
agree-full gated: 560 of 560 AX43 case-bands gated (0 reported, reference pending); 72 of 72 AX45 case-bands gated
agree-full summary: 560 gated AX43 case-bands, 72 gated AX45 case-bands, 0 reported (uncertified), 0 without reference; max |C++ - ref| 0.0460 dB over the gated set; 0 stage-2 runs; 0 failures (N_test 65536)
05i-records (iv) AQ10 room                   48000 Hz, 1 inst: load until the last is audible 430 ms; per instance (load order) prepare [278] ms, restore [152] ms
05i-records (iv) AQ10 room                   48000 Hz, 1 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 151 median 151 max 151 ms
05i-records (iv) AQ10 room                   48000 Hz, 1 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 203 median 203 max 203 ms
05i-records (iv) AQ10 room                   48000 Hz, 1 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 299 median 299 max 299 ms
05i-records (iv) AQ10 room                   48000 Hz, 1 inst: worst host-thread wait of one instance while the other 0 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 191 ms, restore 199 ms, offline switch + first block after a room-size edit 177 ms
05i-records (iv) AQ10 room                   48000 Hz, 4 inst: load until the last is audible 1677 ms; per instance (load order) prepare [267 282 259 259] ms, restore [159 143 142 166] ms
05i-records (iv) AQ10 room                   48000 Hz, 4 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 154 median 367 max 602 ms
05i-records (iv) AQ10 room                   48000 Hz, 4 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 184 median 425 max 658 ms
05i-records (iv) AQ10 room                   48000 Hz, 4 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 6 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 290 median 693 max 1094 ms
05i-records (iv) AQ10 room                   48000 Hz, 4 inst: worst host-thread wait of one instance while the other 3 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 268 ms, restore 332 ms, offline switch + first block after a room-size edit 334 ms
05i-records (iv) AQ10 room                   48000 Hz, 8 inst: load until the last is audible 3475 ms; per instance (load order) prepare [285 279 252 263 266 304 257 317] ms, restore [157 164 160 142 159 147 142 180] ms
05i-records (iv) AQ10 room                   48000 Hz, 8 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 178 median 774 max 1325 ms
05i-records (iv) AQ10 room                   48000 Hz, 8 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 168 median 666 max 1138 ms
05i-records (iv) AQ10 room                   48000 Hz, 8 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 10 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 290 median 1341 max 2363 ms
05i-records (iv) AQ10 room                   48000 Hz, 8 inst: worst host-thread wait of one instance while the other 7 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 312 ms, restore 321 ms, offline switch + first block after a room-size edit 323 ms
05i-records (iv) AQ10 room                   96000 Hz, 1 inst: load until the last is audible 853 ms; per instance (load order) prepare [501] ms, restore [352] ms
05i-records (iv) AQ10 room                   96000 Hz, 1 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 350 median 350 max 350 ms
05i-records (iv) AQ10 room                   96000 Hz, 1 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 352 median 352 max 352 ms
05i-records (iv) AQ10 room                   96000 Hz, 1 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 658 median 658 max 658 ms
05i-records (iv) AQ10 room                   96000 Hz, 1 inst: worst host-thread wait of one instance while the other 0 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 399 ms, restore 455 ms, offline switch + first block after a room-size edit 410 ms
05i-records (iv) AQ10 room                   96000 Hz, 4 inst: load until the last is audible 2793 ms; per instance (load order) prepare [510 388 367 371] ms, restore [326 282 271 280] ms
05i-records (iv) AQ10 room                   96000 Hz, 4 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 278 median 692 max 1133 ms
05i-records (iv) AQ10 room                   96000 Hz, 4 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 365 median 849 max 1395 ms
05i-records (iv) AQ10 room                   96000 Hz, 4 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 6 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 569 median 1413 max 2438 ms
05i-records (iv) AQ10 room                   96000 Hz, 4 inst: worst host-thread wait of one instance while the other 3 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 657 ms, restore 749 ms, offline switch + first block after a room-size edit 746 ms
05i-records (iv) AQ10 room                   96000 Hz, 8 inst: load until the last is audible 7343 ms; per instance (load order) prepare [561 492 504 498 546 589 530 524] ms, restore [407 360 354 376 386 471 364 380] ms
05i-records (iv) AQ10 room                   96000 Hz, 8 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 381 median 1618 max 2852 ms
05i-records (iv) AQ10 room                   96000 Hz, 8 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 376 median 1460 max 2619 ms
05i-records (iv) AQ10 room                   96000 Hz, 8 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 10 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 720 median 3081 max 5570 ms
05i-records (iv) AQ10 room                   96000 Hz, 8 inst: worst host-thread wait of one instance while the other 7 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 723 ms, restore 724 ms, offline switch + first block after a room-size edit 784 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst: load until the last is audible 1012 ms; per instance (load order) prepare [239] ms, restore [774] ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 1015 median 1015 max 1015 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 834 median 834 max 834 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 1623 median 1623 max 1623 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst: worst host-thread wait of one instance while the other 0 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 840 ms, restore 980 ms, offline switch + first block after a room-size edit 1018 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst: load until the last is audible 4429 ms; per instance (load order) prepare [273 292 283 256] ms, restore [832 807 881 804] ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 837 median 1961 max 3056 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 719 median 1879 max 3137 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 6 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 1288 median 3385 max 5648 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst: worst host-thread wait of one instance while the other 3 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 2249 ms, restore 2299 ms, offline switch + first block after a room-size edit 2220 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst: load until the last is audible 8444 ms; per instance (load order) prepare [284 269 230 227 300 222 250 243] ms, restore [918 907 801 802 718 733 740 800] ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 794 median 3491 max 5947 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 668 median 3015 max 5466 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 10 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 1430 median 6421 max 11398 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst: worst host-thread wait of one instance while the other 7 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 1698 ms, restore 1698 ms, offline switch + first block after a room-size edit 1525 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst: load until the last is audible 2175 ms; per instance (load order) prepare [396] ms, restore [1779] ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 1688 median 1688 max 1688 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 1752 median 1752 max 1752 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 3325 median 3325 max 3325 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst: worst host-thread wait of one instance while the other 0 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 1924 ms, restore 2485 ms, offline switch + first block after a room-size edit 2400 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst: load until the last is audible 11039 ms; per instance (load order) prepare [517 442 536 565] ms, restore [2300 2006 2232 2440] ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 1812 median 4413 max 7339 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 2028 median 5470 max 8952 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 6 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 3825 median 9437 max 16730 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst: worst host-thread wait of one instance while the other 3 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 5043 ms, restore 4856 ms, offline switch + first block after a room-size edit 4824 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst: load until the last is audible 16323 ms; per instance (load order) prepare [398 355 367 360 345 424 399 389] ms, restore [1581 1594 1517 1591 1682 1717 1679 1925] ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 1674 median 7865 max 14588 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 1960 median 8213 max 14376 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 10 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 3609 median 15631 max 27899 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst: worst host-thread wait of one instance while the other 7 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 3621 ms, restore 3616 ms, offline switch + first block after a room-size edit 3669 ms
05h-records GATE os=macOS scene=cube100_flutter_fallback x14worst=7.42 median=495 fullRebuildMedian=465 solveMedianMs=102.7 nsPerEval=9.00 status=asserted(30s) flutterRef=484 flutterDev=+2.4%
05h-records GATE os=macOS scene=cube100_lowalpha0.05_s0.3 ratio=3.845 ratioWarnAt=4.500 solveMedianMs=83.7 nsPerEval=6.92 x14worst=43.54 median=1905 growthBound=1999 fullRebuildMedian=1954 status=reported-only trigger=2172 warnings=OVER30S 
05i-records (iv) offline AQ10 room                   48000 Hz, 1 offline instance in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 148 median 162 worst 184 ms; first build (after restore) worst 195 ms; wall 852 ms
05i-records (iv) offline AQ10 room                   48000 Hz, 4 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 551 median 573 worst 608 ms; first build (after restore) worst 607 ms; wall 2882 ms
05i-records (iv) offline AQ10 room                   48000 Hz, 8 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 1005 median 1192 worst 1355 ms; first build (after restore) worst 1277 ms; wall 5815 ms
05i-records (iv) offline AQ10 room                   96000 Hz, 1 offline instance in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 288 median 294 worst 313 ms; first build (after restore) worst 299 ms; wall 1488 ms
05i-records (iv) offline AQ10 room                   96000 Hz, 4 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 1094 median 1106 worst 1142 ms; first build (after restore) worst 1140 ms; wall 5581 ms
05i-records (iv) offline AQ10 room                   96000 Hz, 8 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 2149 median 2294 worst 2597 ms; first build (after restore) worst 2502 ms; wall 11652 ms
05i-records (iv) offline cube100_lowalpha0.05_s0.3   48000 Hz, 1 offline instance in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 784 median 792 worst 872 ms; first build (after restore) worst 797 ms; wall 4037 ms
05i-records (iv) offline cube100_lowalpha0.05_s0.3   48000 Hz, 4 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 3208 median 3378 worst 3510 ms; first build (after restore) worst 3271 ms; wall 16678 ms
05i-records (iv) offline cube100_lowalpha0.05_s0.3   48000 Hz, 8 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 5752 median 6043 worst 6390 ms; first build (after restore) worst 6342 ms; wall 30307 ms
05i-records (iv) offline cube100_lowalpha0.05_s0.3   96000 Hz, 1 offline instance in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 1734 median 1891 worst 1957 ms; first build (after restore) worst 1834 ms; wall 9307 ms
05i-records (iv) offline cube100_lowalpha0.05_s0.3   96000 Hz, 4 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 7156 median 7456 worst 7743 ms; first build (after restore) worst 7300 ms; wall 37156 ms
05i-records (iv) offline cube100_lowalpha0.05_s0.3   96000 Hz, 8 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 13634 median 14517 worst 14980 ms; first build (after restore) worst 14699 ms; wall 71696 ms
05i-records K-e12 os=macOS cube100_flutter_fallback   96 kHz: restore with a room edit in flight (room size -1/-2 m in w/d/h, restore of a new room size at a random point of the 624 ms rebuild), 10 runs: min 482 median 552 worst 675 ms (idle restore of a new state median 501 ms, 3 runs); per-restore budget 2143 ms: within
05i-records K-e12 os=macOS cube100_flutter_fallback   run  0: restore at 168 ms of 624 -> host thread 532 ms
05i-records K-e12 os=macOS cube100_flutter_fallback   run  1: restore at 617 ms of 624 -> host thread 482 ms
05i-records K-e12 os=macOS cube100_flutter_fallback   run  2: restore at 58 ms of 624 -> host thread 548 ms
05i-records K-e12 os=macOS cube100_flutter_fallback   run  3: restore at 490 ms of 624 -> host thread 494 ms
05i-records K-e12 os=macOS cube100_flutter_fallback   run  4: restore at 303 ms of 624 -> host thread 556 ms
05i-records K-e12 os=macOS cube100_flutter_fallback   run  5: restore at 332 ms of 624 -> host thread 635 ms
05i-records K-e12 os=macOS cube100_flutter_fallback   run  6: restore at 175 ms of 624 -> host thread 509 ms
05i-records K-e12 os=macOS cube100_flutter_fallback   run  7: restore at 141 ms of 624 -> host thread 638 ms
05i-records K-e12 os=macOS cube100_flutter_fallback   run  8: restore at 230 ms of 624 -> host thread 675 ms
05i-records K-e12 os=macOS cube100_flutter_fallback   run  9: restore at 50 ms of 624 -> host thread 613 ms
05i-records K-e12 os=macOS cube100_lowalpha0.05_s0.3  96 kHz: restore with a room edit in flight (room size -1/-2 m in w/d/h, restore of a new room size at a random point of the 1941 ms rebuild), 10 runs: min 1665 median 1967 worst 2648 ms (idle restore of a new state median 1803 ms, 3 runs); per-restore budget 2143 ms: FINDING (worst above the budget; register form, remedy phase-07c conditions 9-10)
05i-records K-e12 os=macOS cube100_lowalpha0.05_s0.3  run  0: restore at 1455 ms of 1941 -> host thread 2019 ms
05i-records K-e12 os=macOS cube100_lowalpha0.05_s0.3  run  1: restore at 159 ms of 1941 -> host thread 2265 ms
05i-records K-e12 os=macOS cube100_lowalpha0.05_s0.3  run  2: restore at 1834 ms of 1941 -> host thread 1786 ms
05i-records K-e12 os=macOS cube100_lowalpha0.05_s0.3  run  3: restore at 1881 ms of 1941 -> host thread 1729 ms
05i-records K-e12 os=macOS cube100_lowalpha0.05_s0.3  run  4: restore at 1355 ms of 1941 -> host thread 1915 ms
05i-records K-e12 os=macOS cube100_lowalpha0.05_s0.3  run  5: restore at 214 ms of 1941 -> host thread 1775 ms
05i-records K-e12 os=macOS cube100_lowalpha0.05_s0.3  run  6: restore at 771 ms of 1941 -> host thread 2648 ms
05i-records K-e12 os=macOS cube100_lowalpha0.05_s0.3  run  7: restore at 1405 ms of 1941 -> host thread 1665 ms
05i-records K-e12 os=macOS cube100_lowalpha0.05_s0.3  run  8: restore at 1009 ms of 1941 -> host thread 2369 ms
05i-records K-e12 os=macOS cube100_lowalpha0.05_s0.3  run  9: restore at 570 ms of 1941 -> host thread 2363 ms
[36;1m    grep -E "^(05h|05i)-records|^agree-full (gated|summary)|^agree-full pooled bias band [0-9] \[(CHECK, additive|record, per reference room)" build/benchmark.log || echo "(no record lines)"[0m
```

## windows

```
05i-records (iv) AQ10 room                   48000 Hz, 1 inst: load until the last is audible 572 ms; per instance (load order) prepare [363] ms, restore [210] ms
05i-records (iv) AQ10 room                   48000 Hz, 1 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 208 median 208 max 208 ms
05i-records (iv) AQ10 room                   48000 Hz, 1 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 216 median 216 max 216 ms
05i-records (iv) AQ10 room                   48000 Hz, 1 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 412 median 412 max 412 ms
05i-records (iv) AQ10 room                   48000 Hz, 1 inst: worst host-thread wait of one instance while the other 0 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 205 ms, restore 210 ms, offline switch + first block after a room-size edit 200 ms
05i-records (iv) AQ10 room                   48000 Hz, 4 inst: load until the last is audible 2213 ms; per instance (load order) prepare [345 350 341 348] ms, restore [208 206 205 209] ms
05i-records (iv) AQ10 room                   48000 Hz, 4 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 213 median 515 max 815 ms
05i-records (iv) AQ10 room                   48000 Hz, 4 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 210 median 517 max 827 ms
05i-records (iv) AQ10 room                   48000 Hz, 4 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 6 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 396 median 983 max 1580 ms
05i-records (iv) AQ10 room                   48000 Hz, 4 inst: worst host-thread wait of one instance while the other 3 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 409 ms, restore 410 ms, offline switch + first block after a room-size edit 401 ms
05i-records (iv) AQ10 room                   48000 Hz, 8 inst: load until the last is audible 4447 ms; per instance (load order) prepare [349 337 353 345 360 362 343 350] ms, restore [203 204 205 205 205 205 206 215] ms
05i-records (iv) AQ10 room                   48000 Hz, 8 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 199 median 892 max 1597 ms
05i-records (iv) AQ10 room                   48000 Hz, 8 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 205 median 923 max 1637 ms
05i-records (iv) AQ10 room                   48000 Hz, 8 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 10 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 393 median 1792 max 3177 ms
05i-records (iv) AQ10 room                   48000 Hz, 8 inst: worst host-thread wait of one instance while the other 7 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 414 ms, restore 401 ms, offline switch + first block after a room-size edit 390 ms
05i-records (iv) AQ10 room                   96000 Hz, 1 inst: load until the last is audible 992 ms; per instance (load order) prepare [572] ms, restore [419] ms
05i-records (iv) AQ10 room                   96000 Hz, 1 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 414 median 414 max 414 ms
05i-records (iv) AQ10 room                   96000 Hz, 1 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 421 median 421 max 421 ms
05i-records (iv) AQ10 room                   96000 Hz, 1 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 818 median 818 max 818 ms
05i-records (iv) AQ10 room                   96000 Hz, 1 inst: worst host-thread wait of one instance while the other 0 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 410 ms, restore 431 ms, offline switch + first block after a room-size edit 401 ms
05i-records (iv) AQ10 room                   96000 Hz, 4 inst: load until the last is audible 3920 ms; per instance (load order) prepare [554 551 565 570] ms, restore [413 414 424 429] ms
05i-records (iv) AQ10 room                   96000 Hz, 4 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 421 median 1027 max 1637 ms
05i-records (iv) AQ10 room                   96000 Hz, 4 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 417 median 1029 max 1647 ms
05i-records (iv) AQ10 room                   96000 Hz, 4 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 6 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 823 median 2054 max 3292 ms
05i-records (iv) AQ10 room                   96000 Hz, 4 inst: worst host-thread wait of one instance while the other 3 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 829 ms, restore 821 ms, offline switch + first block after a room-size edit 807 ms
05i-records (iv) AQ10 room                   96000 Hz, 8 inst: load until the last is audible 7963 ms; per instance (load order) prepare [576 561 559 572 573 574 567 564] ms, restore [418 421 426 425 426 436 433 432] ms
05i-records (iv) AQ10 room                   96000 Hz, 8 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 421 median 1852 max 3280 ms
05i-records (iv) AQ10 room                   96000 Hz, 8 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 415 median 1854 max 3297 ms
05i-records (iv) AQ10 room                   96000 Hz, 8 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 10 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 822 median 3695 max 6526 ms
05i-records (iv) AQ10 room                   96000 Hz, 8 inst: worst host-thread wait of one instance while the other 7 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 818 ms, restore 822 ms, offline switch + first block after a room-size edit 796 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst: load until the last is audible 1229 ms; per instance (load order) prepare [361] ms, restore [868] ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 881 median 881 max 881 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 883 median 883 max 883 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 1736 median 1736 max 1736 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst: worst host-thread wait of one instance while the other 0 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 889 ms, restore 897 ms, offline switch + first block after a room-size edit 917 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst: load until the last is audible 4943 ms; per instance (load order) prepare [360 335 359 348] ms, restore [867 879 914 881] ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 903 median 2230 max 3578 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 942 median 2259 max 3572 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 6 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 1761 median 4392 max 7025 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst: worst host-thread wait of one instance while the other 3 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 1772 ms, restore 1770 ms, offline switch + first block after a room-size edit 1749 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst: load until the last is audible 9900 ms; per instance (load order) prepare [335 335 342 344 361 346 351 364] ms, restore [878 874 903 889 889 897 903 890] ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 902 median 4025 max 7201 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 937 median 4149 max 7314 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 10 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 1794 median 8099 max 14392 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst: worst host-thread wait of one instance while the other 7 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 1737 ms, restore 1752 ms, offline switch + first block after a room-size edit 1777 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst: load until the last is audible 2466 ms; per instance (load order) prepare [552] ms, restore [1914] ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 1958 median 1958 max 1958 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 1919 median 1919 max 1919 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 3906 median 3906 max 3906 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst: worst host-thread wait of one instance while the other 0 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 1928 ms, restore 1904 ms, offline switch + first block after a room-size edit 1919 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst: load until the last is audible 10067 ms; per instance (load order) prepare [556 559 578 562] ms, restore [1924 1940 2004 1945] ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 1916 median 4775 max 7606 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 1925 median 4787 max 7668 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 6 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 3877 median 9628 max 15349 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst: worst host-thread wait of one instance while the other 3 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 3816 ms, restore 3823 ms, offline switch + first block after a room-size edit 3823 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst: load until the last is audible 23009 ms; per instance (load order) prepare [554 562 562 568 578 679 697 687] ms, restore [1968 1996 2039 1926 2418 2575 2527 2674] ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 2497 median 9635 max 16421 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 1941 median 8521 max 15128 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 10 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 4591 median 18466 max 31849 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst: worst host-thread wait of one instance while the other 7 rebuild without pause (room size stepping 1 m every 50 ms), 3 runs: prepare 3870 ms, restore 3853 ms, offline switch + first block after a room-size edit 3825 ms
05i-records (iv) offline AQ10 room                   48000 Hz, 1 offline instance in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 196 median 198 worst 202 ms; first build (after restore) worst 204 ms; wall 997 ms
05i-records (iv) offline AQ10 room                   48000 Hz, 4 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 747 median 772 worst 789 ms; first build (after restore) worst 800 ms; wall 3858 ms
05i-records (iv) offline AQ10 room                   48000 Hz, 8 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 1494 median 1539 worst 1576 ms; first build (after restore) worst 1589 ms; wall 7691 ms
05i-records (iv) offline AQ10 room                   96000 Hz, 1 offline instance in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 396 median 404 worst 414 ms; first build (after restore) worst 427 ms; wall 2046 ms
05i-records (iv) offline AQ10 room                   96000 Hz, 4 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 1574 median 1603 worst 1641 ms; first build (after restore) worst 1657 ms; wall 8055 ms
05i-records (iv) offline AQ10 room                   96000 Hz, 8 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 3124 median 3173 worst 3272 ms; first build (after restore) worst 3295 ms; wall 16009 ms
05i-records (iv) offline cube100_lowalpha0.05_s0.3   48000 Hz, 1 offline instance in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 868 median 874 worst 890 ms; first build (after restore) worst 882 ms; wall 4387 ms
05i-records (iv) offline cube100_lowalpha0.05_s0.3   48000 Hz, 4 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 3434 median 3493 worst 3555 ms; first build (after restore) worst 3497 ms; wall 17440 ms
05i-records (iv) offline cube100_lowalpha0.05_s0.3   48000 Hz, 8 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 6907 median 7022 worst 7119 ms; first build (after restore) worst 7079 ms; wall 35121 ms
05i-records (iv) offline cube100_lowalpha0.05_s0.3   96000 Hz, 1 offline instance in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 1996 median 2015 worst 2018 ms; first build (after restore) worst 1909 ms; wall 9953 ms
05i-records (iv) offline cube100_lowalpha0.05_s0.3   96000 Hz, 4 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 7563 median 7612 worst 7646 ms; first build (after restore) worst 7752 ms; wall 38164 ms
05i-records (iv) offline cube100_lowalpha0.05_s0.3   96000 Hz, 8 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 15125 median 15315 worst 15610 ms; first build (after restore) worst 15242 ms; wall 76565 ms
agree-full pooled bias band 0 [CHECK, additive]: mean (C++ - ref) -0.0008 dB over 70 case-bands; bound 3 SE_pool + mean l_ref = 0.0035 + 0.0044 = 0.0079 dB (within)
agree-full pooled bias band 0 [record, per reference room, z']: mean over 26 rooms -0.132 (3/sqrt(M_rooms) 0.588); rooms +/- 10 / 16
agree-full pooled bias band 1 [CHECK, additive]: mean (C++ - ref) -0.0009 dB over 70 case-bands; bound 3 SE_pool + mean l_ref = 0.0035 + 0.0045 = 0.0080 dB (within)
agree-full pooled bias band 1 [record, per reference room, z']: mean over 26 rooms -0.135 (3/sqrt(M_rooms) 0.588); rooms +/- 10 / 16
agree-full pooled bias band 2 [CHECK, additive]: mean (C++ - ref) -0.0009 dB over 70 case-bands; bound 3 SE_pool + mean l_ref = 0.0035 + 0.0045 = 0.0080 dB (within)
agree-full pooled bias band 2 [record, per reference room, z']: mean over 26 rooms -0.138 (3/sqrt(M_rooms) 0.588); rooms +/- 10 / 16
agree-full pooled bias band 3 [CHECK, additive]: mean (C++ - ref) -0.0009 dB over 70 case-bands; bound 3 SE_pool + mean l_ref = 0.0034 + 0.0046 = 0.0080 dB (within)
agree-full pooled bias band 3 [record, per reference room, z']: mean over 26 rooms -0.139 (3/sqrt(M_rooms) 0.588); rooms +/- 10 / 16
agree-full pooled bias band 4 [CHECK, additive]: mean (C++ - ref) -0.0011 dB over 70 case-bands; bound 3 SE_pool + mean l_ref = 0.0034 + 0.0046 = 0.0080 dB (within)
agree-full pooled bias band 4 [record, per reference room, z']: mean over 26 rooms -0.139 (3/sqrt(M_rooms) 0.588); rooms +/- 11 / 15
agree-full pooled bias band 5 [CHECK, additive]: mean (C++ - ref) -0.0012 dB over 70 case-bands; bound 3 SE_pool + mean l_ref = 0.0034 + 0.0046 = 0.0080 dB (within)
agree-full pooled bias band 5 [record, per reference room, z']: mean over 26 rooms -0.137 (3/sqrt(M_rooms) 0.588); rooms +/- 11 / 15
agree-full pooled bias band 6 [CHECK, additive]: mean (C++ - ref) -0.0012 dB over 70 case-bands; bound 3 SE_pool + mean l_ref = 0.0034 + 0.0046 = 0.0080 dB (within)
agree-full pooled bias band 6 [record, per reference room, z']: mean over 26 rooms -0.130 (3/sqrt(M_rooms) 0.588); rooms +/- 11 / 15
agree-full pooled bias band 7 [CHECK, additive]: mean (C++ - ref) -0.0009 dB over 70 case-bands; bound 3 SE_pool + mean l_ref = 0.0034 + 0.0047 = 0.0081 dB (within)
agree-full pooled bias band 7 [record, per reference room, z']: mean over 26 rooms -0.125 (3/sqrt(M_rooms) 0.588); rooms +/- 11 / 15
agree-full gated: 560 of 560 AX43 case-bands gated (0 reported, reference pending); 72 of 72 AX45 case-bands gated
agree-full summary: 560 gated AX43 case-bands, 72 gated AX45 case-bands, 0 reported (uncertified), 0 without reference; max |C++ - ref| 0.0460 dB over the gated set; 0 stage-2 runs; 0 failures (N_test 65536)
05i-records K-e12 os=Windows cube100_flutter_fallback   96 kHz: restore with a room edit in flight (room size -1/-2 m in w/d/h, restore of a new room size at a random point of the 742 ms rebuild), 10 runs: min 745 median 883 worst 1031 ms (idle restore of a new state median 740 ms, 3 runs); per-restore budget 2143 ms: within
05i-records K-e12 os=Windows cube100_flutter_fallback   run  0: restore at 200 ms of 742 -> host thread 890 ms
05i-records K-e12 os=Windows cube100_flutter_fallback   run  1: restore at 734 ms of 742 -> host thread 745 ms
05i-records K-e12 os=Windows cube100_flutter_fallback   run  2: restore at 69 ms of 742 -> host thread 1015 ms
05i-records K-e12 os=Windows cube100_flutter_fallback   run  3: restore at 583 ms of 742 -> host thread 903 ms
05i-records K-e12 os=Windows cube100_flutter_fallback   run  4: restore at 360 ms of 742 -> host thread 761 ms
05i-records K-e12 os=Windows cube100_flutter_fallback   run  5: restore at 395 ms of 742 -> host thread 751 ms
05i-records K-e12 os=Windows cube100_flutter_fallback   run  6: restore at 208 ms of 742 -> host thread 876 ms
05i-records K-e12 os=Windows cube100_flutter_fallback   run  7: restore at 168 ms of 742 -> host thread 916 ms
05i-records K-e12 os=Windows cube100_flutter_fallback   run  8: restore at 273 ms of 742 -> host thread 807 ms
05i-records K-e12 os=Windows cube100_flutter_fallback   run  9: restore at 60 ms of 742 -> host thread 1031 ms
05i-records K-e12 os=Windows cube100_lowalpha0.05_s0.3  96 kHz: restore with a room edit in flight (room size -1/-2 m in w/d/h, restore of a new room size at a random point of the 1931 ms rebuild), 10 runs: min 1948 median 2377 worst 3231 ms (idle restore of a new state median 1939 ms, 3 runs); per-restore budget 2143 ms: FINDING (worst above the budget; register form, remedy phase-07c conditions 9-10)
05i-records K-e12 os=Windows cube100_lowalpha0.05_s0.3  run  0: restore at 1447 ms of 1931 -> host thread 2411 ms
05i-records K-e12 os=Windows cube100_lowalpha0.05_s0.3  run  1: restore at 158 ms of 1931 -> host thread 2344 ms
05i-records K-e12 os=Windows cube100_lowalpha0.05_s0.3  run  2: restore at 1823 ms of 1931 -> host thread 2023 ms
05i-records K-e12 os=Windows cube100_lowalpha0.05_s0.3  run  3: restore at 1870 ms of 1931 -> host thread 1964 ms
05i-records K-e12 os=Windows cube100_lowalpha0.05_s0.3  run  4: restore at 1348 ms of 1931 -> host thread 2461 ms
05i-records K-e12 os=Windows cube100_lowalpha0.05_s0.3  run  5: restore at 213 ms of 1931 -> host thread 2284 ms
05i-records K-e12 os=Windows cube100_lowalpha0.05_s0.3  run  6: restore at 766 ms of 1931 -> host thread 3231 ms
05i-records K-e12 os=Windows cube100_lowalpha0.05_s0.3  run  7: restore at 1397 ms of 1931 -> host thread 2473 ms
05i-records K-e12 os=Windows cube100_lowalpha0.05_s0.3  run  8: restore at 1003 ms of 1931 -> host thread 2867 ms
05i-records K-e12 os=Windows cube100_lowalpha0.05_s0.3  run  9: restore at 567 ms of 1931 -> host thread 1948 ms
05h-records GATE os=Windows scene=cube100_flutter_fallback x14worst=10.58 median=747 fullRebuildMedian=746 solveMedianMs=145.0 nsPerEval=12.72 status=asserted(30s) flutterRef=737 flutterDev=+1.3%
05h-records GATE os=Windows scene=cube100_lowalpha0.05_s0.3 ratio=2.673 ratioWarnAt=3.396 solveMedianMs=90.6 nsPerEval=7.50 x14worst=28.74 median=1996 growthBound=2231 fullRebuildMedian=1973 status=asserted trigger=0 warnings=PASSES30S 
[36;1m    grep -E "^(05h|05i)-records|^agree-full (gated|summary)|^agree-full pooled bias band [0-9] \[(CHECK, additive|record, per reference room)" build/benchmark.log || echo "(no record lines)"[0m
```

