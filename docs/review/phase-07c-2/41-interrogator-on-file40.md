# 41 — Interrogator on file 40 (2a, 2b final)

Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. **Verdict: nothing fails.** 2a and P3 survive with small
corrections; 2b, P1 and H2 survive with corrections (2b's are P1's and H2's). All seven file-39 points answered.

- **Quotations:** NFR-1 (L105), NFR-8 (L112) and AX21 2026-11-05 (BUILD_PLAN L144) verbatim; both options shown
  against every cited id. SURVIVES.
- **D40-L1, L2, L5, L7:** SURVIVES. 0.1865 × 2.009 = 0.3747 s. Optional: 0.0007 × 2.009 = 1.4 ms, not 1.3 ms
  (file 22 prints 1.3; the 0.0007 is rounded).
- **D40-L3:** SURVIVES. 1/3.22² → −10.16 dB (Kuttruff §5.6, Eqs. 5.43–5.44); Eq. 5.43 is "questionable" when ᾱ is
  not small (here 0.28), which touches only the non-load-bearing "about 20 dB".
- **D40-L4 / P1: SURVIVES WITH CORRECTIONS.** Arithmetic holds ((46 − 20 − 13.3)/60 · 1.30 + 0.1 = 0.375 s), but
  L_drop 13.3 dB does not follow from the per-emitter D/R cited (+10.7 → 11.05 dB, +9.7 → 10.14 dB, giving 0.424 /
  0.444 s). It comes from the heard L + R D/R of +13.1 dB at 1 kHz (10·log10(1 + 10^1.31) = 13.31 dB; file 22 L78,
  L138). P1 must say "L_drop 13.3 dB, from the heard L + R D/R +13.1 dB at 1 kHz, file 22". The 46 dB SNR is
  broadband (Seat 9's own [Hyp], 26-seat9 L39; not in the corpus).
- **D40-L6 / P3: SURVIVES WITH CORRECTIONS.** +17.6 % / +19.5 % → "+18 %" fair. Tail EDT is +4.9 % (L), +6.6 % (R):
  P3 says "+5 to +7 %". The anchor at phase-08-4 L133 exists; 08-4 is the freeze point (phase-08-1 L205–206). The
  procedure matches file 27 (L64–66); "returns to the board" and "tools/acoustics only" are process, not acoustic.
- **P2 anchors:** verbatim (L91, L99). SURVIVES.
- **H2 (label kept until M3): SURVIVES WITH CORRECTIONS.** The seal guards hold (L94–96, L112), but a third live site
  is omitted: `tools/ci/listening_pack.py` L452 prints `sc['label']` (the vetoed string) into 07c-2's listening-pack
  artifact, to which the listening checklist sends Maisara, so "no stimulus is … cited under it" is untrue.
  Corrections: name listening_pack.py L452 (and the artifact's text and manifest) in P2, F1 and debt row 2; debt row
  2 becomes three lines in three files (run sheet L56; abx_kit.py L133, L156; listening_pack.py L452 reads the
  kit's string); flag the label as superseded in the PR's listening checklist.
- **2a:** SURVIVES WITH CORRECTIONS (only the optional 1.4 ms fix).
