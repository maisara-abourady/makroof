# 42: Seat 5 on H3+G later and the (a0) top-up (M3-H)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 5 POSITION (short follow-up on M3-H: file 41 Q1 and Q4). Read-only; I changed no files. The orchestrator saves this as /home/user/makroof/docs/review/phase-07c-2b/42-seat5.md.

**1. Reading.**
- (1) I rate H3+G's later column under the decided (a0) text: the manual job, the pin-bump reruns and the red clause.
- (2) I replace 07e-b's "not decidable" step 1.
- Cues: S5 (a deterministic reference), CS-5 (one-person pipeline), and §4.4 (no change to N after results are seen).

**2. Ranking.** H4+G: prefer. H3+G: can live with. Both unchanged.

**3–4. Ratings (H3+G).** Now 1, unchanged. **Later 1**, revised from 0.
- **Why the 0 falls:** I gave 0 in 32-seat5 §4 ("prints and the clause are the same"). That was before the (a0) text existed (39-seat5). That text adds three things, and all three are the same under every home:
  - a standing manual job, rerun on each numpy or Python pin bump (39-seat5 §5);
  - the 24 h runner cap with its SE fallback;
  - the residual after the end date: a discrete-field flip that is named in the reason but that "no gate stops" (34-seat5 §4).
- Under H3+G these cost exactly what they cost under H4+G. Each of them is a debt by my criterion 4, so H3+G's later cell is 1.
- **What H4+G's later 1 rests on:**
  - **The same three common costs:** yes, those carry it.
  - **The one H4+G-specific candidate:** scope 8 held with a likely 07d/07d-b split (32-seat5 §4). G2 holds scope 8 under H3+G as well, and under H3 I priced the hold into its now-1, paid from day one. It does not raise H4+G above 1, and it is not needed to reach 1.
  - **Answer:** my H4+G later 1 rests on nothing that H3+G does not also carry.
- **Result:** S5 is 1/1 under H3+G and 1/1 under H4+G. My row does not separate them, and the tie stands on my cells. Reversibility is the decider's step, not mine.

**5. Evidence.** 32-seat5 §4 (the 0, rated on the pre-(a0) text); 39-seat5 §5 (the pin rerun); 34-seat5 §4 (the residual); B11 at BUILD_PLAN L404, quoted below.

**6. Q4: replacement text.** B11 cannot serve here.
- It doubles N per bin up to 16·N₀ (about 24.4 M), while (a0) is sized per window at ≥ 152 M (F8).
- It also says "N (beyond the pre-stated doubling rule) … never changed after results are seen".
- So any increase has to be (a0)'s own rule, stated in 07e before dispatch, run mechanically inside 07e, and triggered only by realised k, never by the engine-to-tracer difference.
- 07e-b then never reopens N.

Add to **07e scope 3, under "(a0) run, gate and sizing"**, after "Cap.":
> "**Top-up (pre-stated; (a0)'s own rule, not B11's).** After the full run, for each emitter and radius whose realised window k in a band is below that band's gate (684, or 76 where the cap put the band on the SE fallback), N is raised once to N × gate / min_band k_realised, rounded up to whole 200,000-particle chunks; particles are added, never redrawn. This happens only if the total predicted runner time, the top-up included, stays within the 24 h cap and the 36 h ceiling; otherwise the cap rule applies. The trigger is realised k alone; no engine value is read before the top-up completes. There is no second top-up. Seed, windows, bins and radii never change. The run record prints both N values and both k values."

Replace **07e-b "not decidable" step 1** with:
> "1. No further particles are run. (a0)'s pre-stated top-up (phase-07e scope 3) is the only increase of N, and it has already run. N is never changed after the comparison has been seen (B11, L404)."

Ratings on Q4:
- **Text as written** ("under B11's doubling rule"): 2 now and 2 later. It reads as either a no-op or a change of N after results are seen, which breaks determinism (criterion 2).
- **Replacement above:** 0/0. It adds one branch to the job I already specified.
- **"None"** (delete step 1, with no top-up): 1/1. A pilot that underpredicts k sends a decidable band to "not decidable" with gates shut, at the cost of a board loop.

**7. Hand-offs.**
- Seat 7: whether the top-up's share of the 24 h cap needs its own reserve.
- Seats 2 and 9 with Seat 1: file 41 defect 2, what a band on the SE fallback (3σ 1.49 dB, 2.11 dB for the two-radius check) may count as. That is not mine to settle.

**8. Premortem.** Suppose step 1 stays as written. A reviewer reads it as a licence to rerun (a0) "with more particles" after seeing a 1.1 dB difference, and the reference then depends on when the comparison was looked at. The interrogator would notice first, from a second N in the run record that has no trigger.
