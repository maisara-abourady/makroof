Corpus revision: c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

## PRD digest
- **For whom:** producers and DJs who don't need to understand spatial audio (PRD "Target users").
- **Outcome:** the user describes a space and hears the track as if it were played there. Accuracy is the quality gate: "measured match against real impulse responses + listening tests" (metrics table, NFR-1).
- **Priority order:** NFR-1 accuracy first. Then NFR-3 / FR-SIM-6: movement must render smoothly "despite heavy processing", and the PRD sends that tension to the Expert. Then NFR-2: heavy CPU and latency are fine when they buy accuracy, but the plugin "must stay usable in a DAW session". Then NFR-6 and NFR-8.
- **Hard constraints:**
  - NFR-8 / FR-SIM-2: `src/sim` stays generic.
  - AX5: determinism, and offline equals realtime for static scenes (Phase 10).
  - AQ4: effective update interval = max(20 ms, 30 ms, rebuild time).
  - AQ10: the 50 ms rebuild target. Phase 03 misses it, and misses are recorded, not optimised.
  - The Phase 10 cache, the contract rules, and the PRD out-of-scope list.
  - Settled by Maisara: D6–D8 (the switch rule, its bands, and an image-count cap "measured against AQ10"), the B11 rule, δ.
- **Verification culture:** every DSP behaviour has an automated check; independent references come first; goldens are never regenerated to pass; statistical gates are set at 3σ (AX11).
- **PRD silent on:** how quickly the sound must follow movement (responsiveness), as distinct from artifacts.

---

## 1. What the rebuild budget refers to (AQ10, phase-13, AX22 N_cap)

**Restatement.** AQ10 and phase-13 tie the 50 ms rebuild target to "order 30". Since AX20, order 30 no longer describes the work a rebuild does. This choice sets:
- the benchmark Phase 04 writes;
- how the AX22 cap N_cap is fixed;
- the update interval in AQ4 and the staleness gate in Phase 10;
- what Phase 13 optimises.

**What the work actually is.** The arithmetic below is my own, from the corpus equations.
- Integrating Kuttruff Eq. 4.6 gives N(t) = (4π/3)(ct)³/V images arriving by time t.
- The k_eff ≥ 19 rule ends the hybrid's image list at a roughly fixed expected count: about 53 for t_dir,e → 0 (phase-04 scope 2), and up to a few hundred for distant sources. So the ordinary (W1) rebuild is cheap in its image-source part, and its cost comes from IR assembly.
- The only large image workload is the AX22 fallback, which enumerates up to N_cap images per emitter.
- Phase 03 rendered 75 760 images in 344–525 ms, about 4.5–6.9 µs per image including fixed costs. At that rate, 50 ms buys roughly 3 600–5 500 images per emitter, which is ν_r(13) to ν_r(15) (Kuttruff Eq. 9.23).

**Validity screen.**
- *Budget set by N_cap* (pick N_cap for accuracy, e.g. ν_r(30) = 37 880, and accept whatever rebuild time follows). This runs against Maisara's D8, "measured against AQ10". It also has no corpus criterion for "enough" fallback.
  - The fields that fall back are exactly Kuttruff §4.2's flutter-echo rooms: "rigid end walls and absorbent ceiling, floor and side walls".
  - In those rooms, the part after the cap is wrong because an Eyring diffuse tail replaces the flutter. That error remains at any cap the budget can afford.
  - So a larger cap delays the error but does not remove it. Removing it is B12's job.
  - Not chosen.
- *N_cap set by the budget.* Valid, and consistent with D8. One condition: N_cap changes the output, so it must be a frozen constant. It is never derived from timing at run time, and it is the same offline and in realtime (AX5, Phase 10 equivalence).

**Scoring.**
- NFR-1: a budget-set cap can cut accuracy in fallback rooms. The size of that cut is unknown, so I add a sensitivity report that measures it rather than guessing.
- NFR-3 / FR-SIM-6:
  - A miss does not create clicks, because every update still crossfades (AQ4).
  - It lowers the update rate: the sound follows movement in steps of one rebuild time.
  - Vorländer Table 15.1 allows 700 ms for updating the specular part on moves > 0.25 m, and 3 s for the scattering part on moves > 1 m. A miss of a few hundred ms is therefore within the corpus's update proposal for steady moves. Jumps on the beat would lag, though.
  - Offline bounces are synchronous and stay exact, but take longer.
- NFR-2: during movement the builder thread is busy all the time whatever the rebuild time (it starts the next build immediately), so rebuild time costs responsiveness, not extra CPU.
- Testability: a timing benchmark is recorded, not gated; the output-affecting cap is a constant and is gated through goldens.

**DECISION.** Exact wording:

- **AQ10, rebuild clause:** *"IR rebuild ≤ 50 ms (target). It is measured as a position-only rebuild: the Phase 10 tail cache hits; Phases 04–09 time the build without generating the unit decay, as its proxy. Conditions: 2 emitters, 48 kHz, release build, median of 10 runs, on the CI runners (Linux from Phase 04; macOS arm64 and Windows x64 recorded in Phase 13); omni in Phase 04, and every output mode from Phase 08. It applies to two workloads in the 20×30×10 m room:*
  - ***W1:** the hybrid IR without the AX22 fallback.*
  - ***W2:** both emitters in the AX22 fallback at N_cap. This uses a generic flutter scene (hard x-walls, absorbent other faces, Kuttruff §4.2), and the benchmark asserts that the fallback triggered; if it did not, the scene is unsuitable.*

  *`maxReflectionOrder` does not set this workload (AX20). ν_r(30) = 37 880 images per emitter remains only as the Phase 03 `omni-early` benchmark. Full rebuilds (room or material changes) are recorded, not budgeted. A miss is recorded in §0 with the time and the effective update interval it implies (AQ4). It is not optimised before Phase 13, and it is never met by shortening the image list or N_cap: that changes the output, so it goes through AX20/AX22 and /fix-plan."*

- **AX22, "Cap value":** *"N_cap = ν_r(i₀) (Kuttruff Eq. 9.23) for the largest integer i₀ ≥ 10 at which W2 (AQ10) meets 50 ms in the Phase 04 benchmark on the Linux CI runner. If even i₀ = 10 misses, N_cap = ν_r(10) = 1 560 and the miss is recorded.*
  - *N_cap is a constant in `src/sim`, frozen once recorded here. It is the same offline and in realtime and in every output mode, and it changes only as an intended output change (this row, goldens via update_goldens.py, a §6 row).*
  - *For scale: Phase 03's rate suggests i₀ ≈ 13–15. In the 6 000 m³ room, t_cap ≈ 0.38 / 0.53 / 1.10 s at ν_r(10 / 14 / 30), against t_mix,e ≈ 0.12 s (Kuttruff Eq. 4.6, integrated).*
  - ***Sensitivity, reported only:** Phase 04 renders each of its fallback cases at N_cap and at ν_r(2i₀), with the same tailSeed, and reports the EDT, C80 and T30 differences at 500 Hz–2 kHz in jnd units (EDT 5 %, C80 1 dB, T at the working 5 %). If any difference exceeds 1 jnd, this row records 'cap limits accuracy'. Phase 13 then re-derives i₀ after optimisation. If the difference is still above 1 jnd after that, Maisara decides whether to spend rebuild time on it (NFR-2)."*
  - The floor i₀ ≥ 10 is a product choice. It keeps the fallback from being vacuous: about 3·t_mix,e in the AQ10 room.

- **AQ4:** replace "a rebuild takes up to 50 ms (AQ10)" with *"a rebuild targets ≤ 50 ms (AQ10; measured W1/W2 times in §0)"*.

- **phase-13, assumptions:** *"IR rebuild ≤ 50 ms for the AQ10 workloads W1 and W2 (position-only), in every output mode"*.

- **phase-13, acceptance:** *"…or the miss is quantified in the status notes, with the effective update interval max(30 ms, rebuild) and the worst staleness, together with a proposal that does not change the output beyond −100 dB. Raising N_cap with time freed by optimisation is an intended output change, proposed through /fix-plan."*

- **phase-10, staleness gate, new branch:** *"If the ≤ 100 ms staleness gate fails only because of a recorded AQ10 miss, this phase may apply the phase-13 scope 1 optimisations (output unchanged beyond −100 dB). If it still fails, the phase is `blocked (AQ10 miss)` and Maisara chooses between (a) a smaller N_cap (an output change; the AX22 sensitivity report shows the accuracy cost) and (b) for fallback scenes only, a staleness bound taken from Vorländer Table 15.1 (700 ms, translation > 0.25 m). The gate is not loosened otherwise."*
  - This branch is needed because otherwise 10 waits for 13's optimisation while 13 waits for 10 to be done.

**Confidence:** medium. Corpus: Kuttruff Eqs. 4.6 and 9.23, §4.2; Vorländer Table 15.1. PRD: NFR-1, NFR-2, NFR-3.

**Reversal condition:** the Phase 04 sensitivity report shows a difference above 1 jnd (Phase 04, re-checked in Phase 13), or the Phase 08/10 binaural W2 measurement misses badly.

---

## 2. The empirical items: is every outcome covered?

I checked each decision rule against its possible outcomes. Four branches leave a deficit the user could hear with no owner. I repair those; the others are already covered.

| Outcome | Current rule | Gap | Repair (exact wording / owner) |
|---|---|---|---|
| **Choosing BRAS rooms** | "reasonably reduced"; chosen in bras_mapping.md | The criterion is undefined, so rooms could be picked or dropped after seeing results (an NFR-1 risk) | phase-05 Data: *"The room selection and its reasons are committed to `bras_mapping.md` before any simulated-vs-measured number is computed; no room is dropped after results are seen."* Owner: Phase 05. |
| **Zero suitable BRAS rooms** | Phase 05 `blocked` | Blocks the parts of Phase 05 that don't need BRAS (a* test, ΔL_b, humidity) and, through "all previous", Phase 13, with no route forward | *"If no room qualifies, Phase 05 still completes every part that does not need BRAS (a* Table 5.2 test, ΔL_b on the test rooms, Table 5.2 and the s-cases, humidity bound). It is `done` with the note 'NFR-1 not validated against measurement'. The measured remainder becomes phase-05b, `blocked` until Maisara picks a measured data source (PRD Q9 asks which reference IRs). Meanwhile: B11 (B) uses the 'no evaluable pair' branch; the handover rule stands (D1); Eyring stays (B12). Phase 13 may start with 05b blocked only on Maisara's recorded decision."* Owner: Phase 05, then 05b and Maisara. |
| **Pilot R > ~2 000 per arm** | "δ goes back to Maisara" | Gives no default, so B11 and the handover stall indefinitely and the AX21 deficit (step up to 8.7 dB) stays with no phase | phase-05 Paired comparisons: *"If R > 2 000 per arm, run it outside CI when the projected time is ≤ 24 h on one CI-class machine. Validation compute is not user CPU, so this does not touch NFR-2. Beyond that, δ goes to Maisara, with the δ that 2 000 per arm would support, δ·√(R/2000), and the projected time. Until she decides, the comparison counts as 'no evaluable pair': B11 promotion needs her sign-off on (A) alone, and no handover floor is adopted."* Owner: Phase 05 / the B11 phase. |
| **ΔL_b > 1 dB while the hybrid fails (A)** | "switch tail matching … under the same validation" | If (A) fails, the switch cannot happen, and a tail-level error ≥ 1 dB jnd ships with no owner. Also uncovered: Phase 05 ΔL_b ≤ 1 dB but the hybrid itself is biased (D3's reversal, not written into the plan) | B11 (A), added: *"Also compare the matching level directly with the tracer, per case and per band 500 Hz–2 kHz: ΔL_b,tr = 10·log10(E_target(AX16)/E_target(tracer)), and the hybrid's E_target against the tracer's, within ±1 dB, in the same Hann window, with tracer k ≥ 684 over the window.*<br>*(i) If the hybrid's window level passes, tail-level matching switches to the hybrid whenever ΔL_b,tr > 1 dB anywhere, even if the per-bin render gate fails and early rendering is not promoted.*<br>*(ii) If it fails, nothing switches: AX16 records ΔL_b,tr per case as a known deficit, the phase is `blocked ((A) fails)` with the remainder split into its b-phase, and the diagnosis goes to Maisara.*<br>*(iii) If Phase 05 accepted X-b (≤ 1 dB) but ΔL_b,tr > 1 dB anywhere, the acceptance is reversed and (i)/(ii) apply."* Owner: the B11 phase. |
| **Converged tracer bias > 0.3 dB** | "find the systematic source before touching the budget" | No end state if the source is not found, and nothing says whether the tracer or the hybrid is wrong | *"Diagnose with two tracer self-checks against independent anchors: s = 0 against the ISM image energies in 10 ms bins (the lattice is exact, Kuttruff §4.1), and s = 1 against the Table 5.2 iteration T. Fix whichever side fails. Then halve the hybrid's time step and patches until the change is < 1 % (as in D2). If the remaining bias is ≤ 0.5 dB, it is within the stated systematic budget: the gate is unchanged and the bias is recorded. If it is > 0.5 dB in any gated bin, (A) fails and the branch above applies. N (beyond the pre-stated doubling rule), seeds and bins are never changed after results are seen."* Owner: the B11 phase. |
| σ₁,Δ normal, rooms few or uneven | covered (no minimum count; limitation stated, F2) | none | none |

**Confidence:** medium. Corpus: Kuttruff §4.1, §9.8, Table 5.2; Vorländer Table 6.1, §11.2.5. PRD: NFR-1, F2.

**Reversal condition:** `bras_mapping.md` and the pilot values (Phase 05); the (A) result (B11 phase).

---

## 3. Other open items

**3a. B11 is "may be scheduled inside v1".**
- The plan and the PRD diverge here, and I side with the PRD.
- The deficit is a step of up to 8.7 dB (upper estimate) in every room with s > 0. Vorländer §11.6 says scattered energy dominates "after a few reflections (order 3 or 4)", and §11.5 says a scattering model is essential.
- Maisara has already decided the early part should contain scattered energy.
- **DECISION:** B11 becomes a v1 phase, placed after 05 and before 08, so that Phase 08's binaural accumulation is built once.
  - Phase 08 depends on it being `done` or closed as "not promoted"; in the second case Phase 08 builds on the specular-only early part.
- Confidence: medium. Reversal: (A)/(B) fail → not promoted, and 08 proceeds on the specular-only early part.

**3b. B12 has no decision rule.**
- **DECISION:** *"Phase 05 compares predicted T₆₀ (deterministic, so no seed noise) with measured T30 at 500 Hz–2 kHz, room-averaged. A predictor replaces Eyring for all scenes (NFR-8: one predictor, no per-room choice) only if it lowers the mean |error| by ≥ 0.25 working jnd (1.25 % points) and makes no room worse by > 1 jnd (5 %). Otherwise Eyring stays. Shown separately for uniform and uneven α."*
- Same δ convention as FE-01. Kuttruff §5.7 and §9.4 warn against defaulting to a*.
- Owner: Phase 05 provides the evidence; a new phase implements it.
- Confidence: medium.

**3c. B10 (per-band s) is only "after 12".**
- **DECISION:** Phase 05's Python reference hybrid also runs with BRAS per-band s (tools only, no contract change).
  - If that changes the room-averaged AQ9 EDT or C80 error by ≥ δ, or any room's by > 1 jnd, B10 moves ahead of the B11 phase, so B11 is validated only once.
  - Otherwise it stays after 12.
- Confidence: medium-low (it depends on the s data in BRAS).

**3d. AQ9 failure "escalates to the Expert".**
- There is no active Expert, so this has no owner in practice.
- **DECISION:** *"Maisara decides at the Phase 05 review (via /fix-plan) whether to schedule B10/B11/B12/B2 inside v1. Phase 13's beta decision lists 'AQ9 met in x/y' and every recorded known deficit (AX16, AX21, AX22, AQ10 misses)."*
- Confidence: high (PRD NFR-1).

**3e. "To verify" in phase-05** (the T30 ±10 % basis, the ISO 3382-2 scatter constants, the 10 % curvature threshold).
- None of these blocks anything.
- **DECISION:** reword to *"outside the corpus, not verified; product choice, stands (AQ9)"*. The curvature value is reported only.

**3f. AX19, if the measured σ₁ makes R impractical in CI** (e.g. EDT at 63 Hz).
- **DECISION:** the gate moves to the nightly job with the same R; the tolerance is unchanged.

**3g. Outside the listed scope.** AX14's "Pending Expert" does not block Phase 05: ISO 3382 metrics are not per-band levels of sparse responses.

---

## Summary

| id | decision | confidence | PRD basis | corpus basis | reversal condition |
|---|---|---|---|---|---|
| 1 | AQ10 = position-only rebuild ≤ 50 ms for W1 (no fallback) and W2 (fallback at N_cap), 2 emitters, 48 kHz, every mode; order 30 only for omni-early. N_cap = ν_r(i₀), largest i₀ ≥ 10 meeting W2, frozen; sensitivity at ν_r(2i₀); misses recorded, never met by cutting the list; Phase 10 blocked-branch | medium | NFR-1, -2, -3 | Kuttruff Eqs. 4.6, 9.23, §4.2; Vorländer Table 15.1 | sensitivity > 1 jnd (04/13); binaural W2 (08/10) |
| 2a | room selection committed before results | high | NFR-1 | Vorländer §11.5 | none |
| 2b | zero rooms → 05 done without BRAS + 05b blocked on data source | medium | NFR-1, Q9 | none | data source found |
| 2c | R > 2 000: run if ≤ 24 h, else δ to Maisara; meanwhile "no evaluable pair" | medium | NFR-1 | Vorländer §11.2.5 | pilot values |
| 2d | windowed tracer level check; switch / known-deficit / reversal branches | medium | NFR-1 | Kuttruff §9.8, §5.2 | (A) result |
| 2e | tracer self-checks (s = 0, s = 1); ≤ 0.5 dB record, > 0.5 dB fail | medium | NFR-1 | Kuttruff §4.1, §9.8, Table 5.2 | diagnosis |
| 3a | B11 inside v1, after 05, before 08 | medium | NFR-1 | Vorländer §11.5, §11.6 | (A)/(B) fail |
| 3b | B12 rule: deterministic T vs T30, ≥ 1.25 % points better, no room > 5 % worse, one predictor | medium | NFR-1, NFR-8 | Kuttruff §5.7, §9.4 | Phase 05 numbers |
| 3c | B10 ahead of B11 if per-band s moves the error ≥ δ | medium-low | NFR-1, FR-3D-4 | Vorländer Eq. 3.23 | Phase 05 numbers |
| 3d | AQ9 failures go to Maisara; Phase 13 lists known deficits | high | NFR-1 | none | none |
| 3e/3f | reword "to verify"; heavy gates go to nightly | high | none | none | none |

## Challenges to settled decisions

1. **AX22 switch-point dip: "reported, not gated" (D6).** FR-SIM-6 asks for no audible artifacts, and CLAUDE.md asks for an automated check of every DSP behaviour. The 3 dB is the dip in one segment, not in the whole output: total dip = 10·log10(1 − 0.5·f), where f is that segment's share of the output energy (my arithmetic from Vorländer Eq. 4.14).
   - Proposal: gate the total output band-energy dip in Phase 10 at ≤ 1 dB against the power-linear interpolation, 500 Hz–2 kHz. That holds whenever f ≤ 0.41. The 1 dB is G's jnd from Table 6.1, stated for 500–1000 Hz, and its use for a 30 ms dip is my extension.
   - If the gate fails, Phase 10 proposes a crossfade split by time segment as a new AX.
   - This is Maisara's call. Confidence: low-medium.

## For Maisara
- **1:** The 50 ms rebuild goal now refers to the plugin's actual work: a normal move, plus the worst case where the room is too "sparse" for a reverb tail. The cap on how far the exact echoes run in that worst case is set so it fits 50 ms, then frozen. A report tells you whether a bigger cap would sound different. A miss means the sound follows movement in coarser steps; it never clicks.
- **2a:** We choose the test rooms before looking at results, so nobody can pick the rooms that flatter us.
- **2b:** If no measured room fits a box, Phase 05 still does everything that doesn't need real rooms. The real-room check waits for you to pick another data source, and the beta needs your explicit OK without it.
- **2c:** If the statistics need many renders, we run them (up to a day of compute) before asking you to accept a looser margin.
- **2d/2e:** If the scattering upgrade fails the independent ray-tracer check, we still fix the reverb level if that part checks out. Otherwise the error is written down with its size, and you decide.
- **3a:** Build the early-scattering upgrade inside v1, before headphone mode.
- **3b/3c:** Clear rules for when to replace the reverb-time formula and when to add per-band scattering, both decided on Phase 05 numbers.
- **3d:** When rooms miss the accuracy targets, you decide what to fix; the beta decision lists every known shortfall.
- **Challenge:** consider gating the small level dip when a moving source crosses the "sparse room" switch point.

Files read: /home/user/makroof/docs/PRD.md, /home/user/makroof/docs/BUILD_PLAN.md, /home/user/makroof/docs/phases/phase-04.md, /home/user/makroof/docs/phases/phase-05.md, /home/user/makroof/docs/phases/phase-10.md, /home/user/makroof/docs/phases/phase-13.md, /home/user/makroof/docs/review/ledger.md (last sections), /home/user/makroof/docs/review/phase-04-consult/5-decider-expert-questions-c1b171f.md, /home/user/makroof/docs/review/phase-04-consult/7-decider-gates-c1b171f.md, /home/user/makroof/tests/unit/test_engine.cpp (benchmark, from the code). Corpus re-read: Vorländer Table 6.1, Table 15.1, §11.5–11.6; Kuttruff §4.2 (Eq. 4.6, flutter echo), §9.8 (Eqs. 9.23–9.24).