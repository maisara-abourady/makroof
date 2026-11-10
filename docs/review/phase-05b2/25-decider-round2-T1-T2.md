# Decider — decision round 2, D-T1.6, D-T1.3 and D-T2

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

# Decider: decision round 2 for D-T1.6, D-T1.3 and D-T2 (phase 05b session 2, 2026-11-10)

**Outcome**
- **D-T1.6, decided: NW-4C+.** The NW-4C blend is adopted with the seats' conditions folded in. The worst-off seat is Seat 1 at later 2: when both ends sit near a surface, the capped estimate reads low. NW-3 is out on Seat 2's later-3 veto.
- **D-T1.3, rule decided; one parameter goes to Maisara.** The rule is **N-3W\*\***, composed from the seats' round-2 conditions as C13 implemented it. Worst-off is Seat 1 at 2/2: its floor fails in long-window rooms with one fully absorbing face. The work cap's value, W_max, depends on a sizing basis only Maisara can set (AQ10 is settled, and Challenge 1 is still open). I return that as **NEEDS MAISARA (Q2)**, with a provisional value so the build can proceed.
- **D-T2: NEEDS MAISARA (Q1).** Seat 5 vetoes L2-F1R (later 3), and L2-F2 is already vetoed. The only option with no 3 is the bias reading of AX36 (max 1), and only Maisara can rule it in bounds.
- **D-T1.1 now stands at max 1.** Its ᶜ cells are resolved. Seat 5's T1-F† cell is confirmed 1/1 on condition D7, which is added below.
- **No new seat round.** Every composed cell below is either the seat's own cell or is read from that seat's written conditions, marked †.

**Corpus revision:** `c1b171fe649f07cbeb952ef1f75d89bfaa414d0d`. I re-read Kuttruff Eq. 2.50 and L1552: in a diffuse field, wall phase effects are confined to about half a wavelength from the wall, with the squared pressure doubling at the wall. Vorländer Table 6.1 was re-read in round 1 (G jnd 1 dB, 500–1000 Hz).

**Inputs**
- `21-decider-decision-T1-T2-T6.md`
- `22-orchestrator-C12.md`
- `23-seat1…9-round2-T1-T2.md`
- `24-orchestrator-C13.md`
- `19-orchestrator-NW4-and-checks.md` §1–§6
- dossier `14-researcher-T1-T2.md` (F3, F10–F14, F19)

**Inconsistency inside C13, flagged for the orchestrator.** In §2, the table's median replicate-vs-long values for the both-near cases do not match the §2 reading 3 list or the summary:

| case | table median (dB) | reading/summary median (dB) |
|---|---|---|
| W1 both_wall | −0.35 | −0.39 |
| W1 both_corner | −1.20 | −1.44 |
| L5 both_wall | −1.13 | −1.74 |
| L4 both_wall | −2.45 | −2.09 |
| L5 both_corner | −5.57 | −5.97 |
| L4 both_corner | −6.72 | −6.22 |

Below I cite the **table** (−0.35 to −6.72 dB). Nothing here turns on which set is right: both say the estimate reads low by up to about 6–7 dB in the synthetic both-corner cases. The orchestrator should reconcile them before the AX row is written.

---

## D-T1.6 Near-listener handling

### Tension map (round-2 cells; `now/later`)

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| **NW-4C+** | 1/**2** | 1/1 | 1/1 | 0/1 | 1/1 | 1/1 | 1/1 | 1/1 | 1/1 | 2 | 18 |
| NW-3 (re-rated) | 1/2 | 2/**3** | 2/2 | 1/2 | 0/2 | 1/2 | 2/2 | 1/2 | 2/2 | 3 | – |
| NW-2 (round 1, rated before NW-4C existed) | | | | | | | | | | 2 | 21 |
| NW-1 (round 1) | | | | | | | | | | 2 | 31 |

**About the NW-4C+ cells.** These are the seats' own round-2 NW-4C cells. Some seats' conditions, all folded into NW-4C+, would lower their cells further: Seat 4 to 0/0, Seat 8 to 1/0. I do not apply those reductions, because they would not change the decision. Seats 2, 3, 5, 7 and 9 hold 1 only if their conditions are met, and the decision text contains each of them.

**What each seat says, in its own words:**
- **S1 later 2:** "Both ends near a surface… A capped estimate in a user scene can ship several dB low." Its two routes to 1:
  - (a) shipped error ≤ 1 dB at p95 in both-near cases in layouts 4/5 under N-3W\*;
  - (b) a both-near fallback with a bounded, measured bias.

  C13 §2 shows (a) is not met, for example layout 4 both_corner p5/median −9.28/−6.72 dB. For (b), no measured fallback exists.
- **S2 veto on NW-3:** "+0.322 dB at layout 5's absorbing wall, more than τ… the gate cannot fail the error."

### Working
1. **Bounds.** No option breaks a PRD bound.
2. **Veto.** NW-3 is dropped (S2 later 3).
3. **Worst-off seat.** NW-4C+, NW-2 and NW-1 all have max 2.
4. **Composition.** The only route to lower S1 to 1 is route (b). Its candidate, Seat 1's own suggestion of NW-3's clamp at one end, carries the clamp bias Seat 2 vetoes, and no both-near measurement of it exists. So I cannot compose it without raising Seat 2. The max stays 2.
5. **Sum.** NW-4C+ has 18, against NW-2 at 21 and NW-1 at 31.
6. **Reversibility.** w is a formula, so changing it is a parameter change (Seats 2 and 9).

### DECISION D-T1.6 = NW-4C+

**Estimator**
- Per emitter, E_diffuse = w·E_fwd + (1−w)·E_rev, with w = d_L²/(d_L² + d_E²). Here d is that endpoint's distance to the nearest surface. w is computed from geometry only and never from the run's own variances (Seat 2).
- E_fwd starts paths at the emitter and gathers at the listener's lattice images. E_rev starts paths at the listener's head centre and gathers at each emitter's images.
- **One listener-started set serves both emitters, both ears and every output mode** (Seats 2, 3, 4, 5).
- The plan uses the true positions throughout: window, t_mix,e, referral and specular entries.
- There is no clamp and no model change.

**Determinism**
- Both path sets run in the same D4 blocks, so `quiesce()` still waits at most one batch.
- D5's face-sequence hash covers both sets (Seats 5, 7).
- The RNG key carries the start end (D1).

**Both-near flag**
- Pre-registered geometric criterion: **d_L < 0.70 m and d_E < 0.70 m**. Seat 2 asked for a criterion taken from the sweep where the pilot VOV crosses 0.1; C13 §4 puts that crossing between 0.70 m (0.097) and 0.65 m (0.102). I take the 0.70 m end.
- The flag is deterministic, written to `TailMatch` and `--diagnostics`, and its threshold is fixed before release (Seat 7).
- In both-near cases the capped NW-4C estimate is shipped, flagged. Its error is reported, not bounded.

**User-facing "approximate" note.** It lives in `TailMatch` now; the UI phase shows it on the settled scene only, in the info view, worded by Seats 6 and 7. It is raised when any of these holds:
- both-near (Seat 6);
- a cap hit with achieved final SE > 0.33 dB (Seat 6);
- pilot VOV ≥ 0.1 **where the pilot SE > target/3 (0.028 dB)**.

The qualifier on the third trigger is Seat 1's rule. I add it so the note does not fire on excellent hard-walled estimates (flutter cube: final SE 0.002 dB, VOV 0.51). That is exactly Seat 6's round-2 premortem ("a concrete garage… sees 'approximate' on every placement"). The S6 cell rests on this reading, and the interrogator should check it. Bare cap hits, R, VOV and slope stay in the diagnostics and CI (Seats 2, 6).

**Reported, not gated (adds to D-T1.5)**
- W1 both_wall and both_corner at 0.1 m (Seat 7).
- W1 both-near at 0.3 and 0.5 m (Seat 3).
- `club` and `living_room` both-near at 0.1, 0.3 and 0.5 m (Seat 8).
- The layout-5 listener edge and corner: the reference changes 5.3 % and 8.7 % per halving there (C13 §7), so it is not certified. Each carries a "reference uncertified" note (Seat 9).
- An independent near-corner reference, computed and reported before the goldens are frozen. Either `ref_hybrid` with local patch refinement, or the tracer at r_d < 0.1 m at two radii (Seat 2). If it cannot be computed in this session, Seat 2's later becomes 2, which is still the max.

**Benchmark.** W1 both_corner at 0.1 m asserts the cap flag, the way W2 asserts the fallback (Seat 5).

**AX-row text (Seat 9).**
> Within about half a wavelength of a surface, the GA tail level ignores the near-wall pressure rise (Kuttruff Eq. 2.50). It is GA-true, not room-true; no accuracy claim is made there, nor at layout-4/5-type edges and corners, where the reference is uncertified (Seat 7's wording).

**Phase 08 hand-off (Seat 4).**
- A test that E_b is bit-identical between omni and binaural and between the two ears.
- One both-near binaural render in the Phase 08 listening pack.

### Load-bearing claims
- **D16-L1 (C12 (a)).** With one end near a surface, the NW-4C SE at 32 k equals the reference-position SE: 0.013–0.016 dB in W1, 0.068–0.114 dB in layouts 4/5. The largest history share is ≤ 0.54 % and VOV ≤ 0.015.
- **D16-L2 (C13 §6).** The layout-4 emitter-edge outlier does not reproduce. A 1 M-history run agrees with the 256 k run within 0.028 dB, so the 32 k draw was the outlier.
- **D16-L3 (C12 (b)).** Steps per 1 cm: ≤ 0.040 dB in the listener sweeps, ≤ 0.026 dB across d_E = d_L, and 0.209 dB in both-near.
- **D16-L4 (C13 §2 table).** Both-near under the cap, median replicate vs long run: −0.35 dB (W1 wall) to −6.72 dB (layout 4 corner). Seat 1's p95 ≤ 1 dB is met only in W1 both_wall.
- **D16-L5 (19 §4, §6).** The NW-3 clamp bias is +0.322 dB at the layout-5 absorbing wall, which exceeds τ = 0.25 dB. This is the basis of the veto.
- **D16-L6 (C13 §4).** The pilot VOV crosses 0.1 between 0.70 and 0.65 m (W1, long window, both ends moving).
- **D16-L7 (derived, Seat 2 from F3).** The blend's score cap is 2/(π(d_L² + d_E²)): 0.16 m⁻² with one end at 0.1 m and the other at 2 m, and 31.8 m⁻² with both at 0.1 m. This is why both-near reverts to NW-1's behaviour.

### Future-debt register

| seat | commits later phases to | undo cost | evidence arrives | repaid when |
|---|---|---|---|---|
| S1 (2) | both-near reads low (median down to −6.7 dB in synthetic both-corner), flagged, not bounded | a both-near fallback with measured bias (Seat 2 designs it) | C++ CS-NW+ reported set; listening pack | a fallback with p95 ≤ 1 dB, or a measured bounded bias |
| S2 | B7 directivity and B10 weighted branching in both sets; uncertified layout-4/5 edges and corners | estimator change in both directions | near-corner reference (this session); B7, B10 | the reference reported; B7/B10 phases |
| S3, S6, S7, S9 | the both-near region boundary (0.70 m) is fixed from one W1 sweep | parameter change, before release | C++ CS-NW+ | release |
| S4 | binaural parity and the both-near render | test | Phase 08 | Phase 08 |
| S5 | two RNG streams under D5 | – | three-OS CI | permanent |
| S8 | both-near measured in W1, layouts 4/5, `club` and `living_room` only | – | Phase 12 presets | presets checked |

**Strongest objection.** The note may fire in ordinary small-room placements. In `dead_booth` the listener sits at d_L = 0.70 m and the emitters at 0.5 m, from the fixture (from the code). The booth is outside the both-near criterion by the strict "<", but a 1 cm move toward a wall would raise the note on an estimate that is probably fine: `living_room` both_wall at 0.1 m has p95 0.15 dB (C13 §3), and the booth's both-near case was never measured. This is Seat 6's "design failed" risk. The decision holds because the criterion was set before any number in a booth and can be changed as a parameter before release. If the C++ CS-NW+ run shows the note raised in a Phase 04 room's default or near-default placement with final SE ≤ 0.1 dB, the criterion goes back to Seats 2 and 6.

**Confidence:** medium. The S6 cell rests on my reading of its trigger, and the both-near residual is unbounded.

**Reversal**
- A measured both-near fallback that lowers S1's later 2 to 1.
- The near-corner reference contradicting NW-4C at edges and corners by more than τ.

---

## D-T1.3 Path count, pilot and work cap

### Tension map

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| N-3W\* as composed | 2/2 | **3**/1 | 2/2 | 2/2 | 2/2 | **3/3** | 2/2 | 2/2 | 2/2 | 3 | – |
| **N-3W\*\*** (from conditions, as C13 ran it) | **2/2** | 1/1† | 1/1† | 1/1† | 1/1† | 1/1† | 1/1† | 1/1† | 1/1† | 2 | 20 |
| N-1 (round 1) | | 2/**3** | | | | | | | **3/3** | 3 | – |

Why each † cell is 1/1, by the seat's own condition:
- **S2:** C1–C5 (pilot defined in work, share ≤ ½; fixed start at 8 000; N ≥ pilot; W_max a pinned constant in evaluations; slope and VOV in the diagnostics).
- **S3:** C-1 to C-3.
- **S4:** conditions 1–5.
- **S5:** pilot ≤ W_max/2, N ≥ pilot, W_max as it re-derived it, a constant, plus D7.
- **S6:** conditions 1–4.
- **S7:** pilot in work, N ≥ pilot, "target SE; achieved SE reported", slope reported only.
- **S8:** (a) and (c). For (b), the floor stays within W_max by construction.
- **S9:** a work pilot with a floor, and N ≥ n\*_eff.

**Why S1 is not †.** Seat 1's conditions include "my floor measured in layouts 4/5 one-end cases", with the floor being "SE ≤ 0.33 dB with VOV < 0.1". C13 §2 measured it and it fails: final SE in layout 4 is 0.39 dB at the reference positions and 0.57–1.11 dB near walls; in layout 5 it is 0.40 dB and 0.16–0.60 dB. The 100 m cube fails the VOV part (0.31 and 0.37). So the cell stays 2/2.

### Working
1. **Bounds.** See Q2 below for W_max's sizing basis.
2. **Veto.** N-3W\* as composed is dropped (S2 now 3; S6 3/3), and N-1 is dropped (S2, S9).
3. **Worst-off seat: N-3W\*\* is at 2.** The round-1 rows N-2 (sum 23) and N-3 (sum 17) **cannot be ranked against it on their round-1 sums**. Their cap N_max was undefined, and the seats read it in incompatible ways:
   - Seat 1 read a floor-sized N_max, its round-1 NW-1 condition, and rated N-3 0/1.
   - Seat 5 read a path-count cap, rated N-3 1/2, and asked for N-3W.

   Once N_max is defined, the option is N-3W\*\* (Seat 5's cap, where S1 is 2 per C13) or a floor-sized cap that no seat has rated. I am not re-rating anyone; the round-1 row is underspecified, and N-3W\*\* is its specified form.
4. **Composition.** Lowering S1 needs W_max ≈ 11× Seat 5's value: (1.113/0.33)² = 11.4, from the worst one-end SE in layout 4 [Inferred]. Seat 5 has not rated that. Its stated veto ground on L2-F1R is the same structure (work past the restore bound). So the trade goes to Maisara as Q2 rather than to another round.
5. **Sum.** N-3W\*\* has 20.

### DECISION D-T1.3 = N-3W\*\* (rule). Every element names the seat it comes from.
- **Calibration.** A fixed block of histories [0, 256) gives e_cal, the mean image evaluations per history (Seat 4 (4), C13).
- **Pilot.** n\* = min(n\*_max, ⌊(W_max/2)/e_cal⌋), with histories [0, n\*). The size is set before sampling (Seat 4). The pilot is defined in work, with share ≤ ½ (Seats 1, 2, 3, 5, 6, 7, 9).
  - **n\*_max** is a constant ≤ 8 000. It is set from the C++ W1 measurement so that the diffuse solve (pilot plus final) for both emitters takes ≤ 25 ms of the AQ10 W1 record (Seat 4 (1), Seat 3).
  - It is **never below 1 000** (Seats 1, 3, 9 floor).
  - If both bounds cannot hold at the C++ cost, the conflict returns to Seats 1, 3 and 4 before the goldens are frozen. On the prototype the two meet near 1 000 at one thread: 2·n\*·180 evaluations × 2 emitters × 34 ns ≈ 24.5 µs·n\*, so n\* ≈ 1 020 [Inferred].
  - If n\* < 1 000, the cap-hit flag is raised (Seats 1, 3, 9).
- **The pilot is discarded.** The final range starts at the fixed index 8 000 and is disjoint from the pilot (Seats 1, 2, 4; F12, F14).
- **N.** N = max(N_need, n\*), where N_need = ⌈n\*·(SE_pilot/SE_target)²⌉ (Seats 1, 2, 3, 5, 6, 7, 9).
  - N is capped at N_cap = ⌊(2·W_max − W_pilot,both)/ē_pilot⌋. W_pilot,both is the work of both emitters' pilots, and ē_pilot is the pilot's mean evaluations per history.
  - N_cap is computed **before** the final range is sampled, so the final range never stops on realised work (Seat 4 (4)).
  - Seat 5's restore derivation counts the work of both emitters together, and the shared listener set is counted once.
  - **D7 (Seat 5).** N is computed without libm, rounded to whole D4 blocks, and recorded per case in the D5 golden.
  - If the final range is empty, the pilot estimate is shipped, flagged; never a zero tail (Seat 4 (3)).
- **Diagnostics.** Reported: n\*, N, target SE and achieved SE (Seat 7's wording), R, VOV, slope (reported only, never flagged: Seats 1, 2, 3, 7), the cap hit, the pilot floor, both-near, and realised work against W_max.
  - CI escalation on R, and on VOV ≥ 0.1 where the pilot SE > target/3 (Seats 7, 1).
  - Flags expected at gated scenes are pre-registered: the W2 and flutter-cube pilot floor; the 100 m cube cap and VOV; the W1 both_corner cap. They are recorded in the D-T1 packet, not re-escalated on every run.
- **W_max.** A pinned constant in image evaluations, the same on every platform, recorded as an AX row. It is re-derived once from the C++ cost (Seats 2, 5, 6) using:
  - the CI runner's pool size;
  - the worst cost over the gated set;
  - the worst restore-build time over the OSes (Seat 5).

  It is checked against Seat 6's 3 s per emitter at one thread. **The sizing basis is Maisara's (Q2).** Provisional value: Seat 5's derivation, **3.05 M evaluations per emitter** (prototype; C13 header). It is (2.143 − 1.884) s / 2 / 42.5 ns, which I re-checked.
- **SE target.** 0.083 dB (D-T1.4), unless Q1 binds.

### NEEDS MAISARA, Q2: what sets the work cap?
**The question.** The diffuse tail estimate needs a fixed work cap so that a project load cannot stall. Should that cap be sized to pluginval's restore watchdog (about 2.1 s per restore at the 100 m room, Challenge 1), or to the accuracy floor Seat 1 requires in rooms with one fully absorbing face?

AQ10 (yours, 2026-11-05) says full rebuilds are "recorded, not budgeted" and are never met by changing the output. A cap sized to a restore time does exactly that, so this is your call.

**(A) Cap sized to the restore bound, W_max ≈ 3 M evaluations per emitter (provisional default).**
- Restore stays within the bound.
- Ordinary rooms are unaffected:
  - W1, CR4 and the six Phase 04 rooms' one-end cases have no cap hits;
  - the listener grid in W1, `club` and `concert_hall_box` has 0 of 72 cap hits (C13 §1, §5);
  - shipped error in W1 near walls stays within −0.11 / +0.09 dB (p5/p95 over 30 replicates, C13 §2).
- In synthetic rooms with a fully absorbing floor or wall and fully diffuse walls (Table 5.2 layouts 4/5, s = 1), the tail level carries a per-scene random error:
  - SE 0.39–0.40 dB at the reference positions;
  - 0.16–1.11 dB near walls;
  - p5/p95 up to about −1.4 / +1.7 dB.

  For comparison, the old method's error there is a systematic +3.87 dB.
- The 100 m cube's default placement shows "approximate".
- Seat 1 stays at 2.

**(B) Cap sized to Seat 1's floor, about 11× (A) [Inferred].**
- Meets the floor in those rooms.
- Estimated restore of a 100 m cube scene: about 2.6 s against 2.1 s [Inferred, prototype costs].
- Edit-to-hear in layout-4-class rooms: about 1.5 s per emitter at one thread [Inferred].
- Seat 5 has not rated it. Choosing (B) needs one seat round, and a veto from Seat 5 would then be yours to override.

**(C) Take the diffuse solve off the synchronous restore and prepare.**
- This is Seat 5's own route, roughly a phase of Phase 07 rework, outside this session.
- The cap would then be sized by edit-to-hear: Seats 3 and 6's 3 s per emitter.
- (A) ships meanwhile.

**Timing.** Changing W_max changes shipped tail levels, so it must be settled before the first release (Seat 7). Before then it costs one golden round.

### Load-bearing claims
- **D13-L1 (C13 §1).** With the work-defined pilot, every gated scene has a final range: W2 and the flutter cube at n\* = 273–314, SE 0.002–0.012 dB. This resolves C12's conflict 1.
- **D13-L2 (C13 §2).** Seat 1's floor fails in layouts 4/5 at s = 1. The window drives it: t_mix,e is 0.380 s against 0.114 s in W1.
- **D13-L3 (C13 §5, §2).** No cap hits in ordinary rooms. W1 near-wall replicates stay within −0.11 / +0.09 dB.
- **D13-L4 (dossier F12, F14).** A fresh disjoint final range avoids the stopping bias of prefix reuse.
- **D13-L5 (product).** AQ10 forbids meeting a full-rebuild time by changing the output without /fix-plan. That is the basis of Q2.

### Future-debt register

| seat | commits | undo | evidence | repaid |
|---|---|---|---|---|
| S1 (2/2) | random tail error of about 1 jnd in absorbing-face, fully diffuse, long-window rooms | a W_max change (Q2) or async restore | Q2; Phase 12 presets of that class | Maisara's Q2 answer |
| S2, S5, S6 | W_max re-derived from C++, pinned | one golden round | C++ benchmark this session | AX row written |
| S3, S4 | n\*_max from C++ W1 ≤ 25 ms | parameter | C++ W1 | recorded |
| S7 | SE target and pilot rule set shipped bits | golden round before release; a "deal change" after | – | first release |
| S8, S9 | the 1 000 pilot floor rests on [Hyp] | parameter | – | a sourced pilot-size rule (researcher) |

**Strongest objection.** S1 at 2/2 sits in the rooms the switch exists for. It holds because even capped, the median error in layouts 4/5 is −0.29 to +0.34 dB one-end (C13 §2 table), against AX16's systematic +3.87 / −1.17 dB. The switch improves them in every one-end case. It would not hold if Q2's answer were (B) and Seat 5 then vetoed.

A second objection: Seat 2's literal C1 ("stops at… cumulative evaluations") is replaced by Seat 4's pre-sampling rule. Realised work can exceed 2·W_max only by the scatter of the final range's mean cost, and it is recorded. Seat 5 should confirm in the interrogator round.

**Confidence:** medium (eight cells read from conditions; W_max is provisional).

**Reversal**
- Q2 answered (B) or (C).
- The C++ cost making n\*_max < 1 000.
- Realised work over 2·W_max at a gated scene.

---

## D-T2 Resolution rule: NEEDS MAISARA (Q1)

### Tension map

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max |
|---|---|---|---|---|---|---|---|---|---|---|
| L2-F2 (round 1) | | | | | 2/**3** | | | | | 3 |
| L2-F1R | 2/2 | 2/2 | 2/2 | 2/2 | 2/**3** | 2/2 | 2/2 | 2/2 | 1/2 | 3 |
| bias reading (rated as the alternative) | 1/1 | 0/1 (with the per-class condition) | 0/1 | prefers (no cell) | 0/1 | 1/1 | 1/0 | 0/0 | 1/1 | 1 |

### Working
- Both in-bounds options carry a 3: Seat 5, "same structure as L2-F2… the 'certified' SE is false exactly where the work is expensive".
- The variant composed from conditions is the bias reading. It departs from how the convening read "the same per-quantity < 1 % rule", which is the text of AX36 that Maisara accepted, so only she can put it in bounds.
- Seat 5's own route (async restore) lowers L2-F1R only to 2/2 and is out of this session's scope.

**Q1 for Maisara.** Your accepted < 1 % rule (AX36) was written for patch size, where the error is systematic. The new estimator has no patch size; its error is random and measured. Should the rule apply:
- **(a) to the estimator's bias, checked in CI at high precision**, while users get today's precision (0.083 dB, a twelfth of the smallest audible level change);
- **(b) to every scene's random error**, at about 20× the computation?

**(a) Bias reading.**
- Shipped: D-T1.3's rule at SE 0.083 dB, about 0.08 jnd.
- CI (Release, hidden tag): at a pre-registered N per case with 3·SE ≤ 1 %, i.e. SE ≤ 0.0145 dB:
  - the mean signed deviation from the converged reference is < 1 % in every band;
  - it is tested pooled **and per case class**: reference positions, one-end near-wall, absorbing face, small rooms (Seat 2);
  - classes with an uncertified reference are reported only;
  - the BRAS report prints the Monte Carlo SE beside the ensemble spread (Seat 9).
- Cost: CI time only.
- Board max 1.

**(b) Strict reading, L2-F1R.**
- About 19.75× Tol-2's paths: (1.911/0.430)², checked by Seats 1, 2, 3.
- 100 m restore about 3.7 s against 2.14 s at 4 threads, and about 8.6 s at one thread (Seat 5). pluginval's watchdog would be exceeded.
- W1 rebuild 72–100 ms against the 50 ms target.
- 100 m bounce adds about 3 h (Seat 8 [Inf]); 8 instances at 100 m take about 15 s to load.
- Under any cap that protects restore, the 100 m cube (about 7× W_max) cannot reach the strict SE, so the certification fails where it costs most.
- Precision bought: 0.0187 dB, about 1/53 jnd.
- **Requires your override of Seat 5's veto.**

**Coupling.** D-T1.4's shipped SE target (0.083 dB) and D-T1.3's N rule hold as written under (a). Under (b) the target becomes 0.0187 dB and Q2 is forced toward (B) or (C).

---

## D-T1.1 update (from round 2)
- The ᶜ cells are resolved by NW-4C+ and N-3W\*\*:
  - S3 1/1 (work-capped, Seat 3's own NW-4C 1/1);
  - S4 1/1 (L2-F2 vetoed);
  - S6 1/1;
  - S7 1/1 (it says NW-4C meets its "NW-3 or NW-2" condition, plus CS-NW+, the cross-machine set and the wording).
- S5 1/1 is confirmed **on condition D7**, added to the determinism package (see D-T1.3), together with W_max as a cross-platform constant.
- T1-F\*: **max 1**, sum 18. Confidence medium (RQ-T1-4 is still uninformed).

---

## Summary

| id | decision | state | worst-off (cell) | sum | conf. | PRD bound | corpus basis | reversal |
|---|---|---|---|---|---|---|---|---|
| D-T1.1 | T1-F\* + D1–D7 | stands (ᶜ resolved) | 1 | 18 | medium | NFR-1/2/6, AX5, AX6 | Kuttruff Eqs. 4.24/4.29/4.35; Vorländer Fig. 11.38 | as in round 1 |
| D-T1.6 | NW-4C+ (blend; d_bn 0.70 m; flags and note as above) | proposed | S1 1/2 | 18 | medium | NFR-1, NFR-8, FR-SIM-6 | Kuttruff Eq. 2.50 (AX-row limit) | measured both-near fallback; near-corner reference > τ |
| D-T1.3 | N-3W\*\* (rule); W_max provisional 3.05 M | proposed + needs Maisara (Q2) | S1 2/2 | 20 | medium | NFR-1, NFR-2, AQ10, AX5 | Table 6.1 | Q2; n\*_max < 1 000; overrun |
| D-T2 | – | needs Maisara (Q1) | L2-F1R S5 2/3 | – | – | AX36 | – | her ruling |

## Challenges to settled decisions
1. **AX36 applied to an estimator (Q1).** Raised by Seats 1, 2, 3, 7, 8 and 9. Seat 2 now prefers the bias reading.
2. **AQ10 "recorded, not budgeted" (Q2, which extends Challenge 1).** A diffuse work cap sized to a restore time changes the output to meet a full-rebuild time.

No conflict found between `board.md` §1 and the PRD.

## For Maisara
- **Near walls (D-T1.6):** decided. When the listener or a source is near a wall, the plugin now samples from whichever end is safer, so the tail stays accurate with no model change. When **both** are near walls it can read low and is labelled "approximate". Seat 1 gave most; a measured fallback is its repayment.
- **How hard it works (D-T1.3):** decided except for the work limit. **Q2:**
  - size the limit to the 2-second project-restore budget, which leaves about ±1 dB of random tail-level error in rooms with one fully absorbing face (the old error there was +3.9 dB);
  - or spend about 11× more and risk slower loads;
  - or move the work off the load path in a later phase.
- **Precision rule (D-T2), Q1:** apply your 1 % rule to the method's bias, checked in CI, so users keep today's speed; or to every scene, at about 20× cost, which needs you to override Seat 5's veto.

Files:
- /home/user/makroof/docs/review/phase-05b2/22-orchestrator-C12.md
- /home/user/makroof/docs/review/phase-05b2/24-orchestrator-C13.md (the §2 table/summary mismatch)
- /home/user/makroof/docs/review/phase-05b2/23-seat1-round2-T1-T2.md … 23-seat9-round2-T1-T2.md
- /home/user/makroof/docs/review/phase-05b2/21-decider-decision-T1-T2-T6.md
