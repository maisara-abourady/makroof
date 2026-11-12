# 19 — Orchestrator: CI records, run 43215018040 (commit 517e556), Linux and macOS (phase 07c-1)

2026-11-12. https://github.com/maisara-abourady/makroof/actions/runs/43215018040 — build (linux) job 131172413297 success, build (macos) job 131172413185 success, TSan (linux) 131172413153 success, ASan + UBSan (linux) 131172413097 success, host trace build (linux) 131172413150 success; build (windows) 131172413087 FAILED on a test bug (test_host_trace.cpp removed an open file; fixed in 3f89b6e), so the Windows records come from the next run. Records (b) = the 05i gate-wait lines (queue(Synchronous) per call), (c) = callback p99.9 lines, (d) = 07c1 cond12 and 05h quiesce lines, (f) = 07c1 cond12 process RSS lines, (g) = the 05i (iv) staleness lines; condition 10 = 07c1 cond10 lines; the 3-minute bounce (pre-condition-9) = the 05h bounce lines. Lines extracted verbatim from the job logs (timestamps stripped). Printed, never asserted.

### Linux (job log, run 43215018040, commit 517e556)

```
100% tests passed, 0 tests failed out of 231
07c1-records cond10 cube100_lowalpha0.05_s0.3   48000 Hz, Linux: cancel at 2 % of a 766 ms rebuild (builder busy): setNonRealtime(true) 0.26 ms, cancel unwind 11.5 ms, first offline block 756 ms; transient RSS delta 127 MB (process, RSS before 93864 kB)
07c1-records cond10 cube100_lowalpha0.05_s0.3   48000 Hz, Linux: cancel at 10 % of a 766 ms rebuild (builder busy): setNonRealtime(true) 0.27 ms, cancel unwind 2.8 ms, first offline block 739 ms; transient RSS delta 127 MB (process, RSS before 108388 kB)
07c1-records cond10 cube100_lowalpha0.05_s0.3   48000 Hz, Linux: cancel at 30 % of a 766 ms rebuild (builder busy): setNonRealtime(true) 0.27 ms, cancel unwind 39.8 ms, first offline block 744 ms; transient RSS delta 157 MB (process, RSS before 122664 kB)
07c1-records cond10 cube100_lowalpha0.05_s0.3   48000 Hz, Linux: cancel at 60 % of a 766 ms rebuild (builder busy): setNonRealtime(true) 0.26 ms, cancel unwind 33.0 ms, first offline block 750 ms; transient RSS delta 156 MB (process, RSS before 109200 kB)
07c1-records cond10 cube100_lowalpha0.05_s0.3   48000 Hz, Linux: cancel at 90 % of a 766 ms rebuild (builder busy): setNonRealtime(true) 0.27 ms, cancel unwind 9.2 ms, first offline block 776 ms; transient RSS delta 170 MB (process, RSS before 95292 kB)
07c1-records cond10 cube100_lowalpha0.05_s0.3   48000 Hz, Linux: WORST setNonRealtime(true) 0.27 ms (was: the in-flight build, AX38 (i) entry 2 664 ms), cancel unwind 39.8 ms, first offline block 776 ms, transient RSS delta 170 MB
07c1-records cond10 cube100_lowalpha0.05_s0.3   96000 Hz, Linux: cancel at 2 % of a 1919 ms rebuild (builder busy): setNonRealtime(true) 0.56 ms, cancel unwind 16.0 ms, first offline block 1882 ms; transient RSS delta 284 MB (process, RSS before 146300 kB)
07c1-records cond10 cube100_lowalpha0.05_s0.3   96000 Hz, Linux: cancel at 10 % of a 1919 ms rebuild (builder busy): setNonRealtime(true) 0.92 ms, cancel unwind 14.6 ms, first offline block 1917 ms; transient RSS delta 285 MB (process, RSS before 173520 kB)
07c1-records cond10 cube100_lowalpha0.05_s0.3   96000 Hz, Linux: cancel at 30 % of a 1919 ms rebuild (builder busy): setNonRealtime(true) 0.64 ms, cancel unwind 102.7 ms, first offline block 1843 ms; transient RSS delta 233 MB (process, RSS before 201996 kB)
07c1-records cond10 cube100_lowalpha0.05_s0.3   96000 Hz, Linux: cancel at 60 % of a 1919 ms rebuild (builder busy): setNonRealtime(true) 0.76 ms, cancel unwind 97.6 ms, first offline block 1847 ms; transient RSS delta 266 MB (process, RSS before 176876 kB)
07c1-records cond10 cube100_lowalpha0.05_s0.3   96000 Hz, Linux: cancel at 90 % of a 1919 ms rebuild (builder busy): setNonRealtime(true) 0.63 ms, cancel unwind 28.4 ms, first offline block 1810 ms; transient RSS delta 309 MB (process, RSS before 150808 kB)
07c1-records cond10 cube100_lowalpha0.05_s0.3   96000 Hz, Linux: WORST setNonRealtime(true) 0.92 ms (was: the in-flight build, AX38 (i) entry 2 664 ms), cancel unwind 102.7 ms, first offline block 1917 ms, transient RSS delta 309 MB
05h-records AQ4 AQ10 room                   48000 Hz: R (position-only, builder) 20 ms, full rebuild 164 ms, 2P 21.3 ms; R + 2P 41 ms (100 ms), 2R + 2P 61 ms (700 ms), full + 2P 185 ms (3 s)
05h-records AQ4 AQ10 room                   96000 Hz: R (position-only, builder) 20 ms, full rebuild 346 ms, 2P 10.7 ms; R + 2P 31 ms (100 ms), 2R + 2P 51 ms (700 ms), full + 2P 357 ms (3 s)
05h-records AQ4 cube100_lowalpha0.05_s0.3   48000 Hz: R (position-only, builder) 20 ms, full rebuild 791 ms, 2P 21.3 ms; R + 2P 42 ms (100 ms), 2R + 2P 62 ms (700 ms), full + 2P 812 ms (3 s)
05h-records AQ4 cube100_lowalpha0.05_s0.3   96000 Hz: R (position-only, builder) 20 ms, full rebuild 1870 ms, 2P 10.7 ms; R + 2P 31 ms (100 ms), 2R + 2P 51 ms (700 ms), full + 2P 1881 ms (3 s)
05h-records bounce 100 m cube  48000 Hz: 3-minute offline bounce with the room size stepping 1 m every 5 s (36 rebuilds): 55.5 s wall, ratio to real time 0.31 x
05h-records bounce 100 m cube  96000 Hz: 3-minute offline bounce with the room size stepping 1 m every 5 s (36 rebuilds): 239.2 s wall, ratio to real time 1.33 x
05h-records callback p99.9 at host buffer 64 (1333 us period), 1 concurrent builder at 100 m: p99.9 193 us, max 919 us over 6774 callbacks (10 s)
05h-records callback p99.9 at host buffer 64 (1333 us period), 4 concurrent builders at 100 m: p99.9 1224 us, max 1276 us over 6629 callbacks (10 s)
05h-records callback p99.9 at host buffer 64 (1333 us period), 8 concurrent builders at 100 m: p99.9 1178 us, max 3196 us over 6281 callbacks (10 s)
05h-records (iv) AQ10 room                   48000 Hz, 1 instances: load until the last is audible 420 ms; staleness when rebuilding together min 172 median 172 max 172 ms
05h-records (iv) AQ10 room                   48000 Hz, 4 instances: load until the last is audible 1701 ms; staleness when rebuilding together min 256 median 286 max 301 ms
05h-records (iv) AQ10 room                   48000 Hz, 8 instances: load until the last is audible 3407 ms; staleness when rebuilding together min 405 median 576 max 651 ms
05h-records (iv) AQ10 room                   96000 Hz, 1 instances: load until the last is audible 827 ms; staleness when rebuilding together min 376 median 376 max 376 ms
05h-records (iv) AQ10 room                   96000 Hz, 4 instances: load until the last is audible 3306 ms; staleness when rebuilding together min 625 median 686 max 695 ms
05h-records (iv) AQ10 room                   96000 Hz, 8 instances: load until the last is audible 6597 ms; staleness when rebuilding together min 1108 median 1361 max 1441 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 instances: load until the last is audible 1150 ms; staleness when rebuilding together min 808 median 808 max 808 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 instances: load until the last is audible 4404 ms; staleness when rebuilding together min 1351 median 1622 max 1712 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 instances: load until the last is audible 8628 ms; staleness when rebuilding together min 2297 median 3132 max 3330 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 instances: load until the last is audible 2412 ms; staleness when rebuilding together min 1931 median 1931 max 1931 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 instances: load until the last is audible 9785 ms; staleness when rebuilding together min 3288 median 3479 max 3606 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 instances: load until the last is audible 19165 ms; staleness when rebuilding together min 5041 median 6593 max 6900 ms
05h-records pool size 4
05h-records full rebuild dead_booth.json         48000 Hz: min 70 median 70 max 72 ms (3 runs)
05h-records full rebuild dead_booth.json         96000 Hz: min 116 median 117 max 118 ms (3 runs)
05h-records full rebuild living_room.json        48000 Hz: min 80 median 80 max 80 ms (3 runs)
05h-records full rebuild living_room.json        96000 Hz: min 169 median 178 max 179 ms (3 runs)
05h-records full rebuild classroom.json          48000 Hz: min 87 median 93 max 99 ms (3 runs)
05h-records full rebuild classroom.json          96000 Hz: min 186 median 191 max 192 ms (3 runs)
05h-records full rebuild club.json               48000 Hz: min 165 median 166 max 166 ms (3 runs)
05h-records full rebuild club.json               96000 Hz: min 344 median 350 max 376 ms (3 runs)
05h-records full rebuild concert_hall_box.json   48000 Hz: min 181 median 182 max 182 ms (3 runs)
05h-records full rebuild concert_hall_box.json   96000 Hz: min 394 median 394 max 398 ms (3 runs)
05h-records full rebuild stone_box.json          48000 Hz: min 363 median 367 max 368 ms (3 runs)
05h-records full rebuild stone_box.json          96000 Hz: min 814 median 833 max 867 ms (3 runs)
05h-records full rebuild AQ10 room           48000 Hz: min 161 median 165 max 165 ms
05h-records full rebuild AQ10 room           96000 Hz: min 346 median 348 max 348 ms
05h-records full rebuild cube100_flutter_fallback    48000 Hz: min 356 median 357 max 358 ms; transient RSS delta 36 MB (sampled max 58748 kB, RSS before 22020 kB)
05h-records full rebuild cube100_flutter_fallback    96000 Hz: min 639 median 643 max 643 ms; transient RSS delta 81 MB (sampled max 103424 kB, RSS before 19980 kB)
05h-records work ratio cube100_flutter_fallback   e0: realised work / W_scene 0.9347 (W_pilot 3154338, W_final 2547436, W_scene 6100000); achieved SE 0.002 dB; fallback yes
05h-records work ratio cube100_flutter_fallback   e1: realised work / W_scene 0.9347 (W_pilot 3154338, W_final 2547436, W_scene 6100000); achieved SE 0.001 dB; fallback yes
05h-records work pin cube100_flutter_fallback   unit decay 377517 samples (pinned 377517); synthesis FFT size 524288, generator 524288 (pinned 524288)
05h-records solve cube100_flutter_fallback   shipping rule, median of 5: 131.3 ms; 11.52 ns per image evaluation over W_pilot + W_final 11403548 (print, RG-1)
05h-records restore cube100_flutter_fallback   96 kHz with the solve, 10 runs: min 590 median 599 worst 640 ms; 14 x worst 8.96 s (30 s)
05h-records restore gate cube100_flutter_fallback   Linux: strict (recorded 10.59 s <= 29.1 s): 14 x worst 8.96 s <= 30 s
05h-records restore cube100_flutter_fallback   96 kHz contended (another pipeline solving the same room): min 667 median 670 worst 675 ms (3 runs)
05h-records full rebuild cube100_lowalpha0.05_s0.3   48000 Hz: min 787 median 793 max 806 ms; transient RSS delta 137 MB (sampled max 196776 kB, RSS before 56408 kB)
05h-records full rebuild cube100_lowalpha0.05_s0.3   96000 Hz: min 1951 median 1976 max 2034 ms; transient RSS delta 298 MB (sampled max 356156 kB, RSS before 51480 kB)
05h-records work ratio cube100_lowalpha0.05_s0.3  e0: realised work / W_scene 0.9910 (W_pilot 1696086, W_final 4348889, W_scene 6100000); achieved SE 0.092 dB; fallback no
05h-records work ratio cube100_lowalpha0.05_s0.3  e1: realised work / W_scene 0.9910 (W_pilot 1696086, W_final 4348889, W_scene 6100000); achieved SE 0.075 dB; fallback no
05h-records work pin cube100_lowalpha0.05_s0.3  unit decay 1152000 samples (pinned 1152000); synthesis FFT size 2097152, generator 2097152 (pinned 2097152)
05h-records solve cube100_lowalpha0.05_s0.3  shipping rule, median of 5: 82.5 ms; 6.83 ns per image evaluation over W_pilot + W_final 12089950 (print, RG-1)
05h-records restore cube100_lowalpha0.05_s0.3  96 kHz with the solve, 10 runs: min 1828 median 1902 worst 2058 ms; 14 x worst 28.82 s (30 s)
05h-records restore gate cube100_lowalpha0.05_s0.3  Linux: register entry closed, hosted-runner form (recorded 14 x worst 30.27 s); 14 x worst now 28.82 s; passes 30 s (register entry closed under AX38 4c (c)); growth bound asserted in-window after the scene loop (RG-1)
05h-records restore cube100_lowalpha0.05_s0.3  96 kHz contended (another pipeline solving the same room): min 1931 median 2012 worst 2077 ms (3 runs)
05h-records full rebuild cube100_lowalpha0.05_s1     48000 Hz: min 776 median 786 max 791 ms; transient RSS delta 137 MB (sampled max 196776 kB, RSS before 56408 kB)
05h-records full rebuild cube100_lowalpha0.05_s1     96000 Hz: min 1884 median 1917 max 1928 ms; transient RSS delta 298 MB (sampled max 356156 kB, RSS before 51480 kB)
05h-records work ratio cube100_lowalpha0.05_s1    e0: realised work / W_scene 0.9859 (W_pilot 1666253, W_final 4347497, W_scene 6100000); achieved SE 0.360 dB; fallback no
05h-records work ratio cube100_lowalpha0.05_s1    e1: realised work / W_scene 0.9859 (W_pilot 1666253, W_final 4347497, W_scene 6100000); achieved SE 0.359 dB; fallback no
05h-records restore cube100_lowalpha0.05_s1    96 kHz with the solve, 10 runs: min 1760 median 1861 worst 2000 ms; 14 x worst 28.00 s (30 s)
05h-records restore gate cube100_lowalpha0.05_s1    Linux: reported set, not gated
05h-records restore cube100_lowalpha0.05_s1    96 kHz contended (another pipeline solving the same room): min 1925 median 2008 worst 2072 ms (3 runs)
05h-records GATE os=Linux scene=cube100_flutter_fallback x14worst=8.96 median=599 fullRebuildMedian=643 solveMedianMs=131.3 solveWarnAt=157.4 solveBasis=PROVISIONAL(n=1) nsPerEval=11.52 status=asserted(30s) flutterRef=701 flutterDev=-14.5% warnings=
05h-records GATE os=Linux scene=cube100_lowalpha0.05_s0.3 ratio=3.174 ratioWarnAt=3.660 solveMedianMs=82.5 solveWarnAt=97.1 solveBasis=PROVISIONAL(n=1) nsPerEval=6.83 x14worst=28.82 median=1902 growthBound=2275 fullRebuildMedian=1976 status=not-evaluated(runner,flutter-14.5%) trigger=0 warnings=PASSES30S 
05i-records (iv) offline AQ10 room                   48000 Hz, 1 offline instance in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 144 median 146 worst 152 ms; first build (after restore) worst 173 ms; wall 761 ms
05i-records (iv) offline AQ10 room                   48000 Hz, 4 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 240 median 252 worst 267 ms; first build (after restore) worst 311 ms; wall 1307 ms
05i-records (iv) offline AQ10 room                   48000 Hz, 8 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 199 median 489 worst 805 ms; first build (after restore) worst 663 ms; wall 2725 ms
05i-records (iv) offline AQ10 room                   96000 Hz, 1 offline instance in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 304 median 327 worst 334 ms; first build (after restore) worst 352 ms; wall 1644 ms
05i-records (iv) offline AQ10 room                   96000 Hz, 4 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 567 median 608 worst 637 ms; first build (after restore) worst 656 ms; wall 3067 ms
05i-records (iv) offline AQ10 room                   96000 Hz, 8 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 436 median 1190 worst 1722 ms; first build (after restore) worst 1515 ms; wall 6580 ms
05i-records (iv) offline cube100_lowalpha0.05_s0.3   48000 Hz, 1 offline instance in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 754 median 777 worst 815 ms; first build (after restore) worst 800 ms; wall 3922 ms
05i-records (iv) offline cube100_lowalpha0.05_s0.3   48000 Hz, 4 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 1075 median 1517 worst 1880 ms; first build (after restore) worst 1968 ms; wall 8274 ms
05i-records (iv) offline cube100_lowalpha0.05_s0.3   48000 Hz, 8 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 1577 median 3174 worst 3945 ms; first build (after restore) worst 4556 ms; wall 16527 ms
05i-records (iv) offline cube100_lowalpha0.05_s0.3   96000 Hz, 1 offline instance in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 1852 median 1969 worst 2092 ms; first build (after restore) worst 1937 ms; wall 9819 ms
05i-records (iv) offline cube100_lowalpha0.05_s0.3   96000 Hz, 4 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 3099 median 3287 worst 3486 ms; first build (after restore) worst 3753 ms; wall 16780 ms
05i-records (iv) offline cube100_lowalpha0.05_s0.3   96000 Hz, 8 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 3956 median 6593 worst 7981 ms; first build (after restore) worst 8279 ms; wall 34019 ms
05i-records K-e12 os=Linux cube100_flutter_fallback   96 kHz: restore with a room edit in flight (room size -1/-2 m in w/d/h, restore of a new room size at a random point of the 662 ms rebuild), 10 runs: min 604 median 635 worst 648 ms; builder busy at the restore in 10 of 10 runs, worst over those 648 ms (idle restore of a new state median 596 ms, 3 runs); per-restore budget 2143 ms: within
05i-records K-e12 os=Linux cube100_flutter_fallback   run  0: restore at 178 ms of 662 (builder busy: yes) -> host thread 647 ms
05i-records K-e12 os=Linux cube100_flutter_fallback   run  1: restore at 654 ms of 662 (builder busy: yes) -> host thread 638 ms
05i-records K-e12 os=Linux cube100_flutter_fallback   run  2: restore at 62 ms of 662 (builder busy: yes) -> host thread 633 ms
05i-records K-e12 os=Linux cube100_flutter_fallback   run  3: restore at 519 ms of 662 (builder busy: yes) -> host thread 648 ms
05i-records K-e12 os=Linux cube100_flutter_fallback   run  4: restore at 321 ms of 662 (builder busy: yes) -> host thread 629 ms
05i-records K-e12 os=Linux cube100_flutter_fallback   run  5: restore at 352 ms of 662 (builder busy: yes) -> host thread 624 ms
05i-records K-e12 os=Linux cube100_flutter_fallback   run  6: restore at 186 ms of 662 (builder busy: yes) -> host thread 623 ms
05i-records K-e12 os=Linux cube100_flutter_fallback   run  7: restore at 150 ms of 662 (builder busy: yes) -> host thread 647 ms
05i-records K-e12 os=Linux cube100_flutter_fallback   run  8: restore at 244 ms of 662 (builder busy: yes) -> host thread 604 ms
05i-records K-e12 os=Linux cube100_flutter_fallback   run  9: restore at 53 ms of 662 (builder busy: yes) -> host thread 647 ms
05i-records K-e12 os=Linux cube100_lowalpha0.05_s0.3  96 kHz: restore with a room edit in flight (room size -1/-2 m in w/d/h, restore of a new room size at a random point of the 1906 ms rebuild), 10 runs: min 1791 median 1851 worst 2062 ms; builder busy at the restore in 9 of 10 runs, worst over those 2062 ms (idle restore of a new state median 1754 ms, 3 runs); per-restore budget 2143 ms: within
05i-records K-e12 os=Linux cube100_lowalpha0.05_s0.3  run  0: restore at 1429 ms of 1906 (builder busy: yes) -> host thread 2059 ms
05i-records K-e12 os=Linux cube100_lowalpha0.05_s0.3  run  1: restore at 156 ms of 1906 (builder busy: yes) -> host thread 1791 ms
05i-records K-e12 os=Linux cube100_lowalpha0.05_s0.3  run  2: restore at 1800 ms of 1906 (builder busy: yes) -> host thread 1857 ms
05i-records K-e12 os=Linux cube100_lowalpha0.05_s0.3  run  3: restore at 1847 ms of 1906 (builder busy: no) -> host thread 1839 ms
05i-records K-e12 os=Linux cube100_lowalpha0.05_s0.3  run  4: restore at 1330 ms of 1906 (builder busy: yes) -> host thread 1822 ms
05i-records K-e12 os=Linux cube100_lowalpha0.05_s0.3  run  5: restore at 210 ms of 1906 (builder busy: yes) -> host thread 1925 ms
05i-records K-e12 os=Linux cube100_lowalpha0.05_s0.3  run  6: restore at 757 ms of 1906 (builder busy: yes) -> host thread 1845 ms
05i-records K-e12 os=Linux cube100_lowalpha0.05_s0.3  run  7: restore at 1379 ms of 1906 (builder busy: yes) -> host thread 1941 ms
05i-records K-e12 os=Linux cube100_lowalpha0.05_s0.3  run  8: restore at 991 ms of 1906 (builder busy: yes) -> host thread 1828 ms
05i-records K-e12 os=Linux cube100_lowalpha0.05_s0.3  run  9: restore at 559 ms of 1906 (builder busy: yes) -> host thread 2062 ms
05i-records (iv) AQ10 room                   48000 Hz, 1 inst: load until the last is audible 433 ms (prepare's default-scene build + restore, per instance); per instance (load order) prepare [282] ms, restore [150] ms
05i-records (iv) AQ10 room                   48000 Hz, 1 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 166 median 166 max 166 ms
05i-records (iv) AQ10 room                   48000 Hz, 1 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 153 median 153 max 153 ms
05i-records (iv) AQ10 room                   48000 Hz, 1 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 176 median 176 max 176 ms
05i-records (iv) gate-wait AQ10 room                   48000 Hz, 1 inst, prepare: host call 165 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 165 ms; max queue over 3 runs 0 ms; gate turns completed during the call 1; polls 155, max poll gap 1.1 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait AQ10 room                   48000 Hz, 1 inst, restore: host call 162 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 162 ms; max queue over 3 runs 0 ms; gate turns completed during the call 1; polls 151, max poll gap 1.7 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait AQ10 room                   48000 Hz, 1 inst, offline switch + first block: host call 139 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 139 ms; max queue over 3 runs 0 ms; gate turns completed during the call 1; polls 131, max poll gap 1.4 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) AQ10 room                   48000 Hz, 1 inst: worst host-thread wait of one instance while 0 others rebuild without pause (0: uncontended baseline; room size stepping 1 m every 50 ms), 3 runs: prepare 165 ms, restore 162 ms, offline switch + first block after a room-size edit 139 ms
05i-records (iv) AQ10 room                   48000 Hz, 4 inst: load until the last is audible 1739 ms (prepare's default-scene build + restore, per instance); per instance (load order) prepare [291 276 276 282] ms, restore [150 155 156 154] ms
05i-records (iv) AQ10 room                   48000 Hz, 4 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 246 median 264 max 296 ms
05i-records (iv) AQ10 room                   48000 Hz, 4 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 231 median 263 max 294 ms
05i-records (iv) AQ10 room                   48000 Hz, 4 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 325 median 386 max 411 ms
05i-records (iv) gate-wait AQ10 room                   48000 Hz, 4 inst, prepare: host call 264 ms = queue(Synchronous) 10 ms + queue(Offline) 0 ms + remainder 255 ms; max queue over 3 runs 10 ms; gate turns completed during the call 4; polls 234, max poll gap 5.5 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait AQ10 room                   48000 Hz, 4 inst, restore: host call 264 ms = queue(Synchronous) 15 ms + queue(Offline) 0 ms + remainder 249 ms; max queue over 3 runs 15 ms; gate turns completed during the call 4; polls 239, max poll gap 3.8 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait AQ10 room                   48000 Hz, 4 inst, offline switch + first block: host call 267 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 267 ms; max queue over 3 runs 13 ms; gate turns completed during the call 5; polls 242, max poll gap 4.0 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) AQ10 room                   48000 Hz, 4 inst: worst host-thread wait of one instance while 3 others rebuild without pause (0: uncontended baseline; room size stepping 1 m every 50 ms), 3 runs: prepare 264 ms, restore 264 ms, offline switch + first block after a room-size edit 267 ms
05i-records (iv) AQ10 room                   48000 Hz, 8 inst: load until the last is audible 3476 ms (prepare's default-scene build + restore, per instance); per instance (load order) prepare [294 282 278 281 283 275 277 275] ms, restore [151 155 152 155 156 151 157 153] ms
05i-records (iv) AQ10 room                   48000 Hz, 8 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 267 median 498 max 561 ms
05i-records (iv) AQ10 room                   48000 Hz, 8 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 427 median 501 max 579 ms
05i-records (iv) AQ10 room                   48000 Hz, 8 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 4 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 349 median 644 max 714 ms
05i-records (iv) gate-wait AQ10 room                   48000 Hz, 8 inst, prepare: host call 606 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 606 ms; max queue over 3 runs 62 ms; gate turns completed during the call 7; polls 557, max poll gap 4.0 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait AQ10 room                   48000 Hz, 8 inst, restore: host call 684 ms = queue(Synchronous) 18 ms + queue(Offline) 0 ms + remainder 666 ms; max queue over 3 runs 19 ms; gate turns completed during the call 11; polls 626, max poll gap 4.1 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait AQ10 room                   48000 Hz, 8 inst, offline switch + first block: host call 553 ms = queue(Synchronous) 0 ms + queue(Offline) 37 ms + remainder 516 ms; max queue over 3 runs 37 ms; gate turns completed during the call 7; polls 507, max poll gap 3.1 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) AQ10 room                   48000 Hz, 8 inst: worst host-thread wait of one instance while 7 others rebuild without pause (0: uncontended baseline; room size stepping 1 m every 50 ms), 3 runs: prepare 606 ms, restore 684 ms, offline switch + first block after a room-size edit 553 ms
05i-records (iv) AQ10 room                   96000 Hz, 1 inst: load until the last is audible 809 ms (prepare's default-scene build + restore, per instance); per instance (load order) prepare [480] ms, restore [330] ms
05i-records (iv) AQ10 room                   96000 Hz, 1 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 359 median 359 max 359 ms
05i-records (iv) AQ10 room                   96000 Hz, 1 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 336 median 336 max 336 ms
05i-records (iv) AQ10 room                   96000 Hz, 1 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 355 median 355 max 355 ms
05i-records (iv) gate-wait AQ10 room                   96000 Hz, 1 inst, prepare: host call 330 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 330 ms; max queue over 3 runs 0 ms; gate turns completed during the call 1; polls 311, max poll gap 1.2 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait AQ10 room                   96000 Hz, 1 inst, restore: host call 381 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 381 ms; max queue over 3 runs 0 ms; gate turns completed during the call 1; polls 354, max poll gap 1.4 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait AQ10 room                   96000 Hz, 1 inst, offline switch + first block: host call 328 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 328 ms; max queue over 3 runs 0 ms; gate turns completed during the call 1; polls 308, max poll gap 1.6 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) AQ10 room                   96000 Hz, 1 inst: worst host-thread wait of one instance while 0 others rebuild without pause (0: uncontended baseline; room size stepping 1 m every 50 ms), 3 runs: prepare 330 ms, restore 381 ms, offline switch + first block after a room-size edit 328 ms
05i-records (iv) AQ10 room                   96000 Hz, 4 inst: load until the last is audible 3265 ms (prepare's default-scene build + restore, per instance); per instance (load order) prepare [486 475 468 470] ms, restore [330 343 346 347] ms
05i-records (iv) AQ10 room                   96000 Hz, 4 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 585 median 619 max 634 ms
05i-records (iv) AQ10 room                   96000 Hz, 4 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 551 median 591 max 622 ms
05i-records (iv) AQ10 room                   96000 Hz, 4 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 696 median 745 max 775 ms
05i-records (iv) gate-wait AQ10 room                   96000 Hz, 4 inst, prepare: host call 590 ms = queue(Synchronous) 1 ms + queue(Offline) 0 ms + remainder 588 ms; max queue over 3 runs 10 ms; gate turns completed during the call 4; polls 536, max poll gap 4.0 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait AQ10 room                   96000 Hz, 4 inst, restore: host call 613 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 613 ms; max queue over 3 runs 18 ms; gate turns completed during the call 4; polls 563, max poll gap 4.3 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait AQ10 room                   96000 Hz, 4 inst, offline switch + first block: host call 583 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 583 ms; max queue over 3 runs 1 ms; gate turns completed during the call 4; polls 543, max poll gap 2.0 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) AQ10 room                   96000 Hz, 4 inst: worst host-thread wait of one instance while 3 others rebuild without pause (0: uncontended baseline; room size stepping 1 m every 50 ms), 3 runs: prepare 590 ms, restore 613 ms, offline switch + first block after a room-size edit 583 ms
05i-records (iv) AQ10 room                   96000 Hz, 8 inst: load until the last is audible 6501 ms (prepare's default-scene build + restore, per instance); per instance (load order) prepare [496 463 467 470 463 464 466 474] ms, restore [338 342 343 342 343 341 344 345] ms
05i-records (iv) AQ10 room                   96000 Hz, 8 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 1073 median 1290 max 1379 ms
05i-records (iv) AQ10 room                   96000 Hz, 8 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 1100 median 1277 max 1379 ms
05i-records (iv) AQ10 room                   96000 Hz, 8 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 1252 median 1476 max 1628 ms
05i-records (iv) gate-wait AQ10 room                   96000 Hz, 8 inst, prepare: host call 1272 ms = queue(Synchronous) 26 ms + queue(Offline) 0 ms + remainder 1246 ms; max queue over 3 runs 26 ms; gate turns completed during the call 10; polls 1148, max poll gap 11.7 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait AQ10 room                   96000 Hz, 8 inst, restore: host call 1481 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 1481 ms; max queue over 3 runs 0 ms; gate turns completed during the call 9; polls 1384, max poll gap 4.0 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait AQ10 room                   96000 Hz, 8 inst, offline switch + first block: host call 1518 ms = queue(Synchronous) 0 ms + queue(Offline) 42 ms + remainder 1476 ms; max queue over 3 runs 42 ms; gate turns completed during the call 8; polls 1404, max poll gap 5.0 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) AQ10 room                   96000 Hz, 8 inst: worst host-thread wait of one instance while 7 others rebuild without pause (0: uncontended baseline; room size stepping 1 m every 50 ms), 3 runs: prepare 1272 ms, restore 1481 ms, offline switch + first block after a room-size edit 1518 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst: load until the last is audible 1044 ms (prepare's default-scene build + restore, per instance); per instance (load order) prepare [289] ms, restore [755] ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 760 median 760 max 760 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 798 median 798 max 798 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 975 median 975 max 975 ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst, prepare: host call 772 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 772 ms; max queue over 3 runs 0 ms; gate turns completed during the call 1; polls 722, max poll gap 3.0 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst, restore: host call 790 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 790 ms; max queue over 3 runs 0 ms; gate turns completed during the call 1; polls 740, max poll gap 3.4 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst, offline switch + first block: host call 744 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 744 ms; max queue over 3 runs 0 ms; gate turns completed during the call 1; polls 693, max poll gap 3.8 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst: worst host-thread wait of one instance while 0 others rebuild without pause (0: uncontended baseline; room size stepping 1 m every 50 ms), 3 runs: prepare 772 ms, restore 790 ms, offline switch + first block after a room-size edit 744 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst: load until the last is audible 4170 ms (prepare's default-scene build + restore, per instance); per instance (load order) prepare [293 272 270 272] ms, restore [767 755 756 785] ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 1368 median 1591 max 1736 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 1388 median 1527 max 1720 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 1530 median 1885 max 2125 ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst, prepare: host call 1510 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 1510 ms; max queue over 3 runs 78 ms; gate turns completed during the call 4; polls 1399, max poll gap 5.5 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst, restore: host call 1687 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 1687 ms; max queue over 3 runs 7 ms; gate turns completed during the call 4; polls 1563, max poll gap 5.8 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst, offline switch + first block: host call 1554 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 1554 ms; max queue over 3 runs 0 ms; gate turns completed during the call 5; polls 1412, max poll gap 6.3 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst: worst host-thread wait of one instance while 3 others rebuild without pause (0: uncontended baseline; room size stepping 1 m every 50 ms), 3 runs: prepare 1510 ms, restore 1687 ms, offline switch + first block after a room-size edit 1554 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst: load until the last is audible 8614 ms (prepare's default-scene build + restore, per instance); per instance (load order) prepare [293 270 300 272 277 282 276 272] ms, restore [808 826 788 775 802 803 779 791] ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 2411 median 2994 max 3326 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 1576 median 2973 max 3339 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 2167 median 3646 max 3934 ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst, prepare: host call 3207 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 3207 ms; max queue over 3 runs 31 ms; gate turns completed during the call 9; polls 2988, max poll gap 4.0 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst, restore: host call 3235 ms = queue(Synchronous) 109 ms + queue(Offline) 0 ms + remainder 3126 ms; max queue over 3 runs 109 ms; gate turns completed during the call 9; polls 2973, max poll gap 4.3 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst, offline switch + first block: host call 3367 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 3367 ms; max queue over 3 runs 27 ms; gate turns completed during the call 8; polls 3128, max poll gap 4.0 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst: worst host-thread wait of one instance while 7 others rebuild without pause (0: uncontended baseline; room size stepping 1 m every 50 ms), 3 runs: prepare 3207 ms, restore 3235 ms, offline switch + first block after a room-size edit 3367 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst: load until the last is audible 2373 ms (prepare's default-scene build + restore, per instance); per instance (load order) prepare [444] ms, restore [1929] ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 2121 median 2121 max 2121 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 1907 median 1907 max 1907 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 2 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 2081 median 2081 max 2081 ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst, prepare: host call 1883 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 1883 ms; max queue over 3 runs 0 ms; gate turns completed during the call 1; polls 1767, max poll gap 3.8 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst, restore: host call 1843 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 1843 ms; max queue over 3 runs 0 ms; gate turns completed during the call 1; polls 1729, max poll gap 3.2 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst, offline switch + first block: host call 1899 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 1899 ms; max queue over 3 runs 0 ms; gate turns completed during the call 1; polls 1782, max poll gap 2.6 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst: worst host-thread wait of one instance while 0 others rebuild without pause (0: uncontended baseline; room size stepping 1 m every 50 ms), 3 runs: prepare 1883 ms, restore 1843 ms, offline switch + first block after a room-size edit 1899 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst: load until the last is audible 9323 ms (prepare's default-scene build + restore, per instance); per instance (load order) prepare [453 439 447 453] ms, restore [1871 1903 1845 1913] ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 3262 median 3289 max 3435 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 3255 median 3266 max 3505 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 3649 median 4125 max 4319 ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst, prepare: host call 3146 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 3146 ms; max queue over 3 runs 84 ms; gate turns completed during the call 4; polls 2904, max poll gap 6.0 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst, restore: host call 3247 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 3247 ms; max queue over 3 runs 0 ms; gate turns completed during the call 4; polls 3014, max poll gap 4.4 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst, offline switch + first block: host call 3391 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 3391 ms; max queue over 3 runs 0 ms; gate turns completed during the call 4; polls 3162, max poll gap 6.1 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst: worst host-thread wait of one instance while 3 others rebuild without pause (0: uncontended baseline; room size stepping 1 m every 50 ms), 3 runs: prepare 3146 ms, restore 3247 ms, offline switch + first block after a room-size edit 3391 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst: load until the last is audible 19635 ms (prepare's default-scene build + restore, per instance); per instance (load order) prepare [460 444 447 454 481 472 483 446] ms, restore [1997 1947 1904 1958 2097 2017 2052 1975] ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 5893 median 6812 max 6900 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 5059 median 6568 max 6851 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 6346 median 7516 max 7954 ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst, prepare: host call 6882 ms = queue(Synchronous) 91 ms + queue(Offline) 0 ms + remainder 6791 ms; max queue over 3 runs 153 ms; gate turns completed during the call 8; polls 6397, max poll gap 4.0 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst, restore: host call 7163 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 7163 ms; max queue over 3 runs 0 ms; gate turns completed during the call 9; polls 6664, max poll gap 4.9 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst, offline switch + first block: host call 7007 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 7007 ms; max queue over 3 runs 0 ms; gate turns completed during the call 9; polls 6496, max poll gap 4.4 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst: worst host-thread wait of one instance while 7 others rebuild without pause (0: uncontended baseline; room size stepping 1 m every 50 ms), 3 runs: prepare 6882 ms, restore 7163 ms, offline switch + first block after a room-size edit 7007 ms
05h-records quiesce cube100_flutter_fallback   96 kHz: builder rebuild 662 ms; cancel at a random point, 10 runs: wait min 0 median 22 worst 62 ms
05h-records quiesce cube100_flutter_fallback   run  0: cancel at 134 ms of 662 -> waited 46 ms
05h-records quiesce cube100_flutter_fallback   run  1: cancel at 148 ms of 662 -> waited 32 ms
05h-records quiesce cube100_flutter_fallback   run  2: cancel at 593 ms of 662 -> waited 3 ms
05h-records quiesce cube100_flutter_fallback   run  3: cancel at 260 ms of 662 -> waited 9 ms
05h-records quiesce cube100_flutter_fallback   run  4: cancel at 189 ms of 662 -> waited 36 ms
05h-records quiesce cube100_flutter_fallback   run  5: cancel at 117 ms of 662 -> waited 62 ms
05h-records quiesce cube100_flutter_fallback   run  6: cancel at 182 ms of 662 -> waited 1 ms
05h-records quiesce cube100_flutter_fallback   run  7: cancel at 376 ms of 662 -> waited 0 ms
05h-records quiesce cube100_flutter_fallback   run  8: cancel at 268 ms of 662 -> waited 39 ms
05h-records quiesce cube100_flutter_fallback   run  9: cancel at 422 ms of 662 -> waited 12 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  96 kHz: builder rebuild 2059 ms; cancel at a random point, 10 runs: wait min 0 median 52 worst 130 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  0: cancel at 1596 ms of 2059 -> waited 66 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  1: cancel at 2032 ms of 2059 -> waited 0 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  2: cancel at 1813 ms of 2059 -> waited 51 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  3: cancel at 1308 ms of 2059 -> waited 21 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  4: cancel at 1979 ms of 2059 -> waited 0 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  5: cancel at 629 ms of 2059 -> waited 54 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  6: cancel at 571 ms of 2059 -> waited 130 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  7: cancel at 235 ms of 2059 -> waited 98 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  8: cancel at 2048 ms of 2059 -> waited 0 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  9: cancel at 757 ms of 2059 -> waited 72 ms
07c1-records provisional cost  48000 Hz, T60  2.0 s: full tail 3.00 s -> 74 ms; prefix L_p 0.72 s -> 15 ms (one emitter: constructor + make)
07c1-records provisional cost  48000 Hz, T60  8.0 s: full tail 12.00 s -> 430 ms; prefix L_p 2.58 s -> 81 ms (one emitter: constructor + make)
07c1-records provisional cost  48000 Hz, T60 12.0 s: full tail 12.00 s -> 418 ms; prefix L_p 3.82 s -> 87 ms (one emitter: constructor + make)
07c1-records provisional cost  96000 Hz, T60  2.0 s: full tail 3.00 s -> 167 ms; prefix L_p 0.72 s -> 39 ms (one emitter: constructor + make)
07c1-records provisional cost  96000 Hz, T60  8.0 s: full tail 12.00 s -> 1098 ms; prefix L_p 2.58 s -> 172 ms (one emitter: constructor + make)
07c1-records provisional cost  96000 Hz, T60 12.0 s: full tail 12.00 s -> 1114 ms; prefix L_p 3.82 s -> 185 ms (one emitter: constructor + make)
07c1-records cond12 cube100_lowalpha0.05_s0.3   48000 Hz, Linux, 1 concurrent build: all rebuilt in 942 ms; (f) process peak RSS delta 155 MB (RSS before 133728 kB); (d) worst quiesce wait 23 ms (3 cancels at random points)
07c1-records cond12 cube100_lowalpha0.05_s0.3   48000 Hz, Linux, 4 concurrent builds: all rebuilt in 1762 ms; (f) process peak RSS delta 572 MB (RSS before 243168 kB); (d) worst quiesce wait 101 ms (3 cancels at random points)
07c1-records cond12 cube100_lowalpha0.05_s0.3   48000 Hz, Linux, 8 concurrent builds: all rebuilt in 3540 ms; (f) process peak RSS delta 1115 MB (RSS before 391692 kB); (d) worst quiesce wait 108 ms (3 cancels at random points)
07c1-records cond12 cube100_lowalpha0.05_s0.3   96000 Hz, Linux, 1 concurrent build: all rebuilt in 2176 ms; (f) process peak RSS delta 311 MB (RSS before 167076 kB); (d) worst quiesce wait 71 ms (3 cancels at random points)
07c1-records cond12 cube100_lowalpha0.05_s0.3   96000 Hz, Linux, 4 concurrent builds: all rebuilt in 3606 ms; (f) process peak RSS delta 1155 MB (RSS before 488884 kB); (d) worst quiesce wait 6 ms (3 cancels at random points)
07c1-records cond12 cube100_lowalpha0.05_s0.3   96000 Hz, Linux, 8 concurrent builds: all rebuilt in 7343 ms; (f) process peak RSS delta 2006 MB (RSS before 955648 kB); (d) worst quiesce wait 160 ms (3 cancels at random points)
All tests passed (15917 assertions in 19 test cases)
All tests passed (6 assertions in 1 test case)
[36;1mtools/ci/run_pluginval.sh --output-dir build/pluginval-logs "${PLUGINS[@]}"[0m
Downloading pluginval v1.0.4: https://github.com/Tracktion/pluginval/releases/download/v1.0.4/pluginval_Linux.zip
pluginval - 1.0.4
##[group]pluginval build/release/SpatialScene_artefacts/Release/VST3/SpatialScene.vst3
pluginval --strictness-level 10 --timeout-ms 120000 --output-dir build/pluginval-logs build/release/SpatialScene_artefacts/Release/VST3/SpatialScene.vst3
Starting tests in: pluginval / Scan for plugins located in: /home/runner/work/makroof/makroof/build/release/SpatialScene_artefacts/Release/VST3/SpatialScene.vst3...
Completed tests in pluginval / Scan for plugins located in: /home/runner/work/makroof/makroof/build/release/SpatialScene_artefacts/Release/VST3/SpatialScene.vst3
Starting tests in: pluginval / Open plugin (cold)...
Completed tests in pluginval / Open plugin (cold)
Starting tests in: pluginval / Open plugin (warm)...
Completed tests in pluginval / Open plugin (warm)
Starting tests in: pluginval / Plugin info...
Completed tests in pluginval / Plugin info
Starting tests in: pluginval / Plugin programs...
Completed tests in pluginval / Plugin programs
Starting tests in: pluginval / Editor...
Completed tests in pluginval / Editor
Starting tests in: pluginval / Open editor whilst processing...
Completed tests in pluginval / Open editor whilst processing
Starting tests in: pluginval / Audio processing...
Completed tests in pluginval / Audio processing
Starting tests in: pluginval / Non-releasing audio processing...
Completed tests in pluginval / Non-releasing audio processing
Starting tests in: pluginval / Plugin state...
Completed tests in pluginval / Plugin state
Starting tests in: pluginval / Plugin state restoration...
Completed tests in pluginval / Plugin state restoration
Starting tests in: pluginval / Automation...
Completed tests in pluginval / Automation
Starting tests in: pluginval / Editor Automation...
Completed tests in pluginval / Editor Automation
Starting tests in: pluginval / Automatable Parameters...
Completed tests in pluginval / Automatable Parameters
Starting tests in: pluginval / Parameters...
Completed tests in pluginval / Parameters
Starting tests in: pluginval / Background thread state...
Completed tests in pluginval / Background thread state
Starting tests in: pluginval / Parameter thread safety...
Completed tests in pluginval / Parameter thread safety
Starting tests in: pluginval / auval...
Completed tests in pluginval / auval
Starting tests in: pluginval / vst3 validator...
Completed tests in pluginval / vst3 validator
Starting tests in: pluginval / Basic bus...
Completed tests in pluginval / Basic bus
Starting tests in: pluginval / Listing available buses...
Completed tests in pluginval / Listing available buses
Starting tests in: pluginval / Enabling all buses...
Completed tests in pluginval / Enabling all buses
Starting tests in: pluginval / Disabling non-main busses...
Completed tests in pluginval / Disabling non-main busses
Starting tests in: pluginval / Restoring default layout...
Completed tests in pluginval / Restoring default layout
Starting tests in: pluginval / Fuzz parameters...
Completed tests in pluginval / Fuzz parameters
pluginval logs: build/pluginval-logs
  name: pluginval-linux
  path: build/pluginval-logs

Uploading artifact: pluginval-linux.zip
Artifact pluginval-linux successfully finalized. Artifact ID 13946367586
Artifact pluginval-linux has been successfully uploaded! Final size is 1254 bytes. Artifact ID is 13946367586
```

### macOS (job log, run 43215018040, commit 517e556)

```
100% tests passed out of 231
07c1-records provisional cost  48000 Hz, T60  2.0 s: full tail 3.00 s -> 67 ms; prefix L_p 0.72 s -> 12 ms (one emitter: constructor + make)
07c1-records provisional cost  48000 Hz, T60  8.0 s: full tail 12.00 s -> 401 ms; prefix L_p 2.58 s -> 71 ms (one emitter: constructor + make)
07c1-records provisional cost  48000 Hz, T60 12.0 s: full tail 12.00 s -> 444 ms; prefix L_p 3.82 s -> 65 ms (one emitter: constructor + make)
07c1-records provisional cost  96000 Hz, T60  2.0 s: full tail 3.00 s -> 142 ms; prefix L_p 0.72 s -> 28 ms (one emitter: constructor + make)
07c1-records provisional cost  96000 Hz, T60  8.0 s: full tail 12.00 s -> 1166 ms; prefix L_p 2.58 s -> 148 ms (one emitter: constructor + make)
07c1-records provisional cost  96000 Hz, T60 12.0 s: full tail 12.00 s -> 1257 ms; prefix L_p 3.82 s -> 182 ms (one emitter: constructor + make)
05i-records (iv) AQ10 room                   48000 Hz, 1 inst: load until the last is audible 463 ms (prepare's default-scene build + restore, per instance); per instance (load order) prepare [292] ms, restore [171] ms
05i-records (iv) AQ10 room                   48000 Hz, 1 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 145 median 145 max 145 ms
05i-records (iv) AQ10 room                   48000 Hz, 1 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 153 median 153 max 153 ms
05i-records (iv) AQ10 room                   48000 Hz, 1 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 167 median 167 max 167 ms
05i-records (iv) gate-wait AQ10 room                   48000 Hz, 1 inst, prepare: host call 136 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 136 ms; max queue over 3 runs 0 ms; gate turns completed during the call 1; polls 12, max poll gap 13.6 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait AQ10 room                   48000 Hz, 1 inst, restore: host call 159 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 159 ms; max queue over 3 runs 0 ms; gate turns completed during the call 1; polls 17, max poll gap 13.6 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait AQ10 room                   48000 Hz, 1 inst, offline switch + first block: host call 128 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 128 ms; max queue over 3 runs 0 ms; gate turns completed during the call 1; polls 12, max poll gap 13.6 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) AQ10 room                   48000 Hz, 1 inst: worst host-thread wait of one instance while 0 others rebuild without pause (0: uncontended baseline; room size stepping 1 m every 50 ms), 3 runs: prepare 136 ms, restore 159 ms, offline switch + first block after a room-size edit 128 ms
05i-records (iv) AQ10 room                   48000 Hz, 4 inst: load until the last is audible 1693 ms (prepare's default-scene build + restore, per instance); per instance (load order) prepare [253 285 285 273] ms, restore [129 146 160 161] ms
05i-records (iv) AQ10 room                   48000 Hz, 4 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 245 median 262 max 278 ms
05i-records (iv) AQ10 room                   48000 Hz, 4 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 282 median 296 max 331 ms
05i-records (iv) AQ10 room                   48000 Hz, 4 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 293 median 330 max 350 ms
05i-records (iv) gate-wait AQ10 room                   48000 Hz, 4 inst, prepare: host call 428 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 428 ms; max queue over 3 runs 0 ms; gate turns completed during the call 4; polls 59, max poll gap 13.8 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait AQ10 room                   48000 Hz, 4 inst, restore: host call 427 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 427 ms; max queue over 3 runs 0 ms; gate turns completed during the call 4; polls 51, max poll gap 19.1 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait AQ10 room                   48000 Hz, 4 inst, offline switch + first block: host call 437 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 437 ms; max queue over 3 runs 0 ms; gate turns completed during the call 4; polls 51, max poll gap 22.9 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) AQ10 room                   48000 Hz, 4 inst: worst host-thread wait of one instance while 3 others rebuild without pause (0: uncontended baseline; room size stepping 1 m every 50 ms), 3 runs: prepare 428 ms, restore 427 ms, offline switch + first block after a room-size edit 437 ms
05i-records (iv) AQ10 room                   48000 Hz, 8 inst: load until the last is audible 3699 ms (prepare's default-scene build + restore, per instance); per instance (load order) prepare [297 259 272 271 290 384 322 338] ms, restore [160 137 136 142 184 175 197 136] ms
05i-records (iv) AQ10 room                   48000 Hz, 8 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 556 median 605 max 629 ms
05i-records (iv) AQ10 room                   48000 Hz, 8 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 506 median 596 max 615 ms
05i-records (iv) AQ10 room                   48000 Hz, 8 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 535 median 642 max 687 ms
05i-records (iv) gate-wait AQ10 room                   48000 Hz, 8 inst, prepare: host call 555 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 555 ms; max queue over 3 runs 0 ms; gate turns completed during the call 8; polls 69, max poll gap 10.2 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait AQ10 room                   48000 Hz, 8 inst, restore: host call 637 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 637 ms; max queue over 3 runs 0 ms; gate turns completed during the call 8; polls 82, max poll gap 16.1 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait AQ10 room                   48000 Hz, 8 inst, offline switch + first block: host call 516 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 516 ms; max queue over 3 runs 0 ms; gate turns completed during the call 8; polls 64, max poll gap 9.4 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) AQ10 room                   48000 Hz, 8 inst: worst host-thread wait of one instance while 7 others rebuild without pause (0: uncontended baseline; room size stepping 1 m every 50 ms), 3 runs: prepare 555 ms, restore 637 ms, offline switch + first block after a room-size edit 516 ms
05i-records (iv) AQ10 room                   96000 Hz, 1 inst: load until the last is audible 769 ms (prepare's default-scene build + restore, per instance); per instance (load order) prepare [445] ms, restore [323] ms
05i-records (iv) AQ10 room                   96000 Hz, 1 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 297 median 297 max 297 ms
05i-records (iv) AQ10 room                   96000 Hz, 1 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 299 median 299 max 299 ms
05i-records (iv) AQ10 room                   96000 Hz, 1 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 384 median 384 max 384 ms
05i-records (iv) gate-wait AQ10 room                   96000 Hz, 1 inst, prepare: host call 388 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 388 ms; max queue over 3 runs 0 ms; gate turns completed during the call 1; polls 111, max poll gap 10.1 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait AQ10 room                   96000 Hz, 1 inst, restore: host call 472 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 472 ms; max queue over 3 runs 0 ms; gate turns completed during the call 1; polls 141, max poll gap 13.4 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait AQ10 room                   96000 Hz, 1 inst, offline switch + first block: host call 365 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 365 ms; max queue over 3 runs 0 ms; gate turns completed during the call 1; polls 102, max poll gap 10.5 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) AQ10 room                   96000 Hz, 1 inst: worst host-thread wait of one instance while 0 others rebuild without pause (0: uncontended baseline; room size stepping 1 m every 50 ms), 3 runs: prepare 388 ms, restore 472 ms, offline switch + first block after a room-size edit 365 ms
05i-records (iv) AQ10 room                   96000 Hz, 4 inst: load until the last is audible 2944 ms (prepare's default-scene build + restore, per instance); per instance (load order) prepare [420 456 439 412] ms, restore [302 304 328 284] ms
05i-records (iv) AQ10 room                   96000 Hz, 4 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 638 median 686 max 718 ms
05i-records (iv) AQ10 room                   96000 Hz, 4 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 698 median 730 max 753 ms
05i-records (iv) AQ10 room                   96000 Hz, 4 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 2 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 756 median 801 max 849 ms
05i-records (iv) gate-wait AQ10 room                   96000 Hz, 4 inst, prepare: host call 957 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 957 ms; max queue over 3 runs 0 ms; gate turns completed during the call 4; polls 168, max poll gap 9.2 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait AQ10 room                   96000 Hz, 4 inst, restore: host call 860 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 860 ms; max queue over 3 runs 0 ms; gate turns completed during the call 4; polls 149, max poll gap 10.0 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait AQ10 room                   96000 Hz, 4 inst, offline switch + first block: host call 726 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 726 ms; max queue over 3 runs 19 ms; gate turns completed during the call 3; polls 130, max poll gap 10.3 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) AQ10 room                   96000 Hz, 4 inst: worst host-thread wait of one instance while 3 others rebuild without pause (0: uncontended baseline; room size stepping 1 m every 50 ms), 3 runs: prepare 957 ms, restore 860 ms, offline switch + first block after a room-size edit 726 ms
05i-records (iv) AQ10 room                   96000 Hz, 8 inst: load until the last is audible 5818 ms (prepare's default-scene build + restore, per instance); per instance (load order) prepare [479 468 433 399 425 436 424 415] ms, restore [286 293 285 300 295 287 296 299] ms
05i-records (iv) AQ10 room                   96000 Hz, 8 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 1348 median 1436 max 1464 ms
05i-records (iv) AQ10 room                   96000 Hz, 8 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 1375 median 1426 max 1453 ms
05i-records (iv) AQ10 room                   96000 Hz, 8 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 2 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 2112 median 2232 max 2241 ms
05i-records (iv) gate-wait AQ10 room                   96000 Hz, 8 inst, prepare: host call 1368 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 1368 ms; max queue over 3 runs 0 ms; gate turns completed during the call 8; polls 181, max poll gap 10.7 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait AQ10 room                   96000 Hz, 8 inst, restore: host call 1574 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 1574 ms; max queue over 3 runs 0 ms; gate turns completed during the call 8; polls 256, max poll gap 12.3 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait AQ10 room                   96000 Hz, 8 inst, offline switch + first block: host call 1263 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 1263 ms; max queue over 3 runs 0 ms; gate turns completed during the call 8; polls 172, max poll gap 11.1 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) AQ10 room                   96000 Hz, 8 inst: worst host-thread wait of one instance while 7 others rebuild without pause (0: uncontended baseline; room size stepping 1 m every 50 ms), 3 runs: prepare 1368 ms, restore 1574 ms, offline switch + first block after a room-size edit 1263 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst: load until the last is audible 1270 ms (prepare's default-scene build + restore, per instance); per instance (load order) prepare [364] ms, restore [906] ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 855 median 855 max 855 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 785 median 785 max 785 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 1183 median 1183 max 1183 ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst, prepare: host call 991 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 991 ms; max queue over 3 runs 0 ms; gate turns completed during the call 1; polls 201, max poll gap 13.6 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst, restore: host call 895 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 895 ms; max queue over 3 runs 0 ms; gate turns completed during the call 1; polls 100, max poll gap 13.9 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst, offline switch + first block: host call 899 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 899 ms; max queue over 3 runs 0 ms; gate turns completed during the call 1; polls 226, max poll gap 13.6 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 inst: worst host-thread wait of one instance while 0 others rebuild without pause (0: uncontended baseline; room size stepping 1 m every 50 ms), 3 runs: prepare 991 ms, restore 895 ms, offline switch + first block after a room-size edit 899 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst: load until the last is audible 4304 ms (prepare's default-scene build + restore, per instance); per instance (load order) prepare [257 236 274 318] ms, restore [752 744 770 953] ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 2557 median 2693 max 2793 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 2600 median 2655 max 2735 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 2406 median 2705 max 2813 ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst, prepare: host call 2254 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 2254 ms; max queue over 3 runs 0 ms; gate turns completed during the call 4; polls 354, max poll gap 10.0 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst, restore: host call 2116 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 2116 ms; max queue over 3 runs 0 ms; gate turns completed during the call 4; polls 280, max poll gap 10.8 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst, offline switch + first block: host call 2725 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 2725 ms; max queue over 3 runs 0 ms; gate turns completed during the call 4; polls 551, max poll gap 17.3 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 inst: worst host-thread wait of one instance while 3 others rebuild without pause (0: uncontended baseline; room size stepping 1 m every 50 ms), 3 runs: prepare 2254 ms, restore 2116 ms, offline switch + first block after a room-size edit 2725 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst: load until the last is audible 8663 ms (prepare's default-scene build + restore, per instance); per instance (load order) prepare [263 267 278 255 264 305 247 263] ms, restore [745 750 851 795 911 874 755 838] ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 4305 median 4961 max 5155 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 3858 median 4184 max 4403 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 4557 median 5317 max 5564 ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst, prepare: host call 4824 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 4824 ms; max queue over 3 runs 78 ms; gate turns completed during the call 9; polls 636, max poll gap 11.1 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst, restore: host call 4838 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 4838 ms; max queue over 3 runs 0 ms; gate turns completed during the call 8; polls 800, max poll gap 11.0 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst, offline switch + first block: host call 4523 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 4523 ms; max queue over 3 runs 0 ms; gate turns completed during the call 7; polls 696, max poll gap 14.1 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 inst: worst host-thread wait of one instance while 7 others rebuild without pause (0: uncontended baseline; room size stepping 1 m every 50 ms), 3 runs: prepare 4824 ms, restore 4838 ms, offline switch + first block after a room-size edit 4523 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst: load until the last is audible 2405 ms (prepare's default-scene build + restore, per instance); per instance (load order) prepare [416] ms, restore [1989] ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 1987 median 1987 max 1987 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 2005 median 2005 max 2005 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 2 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 2603 median 2603 max 2603 ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst, prepare: host call 2115 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 2115 ms; max queue over 3 runs 0 ms; gate turns completed during the call 1; polls 321, max poll gap 13.7 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst, restore: host call 2578 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 2578 ms; max queue over 3 runs 0 ms; gate turns completed during the call 1; polls 435, max poll gap 13.8 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst, offline switch + first block: host call 1994 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 1994 ms; max queue over 3 runs 0 ms; gate turns completed during the call 1; polls 186, max poll gap 14.4 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 inst: worst host-thread wait of one instance while 0 others rebuild without pause (0: uncontended baseline; room size stepping 1 m every 50 ms), 3 runs: prepare 2115 ms, restore 2578 ms, offline switch + first block after a room-size edit 1994 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst: load until the last is audible 8913 ms (prepare's default-scene build + restore, per instance); per instance (load order) prepare [496 446 371 435] ms, restore [2030 1783 1618 1735] ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 4879 median 5012 max 5085 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 5019 median 5276 max 5354 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 7509 median 7988 max 8176 ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst, prepare: host call 5713 ms = queue(Synchronous) 45 ms + queue(Offline) 0 ms + remainder 5668 ms; max queue over 3 runs 45 ms; gate turns completed during the call 4; polls 732, max poll gap 14.4 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst, restore: host call 5674 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 5674 ms; max queue over 3 runs 0 ms; gate turns completed during the call 4; polls 917, max poll gap 13.4 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst, offline switch + first block: host call 5467 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 5467 ms; max queue over 3 runs 0 ms; gate turns completed during the call 4; polls 727, max poll gap 13.4 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 inst: worst host-thread wait of one instance while 3 others rebuild without pause (0: uncontended baseline; room size stepping 1 m every 50 ms), 3 runs: prepare 5713 ms, restore 5674 ms, offline switch + first block after a room-size edit 5467 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst: load until the last is audible 18334 ms (prepare's default-scene build + restore, per instance); per instance (load order) prepare [409 466 550 393 439 424 408 391] ms, restore [1769 2098 1809 1981 1897 1797 1722 1780] ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst: staleness when automated together, room-size (-1 m in w/d/h) step on every instance at once: min 11506 median 12069 max 12232 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst: staleness when automated together, joint (room size -1 m in w/d/h and listener +0.5 m in x) step on every instance at once: min 10642 median 11100 max 11215 ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst: real-time staleness while 1 more instance renders offline (room size stepping 1 m per block, back to back; 3 offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every real-time instance at once: min 15032 median 15907 max 16203 ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst, prepare: host call 10634 ms = queue(Synchronous) 36 ms + queue(Offline) 0 ms + remainder 10598 ms; max queue over 3 runs 75 ms; gate turns completed during the call 8; polls 1540, max poll gap 19.2 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst, restore: host call 9762 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 9762 ms; max queue over 3 runs 0 ms; gate turns completed during the call 8; polls 1406, max poll gap 13.8 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) gate-wait cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst, offline switch + first block: host call 10140 ms = queue(Synchronous) 0 ms + queue(Offline) 0 ms + remainder 10140 ms; max queue over 3 runs 0 ms; gate turns completed during the call 8; polls 1420, max poll gap 11.9 ms (resolution); remainder includes this pipeline's own quiesce and its own build; queues count waiters process-wide (only this pipeline makes Synchronous/Offline entries here); poller locks the gate mutex about once per ms
05i-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 inst: worst host-thread wait of one instance while 7 others rebuild without pause (0: uncontended baseline; room size stepping 1 m every 50 ms), 3 runs: prepare 10634 ms, restore 9762 ms, offline switch + first block after a room-size edit 10140 ms
05h-records pool size 3
05h-records full rebuild dead_booth.json         48000 Hz: min 72 median 72 max 79 ms (3 runs)
05h-records full rebuild dead_booth.json         96000 Hz: min 114 median 119 max 120 ms (3 runs)
05h-records full rebuild living_room.json        48000 Hz: min 85 median 86 max 89 ms (3 runs)
05h-records full rebuild living_room.json        96000 Hz: min 152 median 160 max 164 ms (3 runs)
05h-records full rebuild classroom.json          48000 Hz: min 82 median 84 max 84 ms (3 runs)
05h-records full rebuild classroom.json          96000 Hz: min 169 median 175 max 191 ms (3 runs)
05h-records full rebuild club.json               48000 Hz: min 159 median 166 max 168 ms (3 runs)
05h-records full rebuild club.json               96000 Hz: min 291 median 339 max 363 ms (3 runs)
05h-records full rebuild concert_hall_box.json   48000 Hz: min 153 median 153 max 156 ms (3 runs)
05h-records full rebuild concert_hall_box.json   96000 Hz: min 299 median 304 max 320 ms (3 runs)
05h-records full rebuild stone_box.json          48000 Hz: min 274 median 293 max 297 ms (3 runs)
05h-records full rebuild stone_box.json          96000 Hz: min 665 median 674 max 711 ms (3 runs)
05h-records full rebuild AQ10 room           48000 Hz: min 134 median 135 max 144 ms
05h-records full rebuild AQ10 room           96000 Hz: min 279 median 283 max 288 ms
05h-records full rebuild cube100_flutter_fallback    48000 Hz: min 388 median 389 max 398 ms; transient RSS delta 0 MB (sampled max 0 kB, RSS before 0 kB)  [RSS n/a on this OS: recorded, not gated]
05h-records full rebuild cube100_flutter_fallback    96000 Hz: min 488 median 494 max 568 ms; transient RSS delta 0 MB (sampled max 0 kB, RSS before 0 kB)  [RSS n/a on this OS: recorded, not gated]
05h-records work ratio cube100_flutter_fallback   e0: realised work / W_scene 0.9347 (W_pilot 3154338, W_final 2547436, W_scene 6100000); achieved SE 0.002 dB; fallback yes
05h-records work ratio cube100_flutter_fallback   e1: realised work / W_scene 0.9347 (W_pilot 3154338, W_final 2547436, W_scene 6100000); achieved SE 0.001 dB; fallback yes
05h-records work pin cube100_flutter_fallback   unit decay 377517 samples (pinned 377517); synthesis FFT size 524288, generator 524288 (pinned 524288)
05h-records solve cube100_flutter_fallback   shipping rule, median of 5: 87.2 ms; 7.64 ns per image evaluation over W_pilot + W_final 11403548 (print, RG-1)
05h-records restore cube100_flutter_fallback   96 kHz with the solve, 10 runs: min 455 median 479 worst 594 ms; 14 x worst 8.32 s (30 s)
05h-records restore gate cube100_flutter_fallback   macOS: strict (recorded 7.59 s <= 29.1 s): 14 x worst 8.32 s <= 30 s
05h-records restore cube100_flutter_fallback   96 kHz contended (another pipeline solving the same room): min 600 median 647 worst 670 ms (3 runs)
05h-records full rebuild cube100_lowalpha0.05_s0.3   48000 Hz: min 694 median 738 max 798 ms; transient RSS delta 0 MB (sampled max 0 kB, RSS before 0 kB)  [RSS n/a on this OS: recorded, not gated]
05h-records full rebuild cube100_lowalpha0.05_s0.3   96000 Hz: min 1808 median 1889 max 1937 ms; transient RSS delta 0 MB (sampled max 0 kB, RSS before 0 kB)  [RSS n/a on this OS: recorded, not gated]
05h-records work ratio cube100_lowalpha0.05_s0.3  e0: realised work / W_scene 0.9910 (W_pilot 1696086, W_final 4348889, W_scene 6100000); achieved SE 0.092 dB; fallback no
05h-records work ratio cube100_lowalpha0.05_s0.3  e1: realised work / W_scene 0.9910 (W_pilot 1696086, W_final 4348889, W_scene 6100000); achieved SE 0.075 dB; fallback no
05h-records work pin cube100_lowalpha0.05_s0.3  unit decay 1152000 samples (pinned 1152000); synthesis FFT size 2097152, generator 2097152 (pinned 2097152)
05h-records solve cube100_lowalpha0.05_s0.3  shipping rule, median of 5: 113.9 ms; 9.42 ns per image evaluation over W_pilot + W_final 12089950 (print, RG-1)
05h-records restore cube100_lowalpha0.05_s0.3  96 kHz with the solve, 10 runs: min 1675 median 1903 worst 2261 ms; 14 x worst 31.66 s (30 s)
05h-records restore gate cube100_lowalpha0.05_s0.3  macOS: LISTED defect (recorded 14 x worst 33.40 s); 14 x worst now 31.66 s; WARNING OVER30S (printed, not asserted on hosted runners); growth bound reported only after the scene loop (RG-1)
05h-records restore cube100_lowalpha0.05_s0.3  96 kHz contended (another pipeline solving the same room): min 2674 median 2939 worst 2947 ms (3 runs)
05h-records full rebuild cube100_lowalpha0.05_s1     48000 Hz: min 679 median 707 max 937 ms; transient RSS delta 0 MB (sampled max 0 kB, RSS before 0 kB)  [RSS n/a on this OS: recorded, not gated]
05h-records full rebuild cube100_lowalpha0.05_s1     96000 Hz: min 1822 median 1827 max 1966 ms; transient RSS delta 0 MB (sampled max 0 kB, RSS before 0 kB)  [RSS n/a on this OS: recorded, not gated]
05h-records work ratio cube100_lowalpha0.05_s1    e0: realised work / W_scene 0.9859 (W_pilot 1666253, W_final 4347497, W_scene 6100000); achieved SE 0.360 dB; fallback no
05h-records work ratio cube100_lowalpha0.05_s1    e1: realised work / W_scene 0.9859 (W_pilot 1666253, W_final 4347497, W_scene 6100000); achieved SE 0.359 dB; fallback no
05h-records restore cube100_lowalpha0.05_s1    96 kHz with the solve, 10 runs: min 1768 median 1997 worst 2173 ms; 14 x worst 30.42 s (30 s)
05h-records restore gate cube100_lowalpha0.05_s1    macOS: reported set, not gated
05h-records restore cube100_lowalpha0.05_s1    96 kHz contended (another pipeline solving the same room): min 2813 median 2913 worst 3053 ms (3 runs)
05h-records GATE os=macOS scene=cube100_flutter_fallback x14worst=8.32 median=479 fullRebuildMedian=494 solveMedianMs=87.2 solveWarnAt=123.2 solveBasis=PROVISIONAL(n=1) nsPerEval=7.64 status=asserted(30s) flutterRef=484 flutterDev=-1.0% warnings=
05h-records GATE os=macOS scene=cube100_lowalpha0.05_s0.3 ratio=3.971 ratioWarnAt=4.500 solveMedianMs=113.9 solveWarnAt=100.4 solveBasis=PROVISIONAL(n=1) nsPerEval=9.42 x14worst=31.66 median=1903 growthBound=1999 fullRebuildMedian=1889 status=reported-only trigger=2172 warnings=OVER30S SOLVE 
07c1-records cond12 cube100_lowalpha0.05_s0.3   48000 Hz, macOS, 1 concurrent build: all rebuilt in 835 ms; (f) process peak RSS delta 0 MB (RSS before 822832 kB); (d) worst quiesce wait 28 ms (3 cancels at random points)
07c1-records cond12 cube100_lowalpha0.05_s0.3   48000 Hz, macOS, 4 concurrent builds: all rebuilt in 2194 ms; (f) process peak RSS delta 151 MB (RSS before 822880 kB); (d) worst quiesce wait 110 ms (3 cancels at random points)
07c1-records cond12 cube100_lowalpha0.05_s0.3   48000 Hz, macOS, 8 concurrent builds: all rebuilt in 4837 ms; (f) process peak RSS delta 672 MB (RSS before 888080 kB); (d) worst quiesce wait 178 ms (3 cancels at random points)
07c1-records cond12 cube100_lowalpha0.05_s0.3   96000 Hz, macOS, 1 concurrent build: all rebuilt in 2147 ms; (f) process peak RSS delta 73 MB (RSS before 651680 kB); (d) worst quiesce wait 90 ms (3 cancels at random points)
07c1-records cond12 cube100_lowalpha0.05_s0.3   96000 Hz, macOS, 4 concurrent builds: all rebuilt in 5182 ms; (f) process peak RSS delta 904 MB (RSS before 823488 kB); (d) worst quiesce wait 247 ms (3 cancels at random points)
07c1-records cond12 cube100_lowalpha0.05_s0.3   96000 Hz, macOS, 8 concurrent builds: all rebuilt in 10713 ms; (f) process peak RSS delta 1972 MB (RSS before 1098464 kB); (d) worst quiesce wait 577 ms (3 cancels at random points)
05h-records AQ4 AQ10 room                   48000 Hz: R (position-only, builder) 22 ms, full rebuild 161 ms, 2P 21.3 ms; R + 2P 44 ms (100 ms), 2R + 2P 66 ms (700 ms), full + 2P 182 ms (3 s)
05h-records AQ4 AQ10 room                   96000 Hz: R (position-only, builder) 27 ms, full rebuild 318 ms, 2P 10.7 ms; R + 2P 37 ms (100 ms), 2R + 2P 64 ms (700 ms), full + 2P 329 ms (3 s)
05h-records AQ4 cube100_lowalpha0.05_s0.3   48000 Hz: R (position-only, builder) 35 ms, full rebuild 793 ms, 2P 21.3 ms; R + 2P 56 ms (100 ms), 2R + 2P 90 ms (700 ms), full + 2P 815 ms (3 s)
05h-records AQ4 cube100_lowalpha0.05_s0.3   96000 Hz: R (position-only, builder) 25 ms, full rebuild 1984 ms, 2P 10.7 ms; R + 2P 35 ms (100 ms), 2R + 2P 60 ms (700 ms), full + 2P 1995 ms (3 s)
05h-records bounce 100 m cube  48000 Hz: 3-minute offline bounce with the room size stepping 1 m every 5 s (36 rebuilds): 49.1 s wall, ratio to real time 0.27 x
05h-records bounce 100 m cube  96000 Hz: 3-minute offline bounce with the room size stepping 1 m every 5 s (36 rebuilds): 152.6 s wall, ratio to real time 0.85 x
05h-records callback p99.9 at host buffer 64 (1333 us period), 1 concurrent builder at 100 m: p99.9 779 us, max 779 us over 861 callbacks (10 s)
05h-records callback p99.9 at host buffer 64 (1333 us period), 4 concurrent builders at 100 m: p99.9 577 us, max 1641 us over 1063 callbacks (10 s)
05h-records callback p99.9 at host buffer 64 (1333 us period), 8 concurrent builders at 100 m: p99.9 4245 us, max 4296 us over 1049 callbacks (10 s)
07c1-records cond10 cube100_lowalpha0.05_s0.3   48000 Hz, macOS: cancel at 2 % of a 811 ms rebuild (builder busy): setNonRealtime(true) 0.27 ms, cancel unwind 17.7 ms, first offline block 766 ms; transient RSS delta 0 MB (process, RSS before 765744 kB)
07c1-records cond10 cube100_lowalpha0.05_s0.3   48000 Hz, macOS: cancel at 10 % of a 811 ms rebuild (builder busy): setNonRealtime(true) 0.43 ms, cancel unwind 53.7 ms, first offline block 775 ms; transient RSS delta 0 MB (process, RSS before 765760 kB)
07c1-records cond10 cube100_lowalpha0.05_s0.3   48000 Hz, macOS: cancel at 30 % of a 811 ms rebuild (builder busy): setNonRealtime(true) 0.28 ms, cancel unwind 13.9 ms, first offline block 820 ms; transient RSS delta 0 MB (process, RSS before 765760 kB)
07c1-records cond10 cube100_lowalpha0.05_s0.3   48000 Hz, macOS: cancel at 60 % of a 811 ms rebuild (builder busy): setNonRealtime(true) 2.22 ms, cancel unwind 38.7 ms, first offline block 898 ms; transient RSS delta 0 MB (process, RSS before 765760 kB)
07c1-records cond10 cube100_lowalpha0.05_s0.3   48000 Hz, macOS: cancel at 90 % of a 811 ms rebuild (builder busy): setNonRealtime(true) 0.40 ms, cancel unwind 8.6 ms, first offline block 805 ms; transient RSS delta 0 MB (process, RSS before 765856 kB)
07c1-records cond10 cube100_lowalpha0.05_s0.3   48000 Hz, macOS: WORST setNonRealtime(true) 2.22 ms (was: the in-flight build, AX38 (i) entry 2 664 ms), cancel unwind 53.7 ms, first offline block 898 ms, transient RSS delta 0 MB
07c1-records cond10 cube100_lowalpha0.05_s0.3   96000 Hz, macOS: cancel at 2 % of a 1900 ms rebuild (builder busy): setNonRealtime(true) 2.31 ms, cancel unwind 6.2 ms, first offline block 1962 ms; transient RSS delta 80 MB (process, RSS before 791376 kB)
07c1-records cond10 cube100_lowalpha0.05_s0.3   96000 Hz, macOS: cancel at 10 % of a 1900 ms rebuild (builder busy): setNonRealtime(true) 0.49 ms, cancel unwind 8.7 ms, first offline block 1897 ms; transient RSS delta 80 MB (process, RSS before 791376 kB)
07c1-records cond10 cube100_lowalpha0.05_s0.3   96000 Hz, macOS: cancel at 30 % of a 1900 ms rebuild (builder busy): setNonRealtime(true) 0.83 ms, cancel unwind 114.4 ms, first offline block 1855 ms; transient RSS delta 80 MB (process, RSS before 791376 kB)
07c1-records cond10 cube100_lowalpha0.05_s0.3   96000 Hz, macOS: cancel at 60 % of a 1900 ms rebuild (builder busy): setNonRealtime(true) 0.52 ms, cancel unwind 58.5 ms, first offline block 2124 ms; transient RSS delta 80 MB (process, RSS before 791376 kB)
07c1-records cond10 cube100_lowalpha0.05_s0.3   96000 Hz, macOS: cancel at 90 % of a 1900 ms rebuild (builder busy): setNonRealtime(true) 2.50 ms, cancel unwind 10.7 ms, first offline block 1933 ms; transient RSS delta 80 MB (process, RSS before 791376 kB)
07c1-records cond10 cube100_lowalpha0.05_s0.3   96000 Hz, macOS: WORST setNonRealtime(true) 2.50 ms (was: the in-flight build, AX38 (i) entry 2 664 ms), cancel unwind 114.4 ms, first offline block 2124 ms, transient RSS delta 80 MB
05i-records (iv) offline AQ10 room                   48000 Hz, 1 offline instance in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 134 median 137 worst 139 ms; first build (after restore) worst 159 ms; wall 706 ms
05i-records (iv) offline AQ10 room                   48000 Hz, 4 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 229 median 257 worst 284 ms; first build (after restore) worst 295 ms; wall 1343 ms
05i-records (iv) offline AQ10 room                   48000 Hz, 8 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 335 median 491 worst 613 ms; first build (after restore) worst 683 ms; wall 2659 ms
05i-records (iv) offline AQ10 room                   96000 Hz, 1 offline instance in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 286 median 301 worst 332 ms; first build (after restore) worst 321 ms; wall 1542 ms
05i-records (iv) offline AQ10 room                   96000 Hz, 4 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 633 median 787 worst 953 ms; first build (after restore) worst 884 ms; wall 4079 ms
05i-records (iv) offline AQ10 room                   96000 Hz, 8 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 1100 median 1341 worst 1509 ms; first build (after restore) worst 1539 ms; wall 6859 ms
05i-records (iv) offline cube100_lowalpha0.05_s0.3   48000 Hz, 1 offline instance in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 823 median 933 worst 1009 ms; first build (after restore) worst 789 ms; wall 4488 ms
05i-records (iv) offline cube100_lowalpha0.05_s0.3   48000 Hz, 4 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 2053 median 2256 worst 2669 ms; first build (after restore) worst 2436 ms; wall 11570 ms
05i-records (iv) offline cube100_lowalpha0.05_s0.3   48000 Hz, 8 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 2921 median 4430 worst 6332 ms; first build (after restore) worst 4463 ms; wall 22651 ms
05i-records (iv) offline cube100_lowalpha0.05_s0.3   96000 Hz, 1 offline instance in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 1850 median 1882 worst 1996 ms; first build (after restore) worst 2874 ms; wall 10483 ms
05i-records (iv) offline cube100_lowalpha0.05_s0.3   96000 Hz, 4 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 4762 median 5054 worst 5471 ms; first build (after restore) worst 5611 ms; wall 25877 ms
05i-records (iv) offline cube100_lowalpha0.05_s0.3   96000 Hz, 8 offline instances in parallel: wait per rebuilding block (room size -1 m per block, 4 steps back to back) min 9501 median 10337 worst 14300 ms; first build (after restore) worst 10376 ms; wall 54387 ms
05h-records (iv) AQ10 room                   48000 Hz, 1 instances: load until the last is audible 455 ms; staleness when rebuilding together min 148 median 148 max 148 ms
05h-records (iv) AQ10 room                   48000 Hz, 4 instances: load until the last is audible 1704 ms; staleness when rebuilding together min 214 median 246 max 269 ms
05h-records (iv) AQ10 room                   48000 Hz, 8 instances: load until the last is audible 3580 ms; staleness when rebuilding together min 479 median 548 max 585 ms
05h-records (iv) AQ10 room                   96000 Hz, 1 instances: load until the last is audible 762 ms; staleness when rebuilding together min 328 median 328 max 328 ms
05h-records (iv) AQ10 room                   96000 Hz, 4 instances: load until the last is audible 3032 ms; staleness when rebuilding together min 659 median 741 max 766 ms
05h-records (iv) AQ10 room                   96000 Hz, 8 instances: load until the last is audible 6081 ms; staleness when rebuilding together min 1411 median 1459 max 1501 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 instances: load until the last is audible 1090 ms; staleness when rebuilding together min 771 median 771 max 771 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 instances: load until the last is audible 3863 ms; staleness when rebuilding together min 2043 median 2125 max 2282 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 instances: load until the last is audible 8666 ms; staleness when rebuilding together min 4968 median 5363 max 5597 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 instances: load until the last is audible 2390 ms; staleness when rebuilding together min 2060 median 2060 max 2060 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 instances: load until the last is audible 10019 ms; staleness when rebuilding together min 4895 median 5000 max 5078 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 instances: load until the last is audible 19864 ms; staleness when rebuilding together min 9863 median 10219 max 10303 ms
05h-records quiesce cube100_flutter_fallback   96 kHz: builder rebuild 552 ms; cancel at a random point, 10 runs: wait min 4 median 13 worst 92 ms
05h-records quiesce cube100_flutter_fallback   run  0: cancel at 112 ms of 552 -> waited 12 ms
05h-records quiesce cube100_flutter_fallback   run  1: cancel at 124 ms of 552 -> waited 6 ms
05h-records quiesce cube100_flutter_fallback   run  2: cancel at 495 ms of 552 -> waited 14 ms
05h-records quiesce cube100_flutter_fallback   run  3: cancel at 217 ms of 552 -> waited 33 ms
05h-records quiesce cube100_flutter_fallback   run  4: cancel at 158 ms of 552 -> waited 26 ms
05h-records quiesce cube100_flutter_fallback   run  5: cancel at 98 ms of 552 -> waited 92 ms
05h-records quiesce cube100_flutter_fallback   run  6: cancel at 152 ms of 552 -> waited 14 ms
05h-records quiesce cube100_flutter_fallback   run  7: cancel at 313 ms of 552 -> waited 4 ms
05h-records quiesce cube100_flutter_fallback   run  8: cancel at 224 ms of 552 -> waited 4 ms
05h-records quiesce cube100_flutter_fallback   run  9: cancel at 352 ms of 552 -> waited 5 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  96 kHz: builder rebuild 1654 ms; cancel at a random point, 10 runs: wait min 14 median 38 worst 120 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  0: cancel at 1282 ms of 1654 -> waited 23 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  1: cancel at 1633 ms of 1654 -> waited 41 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  2: cancel at 1457 ms of 1654 -> waited 91 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  3: cancel at 1051 ms of 1654 -> waited 50 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  4: cancel at 1590 ms of 1654 -> waited 22 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  5: cancel at 505 ms of 1654 -> waited 120 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  6: cancel at 459 ms of 1654 -> waited 14 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  7: cancel at 189 ms of 1654 -> waited 34 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  8: cancel at 1645 ms of 1654 -> waited 57 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  9: cancel at 608 ms of 1654 -> waited 35 ms
05i-records K-e12 os=macOS cube100_flutter_fallback   96 kHz: restore with a room edit in flight (room size -1/-2 m in w/d/h, restore of a new room size at a random point of the 471 ms rebuild), 10 runs: min 471 median 527 worst 686 ms; builder busy at the restore in 9 of 10 runs, worst over those 686 ms (idle restore of a new state median 502 ms, 3 runs); per-restore budget 2143 ms: within
05i-records K-e12 os=macOS cube100_flutter_fallback   run  0: restore at 127 ms of 471 (builder busy: yes) -> host thread 471 ms
05i-records K-e12 os=macOS cube100_flutter_fallback   run  1: restore at 466 ms of 471 (builder busy: no) -> host thread 521 ms
05i-records K-e12 os=macOS cube100_flutter_fallback   run  2: restore at 44 ms of 471 (builder busy: yes) -> host thread 686 ms
05i-records K-e12 os=macOS cube100_flutter_fallback   run  3: restore at 370 ms of 471 (builder busy: yes) -> host thread 558 ms
05i-records K-e12 os=macOS cube100_flutter_fallback   run  4: restore at 228 ms of 471 (builder busy: yes) -> host thread 655 ms
05i-records K-e12 os=macOS cube100_flutter_fallback   run  5: restore at 250 ms of 471 (builder busy: yes) -> host thread 543 ms
05i-records K-e12 os=macOS cube100_flutter_fallback   run  6: restore at 132 ms of 471 (builder busy: yes) -> host thread 533 ms
05i-records K-e12 os=macOS cube100_flutter_fallback   run  7: restore at 106 ms of 471 (builder busy: yes) -> host thread 498 ms
05i-records K-e12 os=macOS cube100_flutter_fallback   run  8: restore at 173 ms of 471 (builder busy: yes) -> host thread 484 ms
05i-records K-e12 os=macOS cube100_flutter_fallback   run  9: restore at 38 ms of 471 (builder busy: yes) -> host thread 519 ms
05i-records K-e12 os=macOS cube100_lowalpha0.05_s0.3  96 kHz: restore with a room edit in flight (room size -1/-2 m in w/d/h, restore of a new room size at a random point of the 1754 ms rebuild), 10 runs: min 1858 median 1955 worst 1992 ms; builder busy at the restore in 10 of 10 runs, worst over those 1992 ms (idle restore of a new state median 1762 ms, 3 runs); per-restore budget 2143 ms: within
05i-records K-e12 os=macOS cube100_lowalpha0.05_s0.3  run  0: restore at 1315 ms of 1754 (builder busy: yes) -> host thread 1951 ms
05i-records K-e12 os=macOS cube100_lowalpha0.05_s0.3  run  1: restore at 144 ms of 1754 (builder busy: yes) -> host thread 1959 ms
05i-records K-e12 os=macOS cube100_lowalpha0.05_s0.3  run  2: restore at 1657 ms of 1754 (builder busy: yes) -> host thread 1965 ms
05i-records K-e12 os=macOS cube100_lowalpha0.05_s0.3  run  3: restore at 1699 ms of 1754 (builder busy: yes) -> host thread 1992 ms
05i-records K-e12 os=macOS cube100_lowalpha0.05_s0.3  run  4: restore at 1224 ms of 1754 (builder busy: yes) -> host thread 1952 ms
05i-records K-e12 os=macOS cube100_lowalpha0.05_s0.3  run  5: restore at 193 ms of 1754 (builder busy: yes) -> host thread 1992 ms
05i-records K-e12 os=macOS cube100_lowalpha0.05_s0.3  run  6: restore at 696 ms of 1754 (builder busy: yes) -> host thread 1973 ms
05i-records K-e12 os=macOS cube100_lowalpha0.05_s0.3  run  7: restore at 1269 ms of 1754 (builder busy: yes) -> host thread 1891 ms
05i-records K-e12 os=macOS cube100_lowalpha0.05_s0.3  run  8: restore at 912 ms of 1754 (builder busy: yes) -> host thread 1858 ms
05i-records K-e12 os=macOS cube100_lowalpha0.05_s0.3  run  9: restore at 515 ms of 1754 (builder busy: yes) -> host thread 1909 ms
All tests passed (15915 assertions in 19 test cases)
All tests passed (6 assertions in 1 test case)
[36;1mtools/ci/run_pluginval.sh --output-dir build/pluginval-logs "${PLUGINS[@]}"[0m
Downloading pluginval v1.0.4: https://github.com/Tracktion/pluginval/releases/download/v1.0.4/pluginval_macOS.zip
pluginval - 1.0.4
##[group]pluginval build/release/SpatialScene_artefacts/Release/VST3/SpatialScene.vst3
pluginval --strictness-level 10 --timeout-ms 120000 --output-dir build/pluginval-logs build/release/SpatialScene_artefacts/Release/VST3/SpatialScene.vst3
Starting tests in: pluginval / Scan for plugins located in: /Users/runner/work/makroof/makroof/build/release/SpatialScene_artefacts/Release/VST3/SpatialScene.vst3...
Completed tests in pluginval / Scan for plugins located in: /Users/runner/work/makroof/makroof/build/release/SpatialScene_artefacts/Release/VST3/SpatialScene.vst3
Starting tests in: pluginval / Open plugin (cold)...
Completed tests in pluginval / Open plugin (cold)
Starting tests in: pluginval / Open plugin (warm)...
Completed tests in pluginval / Open plugin (warm)
Starting tests in: pluginval / Plugin info...
Completed tests in pluginval / Plugin info
Starting tests in: pluginval / Plugin programs...
Completed tests in pluginval / Plugin programs
Starting tests in: pluginval / Editor...
Completed tests in pluginval / Editor
Starting tests in: pluginval / Open editor whilst processing...
Completed tests in pluginval / Open editor whilst processing
Starting tests in: pluginval / Audio processing...
Completed tests in pluginval / Audio processing
Starting tests in: pluginval / Non-releasing audio processing...
Completed tests in pluginval / Non-releasing audio processing
Starting tests in: pluginval / Plugin state...
Completed tests in pluginval / Plugin state
Starting tests in: pluginval / Plugin state restoration...
Completed tests in pluginval / Plugin state restoration
Starting tests in: pluginval / Automation...
Completed tests in pluginval / Automation
Starting tests in: pluginval / Editor Automation...
Completed tests in pluginval / Editor Automation
Starting tests in: pluginval / Automatable Parameters...
Completed tests in pluginval / Automatable Parameters
Starting tests in: pluginval / Parameters...
Completed tests in pluginval / Parameters
Starting tests in: pluginval / Background thread state...
Completed tests in pluginval / Background thread state
Starting tests in: pluginval / Parameter thread safety...
Completed tests in pluginval / Parameter thread safety
Starting tests in: pluginval / auval...
Completed tests in pluginval / auval
Starting tests in: pluginval / vst3 validator...
Completed tests in pluginval / vst3 validator
Starting tests in: pluginval / Basic bus...
Completed tests in pluginval / Basic bus
Starting tests in: pluginval / Listing available buses...
Completed tests in pluginval / Listing available buses
Starting tests in: pluginval / Enabling all buses...
Completed tests in pluginval / Enabling all buses
Starting tests in: pluginval / Disabling non-main busses...
Completed tests in pluginval / Disabling non-main busses
Starting tests in: pluginval / Restoring default layout...
Completed tests in pluginval / Restoring default layout
Starting tests in: pluginval / Fuzz parameters...
Completed tests in pluginval / Fuzz parameters
##[group]pluginval /Users/runner/Library/Audio/Plug-Ins/Components/SpatialScene.component
pluginval --strictness-level 10 --timeout-ms 120000 --output-dir build/pluginval-logs /Users/runner/Library/Audio/Plug-Ins/Components/SpatialScene.component
Starting tests in: pluginval / Scan for plugins located in: /Users/runner/Library/Audio/Plug-Ins/Components/SpatialScene.component...
Completed tests in pluginval / Scan for plugins located in: /Users/runner/Library/Audio/Plug-Ins/Components/SpatialScene.component
Starting tests in: pluginval / Open plugin (cold)...
Completed tests in pluginval / Open plugin (cold)
Starting tests in: pluginval / Open plugin (warm)...
Completed tests in pluginval / Open plugin (warm)
Starting tests in: pluginval / Plugin info...
Completed tests in pluginval / Plugin info
Starting tests in: pluginval / Plugin programs...
Completed tests in pluginval / Plugin programs
Starting tests in: pluginval / Editor...
Completed tests in pluginval / Editor
Starting tests in: pluginval / Open editor whilst processing...
Completed tests in pluginval / Open editor whilst processing
Starting tests in: pluginval / Audio processing...
Completed tests in pluginval / Audio processing
Starting tests in: pluginval / Non-releasing audio processing...
Completed tests in pluginval / Non-releasing audio processing
Starting tests in: pluginval / Plugin state...
Completed tests in pluginval / Plugin state
Starting tests in: pluginval / Plugin state restoration...
Completed tests in pluginval / Plugin state restoration
Starting tests in: pluginval / Automation...
Completed tests in pluginval / Automation
Starting tests in: pluginval / Editor Automation...
Completed tests in pluginval / Editor Automation
Starting tests in: pluginval / Automatable Parameters...
Completed tests in pluginval / Automatable Parameters
Starting tests in: pluginval / Parameters...
Completed tests in pluginval / Parameters
Starting tests in: pluginval / Background thread state...
Completed tests in pluginval / Background thread state
Starting tests in: pluginval / Parameter thread safety...
Completed tests in pluginval / Parameter thread safety
Starting tests in: pluginval / auval...
auval exited with code: 0
Completed tests in pluginval / auval
Starting tests in: pluginval / vst3 validator...
Completed tests in pluginval / vst3 validator
Starting tests in: pluginval / Basic bus...
Completed tests in pluginval / Basic bus
Starting tests in: pluginval / Listing available buses...
Completed tests in pluginval / Listing available buses
Starting tests in: pluginval / Enabling all buses...
Completed tests in pluginval / Enabling all buses
Starting tests in: pluginval / Disabling non-main busses...
Completed tests in pluginval / Disabling non-main busses
Starting tests in: pluginval / Restoring default layout...
Completed tests in pluginval / Restoring default layout
Starting tests in: pluginval / Fuzz parameters...
Completed tests in pluginval / Fuzz parameters
pluginval logs: build/pluginval-logs
[36;1mrun_auval() { auval -v aufx Spsc Mkrf 2>&1 | tee build/auval.log; }[0m
[36;1mif ! run_auval; then[0m
[36;1m  run_auval[0m
[36;1mgrep -q "AU VALIDATION SUCCEEDED" build/auval.log[0m
  name: pluginval-macos
  path: build/pluginval-logs

Uploading artifact: pluginval-macos.zip
Artifact pluginval-macos successfully finalized. Artifact ID 13946666294
Artifact pluginval-macos has been successfully uploaded! Final size is 4459 bytes. Artifact ID is 13946666294
```
