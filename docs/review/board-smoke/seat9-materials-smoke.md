# Seat 9 smoke question (2026-11-09, dry run, nothing applied)

**Convening brief (orchestrator, standing in for the decider for this single-seat format test):**
Phase 12 (material library + starter presets) must choose how a material entry is stored. Options:
(A) one octave-band absorption coefficient per band, single source; (B) per-band low/high bounds plus a
nominal value and a provenance field (≥ 2 independent sources or a single-source flag), the simulator
using the nominal; (C) as (B) plus a per-material "uncertainty" slider in the UI.

**Seat 9's report, verbatim:**

METHOD: general-purpose worker given .claude/agents/seat9-room-acoustician.md verbatim

SEAT 9 POSITION

**Persona assumptions that fell to settled decisions (stated up front).** My §2 criterion 5 and C2 step 2 (people as a material by area) fall to the PRD decision "Audience/crowd: not modeled; spaces are always empty"; I do not press it here. My C2 schema ("125 Hz–4 kHz, 63 Hz if sourced") falls to AQ1/AQ3 (8 fixed bands, 63 Hz–8 kHz); the 63 Hz and usually the 8 kHz columns are therefore extrapolated and my position treats them as the widest-uncertainty bands.

**1. Reading.** The matter is how `resources/materials.json` stores a material: nominal only (A), nominal with bounds and provenance (B), or B plus a user-facing uncertainty slider (C). Cues triggered: §4 "Coefficient provenance" (single source and α > 1 are red flags), situation S8 (suspicious coefficient → cross-source, bracket, recompute with low and high bounds), C2 (library audit; exit: every entry carries bounds), and for C, S5 (a new control is exposed only if its range crosses a JND).

**2. Ranking.**
1. **B — prefer**, with one addition of my own (call it B′): the bounds are consumed by Phase 12's own acceptance test, so each preset's "documented T30 range" is the Sabine/Eyring bracket from the low and high bounds, not a guessed range, and a reference-room check (recompute a measured room's T30 with both bounds; the bracket must straddle the measurement) runs in `tools/acoustics`.
2. **A — can live with, reluctantly (rating 2).** Phase 12 already demands a citation per entry, so A is not provenance-free; what it lacks is the band and the single-source flag.
3. **C — can live with (rating 2), but it is not my ground to approve:** which controls ship belongs to Seat 6, their audibility to Seat 1 (§18).

**3. Tension now.**
- **A: 2.** Without bounds the C2 test cannot run, and the preset T30 ranges in the acceptance criterion are opinions. The spread matters at the JND scale: for a room of uniform ᾱ, T ∝ 1/ᾱ (Kuttruff Eq. 8.53 form, T = 0.161·V/A), so ΔT/T ≈ −Δᾱ/ᾱ. Hard rooms (`warehouse`, `courtyard`, `chapel_box`, `concert_hall_box`) sit at ᾱ ≈ 0.02–0.05, where an inter-table difference of 0.01 (concrete/plaster entries differ by that across published tables; corpus: Vorländer Annex lists chamber walls at 0.01–0.04 across bands) is ±20–50 % in T, i.e. 4–10 EDT JNDs (5 %, Vorländer Table 6.1; Kuttruff §7.6 gives ≈ 4 %). For `living_room` at ᾱ ≈ 0.25 a ±0.05 spread is ±20 %, ≈ 4 JND. A preset built on single values can pass its T30 range and still be an unknown distance from any measured room.
- **B: 1.** The cost is data work for the founder, not accuracy: two sources for 25–40 entries, and some outdoor entries (snow, soil, car trim) will end up single-source flagged, which is honest.
- **C: 2.** The slider spends interface budget below 1 JND for most surfaces: a single non-dominant surface's bounds move A by S_i·Δα_i; e.g. 2 m² of glass at ±0.03 in a 40 m² living room with A ≈ 10 m² is ±0.6 % in T, ≈ 0.1 JND. It crosses a JND only on the dominant absorber. And it is a physics control with no audible meaning (§13), exposed to users the PRD says should describe the space, not translate it into decay parameters (PRD "Problem"). Phase 11 already exposes an advanced per-band α table, so C duplicates an existing edit path with a less honest name.

**4. Tension later (the debt).**
- **A: 2.** The library is module3d-side data and scenes store numbers (phase-12 scope 2), so no contract bump is needed to add bounds later; the cost is re-sourcing every entry a second time and re-deriving every preset range (roughly a second pass over the whole library, `[Hyp]` one to two sessions). Evidence that could overturn it arrives at the first C3-style blind A/B of a preset against a measured reference, or at any complaint "too dead / too live": with A nobody can separate engine error from table error. The project already met this pattern: AQ9 records that the BRAS CR errors "measure method plus input data", and Round-robin I began with simulated T too long because users underestimated absorption (Vorländer §11.5).
- **B: 0–1.** Commits later phases to carrying bounds through library revisions; nothing in `src/sim` changes (nominal in, as random-incidence tables intend, Vorländer §11.1.2). Risk: false independence when the PTB round-robin database is republished in several textbooks (Vorländer Annex names Bork's database as its main source) — see conditions.
- **C: 2.** A shipped control is hard to withdraw; every library revision of a bound becomes a user-visible behaviour change; and the slider becomes a hidden decay knob users turn to "fix" a preset instead of changing the room, which inverts the PRD's premise. Overturning evidence: Seat 1's first blind test of bound-to-bound changes per material.

**5. Evidence.**
- JNDs EDT 5 %, G/C80 1 dB, stated for 500–1000 Hz: Vorländer Table 6.1 (corpus); decay difference limen ≈ 4 %: Kuttruff §7.6 (corpus). Register row "JNDs ISO 3382-1 Annex A" `[Peer; H]` agrees.
- ISO 354 chamber method: Sabine evaluation overrates α, sometimes > 1; edge diffraction; round robins "remarkable disagreement, especially at low frequencies": Kuttruff §8.7 (corpus, qualitative). Toole: coefficients above unity, "something the industry has learned to live with" (corpus). My register's "±0.1 or worse at LF" `[Peer; Vercammen 2010/2019; Scrosati 2020]` is a number the corpus does not give: **researcher to verify** before it appears in any plan text.
- Inputs dominate accuracy: Round-robin I (absorption underestimated → T too long; harmonised α → much better), Round-robin III (operator's α and s choice remains crucial): Vorländer §11.5 (corpus). Kuttruff Ch. 9: given absorption uncertainty, Sabine-vs-Eyring precision is "almost meaningless" (corpus; stated for audience absorption, I extend it to any dominant absorber `[Inf]`).
- Mounting changes a "material" by 2×: 30 mm rock wool on concrete ≈ 0.44 at 250 Hz vs ≈ 0.9 at 315 Hz with a 50 mm partitioned air gap: Kuttruff Fig. 6.14 (corpus). So a library entry needs its mounting/construction stated.
- Random-incidence nominal is adequate for the engine: a specific-angle loss may differ up to 40 % from random incidence before the reflection error exceeds 2 dB: Vorländer §11.1.2 (corpus).
- T ∝ 1/A: Kuttruff Eq. 8.53 / Vorländer Eq. 4.32 (corpus); the percentage arithmetic above is mine.
- Code: the contract carries `bandsAbsorption` (8 bands) and one `scattering` per surface, range [0.01, 1] / [0, 1] (from `src/contract/SceneDescription.h`, `Diagnostics.h`); α > 1 therefore must be clamped at import and flagged, not stored. `resources/materials.json` does not exist yet (from the tree).

**6. Conditions of acceptance.**
- **A → 1:** add, at minimum, a `provenance` field with a `single_source: true/false` flag and a `flags` list (`alpha_clamped_from_above_1`, `extrapolated_63hz`, `extrapolated_8khz`, `mounting_assumed`), so bounds can be added later without re-reading the sources. Document each preset's T30 range as a bracket computed from a stated ±Δα, not a guess.
- **B stays 1 / B′ → 0:** "independent" means a different measurement, not a different book (two textbooks reprinting the PTB database count as one); each entry states mounting; bounds at 63 Hz and 8 kHz are the widest and marked extrapolated where they are; α > 1 in a source is recorded in the bound and clamped to 1.0 in the nominal (AQ3).
- **C → 1:** replace the slider with a read-only display of the bracket (e.g. the preset's T30 "0.4–0.6 s") and keep bounds in tooling; or ship it only after Seat 1 shows a blind bound-to-bound difference for the materials it applies to and Seat 6 names it by its audible meaning.

**7. Hand-offs.**
- Seat 6: whether any uncertainty control belongs on the canvas, and its name.
- Seat 1: blind audibility of bound-to-bound changes per preset; a T30 JND beyond 500–1000 Hz (AQ9 notes the corpus has none).
- Researcher: inter-laboratory spread numbers (Vercammen 2010/2019, Scrosati 2020); the PTB database's reuse terms (phase-12 licence check, `docs/THIRD_PARTY.md`).
- Maisara: the data-work cost of two sources per entry versus a flagged single source.
- Seat 2: nothing changes in `src/sim` under any option; the engine reads nominal values.

**8. Premortem.** If A is chosen and fails, the presets pass their guessed T30 ranges, the first blind A/B against a measured room misses by several JNDs, and the engine is blamed for a table error, the Round-robin I pattern; Maisara notices first on the listening checklist, and the contractor second on the provenance review the phase file already names as his focus.
