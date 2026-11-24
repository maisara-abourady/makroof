# 4-seat5: Seat 5, round 2 on M3 (α, V1-W, F1–F4, HF-W) and M3-L4

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 5 POSITION (round 2, M3 and M3-L4, phase-07c-2b)

This is read-only: I wrote no file. Please save it as docs/review/phase-07c-2b/4-seat5.md.

**1. Reading.**
- **R2:** How the α split shifts the false-reversal channel that my C1 is about. Whether HF-W meets my asserted-form rules.
- **M3-L4:** Which stimulus actually tests AX49's worst case. What a validation-only `render_cli` flag costs the default and offline paths.
- **Cues:**
  - §2 criterion 1 and §4.6: judge the worst case, not the mean.
  - §9: a vacuous test is a reproducibility bug.
  - S5: offline renders stay deterministic.

**2–4. Ratings (now/later).**

**R2 (a), the α treatment:**
- **24-trial split: prefer, 0/1.**
  - At admission the rate is ≤ 0.0439 (2 × 0.021963). That is below the single-family 0.049 I rated 0 in round 1.
  - For F3 and F4 I want the same thresholds (≥ 18/24 noise, ≥ 13/16 speech). The union over F1–F4 is then ≤ 0.0879, against unsplit's 0.196.
  - Later stays 1, because a correct or false flip can still land at 08-3, after admission.
  - The power cost belongs to Seat 1 and the extra trials to Seat 7.
- **Unsplit + C1: can live with, 1/1** (confirmed).

**R2 (b), my V1-W cell:**
- **Confirmed at 1/1 under unsplit + C1.** The now 1 is the 0.098 rate at admission.
- Under the 24-trial split it becomes 0/1.

**R2 (c), the F1–F4 declaration: confirmed,** including (i) as "chain comparison only".
- That rule is asymmetric: a detection counts and a null does not. It adds false-flip channels, not missed ones.
- That is why C1, first branch, should attach under either α option, not only "if unsplit stands". Under the split I can live without it; it is cheap, and I still ask for it.

**R2 (d), HF-W: meets every "any asserted form" condition except one gap.**
- **What it meets:**
  - a pure function of the sealed WAVs, with SHA-256, float64, no RNG and no clock;
  - an analytic β from B and E that is never fitted;
  - the margin printed;
  - N1 and the unmodified-stimulus pair;
  - runs on the kit's platform;
  - a red is a stop.
- **The gap:** a frame is skipped when max(E_a, E_b) < n_f·10⁻⁹, whatever E_o is. A click in a near-silent frame (speech pauses, the pre-N region) would pass, and that is the most audible kind of click.
- **Rating:** 1/1 with condition D below; 1/2 without it.

**M3-L4:**
- **L4-A: prefer, 0/0.**
  - It is the worst case. AX49's own record has an 8-instance Windows load at 9.51 s (keyless; CI run 43242209571), well past L_p ≈ 3.7 s. So "the provisional plays static past L_p" is an observed event, not a corner case.
  - Rendering it is one IR write plus a convolution.
- **L4-B: cannot live with as written, 1/3.**
  - The CrossfadingConvolver's two states read one input history (AX49's K23). After a handover at T ≤ L_f, the output is the exact IR over the whole history, so no input sample's tail ever reaches L_p.
  - L4-B can therefore never present the cut that AX49's Reversal names ("the L4 ABX detects the cut") [Inferred, from K23 and the AX49 text].
  - What it does test is the AX47 (b) level step plus the AQ4 fade, and that is AX47's ground.
  - A null on it would be read as clearing the reversal trigger while the worst case stays unheard. I rate that veto-grade under criterion 1 (worst case, not mean).
  - Now 1: it also needs new two-IR switch plumbing at a seeded time in `Cli.cpp`.
- **The validation-only flag: 1/1 as stated, 1/0 with conditions F1–F6.**
  - It reuses `StagedBuild::assembleProvisional` (`Engine.h` L295–298) and needs no `src/sim` change.
  - The risk is a vacuous L4. Where L_p ≥ L, `assembleProvisional` returns exactly `assemble()`, so A = B bit for bit.
- **The /fix-plan to AX49: 0/0,** provided the exception names the flag and keeps "Offline renders, bounces in hosts that signal offline … never use the provisional" word for word.
  - AX5 is untouched: the provisional comes from the same seed and stream, so it is deterministic run to run.

**5. Evidence.**
- **Arithmetic, redone:**
  - Σ C(24,k), k = 18..24 = 190051, and 190051/2²⁴ = 0.011328.
  - 697/65536 = 0.010635.
  - Sum 0.021963 per scene; × 2 = 0.0439. The decider's 0.0438 is a rounding slip.
  - × 4 = 0.0879.
- **Code facts:**
  - `Engine.h` L146–160 (`ProvisionalTiming.provisional`) and L293–298.
  - `Cli.cpp` L67–73 and L350–372: the abx-flag precedent, with mode and exclusion guards and "src/plugin never names it" checked by `test_abx_kit.py`.
  - AX49 row: L_p ≥ L means the exact tail is built in its place; the 9.51 s record.
- **Corpus:** not consulted. No acoustic fact here is load-bearing for my seat.

**6. Conditions of acceptance.**
- **D (HF-W, later 2 → 1):** in a skipped frame, assert E_o ≤ β·n_f·10⁻⁹. Print the skip count. If any scene skips frames inside [N, N+L), add an N1 variant that puts the spike in a skipped frame.
- **L4-B (3 → 1):** the seeded handover time must cover the worst case record (h) prints, that is, at or past release + L_p. That effectively contains L4-A, so L4-A is simpler.
- **The flag (later 1 → 0):**
  - **F1:** `render_cli` refuses with a non-zero exit unless `--mode omni` and `provisionalTiming().provisional` is true. It prints L_f, L_p and L.
  - **F2:** it excludes `--ensemble`, `--abx-step-db`, `--switch-scene`, `--tail-level ax16` and `--realtime-emulation`.
  - **F3:** both L4 arms go through one convolution path and one tool. A is the provisional IR and B the exact `--ir`. Do not mix `render_cli --in/--out` with a Python convolution.
  - **F4:** the isolation test is extended so that `src/plugin` never names the flag and the plugin never links `src/cli`.
  - **F5:** default renders are bit-identical with and without the new code; two flagged runs are bit-identical; and the `[pipeline]` offline-bypass test is unchanged.
  - **F6:** the CI test uses a small scene with L_p < L. The 100 m gated geometry runs only in the kit.

**7. Hand-offs.**
- Whether the cut or the handover is the audibility target, and the chord and its level: Seat 1, with Seat 3 on the fade.
- A geometry at T60 8 s with L_p < L: Seat 2.
- Hours for 24 + 6 trials: Seat 7.
- Power at 18/24: Seat 1.

**8. Premortem.** If L4-B runs as written and passes, AX49 ships "cleared" while the first 8-instance Windows load longer than L_p cuts every held tail. The first to notice is a user releasing a pad right after opening a session.
