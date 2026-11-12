# 6 — Seat 6, round 2 (phase 07c-1, on decider file 5)

Saved verbatim by the orchestrator from the agent's report, 2026-11-12. Round-2 questions: file 5 §7.

SEAT 6, ROUND 2 (phase 07c-1): numbers on the provisional decision `/home/user/makroof/docs/review/phase-07c-1/5-decider-decision-r1.md` §7

The one change from round 1: I withdraw my preference for A2. Your L2 holds: in 07c-1 there is no path on the same OS where A1 and A2 sound different, so A2 buys the user nothing. All numbers are now/later on the 0–3 scale.

**Matter A**
| opt | now/later | reason |
|---|---|---|
| A0 | 2/2 | Every load is a v1-type load: early part only, with no admissible tail level until the background solve lands (up to 144 ms, K4). The gate serialises the solves, so with 8 instances the last one could wait about 8 × 131 ms ≈ 1 s [Hyp: arithmetic from K4, not measured]. That is "the reverb comes in late on reopen". The 07c-2 W_max raise makes the solve longer, so the gap grows. |
| A1 | 0/1 | Saved key matches → step 0, no switch, the room is right from the first sample (with D3\*). Later: after a post-release engine change (E mismatch), every customer project reopens the A0 way. |
| A2 | 0/1 | Sounds the same as A1 in 07c-1. It carries the same E-mismatch debt. |
| A3 | 0/1 | Adds nothing the user hears now that D3\* covers load. Later: project-size and autosave stalls the user would notice [Hyp]. That cost belongs to Seats 5 and 7, and Seat 4's veto stands anyway. |

Condition on A1's later 1 (keeps it at 1, not 2): the policy due before the first post-release engine change must not leave the user's existing projects with a load gap or a step. Seat 7's recorded proposal (the saved E_b stays authoritative on an E mismatch) meets this from my side, under NFR-6.

**C5′ (AX47): 0/1.**
- My C2 condition is met: the load fallback is the saved E_b plus the provisional tail, and no step arrives unprompted at load.
- Later 1 comes from two open items:
  - Phase 10: steps caused by automation arrive unprompted from the listener's seat; Seat 1 rules on this, as recorded in the decision.
  - 07c-2's deferred load fallback. There I still hold my round-1 side: never take the step at load; extend stage 1.
- Excluding the user's own edit from the scope is acceptable, because "settling" is visible while they edit.

**D3\* (AX49), on the corrected premise (same band noise, equal-gain): 1/1.**
- **Level side.** My round-1 [Hyp] about swapping between unrelated noises is gone. The step is coherent, and equal-gain never goes above the louder endpoint (K13), so there is no 3 dB bump mid-fade.
- **At load.** A tail is present from the first sample at the saved level. This is the Indoor rule: what you hear first is the real room (IndMan, ASFX16).
- **What still costs me:** the provisional is a prefix of length L_p, faded over its last 50–100 ms. If L_p is shorter than the audible decay, the producer hears a shorter reverb for about 3 s, then a longer one. That is "the room changed by itself" in duration rather than level.
  - AX49 tests band levels within 1 dB and EDT within 5 %. EDT covers the first 10 dB of decay [Inf], so neither check sees a truncated late tail.
  - Condition to keep it at 1: add an acceptance check on truncation, either T30 or the level at L_p relative to the decay. The threshold is Seat 1's; I give no number.
- **On edits.** The current IrSet holds only while the provisional builds in the background (0.08–0.2 s, [Hyp] from Seat 3), and the window is open, so "settling" covers it. That is the debt I am already listed for: record (g) now, the split update in Phase 10.

**Hand-offs**
- **Seat 1:** whether the AX49 acceptance needs a check on late truncation, and its threshold.
- **Seats 5 and 7:** load time with the synchronous provisional across 8 instances (R3 dialogs).

**Premortem.** If L_p is set by EDT alone, a producer reopening a project with a long T60 hears the tail lengthen about 3 s after pressing play. Maisara would catch it first, on the new listening item L4.