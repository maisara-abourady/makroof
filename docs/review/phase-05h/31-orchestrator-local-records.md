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
