# 8-seat3: Seat 3, R3 on M3-L4 (F2 composition)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 3 POSITION (R3, M3-L4: L4-A under the F2 composition). This is for saving as docs/review/phase-07c-2b/8-seat3.md. My access was read-only, so I did not write the file.

**1. Reading.** Seat 5's F2 stands, with one exception: `--realtime-emulation` with a fixed `--block` is allowed, and both L4 arms always use it. The cue from my §4 is state discontinuity, here the bit-identity of the prefix and the place of the cut, on the convolver that actually ships.

**2. Ranking.** L4-A under F2 as composed: **prefer, confirmed.** The composition is what my S1 already asked for ("realtime emulation, fixed block, the kit's P"). The decider is right about the code:
- `OfflineRender.h` L5–7 makes one full-length double-precision FFT for long dense IRs.
- So an offline A and B can agree only to about 1e-12 relative, never bit for bit, and S2 would go red on a clean stimulus.
- The real-time path is uniformly partitioned overlap-save (UPOLS) with P ∈ {128, 256, 512}, default 512 (`conv/PartitionedConvolver.h` L3–30). Its output block j sums X(age k)·H_k, and the FDL holds exact zeros before the programme starts. Any partition k that differs between A and B therefore adds an exact 0 until the input reaches it, so the prefix really can be identical.

**3. Tension now: 1, confirmed.** It needs the flag and the chain. The composition adds no work, because the kit already drives this path for AX47.

**4. Tension later: 1, confirmed.**
- The resurrection is still not heard by ear (S7 prints it). That debt belongs to AX49.
- The composition removes one later risk: L4 now tests the shipped convolver, not a reference path the plugin never runs.

**5. Evidence: four precisions so my checks are exact on this path** (all from the code, not acoustics):
- **S2, window.** Let n_on be the programme's first non-zero input sample and n_d the first IR tap where A and B differ (taken from P2's actual result, not the nominal t_mix,e,min − 2.5 ms). The first output sample that can differ is (⌊n_on/P⌋ + ⌊n_d/P⌋ + 1)·P, where the +1 is the P-sample latency (header L13–14). Assert identity before that sample.
- **S2, how to compare.** Compare by value, with +0 and −0 counted equal, not by memcmp. A product 0·H_k can carry the sign of H_k, so a silent prefix can differ only in the sign of zero.
- **S3, tolerance.** Each real-time render must equal `renderOffline` of the IR it wrote, delayed by P, within −120 dB residual/signal energy. That is the Phase 06 criterion (`test_partitioned_convolver.cpp` L170–197; `test_realtime_engine.cpp` L135). "Nulls" means this, not bit-exact. N-L3 must still fail it.
- **S4, the zero point.** "A is exactly zero" holds from output sample (⌈n_end/P⌉ + K_p + 1)·P, where n_end is the end of the release and K_p = ⌈L_p/P⌉. Between the true end of the convolution and that boundary, overlap-save leaves float rounding residue. Assert exact zero from the boundary on. In the partial block, assert at most −120 dB re the hold.

On the tailSeed: I accept one fixed seed shared by A and B. My varied seeds were [Hyp].

No `--abx-step-sample` alignment applies to L4-A, because there is no handover in either arm.

**6. Conditions** (to keep L4-A at 1/1; the third is new):
- P1–P6 and S1–S7 are in place before the seal.
- Seat 2's asserts are in place.
- S2, S3 and S4 are stated on the partition grid, as in point 5.

If S2 is kept on the offline path, or worded as memcmp, L4-A goes to 2/2: a clean stimulus reds and the seal stalls.

**7. Hand-offs.**
- Seat 5: confirm that the fixed block size does not change the identity across arms. Both arms use the same block, so it should not.
- Seat 5: confirm that real-time emulation loads the IR before the first input sample, so no AQ4 fade-in falls inside the prefix.
- Seat 1: its prefix check (A − B ≤ −18.27 dB over [0, release + L_f − h)) now runs on real-time output. Its margin past release is unchanged by the composition.

**8. Premortem.** If S2 were left as an offline or bitwise check, it would red on a clean S′ stimulus at the seal. The first to see it is the builder, and the AX47 seal stalls behind L4.

Files read:
- /home/user/makroof/docs/review/phase-07c-2b/6-decider-m3-r2.md
- /home/user/makroof/docs/review/phase-07c-2b/4-seat3.md
- /home/user/makroof/src/sim/OfflineRender.h
- /home/user/makroof/src/cli/Cli.cpp (L320–379)
- /home/user/makroof/src/sim/conv/PartitionedConvolver.h
