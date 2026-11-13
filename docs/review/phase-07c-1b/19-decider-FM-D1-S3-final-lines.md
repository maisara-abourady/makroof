# 19 — Decider: FM-D1-S3 final lines (file 16 + Seats 5 and 3's conditions)

2026-11-13, corpus c1b171f. Saved by the orchestrator from the decider's report. Maisara chose option (i) herself on 2026-11-13. PRD
bound: NFR preamble (l. 101) "Accuracy is the top priority", NFR-1. D1 (O8) stands: worst-off 1, sum 12. Confidence high (08-3, 09),
medium (07c-2: one cell read from conditions).

Folding: Seat 5 C1 (serial builder calls, repeat-build bit-identity) in all three lines; C2 (coefficients from one shared function or
cache, within one process) in 08-3, 09 (07c-2 has no mix / per-mode coefficients before 08-3); C3 (reuse fixtures, Release job,
exactly 2 seeds, print wall time) in all three; C4 (no-shared-prefix exit backed by an asserted fact) in 07c-2. Seat 3 C1 (zero-tail
'not evaluated (no tail)') in 07c-2 and carried by the decider into 08-3, 09 (the ratio is undefined at zero tail energy); C2 (h only
at the L_f edge), C3 (fade law, EDT, level step in both windows) in 07c-2.

## 1. Tension map
| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| (i) as drafted (file 39) | 1/1 | 1/1 | 0/1 | 1/2 | 1/1 | 0/0 | 1/1 | 0/0 | 1/1 | 2 | 14 |
| (i) file 16 | 1/1 | 1/1 | 1/1 | 0/1 | 1/1 | 0/0 | 1/1 | 0/0 | 1/1 | 1 | 13 |
| **(i) these lines** | 1/1 | 1/1 | **0/1** | 0/1 | **1/1** | 0/0 | 1/1 | 0/0 | 1/1 | **1** | **12** |

S3 0/1 in the seat's words (file 18: "With the conditions: 0"; later "1 (two printed or asserted extras on a test 07c-2 already
builds)"; file 16 cell 1/1). S5 1/1 in the seat's words (file 17: "Conditions (keep the ratings at 1)"); one part read from conditions
— Seat 5 rated before Seat 3's C3(1); read as no higher than 1 because the clause only applies AX18's existing sentence "A `tailSeed`
or fs change gives unrelated tail noise and is joined equal-power", any other law left to 07c-2's loop (which convenes Seat 5). S4 0/1
(file 15; "exactly 2 seeds" meets "≥ 2"; "two serial builds" meets "two renders of one scene and seed, never a measured IR"). S1, S2,
S7, S9 file 37's O8 row. No 3; max 1; sum 12 (back from 13: Seat 3 now 0).

## 2. phase-07c-2
**Scope 9: new bullet after "The load fallback":**
```
   - **Interim stream check (D1, FM-D1-S3; Maisara 2026-11-13).** If this phase's loop admits a class (c) source or a
     load fallback whose interim tail is built from the exact tail's `BandNoiseGenerator`, seed and emitter stream
     (`tailSeedForOutput`), a test compares the interim IR with the final IR, both as shipped, from two serial builds of
     one scene and seed in one process (never from the async pipeline; never against a measured IR; a repeat build of
     each IR is asserted bit-identical before any comparison), per emitter, output and band on the A4 set (48 and
     96 kHz, 2 seeds, more only with a reason in the PR): 10·log10(E(interim − final)/E(final)) ≤ 20·log10(10^(B/20) − 1)
     dB, B the AX47 bound in force after the ABX (1 dB → −18.27 dB; 0.5 dB → −24.55 dB). Window: an interim that fades
     at the AX49 L_f uses AX47 (b)'s [t_mix,e, L_f − h), h AX47 (b)'s plus the backward reach of any per-mode filter in
     force; a full-length interim (the final's length L and per-band decay, differing only in per-band level) uses
     AX47's tail window [t_mix,e, L), since the two IRs share their end: h is subtracted only at an L_f edge, never at
     L. The window length is printed per case and band; an empty window prints 'not evaluated', and a case with zero
     matched tail energy (the AX22 ISM-only fallback; AX49 D1 early-only scenes) prints 'not evaluated (no tail)';
     neither ever counts as a pass; ≥ 1 evaluated case per band, output and fs (non-vacuity, not a quota). Negative
     control N1, asserted red per emitter, output and band: the interim built with tailSeed + 1 (neither of its
     `tailSeedForOutput` seeds equal to either of tailSeed's, asserted as a guard on the seed derivation); expected
     10·log10(1 + g²), +2.5 to +3.5 dB for an interim step g within ±1 dB (≈ +3.01 dB at g = 1; incoherent energies
     add, Vorländer §4.3 Eq. 4.15). In a two-output mode, N2 as phase-08-3 states it is added. The final IRs are those
     the AX47 tests already build; the test runs in the Release test job; the PR prints the added wall time per OS.
     **No shared prefix.** An admitted source whose interim does not share the exact tail's stream, length or per-band
     decay is outside this check, and instead: (1) a test asserts the fact that excludes it (its `tailSeedForOutput`
     seeds, its length or its per-band decay differ from the final's); (2) where its stream differs, its handover to
     the final is equal-power, AX18's law for unrelated tail noise (as a `tailSeed` change), recorded by AX47's
     measurement sentence, unless this phase's loop (Seat 5, AX18) sets another law together with an asserted bound on
     the mid-fade band level; (3) where its per-band decay differs, EDT within 5 % at 500 Hz and 1 kHz against the
     final on AX47 (b)'s terms (cases with d < 0.5; 'not evaluated (outside EDT domain …)' otherwise; ≥ 1 evaluated
     case at each); (4) AX47's level step ≤ B per emitter and band, asserted in the tail window and, for an interim
     that fades at L_f, in the common window t_mix,e…L_f. The PR names the source and gives these results.
```
**Acceptance: new criterion at the end:**
```
- [ ] **Interim stream check (D1, FM-D1-S3):** every admitted interim source that shares the exact tail's stream
      passes scope 9's interim stream check per emitter, output and band (repeat builds bit-identical, N1 red, ≥ 1
      evaluated case per band, output and fs, zero-tail cases 'not evaluated (no tail)'); every admitted source with
      no shared prefix has scope 9's asserted exclusion fact, handover law (equal-power, or the loop's law with its
      asserted mid-fade bound), EDT check where its decay differs, and level step in both windows; or the PR states
      that no such source was admitted. The added wall time per OS is printed.
```

## 3. phase-08-3 acceptance (after "Interim tail per mode (AX48, AX49)")
```
- [ ] **Interim tail stream per ear (AX47 (b) prefix check; D1, FM-D1-S3):** on the A4 set (48 and 96 kHz, 2 seeds,
      more only with a reason in the PR), per emitter, ear and band, the binaural provisional IR against the exact IR,
      both as shipped (after the 2×2 coherence mix and the per-ear diffuse-field HRTF magnitude and any DF-EQ), from two
      serial builder calls of one scene and seed in one process (never from the async pipeline; never against a
      measured IR; a repeat build of each IR, N1 and N2 included, asserted bit-identical before any comparison):
      10·log10(E(provisional − exact)/E(exact)) ≤ 20·log10(10^(B/20) − 1) dB, B the AX47 bound in force
      (1 dB → −18.27 dB; 0.5 dB → −24.55 dB), over [t_mix,e, L_f − h), L_f the AX49 fade start (the same in every
      mode), h the backward reach in samples at each fs of every filter between the noise and the shipped IR (the
      generator's band filters; any band split used by the coherence mix; the per-ear DF-HRTF magnitude and DF-EQ
      filters, half-length if linear-phase with latency compensated, 0 if causal) plus the analysis filterbank's. The
      window length is printed per case and band; an empty window, L_p ≥ L (no provisional) or zero matched tail
      energy (AX49 D1) prints 'not evaluated' with its reason and never counts as a pass; ≥ 1 evaluated case per
      band, ear and fs (non-vacuity, not a quota). Negative controls, both asserted red: **N1**, the provisional built
      with tailSeed + 1 (neither of its `tailSeedForOutput` seeds equal to either of tailSeed's, asserted as a guard on
      the seed derivation), per emitter, ear and band, expected ≈ +3.01 dB whatever γ_b (Vorländer §4.3 Eq. 4.15);
      **N2**, the provisional built with the two `tailSeedForOutput` seeds swapped, asserted on the two-ear aggregate
      per emitter and band, 10·log10((E_L,diff + E_R,diff)/(E_L + E_R)), expected ≈ +3.01 dB at equal ear energies,
      with each ear's value printed beside its unit-gain closed form, L 10·log10(2(1 − √(1 − γ_b²))),
      R 10·log10(2(1 + √(1 − γ_b²))), and the per-band ear energy ratio printed (L alone is not asserted: it is green
      where |γ_b| ≤ 0.122). Direct assertion: the provisional and exact builder paths take the mix coefficients
      (a_b, b_b) and the per-ear filter coefficients from one shared function or cache, and the test asserts them
      bit-identical within one process (never across OSes). The exact IRs are those already built for the AX47 (b) and
      mid-fade fixtures (one build per scene, fs and seed); the test runs in the Release test job; the PR prints the
      added wall time per OS. (Maisara 2026-11-13; phase-07c-1b decider files 16, 19; Seats 4, 5, 3 files 15, 17, 18)
```

## 4. phase-09 acceptance (after the "E_b bit-identical between stereoSpeakers, omni and binaural" line)
```
- [ ] **Interim tail stream per speaker feed (AX47 (b) prefix check; D1, FM-D1-S3):** as phase-08-3's criterion, for the
      stereoSpeakers provisional against the exact IR, per emitter, feed (L, R) and band, both as shipped (after the 2×2
      mix to the ORTF diffuse-field coherence and any per-feed filter); h the backward reach of the generator's band
      filters, any band split used by the coherence mix and any per-feed filter, plus the analysis filterbank's; the
      same bound with B, window [t_mix,e, L_f − h), 'not evaluated' rule (empty window, L_p ≥ L, zero matched tail
      energy) and non-vacuity per band, feed and fs; IRs from serial builder calls in one process, repeat builds
      asserted bit-identical first; N1 (tailSeed + 1) asserted red per feed and band; N2 (seeds swapped) asserted red
      on the two-feed aggregate, each feed's value printed beside its closed form with γ_b the scope 3 ORTF target; mix
      and per-feed filter coefficients from one shared function or cache, asserted bit-identical within one process
      (never across OSes); 2 seeds (more only with a reason in the PR); exact IRs reused from the AX47 (b) and
      mid-fade fixtures; Release test job; the PR prints the added wall time per OS. (Maisara 2026-11-13; phase-07c-1b
      decider files 16, 19; Seats 4, 5, 3 files 15, 17, 18)
```

## 5. AX47
**(b) evidence column, append after "…interrogator files 22, 34, 36, 38, 40.":**
```
FM-D1-S3 (Maisara 2026-11-13, "Write the stream checks now", option (i)): the prefix check extended as interim stream
checks to phase-07c-2 (scope 9, conditional; full-length interims over [t_mix,e, L), h only at an L_f edge; zero-tail
cases 'not evaluated (no tail)'; a source with no shared prefix carries an asserted exclusion fact, AX18's equal-power
handover for a different stream or a loop-set law with an asserted mid-fade bound, EDT within 5 % on this row's terms
where its decay differs, and the level step in both windows), phase-08-3 and phase-09 (acceptance; N1 tailSeed + 1 per
output, N2 swapped seeds on the two-output aggregate, mix and filter coefficients from one shared source, bit-identical
within one process); IRs from serial builder calls with repeat-build bit-identity, 2 seeds, Release job, wall time
printed; bound 20·log10(10^(B/20) − 1) with B the bound in force; phase-07c-1b loop, `docs/review/phase-07c-1b/` decider
files 16, 19, Seats 4, 5, 3 files 15, 17, 18; phase-07c-1 decider file 39, interrogator file 40 corrections 80, 86, 88,
90–93; Vorländer §4.3 Eq. 4.15.
```
**AX47 (b) text addition (unchanged from file 16):** in the acceptance clause, after "(… −1 dB gives −19.27 dB)", add
`; −24.55 dB (= 20·log10(10^(0.5/20) − 1)) once the reversal sets the bound to 0.5 dB`

## 6. BUILD_PLAN §6 row
```
| 2026-11-13 | **Phase 07c-1b, FM-D1-S3 answered by Maisara** ("Write the stream checks now", option (i)): the AX47 (b) prefix check is written as an interim stream check into phase-07c-2 (scope 9 bullet + acceptance; applies only to an admitted class (c) / load-fallback interim on the exact tail's stream; window [t_mix,e, L_f − h) with an AX49 fade, [t_mix,e, L) for a full-length interim, h only at an L_f edge; zero-tail cases 'not evaluated (no tail)'; N1 tailSeed + 1; a source with no shared prefix carries an asserted exclusion fact, AX18's equal-power handover for a different stream or a loop-set law with an asserted mid-fade bound, EDT within 5 % on AX47 (b)'s terms where its decay differs, and AX47's level step in both windows), phase-08-3 and phase-09 (acceptance; per output and band on the shipped IR after the coherence mix and per-mode filters, h including them; N1 tailSeed + 1 per output, N2 swapped seeds asserted on the two-output aggregate with per-output closed forms printed; mix and filter coefficients from one shared function or cache, bit-identical within one process; 'not evaluated' for an empty window, L_p ≥ L or zero tail; ≥ 1 evaluated case per band, output and fs). All three: IRs from serial builder calls in one process, repeat builds asserted bit-identical first; 2 seeds; exact IRs reused from existing fixtures; Release test job; added wall time printed per OS. Bound 20·log10(10^(B/20) − 1) dB, B the AX47 bound in force (−18.27 dB at 1 dB, −24.55 dB at 0.5 dB); AX47 (b) states the 0.5 dB value. Thresholds unchanged; no golden changed. Interrogator file 40 corrections 80, 86, 88, 90–93 applied; Seats 4 (0/1), 5 (1/1, C1–C4), 3 (0/1, C1–C3) heard; D1 O8 stands (max 1, sum 12). | /fix-plan (plan-editor); phase-07c-1b decider files 16, 19, Seats 4, 5, 3 files 15, 17, 18, interrogator file 20; phase-07c-1 decider file 39, interrogator file 40; session brief 2026-11-13-phase-07c-1b; corpus c1b171f |
```

## 7. Future-debt register (changed rows)
| seat | commits later phases to | undo cost | evidence arrives | repaid when |
|---|---|---|---|---|
| S3 | 07c-2 (if it admits a stream-sharing class (c) / load-fallback interim) tests the interim's stream at bound B, N1 red, zero-tail cases not counted; a no-prefix source carries the asserted exclusion, the handover law (equal-power or an asserted mid-fade bound), EDT within 5 % where decay differs, the level step in both windows; 08-3 and 09 test the shipped IR per output | drop AX47 (b)'s prefix clause, the prefix block and the three FM-D1-S3 lines via /fix-plan | 07c-2 CI and L4/L1 listening; 08-3, 09 CI on three OSes | 07c-2's check green with N1 red, or each admitted no-prefix source's four items green, or the PR states no source was admitted; 08-3 and 09 green with N1 red per output and N2 red on the aggregate |
| S4 | 08-3 / 09 carry N1, N2, the per-mode h and the coefficient bit-identity assertion; B follows 07c-2's ABX | drop the lines via /fix-plan | 08-3, 09 CI; 07c-2's ABX (B → 0.5 dB); phase-09 scope 3's documented ORTF formula (γ_b in N2's printed closed form) | the 08-3 and 09 PRs green with both controls red and non-vacuity met at every band, output and fs |
| S5 (changed) | 07c-2: one test or one asserted exclusion; 08-3 / 09: a handful of offline tests (≈ 16 IR builds per scene per mode; no convolution) from serial builder calls with repeat-build bit-identity; coefficients from one shared source; 2 seeds; fixtures reused; Release job; wall time printed | drop the lines via /fix-plan | 07c-2's class (c) / load-fallback decision; 08-3, 09 CI wall time per OS | the three PRs print wall time with no flake; overrun fixed by sharing fixtures, never by cutting seeds; 1 seed only with C1 met and a stated reason |
Rows S1, S2, S7, S9: file 37's, unchanged (S1, S9 incl. file 39's BRAS-only clause).

## 8. Ledger edits
- New phase-07c-1b row: `| FM-D1-S3 | interim stream checks for 07c-2 / 08-3 / 09 | answered by Maisara 2026-11-13 ("Write the stream
  checks now") = option (i); lines written with file 40 corrections 80, 86, 88, 90–93, Seat 4's conditions (file 15; corrected (i) 0/1,
  drafted (i) 1/2 out), Seat 5's C1–C4 (file 17, 1/1) and Seat 3's C1–C3 (file 18, 0/1); 07c-2 window for full-length interims
  [t_mix,e, L) from AX47's tail window, h only at L_f; D1 O8 stands, max 1, sum 12 — [interrogator outcome] | phase-07c-2 scope 9 / AC;
  phase-08-3 AC; phase-09 AC; AX47 (b) text + evidence; §6 |`
- Rows P07C1-G3-80 … 98, last column → "answered by Maisara 2026-11-13 (option (i)); applied in phase-07c-1b (row FM-D1-S3)".
- "NEEDS MAISARA: FM-D1-S3 only (carried from phase-07c-1, still unanswered)." → "NEEDS MAISARA: none (FM-D1-S3 answered by Maisara
  2026-11-13, option (i))".
- Round files list: add "15 (Seat 4 on FM-D1-S3), 16 (decider: FM-D1-S3 lines), 17 (Seat 5 on the lines), 18 (Seat 3 on the 07c-2
  window), 19 (decider: FM-D1-S3 final lines)".
- BUILD_PLAN §0 row 07c-1b notes: "FM-D1-S3 (NEEDS MAISARA)" → "FM-D1-S3 (answered by Maisara 2026-11-13, option (i); lines written)".

## 9. Load-bearing claims
- S3-L1 … S3-L6 as file 16 (bound −18.27 / −24.55 dB, −19.27 dB for a −B step; N1 10·log10(1 + g²), Vorländer §4.3 Eq. 4.14–4.15;
  N2 closed forms and ear-imbalance behaviour (red below a 24.3 dB per-band imbalance); product basis NFR preamble l. 101, NFR-1,
  CLAUDE.md "Every DSP behaviour must have an automated check"; the full-length window from AX47's "tail window (t_mix,e to the
  end)").
- **S3-L7 zero tail (Seat 3 C1; AX22, AX49 D1):** with zero matched tail energy E(final) over the window is 0, the ratio undefined,
  E(interim − final) = 0 would pass trivially and N1 cannot go red — 'not evaluated (no tail)' is needed; carried into 08-3 and 09 for
  the same reason (a consistency step, not a Seat 4 condition).
- **S3-L8 fade law (AX18):** "A `tailSeed` or fs change gives unrelated tail noise and is joined equal-power"; equal-gain mid-fade band
  power (1+ρ)/2 (Vorländer §4.3 Eq. 4.15 cross term) = 0.5 at ρ = 0, −3.01 dB (Seat 3's dip); clause (2) applies AX18's existing law
  to a different-stream interim, changes neither AX18 nor AQ4; any other law set in 07c-2's loop with Seat 5.
- **S3-L9 EDT (AX47 (b)):** EDT within 5 % at 500 Hz and 1 kHz, the d < 0.5 domain and non-vacuity are AX47 (b)'s existing terms; no
  new threshold.
- **S5 facts (file 17, code):** the provisional exists only on the builder path; offline skips it (AX49, L171), so serial builder
  calls are the only deterministic source; the N1 seed assertion cannot fail under `seed ^ (k·0x9E3779B9)` — kept as a guard;
  bit-identity across two independent coefficient computations is fragile (FMA, inlining) [Inferred], hence C2.
- Not load-bearing: Seat 3's convex-combination claim for analysis-band leakage [Inferred] (holds only if cross-band terms are
  non-negative); the lines inherit AX47 (b)'s per-band comparison, which already survived interrogation.

## 10. Strongest objection
S5's cell on Seat 3's C3(1) (Seat 5 rated before the fade-law clause existed): holds because the clause only applies AX18's existing
sentence for unrelated tail noise and defers any other law, with its asserted mid-fade bound, to 07c-2's loop (convening Seat 5); fails
if the interrogator reads "an asserted bound on the mid-fade band level" as a new number — then re-hear Seat 5 on clause (2) alone.
Second: a no-prefix interim differing in matching at t_mix,e is caught only by the level step and EDT items (a Seat 3 debt, now tested
rather than stated). Third: in 09, N2's L term may be red at low frequencies (ORTF γ ≈ 0.66 [Hyp]) — printed only.

## 11. Confidence and reversal
High (08-3, 09); medium (07c-2: S5 cell partly from conditions; window wording the decider's, Seat 3 rates it right). Reversal: 07c-2
admits a source neither a per-band gain of the final nor caught by the four no-prefix items (revise in that loop); 07c-2's ABX sets B =
0.5 dB (all three follow); 08-3 CI shows N2 green on the aggregate (a filter defect, never a reason to loosen); excessive wall time
(share fixtures, never cut seeds).

## 12. Summary / Decided for Maisara
| id | decision | state | worst-off | sum | conf. | PRD bound | corpus | reversal |
|---|---|---|---|---|---|---|---|---|
| FM-D1-S3 (i), final lines | §2–§5 | proposed (her answer; wording for the interrogator) | 1 (S1, S2, S5, S7, S9 1/1; S3, S4 0/1) | 12 | high (08-3, 09) / medium (07c-2) | NFR preamble l. 101, NFR-1 | Vorländer §4.3 Eq. 4.14–4.15 | non-gain 07c-2 source; B → 0.5 dB; N2 green in 08-3; wall time |

- FM-D1-S3: her own answer (i), written out with Seat 4's 2×2-mix-safe controls, Seat 5's determinism and CI-cost conditions, Seat 3's
  exits for interims that do not share the stream; NFR preamble, NFR-1; Seat 5 gives most (a few offline Release tests in 07c-2, 08-3,
  09), gets tests that cannot flake and a printed cost; amends none of her decisions.
- 07c-2 window and no-prefix branch: [t_mix,e, L) from AX47's tail window; a no-prefix source exits to existing tests (AX18's
  equal-power law, AX47 (b)'s EDT terms, AX47's level step); plan wording under her answer; amends nothing.
NEEDS MAISARA: none.
