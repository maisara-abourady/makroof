# Orchestrator — local records of session 2 (one loaded box: the reference job and other suites ran concurrently; the three-OS CI run is the record of record)

Release build, Linux x86-64, 4 cores, 2026-11-10. Timings are contaminated by concurrent compute (noted in the brief's steward log round 9); the memory, work-ratio, flag and agreement figures are not.

## `[diffuse-records]` (records_dh1b.log)

```
05h-records (iv) AQ10 room                   48000 Hz, 1 instances: load until the last is audible 778 ms; staleness when rebuilding together min 286 median 286 max 286 ms
05h-records (iv) AQ10 room                   48000 Hz, 4 instances: load until the last is audible 2894 ms; staleness when rebuilding together min 333 median 774 max 1210 ms
05h-records (iv) AQ10 room                   48000 Hz, 8 instances: load until the last is audible 5464 ms; staleness when rebuilding together min 295 median 1395 max 2393 ms
05h-records (iv) AQ10 room                   96000 Hz, 1 instances: load until the last is audible 1528 ms; staleness when rebuilding together min 644 median 644 max 644 ms
05h-records (iv) AQ10 room                   96000 Hz, 4 instances: load until the last is audible 6215 ms; staleness when rebuilding together min 697 median 1737 max 2750 ms
05h-records (iv) AQ10 room                   96000 Hz, 8 instances: load until the last is audible 11837 ms; staleness when rebuilding together min 745 median 3167 max 5823 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 instances: load until the last is audible 2089 ms; staleness when rebuilding together min 1501 median 1501 max 1501 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 instances: load until the last is audible 7525 ms; staleness when rebuilding together min 1543 median 3812 max 6120 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 instances: load until the last is audible 15587 ms; staleness when rebuilding together min 1478 median 6977 max 12345 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 instances: load until the last is audible 4263 ms; staleness when rebuilding together min 3646 median 3646 max 3646 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 instances: load until the last is audible 17603 ms; staleness when rebuilding together min 3870 median 10349 max 16384 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 instances: load until the last is audible 37740 ms; staleness when rebuilding together min 3456 median 16061 max 29855 ms
05h-records pool size 4
05h-records full rebuild dead_booth.json         48000 Hz: min 111 median 116 max 131 ms (3 runs)
05h-records full rebuild dead_booth.json         96000 Hz: min 197 median 198 max 213 ms (3 runs)
05h-records full rebuild living_room.json        48000 Hz: min 110 median 117 max 154 ms (3 runs)
05h-records full rebuild living_room.json        96000 Hz: min 263 median 274 max 304 ms (3 runs)
05h-records full rebuild classroom.json          48000 Hz: min 100 median 103 max 115 ms (3 runs)
05h-records full rebuild classroom.json          96000 Hz: min 264 median 296 max 304 ms (3 runs)
05h-records full rebuild club.json               48000 Hz: min 235 median 240 max 244 ms (3 runs)
05h-records full rebuild club.json               96000 Hz: min 654 median 660 max 667 ms (3 runs)
05h-records full rebuild concert_hall_box.json   48000 Hz: min 280 median 296 max 308 ms (3 runs)
05h-records full rebuild concert_hall_box.json   96000 Hz: min 703 median 781 max 797 ms (3 runs)
05h-records full rebuild stone_box.json          48000 Hz: min 646 median 685 max 685 ms (3 runs)
05h-records full rebuild stone_box.json          96000 Hz: min 1437 median 1543 max 1551 ms (3 runs)
05h-records full rebuild AQ10 room           48000 Hz: min 237 median 247 max 254 ms
05h-records full rebuild AQ10 room           96000 Hz: min 623 median 642 max 649 ms
05h-records full rebuild cube100_flutter_fallback    48000 Hz: min 526 median 569 max 597 ms; transient RSS delta 38 MB (sampled max 354520 kB, RSS before 315880 kB)
05h-records full rebuild cube100_flutter_fallback    96000 Hz: min 1055 median 1147 max 1155 ms; transient RSS delta 85 MB (sampled max 252940 kB, RSS before 165996 kB)
05h-records work ratio cube100_flutter_fallback   e0: realised work / W_scene 0.9347 (W_pilot 3154338, W_final 2547436, W_scene 6100000); achieved SE 0.002 dB; fallback yes
05h-records work ratio cube100_flutter_fallback   e1: realised work / W_scene 0.9347 (W_pilot 3154338, W_final 2547436, W_scene 6100000); achieved SE 0.001 dB; fallback yes
05h-records restore cube100_flutter_fallback   96 kHz with the solve, 10 runs: min 1104 median 1181 worst 1338 ms; 14 x worst 18.74 s (30 s)
05h-records restore gate cube100_flutter_fallback   Linux: strict (recorded 10.59 s <= 29.1 s): 14 x worst 18.74 s <= 30 s
05h-records restore cube100_flutter_fallback   96 kHz contended (another pipeline solving the same room): min 1087 median 1116 worst 1117 ms (3 runs)
05h-records full rebuild cube100_lowalpha0.05_s0.3   48000 Hz: min 1347 median 1399 max 1432 ms; transient RSS delta 137 MB (sampled max 341976 kB, RSS before 201920 kB)
05h-records full rebuild cube100_lowalpha0.05_s0.3   96000 Hz: min 3349 median 3454 max 3493 ms; transient RSS delta 297 MB (sampled max 500304 kB, RSS before 196680 kB)
05h-records work ratio cube100_lowalpha0.05_s0.3  e0: realised work / W_scene 0.9910 (W_pilot 1696086, W_final 4348889, W_scene 6100000); achieved SE 0.092 dB; fallback no
05h-records work ratio cube100_lowalpha0.05_s0.3  e1: realised work / W_scene 0.9910 (W_pilot 1696086, W_final 4348889, W_scene 6100000); achieved SE 0.075 dB; fallback no
05h-records restore cube100_lowalpha0.05_s0.3  96 kHz with the solve, 10 runs: min 3092 median 3236 worst 3467 ms; 14 x worst 48.54 s (30 s)
05h-records restore gate cube100_lowalpha0.05_s0.3  Linux: LISTED defect (recorded 14 x worst 30.27 s); 14 x worst now 48.54 s; growth bound median 3236 <= 0 ms (BASELINE PENDING: pin this run's median with a CHANGELOG reason; not asserted)
05h-records restore cube100_lowalpha0.05_s0.3  96 kHz contended (another pipeline solving the same room): min 3082 median 3299 worst 3354 ms (3 runs)
05h-records full rebuild cube100_lowalpha0.05_s1     48000 Hz: min 1317 median 1354 max 1406 ms; transient RSS delta 137 MB (sampled max 317176 kB, RSS before 177120 kB)
05h-records full rebuild cube100_lowalpha0.05_s1     96000 Hz: min 3067 median 3220 max 3404 ms; transient RSS delta 297 MB (sampled max 475504 kB, RSS before 171880 kB)
05h-records work ratio cube100_lowalpha0.05_s1    e0: realised work / W_scene 0.9859 (W_pilot 1666253, W_final 4347497, W_scene 6100000); achieved SE 0.360 dB; fallback no
05h-records work ratio cube100_lowalpha0.05_s1    e1: realised work / W_scene 0.9859 (W_pilot 1666253, W_final 4347497, W_scene 6100000); achieved SE 0.359 dB; fallback no
05h-records restore cube100_lowalpha0.05_s1    96 kHz with the solve, 10 runs: min 2754 median 3033 worst 3338 ms; 14 x worst 46.73 s (30 s)
05h-records restore gate cube100_lowalpha0.05_s1    Linux: reported set, not gated
05h-records restore cube100_lowalpha0.05_s1    96 kHz contended (another pipeline solving the same room): min 3252 median 3255 worst 6424 ms (3 runs)
```

## `[diffuse-records-aq4]` (records_aq4.log)

```
05h-records AQ4 AQ10 room                   48000 Hz: R (position-only, builder) 20 ms, full rebuild 268 ms, 2P 21.3 ms; R + 2P 42 ms (100 ms), 2R + 2P 62 ms (700 ms), full + 2P 290 ms (3 s)
05h-records AQ4 AQ10 room                   96000 Hz: R (position-only, builder) 20 ms, full rebuild 628 ms, 2P 10.7 ms; R + 2P 31 ms (100 ms), 2R + 2P 51 ms (700 ms), full + 2P 638 ms (3 s)
05h-records AQ4 cube100_lowalpha0.05_s0.3   48000 Hz: R (position-only, builder) 20 ms, full rebuild 1475 ms, 2P 21.3 ms; R + 2P 42 ms (100 ms), 2R + 2P 62 ms (700 ms), full + 2P 1496 ms (3 s)
05h-records AQ4 cube100_lowalpha0.05_s0.3   96000 Hz: R (position-only, builder) 20 ms, full rebuild 3070 ms, 2P 10.7 ms; R + 2P 31 ms (100 ms), 2R + 2P 51 ms (700 ms), full + 2P 3081 ms (3 s)
05h-records bounce 100 m cube  48000 Hz: 3-minute offline bounce with the room size stepping 1 m every 5 s (36 rebuilds): 84.7 s wall, ratio to real time 0.47 x
05h-records bounce 100 m cube  96000 Hz: 3-minute offline bounce with the room size stepping 1 m every 5 s (36 rebuilds): 239.4 s wall, ratio to real time 1.33 x
05h-records callback p99.9 at host buffer 64 (1333 us period), 1 concurrent builder at 100 m: p99.9 2525 us, max 5174 us over 6294 callbacks (10 s)
05h-records callback p99.9 at host buffer 64 (1333 us period), 4 concurrent builders at 100 m: p99.9 2374 us, max 10427 us over 5938 callbacks (10 s)
05h-records callback p99.9 at host buffer 64 (1333 us period), 8 concurrent builders at 100 m: p99.9 4194 us, max 9490 us over 5716 callbacks (10 s)
```

## `[diffuse-quiesce]` (quiesce.log)

```
05h-records quiesce cube100_flutter_fallback   96 kHz: builder rebuild 1260 ms; cancel at a random point, 10 runs: wait min 7 median 188 worst 491 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  96 kHz: builder rebuild 3645 ms; cancel at a random point, 10 runs: wait min 74 median 461 worst 2664 ms
```

## `[probe-denormals-detector]` (detector2.log)

```
probe-detector calibration: a denormal operand without the guard reads as operand on this architecture
probe-detector fs 48000 absorbentScene (dead_booth, alpha 0.98, s 1)           : flags FTZ off [clear], FTZ on [clear]; IRs bit-identical
probe-detector fs 48000 dead_booth.json                                        : flags FTZ off [clear], FTZ on [clear]; IRs bit-identical
probe-detector fs 48000 edge_values.json                                       : flags FTZ off [clear], FTZ on [clear]; IRs bit-identical
probe-detector fs 48000 open_field.json                                        : flags FTZ off [clear], FTZ on [clear]; IRs bit-identical
probe-detector fs 48000 medium_room.json                                       : flags FTZ off [clear], FTZ on [clear]; IRs bit-identical
probe-detector fs 48000 dead_booth alpha 0.01 at 63 Hz, 0.999 above, s 0.5 (Seat 3): flags FTZ off [operand+underflow], FTZ on [underflow]; IRs bit-identical
probe-detector fs 48000 dead_booth alpha 0.999 s 0.5                           : flags FTZ off [clear], FTZ on [clear]; IRs bit-identical
probe-detector fs 48000 100 m cube alpha 0.999 s 0.5                           : flags FTZ off [clear], FTZ on [clear]; IRs bit-identical
probe-detector fs 48000 100 m cube alpha 0.01 at 63/125 Hz, 0.999 above        : flags FTZ off [clear], FTZ on [clear]; IRs bit-identical
probe-detector fs 96000 absorbentScene (dead_booth, alpha 0.98, s 1)           : flags FTZ off [clear], FTZ on [clear]; IRs bit-identical
probe-detector fs 96000 dead_booth.json                                        : flags FTZ off [clear], FTZ on [clear]; IRs bit-identical
probe-detector fs 96000 edge_values.json                                       : flags FTZ off [clear], FTZ on [clear]; IRs bit-identical
probe-detector fs 96000 open_field.json                                        : flags FTZ off [clear], FTZ on [clear]; IRs bit-identical
probe-detector fs 96000 medium_room.json                                       : flags FTZ off [clear], FTZ on [clear]; IRs bit-identical
probe-detector fs 96000 dead_booth alpha 0.01 at 63 Hz, 0.999 above, s 0.5 (Seat 3): flags FTZ off [operand+underflow], FTZ on [underflow]; IRs bit-identical
probe-detector fs 96000 dead_booth alpha 0.999 s 0.5                           : flags FTZ off [clear], FTZ on [clear]; IRs bit-identical
probe-detector fs 96000 100 m cube alpha 0.999 s 0.5                           : flags FTZ off [clear], FTZ on [clear]; IRs bit-identical
probe-detector fs 96000 100 m cube alpha 0.01 at 63/125 Hz, 0.999 above        : flags FTZ off [clear], FTZ on [clear]; IRs bit-identical
```

## `[diffuse-agree-full]` application run (agree_full5.log)

```
agree-full pooled bias band 0 [CHECK, additive]: mean (C++ - ref) -0.0047 dB over 30 case-bands; bound 3 SE_pool + mean l_ref = 0.0067 + 0.0032 = 0.0099 dB (within)
agree-full pooled bias band 1 [CHECK, additive]: mean (C++ - ref) -0.0047 dB over 30 case-bands; bound 3 SE_pool + mean l_ref = 0.0067 + 0.0032 = 0.0098 dB (within)
agree-full pooled bias band 2 [CHECK, additive]: mean (C++ - ref) -0.0047 dB over 30 case-bands; bound 3 SE_pool + mean l_ref = 0.0066 + 0.0032 = 0.0098 dB (within)
agree-full pooled bias band 3 [CHECK, additive]: mean (C++ - ref) +0.0002 dB over 60 case-bands; bound 3 SE_pool + mean l_ref = 0.0038 + 0.0040 = 0.0078 dB (within)
agree-full pooled bias band 4 [CHECK, additive]: mean (C++ - ref) +0.0000 dB over 60 case-bands; bound 3 SE_pool + mean l_ref = 0.0037 + 0.0040 = 0.0077 dB (within)
agree-full pooled bias band 5 [CHECK, additive]: mean (C++ - ref) +0.0001 dB over 60 case-bands; bound 3 SE_pool + mean l_ref = 0.0037 + 0.0040 = 0.0077 dB (within)
agree-full pooled bias band 6 [CHECK, additive]: mean (C++ - ref) -0.0046 dB over 30 case-bands; bound 3 SE_pool + mean l_ref = 0.0065 + 0.0032 = 0.0096 dB (within)
agree-full pooled bias band 7 [CHECK, additive]: mean (C++ - ref) -0.0046 dB over 30 case-bands; bound 3 SE_pool + mean l_ref = 0.0065 + 0.0031 = 0.0096 dB (within)
All tests passed (13971 assertions in 1 test case)
```

## CI run 42909003931 (d51dde0, 2026-11-10): the three-OS records (the record of record)

Linux `build (linux)` job 130154753751, macOS `build (macos)` 130154753626, Windows `build (windows)` 130154753717. Lines as printed by the Release benchmark step; the macOS job stopped at the detector probe (its calibration SKIPs on Apple silicon: the FZ-off form raises no flag there, fixed in the next push by the guarded-arm IDC form), so macOS carries no pluginval / auval lines from this run; Linux and Windows pluginval strictness 10 ran in their green jobs. The python-tools jobs failed only on the committed validation report (regenerated in the next push).

### Linux

```
05h-records AQ4 AQ10 room                   48000 Hz: R (position-only, builder) 20 ms, full rebuild 182 ms, 2P 21.3 ms; R + 2P 42 ms (100 ms), 2R + 2P 62 ms (700 ms), full + 2P 203 ms (3 s)
05h-records AQ4 AQ10 room                   96000 Hz: R (position-only, builder) 20 ms, full rebuild 395 ms, 2P 10.7 ms; R + 2P 31 ms (100 ms), 2R + 2P 51 ms (700 ms), full + 2P 406 ms (3 s)
05h-records AQ4 cube100_lowalpha0.05_s0.3   48000 Hz: R (position-only, builder) 20 ms, full rebuild 906 ms, 2P 21.3 ms; R + 2P 41 ms (100 ms), 2R + 2P 62 ms (700 ms), full + 2P 927 ms (3 s)
05h-records AQ4 cube100_lowalpha0.05_s0.3   96000 Hz: R (position-only, builder) 20 ms, full rebuild 2119 ms, 2P 10.7 ms; R + 2P 31 ms (100 ms), 2R + 2P 51 ms (700 ms), full + 2P 2130 ms (3 s)
05h-records bounce 100 m cube  48000 Hz: 3-minute offline bounce with the room size stepping 1 m every 5 s (36 rebuilds): 57.0 s wall, ratio to real time 0.32 x
05h-records bounce 100 m cube  96000 Hz: 3-minute offline bounce with the room size stepping 1 m every 5 s (36 rebuilds): 219.9 s wall, ratio to real time 1.22 x
05h-records callback p99.9 at host buffer 64 (1333 us period), 1 concurrent builder at 100 m: p99.9 139 us, max 760 us over 6851 callbacks (10 s)
05h-records callback p99.9 at host buffer 64 (1333 us period), 4 concurrent builders at 100 m: p99.9 156 us, max 757 us over 6750 callbacks (10 s)
05h-records callback p99.9 at host buffer 64 (1333 us period), 8 concurrent builders at 100 m: p99.9 178 us, max 905 us over 6652 callbacks (10 s)
05h-records (iv) AQ10 room                   48000 Hz, 1 instances: load until the last is audible 498 ms; staleness when rebuilding together min 202 median 202 max 202 ms
05h-records (iv) AQ10 room                   48000 Hz, 4 instances: load until the last is audible 2072 ms; staleness when rebuilding together min 212 median 518 max 822 ms
05h-records (iv) AQ10 room                   48000 Hz, 8 instances: load until the last is audible 4149 ms; staleness when rebuilding together min 198 median 879 max 1579 ms
05h-records (iv) AQ10 room                   96000 Hz, 1 instances: load until the last is audible 956 ms; staleness when rebuilding together min 423 median 423 max 423 ms
05h-records (iv) AQ10 room                   96000 Hz, 4 instances: load until the last is audible 3829 ms; staleness when rebuilding together min 424 median 1076 max 1719 ms
05h-records (iv) AQ10 room                   96000 Hz, 8 instances: load until the last is audible 7793 ms; staleness when rebuilding together min 449 median 1969 max 3528 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 instances: load until the last is audible 1265 ms; staleness when rebuilding together min 898 median 898 max 898 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 instances: load until the last is audible 4979 ms; staleness when rebuilding together min 897 median 2272 max 3677 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 instances: load until the last is audible 9932 ms; staleness when rebuilding together min 909 median 4111 max 7379 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 instances: load until the last is audible 2386 ms; staleness when rebuilding together min 1984 median 1984 max 1984 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 instances: load until the last is audible 10494 ms; staleness when rebuilding together min 2138 median 5318 max 8503 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 instances: load until the last is audible 21078 ms; staleness when rebuilding together min 2168 median 9444 max 17827 ms
05h-records quiesce cube100_flutter_fallback   96 kHz: builder rebuild 736 ms; cancel at a random point, 10 runs: wait min 7 median 114 worst 264 ms
05h-records quiesce cube100_flutter_fallback   run  0: cancel at 149 ms of 736 -> waited 170 ms
05h-records quiesce cube100_flutter_fallback   run  1: cancel at 165 ms of 736 -> waited 156 ms
05h-records quiesce cube100_flutter_fallback   run  2: cancel at 660 ms of 736 -> waited 50 ms
05h-records quiesce cube100_flutter_fallback   run  3: cancel at 290 ms of 736 -> waited 34 ms
05h-records quiesce cube100_flutter_fallback   run  4: cancel at 211 ms of 736 -> waited 113 ms
05h-records quiesce cube100_flutter_fallback   run  5: cancel at 130 ms of 736 -> waited 189 ms
05h-records quiesce cube100_flutter_fallback   run  6: cancel at 202 ms of 736 -> waited 115 ms
05h-records quiesce cube100_flutter_fallback   run  7: cancel at 418 ms of 736 -> waited 7 ms
05h-records quiesce cube100_flutter_fallback   run  8: cancel at 299 ms of 736 -> waited 54 ms
05h-records quiesce cube100_flutter_fallback   run  9: cancel at 470 ms of 736 -> waited 264 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  96 kHz: builder rebuild 2035 ms; cancel at a random point, 10 runs: wait min 0 median 59 worst 1184 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  0: cancel at 1577 ms of 2035 -> waited 325 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  1: cancel at 2009 ms of 2035 -> waited 0 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  2: cancel at 1792 ms of 2035 -> waited 103 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  3: cancel at 1293 ms of 2035 -> waited 607 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  4: cancel at 1956 ms of 2035 -> waited 0 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  5: cancel at 622 ms of 2035 -> waited 13 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  6: cancel at 564 ms of 2035 -> waited 14 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  7: cancel at 232 ms of 2035 -> waited 344 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  8: cancel at 2024 ms of 2035 -> waited 0 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  9: cancel at 748 ms of 2035 -> waited 1184 ms
agree-full pooled bias band 3 [CHECK, additive]: mean (C++ - ref) +0.0002 dB over 60 case-bands; bound 3 SE_pool + mean l_ref = 0.0038 + 0.0040 = 0.0078 dB (within)
agree-full pooled bias band 4 [CHECK, additive]: mean (C++ - ref) +0.0000 dB over 60 case-bands; bound 3 SE_pool + mean l_ref = 0.0037 + 0.0040 = 0.0077 dB (within)
agree-full pooled bias band 5 [CHECK, additive]: mean (C++ - ref) +0.0001 dB over 60 case-bands; bound 3 SE_pool + mean l_ref = 0.0037 + 0.0040 = 0.0077 dB (within)
agree-full gated: 330 of 560 AX43 case-bands gated (230 reported, reference pending); 72 of 72 AX45 case-bands gated
agree-full summary: 330 gated AX43 case-bands, 72 gated AX45 case-bands, 230 reported (uncertified), 0 without reference; max |C++ - ref| 0.0460 dB over the gated set; 0 stage-2 runs; 0 failures (N_test 65536)
05h-records pool size 4
05h-records full rebuild dead_booth.json         48000 Hz: min 83 median 83 max 84 ms (3 runs)
05h-records full rebuild dead_booth.json         96000 Hz: min 137 median 140 max 140 ms (3 runs)
05h-records full rebuild living_room.json        48000 Hz: min 94 median 94 max 95 ms (3 runs)
05h-records full rebuild living_room.json        96000 Hz: min 189 median 189 max 198 ms (3 runs)
05h-records full rebuild classroom.json          48000 Hz: min 102 median 102 max 102 ms (3 runs)
05h-records full rebuild classroom.json          96000 Hz: min 203 median 204 max 205 ms (3 runs)
05h-records full rebuild club.json               48000 Hz: min 173 median 174 max 175 ms (3 runs)
05h-records full rebuild club.json               96000 Hz: min 395 median 396 max 397 ms (3 runs)
05h-records full rebuild concert_hall_box.json   48000 Hz: min 190 median 190 max 196 ms (3 runs)
05h-records full rebuild concert_hall_box.json   96000 Hz: min 425 median 425 max 426 ms (3 runs)
05h-records full rebuild stone_box.json          48000 Hz: min 392 median 395 max 395 ms (3 runs)
05h-records full rebuild stone_box.json          96000 Hz: min 916 median 920 max 922 ms (3 runs)
05h-records full rebuild AQ10 room           48000 Hz: min 172 median 172 max 181 ms
05h-records full rebuild AQ10 room           96000 Hz: min 393 median 396 max 396 ms
05h-records full rebuild cube100_flutter_fallback    48000 Hz: min 404 median 405 max 414 ms; transient RSS delta 13 MB (sampled max 59996 kB, RSS before 46596 kB)
05h-records full rebuild cube100_flutter_fallback    96000 Hz: min 703 median 707 max 708 ms; transient RSS delta 46 MB (sampled max 106808 kB, RSS before 59996 kB)
05h-records work ratio cube100_flutter_fallback   e0: realised work / W_scene 0.9347 (W_pilot 3154338, W_final 2547436, W_scene 6100000); achieved SE 0.002 dB; fallback yes
05h-records work ratio cube100_flutter_fallback   e1: realised work / W_scene 0.9347 (W_pilot 3154338, W_final 2547436, W_scene 6100000); achieved SE 0.001 dB; fallback yes
05h-records restore cube100_flutter_fallback   96 kHz with the solve, 10 runs: min 686 median 716 worst 722 ms; 14 x worst 10.11 s (30 s)
05h-records restore gate cube100_flutter_fallback   Linux: strict (recorded 10.59 s <= 29.1 s): 14 x worst 10.11 s <= 30 s
05h-records restore cube100_flutter_fallback   96 kHz contended (another pipeline solving the same room): min 706 median 718 worst 1433 ms (3 runs)
05h-records full rebuild cube100_lowalpha0.05_s0.3   48000 Hz: min 882 median 888 max 895 ms; transient RSS delta 134 MB (sampled max 172464 kB, RSS before 35404 kB)
05h-records full rebuild cube100_lowalpha0.05_s0.3   96000 Hz: min 2115 median 2152 max 2204 ms; transient RSS delta 293 MB (sampled max 335044 kB, RSS before 35404 kB)
05h-records work ratio cube100_lowalpha0.05_s0.3  e0: realised work / W_scene 0.9910 (W_pilot 1696086, W_final 4348889, W_scene 6100000); achieved SE 0.092 dB; fallback no
05h-records work ratio cube100_lowalpha0.05_s0.3  e1: realised work / W_scene 0.9910 (W_pilot 1696086, W_final 4348889, W_scene 6100000); achieved SE 0.075 dB; fallback no
05h-records restore cube100_lowalpha0.05_s0.3  96 kHz with the solve, 10 runs: min 2008 median 2043 worst 2116 ms; 14 x worst 29.62 s (30 s)
05h-records restore gate cube100_lowalpha0.05_s0.3  Linux: LISTED defect (recorded 14 x worst 30.27 s); 14 x worst now 29.62 s; growth bound median 2043 <= 0 ms (BASELINE PENDING: pin this run's median with a CHANGELOG reason; not asserted); WARNING: this entry now passes 30 s, remove it through /fix-plan
05h-records restore cube100_lowalpha0.05_s0.3  96 kHz contended (another pipeline solving the same room): min 2051 median 2130 worst 2134 ms (3 runs)
05h-records full rebuild cube100_lowalpha0.05_s1     48000 Hz: min 897 median 904 max 909 ms; transient RSS delta 116 MB (sampled max 221972 kB, RSS before 102920 kB)
05h-records full rebuild cube100_lowalpha0.05_s1     96000 Hz: min 2131 median 2144 max 2162 ms; transient RSS delta 293 MB (sampled max 384552 kB, RSS before 84912 kB)
05h-records work ratio cube100_lowalpha0.05_s1    e0: realised work / W_scene 0.9859 (W_pilot 1666253, W_final 4347497, W_scene 6100000); achieved SE 0.360 dB; fallback no
05h-records work ratio cube100_lowalpha0.05_s1    e1: realised work / W_scene 0.9859 (W_pilot 1666253, W_final 4347497, W_scene 6100000); achieved SE 0.359 dB; fallback no
05h-records restore cube100_lowalpha0.05_s1    96 kHz with the solve, 10 runs: min 1958 median 2007 worst 2057 ms; 14 x worst 28.80 s (30 s)
05h-records restore gate cube100_lowalpha0.05_s1    Linux: reported set, not gated
05h-records restore cube100_lowalpha0.05_s1    96 kHz contended (another pipeline solving the same room): min 2033 median 2047 worst 4079 ms (3 runs)
probe-detector fs 48000 dead_booth alpha 0.01 at 63 Hz, 0.999 above, s 0.5 (Seat 3): flags FTZ off [operand+underflow], FTZ on [underflow]; IRs bit-identical
```

### macOS

```
05h-records (iv) AQ10 room                   48000 Hz, 1 instances: load until the last is audible 595 ms; staleness when rebuilding together min 202 median 202 max 202 ms
05h-records (iv) AQ10 room                   48000 Hz, 4 instances: load until the last is audible 1998 ms; staleness when rebuilding together min 175 median 427 max 705 ms
05h-records (iv) AQ10 room                   48000 Hz, 8 instances: load until the last is audible 3904 ms; staleness when rebuilding together min 151 median 654 max 1115 ms
05h-records (iv) AQ10 room                   96000 Hz, 1 instances: load until the last is audible 718 ms; staleness when rebuilding together min 284 median 284 max 284 ms
05h-records (iv) AQ10 room                   96000 Hz, 4 instances: load until the last is audible 3029 ms; staleness when rebuilding together min 312 median 784 max 1269 ms
05h-records (iv) AQ10 room                   96000 Hz, 8 instances: load until the last is audible 5920 ms; staleness when rebuilding together min 312 median 1299 max 2320 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 instances: load until the last is audible 1044 ms; staleness when rebuilding together min 672 median 672 max 672 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 instances: load until the last is audible 4054 ms; staleness when rebuilding together min 684 median 1902 max 3012 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 instances: load until the last is audible 7824 ms; staleness when rebuilding together min 750 median 3389 max 6167 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 instances: load until the last is audible 2472 ms; staleness when rebuilding together min 1899 median 1899 max 1899 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 instances: load until the last is audible 9348 ms; staleness when rebuilding together min 1943 median 4918 max 7904 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 instances: load until the last is audible 20444 ms; staleness when rebuilding together min 2242 median 9574 max 16770 ms
agree-full pooled bias band 3 [CHECK, additive]: mean (C++ - ref) +0.0002 dB over 60 case-bands; bound 3 SE_pool + mean l_ref = 0.0038 + 0.0040 = 0.0078 dB (within)
agree-full pooled bias band 4 [CHECK, additive]: mean (C++ - ref) +0.0000 dB over 60 case-bands; bound 3 SE_pool + mean l_ref = 0.0037 + 0.0040 = 0.0077 dB (within)
agree-full pooled bias band 5 [CHECK, additive]: mean (C++ - ref) +0.0001 dB over 60 case-bands; bound 3 SE_pool + mean l_ref = 0.0037 + 0.0040 = 0.0077 dB (within)
agree-full gated: 330 of 560 AX43 case-bands gated (230 reported, reference pending); 72 of 72 AX45 case-bands gated
agree-full summary: 330 gated AX43 case-bands, 72 gated AX45 case-bands, 230 reported (uncertified), 0 without reference; max |C++ - ref| 0.0460 dB over the gated set; 0 stage-2 runs; 0 failures (N_test 65536)
05h-records quiesce cube100_flutter_fallback   96 kHz: builder rebuild 516 ms; cancel at a random point, 10 runs: wait min 0 median 82 worst 205 ms
05h-records quiesce cube100_flutter_fallback   run  0: cancel at 105 ms of 516 -> waited 132 ms
05h-records quiesce cube100_flutter_fallback   run  1: cancel at 116 ms of 516 -> waited 98 ms
05h-records quiesce cube100_flutter_fallback   run  2: cancel at 463 ms of 516 -> waited 0 ms
05h-records quiesce cube100_flutter_fallback   run  3: cancel at 203 ms of 516 -> waited 121 ms
05h-records quiesce cube100_flutter_fallback   run  4: cancel at 148 ms of 516 -> waited 33 ms
05h-records quiesce cube100_flutter_fallback   run  5: cancel at 91 ms of 516 -> waited 100 ms
05h-records quiesce cube100_flutter_fallback   run  6: cancel at 142 ms of 516 -> waited 67 ms
05h-records quiesce cube100_flutter_fallback   run  7: cancel at 293 ms of 516 -> waited 36 ms
05h-records quiesce cube100_flutter_fallback   run  8: cancel at 209 ms of 516 -> waited 22 ms
05h-records quiesce cube100_flutter_fallback   run  9: cancel at 329 ms of 516 -> waited 205 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  96 kHz: builder rebuild 2099 ms; cancel at a random point, 10 runs: wait min 0 median 82 worst 1153 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  0: cancel at 1627 ms of 2099 -> waited 152 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  1: cancel at 2071 ms of 2099 -> waited 0 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  2: cancel at 1848 ms of 2099 -> waited 0 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  3: cancel at 1334 ms of 2099 -> waited 375 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  4: cancel at 2018 ms of 2099 -> waited 0 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  5: cancel at 641 ms of 2099 -> waited 1126 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  6: cancel at 582 ms of 2099 -> waited 11 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  7: cancel at 240 ms of 2099 -> waited 352 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  8: cancel at 2087 ms of 2099 -> waited 0 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  9: cancel at 772 ms of 2099 -> waited 1153 ms
05h-records pool size 3
05h-records full rebuild dead_booth.json         48000 Hz: min 65 median 67 max 71 ms (3 runs)
05h-records full rebuild dead_booth.json         96000 Hz: min 111 median 124 max 126 ms (3 runs)
05h-records full rebuild living_room.json        48000 Hz: min 80 median 82 max 88 ms (3 runs)
05h-records full rebuild living_room.json        96000 Hz: min 157 median 162 max 166 ms (3 runs)
05h-records full rebuild classroom.json          48000 Hz: min 95 median 96 max 117 ms (3 runs)
05h-records full rebuild classroom.json          96000 Hz: min 170 median 197 max 208 ms (3 runs)
05h-records full rebuild club.json               48000 Hz: min 131 median 139 max 152 ms (3 runs)
05h-records full rebuild club.json               96000 Hz: min 283 median 291 max 362 ms (3 runs)
05h-records full rebuild concert_hall_box.json   48000 Hz: min 193 median 193 max 205 ms (3 runs)
05h-records full rebuild concert_hall_box.json   96000 Hz: min 312 median 355 max 357 ms (3 runs)
05h-records full rebuild stone_box.json          48000 Hz: min 290 median 320 max 342 ms (3 runs)
05h-records full rebuild stone_box.json          96000 Hz: min 816 median 856 max 888 ms (3 runs)
05h-records full rebuild AQ10 room           48000 Hz: min 145 median 153 max 165 ms
05h-records full rebuild AQ10 room           96000 Hz: min 289 median 295 max 306 ms
05h-records full rebuild cube100_flutter_fallback    48000 Hz: min 263 median 264 max 287 ms; transient RSS delta 0 MB (sampled max 0 kB, RSS before 0 kB)  [RSS n/a on this OS: recorded, not gated]
05h-records full rebuild cube100_flutter_fallback    96000 Hz: min 494 median 504 max 593 ms; transient RSS delta 0 MB (sampled max 0 kB, RSS before 0 kB)  [RSS n/a on this OS: recorded, not gated]
05h-records work ratio cube100_flutter_fallback   e0: realised work / W_scene 0.9347 (W_pilot 3154338, W_final 2547436, W_scene 6100000); achieved SE 0.002 dB; fallback yes
05h-records work ratio cube100_flutter_fallback   e1: realised work / W_scene 0.9347 (W_pilot 3154338, W_final 2547436, W_scene 6100000); achieved SE 0.001 dB; fallback yes
05h-records restore cube100_flutter_fallback   96 kHz with the solve, 10 runs: min 490 median 528 worst 642 ms; 14 x worst 8.99 s (30 s)
05h-records restore gate cube100_flutter_fallback   macOS: strict (recorded 7.59 s <= 29.1 s): 14 x worst 8.99 s <= 30 s
05h-records restore cube100_flutter_fallback   96 kHz contended (another pipeline solving the same room): min 451 median 486 worst 498 ms (3 runs)
05h-records full rebuild cube100_lowalpha0.05_s0.3   48000 Hz: min 639 median 692 max 747 ms; transient RSS delta 0 MB (sampled max 0 kB, RSS before 0 kB)  [RSS n/a on this OS: recorded, not gated]
05h-records full rebuild cube100_lowalpha0.05_s0.3   96000 Hz: min 1914 median 1928 max 2021 ms; transient RSS delta 0 MB (sampled max 0 kB, RSS before 0 kB)  [RSS n/a on this OS: recorded, not gated]
05h-records work ratio cube100_lowalpha0.05_s0.3  e0: realised work / W_scene 0.9910 (W_pilot 1696086, W_final 4348889, W_scene 6100000); achieved SE 0.092 dB; fallback no
05h-records work ratio cube100_lowalpha0.05_s0.3  e1: realised work / W_scene 0.9910 (W_pilot 1696086, W_final 4348889, W_scene 6100000); achieved SE 0.075 dB; fallback no
05h-records restore cube100_lowalpha0.05_s0.3  96 kHz with the solve, 10 runs: min 1840 median 2106 worst 2669 ms; 14 x worst 37.37 s (30 s)
05h-records restore gate cube100_lowalpha0.05_s0.3  macOS: LISTED defect (recorded 14 x worst 33.40 s); 14 x worst now 37.37 s; growth bound median 2106 <= 0 ms (BASELINE PENDING: pin this run's median with a CHANGELOG reason; not asserted)
05h-records restore cube100_lowalpha0.05_s0.3  96 kHz contended (another pipeline solving the same room): min 1807 median 1921 worst 2040 ms (3 runs)
05h-records full rebuild cube100_lowalpha0.05_s1     48000 Hz: min 731 median 743 max 1101 ms; transient RSS delta 0 MB (sampled max 0 kB, RSS before 0 kB)  [RSS n/a on this OS: recorded, not gated]
05h-records full rebuild cube100_lowalpha0.05_s1     96000 Hz: min 1649 median 1754 max 1784 ms; transient RSS delta 0 MB (sampled max 0 kB, RSS before 0 kB)  [RSS n/a on this OS: recorded, not gated]
05h-records work ratio cube100_lowalpha0.05_s1    e0: realised work / W_scene 0.9859 (W_pilot 1666253, W_final 4347497, W_scene 6100000); achieved SE 0.360 dB; fallback no
05h-records work ratio cube100_lowalpha0.05_s1    e1: realised work / W_scene 0.9859 (W_pilot 1666253, W_final 4347497, W_scene 6100000); achieved SE 0.359 dB; fallback no
05h-records restore cube100_lowalpha0.05_s1    96 kHz with the solve, 10 runs: min 1531 median 1687 worst 1852 ms; 14 x worst 25.92 s (30 s)
05h-records restore gate cube100_lowalpha0.05_s1    macOS: reported set, not gated
05h-records restore cube100_lowalpha0.05_s1    96 kHz contended (another pipeline solving the same room): min 1672 median 1778 worst 1805 ms (3 runs)
05h-records AQ4 AQ10 room                   48000 Hz: R (position-only, builder) 32 ms, full rebuild 138 ms, 2P 21.3 ms; R + 2P 53 ms (100 ms), 2R + 2P 85 ms (700 ms), full + 2P 160 ms (3 s)
05h-records AQ4 AQ10 room                   96000 Hz: R (position-only, builder) 33 ms, full rebuild 293 ms, 2P 10.7 ms; R + 2P 44 ms (100 ms), 2R + 2P 77 ms (700 ms), full + 2P 304 ms (3 s)
05h-records AQ4 cube100_lowalpha0.05_s0.3   48000 Hz: R (position-only, builder) 69 ms, full rebuild 724 ms, 2P 21.3 ms; R + 2P 90 ms (100 ms), 2R + 2P 160 ms (700 ms), full + 2P 745 ms (3 s)
05h-records AQ4 cube100_lowalpha0.05_s0.3   96000 Hz: R (position-only, builder) 73 ms, full rebuild 1744 ms, 2P 10.7 ms; R + 2P 83 ms (100 ms), 2R + 2P 156 ms (700 ms), full + 2P 1755 ms (3 s)
05h-records bounce 100 m cube  48000 Hz: 3-minute offline bounce with the room size stepping 1 m every 5 s (36 rebuilds): 42.1 s wall, ratio to real time 0.23 x
05h-records bounce 100 m cube  96000 Hz: 3-minute offline bounce with the room size stepping 1 m every 5 s (36 rebuilds): 131.8 s wall, ratio to real time 0.73 x
05h-records callback p99.9 at host buffer 64 (1333 us period), 1 concurrent builder at 100 m: p99.9 2212 us, max 2212 us over 961 callbacks (10 s)
05h-records callback p99.9 at host buffer 64 (1333 us period), 4 concurrent builders at 100 m: p99.9 720 us, max 1644 us over 1040 callbacks (10 s)
05h-records callback p99.9 at host buffer 64 (1333 us period), 8 concurrent builders at 100 m: p99.9 1141 us, max 4220 us over 1090 callbacks (10 s)
```

### Windows

```
05h-records (iv) AQ10 room                   48000 Hz, 1 instances: load until the last is audible 555 ms; staleness when rebuilding together min 215 median 215 max 215 ms
05h-records (iv) AQ10 room                   48000 Hz, 4 instances: load until the last is audible 2264 ms; staleness when rebuilding together min 218 median 535 max 853 ms
05h-records (iv) AQ10 room                   48000 Hz, 8 instances: load until the last is audible 4525 ms; staleness when rebuilding together min 219 median 961 max 1714 ms
05h-records (iv) AQ10 room                   96000 Hz, 1 instances: load until the last is audible 1011 ms; staleness when rebuilding together min 441 median 441 max 441 ms
05h-records (iv) AQ10 room                   96000 Hz, 4 instances: load until the last is audible 3976 ms; staleness when rebuilding together min 430 median 1062 max 1712 ms
05h-records (iv) AQ10 room                   96000 Hz, 8 instances: load until the last is audible 8906 ms; staleness when rebuilding together min 557 median 2269 max 3963 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 1 instances: load until the last is audible 1237 ms; staleness when rebuilding together min 884 median 884 max 884 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 4 instances: load until the last is audible 5011 ms; staleness when rebuilding together min 900 median 2225 max 3578 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   48000 Hz, 8 instances: load until the last is audible 11148 ms; staleness when rebuilding together min 1157 median 4443 max 7663 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 1 instances: load until the last is audible 2528 ms; staleness when rebuilding together min 1933 median 1933 max 1933 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 4 instances: load until the last is audible 11543 ms; staleness when rebuilding together min 2515 median 6291 max 9501 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 instances: load until the last is audible 25618 ms; staleness when rebuilding together min 2561 median 10063 max 17185 ms
05h-records pool size 4
05h-records full rebuild dead_booth.json         48000 Hz: min 91 median 93 max 94 ms (3 runs)
05h-records full rebuild dead_booth.json         96000 Hz: min 154 median 158 max 158 ms (3 runs)
05h-records full rebuild living_room.json        48000 Hz: min 107 median 109 max 111 ms (3 runs)
05h-records full rebuild living_room.json        96000 Hz: min 220 median 223 max 223 ms (3 runs)
05h-records full rebuild classroom.json          48000 Hz: min 114 median 116 max 117 ms (3 runs)
05h-records full rebuild classroom.json          96000 Hz: min 232 median 234 max 236 ms (3 runs)
05h-records full rebuild club.json               48000 Hz: min 202 median 202 max 203 ms (3 runs)
05h-records full rebuild club.json               96000 Hz: min 409 median 413 max 418 ms (3 runs)
05h-records full rebuild concert_hall_box.json   48000 Hz: min 220 median 220 max 224 ms (3 runs)
05h-records full rebuild concert_hall_box.json   96000 Hz: min 441 median 442 max 443 ms (3 runs)
05h-records full rebuild stone_box.json          48000 Hz: min 399 median 403 max 406 ms (3 runs)
05h-records full rebuild stone_box.json          96000 Hz: min 881 median 890 max 912 ms (3 runs)
05h-records full rebuild AQ10 room           48000 Hz: min 200 median 202 max 204 ms
05h-records full rebuild AQ10 room           96000 Hz: min 415 median 419 max 421 ms
05h-records full rebuild cube100_flutter_fallback    48000 Hz: min 440 median 441 max 449 ms; transient RSS delta 0 MB (sampled max 0 kB, RSS before 0 kB)  [RSS n/a on this OS: recorded, not gated]
05h-records full rebuild cube100_flutter_fallback    96000 Hz: min 743 median 743 max 747 ms; transient RSS delta 0 MB (sampled max 0 kB, RSS before 0 kB)  [RSS n/a on this OS: recorded, not gated]
05h-records work ratio cube100_flutter_fallback   e0: realised work / W_scene 0.9347 (W_pilot 3154338, W_final 2547436, W_scene 6100000); achieved SE 0.002 dB; fallback yes
05h-records work ratio cube100_flutter_fallback   e1: realised work / W_scene 0.9347 (W_pilot 3154338, W_final 2547436, W_scene 6100000); achieved SE 0.001 dB; fallback yes
05h-records restore cube100_flutter_fallback   96 kHz with the solve, 10 runs: min 746 median 757 worst 762 ms; 14 x worst 10.66 s (30 s)
05h-records restore gate cube100_flutter_fallback   Windows: strict (recorded 9.65 s <= 29.1 s): 14 x worst 10.66 s <= 30 s
05h-records restore cube100_flutter_fallback   96 kHz contended (another pipeline solving the same room): min 756 median 756 worst 762 ms (3 runs)
05h-records full rebuild cube100_lowalpha0.05_s0.3   48000 Hz: min 904 median 907 max 919 ms; transient RSS delta 0 MB (sampled max 0 kB, RSS before 0 kB)  [RSS n/a on this OS: recorded, not gated]
05h-records full rebuild cube100_lowalpha0.05_s0.3   96000 Hz: min 1932 median 1948 max 1973 ms; transient RSS delta 0 MB (sampled max 0 kB, RSS before 0 kB)  [RSS n/a on this OS: recorded, not gated]
05h-records work ratio cube100_lowalpha0.05_s0.3  e0: realised work / W_scene 0.9910 (W_pilot 1696086, W_final 4348889, W_scene 6100000); achieved SE 0.092 dB; fallback no
05h-records work ratio cube100_lowalpha0.05_s0.3  e1: realised work / W_scene 0.9910 (W_pilot 1696086, W_final 4348889, W_scene 6100000); achieved SE 0.075 dB; fallback no
05h-records restore cube100_lowalpha0.05_s0.3  96 kHz with the solve, 10 runs: min 1981 median 2000 worst 2075 ms; 14 x worst 29.04 s (30 s)
05h-records restore gate cube100_lowalpha0.05_s0.3  Windows: strict (recorded 29.04 s <= 29.1 s): 14 x worst 29.04 s <= 30 s
05h-records restore cube100_lowalpha0.05_s0.3  96 kHz contended (another pipeline solving the same room): min 2023 median 2054 worst 2087 ms (3 runs)
05h-records full rebuild cube100_lowalpha0.05_s1     48000 Hz: min 902 median 962 max 965 ms; transient RSS delta 0 MB (sampled max 0 kB, RSS before 0 kB)  [RSS n/a on this OS: recorded, not gated]
05h-records full rebuild cube100_lowalpha0.05_s1     96000 Hz: min 2017 median 2026 max 2116 ms; transient RSS delta 0 MB (sampled max 0 kB, RSS before 0 kB)  [RSS n/a on this OS: recorded, not gated]
05h-records work ratio cube100_lowalpha0.05_s1    e0: realised work / W_scene 0.9859 (W_pilot 1666253, W_final 4347497, W_scene 6100000); achieved SE 0.360 dB; fallback no
05h-records work ratio cube100_lowalpha0.05_s1    e1: realised work / W_scene 0.9859 (W_pilot 1666253, W_final 4347497, W_scene 6100000); achieved SE 0.359 dB; fallback no
05h-records restore cube100_lowalpha0.05_s1    96 kHz with the solve, 10 runs: min 2007 median 2031 worst 2057 ms; 14 x worst 28.80 s (30 s)
05h-records restore gate cube100_lowalpha0.05_s1    Windows: reported set, not gated
05h-records restore cube100_lowalpha0.05_s1    96 kHz contended (another pipeline solving the same room): min 2016 median 2030 worst 2069 ms (3 runs)
05h-records AQ4 AQ10 room                   48000 Hz: R (position-only, builder) 22 ms, full rebuild 203 ms, 2P 21.3 ms; R + 2P 43 ms (100 ms), 2R + 2P 65 ms (700 ms), full + 2P 224 ms (3 s)
05h-records AQ4 AQ10 room                   96000 Hz: R (position-only, builder) 22 ms, full rebuild 414 ms, 2P 10.7 ms; R + 2P 33 ms (100 ms), 2R + 2P 55 ms (700 ms), full + 2P 425 ms (3 s)
05h-records AQ4 cube100_lowalpha0.05_s0.3   48000 Hz: R (position-only, builder) 22 ms, full rebuild 890 ms, 2P 21.3 ms; R + 2P 43 ms (100 ms), 2R + 2P 65 ms (700 ms), full + 2P 911 ms (3 s)
05h-records AQ4 cube100_lowalpha0.05_s0.3   96000 Hz: R (position-only, builder) 22 ms, full rebuild 1924 ms, 2P 10.7 ms; R + 2P 33 ms (100 ms), 2R + 2P 55 ms (700 ms), full + 2P 1935 ms (3 s)
05h-records bounce 100 m cube  48000 Hz: 3-minute offline bounce with the room size stepping 1 m every 5 s (36 rebuilds): 55.7 s wall, ratio to real time 0.31 x
05h-records bounce 100 m cube  96000 Hz: 3-minute offline bounce with the room size stepping 1 m every 5 s (36 rebuilds): 204.2 s wall, ratio to real time 1.13 x
05h-records callback p99.9 at host buffer 64 (1333 us period), 1 concurrent builder at 100 m: p99.9 277 us, max 1566 us over 3333 callbacks (10 s)
05h-records callback p99.9 at host buffer 64 (1333 us period), 4 concurrent builders at 100 m: p99.9 197 us, max 877 us over 3261 callbacks (10 s)
05h-records callback p99.9 at host buffer 64 (1333 us period), 8 concurrent builders at 100 m: p99.9 268 us, max 1294 us over 3161 callbacks (10 s)
05h-records quiesce cube100_flutter_fallback   96 kHz: builder rebuild 755 ms; cancel at a random point, 10 runs: wait min 3 median 137 worst 261 ms
05h-records quiesce cube100_flutter_fallback   run  0: cancel at 153 ms of 755 -> waited 199 ms
05h-records quiesce cube100_flutter_fallback   run  1: cancel at 169 ms of 755 -> waited 177 ms
05h-records quiesce cube100_flutter_fallback   run  2: cancel at 677 ms of 755 -> waited 69 ms
05h-records quiesce cube100_flutter_fallback   run  3: cancel at 297 ms of 755 -> waited 55 ms
05h-records quiesce cube100_flutter_fallback   run  4: cancel at 216 ms of 755 -> waited 135 ms
05h-records quiesce cube100_flutter_fallback   run  5: cancel at 134 ms of 755 -> waited 215 ms
05h-records quiesce cube100_flutter_fallback   run  6: cancel at 208 ms of 755 -> waited 140 ms
05h-records quiesce cube100_flutter_fallback   run  7: cancel at 429 ms of 755 -> waited 3 ms
05h-records quiesce cube100_flutter_fallback   run  8: cancel at 306 ms of 755 -> waited 49 ms
05h-records quiesce cube100_flutter_fallback   run  9: cancel at 482 ms of 755 -> waited 261 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  96 kHz: builder rebuild 1974 ms; cancel at a random point, 10 runs: wait min 0 median 151 worst 1229 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  0: cancel at 1530 ms of 1974 -> waited 435 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  1: cancel at 1948 ms of 1974 -> waited 20 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  2: cancel at 1738 ms of 1974 -> waited 225 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  3: cancel at 1254 ms of 1974 -> waited 702 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  4: cancel at 1898 ms of 1974 -> waited 70 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  5: cancel at 603 ms of 1974 -> waited 12 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  6: cancel at 547 ms of 1974 -> waited 77 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  7: cancel at 225 ms of 1974 -> waited 384 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  8: cancel at 1963 ms of 1974 -> waited 0 ms
05h-records quiesce cube100_lowalpha0.05_s0.3  run  9: cancel at 726 ms of 1974 -> waited 1229 ms
agree-full pooled bias band 3 [CHECK, additive]: mean (C++ - ref) +0.0002 dB over 60 case-bands; bound 3 SE_pool + mean l_ref = 0.0038 + 0.0040 = 0.0078 dB (within)
agree-full pooled bias band 4 [CHECK, additive]: mean (C++ - ref) +0.0000 dB over 60 case-bands; bound 3 SE_pool + mean l_ref = 0.0037 + 0.0040 = 0.0077 dB (within)
agree-full pooled bias band 5 [CHECK, additive]: mean (C++ - ref) +0.0001 dB over 60 case-bands; bound 3 SE_pool + mean l_ref = 0.0037 + 0.0040 = 0.0077 dB (within)
agree-full gated: 330 of 560 AX43 case-bands gated (230 reported, reference pending); 72 of 72 AX45 case-bands gated
agree-full summary: 330 gated AX43 case-bands, 72 gated AX45 case-bands, 230 reported (uncertified), 0 without reference; max |C++ - ref| 0.0460 dB over the gated set; 0 stage-2 runs; 0 failures (N_test 65536)
probe-detector fs 48000 dead_booth alpha 0.01 at 63 Hz, 0.999 above, s 0.5 (Seat 3): flags FTZ off [operand+underflow], FTZ on [underflow]; IRs bit-identical
```


## Final reference extension (commit 45565ee; local run `agree_full7.log`, Linux, Release, `[agree-full]`)

The last `hybrid_fast` references of the session landed (W2 both emitters at 2.5 / 1.25 m; the CS-NW+
emitter-1 placements and the 0.3 m wall case; the emitter-wall case): all 28 AX43 cases now hold the
1.25 m rung, 80 case-bands promoted to gated through `update_goldens.py --extend` (CHANGELOG reason,
`phase05h_hybrid_references.provenance.json`). Pinned in `test_diffuse_agreement.cpp`: `kGatedAx43 = 410`,
`kGatedAx45 = 72`. The suite on the extended set: "All tests passed (14132 assertions in 1 test case)";
0 failures, 0 stage-2 runs, max |C++ − ref| 0.0460 dB over the gated set (N_test 65536). The one
case-band nearest the bound, `W1_listener_corner_0.1_e0` band 4, C++ − ref −0.039 dB (SE 0.0089 dB, z = dev/SE
−4.38 as a record, ℓ_ref 0.628 %), is inside the gate (|C++ − ref| ≤ τ 0.25 dB at the pre-registered N,
where z_FW·SE ≤ τ − ℓ_ref) and inside AX46's 1 %; it is read with that reference's ℓ_ref, not as an
estimator bias (the additive pooled check carries it). What remains reported is the
BRAS pairs' outer bands (63, 125, 250 Hz; 4, 8 kHz: 150 case-bands), phase-05i scope 1.

```
agree-full pooled bias band 0 [CHECK, additive]: mean (C++ - ref) -0.0051 dB over 40 case-bands; bound 3 SE_pool + mean l_ref = 0.0055 + 0.0039 = 0.0094 dB (within)
agree-full pooled bias band 0 [record, per reference room, z']: mean over 23 rooms -0.224 (3/sqrt(M_rooms) 0.626); rooms +/- 7 / 16
agree-full pooled bias band 1 [CHECK, additive]: mean (C++ - ref) -0.0053 dB over 40 case-bands; bound 3 SE_pool + mean l_ref = 0.0054 + 0.0041 = 0.0095 dB (within)
agree-full pooled bias band 1 [record, per reference room, z']: mean over 23 rooms -0.229 (3/sqrt(M_rooms) 0.626); rooms +/- 7 / 16
agree-full pooled bias band 2 [CHECK, additive]: mean (C++ - ref) -0.0054 dB over 40 case-bands; bound 3 SE_pool + mean l_ref = 0.0054 + 0.0042 = 0.0096 dB (within)
agree-full pooled bias band 2 [record, per reference room, z']: mean over 23 rooms -0.234 (3/sqrt(M_rooms) 0.626); rooms +/- 7 / 16
agree-full pooled bias band 3 [CHECK, additive]: mean (C++ - ref) -0.0009 dB over 70 case-bands; bound 3 SE_pool + mean l_ref = 0.0034 + 0.0046 = 0.0080 dB (within)
agree-full pooled bias band 3 [record, per reference room, z']: mean over 26 rooms -0.139 (3/sqrt(M_rooms) 0.588); rooms +/- 10 / 16
agree-full pooled bias band 4 [CHECK, additive]: mean (C++ - ref) -0.0011 dB over 70 case-bands; bound 3 SE_pool + mean l_ref = 0.0034 + 0.0046 = 0.0080 dB (within)
agree-full pooled bias band 4 [record, per reference room, z']: mean over 26 rooms -0.139 (3/sqrt(M_rooms) 0.588); rooms +/- 11 / 15
agree-full pooled bias band 5 [CHECK, additive]: mean (C++ - ref) -0.0012 dB over 70 case-bands; bound 3 SE_pool + mean l_ref = 0.0034 + 0.0046 = 0.0080 dB (within)
agree-full pooled bias band 5 [record, per reference room, z']: mean over 26 rooms -0.137 (3/sqrt(M_rooms) 0.588); rooms +/- 11 / 15
agree-full pooled bias band 6 [CHECK, additive]: mean (C++ - ref) -0.0056 dB over 40 case-bands; bound 3 SE_pool + mean l_ref = 0.0052 + 0.0046 = 0.0098 dB (within)
agree-full pooled bias band 6 [record, per reference room, z']: mean over 23 rooms -0.226 (3/sqrt(M_rooms) 0.626); rooms +/- 8 / 15
agree-full pooled bias band 7 [CHECK, additive]: mean (C++ - ref) -0.0057 dB over 40 case-bands; bound 3 SE_pool + mean l_ref = 0.0052 + 0.0046 = 0.0098 dB (within)
agree-full pooled bias band 7 [record, per reference room, z']: mean over 23 rooms -0.222 (3/sqrt(M_rooms) 0.626); rooms +/- 8 / 15
agree-full gated: 410 of 560 AX43 case-bands gated (150 reported, reference pending); 72 of 72 AX45 case-bands gated
agree-full summary: 410 gated AX43 case-bands, 72 gated AX45 case-bands, 150 reported (uncertified), 0 without reference; max |C++ - ref| 0.0460 dB over the gated set; 0 stage-2 runs; 0 failures (N_test 65536)
```

The catch per band (3·SE_pool + mean ℓ_ref): 0.0094–0.0096 dB at 63–250 Hz over 40 case-bands, 0.0080 dB at 500 Hz–2 kHz over 70, 0.0098 dB at 4–8 kHz over 40; |mean (C++ − ref)| 0.0051–0.0057 dB in the outer bands and 0.0009–0.0012 dB at 500 Hz–2 kHz; 23 reference rooms in the outer bands and 26 at 500 Hz–2 kHz; no room with |mean z′| > 3 (worst −2.06, room 14, band 7).

## The AArch64 arm of the FTZ test: the two macOS observations (K-c4)

- CI run 42909003931 (d51dde0), `build (macos)`: the `[probe-denormals-detector]` probe SKIPped at its
  calibration step (`1e-310 × 1.0` with FZ off raised no cumulative flag on the Apple-silicon runner: IDC
  needs FZ = 1, and an exact product raises no UFC); the job failed on Catch2's all-skipped exit 4. ca6263b
  read that as "no cumulative flag with FZ off" and moved the `[pipeline]` assertion to IDC in the guarded arm.
- CI run 42921348351 (335fdbb), `build (macos)`: that form failed (`REQUIRE(flagsOn.operand)` false). The
  named scene printed `flags FTZ off [underflow], FTZ on [underflow]; IRs bit-identical`: UFC is raised in
  both arms on the caller's thread, IDC in neither (the denormal operands are consumed on the pool worker,
  under its own guard). That is the pattern decision D-H3 (c) wrote for AArch64 (decider file 20 L183 (1):
  UFC in the FZ-off arm, IDC | UFC in the FZ-on arm), so the test now asserts exactly that form, with the
  calibration of file 20 L183 (3) (IDC under FZ = 1 for the operand, UFC for the underflow; SKIP on failure).
  Linux x86-64, same test (local, Debug): `FTZ off [operand+underflow], FTZ on [underflow]; IRs bit-identical
  (calibration: denormal operand without the guard yes, underflow without the guard yes, operand flag under
  the guard no)`; the probe's calibration line reads the same.

## CI run 42924781618 (2026-11-11, on 03213e7; the final run: `ci ok` green on Linux, macOS, Windows) and nightly 42924784861 (green)

Jobs `build (linux)` 130208649120, `build (macos)` 130208648898, `build (windows)` 130208648915. The head
a9d8313 carries the same CI fingerprint (prose only after 03213e7). Debug ctest: 223 / 223 on each OS (the
FTZ test #112 in D-H3 (c)'s per-architecture form passes on all three; the D5 golden #31; the tracer #124).
Release benchmark step: `agree-full gated: 410 of 560 AX43 case-bands gated (150 reported, reference
pending); 72 of 72 AX45 case-bands gated`; `agree-full summary: … max |C++ - ref| 0.0460 dB over the gated
set; 0 stage-2 runs; 0 failures (N_test 65536)` on each OS. Detector probe calibration: Linux / Windows
"denormal operand without the guard yes, underflow without the guard yes, operand flag under the guard no";
macOS "denormal operand without the guard no, underflow without the guard yes, operand flag under the guard
yes" (the AArch64 pattern of the section above). pluginval strictness 10 passed on the three OSes
(artifacts `pluginval-linux/macos/windows`); auval "AU VALIDATION SUCCEEDED" (macOS). Artifacts:
`listening-pack` (236 MB, `phase-05h/` inside), `SpatialScene-linux/macos/windows`.

Restore gate (`kGateRegister`, baselines 2 043 / 2 106 ms):

```
Linux  : 96 kHz with the solve, 10 runs: min 1961 median 2092 worst 2155 ms; 14 x worst 30.18 s (30 s) -> LISTED defect (recorded 30.27 s); growth bound median 2092 <= 2247 ms
macOS  : 96 kHz with the solve, 10 runs: min 1665 median 1849 worst 2231 ms; 14 x worst 31.23 s (30 s) -> LISTED defect (recorded 33.40 s); growth bound median 1849 <= 2317 ms
Windows: 96 kHz with the solve, 10 runs: min 2011 median 2056 worst 2107 ms; 14 x worst 29.50 s (30 s) -> strict (recorded 29.04 s <= 29.1 s): 29.50 s <= 30 s
contended (another pipeline solving the same room), 3 runs: Linux min 2095 median 2098 worst 4174 ms; macOS min 1794 median 2058 worst 2266 ms; Windows min 2021 median 2055 worst 2101 ms
```

The Linux listed entry did not pass 30 s on this run (30.18 s; it did on run 42909003931 at 29.62 s), so the
§5 (c) warning did not print and the entry stays listed; its removal is phase-05i scope 3's call. The gated
cube's contended restore on Linux shows a second worst-of-3 outlier above 3 s (4.174 s; the other two runs
2.095–2.098 s): finding F-a (decider file 36 R2) recurs on the Linux runner, same remedy.

AX38 (iv), 8 instances, load until the last is audible (ms) / staleness when rebuilding together (min, median, max; ms):

```
                               Linux                      macOS                      Windows
AQ10 room 48 kHz          4175 / 197 916 1662         2887 / 137 594 1114         4464 / 211 939 1666
AQ10 room 96 kHz          7596 / 447 2041 3799        6160 / 371 1487 2539        8290 / 481 2111 3697
100 m low-alpha 48 kHz    9924 / 946 4256 7984        9060 / 874 3718 6924       10329 / 954 4132 7350
100 m low-alpha 96 kHz   21357 / 2100 10519 19773    20373 / 2396 9973 17316     24440 / 2604 10223 17601
```

Consistent with run 42909003931 (21.1 / 20.4 / 25.6 s at 8 × 100 m / 96 kHz): the R3 answer stands on this
run too.

## AX46 in the file 42 form (local Release run `agree_full8.log`, 2026-11-11; the test edits of QB/QC, before CI run 8)

```
agree-full AX46 class near_wall  band 0: mean deviation -0.136% (SE_prop 0.078%, SE_emp 0.139%, 9 cases, l_ref mean 0.162% max 0.474%) evaluated
agree-full AX46 class near_wall  band 1: mean deviation -0.157% (SE_prop 0.077%, SE_emp 0.145%, 9 cases, l_ref mean 0.181% max 0.532%) evaluated
agree-full AX46 class near_wall  band 2: mean deviation -0.169% (SE_prop 0.076%, SE_emp 0.148%, 9 cases, l_ref mean 0.192% max 0.567%) evaluated
agree-full AX46 class near_wall  band 3: mean deviation -0.181% (SE_prop 0.075%, SE_emp 0.152%, 9 cases, l_ref mean 0.203% max 0.599%) evaluated
agree-full AX46 class near_wall  band 4: mean deviation -0.191% (SE_prop 0.074%, SE_emp 0.154%, 9 cases, l_ref mean 0.212% max 0.628%) evaluated
agree-full AX46 class near_wall  band 5: mean deviation -0.201% (SE_prop 0.074%, SE_emp 0.157%, 9 cases, l_ref mean 0.221% max 0.653%) evaluated
agree-full AX46 class near_wall  band 6: mean deviation -0.210% (SE_prop 0.073%, SE_emp 0.159%, 9 cases, l_ref mean 0.229% max 0.675%) evaluated
agree-full AX46 class near_wall  band 7: mean deviation -0.217% (SE_prop 0.072%, SE_emp 0.160%, 9 cases, l_ref mean 0.236% max 0.694%) evaluated
agree-full AX46 class bras       band 0: not evaluated (reference pending)
agree-full AX46 class bras       band 1: not evaluated (reference pending)
agree-full AX46 class bras       band 2: not evaluated (reference pending)
agree-full AX46 class bras       band 3: mean deviation +0.117% (SE_prop 0.029%, SE_emp 0.031%, 30 cases, l_ref mean 0.113% max 0.367%) evaluated
agree-full AX46 class bras       band 4: mean deviation +0.110% (SE_prop 0.028%, SE_emp 0.029%, 30 cases, l_ref mean 0.109% max 0.360%) evaluated
agree-full AX46 class bras       band 5: mean deviation +0.110% (SE_prop 0.028%, SE_emp 0.029%, 30 cases, l_ref mean 0.109% max 0.351%) evaluated
agree-full AX46 class bras       band 6: not evaluated (reference pending)
agree-full AX46 class bras       band 7: not evaluated (reference pending)
agree-full AX46 band 0: mean of the evaluated class means -0.134% (pooled over 4 of 6 classes; never a bare 'bias <= 1 %')
agree-full AX46 band 1: mean of the evaluated class means -0.140% (pooled over 4 of 6 classes; never a bare 'bias <= 1 %')
agree-full AX46 band 2: mean of the evaluated class means -0.144% (pooled over 4 of 6 classes; never a bare 'bias <= 1 %')
agree-full AX46 band 3: mean of the evaluated class means -0.081% (pooled over 4 of 6 classes; never a bare 'bias <= 1 %')
agree-full AX46 band 4: mean of the evaluated class means -0.085% (pooled over 4 of 6 classes; never a bare 'bias <= 1 %')
agree-full AX46 band 5: mean of the evaluated class means -0.087% (pooled over 4 of 6 classes; never a bare 'bias <= 1 %')
agree-full AX46 band 6: mean of the evaluated class means -0.155% (pooled over 4 of 6 classes; never a bare 'bias <= 1 %')
agree-full AX46 band 7: mean of the evaluated class means -0.158% (pooled over 4 of 6 classes; never a bare 'bias <= 1 %')
agree-full gated: 410 of 560 AX43 case-bands gated (150 reported, reference pending); 72 of 72 AX45 case-bands gated
All tests passed (14141 assertions in 1 test case)
```

Six classes: the BRAS pairs evaluated at 500 Hz–2 kHz (mean +0.110…+0.117 %, SE_prop 0.028–0.029 %, 30 cases); the near-wall class evaluated in all eight bands (SE_prop 0.072–0.078 %, mean ℓ_ref 0.16–0.24 %; means −0.14…−0.22 %; no heterogeneity label: |mean| + 3·SE_emp ≤ 0.70 %); reference and absorbing as before; small "reference pending"; the 100 m class the tracer line; "pooled over 4 of 6 classes". 14141 assertions passed, 410 / 560 and 72 / 72 unchanged.

## CI run 42935789745 (2026-11-11, on b8b3c6d: the review-39 test forms; `ci ok` green on Linux, macOS, Windows) and nightly 42935793376 (green)

Jobs `build (linux)` 130245491714, `build (macos)` 130245491902, `build (windows)` 130245491738; `python tools` 130245491769 / 130245491771 / 130245491821. The head after it (e71bb88 and the prose commits) has the same CI fingerprint. Debug ctest 223 / 223 on each OS. Release benchmark step on each OS: `agree-full gated: 410 of 560 … 72 of 72`, 0 failures; the AX46 six-class lines identical on the three OSes (near-wall evaluated in all eight bands, SE_prop 0.072–0.078 %; BRAS +0.110…+0.117 % at 500 Hz–2 kHz; "pooled over 4 of 6 classes"; no heterogeneity label). The open_field check at the validation N 2^23 passes on the three OSes with identical numbers (4–8 kHz: −0.019 / −0.020 dB and +0.005 dB, SE 0.073 / 0.076 dB, z −0.27 / +0.06; s 0.4 = s 0.5). pluginval strictness 10 on three OSes and auval green; artifacts as in run 7 (listening-pack 236 MB).

**QA's 10 min trigger fired on Linux:** the two 2^23 renders took 386 + 386 s = 12.9 min on the Linux runner (macOS 227 + 246 s = 7.9 min; Windows 265 + 265 s = 8.8 min; from the job logs' timestamps); the python jobs went from 10.5 / 10.7 / 10.1 min (run 7) to 22.1 / 16.6 / 16.6 min. Returned to the board with Seat 5 convened (file 47).

Restore gate (`kGateRegister`) and the (iv) 8-instance line, run 8:

```
05h-records restore cube100_lowalpha0.05_s0.3  96 kHz with the solve, 10 runs: min 1586 median 1666 worst 1736 ms; 14 x worst 24.31 s (30 s)
05h-records restore cube100_lowalpha0.05_s0.3  96 kHz contended (another pipeline solving the same room): min 1706 median 1715 worst 1757 ms (3 runs)
05h-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 instances: load until the last is audible 16535 ms; staleness when rebuilding together min 1653 median 7687 max 14
05h-records restore cube100_lowalpha0.05_s0.3  96 kHz with the solve, 10 runs: min 1768 median 1887 worst 2265 ms; 14 x worst 31.71 s (30 s)
05h-records restore cube100_lowalpha0.05_s0.3  96 kHz contended (another pipeline solving the same room): min 1890 median 1934 worst 2051 ms (3 runs)
05h-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 instances: load until the last is audible 19139 ms; staleness when rebuilding together min 1928 median 8114 max 14
05h-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 instances: load until the last is audible 20187 ms; staleness when rebuilding together min 2029 median 8853 max 15
05h-records restore cube100_lowalpha0.05_s0.3  96 kHz with the solve, 10 runs: min 1898 median 1926 worst 2041 ms; 14 x worst 28.57 s (30 s)
05h-records restore cube100_lowalpha0.05_s0.3  96 kHz contended (another pipeline solving the same room): min 1798 median 1850 worst 1870 ms (3 runs)
05h-records restore gate cube100_lowalpha0.05_s0.3  Linux: LISTED defect (recorded 14 x worst 30.27 s); 14 x worst now 24.31 s; growth bound median 1666 <= 2247 ms; WARNING: this entry now passes 30 s, remove it through /fix-plan
05h-records restore gate cube100_lowalpha0.05_s0.3  macOS: LISTED defect (recorded 14 x worst 33.40 s); 14 x worst now 31.71 s; growth bound median 1887 <= 2317 ms
05h-records restore gate cube100_lowalpha0.05_s0.3  Windows: strict (recorded 29.04 s <= 29.1 s): 14 x worst 28.57 s <= 30 s
```

The Linux listed entry passed 30 s again on this run (24.31 s; 29.62 / 30.18 / 24.31 s over the three runs): the (c) warning printed; its removal stays phase-05i scope 3's call. The contended restore shows no outlier above 3 s on this run.

## CI run 42942694523 (2026-11-11, on cb7effb: the `open-field-validation` job) and nightly 42942697249 (green)

32 of 33 jobs green; `build (windows)` (job 130268111168) failed the strict restore gate at the gated low-α cube on a slow runner: `14 x worst 36.73 s` (min 2476 median 2589 worst 2624 ms) against 29.04 / 29.50 / 28.57 s on the three earlier green runs; the restore, flutter and full-rebuild records of that run 25–30 % slower (the flutter restore 13.15 s against 10.66 s on run 42909003931; the low-α full rebuild 2 555 ms against 1 948–2 026 ms; the (iv) 8-instance load 25.4 s inside its earlier 24.4–25.6 s). Applied under D-H1 (v)(d) (no re-run): the Windows entry listed with that run's median as its baseline (file 53; `kGateRegister`; CHANGELOG). The new job: `open-field validation` 11.8 / 10.2 / 14.3 min on Linux / macOS / Windows (the 2^23 cases identical to run 42935789745: 4–8 kHz −0.020 / +0.005 dB, 3·SE ≤ 0.229 dB); the python jobs back to 7.2–8.9 min; `ci ok` wall clock 49.2 min, set by `build (windows)` (49.0 min on the slow runner; `build (macos)` 33.4, `build (linux)` 32.8).

```
run 9 ci ok wall clock: 49.2 min
  49.0 min  build (windows)
  33.4 min  build (macos)
  32.8 min  build (linux)
  14.3 min  open-field validation (windows)
  12.3 min  tail gates (windows, living_room)
  12.2 min  tail gates (macos, stone_box)
  11.8 min  open-field validation (linux)
  11.4 min  tail gates (macos, concert_hall_box)
  11.0 min  tail gates (macos, classroom)
  14.3 min  open-field validation (windows)
  11.8 min  open-field validation (linux)
  10.2 min  open-field validation (macos)
   8.9 min  python tools (windows)
   7.2 min  python tools (macos)
```

## The RG-1 gate form, local run (Release, this 4-core Linux box while other work ran; 2026-11-11; `records_rg1.log`)

```
05h-records work pin cube100_flutter_fallback   unit decay 377517 samples (pinned 377517); synthesis FFT size 524288 (pinned 524288)
05h-records solve cube100_flutter_fallback   shipping rule, median of 5: 102.8 ms; 9.01 ns per image evaluation over W_pilot + W_final 11403548 (print, RG-1)
05h-records restore gate cube100_flutter_fallback   Linux: strict (recorded 10.59 s <= 29.1 s): 14 x worst 14.98 s <= 30 s
05h-records work pin cube100_lowalpha0.05_s0.3  unit decay 1152000 samples (pinned 1152000); synthesis FFT size 2097152 (pinned 2097152)
05h-records solve cube100_lowalpha0.05_s0.3  shipping rule, median of 5: 63.7 ms; 5.27 ns per image evaluation over W_pilot + W_final 12089950 (print, RG-1)
05h-records restore gate cube100_lowalpha0.05_s0.3  Linux: LISTED defect (recorded 14 x worst 30.27 s); 14 x worst now 49.36 s; WARNING OVER30S (printed, not asserted on hosted runners); growth bound asserted in-window after the scene loop (RG-1)
05h-records restore gate cube100_lowalpha0.05_s1    Linux: reported set, not gated
05h-records GATE os=Linux scene=cube100_flutter_fallback x14worst=14.98 median=997 fullRebuildMedian=1045 solveMedianMs=102.8 nsPerEval=9.01 status=asserted(30s) flutterRef=701 flutterDev=+42.2%
05h-records GATE os=Linux scene=cube100_lowalpha0.05_s0.3 ratio=3.206 ratioWarnAt=3.660 solveMedianMs=63.7 nsPerEval=5.27 x14worst=49.36 median=3196 growthBound=2275 fullRebuildMedian=3067 status=not-evaluated(runner) warnings=GROWTH OVER30S 
All tests passed (33 assertions in 2 test cases)
```

On a machine 42 % slower than the flutter reference the form behaves as decided: the work pins and the flutter strict 30 s line are asserted (14.98 s), the low-α entry's growth bound is `not-evaluated(runner)` with its GROWTH and OVER30S warnings printed, the ratio 3.21 is under the 3.66 warning line, the solve medians (63.7 / 102.8 ms; 5.27 / 9.01 ns per evaluation over W_pilot + W_final of both emitters) are printed; 33 assertions passed. (The probe `[probe-restore-split]` now prints the filterbank half-length 15 697 and the synthesis FFT sizes 2 097 152 / 524 288 that the work pins hold.)

## CI run 42954077281 (2026-11-11, on b83c49d: the pre-RG-1 register form; `ci ok` green on Linux, macOS, Windows) and nightly 42954079834 (green)

The runners were at normal speed this time: every listed entry inside its bound. It changes nothing in file 56's matter (two of the previous five runs were red on identical code; RG-1 decides the form) but it is the branch's last green `ci ok` before the RG-1 commit.

```
05h-records restore cube100_flutter_fallback   96 kHz with the solve, 10 runs: min 568 median 583 worst 598 ms; 14 x worst 8.38 s (30 s)
05h-records restore gate cube100_flutter_fallback   Linux: strict (recorded 10.59 s <= 29.1 s): 14 x worst 8.38 s <= 30 s
05h-records restore cube100_lowalpha0.05_s0.3  96 kHz with the solve, 10 runs: min 1755 median 1879 worst 1986 ms; 14 x worst 27.81 s (30 s)
05h-records restore gate cube100_lowalpha0.05_s0.3  Linux: LISTED defect (recorded 14 x worst 30.27 s); 14 x worst now 27.81 s; growth bound median 1879 <= 2247 ms; WARNING: this entry now passes 30 s,
05h-records restore cube100_flutter_fallback   96 kHz with the solve, 10 runs: min 462 median 501 worst 586 ms; 14 x worst 8.20 s (30 s)
05h-records restore gate cube100_flutter_fallback   macOS: strict (recorded 7.59 s <= 29.1 s): 14 x worst 8.20 s <= 30 s
05h-records restore cube100_lowalpha0.05_s0.3  96 kHz with the solve, 10 runs: min 1715 median 1967 worst 2122 ms; 14 x worst 29.70 s (30 s)
05h-records restore gate cube100_lowalpha0.05_s0.3  macOS: LISTED defect (recorded 14 x worst 33.40 s); 14 x worst now 29.70 s; growth bound median 1967 <= 2317 ms; WARNING: this entry now passes 30 s,
05h-records restore cube100_flutter_fallback   96 kHz with the solve, 10 runs: min 477 median 488 worst 530 ms; 14 x worst 7.43 s (30 s)
05h-records restore gate cube100_flutter_fallback   Windows: strict (recorded 9.65 s <= 29.1 s): 14 x worst 7.43 s <= 30 s
05h-records restore cube100_lowalpha0.05_s0.3  96 kHz with the solve, 10 runs: min 1317 median 1341 worst 1428 ms; 14 x worst 19.99 s (30 s)
05h-records restore gate cube100_lowalpha0.05_s0.3  Windows: LISTED defect (recorded 14 x worst 36.73 s); 14 x worst now 19.99 s; growth bound median 1341 <= 2848 ms; WARNING: this entry now passes 30 
run 11 ci ok wall clock 45.0 min; longest: build (linux) 33.0, build (macos) 32.8, build (windows) 32.6, tail gates (macos, stone_box) 12.0, ASan + UBSan (linux) 11.7
```
