# 22 — Interrogator (document mode): G3 / D1, the AX47 (b) EDT clause (phase 07c-1 session 2)

2026-11-12. Corpus audio-resources c1b171f. Input: file 21; BUILD_PLAN AX47, AX49; phase-07c-1 A4; test_interim.cpp.

**Bottom line:** no single option is correct. O1 CONDITIONS VIOLATED (Vorländer §6.4.4 Table 6.1, 5 % EDT jnd at
500–1000 Hz, test conditions not stated; Kuttruff §8.4: decay measurement needs r ≫ r_c, "else direct sound unduly shapes
the decay curve"; §7.6: EDT strongly influenced by early reflections). O2–O5 each admissible, each with a value the corpus
does not fix: **several valid / PRODUCT MATTER → decision loop.**

Arithmetic (Eq. 6.4): with eps the provisional's missing fraction, Δ(−10 dB) = 10 log(1 − 10 eps) − 10 log(1 − eps);
eps = 1.3e-4 → −0.0051 dB (EDT ≈ 0.05 %). By construction (K17′, eps ≤ 0.0134): reference −0.0586 dB (the "≤ 0.06 dB"
bound holds on the 0 dB reference) but −0.566 dB at −10 dB (≈ 4.9 % shorter EDT for a pure exponential). Step model with
Kuttruff Eq. 5.45: ±0.06 dB moves EDT > 5 % only when d > 0.868, i.e. r < 0.39 r_c.

Verdicts: O1 CONDITIONS VIOLATED (major). O2 valid; its 5 % conditioning threshold reuses a listener jnd as an estimator
criterion (IMPRECISE, minor); "±0.06 dB (the truncation bound above)" holds only as a bound on the reference, not on the
EDC change over 0 … −10 dB (CONDITIONS VIOLATED, major, as a justification); only two end points tested (IMPRECISE); the
"at least half evaluated" floor has no corpus basis (PRODUCT MATTER). O3 valid (Kuttruff §7.6 Atal 160 ms slope, §8.4
Eqs. 8.26–8.27), loses the Table 6.1 jnd. O4 valid as a scope choice, selected from results; the corpus criterion is a
prior r ≫ r_c. O5 valid, x not sourced. AX47 scope and reversal unaffected; AX49 "Acceptance" changes only under O4; a
§6 row is due under O2–O5. Process: ad8971c implements O2 before D1 is verified.

| id | kind | item | verdict | severity | status |
|---|---|---|---|---|---|
| P07C1-G3-01 | NUMBER | O1 on every A4 case | CONDITIONS VIOLATED | major | open |
| P07C1-G3-02 | FACT | the 7 failures are the estimator's, not the IR's | CORRECT (conditional on Q1) | none | open |
| P07C1-G3-03 | FACT | ill-conditioned bands are direct-dominated | NOT CHECKABLE | none | open |
| P07C1-G3-04 | NUMBER | O2 5 % conditioning threshold = Table 6.1 | IMPRECISE | minor | open |
| P07C1-G3-05 | NUMBER | O2 ±0.06 dB "(the truncation bound above)" | CONDITIONS VIOLATED | major | open |
| P07C1-G3-06 | NUMBER | O2 "at least half evaluated" | PRODUCT MATTER | none | open |
| P07C1-G3-07 | NUMBER | 33/40 within 1.81 % alongside eps 0.013 % | INCONSISTENT (pending Q1) | major | open |
| P07C1-G3-08 | — | draft prints "level steps"; code does not | INCONSISTENT | minor | open |
| P07C1-G3-09 | FACT | edtS = EDT definition (0 … −10 dB, LS, −60/slope) | CORRECT | none | closed |
| P07C1-G3-10 | DECISION | O3 fixed-window slope | CONSEQUENCE | minor | open |
| P07C1-G3-11 | DECISION | O4 restrict to layout 5 and CR3 | CONSEQUENCE | minor | open |
| P07C1-G3-12 | DECISION | O5 threshold x | CONSEQUENCE | minor | open |
| P07C1-G3-13 | — | AX47 scope/reversal; AX49 Acceptance under O2, O3, O5 | unaffected | none | closed |
| P07C1-G3-14 | — | D1 overall | several valid / PRODUCT MATTER | — | to decision loop |

Questions: Q1 per-band eps; Q2 direct fraction / r/r_c of the 7 cases; Q3 meaning of ±0.06 dB in the O2 draft; Q4 the
5 % threshold's status; Q5 the "half" floor. Q1/Q2 answered in file 23.
