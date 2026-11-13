# 18 — Seat 3 position on the 07c-2 window (FM-D1-S3, file 16 §2)

2026-11-13. Saved by the orchestrator from the seat's report. Corpus not re-read (Vorländer §4.3 Eq. 4.15 taken on the decider's
citation).

**Reading.** The 07c-2 scope 9 "Interim stream check" bullet and AC: the window [t_mix,e, L) for a full-length interim differing only
in per-band level, and the "no shared prefix" exit. Cues §4 state discontinuity (the handover crossfade), decay accuracy; strategies S2,
S4.

**Ranking.** Bullet with conditions C1–C3 (own) prefer; as written (file 16 §2) can live with; no 07c-2 line (debt row only) cannot
live with (moot: Maisara chose (i)).

**Now.** As written 1: the [t_mix,e, L) window is right — same `BandNoiseGenerator` stream, same L and per-band decay ⇒ per band
interim − final = (g_b − 1)·tail_b, no edge at L, no h needed there; with analysis-band leakage the ratio is a convex combination of the
(g_k − 1)² over neighbouring bands, ≤ max_k (g_k − 1)², so 20·log10(10^(B/20) − 1) holds exactly when every band holds B. The 1 is for
two wording gaps (C1, C2). With the conditions: 0.

**Later.** As written 1: the "no shared prefix" branch is a silent exit for exactly the interims that matter — (a) a different stream:
the handover is the AX18 / AQ4 equal-gain crossfade, which with incoherent states dips up to 3 dB mid-fade (energies add, Vorländer §4.3
Eq. 4.15, the N1 physics); AX47's fade test is an upper bound (E_out ≤ …·max) and does not catch a dip — a criterion-1 artifact on
every load; (b) a different per-band decay — criterion 2 (decay JND 5 % strict); AX47's level step over the tail window does not test
the slope. Both would surface in 07c-2's PR or the L1 listening item; undo a `/fix-plan` line. With the conditions: 1 (two printed or
asserted extras on a test 07c-2 already builds).

**Evidence.** Gain-only difference has no edge at L; band leakage a convex combination [Inferred]; AX49 normalisation applies
√(E_p,b/f_b) to the same realised noise, so a shared stream gives a pure gain (BUILD_PLAN AX49). Incoherent equal-gain mid-fade energy
0.5·(E_a + E_b), a 3 dB dip at equal levels (Vorländer §4.3 Eq. 4.15 via file 16 S3-L2). AX20: specular images end at t_mix,e + 2.5 ms
in the hybrid; under the AX22 ISM-only fallback the list extends past t_mix,e and there is no tail; AX49: D1 (early only) for scenes
whose matched tail energy is zero. Decay JND 5 % [Observed, register]; AX47 (b) already uses EDT within 5 %.

**Conditions (as written 1/1 → 0/1):**
- **C1 (zero-tail cases):** cases with zero matched tail energy print 'not evaluated (no tail)' and never count as a pass (AX22
  ISM-only fallback, AX49 D1 early-only scenes) — otherwise E(interim − final) = 0 passes trivially and N1 cannot go red.
- **C2 (wording of h):** h applies only at the L_f edge; the full-length window [t_mix,e, L) has no subtraction at L ("h as in AX47 (b)"
  can be read as trimming it).
- **C3 ("no shared prefix" branch):** the PR's statement also carries (1) the handover fade law for that source — equal power if the
  streams are incoherent, or an asserted bound on the mid-fade dip, routed to AX18's owner (Seat 5); (2) if the interim's per-band decay
  differs from the final's: EDT within 5 % at 500 Hz and 1 kHz against the final, on AX47 (b)'s terms (d < 0.5); (3) AX47's level step
  in both windows — the branch exits to an existing test, not a sentence.
- Optional (0 either way): print the window's specular energy share (negligible over 2.5 ms).

**Hand-offs.** Equal-gain vs equal-power for incoherent handovers (AX18, AQ4) — Seat 5 (thread and fade mechanics); audibility of a
30 ms dip — Seat 1; whether 07c-2 admits a non-gain interim — 07c-2's loop (Seats 1, 3, 5).
**Premortem.** 07c-2 admits a statistical interim on a fresh stream or with a shifted decay; the branch exits on a PR sentence; every
large-room load dips ≈ 3 dB mid-handover or settles to a different decay; Maisara hears it first at L1 ("without an obvious jump"),
after CI was green.
