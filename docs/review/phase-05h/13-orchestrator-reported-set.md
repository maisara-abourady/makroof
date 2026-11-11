# Orchestrator — the AX43 reported set on the C++ shipping rule (2026-11-10, local Release, provisional W_max 3.05 M, n\*_max 1 024)

Reported, not gated (AX43; phase-05h scope 4 "before the goldens"). Test `records: the AX43 reported set` (`tests/unit/
test_diffuse_records.cpp`, `[.][benchmark][diffuse-reported-set]`). Layouts 4/5 at s = 1 with Table 5.2's rigid faces at the
contract minimum α 0.01 (the references use 0); listener / emitter placements as the prototype's C12/C13 (0.1 m from the
faces; both_corner = listener (0.1, 0.1, 0.1), emitter 0 (19.9, 29.9, 9.9)); W1, club and living_room both-near at 0.1 / 0.3 /
0.5 m. The run stopped at W1 both_corner's cap-flag assertion (D-H3 (d)); the club / living_room rows follow once it is read.

```
05h-reported layout4_s1/listener_wall     n* 384 N 320 N_cap 320 cap hit 1 floor truncated 1 pilot floor 1 pilot shipped 0 | e0 SE 0.657 dB VOV_union 0.030 both-near 0 U 1 | e1 SE 0.690 dB VOV_union 0.038 both-near 0 U 1
05h-reported layout4_s1/listener_edge     n* 320 N 192 N_cap 192 cap hit 1 floor truncated 1 pilot floor 1 pilot shipped 0 | e0 SE 0.925 dB VOV_union 0.040 both-near 0 U 1 | e1 SE 0.968 dB VOV_union 0.038 both-near 0 U 1
05h-reported layout4_s1/listener_corner   n* 256 N 128 N_cap 128 cap hit 1 floor truncated 1 pilot floor 1 pilot shipped 0 | e0 SE 0.919 dB VOV_union 0.082 both-near 0 U 1 | e1 SE 1.015 dB VOV_union 0.147 both-near 0 U 1
05h-reported layout4_s1/emitter_wall      n* 448 N 320 N_cap 320 cap hit 1 floor truncated 1 pilot floor 1 pilot shipped 0 | e0 SE 0.708 dB VOV_union 0.034 both-near 0 U 1 | e1 SE 0.476 dB VOV_union 0.019 both-near 0 U 1
05h-reported layout4_s1/both_wall         n* 640 N 512 N_cap 512 cap hit 1 floor truncated 1 pilot floor 1 pilot shipped 0 | e0 SE 0.842 dB VOV_union 0.476 both-near 1 U 1 | e1 SE 0.538 dB VOV_union 0.021 both-near 0 U 1
05h-reported layout4_s1/both_corner       n* 256 N 128 N_cap 128 cap hit 1 floor truncated 1 pilot floor 1 pilot shipped 0 | e0 SE 1.283 dB VOV_union 0.798 both-near 1 U 1 | e1 SE 1.239 dB VOV_union 0.056 both-near 0 U 1
05h-reported layout5_s1/listener_wall     n* 1024 N 6976 N_cap 6976 cap hit 1 floor truncated 0 pilot floor 0 pilot shipped 0 | e0 SE 0.141 dB VOV_union 0.023 both-near 0 U 0 | e1 SE 0.142 dB VOV_union 0.015 both-near 0 U 0
05h-reported layout5_s1/listener_edge     n* 1024 N 5952 N_cap 5952 cap hit 1 floor truncated 0 pilot floor 0 pilot shipped 0 | e0 SE 0.248 dB VOV_union 0.043 both-near 0 U 0 | e1 SE 0.215 dB VOV_union 0.040 both-near 0 U 0
05h-reported layout5_s1/listener_corner   n* 1024 N 4608 N_cap 4608 cap hit 1 floor truncated 0 pilot floor 0 pilot shipped 0 | e0 SE 0.225 dB VOV_union 0.060 both-near 0 U 0 | e1 SE 0.200 dB VOV_union 0.022 both-near 0 U 0
05h-reported layout5_s1/emitter_wall      n* 512 N 448 N_cap 448 cap hit 1 floor truncated 1 pilot floor 1 pilot shipped 0 | e0 SE 0.438 dB VOV_union 0.268 both-near 0 U 1 | e1 SE 0.266 dB VOV_union 0.016 both-near 0 U 0
05h-reported layout5_s1/both_wall         n* 1024 N 3200 N_cap 3200 cap hit 1 floor truncated 0 pilot floor 0 pilot shipped 0 | e0 SE 0.428 dB VOV_union 0.141 both-near 1 U 1 | e1 SE 0.215 dB VOV_union 0.024 both-near 0 U 0
05h-reported layout5_s1/both_corner       n* 1024 N 1024 N_cap 1024 cap hit 1 floor truncated 0 pilot floor 0 pilot shipped 0 | e0 SE 0.208 dB VOV_union 0.067 both-near 1 U 1 | e1 SE 0.488 dB VOV_union 0.049 both-near 0 U 1
05h-reported W1/both_corner               n* 1024 N 1024 N_cap 1088 cap hit 0 floor truncated 0 pilot floor 0 pilot shipped 0 | e0 SE 1.122 dB VOV_union 0.567 both-near 1 U 1 | e1 SE 0.089 dB VOV_union 0.026 both-near 0 U 0
```

Readings: the layout 4 one-end cases carry SE 0.66–1.02 dB with U raised (prototype C16: 0.13–1.33 dB); layout 5 one-end
cases 0.14–0.25 dB with U silent except emitter_wall (0.44 dB, U) and the both-near rows; W1 both_corner e0 SE 1.12 dB, U
raised, cap flag 0 (D-H3 (d)). The joint-rule replicates at the gated cubes are in file 10.
