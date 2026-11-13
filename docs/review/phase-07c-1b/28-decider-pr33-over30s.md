# 28 — Decider: PR #33 run 43427854710, the macOS OVER30S and the single MACTRIGGER (P07C1B-R1)

2026-11-13, corpus c1b171f (no acoustic fact load-bearing; arithmetic on GATE lines and plan text). Saved by the orchestrator from the
decider's report. A reading of decided text (AX38 4c (a), (c), E1, FM-TRIG, X-d−); seats recorded not required (neither option changes
an assertion, a CI behaviour or anything a user hears: the macOS low-α check is print-only listed or not; "14 × worst above 30 s" is
"Printed with WARNING, never asserted on hosted runners"). NEEDS MAISARA: none. Challenges to settled decisions: none.

**Run facts** (PR #33 CI run of record 43427854710, head ac54495; src/ identical to 9717a58; all jobs green): macOS low-α ratio 4.626
(1.48 × r̄ 3.1203), PRINT-ONLY, S2-PROVISIONAL, 14 × worst 30.50 s, median 1 851 ms > trigger 1 703, warnings RATIO GROWTH OVER30S
MACTRIGGER; macOS flutter median 400 ms, flutterDev −15.8 %, 6.78 s asserted(30s) pass. Preceding macOS run: S2 43412038058, 1 586 ms.
Windows low-α ratio 2.501 ASSERTED pass (≤ 2.783), 19.54 s; Linux 2.380 PRINT-ONLY, GROWTH, 21.58 s. Fingerprint hash = pin on all
three; 253/253 ctest on Linux and Windows.

**Answers.**
1. The macOS `cube100_lowalpha0.05_s0.3` entry stays closed; run 43427854710 is named in the PR and recorded under X-d−. Rule (a) applies
   to a pin's recorded values, not to one later print (precedent: Windows' strict 29.50 s on run 42924781618 did not list it; it was
   listed only when its strict assertion broke at 36.73 s, under (d)). A closed entry is re-listed at the next re-pin (07c-2, or 07d
   scope 8) when any of that pin's runs prints 14 × worst > 29.1 s. Re-listing now would duplicate X-d− (same scene, OS, remedy, closing
   phase), change no assertion on hosted macOS, and need a `tests/` push after the PR opened that is neither a CI fix nor a review
   request (CLAUDE.md, Maisara 2026-11-08).
2. The single MACTRIGGER is a print under FM-TRIG (a defect needs two consecutive runs above 1 703 ms; the preceding one was 1 586 ms);
   not an S2 run, so "If an S2 run exceeds the trigger it helped set" does not fire. Added as evidence to X-d− / phase-07d scope 7 (the
   excess recurs on the S2 restore path, not only on 07c-1 code). If the next macOS run on the same restore path also exceeds 1 703 ms,
   the pair joins X-d− through `/fix-plan` (no re-run).
3. AC 2 unchanged and met ("on the runs of scope 1" = the S2 runs; E1 met on them; `listed` flags false / false match the register).

**FOR MAISARA P07C1B-R1** (a reading; amends nothing): kept closed and named, re-listed at the next re-pin if any of its runs is above
29.1 s; the single MACTRIGGER a print, added as evidence to the macOS defect owned by phase-07d. Rests on NFR-4, the NFR preamble, NFR-6;
4c (a), (c), E1, X-d−. Seat 5 gives most (no register line for one > 30 s print on a shipping OS); it gets back the open X-d− defect, the
07d re-pin re-test and Phase 13's strict 30 s. Veto risk: NFR-4 makes macOS a shipping platform and a closed entry next to a 30.50 s print
looks healthier than the runner; holds because X-d− stays open on this exact scene and OS with a 07d remedy and the run is named in the PR
and the plan.

**Texts (`/fix-plan`).**
- **T1 — AX38 4c**, after "…re-listing it is a `/fix-plan` reading under (a).": "*Reading (phase-07c-1b, 2026-11-13, decider P07C1B-R1;
  amends nothing):* (a) is applied to a pin's recorded values, not to one later print (as Windows' strict 29.50 s on run 42924781618 did
  not list it); a closed entry is re-listed at the next re-pin (07c-2, or 07d scope 8) when any of that pin's runs prints 14 × worst >
  29.1 s. First instance: PR #33's run 43427854710 (head ac54495; src/ as 9717a58): macOS low-α 14 × worst 30.50 s, median 1 851 ms,
  ratio 4.626 (1.48 × r̄ 3.1203), flutterDev −15.8 %; RATIO, GROWTH, OVER30S and MACTRIGGER printed; the entry stays closed, the run is
  named in the PR and recorded under X-d−."
- **T2 — X-d− paragraph**, inside the parenthesis after "…no S2 run exceeds it", before its ")": "; PR #33's run 43427854710 (head
  ac54495; restore path as the S2 runs) prints MACTRIGGER once (macOS low-α median 1 851 ms > 1 703 ms; the preceding macOS run, S2
  43412038058, 1 586 ms): one run, a print under FM-TRIG, not a new (d) defect; evidence for phase-07d scope 7 that the excess recurs on
  the S2 restore path; if the next macOS run on the same restore path also exceeds 1 703 ms, the pair joins this defect through
  `/fix-plan` (no re-run)"
- **T3 — phase-07d scope 7**, appended: "Evidence added at 07c-1b (AX38 4c X-d−): PR #33's run 43427854710 (head ac54495, restore path as
  the S2 runs): MACTRIGGER once (low-α median 1 851 ms), ratio 4.626 (1.48 × r̄), flutterDev −15.8 %, 14 × worst 30.50 s (OVER30S on the
  closed entry; E1 reading P07C1B-R1): a print, not a new defect."
- **T4 — phase-07d scope 1**, replacing "a later OVER30S is handled as AX38 4c E1 states." with "a later OVER30S is handled as AX38 4c E1
  states (reading P07C1B-R1: named in the PR; re-listed at the next re-pin if any of its runs prints > 29.1 s; first instance run
  43427854710, macOS 30.50 s)."
- **T5 — §0 row 05h** ("latest figures and the counts"), appended: "PR #33 run 43427854710 (ac54495): low-α 14 × worst Linux / macOS /
  Windows 21.58 / 30.50 / 19.54 s; ratio 2.380 (print-only) / 4.626 (print-only) / 2.501 (asserted, ≤ 2.783, pass); WARNING: Linux
  GROWTH; macOS RATIO, GROWTH, OVER30S, MACTRIGGER."
- **T6 — PR #33 description:** the run under WARNING runs with T5's figures; P07C1B-R1 under "Decided for Maisara".

**Future debt (Seat 5, as read; unrated):** one macOS print above 30 s unlisted until the next pin; undo one `/fix-plan` line plus a
`listed` flip at a re-pin; evidence the 07c-2 / 07d re-pin runs and 07d scope 7's closure test; repaid at the 07d re-pin or Phase 13.

| id | decision | state | worst-off | sum | confidence | PRD bound | reversal |
|---|---|---|---|---|---|---|---|
| P07C1B-R1 | keep closed, name run, re-list at next pin if any run > 29.1 s; single MACTRIGGER a print, added to X-d− / 07d scope 7 | reading, for Maisara | none (0/0) | 0 | high | NFR-4, NFR-6, preamble | a re-pin run > 29.1 s; a second consecutive macOS median > 1 703 ms |
