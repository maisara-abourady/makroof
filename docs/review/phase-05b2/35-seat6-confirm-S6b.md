# Seat 6 — confirmation S6-b (D-T1.6 note U on the final text)

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

SEAT 6 POSITION: S6-b, the D-T1.6 user note U on the final text (round 4)

I read `34-decider-round4-final-T1-T2-T6.md` (§C and §D-T1.6) and `33-orchestrator-C16.md` (f). I did not re-read the corpus this round.

**1. Reading.** Under the joint rule, does U show "approximate" only where producers should be warned, at both pilot sizes? It triggers two cues:
- a flag on ordinary placements, which breeds habituation (W3);
- a helper whose trigger the user cannot see or predict (W4).

My conditions (i)–(iii) are adopted as written (34 §D-T1.6). Condition (ii) is met today: U is silent at all six Phase 04 defaults, at every one-end placement, at `dead_booth` with the listener at a wall, and in the D-T6 small room, at both n\*_max values (C16 (f) reading 1).

**2–4. Ratings**

**U at n\*_max 8 000: prefer. 1/1.**
- **Now: 1.** U flags two good estimates, and both come from a deliberate "back both ends into the walls" gesture, never from a default:
  - `living_room` both_wall_0.1: SE 0.079 dB, replicate p95 0.15 dB;
  - W1 both_wall_0.3: SE 0.095 dB, p95 0.49 dB.
- The warning points the right way:
  - Both cases carry VOV of 0.23 and 0.37 (C16 (f) reading 3). Capped or heavy-tailed draws of this class read low by skew (C13 §2: medians −0.35 to −6.72 dB), and the replicate p95 cannot see that.
  - Under (i), the note is qualitative ("move either about 0.7 m away") or quotes a class p95. A false positive therefore costs the user one sentence and an action, not a wrong number.
  - Everywhere else U fires on poor estimates: layout 4, layout 5, and the low-α cube at s = 1 (SE 0.29–1.33 dB).
- **Later: 1.**
  - The 0.70 m threshold comes from one sweep, and the good-estimate flags may grow or shrink in C++. The evidence is the C++ reported set (34 debt register).
  - Phase 12 presets must keep (ii). Undoing means moving a preset placement or changing a parameter before release.

**U at n\*_max 1 024: can live with. 2/1.**
- **Now: 2.** The smaller pilot makes the VOV leg noisier. U then fires on three more good estimates at ordinary placements (C16 (f) reading 4):
  - `club` both_wall_0.3 and both_wall_0.5 (SE 0.069 / 0.066 dB);
  - `living_room` both_edge_0.3 (SE 0.105 dB).

  A band 0.5 m off a club's wall with the listener 0.5 m off the opposite wall is a normal scene. A note there, decided by pilot noise rather than by the estimate, is what makes users ignore it in the both-corner cases that read 1–6 dB low.

  Since the note is evaluated only on the settled scene, it cannot flicker mid-drag. But neighbouring settled placements could toggle it [Hyp; no 1 cm sweep of U at 1 024 exists].
- **Later: 1.** The fix is a predicate or parameter change, made before release.

**Minor, at both sizes (1/1; it does not change the ratings above).**
- Under joint accounting, an emitter the user did not move can be capped, and can raise U, when the other emitter or the listener moves: layout 5 listener_absorber, and layout 4 throughout (C16 (f) reading 5).
- This is the W4 pattern: a note on an object the user did not edit. So far it is seen only in s = 1 layouts that are not presets.

**5. Evidence**
- C16 (f): the table and readings 1, 3, 4 and 5.
- C13 §2 (skew of capped both-near draws) and §3 (replicate p95).
- 34 §D-T1.6: the note text, (ii), (iii) and the debt register.
- 34 "Where U fires": C15 shows the capped cubes, where U is silent, are not skewed (median −0.06 to +0.04 dB, p95 ≤ 0.28 dB). This supports the silence at the 100 m defaults.
- [Hyp] neighbour toggling at 1 024.

**6. Conditions of acceptance**
- **U at 1 024 → 1/1.** Pre-register the note's VOV leg on the same number of histories at both pilot sizes. For example, compute the note's VOV over pilot ∪ final range, up to the first 8 000 histories.
  - This is valid because the note does not feed the estimate, so the final range's freshness (F14) is untouched.
  - **For the orchestrator:** recompute C16 (f)'s U column at 1 024 with that VOV, and check that `club` both_wall_0.3/0.5 and `living_room` both_edge_0.3 go silent while every SE > 0.33 dB case still fires. If they do not go silent, my rating stays 2/1.
- **The unmoved-emitter note (optional; would remove the minor item).** In the info view, a note on an emitter the user did not edit names the scene as the cause, not that emitter. Alternatively, Seat 5 judges a per-emitter N_cap inside W_scene.
- **My preference on Q2 (Maisara's call):** n\*_max 8 000. For my seat it means fewer false notes at ordinary placements and lower SE at the defaults (0.007–0.054 dB against 0.017–0.086 dB, C16 (f)).

**7. Hand-offs**
- **Maisara:** Q2 (n\*_max).
- **Seats 6 and 7, Phase 11:** the note's wording.
- **Seat 5:** whether a per-emitter cap is possible under joint accounting.
- **Seat 9 / Phase 12:** the per-preset check required by (ii).
- **Seat 1:** whether p95 0.49 dB (W1 both_wall_0.3) deserves the note. I think it does.

**8. Premortem.** If Q2 lands at 1 024 with the VOV leg as written, a beta user who backs a band and the listener against a club's walls sees "level unreliable" on a tail accurate to about 0.07 dB. Later the note is right and they ignore it. A beta user or Maisara at the Phase 11 placement check notices first.
