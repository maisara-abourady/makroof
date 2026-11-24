# 42 — Interrogator: diff check of decider file 40's P1–P3 (with file 41's corrections)

Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. **Verdict: CLEAN**, one optional wording fix (applied).

- P1 (phase-07c-2b.md L91–96): matches file 40 P1 with file 41's correction (L_drop 13.3 dB from the heard L + R D/R
  +13.1 dB at 1 kHz; 46 dB SNR marked Seat 9's [Hyp]). Numbers: 10·log10(1 + 10^1.31) = 13.31 dB (file 22 L78);
  hold 0.1 s and tail T60 1.30 s (file 22 L140–141); (46 − 20 − 13.3)/60 · 1.30 + 0.1 = 0.375 s (26-seat9 L35–36).
- P2 (phase-07c-2b.md L105–111): appended after the L99 anchor, verbatim, with file 41's third site
  (`listening_pack.py` L452, artifact text and manifest, PR listening-checklist flag).
- P3 (phase-08-4.md L134–140): verbatim; T30 +17.6 % / +19.5 % ("+18 %" fair), tail EDT +4.9 % / +6.6 % ("+5 to
  +7 %"), file 22 L115; procedure matches file 27 L64–65.
- Scope: nothing beyond these three edits and one §6 row.
- §6 row (BUILD_PLAN L533): accurate (numbers, PRD ids, amends none, no AX/AQ value, threshold or golden changed).
  Wording fix: "marked superseded pending M3 in its three live sites" read as if those files were edited; now
  "…in phase-07c-2b scope 2, which names its three live sites (run sheet §1, `abx_kit.py`, `listening_pack.py` L452;
  unchanged until M3)".
