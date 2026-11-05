## Decider report 15: the second measured dataset (BUILD_PLAN §3 F2, PRD Q9)

Corpus revision: `c1b171fe649f07cbeb952ef1f75d89bfaa414d0d`. I read the PRD, CLAUDE.md, BUILD_PLAN (§0–§6), phase-05, phase-13, decider report 11 (F2 lines) and researcher reports 13 and 14. All dataset facts below come from those two reports (external sources, cited there by DOI). They are not corpus evidence. Code fact: `src/sim/ism/ImageSources.h:19` fixes c = 343 m/s.

### PRD digest
- **For whom:** producers and DJs who should not need to understand spatial audio (PRD "Target users").
- **Outcome:** the user hears the space they described. Accuracy is a quality gate, "measured match against real impulse responses + listening tests" (metrics table; NFR-1).
- **Priority:** NFR-1 accuracy first ("Accuracy is the top priority"), then NFR-3/FR-SIM-6, NFR-2, NFR-8. FR-3D-3 sets the preset categories that the evidence should cover: clubs & warehouses; halls, chapels & churches; outdoor; domestic (living rooms, cars, small rooms).
- **Hard constraints:**
  - NFR-8 / FR-SIM-2: no scene-specific logic.
  - The PRD scopes out audiences and crowds: spaces are always empty.
  - AQ1: the v1 contract is a shoebox with 6 faces, per-band α and broadband s, no objects.
  - AQ8: omni emitters only.
  - AX4: fixed atmosphere, with a validation-only override.
  - CLAUDE.md: datasets are fetched by checksum and never committed; attribution goes in THIRD_PARTY.md.
  - Phase 05 conventions: the sample selection is committed before any results, sim–meas errors are reported and not gated, and a nightly regression baseline guards the simulation.
- **Verification culture:** every DSP behaviour has an automated check; independent references are preferred; goldens are never regenerated to pass; statistical gates are set at 3σ (AX11).
- **PRD is silent on** which reference IRs to use (Q9 is open) and on whether input data must be measured.

---

### SD-1: Which dataset(s) to adopt
**Restatement.** Which measured set(s) a new validation phase fetches, maps to contract scenes and reports, beside BRAS.

**Validity screen.**
- **SoundCam: out.** People are in the room. The PRD says spaces are always empty and the contract cannot model people.
- **ACE: out.** It is mostly occupied, and its licence is in conflict (C3).
- **C4DM: out.** Its licence is non-commercial.
- **MIT Survey and GTU: out.** No geometry, and the licences are unconfirmed.
- **Bologna: out.** It is a tiered hall of about 900 m³, not a shoebox, and its α were calibrated (V9).
- **RR-III: out.** It offers no IRs (D9).
- **SRIRACHA: out for now.** Its licence is in conflict (C2) and its α are unknown.
- **BUT ReverbDB, MeshRIR: out.** No material data, so there is nothing to put in a scene except invented α.
- **Survivors:** Arni, dEchorate, Motus, May et al.

**Scoring.**
- **Contract fit (AQ1).**
  - dEchorate is an exact cuboid whose faces switch as whole faces. That is exactly what the contract can express.
  - Arni's variable panels are wall- and ceiling-mounted, so they map to per-face α through Phase 05's absorption-area rule.
  - **Motus's variable is furniture inside the room.** v1 cannot represent objects, so Motus would mainly test our shoebox reduction, which phase-05 Risks already says the corpus does not quantify.
  - May et al. is a single near-uniform hard room (454 m³) recorded with a TetraMic. It adds little beyond BRAS 145 m³ and Arni 202 m³.
- **What BRAS cannot give: a test with the input bias held fixed (NFR-1).**
  - Eyring depends on α only through ᾱ = ΣSᵢαᵢ/S (Vorländer Eq. 4.30, 4.32).
  - Derivation: take two configurations with the same area of each material. A common error εᵢ in a material's α gives the same estimated ᾱ in both, so it cancels exactly from the Eyring ΔT. For models that respond to where the absorption sits (ISM early part, a*, ray tracing), it cancels to first order only.
  - The real measured ΔT between such configurations is a pure distribution effect. Kuttruff Table 5.2 cases 3 and 4 have equal A (Sabine 1.61 s for both) but iteration T of 1.52 s and 1.21 s, about 20 %. Eyring gives 1.38 s for both.
  - **The claim holds only with a condition.** Kuttruff §8.7 Eq. 8.56 gives α_eff = βL′ + α_∞, with β "may reach 0.2 m or more". A cluster of open panels has fewer free edges than the same panels spread out, so placement alone changes the effective α.
  - So pairs must match the number of open panels **and** the total shared-edge length between open panels. For whole-face switching (dEchorate) the problem does not arise: covering an entire wall removes free edges (Kuttruff §8.7).
  - The slope across different numbers of open panels (dT/dn) is **not** input-independent, because the error in α_open − α_closed enters it linearly.
- **Small rooms (FR-3D-3 domestic).**
  - dEchorate (86.4 m³) is the only survivor under 100 m³ that the contract can represent.
  - Vorländer §11.5 limits geometrical acoustics to large rooms, and Round-robin III's smaller room showed modal effects. So small-room evidence is exactly what is missing.
- **Low-frequency limits.** Schroeder frequency, Kuttruff Eq. 3.44 (2000√(T/V)), with Vorländer Eq. 4.13 (1200√(T/V)) in brackets:
  - dEchorate, T 0.14–0.73 s: 80–184 Hz (48–110 Hz).
  - Arni, T 0.30–1.28 s at 500 Hz: 77–159 Hz (46–96 Hz). The researcher reports about 200 Hz at low absorption (V4).
  - The AQ9 bands (500 Hz–2 kHz) lie above both estimates in both rooms. Bands from 63 to 250 Hz fall under phase-05's Schroeder rule (read as method-validity evidence). dEchorate below about 300 Hz is "not evaluable" because of loudspeaker roll-off (D3), never a pass.
- **Cost and reversibility.** Adopting two sets adds one phase. Motus and May stay as reserves at no cost.

**DECISION.** Adopt **Arni** and **dEchorate** together.
- **Arni:** Zenodo 10.5281/zenodo.6985104 (the omni LS01 campaign with the per-IR `combinations_setup.csv`). This is the primary second source.
- **dEchorate:** Zenodo 10.5281/zenodo.6576203 v2.0, using **only the sources documented as omnidirectional** (AQ8).
- **Not adopted:**
  - Motus: reserve, revisited with B2/B8 (objects).
  - May et al.: reserve.
  - SRIRACHA: lead, pending its licence.

**Confidence:** medium. The corpus supports the reasoning; the dataset facts are external and only "read on record pages".

**Reversal:** the 05d session finds that Arni's file layout makes even a subset impractical, or that dEchorate's 11 configurations contain no omni source. In that case Motus moves up as the under-100 m³ source, labelled "reduction-limited".

### SD-2: What each dataset can and cannot validate
**Restatement.** These labels go into the 05d report and the beta decision.

| Question | Arni | dEchorate |
|---|---|---|
| Absolute T30/EDT/C80 vs AQ9 | **Evidence, not validation.** Panel α come from one unretrievable "exploratory" report; walls and floor use textbook α (V1–V3). Vorländer §11.5: the operator's absorption choice has "crucial influence". | **Evidence, not validation.** No α at all, so α come from a published table chosen by a rule committed before results. |
| Effect of absorption distribution with the input bias held fixed (T30, EDT, C80) | **Yes**, on matched pairs: same receiver, same number of open panels, equal open–open shared-edge length. Position effects cancel too (EDT "varies considerably within a hall", Kuttruff §8). | **Yes, if** two configurations have equal absorbing area on different faces (e.g. two 6 × 2.4 m walls). The 05d session checks this. |
| Early reflection **timing** per wall | Not useful (protruding panels). | Sanity check only. The authors refined positions against echo times (0.4 cm), so agreement is nearly circular, and Phase 03 already gates timing analytically. Compare arrival times scaled by c_meas/c_sim = 346.98/343 (1.16 %, ≈ 16 samples at 48 kHz over 10 m), analysis-side, no code change. |
| Early reflection **level** per wall (reflective vs absorbing state) | No. | Reported. It depends on the table α, and random-incidence α can misstate a specific-angle reflection by up to 2 dB (Vorländer §11.1.2). |
| Small room under 100 m³ | No (201.9 m³, V5). | Yes, at 500 Hz–4 kHz only. |
| Below about 250 Hz | Transition zone, evidence on method validity only. | Not evaluable. |
| B12 (decay predictor) | The matched-pair spread directly measures what Eyring cannot see. Reported as "input-matched", not counted in B12 rule (iv). | Same. |
| Atmosphere | Documented, 19–20 °C, RH 28–50 % (V4). Use the AX4 override. | 24 °C, 80 % RH. Use the AX4 override. |

**DECISION.** Use the labels above verbatim. The only claim stronger than "evidence" is the **input-matched distribution test**, stated as: "method evidence with the input bias cancelled to first order; not an NFR-1 validation".

**Confidence:** medium. **Reversal:** obtaining the DELTA report does not change these labels, because walls and floor stay textbook values.

### SD-3: How it enters the plan
**Restatement.** Phase placement, gates, reporting, licence and fetching.

**DECISION.**
- **New phase `phase-05d` "Second measured dataset (Arni, dEchorate)", size M.**
  - Depends on 05. It is run after 05 and before 05b, but 05b does **not** depend on it. If 05d is blocked on data access, 05b proceeds.
  - Phase 13 depends on 05d being `done` or `blocked (reason)`.
  - The name 05c stays reserved for Phase 05's zero-rooms branch.
- **Scope:**
  - `tools/validation/fetch_arni.py` and `fetch_dechorate.py`, with SHA-256 manifests cross-checked against Zenodo's md5, caching under `~/.cache/makroof/<set>`. Partial download if the archive layout allows it; the layout is checked first and recorded.
  - Mapping files `docs/validation/{arni,dechorate}_mapping.md`. Before any sim–meas number is computed, they commit: the α source rule, the configuration subset (a seeded stratified sample over n = 0…55), and the matched-pair list derived from the CSV and the panel drawing.
  - Phase 05's generic reduction rules, metric conditions and report generator, unchanged.
- **Gated (CI):**
  - The checksum check plus a tampered-file test.
  - The report reproduces exactly.
  - The nightly baseline includes the 05d scenes (the same ±2 % T30/EDT and ±0.2 dB C80 change limits).
  - A matched-pair selector unit test: every selected pair gives an Eyring ΔT of exactly 0 and equal shared-edge length, and a deliberately unmatched pair is rejected. This is the negative control, so the test is not vacuous.
- **Reported, not gated:**
  - AQ9 per configuration and per room, by α set.
  - The matched-pair differential d = ΔT_sim − ΔT_meas (and the same for EDT and C80): mean, SE and K.
  - Per-face reflection level changes.
  - Coverage by FR-3D-3 category.
- **Statistics (AX11 convention):**
  - The simulated side is seed-paired, as in phase-05 "Paired comparisons".
  - On the measured side, take a pilot of ≥ 51 disjoint pairs, measure σ_d, then use K ≥ 9·(σ_d/1 jnd)² disjoint pairs, so that SE ≤ 1/3 jnd. The two-sided "moves by more than 1 jnd" check then gives a false-positive rate of 0.27 % at a true d = 0.
  - Example: with σ_d ≈ 1 jnd (two single-position T30s at ≈ 2–3.5 % each, phase-05 figure, outside the corpus), K ≥ 9.
- **Licence:** THIRD_PARTY.md gets one row per set: authors, title, DOI, "CC BY 4.0, validation only, not shipped, not committed, changes: shoebox mapping". Each committed report derived from them carries the same attribution. The session confirms the licence on the live record and stores it in the manifest.
- **B11 (B)** stays on BRAS as decided. 05b additionally *prints* the 05d numbers as context.

**Confidence:** medium-high (PRD NFR-1 and F2; CLAUDE.md rules).

**Reversal:** if the projected nightly runtime is too long, the run moves outside CI under phase-05's 24 h rule, with K unchanged.

### SD-4: Does the "measured α for all surfaces" requirement stay?
**Validity screen.**
- Bologna fails three criteria (V9).
- RR-III has no IRs.
- Obtaining the DELTA report would leave the walls and floor as textbook values, and at low absorption ᾱ is dominated by those small values (Eq. 4.30), so a 0.02-vs-0.03 error matters.

**DECISION.**
- **Keep the F2 target unchanged as the bar for the word "validated".** Record that no open dataset meets it (reports 13 and 14). This is the branch F2 already foresees ("if none is found, the beta decision says so"), so no settled decision changes.
- **Low-cost action, now:** one request to the Aalto authors or FORCE/Flex Acoustics for the DELTA 2018 report and its standard. It improves the provenance label for the panel α only.
- **Do not pursue** Bologna.
- **Commissioning a measured-α room:** Maisara decides **after** 05/05d.
  - If the input-matched differential is within 1 jnd but the absolute AQ9 errors are large, the input data dominate (as Vorländer §11.5 Round-robin I found). A commissioned room is then the only route to "validated", and it is a business cost for Maisara.
  - If the differential exceeds 1 jnd, the method is at fault, and B12/B2 come first.
- **Phase 13 beta decision wording:** "Second measured source: Arni (202 m³) and dEchorate (86 m³), CC BY 4.0, used in phase 05d. No open dataset has measured α for all surfaces; all measured comparisons (BRAS, Arni, dEchorate) are evidence, not validation of NFR-1. Input-matched distribution test: [result]. Coverage: domestic small room (one treated empty cuboid), mid room 145–454 m³, halls 2 350/8 650 m³ (BRAS); none for outdoor, cars or furnished living rooms."

**Confidence:** high for the product part (F2, NFR-1); medium for the commissioning trigger.

**Reversal:** a dataset with measured α appears (researcher), or the DELTA report arrives together with measured wall α.

### SD-5: NFR-1 claims that must change
**DECISION.**
1. **§1 BRAS row:** "the only open dataset with geometry, (estimated) materials and measured IRs together" is contradicted by Motus, Arni and May et al. (D1, D2, V11). The replacement wording is under Challenges.
2. **F2:** append "Second source adopted: Arni + dEchorate (decider report 15); measured-α target not met by any open dataset."
3. **AQ9 measured row:** extend it to "BRAS, Arni, dEchorate, by α set; all evidence; plus the input-matched distribution test (05d), reported".
4. **Everywhere** (report summaries, the beta decision, any UI or marketing text): "validated against real rooms" must read "compared with measured rooms (evidence)". For user scenes the claim stays "method evidenced on N rooms" (F2).

**Confidence:** high. **Reversal:** none expected.

---

### Summary

| id | decision (exact value/wording) | confidence | PRD basis | corpus basis | reversal condition |
|---|---|---|---|---|---|
| SD-1 | Adopt Arni (zenodo.6985104) + dEchorate (zenodo.6576203, omni sources only); Motus and May reserves; SRIRACHA lead | medium | NFR-1, FR-3D-3, AQ1, AQ8, "spaces empty" | Vorländer Eq. 4.30/4.32, §11.5; Kuttruff Table 5.2, §8.7 Eq. 8.56 | Arni layout impractical or no dEchorate omni source (05d) → Motus moves up |
| SD-2 | Absolute errors: "evidence, not validation"; matched pairs: "method evidence with the input bias cancelled to first order"; dEchorate timing is a sanity check; < 300 Hz not evaluable | medium | NFR-1, F2 | Vorländer §11.1.2, §11.5, Eq. 4.13; Kuttruff Eq. 3.44, §8.7 | none from DELTA alone |
| SD-3 | New phase-05d after 05 (05b not dependent; 13 dependent); CI gates: checksum + tamper, reproducibility, nightly baseline, matched-pair selector with negative control; K ≥ 9(σ_d/jnd)² from a ≥ 51-pair pilot; CC BY 4.0 rows in THIRD_PARTY.md | medium-high | NFR-1, CLAUDE.md | AX11 convention | nightly runtime → outside-CI rule |
| SD-4 | F2 target kept as the bar for "validated"; request the DELTA report; Bologna dropped; commissioning decided after 05/05d; beta wording as above | high/medium | F2, Q9, NFR-1 | Vorländer §11.5 (input data dominate) | measured-α dataset found |
| SD-5 | Fix the §1 row, F2 and the AQ9 row; "compared with measured rooms (evidence)" everywhere | high | NFR-1, F2 | — | — |

### Challenges to settled decisions
1. **§1 BRAS row wording** (decider report 11, accepted by Maisara). "The only open dataset with geometry, (estimated) materials and measured IRs together" is factually wrong per researcher D1 (Arni), D2 (Motus: 3D model plus α per surface, CC BY 4.0) and V11 (May et al.).
   - Proposed replacement: "the first adopted open dataset with geometry, estimated materials and measured IRs; its authors say the CR rooms 'cannot serve as a direct reference' (F2); second source: phase 05d."
   - This changes no rule.

### For Maisara
- **SD-1:** Use two free, commercially usable datasets: Arni (a 202 m³ room with thousands of panel settings) and dEchorate (an 86 m³ box whose walls switch between hard and absorbing). Skip the others: people in the room, wrong licence, furniture v1 can't model, or nothing new.
- **SD-2:** Neither proves accuracy outright, because their material data are not measured. Arni's matched settings do test one thing BRAS cannot: whether moving the same absorption around changes the sound as it does in reality, with the material error cancelled.
- **SD-3:** Add one new phase, 05d, after 05. It does not hold up 05b. CI checks the downloads, the repeatability and a fake-pair control; the accuracy numbers are reported, not gated.
- **SD-4:** Keep "measured materials" as the bar for saying "validated". Send one email asking for the panel lab report. Decide on paying for a room measurement only after seeing the 05/05d numbers. The beta decision states plainly what was and wasn't covered.
- **SD-5:** Correct the plan's wording so it never says "validated" for these comparisons, and fix the BUILD_PLAN line that calls BRAS the only such dataset.

Files: `/home/user/makroof/docs/BUILD_PLAN.md`, `/home/user/makroof/docs/phases/phase-05.md`, `/home/user/makroof/docs/phases/phase-13.md`, `/home/user/makroof/docs/review/phase-04-consult/13-researcher-second-dataset.md`, `/home/user/makroof/docs/review/phase-04-consult/14-researcher-leads-verified.md`, `/home/user/makroof/src/sim/ism/ImageSources.h`.