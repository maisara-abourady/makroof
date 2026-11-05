Corpus revision: c1b171fe649f07cbeb952ef1f75d89bfaa414d0d (`docs/corpus/SOURCE_COMMIT`).

## PRD digest
- **For whom:** producers and DJs who don't need to understand spatial audio (PRD "Target users").
- **Outcome:** the user describes a space and hears the track as if played there. Accuracy is a quality gate, "measured match against real impulse responses + listening tests" (PRD metrics table, "Validation").
- **Priority order:** NFR-1 accuracy first ("Accuracy is the top priority"), then NFR-3/FR-SIM-6 artifact-free movement, then NFR-2 (heavy CPU is acceptable when it buys accuracy), NFR-6 persistence, NFR-8 generic engine. FR-SIM-2: no preset-specific logic.
- **Hard constraints:** NFR-8 (no scene-specific code in `src/sim`); AX5 determinism; AQ10 rebuild time ≤ 50 ms (Phase 03 already misses it; misses are recorded, not optimised); the Phase 10 cache of the unmatched unit decay; the contract rules (CLAUDE.md); PRD out of scope: multichannel, user-controlled atmosphere, crowds.
- **Verification culture (CLAUDE.md):** every DSP behaviour is checked automatically; independent references are preferred over self-made goldens; goldens are never regenerated to make a test pass; AX11 statistical gates are set at 3σ.
- **PRD silent on:** what counts as "accurate" (Q9 → AQ9 defaults), and any rule for the mixing time or for diffuseness.

---

## D1. Mixing-time rule: closing "Expert may revise"

**Restatement.** Phase-04 scope 2 and the Risks section leave the t_mix,e rule open to Expert revision. The choice is whether to close that, and what Phase 05 result would change the rule. It drives `MixingTime.cpp`, the AX20 image-list length, rebuild cost and the Phase 05 handover comparison.

**Validity screen.**
- The corpus has no rule. Vorländer §11.7 says there is "no simple rule for choosing the late-response parameters and the transition time" (re-read).
- So the rule cannot be derived by reasoning. Its consequences are empirical.
- The k_eff ≥ 19 part is a statistical design criterion, not a claim about how rooms behave: σ = 4.34/√19 = 0.996 dB (Vorländer Eqs. 11.9/11.17), against the 1 dB jnd of G (Table 6.1, stated for 500–1000 Hz). It stays valid as framed.
- One flaw in the arbiter as written. Phase-05 scope 6 compares the 80/140 ms floors with the Phase 04 rule, but does not say on which IR. On the Phase 04 IR (specular-only before t_mix, AX21), a later floor lengthens the stretch with no scattered energy. The comparison would then mostly measure AX21, not the handover. The consult's own check (ledger, falsifiable check 4) required "with item 3 in place", i.e. with early scattering present.
- A second gap: the scope compares simulation with simulation (">1 jnd apart") and never says which handover is closer to the measured IR.

**Scoring.**
- NFR-1: served only if the arbiter compares against BRAS, on an IR that has early scattered energy.
- NFR-3: neutral. The floor only raises the lower bound (D14), so t_mix,e stays continuous in position.
- Testability: the simulated IRs are deterministic, and the measured IR is the same in both arms of the comparison, so the difference between arms is paired and needs no statistical margin.
- Cost: a 140 ms floor lengthens the AX20 list. The rebuild time against AQ10 must be measured if that floor is adopted.
- Reversibility: high (one constant, set through an AX change).

**DECISION: close the "Expert may revise" question, with Phase 05 as the arbiter.**
- Replace "The Expert may revise the rule" (scope 2) and the Risks item "Expert question (mixing time)" with: *"No corpus rule exists (Vorländer §11.7); the rule is revised only on the Phase 05 handover evidence (phase-05 scope 6)."*
- Add to phase-05 scope 6, "Mixing-time handover": *"Run the three handovers (Phase 04 rule, floors t_dir,e + 80 ms and + 140 ms) on both the Phase 04 IR and the reference-hybrid IR. The reference-hybrid run is the arbiter. For each, report the AQ9 error metric (mean |sim − meas|/jnd at 500 Hz, 1 kHz, 2 kHz; 500–1000 Hz mean also printed) for EDT and C80."*
- **Trigger for a change:** a floor replaces the current lower bound (via an AX change, raising the lower bound only, per D14) only if, on the reference-hybrid IR, all three hold:
  - (a) it moves EDT or C80 by more than 1 jnd (EDT 5 %, C80 1 dB, Table 6.1) in at least one evaluable pair;
  - (b) it lowers the room-averaged mean |error|/jnd of both EDT and C80;
  - (c) it makes no room worse by more than 1 jnd.
- Otherwise the current rule stands and the question is closed.

**Confidence:** medium. The corpus supports the absence of a rule and the jnds; the arbiter design is a product choice under NFR-1.
**Reversal condition:** the Phase 05 reference-hybrid handover result meeting (a)–(c); or the B11 promotion phase, whose rendered early scattering changes what the handover hands over. The comparison is re-run there.

---

## D2. A threshold for when a field counts as diffuse

**Restatement.** Should the product have a numeric diffuseness threshold, and does any code path or gate depend on one?

**Validity screen.**
- The corpus has none. Kuttruff §8.5 calls it an "Open question: is diffuseness a quality parameter in its own right" (re-read). Its measured directional diffusivity d needs a directional microphone and is "comparable only for similar microphones".
- Per-axis energy shares are only a necessary condition: three equal flutter pairs also read 1/3 each (ledger row 5, rebuttal).
- Any threshold would be invented, so a gated threshold is not supported.

**Dependency check.**
- From the plan: the only branch in `src/sim` that reacts to a sparse field is the AX22 switch, k_real < 19 at 500 Hz–2 kHz.
- That is a level-precision criterion (Vorländer Eqs. 11.9/11.17), not a diffuseness criterion, and Maisara settled it (D6–D8).
- Per-axis shares, k_real and realised σ are "reported, not gated" (phase-04 scope 3). Phase 10 depends on the AX22 switch point only.
- From the code: `src/sim` has no tail or mixing-time code yet. No gate or code path depends on a diffuseness threshold.

**DECISION: close it. No threshold is needed.**
- Replace "a diffuseness criterion is an Expert question" (BUILD_PLAN §4 Phase 04 Risks, phase-04 Risks) with: *"No diffuseness threshold: no code path or gate needs one (AX22 uses realised k, a precision criterion), and the corpus gives none (Kuttruff §8.5)."*
- One cheap addition keeps evidence available: Phase 05 prints the Phase 04 render's per-axis energy shares and k_real per pair, next to the existing non-diffuseness indicators. Reported only.
- Reopen only if a later phase proposes branching on diffuseness, for example a decay predictor chosen per room under B12. That would be a new AX decided on Phase 05 evidence.

**Confidence:** high (Kuttruff §8.5; PRD NFR-8; no dependent path in the plan).
**Reversal condition:** a future phase design (B12 or B2) that wants a diffuseness branch.

---

## D3. Remaining scattering-absorption bias (X-b)

**Restatement.** AX16 gives a path's scattered energy that path's own (1−α) product, which sets the tail level E_b.
- With uniform α this is exact. Kuttruff §5.2: after n reflections, specular plus non-specular is (1−α)^n (re-read).
- With uneven α the scattered energy should take the absorption of the walls it actually meets next (Kuttruff §4.6, Gilbert, re-read). The sign of the error depends on the case, as with Table 5.2's Lambert cases, which fall on both sides of Eyring (re-read: case 4 gives 1.21 against 1.38 s; case 6 gives 5.93 against 4.61 s).
- There is also an unquantified per-path hit-count residual.

**Validity screen.**
- "Accept as is, unbounded": this conflicts with NFR-1 because the size is unknown.
- "Remove now": not possible without the B11 propagation, which is not yet validated (B11).
- "Bound, then remove through B11": valid.

**Scoring.**
- The bias is a deterministic model-versus-model difference, so it can be measured exactly. The Phase 05 reference hybrid propagates scattered energy through Lambert patches with mixed s, so its gathered diffuse energy in the matching window takes the absorption of the walls actually met.
- It does not need BRAS. It can be run on synthetic rooms, which also isolates the uniform-α residual.
- Tolerance: 1 dB (G jnd, Table 6.1, 500–1000 Hz). The k ≥ 19 rule already spends a 1 dB precision budget on the same level, so a bias of that size would double the error.

**DECISION: bound it in Phase 05; remove it only through B11.**
- Add to phase-05 scope 6, "Reference hybrid": *"Report per band (500 Hz–2 kHz; other bands for information) ΔL_b = 10·log10(E_target,b(AX16) / E_target,b(hybrid)), both in the same Hann window [t_dir,e + 2.5 ms, t_mix,e] and both referred to t_mix,e. Compute it for every BRAS pair and for the six Phase 04 test rooms. The test rooms have uniform α per face set, so they isolate the hit-count residual. Also compute it for Kuttruff Table 5.2 layouts 2, 4, 5 and 6 with the solver called directly."*
- **How to read it:**
  - If |ΔL_b| ≤ 1 dB everywhere: X-b is accepted as is. Record the measured bound in AX16 and close the row.
  - If |ΔL_b| > 1 dB anywhere: the B11 phase must switch tail-level matching to the hybrid's propagated diffuse energy. This holds even if rendering early scattering is not promoted, and it is subject to the same independent-reference validation (D4 (A)).
- The result is model against model. It bounds what B11 would change; it is not a measured truth.

**Confidence:** medium. The mechanism is in the corpus (§5.2, §4.6, Table 5.2); the 1 dB criterion is a product choice anchored to Table 6.1.
**Reversal condition:** the Phase 05 ΔL_b values; or the §9.8 ray-tracer validation in the B11 phase showing that the hybrid's propagated energy is itself off by more than 1 dB.

---

## D4. Acceptance rule for promoting the B11 hybrid into `src/sim`

**Restatement.** When does the Phase 05 Python reference hybrid (early Lambert-scattered energy) get built into the simulator? This decides AX16, AX21, the `open_field` check and rebuild cost.

**BRAS data check.**
- Phase 05 does not name its rooms. It says only "likely the small seminar room and similar", and the choice is recorded later in `docs/validation/bras_mapping.md`, which doesn't exist yet.
- Nothing in the repo or the corpus tells how many BRAS rooms have uneven absorption or low s. **It is unknown until the Phase 05 session reads the BRAS documentation, and it may be one room.**
- So the rule cannot rest on BRAS alone.

**Validity screen.**
- A check at s = 1 alone is circular (ledger C3, B11), so it is rejected as the only check.
- An s-stratified BRAS-only rule with a minimum room count is not viable, because the count is unknown.
- What survives: independent reference first, with BRAS as a paired real-room check.

**Scoring.**
- NFR-1: the deficit is corpus-backed. The scattered fraction s(1−α) per reflection dominates after a few orders (Kuttruff §5.2, Fig. 5.3; Vorländer §11.6), and the round robins found a scattering model essential (Vorländer §11.5).
- The upper-estimate step grows with s (0.9 dB at s = 0.05 up to 8.7 dB at s = 0.4, AX21). So the rooms where B11 matters most are high-s rooms, not low-s ones. Few low-s rooms in BRAS costs little evidence where the stakes are small.
- Testability: the §9.8 partially diffuse ray tracer (re-read: scatter if z₃ ≤ s; 10⁵–10⁶ particles) covers any s and α layout synthetically. On BRAS, the measured IR is shared by both arms, so the comparison is paired.
- AX5 / the Phase 10 cache: the early diffuse energy depends on positions, so it is rebuilt each time, not cached.
- AQ10: rebuild time must be measured and recorded.

**DECISION (wording for B11 and the promotion phase).** Promote only if (A) and (B) both pass.
- **(A) Independent reference (CI gate in the promotion phase).**
  - Rendered energy envelope (ISM specular + hybrid diffuse) against a Kuttruff §9.8 partially diffuse ray tracer, seeded, in 10 ms bins up to t_mix,e, all 8 bands, within ±1 dB per bin.
  - A bin is gated only where the tracer's effective count k = (ΣE)²/ΣE² is ≥ 171, so its own 3σ = 3·4.34/√171 = 0.996 dB (AX11 convention, as FQ-12). At least 3 gated bins per case.
  - Cases: s = 0.1, 0.25, 0.4; uniform α; and Table 5.2 layouts 4, 5 and 6 with the solver called directly.
  - Also re-derive the `open_field` check against the Lambert estimate (−23 to −43 dB per band, ledger OF).
- **(B) BRAS paired check (Phase 05 numbers).**
  - Metric: the AQ9 metric for EDT and C80, i.e. mean |sim − meas|/jnd over 500 Hz, 1 kHz and 2 kHz per pair, averaged over pairs per room and then over rooms with equal room weight. The 500–1000 Hz mean is also printed.
  - Simulated values come from AX11/AX19 ensembles with the same seeds in both arms.
  - Pass if the room-averaged error with the hybrid is lower for at least one of EDT and C80, not higher for the other, and no room is worse by more than 1 jnd on either.
  - Report the per-room gain sorted by absorption contrast, largest single-face absorption share and broadband s, with no threshold (as D5).
- **If BRAS has too few uneven-α or low-s rooms:** no minimum count is imposed. (A) covers those conditions synthetically, and (B) is applied to whatever rooms Phase 05 has. The report and `bras_mapping.md` state "B11 not validated against measurement for uneven-α / low-s rooms" (F2).
- **If Phase 05 has no evaluable EDT/C80 pair:** promotion needs Maisara's explicit sign-off on (A) alone.
- **Also required:** rebuild time measured against AQ10 and recorded (not a promotion blocker, consistent with Phase 03).

**Confidence:** medium-low. The physics is corpus-backed; the BRAS room mix is unknown and the pass rule is a product choice.
**Reversal condition:** `bras_mapping.md` (Phase 05), which shows how many and which rooms; the Phase 05 paired errors; the (A) ray-tracer result in the promotion phase.

---

## Summary

| id | decision (exact value/wording) | confidence | PRD basis | corpus basis | reversal condition |
|---|---|---|---|---|---|
| D1 | Close "Expert may revise". Phase 05 runs the 3 handovers on the Phase 04 and reference-hybrid IRs, scored by the AQ9 error. A floor is adopted only if, on the hybrid IR, it moves EDT/C80 > 1 jnd in some pair, lowers the room-averaged EDT and C80 error, and makes no room worse by > 1 jnd. | medium | NFR-1, NFR-3, AQ10 | Vorländer §11.7; Eqs. 11.9/11.17; Table 6.1 | Phase 05 hybrid handover result; re-run in the B11 phase |
| D2 | Close it: no diffuseness threshold, since no code path or gate needs one. Per-axis shares and k_real also printed in the Phase 05 report. | high | NFR-8, NFR-1 | Kuttruff §8.5, Eqs. 5.1–5.2 | a later phase wanting a diffuseness branch (B12/B2) |
| D3 | Bound it: Phase 05 reports ΔL_b (AX16 vs hybrid matching level) on BRAS, the 6 test rooms and Table 5.2 layouts 2/4/5/6. ≤ 1 dB: accept and record in AX16. > 1 dB: the B11 phase switches matching to the hybrid's energy. | medium | NFR-1 | Kuttruff §5.2, §4.6, Table 5.2; Vorländer Table 6.1 | Phase 05 ΔL_b; §9.8 tracer check in the B11 phase |
| D4 | Promote B11 only if (A) the §9.8 tracer agrees within ±1 dB per 10 ms bin (bins with k ≥ 171; s = 0.1/0.25/0.4; uniform α and Table 5.2 layouts 4/5/6) and (B) the room-averaged AQ9 EDT/C80 error on seed-paired ensembles is lower for one metric, not higher for the other, and no room is worse by > 1 jnd. With too few uneven or low-s rooms: no minimum count, limitation stated. | medium-low | NFR-1, FR-SIM-6, AQ10 | Kuttruff §5.2, §9.8, Fig. 5.3; Vorländer §11.5, §11.6, Table 6.1 | `bras_mapping.md` and errors (Phase 05); (A) result (B11 phase) |

## Challenges to settled decisions

1. **B11's "only if it lowers the EDT/C80 errors against BRAS".** I kept this in D4 (B) because it was adopted with Maisara's approval. But with an unknown and possibly single-room BRAS set, the round robins show the absorption and scattering input data are decisive (Vorländer §11.5). A real model improvement can therefore fail to show as a lower error. Maisara has already decided that the early part should contain scattered energy, and the deficit is a non-physical step (AX21). So I would relax (B) to "not worse" (room-averaged error not higher, no room worse by more than 1 jnd), with (A) as the accuracy gate. This is her call.

## For Maisara

- **D1:** Stop waiting for an Expert on the mixing time. Phase 05 decides it by measuring whether a later handover gets closer to the real rooms. It is tested with early scattering added, otherwise the test measures the wrong thing.
- **D2:** Drop the "diffuseness threshold" question. Nothing in the plugin uses one, and the books don't give one.
- **D3:** Phase 05 measures how much the tail-level shortcut is off (in dB). Within 1 dB, we keep it. Above 1 dB, the scattering upgrade (B11) also fixes the tail level.
- **D4:** The scattering upgrade goes into the plugin only if it agrees with an independent ray-tracer check and doesn't make the real-room match worse (and improves it on EDT or C80). If BRAS lacks the right rooms, we don't wait for more rooms; we write down the limitation. See the challenge if you'd accept "not worse" instead of "better".

Files read: /home/user/makroof/docs/PRD.md, /home/user/makroof/docs/BUILD_PLAN.md, /home/user/makroof/docs/phases/phase-04.md, /home/user/makroof/docs/phases/phase-05.md, /home/user/makroof/docs/review/ledger.md, /home/user/makroof/docs/review/phase-04-consult/4-sme-rebuttal-c1b171f.md; corpus passages re-read: Vorländer §11.5–11.7 and Table 6.1, Kuttruff §5.2, §4.6, §8.5, §9.8 and Table 5.2.