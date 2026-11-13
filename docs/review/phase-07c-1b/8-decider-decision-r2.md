# 8 — Decider: decision round 2, phase 07c-1b (D-B1 … D-B5), interrogator corrections applied

2026-11-13, corpus c1b171f. Saved by the orchestrator from the decider's report. Read: files 1–7, RG-1
`docs/review/phase-05h/70-…`, BUILD_PLAN AX38 4c / (iv) / AX47, `docs/phases/phase-13.md` L50–79, phase-13-3 scope 4, phase-13-5
Raise / scope 3, phase-07c-1b scope, README "Who answers Maisara's questions".

## PRD digest (file 1's, corrected)
- Users: producers / DJs on macOS and Windows, any DAW, no spatial-audio knowledge; scenes across instances (FR-3D-5, FR-3D-6,
  FR-SIM-7, A5). Usability: "Accuracy is the top priority; CPU load and latency may be high, but the plugin must stay usable in a
  DAW session" (NFR preamble, L101).
- **NFR-2 is narrower than round 1 used it**: processing latency "report[ed] … to the DAW for compensation"; a UI stall falls
  under the preamble only (P07C1B-R1-15).
- Hard bounds: no instance cap; no W_max cut, range change or seam; NFR-8; AX5; offline never interim (AX49); AQ4 30 ms; AX47
  (statistical interim only from 07c-2); AX48 FM-3′; AX38 (i) incl. "the builder's priority is not raised to compensate".
- Her recorded decisions here: **AX38 4a / (iv), "Accepted by Maisara 2026-11-10"** — the 10 s line ("if the 8-instance, 100 m
  time until the last instance is audible at load exceeds 10 s, it goes to Maisara before the first release"); **RG-1 / RG-F1
  text in AX38 4c** carrying `AMENDS her decision of 2026-11-10` — the macOS trigger "1.15 × the mean … re-derived at the 07c
  re-pin"; (d) "A broken assertion, or the macOS trigger, is a defect"; the low-α check "in-window on Linux and Windows, printed on
  macOS"; baselines "never a red or out-of-window run". **AX47** is board text (D-C1; FM-4′ "amends nothing"): a plan default.
- **K7 restated (R1-07):** AX38's rationale says "4a … Accepted by Maisara 2026-11-10" and 4a contains (i)'s "not raised to
  compensate" — that clause is hers; cond. 12's "Builder threads keep their default priority" is board decision D-G1; B1-c would
  touch cond. 12, not her clause; no option chosen changes either.
- Verification culture: every DSP behaviour checked, independent references preferred, goldens never regenerated to pass,
  tolerances never loosened.
- Session limit (steward G1): no decision below needs a `src/` change; new code is under `tests/` and `ci.yml` (Seat 5 Q5); the
  S2 runs follow the session's last code change.

## D-B1 — stands, corrected

| opt | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| B1-a | 1/2 | 0/1 | 1/2 | 1/2 | 1/**3** | 1/2 | 1/2 | 1/2 | 0/0 | 3 | **23** |
| B1-b | 0/1 | 0/0 | 0/1 | 0/0 | 1/0 | 0/1 | 1/0 | 0/0 | 0/0 | 1 | 5 |
| B1-c | 1/1 | 1/1 | 2/2 | 1/1 | 2/2 | 1/2 | 1/1 | 1/2 | 0/0 | 2 | **22** |
| B1-d | 1/1 | 1/1 | 1/1 | 1/1 | 1/1 | 1/1 | 1/1 | 1/1 | 0/0 | 1 | 16 |

Working: no bound broken (B1-c touches only the cond. 12 plan default); B1-a dropped (S5 3 later); max 1 B1-b, B1-d; sum 5 < 16.
**DECISION D-B1: B1-b.** Spec items 1–5 as round 1 (file 4). Item 6 corrected (R1-04): "6. Residual owner: an overrun > period at
8 builders with none at 0 is re-measured with this instrument in **phase-13-3 scope 4** (real macOS hardware, runs first in 13-3)
and on the R5 Windows release machine. A miss opens **13-1b** (D-PS4 instruction 2), with B1-d first candidate. Never an instance
cap." Load-bearing: D1-L1 p99.9 = `us[ceil(0.999·N)−1]` = 1st–2nd largest at N ≤ 1 936 (R16; R1-05); D1-L2 host render threads
real-time, default workers not (R4, R7, R8; R6 a lead); D1-L3 Seat 5 B1-a 3 later.

| seat | commits | undo | evidence | repaid when |
|---|---|---|---|---|
| S1 | zero underruns verified only on real hosts | none | 13-3 scope 4 / R5 machine | that re-measure |
| S3 | convolver per-callback cost before 08 | none | 07c-1b runs; 08-4 | 08-4 repeats in both modes |
| S6 | one more record; remedy in Phase 13 | none | 07c-1b runs | 13-1b if a miss |

Objection (Seats 1, 7, 8: real rise, remedy waits): B1-b's sweep settles it this phase; 08-4 repeats. Confidence high. Reversal:
`INSTRUMENT INVALID` everywhere, or an overrun at 8 builders with a clean floor. PRD lines: B1-b serves the preamble by measuring
"usable"; B1-d the same unmeasured; B1-c strains AX38 (i) class (1) (inversion); B1-a vetoed; no PRD id points to B1-d before
evidence.

## D-B2 — revised: DECISION B2-a″ + FOR MAISARA FM-B2 (scope reading) + FM-10S
**Q1 (Seat 5 r2b, code `ScenePipeline.cpp` L812–822, L443–476, L908–937):** in a `setActive`-before-`setState` host each instance
runs insertion solve, ISM and interim, then its restore; nothing reused. Added serial 8 × 145–430 ms = **1.16–3.44 s**; run 42
macOS keyed 10 206 ms → **≈ 11.4–13.6 s** vs AX38 (iv)'s 10 s. `setState`-first hosts unaffected. Record (h) under-reports this
order (settle wait, L1730–1734). Seat 4 convened narrowly (R1-12). Seat 6's B2-b (silent) entered **3/3, veto-grade** (R1-09).

Options: B2-a (round 1); **B2-a″** (Seats 5 and 4's conditions): B2-a plus record (h) prepare-first totals in two orders
(interleaved, batched) without a settle wait beside the `setState`-first total; 07d's 5 s criterion and the 10 s reading use the
larger total (FM-10S); **C9** (process-wide single-flight insertion cache keyed by canonical scene + `tailSeed`, fs, P,
`engineKey()`, platform) named in 07d ahead of C1; Seat 4 (i) output-1 unit decays at insertion a 07d design item, built in the
background unless the current mode needs two outputs (Seat 5: synchronous 0/2, background 0/1; Seat 4's fallback "goes to 07d with
D-B4"); Seat 4 (ii) 08-4 prints `insertMs` per mode; Seat 4 (iii) 08-3 asserts per-ear seeds in the first IrSet at insertion;
B2-a′ (C9 now); B2-d; B2-b dry; B2-b silent.

| opt | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| **B2-a″** | 0/0 | 0/1 | 0/1 | 0/1 (fc) | 1/1 | 0/0 | 0/1 | 1/1 | 0/0 | **1** | **8** |
| B2-a (r1) | 0/0 | 0/1 | 0/1 | 0/1† | 1/**2** | 0/0 | 0/1 | 1/1 | 0/0 | 2 | 9 |
| B2-a′ (C9 now) | — | — | — | — | **2**/0 | — | — | — | — | ≥2 | — |
| B2-d | 0/1 | 1/2 | 1/2 | 1/2 | 1/2 | 0/1 | 1/2 | 0/2 | 0/0 | 2 | **19** |
| B2-b dry | 2/1 | 0/1 | 1/2 | 1/2 | not rated (no dry path, K11) | 2/2 | 1/1 | 2/1 | — | 2 | — |
| B2-b silent | 1/1 | 0/1 | 1/2 | 1/2 | 2/2 | **3/3** | 1/1 | 1/1 | 0/0 | 3 | vetoed |

(fc) read from conditions: for S1, S2, S3, S6, S7, S8 the B2-a cells carried (the variant adds only test records and 07d / 08
plan lines) — interrogator to check. † Seat 4 ties its later 1 to (i)–(iii), which B2-a wrote none of (irrelevant: S5's 2 sets the
max). Seat 5 re-rated B2-a 1/2 ("the prepare-first cost counted in no criterion"). B2-d sum 19 with S4 (16 without; R1-10). Seat 9
not required.
Working: B2-b silent dropped (Seat 6 3/3; only Maisara overrides); max 1 only B2-a″ (B2-a′ out: Seat 5 now 2 — a `src/` change on
the prepare / decide path plus TSan, also forcing fresh re-pins under G1).
**DECISION D-B2: B2-a″**, accepted for her through FM-B2 and FM-10S.

**FOR MAISARA FM-B2 (scope reading; R1-13).** Q: is a fresh instance's first prepare (no restore, no saved level) a load under AX48
FM-3′? Answer: "AX48 FM-3′ covers instance insertion, which its text does not name: a fresh instance's first prepare (no IrSet
current, no saved state) is a keyless load of the instance's default scene. Its stage-1 (A) solve runs synchronously, class (1) at
the AX38 gate, and its first IrSet is installed at the first partition boundary with no fade. In a host that prepares before
restoring, this insertion cost counts in the load totals of record (h) and AX38 (iv) (FM-10S)." Rests on: preamble (L101); NFR-1;
NFR-6; NFR-8; FR-3D-6, A5; AX48 FM-3′ ("With no IrSet current: the stage-1 (A) solve runs synchronously"); AX38 (iv). Reasoning:
FM-3′'s "no IrSet current" is met by a fresh instance; AX48's keyless list ("any mismatch, or a v1 state") does not name insertion,
so this settles scope where her decision is silent; NFR-1 (first sound = final level, AX47 (a), step 0); the cost is a 145–430 ms
UI stall inside `setActive` / Initialize (R19, R20), far below pluginval's 30 s (R21) — preamble territory; at project load in
prepare-first hosts it adds 1.16–3.44 s, now counted (FM-10S) and assigned to 07d with C9 first. Options vs PRD ids: B2-a″ serves
NFR-1, strains the preamble by up to 3.44 s at 8-instance load in prepare-first hosts, measured and owned by 07d before release;
B2-a serves NFR-1, same strain uncounted; B2-a′ serves NFR-1 and the preamble earliest, needs a restore-path `src/` change now; B2-d
serves NFR-1, saves only the solve, risks NFR-8 if in `src/sim`; B2-b dry strains NFR-1 (dry first sound unlike the render); B2-b
silent strains NFR-1 (0.15–0.43 s silence), vetoed; no PRD id ranks timing inside the pre-release plan. Veto trigger: a host or
validator timing out / "not responding" at insertion (cond. 11 trace; 13-5 matrix). AMENDS nothing.

**FOR MAISARA FM-10S (reading of AX38 (iv)).** Q: in a host preparing before `setState`, does "time until the last instance is
audible at load" include the insertion solves? Answer: "Yes. The 10 s line, and 07d's 5 s criterion, are read on the larger of
record (h)'s totals measured without a settle wait: prepare-first (interleaved and batched) and `setState`-first. All three are
printed." Rests on: her AX38 (iv) line (2026-11-10); preamble; NFR-6; R17 (VST3 fixes no order). Reasoning: her line names the
user's wait, not a code path; with no fixed call order the user may wait for both; the larger total is the honest one; it tightens
the measurement, loosens nothing. Options: prepare-first max serves the preamble and NFR-6; `setState`-first only under-reports by
up to 3.44 s, straining the preamble. Veto trigger: she may read "at load" as the plugin's restore alone. AMENDS nothing (reads her
line where silent on call order). Status: line already crossed (10 206 ms); goes to the decider for her before the first release,
on 07d's record (not due now).

Load-bearing: D2-L1 prepare-first runs insertion then restore, no reuse (Seat 5 r2b, code); D2-L2 8 × 145–430 ms = 1.16–3.44 s;
10 206 + that = 11 366–13 646 ms; D2-L3 first IrSet at the first boundary, no fade (`computeBlock` L281–287; R1-16); D2-L4 Seat 6
silent 3/3; D2-L5 Seat 5 B2-a 1/2, B2-a″ 1/1 on its conditions.

| seat | commits | undo | evidence | repaid when |
|---|---|---|---|---|
| S2, S3 | insertion takes 07c-2's stage-1 rules | one reading | 07c-2 | plan item 5 |
| S4 | binaural insertion builds output-1 decays; per-ear seeds | design in 07d | 07d; 08-3; 08-4 `insertMs` | items 8, 11 |
| S5 | prepare-first cost in 07d's 5 s / 10 s reading; C9 | B2-b dry or B2-d, one test | 07d record (h) | item 8 |
| S7 | binaural may lengthen the stall | as above | 08-4 `insertMs` per mode | item 11 |
| S8 | UI stall at insertion | as above | 13-5 matrix reads insertion per host | item 12 |

Confidence medium. Reversal: a host / validator limit below the measured insertion time, or a hang in the cond. 11 trace → the
board considers **only B2-b dry or B2-d**; B2-b silent vetoed by Seat 6 (3/3), only Maisara overrides.

## D-B3 — stands, corrected; signal ruling re-issued

| opt | S1 | S3 | S4 | S5 | max | sum |
|---|---|---|---|---|---|---|
| W-a | 0/0 | 0/0 | 0/1 | 0/0 | 1 | 1 |
| W-b | 0/0 | 1/1 | 0/0 | 0/0 | 1 | 2 |
| W-c | 2/1 | 1/2 | 1/1 | 0/1 | 2 | 9 |
| W-d | **3**/2 | 2/2 | 2/2 | 1/1 | 3 | 15 |
| T-0 | 1/2 | 2/2 | 1/2 | 2/2 | 2 | 14 |

(Seats 2, 6, 7, 8, 9 not required for the window; Seat 7 convened for the signal.) W-d dropped; max 1 W-a, W-b; 1 < 2.

Signal (Q2, R1-24):

| opt | S1 | S7 | S3, S4, S5 | max | sum |
|---|---|---|---|---|---|
| **s1 + A, B (+ C)** | 0/0 (0/1 → 0 with A) | 0/0 | 0/0 (fc) | **0** | **0** |
| s1 + s2 | 0/0 | 1/1 | not rated | 1 | — |
| s2 | 0/0 | 1/1 | not rated | 1 | — |
| s3 | 0/0 | 1/2 | not rated | 2 | — |

(fc) for S3, S4, S5: conditions input-independent (D3-L1, D3-L2); Seat 5's "identical on three OSes" met by the seeded generator.
Seat 1 accepts s1 ("Yes in function; not the literal word 'speech'"), rates renaming AX47's "speech" to "seeded speech-like" 0.
Seat 7's condition: AX47 and AC 7 "say what was used ('seeded speech-like')"; the public record never says "tested with speech".

**DECISION D-B3: W-a + companions + signal s1** — changes AX47's plan-default wording by board DECISION (AX47 not her text; no
FOR MAISARA). Corrections: **D3-L3 restated (R1-21):** tolerance 8u·(|a|+|b|), u = 2⁻²⁴ (rounding ≤ 3u, ≤ 8u with FMA, R1-20); a
one-sample alignment error moves g by 1/L and o by **|b−a|/L** — caught only where |b−a|/(|a|+|b|) > 8u·L = 6.9·10⁻⁴ @ 48 kHz,
1.37·10⁻³ @ 96 kHz (≈ −63 / −57 dB relative); a near-zero-step fade (provisional → exact) is not offset-checked by (ii).
**Companion (iii) (R1-22):** outside [s0, s0+L) output equals the endpoint rendered alone **by value** (`==` per sample), accepting
the documented b = −0 / o = +0 case of the last fade block (stated in the test comment). **Signal s1:** seeded glottal pulse
train f0 120 Hz ±5 % jitter, resonators 500 / 1 500 / 2 500 Hz, 4 Hz syllabic envelope; **C** ≥ one pause starting inside a fade
and one ending inside a fade; **B** seed and parameters fixed and versioned, never changed between versions; **A** a CI test signal
only — never labelled as speech in a listening pack, never replacing recorded speech or a cappella voice in the acceptance set;
07c-2's self-ABX uses recorded speech; resonator values test parameters, not speech claims; no P.50 conformance claimed.
Load-bearing: D3-L1 (R1-18), D3-L2 (R1-19), D3-L3 restated, fade from silence |o| ≤ |b| (R1-23), Vorländer §4.3 Eq. 4.15 (≈ +3.0 dB
at ρ ≈ 1).

| seat | commits | undo | evidence | repaid when |
|---|---|---|---|---|
| S4 | per-channel windows to 08-3 / 09 per ear / feed | widen N_w | 08-3 / 09 CI | items 6, 11 |

(Seat 1's signal debt 0 with A, B written.) Objection: Seat 4 prefers W-b (0/0); W-a holds on the sum. Confidence high (window),
medium (signal, three cells from conditions). Reversal: a false red on correct code falsifies D3-L1 or D3-L3 → interrogator; never
loosened. PRD lines (R1-25): W-a serves NFR-1, FR-SIM-6 best (0.285 dB catches the 3 dB fault); W-b coarser (0.70 dB); T-0 strains
them (not valid per window; a false red invites loosening); W-c, W-d strain them (1.34 / 2.64 dB faults hide); s1 serves NFR-1 (all
fault regimes, bit-identical); s2, s3 add no detection.

## D-B4 — stands, corrected

| opt | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| C1 | 0/0 | 0/0 | 0/0 | 0/0 | 1/1 | 0/0 | 0/0 | 0/1 | 0/0 | 1 | 3 |
| C6 | 0/1 | 0/0 | 1/1 | 0/1 | 1/1 | 0/1 | 0/1 | 1/1 | 0/0 | 1 | **10** |
| C1 + C6 | 0/1 | 0/0 | 1/1 | 0/1 | 1/1 | 0/1 | 0/1 | 1/1 | 0/0 | 1 | **10** |
| C2 | 0/0 | 0/0 | 0/1 | 0/0 | 1/2 | 0/0 | 0/1 | 0/1 | 0/0 | 2 | 6 |
| C4 | 0/0 | — | 1/2 | 1/2 | 2/2 | 0/1 | 1/2 | 0/0 | 0/0 | 2 | — |
| C8 | 0/1 | 0/1 | 1/2 | 1/2 | 1/2 | 1/2 | 1/2 | 1/2 | 0/1 | 2 | **21** |
| **C7′** | 0/1 | 0/1 | 1/1 (fc) | 1/1 (fc) | 0/1 (fc) | 1/1 | 1/1 | 1/1 | 0/0 (fc) | 1 | 13 |

(C3, C5 vetoed, D4-L2.) Working: C3, C5 dropped; max 1 C1, C6, C1 + C6, C7′; **§3 deferral, not a §5 step (R1-27):** C1, C6, C1 + C6
not decidable as "the remedy" — that rests on K17 (contention share, under-informed) and K18 (C1/C2 speed-ups, uninformed):
RESEARCH NEEDED answered by measurement, which C7′ schedules; among complete answers C7′ 13 ("C1 + C6 now, residual to 07d" 14); C7′
commits no code (Q5: new records test-only).
**DECISION D-B4: C7′.** Records this phase (test-only): record (h) per instance prints its restore time; background builds running
at its start (stage hook + `builderBusy()`, split Solve / Assemble, labelled as instances); `hardware_concurrency()`; the
prepare-first totals in two orders without a settle wait (D-B2). Plan text item 8. The C1 memory clause **struck** (R1-31): its
AX38 (i) / (ii) accounting left to 07d's loop (Seats 2, 5 read (ii): 8 × 2²¹ × 8 B = 134 217 728 B).
Load-bearing: D4-L1 restated (R1-28): run 41's Windows single-instance 634 ms, 8 × 634 = 5.07 s > 5 s — one run's figure, used
only to show no measured remedy yet clears 5 s; D4-L2 vetoes (R1-29); D4-L3 C1's key (R1-30); D4-L4 10 206 ms. Debt register: as
round 1, plus S4 (07d designs output-1 decays at insertion) and S5 (C9 ahead of C1; the prepare-first total governs 07d's 5 s).
Confidence medium. Reversal: 07d's records show C9 + C1 + C6 + C2 cannot reach 5 s → C4 or C3-pb under their conditions, never an
instance cap. PRD lines (R1-33): C7′ serves the preamble before the first release and NFR-6; C1, C6, C1 + C6 the same earlier,
unproven (K17, K18); C2 serves the preamble only with free cores and strains it through D-B1 contention; C4 serves load time,
strains "usable" through ≈ 147 MB per instance; C8 defers to Phase 13 with no phase left, straining the preamble; C3, C5 strain NFR-1
(vetoed); no PRD id ranks timing within the pre-release plan.

## D-B5 — re-pin
**(i) S2 — stands.** S2 max 1 sum 1, wins however S1's conditional cells are read (R1-34); Q5: no `src/` change, "C7′ commits no
code" holds. **DECISION: S2** — ≥ 3 manual (`force`) runs on the head commit after the session's last code change, every job green;
runs 41 / 42 / 44 printed, never baselines. PRD lines: S2 serves NFR-6 and the preamble (baselines on shipping code); S1 strains
them if any restore-path change lands; S3 reduces to S1 here.

**(ii) Low-α growth check — FOR MAISARA FM-GROWTH (B-iv)**

| opt | S2 | S3 | S5 | S6 | S7 | max | sum |
|---|---|---|---|---|---|---|---|
| B-i | — | 1/2 | 2/1 | 1/2 | 2/1 | 2 | 12+ |
| B-ii | — | 1/2 | 2/1 | 1/2 | 2/1 | 2 | 12+ |
| B-iii | — | 1/2 | 2/2 | 2/2 | 2/2 | 2 | 15+ |
| **B-iv (conditions met)** | 1/1 | 1/1* | 1/1 | 1/1 | 1/1 | **1** | **10** |
| B-iv+ (Seat 3) | 1/1 (fc) | 1/1 (→1/0) | not rated | not rated | not rated | — | — |

Seats 1, 4, 8, 9 not required. "—": Seat 2 briefed on B-iv only (rows at max 2 without it). * Seat 3 1/1 only if the measured
uniform-slowdown factor ≤ ×1.4, else 1/2 (Seats 2, 3 estimate ≈ ×1.28). B-iv+ not ranked: Seats 5, 6, 7 did not rate it, and their
conditions point opposite ways (Seat 5's fallback prints absolute growth only; Seat 6's (a) says a uniform slowdown is "asserted
only at 30 s and at Phase 13"); B-iv+ only adds an assertion to B-iv, so choosing B-iv forecloses nothing; an optional narrow
question to Seats 5, 6, 7 can run beside interrogation — if all rate ≤ 1/1 and Seat 3's 07d condition (≥ 6 runs) is written, B-iv+
wins on sum (9 vs 10) and is added at the 07d re-pin. Working: all options amend RG-1's form (FOR MAISARA); none vetoed; max 1 only
B-iv.

**FM-GROWTH (covers (ii), (iv)).** Q: may the hosted low-α growth assertion and the solve baselines leave the in-window form, which
almost never evaluates (fact 5: 1 of 9 OS-runs in window; Linux 453 / 490 / 706 vs mean 550)? Answer: AX38 4c plan item 9a. Rests
on: preamble (L101 "must stay usable": a load-time detector); NFR-6; NFR-4 (macOS print-only, carried from RG-1); RG-F1 (AX38 4c),
her decision via `AMENDS … 2026-11-10`; RG-1's own PRD basis (L101, NFR-2, NFR-4, NFR-1, NFR-6). Reasoning: RG-1 set the in-window
bound to detect restore growth; on the S2-proxy runs it evaluates almost never, so the PRD purpose has no armed detector; the
same-run ratio cancels runner speed (Linux max/min 1.071, Windows 1.096) and evaluates every run; the 1.10 factor unchanged — a
change of form, its blind spot stated in words; the absolute bound returns on Phase 13 release machines. Options vs PRD ids: B-iv
serves the preamble and NFR-6 (armed every Linux / Windows run), strains them through a uniform slowdown up to ≈ ×1.28 [Inferred],
visible only as a printed WARNING until 30 s and Phase 13; B-iv+ the same plus in-window uniform detection, unrated; B-i, B-ii
strain the preamble (no detector armed, 0–1 in-window runs); B-iii strains it (false defects: ±22 % honest width vs a 1.10 bound);
keeping RG-1 unchanged = B-i on these runs. Veto trigger: CLAUDE.md "never loosen" read as covering a change of form (the blind
spot the strongest reading against). Public reason (Seat 7): "The absolute bound measured runner speed; the same-run ratio measures
the code; Phase 13 restores the absolute bound on release machines." `AMENDS her decision of 2026-11-10: "I accept the board's
answer by definition."` (via RG-1 / RG-F1: "in-window on Linux and Windows, printed on macOS" and "never a red or out-of-window
run").

| seat | commits | undo | evidence | repaid when |
|---|---|---|---|---|
| S2 | uniform slowdown blind; mandatory re-pins | one constant + CHANGELOG | 07c-2, 07d, Phase 13 | re-pins at 07c-2 / 07d |
| S3 | factor > ×1.4 leaves its later at 2 | add B-iv+ | S2 split | 07d re-pin board on B-iv+ |
| S5, S7 | absolute bound only on release machines | — | Phase 13 | 13-5 R5 |
| S6 | ratio re-derived after 07d's remedy | — | 07d | 07d re-pin |

Confidence medium. Reversal: the S2 split gives f > ×1.4 (B-iv+ to the board at the 07d re-pin), or a false red on identical code.

**(iv) Solve baselines — (iv″) with a dated exit, inside FM-GROWTH**

| opt | S2 | S3 | S5 | S6 | S7 | max | sum |
|---|---|---|---|---|---|---|---|
| **(iv″) + exit** | 1/1 | 0/1 | 0/1 | 0/0 (fc) | 0/1 | **1** | **5** |
| (iv″) without exit | 1/2 | 0/1 | 0/1 | 0/1 | 0/2 | 2 | 8 |

"Confirm the 05i rule" cannot be met (no OS has 3 in-window runs; = (iv″) here). Exit composed from Seat 2 C4 (second branch), Seat
3's ns/eval criterion, Seats 6, 7's dated end; Seat 3's "assert the ns/eval ratio at exit" **not** adopted (unrated by Seats 2, 5,
6, 7; Seat 3 stays 0/1). **DECISION (via FM-GROWTH):** solveRefMs = mean of the S2 runs per OS and scene; k per OS = the largest
max/mean of those runs; PROVISIONAL (print-only, never a (d) trigger); **exit:** ≥ 3 green runs on unchanged work pins (S2 or
later) whose same-run low-α / flutter ns-per-eval ratio lies within 1.05 of its mean — k and baselines then from those runs;
otherwise re-derived at the 07d re-pin; otherwise named in Phase 13 on release machines (13-5 R5); the same-run ns/eval ratio
printed every run.

| seat | commits | evidence | repaid when |
|---|---|---|---|
| S2, S5, S7 | PROVISIONAL until the exit | S2 / 07d runs | exit met |
| S3 | ns/eval ratio not asserted | 07d | 07d re-pin board |

**(iii) macOS trigger — revised: M-a + FOR MAISARA FM-TRIG (reading).** Q3 (R1-35, -36), proxy medians 1 528 / 2 223 / 2 572, mean
2 107.7: M-a ⌊1.15 × 2 107.7⌋ = **2 423 ms** (run 44 over); S6-k needs k = 1.23 (1.22 → 2 571 < 2 572) → **2 592 ms**, cap 1.25.

| opt | S3 | S5 | S6 | S7 | max | sum |
|---|---|---|---|---|---|---|
| **M-a + closure path (X-d−)** | 1/1 (1/2 → 1/1 with closure path) | 1/1 (1/2 → "back to 1 with Seat 3's closure path") | 1/1 | not rated (no condition engaged) | 1 | 6 |
| S6-k (k rounded up, cap 1.25) | 1/1 | 1/1 | 1/1 | 1/1 (fc: B-iv public-reason condition; (vi) "recorded as fired") | 1 | 8 |

(Seat 2 not required.) Working: (1) bounds — S6-k changes "1.15 ×", her recorded RG-F1 text, admissible only by an amendment where
the PRD calls for it; (2) M-a in bounds; with the closure path decided in (vi), every rating seat gives M-a 1/1; (3) the preamble is
served by both (M-a more sensitive ≈ ×1.16 vs ×1.25; S6-k cleaner calibration); no PRD goal points to S6-k, so the amendment is not
called for; (4) M-a lower sum. **DECISION D-B5 (iii): M-a.** kMacGrowthTriggerMs = ⌊1.15 × mean of the green macOS low-α medians of
the S2 runs⌋, computed by the test or a script from the GATE lines, never by hand; 4c states the detection factor in words: 1 +
0.15/s_L from the S2 split (≈ ×1.16 at s_L = 0.92).
**FM-TRIG.** Q: RG-1's decision file says the trigger is re-derived "(≥ 3 in-window runs)" but the applied 4c text has no window;
which applies? Answer: "Re-derived at the 07c re-pin over all green macOS low-α medians of the S2 runs, factor 1.15 unchanged; no
in-window qualifier (no macOS run is in window, fact 5; the window is a print under FM-GROWTH)." Rests on: preamble; NFR-4; RG-F1.
Options: M-a serves the preamble (a detector at ×1.16), strains it through a possible weather double answered by the X-d− closure
evidence; S6-k cleaner calibration, blunts detection, ratchets k; M-b undefined. Veto trigger: she may read a trigger firing on its
own calibration run as the K24 failure (→ S6-k). `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` —
only RG-1's "(≥ 3 in-window runs)" parenthesis; 1.15 kept. Debt: Seats 3, 5, 6 (later 1) — a weather double possible ([Hyp] ≈ 1 in
9 pairs), a defect closing only with evidence (vi); evidence 07d runs, Phase 13. Objection: Seats 3, 5 prefer S6-k; it falls at step
1, ratings tie. Reversal: a weather double on identical code shown to be weather by the closure evidence → board on S6-k at 07d; if
Seat 7 rates M-a 2, redo the ordering.

**(v) E1 — stands, worded (R1-39).** E1 2 < E3 3; E2, E4 max 2. **DECISION: E1.** "Each `cube100_lowalpha0.05_s0.3` entry (macOS,
Windows) closes under 4c (c) only if 14 × worst ≤ 30 s on every S2 run; otherwise it stays listed, 'closes at' phase-07d (scope
1)." Debt Seats 3, 6 later 1, repaid when 07d closes the entry. PRD lines: E1 serves the preamble and NFR-6 (closes only on
evidence); E3 same outcome, no closure path; E2 strains (closes on the median while a run is over 30 s); E4 strains (runner cause
not shown).

**(vi) MACTRIGGER on runs 42, 44 — revised: X-d− (item 4 dropped).** Q4: no AX38 4c text allows closure "by recording a
recalibration" (Seat 3 agrees, row 41).

| opt | S3 | S5 | S6 | S7 | max | sum |
|---|---|---|---|---|---|---|
| **X-d−** | 1/1 (fc: closure evidence in the 07d remedy line) | 1/0 (fc: X-a + its "either way" asks) | 0/1 | 1/1 (fc: "X-a plus a re-derivation") | **1** | **6** |
| X-d+ (item 4 as FM reading) | 1/1 | 1/0 | 1/1 (0/1 with its 2 conditions) | 1/1 | 1 | 7 (6) |
| X-a | 1/2 | 1/0 | 1/1 | 0/0 | 2 | 6 |
| X-b | 1/2 | 1/2 | 1/2 | 2/2 | 2 | — |

Working: X-d+ adds a closure 4c (d) lacks (out of bounds for a board decision; the PRD does not call for it since X-d− is at max 1);
X-a max 2; X-d− wins. **DECISION D-B5 (vi): X-d−**, applying 4c (d) as written: (1) runs 42 and 44 recorded as "two consecutive
runs over 2 172 ms, a defect under 4c (d)", remedy phase-07d, with the medians, flutterDev and ratio; a ledger row records K24
(fired, unread); (2) the (iii) trigger applied to 42, 44 and the S2 runs, printed; (3) the per-stage split printed on every OS on
the S2 runs, test-only (Q5: stage-hook timestamps ISM / solve / synthesis + assembly, plus a `sim::StagedBuild` replay separating
synthesis from assembly, labelled "replay"); (4) the 07d remedy line carries Seat 3's closure evidence inside (d): the macOS
per-stage split after the remedy at equal work pins; the macOS / Linux per-emitter synthesis ratio within 1.10 × the same runs'
flutter macOS / Linux ratio; the trigger in force not exceeded on two consecutive runs — no closure by recalibration; (5) MACTRIGGER,
OVER30S, GROWTH to `$GITHUB_STEP_SUMMARY` or `::warning::`, `pytest tools/ci` green. Debt: S3 / S6 07d may chase a non-defect (the
split and evidence limit it); S7 precedent held by "as written". PRD lines: X-d− serves the preamble (the macOS load signal read and
owned); X-d+ equally but amends her (d); X-a strains it (an unexplained macOS load could close silently); X-b strains NFR-6 trust.

## Answers to the interrogator's rows
03 B1-a 23, B1-c 22 · 04 13-3 scope 4 + R5 machine, remedy 13-1b · 07 K7 restated · 09 Seat 6 silent 3/3, vetoed in the reversal ·
10 B2-d 19 (with S4) · 11 items 11, 12 (`insertMs` per mode in 08-4; insertion in the 13-5 matrix) · 12 Seat 4 convened · 13 FM-B2 a
scope reading · 14 prepare-first cost and the 10 s line for every option; FM-10S · 15 NFR-2 dropped, preamble only · 21 D3-L3 with
|b−a| · 22 by value · 24 signal rated by Seats 1, 7; AX47 wording decided · 25 T-0 line · 27 sums; deferral as §3 · 28 D4-L1
restated · 31 C1 memory clause struck · 32 test-only (Seat 5 Q5) · 33 PRD lines C2, C4, C8 · 34 PRD lines · 35, 36 Seats 5, 3 rated;
ordering redone · 37 FM-TRIG reading · 38 E1 PRD lines · 39 wording · 41 item 4 dropped. Q1–Q5 answered in the decisions.

## Consolidated plan text for /fix-plan (only after SURVIVES)
1. **BUILD_PLAN AX38 (i) / cond. 12 (c) note:** "Cond. 12 (c) record re-instrumented in 07c-1b (D-B1 B1-b): the 05i / 07c-1 p99.9 on
   a normal-priority `sleep_for` thread is the 1st–2nd largest of 953–1 936 callbacks (R16), not a host audio thread (R4, R7, R8);
   07c-1b figures [runs]. A residual (overrun > period at 8 builders, none at 0) is re-measured in phase-13-3 scope 4 and on the R5
   Windows release machine; a miss opens 13-1b with B1-d first; never an instance cap." + §6 row.
2. **phase-13-3 scope 4:** add "and the 8-concurrent-builder sweep with 07c-1b's instrument (buffer 64; 0/1/2/4/8 builders; priority
   obtained and callback count printed), also on the R5 Windows release machine; a residual opens 13-1b with B1-d = a process-wide
   limit on running background builds ≤ hardware threads − 1, class (1) and offline exempt, slot taken before the gate and never
   under `stateMutex_`, `quiesce()` waking slot waiters."
3. **phase-08-4:** the AX38 (iv) binaural repeat runs 07c-1b's callback instrument in both modes in one CI run, printing callback
   count and priority obtained; re-reads the AX49 8-instance trigger (prepare-first total, FM-10S) in the heaviest mode and returns
   it to the board if it fires.
4. **AX48:** the FM-B2 answer sentence. Tests in phase-07c-1b scope 6: "a fresh `ScenePipeline`, no setState, prepare at 48 kHz on
   `medium_room`: `insertSolves == 1`, solve done before prepare returns; diffuse E_b bit-identical to a stage-1 solve; first IrSet
   at the first boundary, `fadeCount() == 0`; also prepare-then-setState (both VST3 orders, R17)"; "record (h) prints prepare-first
   totals (interleaved; batched) without a settle wait, beside the setState-first total". + §6 row + "Decided for Maisara" line.
5. **phase-07c-2:** "Instance insertion (FM-B2) takes 07c-2's stage-1 rules for statistical sources." and "The generated speech-like
   stimulus of `[ax47-midfade]` is a CI test signal only; 07c-2's self-ABX and the acceptance set use recorded speech (D-B3
   condition A)."
6. **AX47 Measurement:** replace with "Wet pink-noise and seeded speech-like renders (D-B3: generated, seed and parameters fixed and
   versioned; pauses starting and ending inside a fade) check, per 1 ms window aligned to the fade start (N_w = lround(0.001·fs)),
   per output channel, E_out ≤ (1 + N_w/L)²·max(E_a, E_b)·(1 + 10⁻⁵); a per-sample bound |o| ≤ max(|a|,|b|) + 8u·(|a|+|b|); a
   reconstruction to 8u·(|a|+|b|) (detects alignment errors where |b−a|/(|a|+|b|) > 8u·L); value equality with the endpoint outside
   the fade; fades from silence |o| ≤ |b|; the load's equal-power fade recorded." Phase-07c-1b scope 7 / AC 7: "speech" → "seeded
   speech-like". phase-08-3 and phase-09: "the AX47 mid-fade check per ear / speaker feed". Public records never say "tested with
   speech".
7. **AX49 Reversal:** "(trigger met 2026-11-12 … to the board in 07c-1b) → moved to phase-07d by D-B4 (C7′)."
8. **phase-07d, new criterion:** "8-instance Windows load at the rated corner ≤ 5 s on record (h), read on the larger of the
   prepare-first (interleaved, batched) and setState-first totals (FM-10S), with runner label and vCPU printed (R1). AX38 (iv)'s 10 s
   line read on the same total (run 42 macOS keyed 10 206 ms; prepare-first ≈ 11.4–13.6 s est.); an exceedance after 07d goes to the
   decider for Maisara before the first release." Candidates in order: **C9** (process-wide single-flight insertion cache keyed by
   canonical scene + `tailSeed`, fs, P, `engineKey()`, platform — any scene, NFR-8; `shared_ptr<const>`; test `insertSolves +
   insertCacheHits == 1` and bit-identity; TSan with 8 concurrent insertions); **C1** (transient shared spectra cache keyed by
   filterbank + FFT size, freed when unused; its AX38 (i) / (ii) accounting decided in 07d's loop; W1/W2 "no cache credit"); **C6**
   (as round 1); **C2** only on the gate's pool with C6; **C4** only as shared per-(emitter, outputIndex) unit decays, memory
   measured; **C3** only as C3-pb (L_p,b ≥ t_mix,e,max + 0.312·T60_b + 0.1 s); **C5** only with Seat 1's ABX, Seat 2's equivalence
   test, Seat 9's BRAS condition, before Phase 12. Also in 07d: insertion unit decays for every outputIndex (Seat 4 (i)) — output-1
   built by the builder after the first IrSet unless the current mode needs two outputs; whether a mode switch inside the settling
   window plays an interim decided with Seats 3, 4 and asserted in 08-3; any remedy scales with outputs; 07d lands before 08-4
   freezes goldens; the macOS (d) defect from D-B5 (vi) with its closure evidence (item 9d).
9. **AX38 4c:** **(a) Growth check (FM-GROWTH; replaces "in-window on Linux and Windows, printed on macOS"):** "On Linux and Windows
   the run's low-α / flutter median ratio is asserted ≤ 1.10 × the mean ratio of the ≥ 3 green S2 runs on that OS; printed only on
   an OS whose S2 ratio max/min exceeds 1.10 (macOS). Each run prints the ratio and its margin, and a WARNING (not asserted) below
   mean / 1.10. The absolute low-α median vs the S2 mean prints GROWTH WARNING on every OS, to `$GITHUB_STEP_SUMMARY`, counted per
   run in §0. Flutter 14 × worst ≤ 30 s stays asserted. Blind spot, in words: a slowdown common to both scenes; the uniform
   synthesis slowdown at which the ratio reaches 1.10 is f = [1.10(1−s_F) − (1−s_L)]/(s_L − 1.10·s_F) from the S2 split, value [f]
   (≈ ×1.28 at s_L 0.92, s_F 0.51); it is printed and asserted only at 30 s and on the Phase 13 release machines. The ratio reference
   is re-pinned from ≥ 3 green runs with a CHANGELOG reason at 07c-2 (W_max change), at 07d after its remedy, and whenever the
   restore path changes; f > ×1.4 sends B-iv+ to the board at the 07d re-pin. The ±5 % flutter window is a printed S2 mean only."
   Public reason sentence as in FM-GROWTH; `AMENDS` line. **(b) Solve baselines ((iv″))** as decided, PROVISIONAL with the dated
   exit. **(c) macOS trigger (M-a, FM-TRIG):** ⌊1.15 × mean of the green macOS S2 low-α medians⌋, computed by script, detection
   factor 1 + 0.15/s_L in words; no in-window qualifier. **(d) MACTRIGGER defect entry (X-d−)** with the closure evidence in
   phase-07d. **(e) E1 wording.** **(f)** MACTRIGGER / OVER30S / GROWTH to the step summary or `::warning::`. + §6 row and a
   CHANGELOG reason (scope 1).
10. **Ledger:** rows for D-B1 … D-B5, FM-B2, FM-10S, FM-GROWTH, FM-TRIG, K24 ("MACTRIGGER fired on 42, 44, unread").
11. **phase-08-3 / 08-4 (D-B2 debt):** 08-3 asserts the first IrSet at insertion carries the per-ear seeds and decorrelation, beside
    the `[pipeline]` insertion test; 08-4 prints `insertMs` per mode (omni, binaural, stereoSpeakers) and returns it to the board if
    binaural exceeds a host or validator limit.
12. **phase-13-5 scope 3:** "The matrix's load column records instance-insertion time per host (cond. 11 trace, FM-B2); a hang,
    not-responding state or limit at insertion returns FM-B2 to the board (B2-b dry or B2-d only; B2-b silent vetoed by Seat 6)."

## Summary
| id | decision | state | worst-off | sum | conf. | PRD bound | corpus | reversal |
|---|---|---|---|---|---|---|---|---|
| D-B1 | B1-b re-instrument | stands (corrected) | S5, S7 1 now | 5 | high | FR-3D-5/6, FR-SIM-7, AX38 (i) | — | INSTRUMENT INVALID; overrun with clean floor |
| D-B2 | B2-a″ + FM-B2 + FM-10S | revised / for Maisara | S5, S8 1/1 | 8 | medium | preamble, NFR-1, NFR-6, NFR-8, AX38 (iv) | — | host limit or hang → B2-b dry / B2-d only |
| D-B3 | W-a + companions; s1 seeded speech-like | stands (corrected) | S4 1 later | 1 / 0 | high (signal medium) | NFR-1, FR-SIM-6 | Vorländer §4.3 Eq. 4.15 | false red on correct code |
| D-B4 | C7′ → 07d (C9 first) | stands (corrected) | several 1 | 13 | medium | preamble, NFR-6 | — | 07d cannot reach 5 s |
| D-B5 (i) | S2 | stands | S7 1 now | 1 | high | NFR-6 | — | — |
| D-B5 (ii) | B-iv (FM-GROWTH) | for Maisara | all 1/1 | 10 | medium | preamble, NFR-6, NFR-4 | — | f > ×1.4; false red |
| D-B5 (iv) | (iv″) + dated exit | for Maisara | S2 1/1 | 5 | medium | NFR-6 | — | exit unmet at 07d |
| D-B5 (iii) | M-a + FM-TRIG | revised / for Maisara | S3, S5, S6 1/1 | 6 | medium | preamble, NFR-4 | — | weather double shown weather |
| D-B5 (v) | E1 | stands (worded) | S3, S6 1 later | 2 | high | preamble, NFR-6 | — | — |
| D-B5 (vi) | X-d− | revised | S3, S7 1/1 | 6 | medium | preamble | — | 07d evidence |

Challenges to settled decisions: none beyond the FOR MAISARA answers. Decided for Maisara (once they survive): FM-B2 (adding an
instance computes its default room in full before it plays, 0.15–0.43 s, never silent or dry; preamble, NFR-1, NFR-8, scope reading
of AX48 FM-3′; Seats 5, 8 gave most, get the cost counted, C9 first in 07d, checks in 08-4 and the 13-5 matrix; amends nothing);
FM-10S (the 10 s load line counts the slower host call order; AX38 (iv), preamble, NFR-6; amends nothing); D-B1 (measure the
deadline properly first; preamble, FR-3D-5); D-B3 (1 ms windows + exact reconstruction on a generated, fixed, named speech-like
signal; NFR-1, FR-SIM-6); D-B4 (the 8-stem load fix to 07d, slower host order counted, hard line before release; preamble, NFR-6);
FM-GROWTH (restore growth judged by the within-run low-α / flutter ratio; blind spot written down; absolute check returns at Phase
13; solve baselines provisional until a dated exit; preamble, NFR-6, NFR-4; `AMENDS her decision of 2026-11-10: "I accept the
board's answer by definition."`); FM-TRIG (macOS trigger keeps 1.15 × over all green re-pin runs, no in-window qualifier; preamble,
NFR-4; `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` — only the "(≥ 3 in-window runs)"
parenthesis); D-B5 (i), (v), (vi) (fresh runs; entries close only if passing every run; the fired macOS trigger a defect for 07d
closing only on measured evidence; preamble, NFR-6). NEEDS MAISARA: none new (FM-D1-S3 already with her). Optional parallel
question: Seats 5, 6, 7 rate B-iv+ (changes (ii) only if all three ≤ 1/1).
