# Seat 9 — D-H1 and D-H2 (phase 05h session 2)

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

SEAT 9 POSITION — D-H1

**1. Reading.** Pin the gated closed 100 m cube (α, s), the "further rise", the ratio, W_max/n\*_max, and how a gate that already fails on the non-diffuse build is treated. Cues: coefficient provenance (§4), surface roughness relative to wavelength, late change after commitment. Corpus present (c1b171f). Q-a…Q-d are Seat 5's; I do not rate them.

**2–4. Ranking, tension now / later.**

| sub-choice | option | label | now | later | reason |
|---|---|---|---|---|---|
| P | **P-a** s = 0.3 | prefer | 0 | 0 | The realistic cost-worst closed room. Cost is the same as s = 1 (restore 2.063 vs 2.075 s Linux; W_pilot 1.70 vs 1.67 M; file 1 §1, §4): s does not change the hit count, the window does. Floor met via (d), pending O18. The s = 1 cube stays reported. |
| P | P-b s = 1 | can live with | 1 | 1 | A bound, not a room: full Lambert reflection is "often assumed but hardly ever real" (Kuttruff §5, L2504); no fixture has s > 0.7 (`large_hall` floor 0.7, `concert_hall_box` 0.6; from the code). Gating it escalates a synthetic bound to Maisara (Raise item 1) as if a preset approached it. |
| R | **R-c** fixed ≥ 0.05 dB | prefer | 0 | 0 | 1/20 of G's jnd (Vorländer Table 6.1); deterministic per OS (AX40, D7), so it never fires on noise. |
| R | R-d line crossing only | can live with | 0 | 1 | Matches my criterion 1, but degenerates under P-b (SE already above 0.33 dB: no crossing can happen again). |
| R | R-b > 2 SD | can live with | 0 | 1 | A p95 from 30 replicates is itself noisy [Hyp]; 2 SD limits false escalations. |
| R | R-a > 1 SD | can live with | 1 | 1 | Fires on replicate noise about 1 time in 6 [Hyp]; board rounds for nothing audible. |
| W | **W-a** keep 3.05 M, gate as written, defect recorded, (C) next | prefer | 0 | 1 | For validation nothing changes: BRAS rooms are far from the cap (W1-size rooms realise 0.12 W_scene; file 1 §2), so the report's SE beside the ensemble spread (AX40) is ≈ 0.02–0.08 dB under every W option. One golden round when (C) raises W_max. Phase 12's preset check runs at the final W_max (decider 51 §4 item 7), which W-a reaches soonest. |
| W | W-e (Linux-enforced; recorded elsewhere) at 3.05 M | can live with | 0 | 1 | Same as W-a for my seat; the OS scope is Seat 5's. At W-b's value: 1/2 as W-b. I would accept it if the FOR MAISARA reading survives. |
| W | W-c (C) first, 05h blocked/split | can live with | 1 | 1 | Best final precision (54–68 M ≈ 18–22× → SE ÷ 4.2–4.7: s = 1 cube ≈ 0.08 dB, layout 4 ≈ 0.3 dB [Inf, 1/√W]). But the switch, which corrects +3.87 dB in the audience-floor class (layout 4, Kuttruff §5.7 "crude model of most auditoria") and +2.4 dB in the absorbing-floor cube, waits one phase; the Phase 04 goldens and the BRAS nightly stay on AX16 meanwhile. A 0.4 dB random error in a synthetic cube is worth less to me than a 3.9 dB systematic one in the auditorium class. |
| W | W-b cut to ≈ 2.0–2.4 M | can live with | 1 | 2 | Buys nothing on macOS; raises the capped-class SE ×1.21 (layout 4 ≈ 1.6 dB > 1 jnd) for Phase 08's goldens; two golden rounds instead of one. |
| N | **N-a** 1 024 | prefer | 0 | 0 | Uncapped rooms (BRAS, Phase 04 defaults, C18 halls) already reach the 0.083 dB target through N_need; a larger pilot gains them nothing I measure and raises SE at the gated cubes. |
| N | N-b raise now | can live with | 1 | 1 | A second parameter change if (C) re-derives it. |

**Facts behind P (my brief's three questions).**
- *Worst realistic closed room for diffuse cost:* the lowest-α hard shell the library allows, any s. Hard surfaces are α 0.02–0.05 (Kuttruff Table 9.2); the fixtures go to 0.01 at 125 Hz. But the estimator's path length is bounded by the window (c·t_mix + |dims|), not by annihilation, and t_mix,e at 100 m is the same at α 0.05 and 0.10–0.22 (C14), so cost barely moves with α or s below the fallback. The restore overrun is the ISM build (2.0–2.6 s), not the solve (0.06–0.16 s).
- *Does α 0.05 / s = 1 at 100 m correspond to anything a preset approaches?* No. Flat stone or concrete has s < 0.05 below a/λ = 0.125 and 0.1–0.5 at mid frequencies for articulated surfaces; 0.7–0.9 only for deep random relief at a/λ ≥ 2 (Vorländer, scattering tables, Appendix). Where s could reach 0.9 (4–8 kHz), air dominates a 100 m tail: m = 6.84·10⁻³ m⁻¹ at 4 kHz, 50 % RH (Kuttruff Table 6.1), 343 m of path → −10 dB; at 1 kHz −1.6 dB. So a cathedral-class preset (stone, α 0.05–0.10, s 0.3–0.5, elongated) sits near the s = 0.3 cube, never near s = 1 [Inf]. Such a preset at 100 m will be capped with U silent (C16 (f): "reported only" under Trigger 2).
- *SE against α provenance:* tail energy ∝ 1/A (Vorländer Eq. 11.19). α 0.05 ± 0.02 on 6·10⁴ m² gives A 1 800–4 200 m², a level band of −1.5 / +2.2 dB [Inf, arithmetic mine]. The s = 0.3 cube's SE 0.09–0.11 dB is 1/15 of that; the s = 1 cube's 0.36–0.44 dB is 1/4. Both are inside the input uncertainty; only s = 1 approaches the 1 dB jnd at p95 (≤ 0.89 dB).
- *Corpus vs data:* Eq. (11.21) gives σ_L ∝ √(A/N) for a detector-sphere tracer, so the low-α cube would be the precision-*best*. Our estimator's variance comes from branching on s(1−α) over lattice images (AX39), not from Poisson hits; the condition differs, so the replicates stand, as the packet says.

**5. Evidence.** Kuttruff Table 9.2, §5.7 and Table 5.2 (case 4), Table 6.1 (m), L2504 (Lambert "hardly ever real"); Vorländer Table 6.1, Eqs. (11.19), (11.21), (11.30), scattering tables (Appendix, "below a/λ = 0.125, s … smaller than 0.05"); file 1 §1–§4 [Obs, from the code/CI]; C14, C16 (f), C18 (decider 47 L5); fixtures in `tests/scenes/valid/` [from the code]. [Hyp]: the noise of a 30-replicate p95; my ℓ/d normalisation (D-H2). Researcher: none needed from my seat.

**6. Conditions.** W-b later 2 → 1: (C) stays the next phase regardless of the Linux/Windows pass, and Phase 08's capped-room goldens carry the SE tolerance (phase-07c condition 8). W-c now 1 → 0: the M-2 tracer runs and the AX16-vs-switched listening pack ship in 05h anyway, so the audience-floor evidence is not delayed. P-b now 1 → 0: the finding states it is a bound no preset approaches.

**7. Hand-offs.** Seat 5: Q-a…Q-d; the OS scope of W-e; the ISM build overrun. Seat 1: R's audibility reading. Seat 2: the ISM build at 100 m / 96 kHz (Phase 07 finding). Phase 12 / Seat 8: the preset check at the final W_max must include an elongated stone cathedral (≈ 100×35×30 m, α 0.05–0.1, s 0.3), not only audience-floor halls (C18 covers four rooms).

**8. Premortem.** If P-b wins and W_max is cut, the s = 1 bound raises U at a scene nobody builds, Maisara is asked to rule on a non-room, and the real cathedral-class preset at s = 0.3, which nobody computed, is the one that surprises Phase 12.

---

SEAT 9 POSITION — D-H2

**1. Reading.** Which case-bands have a certified reference now, what the single-rung values may be used for, how the rest are produced. Cues: coefficient/reference provenance; bass strength at 125–250 Hz.

**Correction to the packet.** The Phase 04 rooms are not all at 2.25 m. `tools/validation/scope6.py` uses min(dims)/2 per room (L162): `dead_booth` 1.0, `living_room` 1.3, `classroom` 1.6, `club` 2.25, `concert_hall_box` 8.0, `stone_box` 5.0 m; BRAS CR2 1.45, CR3 2.20, CR4 2.47 m (`tools/validation/data/phase05_scope6.json`; `docs/validation/report-phase05.md` L453). CR2's halving at the initial α changed ΔL_b ≤ 0.006 dB, but at 500 Hz–2 kHz only (L454).

**Seat 2's rung question.** Relative to the room, min/2 is the coarsest rung of the (A) ladder (5 m in a 10 m dimension), not the certified 2.5 m = min/4. The normalisation that matters is ℓ against the ends' clearance d to the nearest face: AX36 (c) certified 2.5 m at reference positions (d ≈ 1.7–2 m, ℓ/d ≈ 1.3–1.5) and failed it near walls (4.75–8.7 %) at the same ℓ [Inf]. On that scale `club` (2.25 m, d 1.7–2.0 m, ℓ/d ≈ 1.3) is comparable to a certified (A) rung; `stone_box` (ℓ/d 2.9) and `concert_hall_box` (8 m, emitters at z 1.5 m, ℓ/d 5.3) are coarser than anything certified. So the Phase 04 single-rung values are not a rung of the ladder; they are a* start sizes.

**2–4. Ranking.**

| option | label | now | later | reason |
|---|---|---|---|---|
| G-a (forced) | — | 1 | 1 | Honest by construction (criterion 4). Cost: my preset references (the six Phase 04 rooms) and the bass bands (63–250 Hz, my warmth cue) are reported, not gated. Tolerable now because the independent tracer M-2 runs cover the five mixed-α rooms and the BRAS nightly compares to measurement regardless of D-H2. |
| **U-a** reported, labelled | prefer | 0 | 0 | Yes, print it. The C++ estimator is the ℓ → 0 form (AX39); \|C++ − ref\| at one rung estimates ℓ_ref's effect plus SE. It is the cheapest ranking of which second rungs are urgent. Label: "one rung, ℓ_ref unknown; a disagreement is attributed to the rung, never gated". At 63–125 Hz in CR2/CR3 it is a model-vs-model check only: the room is near its Schroeder frequency [Hyp, dims not read]. |
| U-c not used | can live with | 1 | 1 | Throws away the only model-agreement number the Phase 04 rooms get this phase. |
| **M-e** M-a now + priority order + 05i gates what is certified | prefer | 0 | 1 | My order: (1) `concert_hall_box` and `club`, both emitters (audience-floor and mixed-α classes, largest ΔL_b 0.18–0.30 dB); (2) W1 e1 and the 0.3 m wall case; (3) the small room and `stone_box` (cheap: ≤ 720 patches at 1.25 m); (4) BRAS 250 Hz and 4 kHz (bracket the certified bands); (5) BRAS 63/125 Hz and 8 kHz last. `concert_hall_box` needs 2.5 → 1.25 m (≈ 650 → 2 600 patches, 162 bins; ≈ 4.4 GB per band column at 1.25 m [Inf, arithmetic for K23]), not 4 → 2 m. |
| M-a alone | can live with | 1 | 1 | Leaves the order to the implementer. |
| M-d larger machine | can live with | 1 | 0 | The only route to the BRAS 1.25 m outer-band rungs (15 GB) in days; cost is Seat 7's. Compose with M-e. |
| M-c nightly | can live with | 1 | 1 | Pending RQ-H2-1; Seat 5's. |
| M-b all to 05i | can live with | 1 | 1 | Wastes this session's cores. |
| **B-a** bias now on certified classes | prefer | 0 | 1 | The absorbing-face class is my audience-floor class; a bias there is the systematic error AX16 had. No pooled claim across classes; "not evaluated (reference pending)" per missing class. 100 m: name the tracer only if its own SE ≪ 0.043 dB (Seat 2), else "not evaluated". |
| B-b defer | can live with | 1 | 1 | The switch lands with no bias check on the class it was built for. |

**5. Evidence.** AX36, AX39, AX43, AX45, AX46 (plan ids); `scope6.py` L56, L162, `phase05_scope6.json` (from the code); report-phase05 L453–454; Kuttruff Table 5.2 case 4; Vorländer Table 6.1. [Inf]: ℓ/d normalisation; patch and memory arithmetic. [Hyp]: CR2/CR3 Schroeder frequencies.

**6. Conditions.** G-a now 1 → 0: the per-case-band listing names each ungated Phase 04 room and BRAS band, and the M-2 tracer comparison is printed per band for the five mixed-α rooms in this phase's report. M-a → M-e: the order above adopted, Seats 1 and 8 merging theirs.

**7. Hand-offs.** Seat 2: the ℓ/d criterion; the 100 m class reference. Seat 7: M-d's machine. Seat 5: M-c and CI time. Seat 1: audibility of the ungated outer bands.

**8. Premortem.** If U-c wins and M-b defers everything, the switch ships through the Phase 04 rooms with no model-agreement number, and the first sign of an ℓ or code error in `concert_hall_box` is a producer hearing a hall preset's tail 0.3 dB off against the AX16 level nobody can explain.

Files read: /home/user/makroof/docs/review/phase-05h/4-decider-convene-D-H1-D-H2.md, /home/user/makroof/docs/review/phase-05h/3-orchestrator-D-H1-D-H2-question.md, /home/user/makroof/docs/review/phase-05h/1-orchestrator-cpp-costs.md, /home/user/makroof/docs/phases/phase-05h.md, /home/user/makroof/docs/phases/phase-07c.md, /home/user/makroof/docs/BUILD_PLAN.md (AQ10, AX36–AX46), /home/user/makroof/docs/review/phase-05b2/45-seat9-R1-R3.md, 47-decider-board-answers-C1-Q2a-final.md §4, 51-decider-addendum-J1.md §3–§4, 53-decider-J1-trigger-definitions.md, 54-interrogator-J1-triggers-round2.md, 55-seat1-confirm-clause-d.md, 18-seat9-T1-T2-T6.md, 3-seat9-T5-T4.md, /home/user/makroof/docs/sessions/2026-11-10-phase-05h.md (Session 2), /home/user/makroof/docs/corpus/vorlaender-auralization.md (Table 6.1, §11.2.5, Table 15.1, scattering tables), /home/user/makroof/docs/corpus/kuttruff-room-acoustics.md (Table 5.2, §5.7, Table 6.1, Table 9.2, §4.5), /home/user/makroof/tools/validation/scope6.py, /home/user/makroof/tools/validation/data/phase05_scope6.json, /home/user/makroof/tools/validation/data/phase05b.json (ell), /home/user/makroof/docs/validation/report-phase05.md, /home/user/makroof/tests/scenes/valid/*.json.
