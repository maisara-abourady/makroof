# Interrogator on commit 98ebd12 (plan-editor applies decider files 17 and 21, as corrected by interrogator files 18 and 22)

**Verdict: faithful.** Nothing in this commit is WRONG or INCONSISTENT with the surviving decisions or their corrections. There is one trivial rounding nit. Two code items from file 22 are still open, but they sit outside this commit.

**Corpus revision:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**What I read:** I have no shell, so I checked the files' current state rather than the diff:
- the run sheet §8 (L332–471);
- BUILD_PLAN AX49 (L172), the new §6 row (L537), the §5 B11 entry (L404) and the §0 row 05b (L26);
- `docs/phases/phase-07d.md` L113–135;
- `docs/phases/phase-05e.md` scope (b), L143–151.

## Checks

- **D1, rule (a).**
  - Run sheet §8 L408–416 quotes file 17's wording verbatim: void, scored trials not unsealed, a pre-sealed second block, never "not detected", and "inconclusive (anchor failed twice)" with AX49's reversal left unread.
  - It adds the kit's scoring refusal and the build-and-seal of both blocks together.
- **D1 hours** (file 21, Seat 7's conditions in file 19). §8 L417–422 has all of them:
  - the worst case, counted as E's second sitting plus the primary block plus the rerun block;
  - the statement that the existing K6 covers only the AX47 chains;
  - the third-sitting decision taken before the seal and dated in the brief;
  - a rerun that would pass 2 h opens the next sitting.
- **P1.**
  - Detection wording "detected (≥ 12/16, family α 0.038)" appears at L407 and L437.
  - The power 0.63 matches the binomial.
  - "L4 is its own family, not in the AX47 union ≤ 0.098" appears at L339–340 and L443.
- **P8 items 1–4 and P8-3.**
  - §8 L448–458 lists the four triggers in file 17's wording: AX21 / t_mix,e, decay target, AX49 constants, and the IR-hash check on the same platform (AX5).
  - Seat 3's O5 manifest print of f, fade length, normalisation and L rule is present.
  - The rebuild requirements (assertions 1–13, tests 1–8, label check) and the "pre-change engine" marking match file 17.
- **P8-S.** §8 L464–471 quotes file 21 verbatim, with file 22's correction "Every 07d L4 session, including those after a detection, is dated before the Phase 08-4 freeze."
- **AX49 (L172).** "void rule and session rule: phase-07c-2b decider files 17 (P8) and 21 (P8-3, P8-S)" is present, as file 17's homes require.
- **§5 B11 (L404), §0 row 05b (L26) and phase-05e (b) L149–151.** Each now names the L4 stimuli under items 1–2. Items 3–4 and P8-S are pointed to run sheet §8, consistent with file 17's homes.
- **phase-07d L120–135.**
  - P8-S's ordering for 07d's own remedy, with the freeze-date correction.
  - Seat 3's O1, O2 and O4 as inputs to 07d's round, each with the seats it needs.
  - Seat 7's hand-off to Seat 1 (file 22's correction).
  - All match file 21 and its correction.
- **File 22, B3.**
  - L is now "**[measured at build]** (11.993 s at k = 0.84)" at L361.
  - The measured values at L350 match builder file 15: k 0.84, T60_max 7.9955 s, t_mix,e,max 0.08017 s, L_f 2.5748 s, L_p 2.6748 s.
- **§6 row (L537).** It accurately summarises the changes above, and its sources are complete: files 17, 21, 18, 22, 19, 20 and 15.

**Nit (IMPRECISE, trivial).** L407 writes "family α 0.038 = 2517/65536". The fraction is 0.0384, so "≈" belongs there, not "=".

**Still open, outside this commit:**
- B1: narrow test 2's `tests/unit/` exemption to the flag's own test files.
- B2: Seat 5 confirms test 3's C++ comparison against `buildRoomIR` as an equivalent of its condition.
- The L4 scene JSON and its SHA-256 are to be committed with the kit when `abx_kit.py` gains L4.

## Ledger
| id | kind | item | verdict | evidence | severity | status |
|---|---|---|---|---|---|---|
| 98-1 | DECISION | D1 rule (a) wording and kit refusal | faithful | file 17 D1; run sheet L408–416 | none | — |
| 98-2 | DECISION | D1 hours (worst case, third sitting) | faithful | file 21; 19-seat7 §6; run sheet L417–422 | none | — |
| 98-3 | NUMBER | "family α 0.038 = 2517/65536" | IMPRECISE (= should be ≈; 0.0384) | binomial | minor | open (nit) |
| 98-4 | DECISION | L4 not in the AX47 union | faithful | file 17 P1; run sheet L339–340, L443 | none | — |
| 98-5 | DECISION | P8 items 1–4 and O5 print; rebuild rules | faithful | files 17, 21; run sheet L448–462 | none | — |
| 98-6 | DECISION | P8-S with the freeze-date correction | faithful | file 21; file 22; run sheet L464–471; phase-07d L120–126 | none | — |
| 98-7 | DECISION | 07d inputs O1/O2/O4 and the Seat 7 → Seat 1 hand-off | faithful | file 21; file 22; phase-07d L127–135 | none | — |
| 98-8 | DECISION | AX49 pointer; B11 L404; §0 05b; 05e (b) name the L4 stimuli | faithful | file 17 homes | none | — |
| 98-9 | NUMBER | L 11.993 s; k 0.84 timing | CORRECT | builder file 15; 1.5 × 7.9955 = 11.993 | none | closed (file 22 B3) |
| 98-10 | SOFTWARE | test 2 allow-list (B1); test 3 form (B2); scene JSON with the kit | not in this commit | file 22 | — | open |
