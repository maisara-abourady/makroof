# 5 — Decider, decision round 1: D-C1, D-C2, D-C3, D-C9 (phase 07c-1)

Saved verbatim by the orchestrator from the agent's report, 2026-11-12. Inputs: files 1–4.

## Decider decision round for D-C1, D-C2, D-C3 and D-C9 (phase 07c-1, 2026-11-12)

I decided all four, each by minimum tension. A second round is still needed on a few cells and is listed in §7. Nothing goes to Maisara (no NEEDS MAISARA), and I raise no challenge to a settled decision.

**Corpus:** revision `c1b171fe649f07cbeb952ef1f75d89bfaa414d0d`.

**Inputs read:**
- `/home/user/makroof/docs/review/phase-07c-1/` files 1, 2, 3-seat1 to 3-seat9 and 4.
- `docs/PRD.md`.
- AQ4 and AX18 (BUILD_PLAN L109 and L138).
- `docs/phases/phase-07c-1.md` and `phase-07.md` L224–235.
- phase-13-1, phase-13-2, and file 47 §4.
- `src/sim/tail/NoiseTail.cpp` L80–167.
- Vorländer §4.3 Eq. 4.14–4.16, §6 Eq. 6.4/6.5/6.7, Table 6.1.

### PRD digest
- **For whom:** producers and DJs on macOS and Windows, in any DAW, who know nothing about spatial audio.
- **Outcome:**
  - a reopened project restores "the scene and its render exactly, on any machine" (NFR-6);
  - "render state" is saved (FR-LIC-1);
  - movement is smooth and free of artifacts (NFR-3, FR-SIM-6);
  - the bounce is the deliverable (A4).
- **Hard bounds:**
  - NFR-8/FR-SIM-2: no scene-specific path; AX5: offline bit-identical on the same OS.
  - AQ4 (30 ms crossfade). AX18 is open only where this decision amends it.
  - AX40/AX44: E_b is independent of the seed and shared across modes and ears. AX41: W_max stays (A).
  - No `contractVersion` change; the phase-07 state rules apply (a version bump adds fixtures, old fixtures keep loading).
  - 07c-1 conditions 4, 5, 6, 9, 10 and 12, and A2.
  - No instance cap, no W_max cut, no per-host path.
- **Verification:** every DSP behaviour has an automated check; independent references are preferred; goldens are never regenerated to pass.

### Knowledge inventory (all four decisions)

| K | item | source | status |
|---|---|---|---|
| K1 | The saved quantity must be `bandsDiffuse` per emitter (reference units, fs-free up to rounding). The solve depends on gain, mixing constants, the AX22 cap, AX4 air and `DiffuseLimits`. | Seat 2, from the code | known |
| K2 | Level and waveform are separable. `make()` draws the same PCG stream for any length or T60, and output j depends only on noise j…j+2h (linear, no wrap). So a prefix tail, an old-T60 tail and the exact tail share the band noise up to rounding; only envelope, length and normalisation differ. | code, NoiseTail.cpp L83–85, L123–163 | known |
| K3 | Synthesis takes 3.14 of 3.29 s; ISM + matching + mix ≈ 0.15 s (100 m / 96 kHz). | AX38 4c | known |
| K4 | Solve at (A): 81–144 ms across the three OSes. | AX38 4c RG-1 | known (PROVISIONAL n) |
| K5 | An assembled IR is 18.4 MB; unit decays are ≈ 147 MB per instance (8 × 1.152 M × 2 × 8 B). | F/K5; Seat 3; arithmetic | known |
| K6 | AX16 errors: +3.83 dB, +2.38 dB; 26/345 case-bands > 1 dB; no generic predictor. | AX16 row; Seat 2 | known |
| K7 | Step under 07c-2: SE 0.13–1.33 dB (layouts 4/5). | AX41 | known |
| K8 | jnd of G and C80 = 1 dB (500–1000 Hz, paired comparison). | F1 | known as printed |
| K8′ | Within-stream detection threshold. | R4 | **uninformed: no study exists.** Bounds from F3 (< 0.5 dB audible in mono noise), F7 (direction only) and researcher D1 (a 1 dB tail step changes the overall level by 0.53 dB at D/R 0 and 0.92 dB at −10 dB). Closable only by measurement. |
| K9 | Host tolerance of a slow restore. | F8, F13, F14 | under-informed: setState may run on the UI thread while Processing; macOS reports hangs at 250 ms; Windows marks not-responding at 5 s; no host limit documented |
| K10 | Hosts that don't signal offline. | F16–F19 | under-informed: leads only |
| K12 | Practical cost of multi-MB state. | F20 | uninformed at vendor level |
| K13 | Crossfade cross term. | Vorländer Eq. 4.15; AX18 row | known. Working: equal-power with ρ = 1 gives mid-fade amplitude cos45° + sin45° = 1.414, i.e. +3.01 dB. Equal-gain gives 1, i.e. 0 dB, and never exceeds the louder endpoint (AX18, Cauchy–Schwarz). |
| K15 | Cost of a provisional tail and whether it meets 1 dB / 5 % EDT. | Seat 3 [Hyp] | uninformed; measured in this phase (see the AX49 reversal) |
| K16 | Tail step x ⇒ \|ΔG\| ≤ x and \|ΔC80\| ≤ x per band. | derived, below | known |

K16 working:
- G (Eq. 6.5): ΔG = 10log[(E_e + kE_t)/(E_e + E_t)], which lies in [0, x] for k = 10^(x/10).
- C80 (Eq. 6.7): ΔC80 = A − B, with A and B each in [0, x], so |ΔC80| ≤ x.

**Gaps K8′, K9, K10, K12 and K15 cannot be closed by documentation.** The researcher returned NOT READY. They close only through this phase's measurements and the condition 11 trace run (a person's action). For each decision I show whether a gap changes the winner (mostly no) or only triggers reversal. Each such trigger is named.

---

## 1. D-C3 and the storage half of D-C2 (Matter A)

**Tension map** (now/later; n.r. = not rated):

| opt | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 |
|---|---|---|---|---|---|---|---|---|---|
| A0 | 1/2 at 07c-2, load SE ≤ 1.33 dB | 0/1 honest; estimator change moves levels | n.r. | 1/2 interim step confused with the mode-parity check | 0/1 v2 needed anyway | n.r. ("rests on B2+D3") | 0/2, 3 if it ships in a release | 1/2 07c-2 step after listening starts | 1/1 exact in 07c-1 |
| A1 | 0/0 confirming solve is a free key test | 1/1 same inputs, step 0 | n.r. (ranking: "A1/A2 level + D3 prefer") | 0/1 with key K | 1/1 16 doubles, v2, fixtures | n.r. ("can live with") | 1/2 post-release update changes the mix (V4) | 1/1 a solve per load; a leak gives a step | 0/1 interim only |
| A2 as offered | 0/1 a wrong level ships if the key misses something | 2/2 incomplete key: a level outside AX43, silently | n.r. (prefer) | 0/1 with K | 1/2 stale value is authoritative; undo issue | n.r. (prefer) | 1/1 stated with the split key | 0/1 | 1/2 stale E_b in bounces and validation |
| A2 + S2/S5/S9 conditions, no split | 0/1 | 1/1 | n.r. | 0/1 | 1/1 | n.r. | **1/2 (read from conditions)**: without the split, A2 re-solves on an engine change, which is A1's stated later reason | 0/1 | 1/1 |
| A3 assembled | 0/0 | 1/2 | 1/2 | **1/3** (frozen copy of the chain) | 2/2 | 0/1 | 2/2 | 1/2 | 0/1 |

**Working:**
1. **Bounds.** None of the options breaks a bound.
2. **Vetoes.** A3 in assembled form is out (S4 later 3). A3 as unit decays only (S4's condition) is 147 MB per instance. S5 rated A3 2/2 and S7 rated it 2/2, so its max is 2.
3. **Worst-off seat.** A0, A1 and A2+conditions all have a max of 2 (S7 later in each).
4. **Composing.** S7's condition (the split key) would lower S7 to 1/1. It contradicts the reason behind S2's 2 and S9's 2 ("a level the current build would not produce"), and neither seat rated it. It also bites only on an engine-id change after the first public release, because 07c is a beta prerequisite (phase-13-2 scope 1; file 47 §4 (iii) 1). So I compose the following and defer the policy to its evidence point:
   - the **format** stores both key parts now;
   - the **policy** is "any mismatch: saved E_b not used". The split goes to Seats 2, 5 and 9 in the second round (§7).
5. **Sum** (n.r. cells excluded):
   - A1 = 0 + 2 + 1 + 2 + 3 + 2 + 1 = **11**
   - A2+conditions = 1 + 2 + 1 + 2 + 3 + 1 + 2 = **12**
   - A0 = 3 + 1 + 3 + 1 + 2 + 3 + 2 = **15**
   - **A1 wins by 1.** The result is sensitive to the n.r. cells. If the second round puts S3 + S6 on A1 at least 2 above A2, then A2+conditions wins. That would be a one-line switch, because the format is the same.
6. **Reversibility.** A1 and A2 are equal: same format.

**DECISION D-C3/D-C2(A): A1.** Exact text in AX48 (§5).
- **What is saved and how:**
  - Per emitter, `bandsDiffuse` as hex IEEE-754 bit patterns.
  - A two-part key:
    - **Scene part:** P = canonical hash of the `DiffuseProblem` after ISM planning (Seat 2), and S = hash of the effective scene excluding `outputMode`, `hrtfId` and `tailSeed` (Seat 4's K).
    - **Engine part:** E = hash of `DiffuseLimits` plus an estimator-version id, tied to the D5 golden, with a CI fingerprint test (Seats 2, 5 and 9).
  - The saved E_b is **interim only**. The solve always runs. On a P+E match the result is bit-identical, so there is no switch and the counter reads 0.
- **On an S+E match with a P mismatch (other OS or other fs):** the saved E_b is still the interim and the step is recorded. This is my composition, resting on Seat 2's fact (b) "rounding only", and it goes to Seat 2 in round 2.
- **State format:**
  - `pluginStateVersion` 2; v1 fixtures keep loading.
  - v2 fixtures assert only "loads, and a mismatch triggers a solve" (Seat 2). The key-match test builds its state in-process.
- **No waveform in state.** A3 and D4 are not adopted.

**PRD check:**
- NFR-6: on the same build A1 renders exactly the saved level and offline waits for identical bits. Across OSes, A1 and A2 both re-solve under P (ulp level, AX5).
- FR-LIC-1: render state is saved, since E_b, scene and seed determine the IR.
- A3 is not pointed to by the PRD: it is fs-tied, and not bit-identical across OSes (Seat 3), so it serves NFR-6 no better.

**Load-bearing claims:**
- **L1:** `bandsDiffuse` is fs-free up to rounding, and the amplitude depends on fs (Seat 2, from the code).
- **L2:** there is no 07c-1 path on which A1 and A2 sound different on the same OS (K1, K4, AX18 no-switch rule).
- **L3:** the engine-mismatch policy has no customer effect before release (phase-13-2 scope 1; file 47 §4 (iii) 1).

**Future-debt register:**

| seat | commits | undo cost | evidence | repaid |
|---|---|---|---|---|
| S2 1 | key completeness | key-format change, i.e. v3 | 07c-2 W_max raise (every pre-raise v2 state mismatches; team-only) | CI fingerprint and bit-equality tests green at 07c-2 |
| S4 1 | mode-independent key | v3 | Phase 09 mode switch | other-mode restore test at 09 |
| S5 1 | v2 forever; a v1 build rejects v2 state | none pre-release | 07c-2 (C) solve time; release | Phase 13 compat notes |
| S7 2 | post-release engine-change policy | none (format carries both parts) | first post-release engine-id change | board decision before that build ships |
| S8 1 | a solve per load | switch to A2 | 07c-2 load CPU | 07c-2 packet |
| S9 1 | presets never carry E_b | — | Phase 12 | phase-12 note |

**Strongest objection:** S7 later 2, together with Seat 6's preference for A2. It holds because before release the deferred split has no user effect, and the format already supports it. If the second round shows Seats 2, 5 and 9 rating the split at most 1, adopt it now and S7 falls to 1/1.

**Confidence: medium** (two seats n.r.; one composed key use). **Reversal:** the second-round cells (above); 07c-2's solve time at (C).

---

## 2. D-C2, the interim level (Matter B)

| opt | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 |
|---|---|---|---|---|---|---|---|---|---|
| B1 alone | 1/1 | 1/1 | n.r. | 0/1 | 0/1 "incomplete at load" | 0/0 "does not exist at load" | 0/1 | 0/2 | 1/1 |
| B2 | 0/2 (SE ≤ 1.33 at 07c-2) | 0/1 | n.r. | 0/1 | 0/1 | 0/2 (two steps per edit) | 0/1 | 1/1 | 0/2 (p95 ≈ 2.6 dB) |
| B3 | 3/3 | 3/3 | n.r. | 2/2 | 1/2 | 2/2 | 2/2 | 3/3 | 3/3 |
| B4 | 0/2 | 0/1 | n.r. | 0/1 | 0/1 | 0/1 | 0/1 | 0/1 | 0/2 |
| **B4-G** (composed) | **0/1 (read from conditions:** "lowered to 0/1 with the SE ≤ 0.5 dB admissibility gate") | 0/1 | n.r. | 0/1 | 0/1 | 0/1 | 0/1 | 0/1 | **0/1 (read from conditions:** "B2/B4 → 1" if the stage-1 per-band p95 can't exceed 1 dB; SE ≤ 0.5 ⇒ p95 ≈ 1.96 × 0.5 = 0.98 dB) |

**Working:**
1. **Bounds.**
   - B3 breaks condition 5: no generic predictor exists (Seat 2, K6; NFR-8). Seats 1, 2, 8 and 9 also rate it 3.
   - B1 alone breaks condition 5's "never silence" at a load without a saved E_b, because no source exists there.
2. **Worst-off seat.** B2 and B4 have max 2. B4-G (B4 plus Seat 1's and Seat 9's gate) has max 1 and raises no other seat.
3. **Sum.** B4-G = 8.

**DECISION D-C2(B): B4-G.**
- **Edits, `reset()` and prepare:** hold the previous diffuse E_b and recompute the specular part from the new ISM. This is Seat 2's B1′, taken as the exact meaning of "previous level". `reset()` keeps the IrSet (condition 10).
- **Load without a usable saved E_b:** the (A) solve. In 07c-1 this is the final solve, so the step is 0.
- **From 07c-2:** stage 1 is admissible only when its achieved SE is at most 0.5 dB in every band (AX41 diagnostics, NFR-8-clean). The fallback at load when stage 1 is inadmissible is **deferred to 07c-2's loop**, because the case is empty in 07c-1. The two sides are Seat 1 (take the step and record it) and Seats 6/9 (never at load; extend stage 1). It is decided on 07c-2's measured stage-1 times.
- **Residual against condition 9:** a v1-state load (pre-release projects only) has no admissible tail level until the background solve lands (≤ 144 ms, K4), because A2 forbids a synchronous solve and B3 is out. My reading: a v1 state carries no tail data, so condition 9's "a tail existed in the saved state" does not bind it. The interrogator should check this.

**Load-bearing claims:**
- **L1:** no generic predictor of AX16's error exists (Seat 2, citing the AX16 row; Seat 9 via Kuttruff §5.7).
- **L2:** in 07c-1, B2 equals the final solve (K4; AX41).
- **L3:** the 0.98 dB p95 figure, from the arithmetic above (normal approximation, per band; the family-wise rate across 8 bands is higher, and 07c-2 checks it).

**Future-debt register** (each seat later 1):
- S1 and S9: the gate and the fallback (07c-2 loop).
- S2: verify the prefix claim on `pathCount` and `pilotStops` (07c-2).
- S5: two submits per change (07c-2).
- S6: the load step (07c-2 run).
- S7: a two-stage solve to maintain.
- S4 and S8: interim parity, and the A/B on edits.
- All are repaid at 07c-2.

**Strongest objection:** the S1 vs S6/S9 fallback conflict is deferred, not resolved. It holds because the case has no instances in 07c-1. **Confidence: medium** (two cells read from conditions; S3 n.r.).

---

## 3. D-C1, the provisional-to-final step (Matter C)

| opt | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 |
|---|---|---|---|---|---|---|---|---|---|
| C1 | 1/2 | NMM | 1/1 | NMM | 0/0 | 1/2 | 0/0 | NMM | 1/2 |
| C2 | 0/1 | NMM | 1/2 (forces holds on B1) | NMM | 2/2 (not checkable at run time) | 0/1 | 1/1 | NMM | 0/1 |
| C3 | 0/1 | NMM | 1/2 | NMM | 0/1 | 0/1 | 1/1 | NMM | 0/2 |
| C4 | 2/3 | NMM | 1/1 | NMM | 0/1 | 3/3 | 0/1 | NMM | 2/2 |
| **C5′** (composed) | 0/1 (C5/C2 as rated) | NMM | **1/1 (read from conditions):** B1's step is outside scope, the 07c-1 fallback is empty, so no hold arises; equal-gain met | NMM (its condition is met: the mode switch is unchanged) | **1/1 (read from conditions):** "a design-time bound per source … brings it to 1" | **0/1 (read from conditions):** C2's 0/1; load fallback = saved E_b plus the provisional tail | **1/1 (read from conditions):** C2's "extra refusal path" | NMM (its condition is met: covers realtime captures) | 0/1 (C2) |

**Working:**
1. **Vetoes.** C4 is out (S1 later 3; S6 3/3; and condition 5 "stays within Seat 1's ruling" has nothing to stay within).
2. **Worst-off seat.** C1, C2 and C3 each have max 2. C5′ has max 1.
3. **Sum.** C5′ = 9.

**Seat 3's condition is a plan-default change.** Seat 3 conditioned every C option on equal-gain (otherwise all rise to now 2). Seats 1 and 5 raised the same point. AX18's own rationale says equal-gain is the closer law where ρ ≥ 0.414, and K2/K13 give ρ ≈ 1 for these steps. **This amends AX18**, a plan default; the amendment is part of this decision (§5).

Seats 6 and 8 rated D3 assuming "unrelated noises under equal-power". That premise is false from the code (K2). I do not re-rate them, and §7 asks them.

**DECISION D-C1: C5′ (AX47).**
- **Bound:** at most 1 dB per band, in all 8 bands.
- **Admissible sources:**
  - a matching saved E_b (step 0);
  - the provisional tail (its bound shown by test);
  - the 07c-2 stage 1 at SE ≤ 0.5 dB.
- **Every step** is measured from the two IRs' band levels on the builder thread and recorded.
- **Scope:** excludes the user's own edit (B1).
- **Crossfade law:** equal-gain for same-scene steps.
- **Fallback when no source is admissible at load:** 07c-2's loop.
- **The number is Seat 1's ruling** under its mandate.
- **The A4 test asserts on IR band levels, not on 50 ms pink-noise windows.** Statistical reason: a 63 Hz octave holds only about 3 cycles in 50 ms, so the window variance would swamp a 1 dB bound. Seat 1's noise/speech render remains the check that no mid-fade value exceeds the louder endpoint.

**Load-bearing claims:**
- **L1:** Table 6.1 jnds (F1, corpus).
- **L2:** K16 (derived from Eq. 6.5 and 6.7).
- **L3:** K13 (+3.01 dB for equal-power at ρ = 1; derived from Eq. 4.15).
- **L4:** K2 (code).
- **L5:** researcher D1 arithmetic: at D/R −10 dB a 1 dB step is a 0.92 dB overall change, above F3's 0.5 dB figure in noise. Seat 1 accepted this residual for wet steady noise.

**Future-debt register** (later 1 each):
- S1: R4 / the within-stream threshold. Evidence: the 07c-2 self-ABX (16 trials, layout-4 capped scene, noise and speech). Repaid when the ABX is done; the bound goes to 0.5 dB if a < 1 dB step is detected.
- S3, S5, S7: refusal-path tests; 07c-2.
- S6: automation-driven steps count as unprompted; Phase 10, Seat 1 rules.
- S9: the occupied-hall preset in the A4 set; Phase 12-2.

**Strongest objection:** K8′ is uninformed. If within-stream detection proves below 1 dB on music, C3 wins. That is the named reversal. **Confidence: low–medium** (4 cells read from conditions; K8′).

---

## 4. D-C9, the interim tail while the synthesis is pending (Matter D)

| opt | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 |
|---|---|---|---|---|---|---|---|---|---|
| D1 at load | **3/3** | NMM | **3**/2 | 2/2 | 1/2 | **3/3** | 2/2 | 2/2 | n.r. ("a different room") |
| D2 (edits) | 1/1 | NMM | **3/3** | 1/2 | 1/1 | 2/2 | 0/0 | 1/1 | n.r. |
| D3 | 1/1 (≤ 1 dB and EDT within 5 %) | NMM | 1/1 | 1/2 | 2/2 | 1/1 | 1/1 | 1/1 | n.r. (D3 preferred over D5) |
| D4 / A3 assembled | 0/0 | NMM | 1/2 | **1/3** | 2/2 | 0/1 | 2/2 | 1/2 | n.r. |
| D5 (edits) | 1/2 | NMM | 1/1 | 1/1 | 1/1 | 1/2 | 0/1 | 2/1 | n.r. |
| **D3\*** (D3 with seat conditions, placement below) | 1/1 | NMM | 1/1 (its ranking prefers D5/D6 on edits) | **1/1 (read from conditions:** R, per-mode coherence, as a 08/09 debt) | **1/1 (read from conditions:** outside the gate, cost records, offline-bypass test) | 1/1 | 1/1 | 1/1 | n.r. |

D6 (Seat 3's own option) was rated by nobody, Seat 5 included. It is not decidable this round.

**Working:**
1. **Bounds.** **My reading of condition 9 (for the interrogator):** "never silence where a tail existed in the saved state" sits in the clause about "the interim tail while the synthesis is pending". Its subject is the tail. So D1 at load (about 3.3 s with no tail) is out at step 1 for every scene whose saved state had a tail. This also excludes even a short early-only first IrSet at load, hence the synchronous placement below. D1 remains only for tailless (AX22) scenes. D2 at load is D1.
2. **Vetoes.**
   - D1 at load: S1, S3 and S6 rate it 3.
   - D2 on edits: S3 rates it 3 (condition 4).
   - D4 assembled: S4 rates it 3.
   - D4 as unit decays only: max 2 (S3, S5, S7).
3. **Worst-off seat.** D5 has max 2. D3\* has max 1.
4. **The R2 contingency does not change the winner.** Seat 5 said D3 later goes to 3 if a common host doesn't signal offline (K10). In that world, D1 and D2 get the same contingent 3, and D4 still carries S4's 3 or is the 147 MB unit-decay form. D3\* is chosen in both worlds. R2 decides only whether D3 then carries a veto, which would mean re-convening Seat 5 and, if it holds, NEEDS MAISARA case (c).

**DECISION D-C9: D3\* (AX49).**
- **What the provisional tail is:** the same `BandNoiseGenerator`, seed and stream as the exact tail, at a prefix L_p set by a generic rule; normalised to expected energy; faded over its last 50–100 ms; at the interim level.
- **Built synchronously** where no IrSet valid at the current fs is current: project load, first restore, and prepare with an fs change. This keeps condition 9 literal.
- **Built in the background, concurrently with ISM planning,** where one is current: undo or preset recall during playback, and T60-changing edits. The current IrSet plays until the new one is ready. A restore of a scene identical to the current one keeps the current IrSet (AX18 no-switch).
- **Then the exact tail**, with an equal-gain step.
- **Offline never uses it**, and it runs outside the gate.
- **Seat 5's submit rules apply:** an interim submit never marks its generation as handled, and there is a monotonic (generation, stage) check under `stateMutex_`.

**PRD check:** NFR-6 (the room is present from the first second); FR-SIM-6/NFR-3 (no +3 dB bump); A4 (offline exact). D5 strains NFR-6 on edits only. D1 and D4 are out on bounds or vetoes.

**Load-bearing claims:**
- **L1:** K2 (code), so the provisional-to-exact step is coherent and crossfades equal-gain.
- **L2:** K3 (the tail gap D3 removes).
- **L3:** my reading of condition 9 (above).
- **L4:** K15 is unknown, and AX49 makes it an acceptance test.

**Future-debt register** (later 1 each):

| seat | commits | evidence | repaid |
|---|---|---|---|
| S1 | provisional within 1 dB, EDT within 5 % | condition 9 packet | test green |
| S3 | second use of the generator | packet | test |
| S4 | per-mode coherence of the provisional | Phase 08/09 | phase-08/09 check |
| S5 | sync restore time; R2 | packet; condition 11 trace | Phase 13 host matrix |
| S6 | ISM wait on T60 edits | record (g) | Phase 10 split update |
| S7 | R3 dialogs at 8 × ~0.3 s | trace run | Phase 13 |
| S8 | realtime captures print the provisional | trace run | Phase 13 |

**Strongest objection:** the synchronous provisional cost is [Hyp] (Seat 3: 0.08–0.2 s), and Seat 1's EDT condition may need a long L_p at an 8 s T60.

**Reversals:**
1. If no generic L_p meets 1 dB and EDT within 5 % with a synchronous restore of at most 0.5 s per call at 100 m / 96 kHz (Seat 5's R1 threshold), D-C9 returns to the board with D4 in unit-decay form and R5.
2. If the condition 11 trace shows a common host not signalling offline by default, re-convene Seat 5.

**Confidence: medium.**

**Which options commit memory** (the orchestrator's question):
- **A3/D4** commit **project-state size**: 18.4 MB raw per instance for the assembled IR (≈ 24 MB as base64 XML, Seat 5, from the code), or ≈ 147 MB for unit decays. Multiplied by host autosave and undo snapshots, which are undocumented (F20).
- **D6** commits **resident RAM**: 8 × 1.152 M × 8 B = 73.7 MB per emitter, ≈ 147 MB per instance at 96 kHz / 12 s, ≈ 1.2 GB at 8 instances. That is on top of the cached unit decays, which are the same size (double vectors, from the code).
- **D3** commits only transient memory for a prefix-length FFT.
- None of A3, D4 or D6 is adopted.

---

## 5. Exact rows for BUILD_PLAN §2 (AX46 is the last row; next are AX47–AX49)

**AX18, append before "Amended by…":**
> **Same-scene steps (phase 07c-1 loop 2026-11-12, AX47):** an IrSet that replaces an interim IrSet of the same scene uses **equal-gain**: saved or interim E_b → final level, and provisional → exact tail (AX49). The early parts are identical, and the tails share the same band noise (from the code: `BandNoiseGenerator::make` draws one PCG stream; output j depends on noise j…j+2h only), so ρ ≈ 1. Equal-power would raise the mid-fade by 10·log10(1+ρ) ≈ +3.0 dB (Eq. 4.15 cross term). The first IrSet after a restore fades from silence (the law is immaterial). A restore over a current IrSet of another scene (undo, preset recall) and the output-mode switch stay equal-power.

**| AX47 |**
> **Provisional-to-final step (D-C1, Seat 1's ruling).** For one scene, every step from an interim IrSet to a later one changes the tail level by at most **1 dB in each of the 8 octave bands (63 Hz–8 kHz)**, hence G and C80 by at most 1 dB per band.
>
> **Admissible interim sources** (each with a bound known by construction):
> - a saved E_b whose AX48 key matches (step 0; bit-identical, no switch);
> - the AX49 provisional tail (bound shown by the A4 test);
> - from 07c-2, the stage-1 (A) estimate only when its achieved SE ≤ 0.5 dB in every band (AX41 diagnostics; NFR-8).
>
> **Measurement:** every such step is measured on the builder thread from the two IRs' band levels and recorded (diagnostic + counter; never in the callback). The test asserts on IR band levels; the wet pink-noise and speech renders check that no mid-fade value exceeds the louder endpoint.
>
> **Scope:** excludes the step the user's own edit causes (B1; AX38 (iv) staleness records). Same-scene steps are equal-gain (AX18).
>
> **Deferred:** the rule when no admissible source exists at load is empty in 07c-1 and is decided in phase 07c-2's loop on measured stage-1 times.
>
> **Reversal:** if 07c-2's within-stream check shows a < 1 dB step detected, the bound becomes 0.5 dB.

Rationale column: "Vorländer Table 6.1 (G and C80 jnd 1 dB at 500–1000 Hz; paired comparison; researcher R4: no within-stream study found). A tail step x moves G (Eq. 6.5) and C80 (Eq. 6.7) by at most x. Researcher D1: at D/R 0 dB a 1 dB tail step is 0.53 dB overall, at −10 dB 0.92 dB; Zotter & Frank §4: < 0.5 dB audible in mono noise; this residual is accepted by Seat 1. Board D-C1, ledger rows." Phases: 07c-1, 07c-2, 10.

**| AX48 |**
> **Saved diffuse level and interim level (D-C2, D-C3).**
>
> **State format:** `pluginStateVersion` 2 adds, per emitter, `bandsDiffuse` (8 doubles, reference units; never amplitudes or E_target) as hex IEEE-754 bits, with a two-part key:
> - **scene part:** P = canonical hash of the `DiffuseProblem` after ISM planning, and S = canonical hash of the effective scene without `outputMode`, `hrtfId` and `tailSeed` (AX40, AX44);
> - **engine part:** E = canonical hash of `DiffuseLimits` (W_max, n\*_max, SE_target) plus an estimator-version id. The id is bumped with every D5-golden regeneration (a test checks that the golden records it). A CI fingerprint test fails when E_b on a fixed fixture changes without a bump.
>
> **Role of the saved E_b:** the **interim** level only (A1). The background solve always runs. On a P+E match its result is bit-identical (no switch; AX47 counter 0). On an S+E match with a P mismatch (other OS or fs; rounding) it remains the interim and the step is recorded. On an E mismatch it is not used. Until a board decision, which falls due before the first post-release build that changes E, the saved E_b is never final. Seat 7's proposal (saved E_b stays authoritative; PRD NFR-6, FR-LIC-3, NFR-7) is recorded.
>
> **Without a usable saved E_b (B4):**
> - edits, `reset()` and prepare hold the previous diffuse E_b, with the specular part recomputed from the new ISM;
> - at load, the (A) solve (in 07c-1, the final), admissible from 07c-2 only under AX47's gate;
> - never the AX16 level (no generic predictor of its error).
>
> **Not saved:** no tail waveform or IR.
>
> **Tests and fixtures:**
> - v1 fixtures keep loading;
> - v2 fixtures assert only "loads; a mismatch triggers a solve";
> - the key-match test builds its state in-process;
> - a v2 state restored in the other `outputMode` uses the saved E_b bit-identically;
> - an output-mode, HRTF or seed change never re-solves.

Rationale column: Seat 2's code facts (fs only through rounding; the problem hash is complete by construction); minimum tension (file 3-seat1…9); phase-07 state rules. Phases: 07c-1, 07c-2, 08, 09, 12, 13.

**| AX49 |**
> **Interim tail while the unit-decay synthesis is pending (D-C9).**
>
> **What it is:** a **provisional tail** from the same `BandNoiseGenerator`, seed and emitter stream as the exact tail, at a prefix length L_p set by a generic rule from the T60s and fs (NFR-8). It is normalised to expected unit energy (`expectedUnitEnergyPer10ms`), faded out over its last 50–100 ms, and played at the AX48 interim level.
>
> **Where it is built:**
> - **synchronously** with ISM + matching + mix wherever no IrSet valid at the current fs is current (project load, first restore, prepare with an fs change), so the first IrSet carries a tail (condition 9);
> - **in the background**, concurrently with ISM planning, wherever one is current (undo or preset recall during playback, T60-changing edits). The current IrSet plays until the new one is ready.
>
> **Unchanged:**
> - a restore of a scene equal to the current one keeps the current IrSet;
> - position-only edits keep the cached unit decays (AQ4);
> - `reset()` follows condition 10.
>
> **Handover and offline:**
> - the exact tail replaces the provisional with one AQ4 crossfade, equal-gain (AX18);
> - offline renders, bounces and `render_cli` never use it (AX5, condition 6);
> - it runs outside the diffuse gate.
>
> **Submits:** an interim submit never records its generation as handled; every submit passes `decide()` under `stateMutex_` with a monotonic (generation, stage) check.
>
> **Acceptance:**
> - the provisional's band levels are within 1 dB of the exact tail's (AX47) and its EDT within 5 % (Table 6.1), on the A4 scene set plus the 100 m low-α cube at 48 and 96 kHz;
> - a `[pipeline]` test shows offline bypasses it;
> - its cost is printed at 1, 4 and 8 instances in records (c), (d) and (f), and the synchronous restore time with the provisional is in the condition 9 packet.
>
> **D1 (early part alone)** is allowed only for tailless scenes.
>
> **Reversal:** if no generic L_p meets the acceptance bounds within a synchronous restore of ≤ 0.5 s per call at 100 m / 96 kHz, or the condition 11 trace shows a common host not signalling offline by default, back to the board.
>
> **Recorded for Phase 10:** D5 (old-T60 waveform matched at t_mix to the old ebar) and D6 (cached pre-envelope noise, ≈ 147 MB per instance at 96 kHz).

Rationale column: code facts K2/K3; min-tension working (D1, D2 and D4 vetoed). Phases: 07c-1, 08, 09, 10, 13.

---

## 6. Phase-file edits the debt register implies

**phase-07c-1:**
- A1 cites AX47–AX49.
- Condition 9 and A2: "the restore gate measures ISM + matching + **the AX49 provisional tail (restore with no current IrSet)** + mix; without the exact unit-decay synthesis". Condition 7's re-pin includes it.
- A4: AX47 tests (Seat 1's items 1–4), plus BRAS CR3 (Seat 9).
- A7: state v2 per AX48.
- A8: the other-`outputMode` restore test.
- F3/F5: AX47 and AX48.
- Listening: add **L4** "Reopen a saved 100 m project and play at once: the tail is there from the first second; no jump when it settles."

**phase-07c-2:**
- AX47's SE gate.
- A **decision item**: the load fallback when stage 1 is inadmissible (Seat 1 vs Seats 6/9), decided on measured stage-1 times.
- The W_max raise changes AX48's E: pre-raise v2 states re-solve.
- Verify Seat 2's prefix claim (`pathCount`, `pilotStops`).
- Maisara's self-ABX, 16 trials, capped layout-4 scene, noise and speech. This is the reversal test for AX47's 1 dB.
- Check the family-wise all-band rate of the SE gate.

**phase-08 / phase-09:**
- The AX49 provisional tail gets the same per-mode decorrelation and coherence target as the exact tail (Seat 4 R).
- Extend the AX44/AX48 test to stereoSpeakers.
- A mode switch never re-solves and adds no level step.

**phase-10:**
- Record (g)'s ISM delay from the concurrent provisional on T60 edits is an input to the AX38 (v) split update.
- D5 and D6 are recorded alternatives for room-size automation.
- Whether automation-driven steps count as unprompted under AX47: Seat 1 rules (Seat 6).

**phase-12:** presets never carry E_b; preset validation always runs the solve (Seat 9).

**phase-13-1 / 13-5:**
- The board decides AX48's engine-mismatch policy before the first post-release build that changes E.
- The condition 11 trace results on offline signalling, restore thread and timing (R1/R2/R3/R5) go to the host matrix and trigger the AX49 reversal check.
- Compat notes: a v1 build rejects v2 state.
- Seat 7's wording:
  - never "opens instantly";
  - "offline export waits for the final room in hosts that signal offline rendering";
  - no cross-machine bit-identity claim.

---

## 7. Second round (run in parallel with the interrogator; it does not stop the code)

| seat | what to rate |
|---|---|
| S2 | (a) AX48's S+E-match interim use; (b) Seat 7's split policy |
| S3 | A0–A2 and B1–B4 numbers; D3\* on T60 edits with the ISM waiting on the concurrent provisional |
| S5 | confirm the cells read for C5′ and D3\* (synchronous placement); the split |
| S6 | A0–A3 numbers; C5′; D3\* under equal-gain on coherent noise |
| S7 | C5′; whether format-now with the policy decided before the first post-release engine change meets its condition |
| S9 | D1–D5 numbers; B4-G; the split |
| S1 | B4-G; the synchronous D3\* and its EDT test |
| S4 | the R-as-08/09 debt read 1/1 |
| S8 | D3\* placement |

**What would flip a decision:**
- **Matter A flips to A2** if S3 + S6 rate A1 at least 2 above A2.
- **The split is adopted now** if S2, S5 and S9 rate it at most 1.

---

## 8. Summary

| id | decision | state | worst-off | sum | conf. | PRD bound | corpus basis | reversal |
|---|---|---|---|---|---|---|---|---|
| D-C1 | AX47: ≤ 1 dB per band, all 8 bands; admissible sources; equal-gain (AX18 amended) | proposed | 1 (S1, S3, S5, S6, S7, S9) | 9 | low–med | NFR-3, FR-SIM-6, NFR-6 | Table 6.1; Eq. 4.15, 6.5, 6.7 | 07c-2 within-stream ABX |
| D-C2 | AX48 B4-G | proposed | 1 | 8 | med | NFR-6, NFR-8 | — (AX16, AX41) | 07c-2 stage-1 times |
| D-C3 | AX48 A1, state v2 | proposed | 2 (S7 later) | 11 | med | NFR-6, FR-LIC-1 | — | round-2 cells; post-release policy |
| D-C9 | AX49 D3\* | proposed | 1 | 14 + S9 | med | NFR-6, condition 9, A4 | — (code) | L_p/EDT/sync ≤ 0.5 s; condition 11 R2 |

**Challenges to settled decisions:** none.

### Decided for Maisara
Each line is applied once it survives the interrogator; she may veto any of them afterwards.

- **AX47:** the reverb may settle by at most 1 dB per band, and only from sources whose error is known in advance (NFR-3, FR-SIM-6, NFR-6). C1 strains FR-SIM-6 by allowing audible self-steps; C3 serves the same ids at more 07c-2 cost; C4 strains FR-SIM-6.
  - Seat 3 gave most: it carries a refusal path. It gets equal-gain everywhere.
  - Amends plan default AX18, not one of her decisions.
- **AX48:** the solved room level is saved in the project as an interim, and the engine always confirms it (NFR-6, FR-LIC-1, NFR-8). A2 serves the same ids equally in 07c-1; A0 strains FR-LIC-1 ("render state"); A3 serves NFR-6 at load but is fs-tied and vetoed.
  - Seat 7 gave most: its post-release key split is deferred. It gets the format now and a dated board decision.
- **AX49:** a reopened project plays a provisional tail from the first second, which then settles into the exact tail; bounces always use the exact one (NFR-6, condition 9, A4, NFR-3). D1 breaks condition 9; D5 strains NFR-6 on edits.
  - Seat 5 gave most: the restore does more synchronously. It gets measured records and a 0.5 s reversal.

**NEEDS MAISARA:** none.

