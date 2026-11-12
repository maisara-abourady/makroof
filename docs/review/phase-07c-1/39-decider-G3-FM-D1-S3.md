# 39 — Decider: G3 / D1 after three rounds: FOR MAISARA ruling FM-D1-S3, final texts

2026-11-12, corpus c1b171f. D1 stays O8 (max 1, sum 11). The contested Seat 3 debt is ruled FOR MAISARA from the PRD.

**FM-D1-S3 — answer (i): write the plan lines now.** Rests on NFR-1 ("Accuracy is the top priority"); phase-08-3 scope
l. 38–40 and phase-09 scope l. 39 already require the provisional to use "the same `tailSeedForOutput` seeds … as the exact
tail" but have no test of it; AX18 (as quoted in phase-09 l. 36–37: equal-gain crossfade dips ≈ 3 dB mid-fade on
uncorrelated outputs); AX47 (b) as amended; CLAUDE.md "every DSP behaviour must have an automated check" (plan rule). The
level steps cannot see a stream mismatch (K10); the prefix check does (+3.0 dB vs −18.27 dB). Options: (i) keeps O8 at max
1, sum 11; (ii) leaves the debt unrepaid, Seat 3 0/2 → O8 max 2 sum 12, O7 (max 2, sum 10) wins and the prefix check is
dropped — less NFR-1 evidence; (iii) a follow-up note — the silent borrowing CLAUDE.md forbids (row 68). Strongest veto
reading: a 07c-1 decision commits 07c-2, 08-3, 09 — answered: each line tests a sentence those phases already contain.
Amends none of her decisions.

S3 debt row (final): commits 08-3 / 09 to test the per-output provisional's stream (with a negative control) and 07c-2 to
test any admitted stream-sharing interim source or state why it has no prefix; undo: AX47 (b)'s prefix clause, the prefix
block, the three FM-D1-S3 lines; evidence: 07c-2, 08-3, 09 CI on three OSes; repaid when each line is green with its
negative control red. S1/S9: as file 37, plus item 7 runs on BRAS even if 05d ends blocked.

Plan lines written by FM-D1-S3:
- phase-07c-2 scope 9, after "Class (c) decision": "**Interim stream check (D1, FM-D1-S3).** If this phase's loop admits a
  class (c) source or a load fallback whose interim tail comes from the exact tail's generator stream, its interim IR keeps
  an AX47 (b)-style prefix check green against the final: E(interim − final)/E(final) ≤ 20·log10(10^(B/20) − 1) per emitter
  and band over [t_mix,e, L_f − h), with B the AX47 bound in force after the ABX (1 dB → −18.27 dB; 0.5 dB → −24.55 dB). A
  source with no shared prefix states so in the PR, with the reason."
- phase-07c-2 acceptance: "- [ ] Any admitted interim source sharing the exact tail's stream passes the scope 9 interim
  stream check, or the PR states why it has no prefix. (D1, FM-D1-S3)"
- phase-08-3 acceptance, after "Interim tail per mode (AX48, AX49)": "- [ ] **Interim tail stream (AX47 (b) prefix check;
  D1, FM-D1-S3):** for the binaural provisional against the exact tail, per output (left, right) and band, on the A4 set (48
  and 96 kHz, ≥ 2 seeds): E(provisional − exact)/E(exact) ≤ −18.27 dB over [t_mix,e, L_f − h). Negative control: built with
  the other output's `tailSeedForOutput` seed, it fails (expected ≈ +3 dB)."
- phase-09 acceptance, after the E_b line: the same for the stereoSpeakers provisional, outputs (L, R).
(0.5 dB: 10^(0.5/20) = 1.05925 → 20·log10(0.05925) = −24.55 dB.)

Phase-05d changes (rows 64, 65, 71): l.18 → "This phase has no open items except scope item 7's ruling on the AX47 (b) d
constant (D1, phase-07c-1 G3, 2026-11-12), which this session's decision loop settles."; header "Depends on: 05, 05e; 07c-1
for scope item 7 only (it reads AX47 (b) and may change `tests/unit/test_interim.cpp` through /fix-plan)"; AX47 in "Read
first"; scope item 7 final: as file 37 with d_dir's total "taken to the Phase 05 scope 3 truncation point, with the same
`metrics.lundeby` noise-energy compensation as that band's EDC (uncompensated noise would inflate the total and push d_dir
toward 'in domain')", "decider files 35, 37, 39", and "**If this phase ends blocked on data access**, item 7 still runs on the
BRAS nightly positions (already downloaded by checksum, no new download), and the ruling is made on BRAS alone, labelled
'BRAS only'. The status reads `blocked (reason); item 7 done on BRAS`."

Unchanged from file 37: AX47 (b) replacement, evidence append (+ "decider file 39; interrogator file 38; FM-D1-S3"), test
comment, map. §6 row: file 37's, extended by "; FM-D1-S3: interim stream checks written into phase-07c-2 (scope 9,
conditional), phase-08-3 and phase-09 (acceptance, with negative control); phase-05d l. 18 and its dependencies amended",
sources + "decider file 39, interrogator file 38".

Decided for Maisara (final): D1 (as file 37 §6) and FM-D1-S3 — later phases (07c-2 if it applies, 08-3, 09) gain a test
that the interim tail plays on the exact tail's noise stream, a requirement their plans already state but never tested;
rests on NFR-1, 08-3 l. 38–40, 09 l. 39, AX18; (i) checks the existing requirement and keeps O8, (ii) flips to O7 and loses
the check, (iii) borrows silently; who gave most: Seats 7 and 5 carry two small tests each in 08-3 and 09; Seat 3 gets its
stream risk under CI. Amends none of her decisions. NEEDS MAISARA: none.
