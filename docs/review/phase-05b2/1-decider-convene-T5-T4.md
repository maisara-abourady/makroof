# Decider — convening round, phase 05b session 2, D-T5 and D-T4 (2026-11-09)

Verbatim output of the decider agent (convening round, `/fix-plan` step 3a), saved by the orchestrator.

**Corpus revision:** `c1b171fe649f07cbeb952ef1f75d89bfaa414d0d` (`docs/corpus/SOURCE_COMMIT`; 14 files present).

## PRD digest
- **Who it is for:** producers and DJs on macOS and Windows, in any DAW. They do not know spatial audio. They describe a space (indoor or outdoor) and the plugin works out what it does to sound (PRD Overview, Target users, Key decisions "any environment").
- **What v1 must deliver:** a track that sounds as if played in the designed or preset space (FR-3D-3 has four categories, outdoor included). Accuracy is a quality gate, not a success metric (NFR-1). Success itself is subscribers.
- **Hard constraints this round must respect:**
  - PRD: NFR-1 (accuracy first); NFR-2 (heavy CPU is fine if it buys accuracy, but the plugin must stay usable in a DAW session); NFR-3 / FR-SIM-6 (no artefacts under automation); NFR-8 / FR-SIM-2 (no scene- or preset-specific logic); NFR-6 / AX5 (determinism).
  - Plan rows: AX6 (rooms 1.5–100 m per side; 44.1–96 kHz); AQ10 (rebuild ≤ 50 ms is a target that is recorded, not a blocker; full rebuilds are recorded, not budgeted; misses go in §0); AQ4 (offline renders rebuild synchronously); contract unchanged; Phase 13 scope 1 owns any memory budget.
  - Settled in phase-05b2 §1: gate (B) fails, so AX21 stands; the switch is built this session (Maisara, option (b)); window check branch (i); B12 (Eyring stays); AX22, N_cap and the mixing-time rule are unchanged; AX36 accepted.
  - Settled in phase-05b scope 0: ℓ is absolute and a coarser ℓ is not a remedy; the Table 15.1 option is a Phase 10 remedy only if W1 > 700 ms.
  - PRD out of scope: user atmosphere control, crowds.
- **Verification culture (CLAUDE.md):** every DSP behaviour is checked automatically; independent references are preferred over self-made goldens; a golden is never regenerated to make a test pass.

---

## Convening round

### Decision D-T5: how the switch interacts with the matching

**What is being chosen.** How E_target, the AX22 fallback test, `bandsAxisShares` and the `open_field` outcome are defined once the AX16 scattered entries stop setting the tail level. This decides the code in `planEmitter`/`matchTail`, which output D-T1 must produce, the goldens and tests (`test_hybrid_ir.cpp` "open_field AX16 consistency", `test_tail.py::test_open_field_has_no_tail`), and what Phase 08 receives.

**Options.** Every seat gets the same list.

*(1) What E_target is built from*
- **5.1-A.** E_target,b = the window-referred specular entries plus the window-referred propagated diffuse energy. The diffuse energy is injected as s(1−α) at each specular hit (Kuttruff Eq. 4.24), propagated with Eq. 4.35 and the §5.2 split, gathered at the listener (Eq. 4.29), with AX4 air. It uses the same Hann window, the same Eyring referral and the same t_mix,e. This is exactly `ref_hybrid.target_hybrid`, and it applies to all 8 bands.
- **5.1-C** (minimal variant, mine). 5.1-A in 500 Hz–2 kHz only, the bands the window check validated; the AX16 entries stay in the other five bands.
- **Dropped at bounds, not for rating:**
  - Keeping AX16 breaks Maisara's 2026-11-09 option (b) and the B11 rule.
  - Any blend of AX16 and the hybrid (maximum, mean and so on) is not the validated model (phase-05b2 §3 D-T5 (1)).

*(2) What the AX22 realised-k test counts*
- **5.2-A.** k_real, `needsIsmFallback` and t_mix,e are computed exactly as today, from the specular plus AX16 scattered entries. The AX16 list is still computed, but only for this test and for diagnostics; it has no role in the level. This is what `phase04_plan` does and what session 1 compared against.
- **5.2-B.** k_real from the specular entries only.
- **5.2-C.** k_real from the specular entries plus the diffuse energy, entered as dense terms (one per time bin).
- 5.2-B and 5.2-C change AX22, which is settled. They are out of bounds unless the loop shows the change is forced. Rate them only if you rate 5.2-A a 3; otherwise write "not rated (out of bounds)".

*(3) What `bandsAxisShares` is computed from, and what Phase 08 receives*

Facts for every seat, from the code and the plan:
- `bandsAxisShares` is computed in `matchTail` (`src/sim/tail/NoiseTail.cpp` L234–244) and printed only by `render_cli --diagnostics` (`src/cli/Cli.cpp` L484). AX22 lists it as "reported, not gated".
- `docs/phases/phase-08.md` session 2 item 5 builds the binaural late tail from two noise tails with the Phase 04 per-band envelopes, mixed to a diffuse-field interaural coherence target. It reads no direction from the tail.

The options:
- **5.3-A.** Unchanged: computed from the AX16 entries (specular and scattered, at the specular arrival directions); diagnostic only. Phase 08 receives the switched E_b and t_mix,e only.
- **5.3-B.** Computed from the specular entries plus the diffuse model's gather directions (the line dS′→P, energy-weighted in the window); diagnostic only. Phase 08 still receives only E_b and t_mix,e. This raises D-T1's required output: per-direction window energies.
- **5.3-C.** As 5.3-B, and the per-band direction distribution of the window's diffuse energy also goes to Phase 08 as a new input for a directional late tail. This changes Phase 08's scope, and Phase 08's dependencies gain 05b or 05h.
- **5.3-D.** Computed from the specular entries only and labelled specular-only; diagnostic only. Phase 08 receives E_b and t_mix,e.

*(4) `open_field` (outdoor fixture)*

Facts: the fixture is 100×100×30 m. Five faces have α = 1 and s = 0. The floor has α 0.05…0.99 and s = 0.4. Today E_b = 0: the floor reflection arrives 1.4 ms after the direct sound, before the window starts, and every later image is zero (phase-04.md L62–68). The scene is in the AX22 fallback, with t_mix,e = 1404.4 ms and a nominal Eyring T60 of 0.636 s at 1 kHz (golden `phase04_open_field_omni`), although Eyring does not apply here (phase-04.md, citing Vorländer §4.4.1).

Under 5.1-A, Lambert energy scattered by the floor reaches the listener from across the floor. Part of it falls inside [t_dir,e + 2.5 ms, 1404 ms], so E_b > 0 in general. A noise tail would then start at about 1.4 s, at that energy's level after decaying along the nominal Eyring rate. Its size has not been computed (K9).
- **5.4-A.** Accept the generic outcome. Replace the Phase 04 check "E_b = 0" with two checks: E_b equals an independent single-scatter Lambert floor integral's window value, to D-T1's tolerance; and the rendered IR's energy later than 50 ms stays at or below the ledger OF Lambert estimate (−23 to −43 dB per band) as an upper bound.
- **5.4-B.** A generic rule that keeps E_b = 0 when the propagated diffuse energy has vanished before the handover. The criterion and its AX would be proposed by the seats. It must be generic (NFR-8) and must not create a level step under automation (FR-SIM-6).
- **Dropped at bounds:** keeping E_b = 0 for `open_field` by any scene-specific means (NFR-8).

**Convening table, D-T5**

| seat | status | reason (README convening table item) | brief |
|---|---|---|---|
| 1 Perceptual gatekeeper | convened | audibility of an error and a detail; which bar applies; acceptance tests. This is a PRD-priority seat: the matter changes what the user hears. | B1-T5 |
| 2 Engine architect | convened | scattering and late-tail statistics; the representation handed to the renderer; simulator compute; validation and circularity | B2-T5 |
| 3 Reverb renderer | convened | decay and level matching; time variance under automation (the AX22 jump point); channel spreading | B3-T5 |
| 4 Chain keeper | convened | binaural architecture: what Phase 08's late tail receives; cross-format loudness parity (phase-08 item 5, ±1 dB) | B4-T5 |
| 5 Deadline keeper | convened | beside the audio thread: rebuild contents on the builder thread; offline equals real-time; CI gates. This is a PRD-priority seat. | B5-T5 |
| 6 Canvas designer | convened | couplings: what the absorption and scattering controls do to the tail; presets (outdoor); the automation model. This is a PRD-priority seat: the user's controls change meaning. | B6-T5 |
| 7 Founder | convened | schedule and complexity cost (5.3-B/C widen D-T1 and Phase 08); public accuracy wording. This is a PRD-priority seat: cost. | B7-T5 |
| 8 Storyteller | convened | what producers do: depth and density in venues with concentrated absorption; outdoor scenes; which features storytellers use | B8-T5 |
| 9 Room acoustician | convened | real rooms as references: concentrated absorption (seating, carpet, open faces), outdoor ground, preset validation | B9-T5 |

**Common D-T5 brief (pass verbatim to every convened seat, followed by that seat's addendum)**

> Subject: phase 05b session 2, decision D-T5 (`docs/phases/phase-05b2.md` §3; context §0–§2, §4, §8). Options: 5.1-A, 5.1-C; 5.2-A (5.2-B and 5.2-C only if you rate 5.2-A a 3); 5.3-A, 5.3-B, 5.3-C, 5.3-D; 5.4-A, 5.4-B, exactly as listed in the decider's convening output (the orchestrator attaches the option block). Settled, do not reopen: the switch happens this session; AX21, AX22, N_cap, the mixing-time rule, Eyring (B12) and AX36 are unchanged; the contract is unchanged; NFR-8 applies. D-T1 (formulation) comes later; do not choose or favour one.
>
> Read:
> - `docs/phases/phase-05b2.md` §0–§4 and §8;
> - `docs/BUILD_PLAN.md` §2 AX16, AX21, AX22, AX20, AX36, and §0 rows 04 and 05b;
> - `docs/validation/report-phase05b.md` §5 and §5b;
> - `src/sim/tail/NoiseTail.h` and `NoiseTail.cpp` (`matchTail`, `needsIsmFallback`);
> - `src/sim/Engine.cpp` `planEmitter` (L115–151);
> - `tools/acoustics/ref_hybrid.py` `phase04_plan` and `target_hybrid` (L502–533);
> - `docs/phases/phase-08.md` session 2 item 5;
> - `tests/scenes/valid/open_field.json` and `tests/golden/phase04_open_field_omni.json`;
> - PRD NFR-1, NFR-2, NFR-3, NFR-8, FR-SIM-6, FR-3D-3.
>
> For each option of each sub-question (1)–(4): give ratings now and later (0–3) with one-line reasons in your own measures; conditions of acceptance for every rating of 2 or 3; and evidence tags, corpus first. Name anything the researcher should verify.

**Seat addenda**
- **B1-T5 (Seat 1).**
  - Is a tail-level change of +3.87 / −1.17 dB (synthetic) and −1.18 dB (BRAS CR3, 2 kHz) audible, against the 1 dB G jnd (Vorländer Table 6.1, extended)? Is the uniform-α residual (≤ 0.43 dB) audible?
  - Does 5.1-C's band split create a spectral seam a listener could hear?
  - (3): is a directional late field audible in binaural rendering with a generic HRTF, and which bar applies (plausibility or authenticity)?
  - (4): is an `open_field` noise tail starting at about 1.4 s audible at the level the model gives (not yet computed)?
  - Which acceptance tests would you require for each option?
- **B2-T5 (Seat 2).**
  - Is 5.1-A equivalent to the validated model in every band, and what does 5.1-C cost in consistency?
  - Is 5.2-A defensible once the level comes from the diffuse model? The fallback guards against sparse or flutter fields (Kuttruff §4.1–4.2); say whether diffuse energy in the window removes that need, or whether only a forced AX22 change could address it.
  - (3): what each option adds to D-T1's required output (a scalar per emitter and band versus per-direction tallies). Note that adjoint candidate (d) needs 5.2-A for linearity.
  - (4): the physics of single-generation floor scatter, and Eyring's inapplicability outdoors.
- **B3-T5 (Seat 3).**
  - Behaviour of the tail level at the seam (t_mix,e).
  - The AX22 jump point under automation: does 5.2-A leave Phase 10's continuity work unchanged?
  - Does the renderer need tail directions (5.3-C) for channel spreading?
  - What an `open_field` tail starting at 1.4 s does to the render.
- **B4-T5 (Seat 4).**
  - What Phase 08 should receive: is the diffuse-coherence tail of phase-08 item 5 enough, or is 5.3-C needed?
  - The effect on the ±1 dB omni-to-binaural energy parity.
  - Whether Phase 08 may start before the switch lands (the phase-05b2 §8 dependency on 05h).
- **B5-T5 (Seat 5).**
  - Builder-thread cost of keeping the AX16 list for k_real (5.2-A), and of direction tallies (5.3-B/C).
  - Determinism (AX5); offline equals real-time.
  - Which tests must be replaced and how they should be gated (the `open_field` E_b = 0 tests in C++ and Python).
  - Phase 10 continuity.
- **B6-T5 (Seat 6).**
  - How the per-surface absorption and scattering controls change audibly in rooms with concentrated absorption.
  - Whether any option creates a coupling or an automation behaviour a user would not expect.
  - Outdoor presets (FR-3D-3) under 5.4-A versus 5.4-B.
- **B7-T5 (Seat 7).**
  - Schedule and complexity of each option: 5.3-B/C widen D-T1 and Phase 08; 5.2-A keeps two energy models alive.
  - Public accuracy wording each option supports or forbids.
  - What one founder can sustain.
- **B8-T5 (Seat 8).**
  - What producers hear and use: the tail level in absorbent clubs and halls (depth, distance, density); outdoor scenes staying "dry with a ground reflection" (phase-05b listening item).
  - Whether a directional tail serves any storytelling use.
- **B9-T5 (Seat 9).**
  - Real venues with concentrated absorption (unoccupied seating, Kuttruff §6.7; carpet; open faces) and the size of the error each option leaves.
  - Whether an outdoor ground-scatter tail at 1.4 s is plausible against real outdoor responses.
  - Which option keeps preset validation (FR-3D-3) honest against measured references.

---

### Decision D-T4: cost budget (formulation-neutral)

**What is being chosen.** Three things, all independent of which formulation D-T1 later picks: (a) the working memory ceiling per instance at the largest AX6 room; (b) how W1/W2 are read once the diffuse part exists; (c) which misses block and which are recorded. This decides the O15 cost records, whether D-T3 is triggered, and the Phase 13 cross-reference.

**Options.** Every seat gets the same list.

*(a) Memory ceiling.* The ceiling covers the peak additional working memory of the diffuse computation per plugin instance at the largest AX6 room (100 m per side). It covers both emitters, every supported sample rate, and both transient and resident data (anything kept between rebuilds). The candidate values are product choices for rating, chosen to span the range; none is a fact.
- **4a-1.** ≤ 128 MB, about the Phase 07 baseline (+122.6 MB): the switch at most roughly doubles per-instance memory.
- **4a-2.** ≤ 1 GB.
- **4a-3.** ≤ 4 GB.

*(b) Time reading.* In both options AQ10's 50 ms stays a target that is recorded, and the full-rebuild time is recorded beside W1/W2 for the AQ10 room, CR4 and the 100 m room, at 48 and 96 kHz.
- **4b-1.** W1/W2 include every part of the diffuse computation that a position-only rebuild runs. Parts that depend only on room and materials are excluded only if the formulation keeps them between rebuilds and their resident memory counts inside (a).
- **4b-2.** W1/W2 include the whole diffuse computation, with no cache credit, because Phase 10's cache scope today is only the unit decay. Credit comes only when Phase 10 adopts a kernel cache through an AX.

*(c) What blocks and what is recorded*
- **4c-1.** Memory over the ceiling at any AX6 room blocks the formulation in that range and sends it to D-T3, with the numbers going to Maisara. Time misses are recorded only (AQ10). W1 > 700 ms triggers the Phase 10 Table 15.1 remedy (phase-05b scope 0).
- **4c-2.** As 4c-1, plus a full rebuild at the largest room above a usability limit also blocks. The limit would be set from the researcher's base rates (RQ4, RQ5). This amends AQ10's "full rebuilds are recorded, not budgeted" (accepted by Maisara 2026-11-05), so if it is chosen it goes to her as a challenge.
- **4c-3.** Nothing blocks. The ceiling becomes a reporting threshold handed to Phase 13.
- **Dropped at bounds:**
  - "No ceiling, record only": phase-05b2 §3 D-T4 requires a working ceiling.
  - Any remedy by a coarser ℓ (phase-05b scope 0).
  - Shortening the image list or N_cap (AQ10, AX22).

**Convening table, D-T4**

| seat | status | reason | brief |
|---|---|---|---|
| 1 Perceptual gatekeeper | convened | the 700 ms / Table 15.1 update interval is a perceptual criterion: whether a slower update is heard as lag under automation. This is a PRD-priority seat. | B1-T4 |
| 2 Engine architect | convened | simulator compute and recompute time; whether each ceiling leaves any candidate (a)–(f) viable at 100 m | B2-T4 |
| 3 Reverb renderer | convened | per-instance cost; update rate under automation (AQ4 interval = max(20 ms, 30 ms, rebuild)) | B3-T4 |
| 4 Chain keeper | convened | Phase 08/09 share the budget (HRTF set ≈ 32 MB, BRIR build; AQ10 "every output mode from Phase 08") | B4-T4 |
| 5 Deadline keeper | convened | builder-thread memory; concurrent builders across instances; host and validator timeouts; offline synchronous rebuild (AQ4); CI gates. This is a PRD-priority seat. | B5-T4 |
| 6 Canvas designer | convened | DAW workflow: delay from an edit to hearing it; room-size automation means full rebuilds. This is a PRD-priority seat. | B6-T4 |
| 7 Founder | convened | cost floor, customer hardware, support load, the "any environment" claim if a ceiling forces D-T3. This is a PRD-priority seat. | B7-T4 |
| 8 Storyteller | convened | workflow requirements: many instances per session, bounce times | B8-T4 |
| 9 Room acoustician | convened | which real venue classes need rooms near the 100 m limit (FR-3D-3 halls, festivals, outdoor) and what a ceiling that excludes them costs | B9-T4 |

**Common D-T4 brief (pass verbatim to every convened seat, followed by that seat's addendum)**

> Subject: phase 05b session 2, decision D-T4 (`docs/phases/phase-05b2.md` §3 D-T4, §0.3, §8). Options: 4a-1, 4a-2, 4a-3; 4b-1, 4b-2; 4c-1, 4c-2, 4c-3, exactly as listed in the decider's convening output (the orchestrator attaches the option block). D-T4 is formulation-neutral: do not choose or favour a D-T1 candidate. Do say whether a ceiling would rule out every candidate class at 100 m, and so force D-T3.
>
> Read:
> - `docs/BUILD_PLAN.md` §2 AQ10, AQ4, AX6, AX20, AX22, AX36 (c), and §0 rows 04 and 07;
> - `docs/phases/phase-05b.md` scope 0 (L31–42);
> - `docs/phases/phase-13.md` scope 1 (L36–47);
> - `docs/phases/phase-10.md` scope 2;
> - `docs/phases/phase-08.md` scope 3;
> - `src/plugin/core/IrBuilderThread.h`;
> - PRD NFR-2, NFR-3, FR-SIM-6, FR-3D-3, Key decisions "Accuracy vs CPU".
>
> Context:
> - The dense kernel needs ≈ 0.47 GB in the AQ10 room, ≈ 2.5 GB for CR4 and ≈ 3–6 TB at 100 m (phase-05b2 §0.3).
> - Phase 07 baseline: +122.6 MB RSS at 96 kHz in the maximum room (Linux only).
> - Full rebuild in the maximum room: 603–802 ms at 48 kHz and 1509–1884 ms at 96 kHz.
>
> For each option of (a), (b) and (c): give ratings now and later (0–3) with one-line reasons; conditions of acceptance for every rating of 2 or 3; and evidence tags. Name base rates you want the researcher to verify.

**Seat addenda**
- **B1-T4 (Seat 1).** The perceptual standing of the 700 ms and 3 s intervals (Vorländer Table 15.1, after Lentz et al.). Is a longer rebuild audible as lag or as an artefact under automation? Make no audibility claim about memory.
- **B2-T4 (Seat 2).** For each ceiling: is there at least one candidate class whose memory scaling plausibly fits at 100 m (mark it [Hyp] until D-T1 measures it)? The risk that a ceiling pre-decides D-T1 or forces D-T3. Whether 4b-1's cache credit is sound.
- **B3-T4 (Seat 3).** Per-instance cost and the update rate under automation. The rebuild interval through AQ4's chain (slot wait + rebuild + 2P).
- **B4-T4 (Seat 4).** Headroom Phase 08/09 need inside the same budget (HRTF memory, BRIR build time, W1/W2 per output mode).
- **B5-T4 (Seat 5).**
  - Concurrent builder threads across instances (from the code: one `std::thread` per `IrBuilderThread`).
  - Host and validator timeouts: pluginval strictness 10, auval, state load, and offline bounce with synchronous rebuild (AQ4).
  - Which misses should gate CI.
- **B6-T4 (Seat 6).** Edit-to-hear delay for room-size and material changes (full rebuilds); room-size automation; time-to-first-plausible-scene.
- **B7-T4 (Seat 7).** Customer hardware; support load from memory use; the cost of a ceiling that later narrows "any environment" through D-T3 or a contract change (Maisara's call); sustainability.
- **B8-T4 (Seat 8).** Sessions with many instances; tolerance for bounce times; when a producer would abandon a slow scene.
- **B9-T4 (Seat 9).** Which real venue classes sit near 100 m per side (large halls, arenas, festival grounds, outdoor), and what each ceiling and blocking option would cost FR-3D-3 presets.

---

### Knowledge inventory, first pass

| id | what must be known | source | status |
|---|---|---|---|
| D5-K1 | The validated combination: specular entries + diffuse bins, same window and referral, t_mix,e and fallback from `phase04_plan` with k_real on specular + AX16 scattered entries | from the code: `tools/acoustics/ref_hybrid.py` L502–533 | known |
| D5-K2 | Hybrid vs tracer within 0.08 dB (SE ≤ 0.078 dB) | report-phase05b §5: 15 cases, 500 Hz–2 kHz, one AX28 pair per case, 20×30×10 m geometry | known under those conditions; **under-informed** for 63–250 Hz and 4–8 kHz (bears on 5.1-C) |
| D5-K3 | AX16 error +3.87 … −1.17 dB (synthetic); BRAS −1.18 dB (CR3, 2 kHz) | report-phase05b §5; AX16 row | known |
| D5-K4 | AX22, N_cap and the mixing-time rule are unchanged | phase-05b2 §1 | known |
| D5-K5 | Who consumes `bandsAxisShares` | from the code (NoiseTail.cpp L234–244, Cli.cpp L484); AX22 "reported, not gated"; phase-08.md item 5 | known: diagnostic only. The phase-05b2 §3 wording "(used for directional output in Phase 08)" is **misinformed risk** in the plan text (see the note under Challenges) |
| D5-K6 | Eq. 4.29 carries direction (ϑ″, the line dS′→P) | Kuttruff §4.5, Eq. 4.29 (notation table L620–621) | to re-read in the decision round |
| D5-K7 | Audibility of late-field anisotropy in binaural rendering | none yet; corpus check (Blauert ch. 3, Begault, Kuttruff §5.1) plus RQ6 | uninformed |
| D5-K8 | `open_field`: fallback active, t_mix,e = 1404.4 ms, nominal T60 0.636 s at 1 kHz, E_b = 0 today | golden `phase04_open_field_omni`; §0 row 04; phase-04.md L62–68 | known (from the code and goldens) |
| D5-K9 | `open_field` E_target per band under 5.1-A | computation C1 | uninformed |
| D5-K10 | Eyring does not apply outdoors | Vorländer §4.4.1 (cited by phase-04.md) | misinformed risk until re-read |
| D5-K11 | Lambert ground estimate −23 … −43 dB after 50 ms | ledger OF; `tools/acoustics/tests/test_ground_scatter.py` (exact integral, fixture geometry, s = 0.4) | known |
| D5-K12 | Candidate (d)'s linearity needs 5.2-A | phase-05b2 §3 D-T1 (d) | known (plan text) |
| D4-K1 | AQ10 definitions: W1/W2, 50 ms target recorded, full rebuilds not budgeted | BUILD_PLAN AQ10 | known |
| D4-K2 | Phase 07 baseline: +122.6 MB RSS; full rebuild 603–802 ms (48 kHz) and 1509–1884 ms (96 kHz) | §0 row 07; phase-13 L40–47 | known; RSS **under-informed** for macOS and Windows (Linux only) |
| D4-K3 | No memory budget yet; Phase 13 decides | phase-13 L45–47 | known |
| D4-K4 | W1 > 700 ms → Phase 10 Table 15.1 remedy; ℓ absolute; coarser ℓ not a remedy | phase-05b scope 0 L33–41 | known |
| D4-K5 | Table 15.1 values: 700 ms for moves > 0.25 m, 3 s for moves > 1 m | vorlaender-auralization.md L3959 | to re-read in the decision round |
| D4-K6 | Dense-kernel memory by room size | phase-05b2 §0.3; AX36 (c) | known for the dense solver only (other formulations are D-T1's job) |
| D4-K7 | One builder thread per instance, so peaks add across instances | from the code (IrBuilderThread.h L49, L92) | known; per-instance ownership to confirm in ScenePipeline |
| D4-K8 | RAM in target users' machines; DAW minimum and recommended RAM | RQ1 | uninformed |
| D4-K9 | Memory used by comparable plugins | RQ2 | uninformed |
| D4-K10 | Instances per session | RQ3 | uninformed |
| D4-K11 | Host and validator timeouts | RQ4 | under-informed |
| D4-K12 | Limits on how long users will wait | RQ5 | uninformed |
| D4-K13 | Phase 08 additions (HRTF ≈ 32 MB) | phase-08.md scope 3 (L64–67) | known in part |
| D*-K | Each seat's tension | seat reports | uninformed (this round) |

### RESEARCH NEEDED (researcher, runs alongside the seats)
- **RQ1 (D-T4 (a)).** How much RAM do music producers' machines have (macOS and Windows, 2025–2026), and what minimum and recommended RAM do the main DAWs state (Ableton Live 12, Logic Pro, Cubase, FL Studio, Studio One, Reaper)? Use vendor documentation with dates and any producer hardware survey, naming each survey's sample. *Changes:* whether 1 GB or 4 GB per instance fits beside a session, which separates 4a-1 from 4a-2 and 4a-3.
- **RQ2 (D-T4 (a)).** Published or measured per-instance memory of comparable plugins: IR or convolution reverbs and room simulators (e.g. Altiverb, Spat Revolution, dearVR PRO, Anaglyph, Steam Audio plugins, Seventh Heaven, Space Designer). Only sources marked read, with the conditions (IR length, sample rate). *Changes:* where each ceiling sits against market norms (Seat 7 and Seat 5 ratings).
- **RQ3 (D-T4 (a)).** Any base rate for the number of reverb or spatializer instances per project. If none exists, say so. *Changes:* the multiplier on the per-instance ceiling.
- **RQ4 (D-T4 (c)).** Timeouts that a long builder-thread or synchronous rebuild could hit: pluginval v1.0.4 at strictness 10 (per-test timeout, from source or documentation); auval; DAW behaviour on a slow `setStateInformation` or `prepareToPlay` (Logic's AU hosting, Ableton and Cubase scanners); offline bounce with a slow non-realtime render. *Changes:* whether 4c-2 is needed and what limit it would carry.
- **RQ5 (D-T4 (c)).** Primary references on response-time limits for interactive systems (Miller 1968; Card, Robertson & Mackinlay 1991; Nielsen 1993), with the task conditions they hold under. *Changes:* the anchor for any full-rebuild usability limit under 4c-2.
- **RQ6 (D-T5 (3)).** Peer-reviewed listening-test evidence on whether direction-dependent (anisotropic) late reverberation is audible against an isotropic diffuse tail in binaural rendering, under which conditions (a strongly absorbing face, non-individual HRTF, headphones). *Changes:* whether 5.3-C has any perceptual basis. If there is none, 5.3-C's later debt cannot be justified now.

**Orchestrator computation (in-repo; not research)**
- **C1 (D-T5 (4), K9).** `open_field` E_target per band and emitter under 5.1-A. The model has a single generation here: s(1−α) injected at the floor's specular hit, Lambert floor patches, gathered directly at the listener (Eq. 4.29), AX4 air. The other five faces have α = 1, so there is no further transport and the dense kernel is not needed; `ref_hybrid.injection` and `gather_kernel` suffice. Use window [t_dir,e + 2.5 ms, 1404.4 ms] with referral at the nominal Eyring rate. Report: the tail level at t_mix,e in dB relative to the direct sound per 10 ms; the rendered energy later than 50 ms against ledger OF; an independent check with `tools/acoustics/ground_scatter.py`.

---

## Summary

| id | decision | state | worst-off seat | sum | confidence | PRD bound | corpus basis | reversal condition |
|---|---|---|---|---|---|---|---|---|
| D-T5 | (1) composition, (2) k_real basis, (3) axis shares and Phase 08 input, (4) `open_field` | convening (9/9 seats) + RQ6 + C1 | – | – | – | NFR-1, NFR-8, FR-SIM-6; settled AX21/AX22 | Kuttruff Eqs. 4.24, 4.29, 4.35, §5.2; Vorländer §4.4.1 (to re-read) | – |
| D-T4 | (a) ceiling, (b) W1/W2 reading, (c) block or record | convening (9/9 seats) + RQ1–RQ5 | – | – | – | NFR-2, AQ10, AX6, phase-05b scope 0 | Vorländer Table 15.1 (to re-read) | – |

## Challenges to settled decisions
- **Not a settled decision, but a plan-text premise to correct.** phase-05b2 §3 D-T5 (3) says `bandsAxisShares` is "used for directional output in Phase 08". From the code and `phase-08.md`, it is diagnostic only and Phase 08 reads no tail direction. This bears on the §8 rule that Phase 08 depends on 05h "unless the decision loop records why 08 may go first". The D-T5 decision will state what Phase 08 actually receives.
- **Possible challenge, pending the seats.** If any seat rates 4c-1 or 4c-3 a 3 on usability grounds (NFR-2), AQ10's "full rebuilds recorded, not budgeted" would come to Maisara as a challenge through 4c-2. I will raise it only if the ratings force it.

## For Maisara
- **D-T5 (convening):** all nine seats are asked how the tail level should switch to the validated diffuse model; whether the fallback test stays as it is; what Phase 08 gets (today it is the tail level only, no directions); and whether the outdoor `open_field` scene may gain a faint tail. Nothing is decided yet.
- **D-T4 (convening):** all nine seats are asked to rate a per-instance memory ceiling (about 128 MB, 1 GB or 4 GB at the 100 m room), how rebuild time is measured, and whether exceeding the memory ceiling blocks. No veto-grade override is pending.

**CONVENE**
