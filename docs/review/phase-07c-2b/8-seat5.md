# 8-seat5: Seat 5, R3 on M3 (F2, speech-also, skip)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 5 POSITION (R3 on M3, phase-07c-2b; narrow). This is read-only and I wrote no file. Please save it as docs/review/phase-07c-2b/8-seat5.md.

**1. Reading.** There are three items: (a) the F2 flag composition (both L4 arms run through `--realtime-emulation` with a fixed `--block`); (b) speech-also at ≥ 18/24; (c) Seat 7's skip. The cues are §2 c1 and c2 (worst case, determinism), S5 and S7 (paths stay deterministic and mechanically gated), and §9 (outcome-dependent behaviour is a reproducibility bug).

**(a) F2 composition: confirmed. Can live with, 1/1, as the decider read it. 1/0 with F2′ below.**
- **Code fact confirmed:** `OfflineRender.h` L3–7 says the reference renderer uses no partitioning and, for long dense IRs, "a one-shot full-length FFT" in double precision. So Seat 3's S2 (a bit-identical prefix floored to a partition) can only hold on the partitioned path, and my original F2 exclusion would have made S2 fail on a clean stimulus. I withdraw that exclusion.
- **Precedent:** `Cli.cpp` L358–362 already requires `--abx-step-db` with `--in/--out` to use `--realtime-emulation` with a fixed, non-zero `--block`. The composed F2 follows the same rule.
- **Now 1:** guard and test plumbing.
- **Later 1:** a third flag that combines with realtime emulation, and nothing yet pins A and B to the same partition and block.

**F2′, which takes later from 1 to 0:**
1. The flag refuses `--block 0`/random and requires `--realtime-emulation` whenever `--in/--out` is given.
2. Both arms use the same `--block` and `--partition`. The kit prints both values and records them in the manifest.
3. The IR the realtime path convolves for arm A is the `assembleProvisional` IR byte for byte. Test: hash the flagged `--ir` output and the IR handed to `RealtimeEngine`.
4. F5's "two flagged runs bit-identical" also covers the realtime-emulation render.

**(b) Speech-also at ≥ 18/24: confirmed. Prefer, 0/1, as read.**
- At admission the rate is ≤ 0.0453 (2 × 0.022656), still below the single-family 0.049 I rated 0. Over F1–F4 it is ≤ 0.0906, against unsplit's 0.196.
- Later stays 1, for the same reason as the split: a flip can still land at 08-3. C1 repays it.
- The hours are Seat 7's to rate and the power is Seat 1's.

**(c) Seat 7's skip (no S-B\* 0.9 dB blocks after an S-W 0.9 dB detection).**

| variant | rank | now | later |
|---|---|---|---|
| Decided at the sitting, after S-W's result | cannot live with | 2 | 2 |
| Written into the pre-registration commit and enforced by the scoring script (K1–K4) | can live with | 0 | 1 |

- **Ad hoc, now 2:** the trial plan would change depending on a scored result. A decision taken after the results is not in the sealed record, so nobody could check it later. That breaks reproducibility (§9), the same reason run-sheet L144–145 makes the script refuse to unseal a 0.5 dB block.
- **Ad hoc, later 2:** it cannot be undone once trials are scored.
- **Pre-registered, later 1:** S-B\* (the s < 1 class) gets no 07c-2b record in that branch. Its first evidence would be F4 at 08-3, after admission. That is the same flip-at-08-3 channel I already carry at 1, with one more class on it. The AX47 bound is already at 0.5 dB in that branch, so the reversal itself is not affected.

**5. Evidence.**
- From the code: `OfflineRender.h` L3–7 and L26–28; `Cli.cpp` L341–345 and L358–362.
- Run sheet L143–147 (fixed sequence and void rule).
- Binomial figures as in 6-decider R2 K6; I redid the arithmetic: 2 × 0.022656 = 0.0453 and 4 × 0.022656 = 0.0906.
- No acoustic fact is load-bearing here. The corpus was not needed.

**6. Conditions (skip, now 2 → 0, later 2 → 1):**
- **K1:** the skip rule goes in the pre-registration commit, before the first scored trial.
- **K2:** the scoring script refuses to unseal S-B\*'s 0.9 dB blocks only after a valid S-W 0.9 dB detection. A block whose anchor fails (void) never triggers the skip.
- **K3:** the S-B\* stimuli are still built, checked by HF-W (with condition D) and sealed before the first trial, so the sealed hash set does not depend on outcomes and S-B\* is ready for 08-3 F4.
- **K4:** the record says "S-B\* not run at 07c-2b, by pre-registered rule after S-W detection", never "not detected".

**7. Hand-offs.**
- Seat 3: whether s < 1 evidence before O4 can be lost in the detection branch. This is its F2-before-O4 debt.
- Seat 1: whether the S-B\* speech chain should still run.
- Seat 7: the hours saved.
- Decider: in the skip branch, the L4 timing rule ("the same day as the S-B\* sitting") needs a new anchor.

**8. Premortem.** If the skip is decided at the sitting, the 07c-2b record cannot show why S-B\* was not run. The first to notice is the contracted reviewer at 08-3, when F4 has no 07c-2b record to compare against.

Files:
- /home/user/makroof/docs/review/phase-07c-2b/6-decider-m3-r2.md
- /home/user/makroof/docs/review/phase-07c-2b/4-seat5.md
- /home/user/makroof/docs/review/phase-07c-2b/4-seat7.md
- /home/user/makroof/src/sim/OfflineRender.h
- /home/user/makroof/src/cli/Cli.cpp
- /home/user/makroof/docs/validation/abx-07c-2-run-sheet.md
