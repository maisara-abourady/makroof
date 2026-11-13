# 16 — Decider: FM-D1-S3 final plan lines for Maisara's option (i)

2026-11-13, corpus c1b171f. Saved by the orchestrator from the decider's report. Maisara answered herself on 2026-11-13: "Write
the stream checks now" (brief, line 12) = option (i); this round only writes the lines: file 39's draft with interrogator file 40's
corrections 80, 86, 88, 90, 91, 92, 93 and Seat 4's conditions (file 15). No CONVENE / RESEARCH: the 07c-2 window (correction 91)
is written from AX47 ("the tail window (t_mix,e to the end)") and AX49 (only the AX49 interim fades, at L_f) — test wording, not a
new number; it meets Seat 3's debt-row condition ("test any admitted interim source that shares the stream, or say why it has no
prefix"); Seats 3 and 5 may contest it at interrogation. PRD bound (correction 80): NFR preamble (l. 101) "Accuracy is the top
priority", NFR-1.

## 1. Tension map (what changed)
| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| (i) as drafted (file 39) | 1/1 | 1/1 | 0/1 | **1/2** | 1/1 | 0/0 | 1/1 | 0/0 | 1/1 | 2 | 14 |
| (i) corrected (these lines) | 1/1 | 1/1 | 0/1 | **0/1** | 1/1 | 0/0 | 1/1 | 0/0 | 1/1 | **1** | **12** |

S4 cells are Seat 4's own (file 15): drafted now 1 / later 2 ("fails by construction at high frequencies in 08-3, and in 09 as
spacing lowers coherence; an unplanned rewrite in 08-3 and silent weakening"); corrected 0/1 ("two small tests on a path the phases
already build"; "commits 08-3 and 09 to a few tests"). Others are file 37's O8 row, unchanged. D1 (O8) stands: worst cell 1; sum 11 →
12 because Seat 4 is now convened (observation 98 fixed). The drafted (i) is out on the worst-off seat.

## 2. phase-07c-2
**Scope 9: new bullet after "The load fallback"** (covers both class (c) and the load fallback):
```
   - **Interim stream check (D1, FM-D1-S3; Maisara 2026-11-13).** If this phase's loop admits a class (c) source or a
     load fallback whose interim tail is built from the exact tail's `BandNoiseGenerator`, seed and emitter stream
     (`tailSeedForOutput`), a test compares the interim IR with the final IR, both as shipped, from two renders of one
     scene and seed (never against a measured IR), per emitter, output and band on the A4 set (48 and 96 kHz,
     ≥ 2 seeds): 10·log10(E(interim − final)/E(final)) ≤ 20·log10(10^(B/20) − 1) dB, B the AX47 bound in force after
     the ABX (1 dB → −18.27 dB; 0.5 dB → −24.55 dB). Window: an interim that fades at the AX49 L_f uses AX47 (b)'s
     [t_mix,e, L_f − h); a full-length interim (the final's length L and per-band decay, differing only in per-band
     level) uses AX47's tail window [t_mix,e, L), since the two IRs share their end; h as in AX47 (b), plus the
     backward reach of any per-mode filter in force. The window length is printed per case and band; an empty window
     prints 'not evaluated' and never counts as a pass; ≥ 1 evaluated case per band, output and fs (non-vacuity, not a
     quota). Negative control N1, asserted red per emitter, output and band: the interim built with tailSeed + 1
     (neither of its `tailSeedForOutput` seeds equal to either of tailSeed's, asserted); expected 10·log10(1 + g²),
     +2.5 to +3.5 dB for an interim step g within ±1 dB (≈ +3.01 dB at g = 1; incoherent energies add, Vorländer §4.3
     Eq. 4.15). In a two-output mode, N2 as phase-08-3 states it is added. An admitted source whose interim does not
     share the exact tail's stream, length or per-band decay has no shared prefix: the PR states so, with the reason,
     and this check does not apply.
```
**Acceptance: new criterion at the end:**
```
- [ ] **Interim stream check (D1, FM-D1-S3):** every admitted interim source that shares the exact tail's stream
      passes scope 9's interim stream check per emitter, output and band, with its negative control red and
      ≥ 1 evaluated case per band, output and fs; otherwise the PR states, with the reason, why the source has no
      shared prefix, or that no such source was admitted.
```

## 3. phase-08-3 acceptance (after "Interim tail per mode (AX48, AX49)")
```
- [ ] **Interim tail stream per ear (AX47 (b) prefix check; D1, FM-D1-S3):** on the A4 set (48 and 96 kHz, ≥ 2 seeds),
      per emitter, ear and band, the binaural provisional IR against the exact IR, both as shipped (after the 2×2
      coherence mix and the per-ear diffuse-field HRTF magnitude and any DF-EQ), from two renders of one scene and seed
      (never against a measured IR): 10·log10(E(provisional − exact)/E(exact)) ≤ 20·log10(10^(B/20) − 1) dB, B the AX47
      bound in force (1 dB → −18.27 dB; 0.5 dB → −24.55 dB), over [t_mix,e, L_f − h), L_f the AX49 fade start (the same
      in every mode), h the backward reach in samples at each fs of every filter between the noise and the shipped IR
      (the generator's band filters; any band split used by the coherence mix; the per-ear DF-HRTF magnitude and DF-EQ
      filters, half-length if linear-phase with latency compensated, 0 if causal) plus the analysis filterbank's. The
      window length is printed per case and band; an empty window, or L_p ≥ L (no provisional), prints 'not evaluated'
      and never counts as a pass; ≥ 1 evaluated case per band, ear and fs (non-vacuity, not a quota). Negative controls,
      both asserted red: **N1**, the provisional built with tailSeed + 1 (neither of its `tailSeedForOutput` seeds equal
      to either of tailSeed's, asserted), per emitter, ear and band, expected ≈ +3.01 dB whatever γ_b (Vorländer §4.3
      Eq. 4.15); **N2**, the provisional built with the two `tailSeedForOutput` seeds swapped, asserted on the two-ear
      aggregate per emitter and band, 10·log10((E_L,diff + E_R,diff)/(E_L + E_R)), expected ≈ +3.01 dB at equal ear
      energies, with each ear's value printed beside its unit-gain closed form, L 10·log10(2(1 − √(1 − γ_b²))),
      R 10·log10(2(1 + √(1 − γ_b²))), and the per-band ear energy ratio printed (L alone is not asserted: it is green
      where |γ_b| ≤ 0.122). Direct assertion: the mix coefficients (a_b, b_b) and the per-ear filter coefficients are
      bit-identical between the provisional and exact builder paths. (Maisara 2026-11-13; phase-07c-1b decider file 16,
      Seat 4 file 15)
```

## 4. phase-09 acceptance (after the "E_b bit-identical between stereoSpeakers, omni and binaural" line)
```
- [ ] **Interim tail stream per speaker feed (AX47 (b) prefix check; D1, FM-D1-S3):** as phase-08-3's criterion, for the
      stereoSpeakers provisional against the exact IR, per emitter, feed (L, R) and band, both as shipped (after the 2×2
      mix to the ORTF diffuse-field coherence and any per-feed filter); h the backward reach of the generator's band
      filters, any band split used by the coherence mix and any per-feed filter, plus the analysis filterbank's; the
      same bound with B, window [t_mix,e, L_f − h), 'not evaluated' rule and non-vacuity per band, feed and fs; N1
      (tailSeed + 1) asserted red per feed and band; N2 (seeds swapped) asserted red on the two-feed aggregate, each
      feed's value printed beside its closed form with γ_b the scope 3 ORTF target; mix and per-feed filter coefficients
      bit-identical between the provisional and exact builder paths. (Maisara 2026-11-13; phase-07c-1b decider file 16,
      Seat 4 file 15)
```

## 5. AX47
**(b) evidence column, append after "…interrogator files 22, 34, 36, 38, 40.":**
```
FM-D1-S3 (Maisara 2026-11-13, "Write the stream checks now", option (i)): the prefix check extended as interim stream
checks to phase-07c-2 (scope 9, conditional; full-length interims over [t_mix,e, L)), phase-08-3 and phase-09
(acceptance; N1 tailSeed + 1 per output, N2 swapped seeds on the two-output aggregate, mix and filter coefficients
bit-identical), bound 20·log10(10^(B/20) − 1) with B the bound in force; phase-07c-1b loop, `docs/review/phase-07c-1b/`
decider file 16, Seat 4 file 15; phase-07c-1 decider file 39, interrogator file 40 corrections 80, 86, 88, 90–93;
Vorländer §4.3 Eq. 4.15.
```
**AX47 (b) text (correction 90 carried through, recommended):** in the acceptance clause, after "(… −1 dB gives −19.27 dB)", add
`; −24.55 dB (= 20·log10(10^(0.5/20) − 1)) once the reversal sets the bound to 0.5 dB` — otherwise AX47 (b) keeps −18.27 dB fixed
while the three new lines follow B (INCONSISTENT risk).

## 6. BUILD_PLAN §6 row
```
| 2026-11-13 | **Phase 07c-1b, FM-D1-S3 answered by Maisara** ("Write the stream checks now", option (i)): the AX47 (b) prefix check is written as an interim stream check into phase-07c-2 (scope 9 bullet + acceptance; applies only to an admitted class (c) / load-fallback interim on the exact tail's stream; window [t_mix,e, L_f − h) with an AX49 fade, [t_mix,e, L) for a full-length interim; N1 negative control tailSeed + 1), phase-08-3 and phase-09 (acceptance; per output and band on the shipped IR after the coherence mix and per-mode filters, h including them; N1 tailSeed + 1 per output, N2 swapped seeds asserted on the two-output aggregate with per-output closed forms printed; mix and filter coefficients bit-identical between provisional and exact paths; 'not evaluated' for an empty window or L_p ≥ L, ≥ 1 evaluated case per band, output and fs). Bound 20·log10(10^(B/20) − 1) dB, B the AX47 bound in force (−18.27 dB at 1 dB, −24.55 dB at 0.5 dB); AX47 (b) states the 0.5 dB value. Thresholds unchanged; no golden changed. Interrogator file 40 corrections 80, 86, 88, 90–93 applied; Seat 4 convened (0/1); D1 O8 stands (max 1, sum 12). | /fix-plan (plan-editor); phase-07c-1b decider file 16, Seat 4 file 15, interrogator file <next>; phase-07c-1 decider file 39, interrogator file 40; session brief 2026-11-13-phase-07c-1b; corpus c1b171f |
```

## 7. Future-debt register (changed rows)
| seat | commits later phases to | undo cost | evidence arrives | repaid when |
|---|---|---|---|---|
| S3 | 07c-2 (if it admits a stream-sharing class (c) / load-fallback interim), 08-3 and 09 test the interim's stream on the shipped IR at bound B, negative controls red | drop AX47 (b)'s prefix clause, the prefix block and the three FM-D1-S3 lines via /fix-plan | 07c-2, 08-3, 09 CI on three OSes | 07c-2's line green with N1 red, or its PR states why no admitted source has a shared prefix; 08-3's and 09's lines each green with N1 red per output and N2 red on the aggregate, ≥ 1 evaluated case per band, output and fs |
| S4 (new) | 08-3 / 09 carry N1, N2, the per-mode h and the coefficient bit-identity assertion; B follows 07c-2's ABX | drop the lines via /fix-plan | 08-3, 09 CI; 07c-2's ABX (B → 0.5 dB); phase-09 scope 3's documented ORTF formula (γ_b in N2's printed closed form) | the 08-3 and 09 PRs green with both controls red and non-vacuity met at every band, output and fs |
Rows S1, S2, S5, S7, S9: file 37's, unchanged (S1, S9 incl. file 39's BRAS-only clause).

## 8. Ledger edits
New phase-07c-1b row: `| FM-D1-S3 | interim stream checks for 07c-2 / 08-3 / 09 | answered by Maisara 2026-11-13 ("Write the stream
checks now") = option (i); lines written with file 40 corrections 80, 86, 88, 90–93 and Seat 4's conditions (file 15, corrected (i)
0/1; drafted (i) 1/2 out); 07c-2 window for full-length interims [t_mix,e, L) from AX47's tail window; D1 O8 stands, max 1, sum 12 —
[interrogator outcome] | phase-07c-2 scope 9 / AC; phase-08-3 AC; phase-09 AC; AX47 (b) text + evidence; §6 |`. Row P07C1-G3-80 …
98 last column → "answered by Maisara 2026-11-13 (option (i)); applied in phase-07c-1b (row FM-D1-S3)". "NEEDS MAISARA: FM-D1-S3 only
(carried from phase-07c-1, still unanswered)." → "NEEDS MAISARA: none (FM-D1-S3 answered by Maisara 2026-11-13, option (i))". Round
files list: add "15 (Seat 4 on FM-D1-S3), 16 (decider: FM-D1-S3 final lines)". BUILD_PLAN §0 row 07c-1b notes: "FM-D1-S3 (NEEDS
MAISARA)" → "FM-D1-S3 (answered by Maisara 2026-11-13, option (i); lines written)".

## 9. Load-bearing claims
- **S3-L1 (bound):** 20·log10(10^(B/20) − 1): B 1 dB → 0.12202 → −18.27 dB; B 0.5 dB → 0.05925 → −24.55 dB; a −B step gives
  20·log10(1 − 10^(−B/20)) = −19.27 dB at 1 dB, so +B is the looser side and the right bound (file 40 row 85).
- **S3-L2 (N1):** each output's stream independent of the exact tail's; the cross term averages out, energies add (Vorländer §4.3
  Eq. 4.14–4.15: "integration over frequency kills the cross term"); E(g·n′ − n)/E(n) = g² + 1 → 10·log10(1 + g²); g = 10^(±1/20):
  +2.54 / +3.54 dB; through the mix a²(g₁² + 1) + b²(g₂² + 1) in the same range (a² + b² = 1); margin to −18.27 dB ≥ 20.8 dB (file
  40 row 87).
- **S3-L3 (N2 closed forms):** swapping gives L′ − L = (b − a)(n1 − n2), R′ − R = (a + b)(n2 − n1); energies 2(1 − 2ab) and 2(1 +
  2ab), 2ab = √(1 − γ²) (a² − b² = γ); sum 4 over a total 2 → aggregate +3.01 dB whatever γ_b; L alone ≤ −18.27 dB where |γ_b| ≤
  0.122 (agrees with file 40 row 88 and Seat 4).
- **S3-L4 (N2 under ear imbalance):** w = E_R/(E_L + E_R); aggregate 2(1 − s + 2ws), s = √(1 − γ²); minimum at s = 1: 4w; red while
  4w > 10^(−1.827) = 0.0149, i.e. per-band ear imbalance below 24.3 dB — hence the printed ear energy ratio; the phase's Energy and
  E_b-parity criteria hold the ears far inside this.
- **S3-L5 (product):** each line tests a sentence the phases already contain (08-3 scope l. 38–42, AC l. 72–73; 09 scope l. 39–40;
  file 40 row 81); rests on the NFR preamble (l. 101), NFR-1 (correction 80), CLAUDE.md "Every DSP behaviour must have an automated
  check".
- **S3-L6 (07c-2 window):** AX47's level window is "t_mix,e to the end"; a full-length interim differing only in per-band level has
  the same L and envelopes, so interim − final is a per-band (g − 1) copy of the tail with no edge of its own (no h at L); only an
  AX49-faded interim has an L_f edge (keeps AX47 (b)'s window); any interim whose length or decay differs falls under the "no shared
  prefix" branch.
- Code facts (Seat 4, file 15): n1 = `tailSeedForOutput(seed, 0)`, n2 = `(seed, 1)` on one PCG stream per emitter; the 2×2 mix
  phase-08-3 scope 5 l. 29–31.

## 10. Strongest objection
Seats 3 and 5 on the 07c-2 window (correction 91 handed to them, not re-heard). Holds because the window is AX47's own tail-window
definition, not a new threshold; the line is conditional and 07c-2's loop convenes both seats for the class (c) / load-fallback
decision anyway; the "no shared prefix" branch covers any source the window does not fit. Fails if 07c-2 admits a full-length
interim differing from the final by more than a per-band gain (e.g. different matching at t_mix,e): the line routes it to the PR
statement and the check is silent for it (a Seat 3 debt). If UNDERCONVENED: brief Seats 3, 5 to rate the 07c-2 scope 9 bullet
now / later with conditions. Second risk: in 09, N2's L term may be red at low frequencies (Seat 4's ORTF coherence ≈ 0.66 [Hyp]) —
printed only, not load-bearing.

## 11. Confidence and reversal
High for the 08-3 and 09 lines; medium for the 07c-2 window (own wording, Seats 3, 5 not re-heard). Reversal: 07c-2 admits a source
whose interim is not a per-band gain of the final (the window line revised in that loop); 07c-2's ABX sets B = 0.5 dB (all three lines
follow); 08-3 CI shows N2 green on the aggregate (an ear imbalance > 24 dB is a filter defect, never a reason to loosen the control).

## 12. Summary and Decided for Maisara
| id | decision | state | worst-off | sum | conf. | PRD bound | corpus | reversal |
|---|---|---|---|---|---|---|---|---|
| FM-D1-S3 (i), corrected | lines §2–§5 | proposed (her answer; wording for the interrogator) | 1 (S1, S2, S5, S7, S9 file 37; S3 0/1; S4 0/1) | 12 | high / medium (07c-2 window) | NFR preamble l. 101, NFR-1 | Vorländer §4.3 Eq. 4.14–4.15; S3-L3, L4 | 07c-2 non-gain source; B → 0.5 dB; N2 green in 08-3 |

- FM-D1-S3: her own answer (i); the board only wrote it out, with the 2×2-mix-safe controls Seat 4 asked for (NFR preamble, NFR-1);
  Seats 4, 5 carry the N1, N2 and coefficient tests in 08-3 and 09; Seat 3's stream risk goes under CI; amends none of her decisions.
- 07c-2 window reading for full-length interims: [t_mix,e, L) from AX47's tail window — plan wording under her answer; amends
  nothing.
NEEDS MAISARA: none.
