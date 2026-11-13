# 2 — Seat 1 position (D-B1, D-B2, D-B3, D-B4), round 1

2026-11-13, corpus c1b171f. Saved by the orchestrator from the seat's report. D-B5 / K24 not its matter (recorded not
required; agreed). Orchestrator check of the arithmetic: (1 + 10.67/30)² = 1.838 → 10·log10 = 2.64 dB (Seat 1 is right;
file 1's 2.88 dB is wrong).

## D-B1
Reading: is the overrun an audible failure, which bar? Cues W1 ("measure the floor first", "confounded instrument"), S2's
anomaly (a gross artifact needs no JND test). **The bar:** a real host callback missing its 1 333 µs deadline underruns —
a dropout/click, far above any JND; the bar is a count: zero underruns on a real host audio thread (PRD NFR-3). The
instrument cannot show it: normal-priority thread, wall-clock timing, `sleep_for` pacing, 953–1 936 of ≈ 7 500 callbacks
(so "p99.9" = the largest 1–2 samples); macOS ≈ 9 ms with one builder points to the instrument's floor (RQ4).

| Option | Label | Now | Later | Reason |
|---|---|---|---|---|
| B1-b | prefer | 0 | 1 | measures the floor (0 builders) at the real priority and counts overruns — the audible quantity |
| B1-d | can live with | 1 | 1 | output-identical; the interim plays longer, AX47 still bounds the step |
| B1-c | can live with | 1 | 1 | output-identical for this seat; inversion and the cond. 12 amendment Seat 5's |
| B1-a | can live with | 1 | 2 | a possible dropout unmeasured until Phase 13's single re-check; finding it there ≈ a phase of threading rework |

Condition (B1-a 2 → 1): the record prints the 0-builder floor, the callback count and the overruns past one period.
Premortem: record only; a producer on a 4-core laptop hears clicks; a ticket finds it first.

## D-B2
Reading: what the producer hears at insertion (R3, §9: the first bug report after a change is about a transition).

| Option | Label | Now | Later | Reason |
|---|---|---|---|---|
| B2-a | prefer | 0 | 0 | first sound already the final level (AX47 (a), step 0); a 145–430 ms wait hides inside a user-initiated insert; host tolerance Seat 5's |
| B2-d | can live with | 0 | 1 | sounds the same; a second level source to keep in sync; mismatch falls back to keyless |
| B2-b dry | only as the silent variant | 2 | 1 | dry then wet for 0.15–0.43 s: an audible scene change |
| B2-b silent | can live with | 1 | 1 | a gap < 0.5 s then an AQ4 fade from silence |

Condition (B2-b 2 → 1): silent, never dry; the fade from silence covered by the D-B3 check. Premortem: dry B2-b → "the reverb
kicks in late".

## D-B3
Reading: can the test fail on the fault it exists to catch (a test that cannot fail is opinion)? The fault: equal-power
where equal-gain is required; at mid-fade with ρ ≥ 0.993, (cos θ + sin θ)² = 1 + ρ·sin 2θ ≈ 2 → +3.0 dB (AX18; Vorländer
§4.3 Eq. 4.15). The tolerance is the largest fault that can hide; this seat wants it below AX47's 1 dB step bound.
Arithmetic (1 + T/30 ms)²: 1 ms 0.285 dB; 2.5 ms 0.695 dB; 5 ms 1.339 dB; 10.67 ms 1.838 → **2.64 dB (not 2.88)**. W-d on
[10.67, 21.33] ms: the window-averaged equal-power excess 1 + (cos 1.117 − cos 2.234)/1.117 ≈ 1.944 → +2.89 dB, a margin of
≈ 0.25 dB at ρ ≈ 1, gone at lower ρ (a B1′-held edit is not bounded at 0.993).

| Option | Label | Now | Later | Reason |
|---|---|---|---|---|
| W-a 1 ms | prefer | 0 | 0 | hides ≤ 0.28 dB; fine resolution |
| W-b 2.5 ms | prefer (tie) | 0 | 0 | hides ≤ 0.70 dB (< 1 dB); 12 windows per ramp; catches the 3 dB fault by > 2 dB |
| W-c 5 ms | can live with | 2 | 1 | a 1.34 dB bump can hide, above the 1 dB step bound |
| T-0 | can live with | 1 | 2 | not shown valid per window; a false failure invites loosening (§17) |
| W-d 10.67 ms | cannot live with | 3 | 2 | barely catches or misses its one fault; the pass carries no information |

Conditions: W-c, W-d → 1 with an added mid-fade-centred window ≤ 2.5 ms; T-0 → 1 only with a per-window proof. Signal: the
fixed sparse set — pink noise and speech with pauses (B2). Recorded gap (not a condition): the comparison is broadband; a
fault confined to one band (+3 dB at 63 Hz only) can stay under it. Premortem: W-d, an equal-power regression ships, a +3 dB
swell on every settle.

## D-B4
Reading: which candidates change what is heard (T4 tone colour, test first; no claim without data).

| Option | Label | Now | Later | Reason |
|---|---|---|---|---|
| C1 | prefer | 0 | 0 | bit-identical |
| C2 | prefer | 0 | 0 | bit-identical |
| C6 | can live with | 0 | 1 | output-identical; interims play longer; step unchanged |
| C4 | can live with | 0 | 0 | output-identical; memory Seat 5's |
| C8 | can live with | 0 | 1 | no detection question; load time Seats 6, 8 |
| C7 | can live with | 0 | 1 | deferral only |
| C5 | cannot live with as offered | 3 | 2 | changes every shipped tail (density, colour) untested (Tier A); L4 and goldens redone |
| C3 | cannot live with | 3 | 3 | at the rated corner L_p ≈ 3.7 s; any cap below 0.312·T60 cuts the provisional's depth below 18.7 dB, removing the by-construction AX47 (b) truncation bound (≤ 0.06 dB, Vorländer §6.4.1 Eq. 6.4); a cut tail on a sparse release is exposed (B2); L4 tests the exact length |

Conditions: C5 (3 → 1) a blind ABX of the new generator vs the current on the fixed set (pink-noise pulses, speech, a held
chord) at chance (< 12/16; P(≥ 12 | 16, 0.5) = 0.038) before adoption, goldens via `update_goldens`; otherwise defer to
Phase 13 (AQ10). C3 (3 → 1) no cap below 18.7 dB depth (≡ Seat 9's L_p ≥ 0.31·T60) — nothing left to cut at the corner —
or L4 run at the capped length and passing, AX47 (b) re-proven. L4: C1, C2, C4, C6 leave it valid; C3, C5 invalidate it.
Request: the L4 stimulus includes a chord release inside the interim window (a held chord masks a cut tail) [Hyp].
Premortem: C3 untested → stopping playback during a load, the reverb cuts off.

Evidence tags: gross dropout needs no JND (S2, [Inferred]); floor first (W1/T1); dense content masks (B2); tone colour (T4);
+3 dB (Vorländer §4.3 Eq. 4.15 via the brief, own arithmetic); 18.7 dB / 0.06 dB (Vorländer §6.4.1 Eq. 6.4 via AX49);
release exposure [Hyp]. Hand-offs: Seat 5 (0.43 s prepare, B1-c inversion, C4, C6); Seats 6, 8 (C7, C8); Seat 9 (C3);
interrogator (W-d tolerance figure).
