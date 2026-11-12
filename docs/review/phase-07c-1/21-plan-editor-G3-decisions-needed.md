# 21 — Plan-editor: steward G3, DECISIONS NEEDED (phase 07c-1 session 2)

2026-11-12. /fix-plan step 2. No edits made.

**D1.** `docs/BUILD_PLAN.md` §2 AX47 (b) (and through it AX49 "Acceptance" and phase-07c-1 A4): how the EDT clause
("Asserted per band on the A4 set (several seeds, 48 and 96 kHz): both windows; EDT within 5 % at 500 and 1000 Hz on the
whole IR against the exact IR.") reads for bands whose EDC is ill-conditioned.

Measured (tests/unit/test_interim.cpp @ ad8971c): provisional = exact prefix to 3.6e-5 relative; tail-window step
≤ 0.072 dB, common-window step ≤ 0.015 dB in every band; EDT within 1.81 % on 33 of 40 cases; 7 cases (layout4_s1 at
500 Hz and 1 kHz; absorbing-floor cube at 1 kHz) where the exact IR's own EDT moves 5.1–98 % under ±0.06 dB of the EDC's
0 dB reference.

Options (with the plan-editor's corpus pointers):
- O1 assert as written on every case — Vorländer Table 6.1 (5 % EDT jnd), §6.4.1 (EDT definition); A4 cannot pass.
- O2 conditioning rule (implementer's candidate): assert ≤ 5 % where the exact EDT moves ≤ 5 % under ±0.06 dB of the
  EDC reference; otherwise print 'not evaluated (ill-conditioned EDC)' with the band's level steps (still ≤ 1 dB, both
  windows); at least half the cases evaluated — Kuttruff §8.4 (direct sound shapes the decay curve unless r ≫ critical
  distance), §7.6 (EDT strongly influenced by early reflections); ±0.06 dB = AX49 K17′; 5 % = Table 6.1; "half": no
  corpus basis.
- O3 smoothed / fixed-window EDT — Kuttruff §8.4 Eqs. 8.26–8.27; §7.6 (Atal, first 160 ms); loses the Table 6.1 link.
- O4 restrict the EDT clause to well-conditioned scenes (layout 5, CR3: 20 of 40 cases) — chosen from results.
- O5 a direct IR-difference criterion — no corpus value for its threshold x.

Sentences per option: only the AX47 (b) "Asserted per band…" sentence (and its evidence column) changes under O2, O3 and
O5; O4 also qualifies AX49 "Acceptance"; A4 unchanged (it points to AX47 (a)/(b) and AX49). Under O2–O5 a §6 row is due.

Draft O2 text (to apply once verified): "Asserted per band on the A4 set (several seeds, 48 and 96 kHz): both windows; EDT
(ISO 3382-1 A.2.1, as `tools/acoustics/metrics.py` takes it) within 5 % at 500 and 1000 Hz on the whole IR against the
exact IR, in every (scene, rate, seed, band) case whose EDC is well-conditioned: the exact IR's own EDT moves by ≤ 5 % when
the Schroeder curve's 0 dB reference (its total energy) is changed by ±0.06 dB (the truncation bound above). Other cases
print 'not evaluated (ill-conditioned EDC)' with the exact and provisional EDT and the band's level steps, which stay
asserted ≤ 1 dB in both windows; at least half the EDT cases are evaluated."

Sub-choices to confirm: the 5 % threshold; the ±0.06 dB perturbation applied to the EDC reference (`sch[onset]`), not the
IR samples; the "at least half" floor (code: `edtEvaluated >= illConditioned`). Observation: ad8971c already implements O2
before D1 is verified.
