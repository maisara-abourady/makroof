# 64 — Decider: DECISION RG-1, the restore-gate form on shared runners (file 56; Seats 2, 3, 5, 6, 7: files 62, 58, 57, 61, 60)

phase-05h (session 2). Verbatim decider output (the orchestrator saved it). File 63 is the researcher's RQ-RG dossier (in flight at decision time; the premise stated).

# Decider — DECISION RG-1: the restore-gate form on shared runners (file 56)

Corpus `c1b171fe649f` (no acoustic claim; the matter is a CI assertion form). PRD digest, restatement, options and the nine-row convening table: as my round-1 hand-back. Convened: Seats 2, 3, 5, 6, 7 (files 62, 58, 57, 61, 60). Not required: 1, 4, 8, 9 (no option touches audio, the delivery chain, the producer's wait or a room). Researcher file 63 absent: **premise stated** — no external statement on hosted-runner timing reproducibility is used; step 1 and the cells rest on the in-repo CI record.

## Knowledge inventory (final)
| id | what | source | status |
|---|---|---|---|
| K1 | identical code: low-α restore median ×1.63 Linux / ×1.43 Windows / ×1.23 macOS between runs; low-α/flutter same-run ratio ±5–8 % | file 56 table (CI) | known |
| K2 | one-run baseline × 1.10 on the ratio would have been red on run 42935789745: Windows 3.08/2.64 = 1.17, Linux 3.24/2.85 = 1.14 | Seats 3 §1, 5 §3; redone | known |
| K3 | ratio means Linux 3.05 / Windows 2.83 (measured rows); pooled CV 5.4 %; k = 1.16 (t₀.₉₉ prediction bound), 1.20 pinned | Seat 5 (ii) | known (n = 4–5, stated) |
| K4 | flutter non-diffuse build 889 ms = synthesis 536 (60 %) + ISM/mix 332; low-α 3 339 ms, synthesis ≈ 95 % | file 56 last section (measured) | known |
| K5 | ratio under a uniform synthesis slowdown d: (1 + 0.95d)/(1 + 0.60d); = 1.20 at d ≈ 0.87 → fires only at ≈ ×1.9; a ×2 solve regression moves the low-α median +4.9 % and lowers the ratio | my working on K4; Seat 3 §1 | known (derived) |
| K6 | solve work nearly equal: W_pilot+W_final 5.70 M flutter vs 6.04 M low-α; ns/evaluation ratio 0.58 / 0.57 / 0.58 on the three OSes | Seat 2 from code L337–342; file 1 §3 via Seat 3 | known |
| K7 | in-window low-α medians: Linux 2 043 / 2 092 (2.4 %), Windows 2 000 / 2 056 (2.8 %); macOS low-α ×1.23 while its flutter sits 474–494 ms | Seat 5 (iii), file 56 | known |
| K8 | a ±7 % flutter window evaluates the same rows as ±10 %: Linux 716, 693 in (ref 701), 514, 880 out; Windows 757, 752 in (ref 737), 626, 622, 927 out: 8 of 13 rows, macOS print-only | my working from file 56 with Seat 5's refs | known |
| K9 | ci.yml: Benchmark L404 precedes pluginval L425 / auval L434; first `if: always()` L472 | from the code (verified) | known |
| K10 | precedent "a print, never a CHECK with a timing threshold on shared runners" | BUILD_PLAN L139 AX38 (i) (verified) | known |
| K11 | Phase 13 release-machine strict re-check exists | AX41 / AX38 4c | known |

## The final form **(x″)** (composed from the five seats' conditions)
1. **Asserted every run, runner-free:** W_pilot / W_final exact pins and AX41 ratio ≤ 1.02 (existing L331, L343–344); the solve's per-evaluation ns ratio low-α / flutter on the same run ≤ 1.10 × 0.58 (Seat 3 c2, Seat 5 iv); the synthesis **work** pin per gated scene: unit-decay samples per emitter (1 152 000 low-α, 377 517 flutter at 96 kHz) and the `BandNoiseGenerator` IFFT count, asserted exactly (Seat 2 §6, Seat 3 c1).
2. **Asserted, timing:** the flutter scene's 14 × worst ≤ 30 s on every OS (headroom ≥ 2.3×, Seat 5 iv); the low-α **absolute median ≤ 1.10 × `baselineMedianMs` on Linux and Windows only, and only when |flutter median / `flutterRefMs` − 1| ≤ 7 %** (Seat 3 c (e): ±7 % with 1.10; Seat 5 iii: x64 only; K8: no evaluated row lost). Otherwise `NOT EVALUATED (runner: flutter +N %)`; macOS `reported only` until Phase 13 (K7).
3. **Printed with `WARNING`, never asserted:** low-α/flutter ratio > 1.20 × `baselineRatio` (Seat 5 ii: a CHECK that cannot fire below ×1.9 is a defect of the gate); 14 × worst > 30 s; absolute median > 1.10 × baseline when not evaluated or on macOS; the §5 (c) "passes 30 s" line; the 29.1 s strict/listed rule and the register entries (recorded value, remedy, closing phase) stand as text.
4. **One machine-readable line per OS/scene per run**, Seat 6's four fields; §0 row 05h carries the latest figures and the counts (warnings, not-evaluated), a run with a WARNING is named in the PR (Seats 3 c3, 6 §6).
5. **Baselines** (Seat 5 v): `flutterRefMs` and `baselineRatio` = mean of the measured runs on file per OS (Linux 701 ms / 3.05; Windows 737 / 2.83; macOS 484 / 3.75, measured rows only); `baselineMedianMs` = mean of in-window runs (Linux 2 068, Windows 2 028; macOS 1 889, print only). Never a red or out-of-window run as a baseline. Re-pinned only when the restore path changes (W_max / n*_max re-derivation, 07c's synthesis move): one run pins PROVISIONAL (printed, not asserted), the mean of ≥ 3 runs re-pins with a CHANGELOG reason naming the code change.
6. **CI:** `if: always()` on the pluginval and auval steps (every seat).
7. **Later:** strict 30 s and 1.10 growth re-enforced on all three OSes on Phase 13's release machines (AX41); phase-07c condition 9's packet repeats file 7's split timer on one named local box before sizing its interim rules (Seat 5 vi); release machines bought once, no standing runner (Seat 7: a Phase 13 Raise item, a person's purchase).

## Tension map (final form; each seat's own words)
| seat | now / later | reason |
|---|---|---|
| 5 | 0 / 1 | own cell for "(x′) = (f) with the ratio CHECK demoted to a print, Seat 3's two pins, absolute in-window on x64, baselines per (v)"; ±7 % *(read from its (iii): the same rows evaluated)*; later "a record nobody reads … mitigated by a machine-readable summary line and Phase 13" |
| 3 | 1 / 1 | round 2: "(x′) now 1 / later 2 … conditions that move (x′) to 1 / 1": c1 pins, c2 ns ratio, c3 WARNING line + §0 count + PR — all in the form |
| 2 | 1 / 1 | "(f) 1 with the pin … (x) 1 with the pin"; condition: pinned synthesis work count, k from the spread, one machine-readable line — all in |
| 6 | 0 / 0 | "(f) 0 … (x) 0" now; "(x)/(e)/(f) later 1 → 0: every run prints one machine-readable line … four fields … §0 carries the figures" *(read from §6, met)*; B6 (i): the producer's guarantee weakened "0 on all four" |
| 7 | 1 / 1 | "(f) 1 / 1 … condition: k and the band derived, not 1.10 by analogy" (K3, K8); `if: always()` in |
| 1, 4, 8, 9 | 0 / 0 | not required (table) |

Other options, max cell: (a) 3 (Seat 5 now; 2/2 from Seats 2, 3, 6, 7); (b) one-run × 1.10: 2 (Seats 5, 7); (b) conditioned: max 1, sum 10 (5: 1/1, 3: 1/1, 2: 1/1, 6: 1/1, 7: 1/1); (c): 2 later (Seats 2, 3, 5, 6, 7); (e): 2 later (Seats 2, 5, 6, 7); (x) bare: 2 later (Seats 2, 3); (d): out of bounds; (g): 2 later (Seat 5).

## Ordering
1. **Bounds:** (d) out (one-phase rule). Every other option keeps W_max, range, formulation ((v)(d)) and H1-F1's convention (30 s printed every run, asserted at the flutter scene and on release machines). (x″) amends (v)(a)–(b) → `FOR MAISARA` below.
2. **Veto:** (a) dropped (Seat 5: 3 now, "each red masking pluginval/auval on that OS", K9).
3. **Worst-off:** (x″) max 1; (b)-conditioned max 1; all others max 2.
4. **Compose:** (x″) is the composition (one per round), rated from the seats' conditions where marked.
5. **Sum:** (x″) 6 < (b)-conditioned 10.
6. **Reversibility:** a test edit either way; (x″) keeps the REQUIRE lines in place (guarded), so re-enabling the absolute CHECK at Phase 13 is a flag flip.
7. **Decide: (x″).** Confidence **medium** (two cells read from conditions; the IFFT counter is a code fact the orchestrator establishes; RQ-RG-1 absent). **Reversal:** Phase 13's release-machine run (entries close, or the absolute CHECK returns on named hardware); 07c's split-timer packet; a §0 count showing the in-window x64 bound red by runner (then macOS's form extends to x64); file 63 contradicting the premise.

## FOR MAISARA RG-F1
**Question.** May D-H1 (v)(a)–(b)'s absolute timing assertions become guarded or printed figures on GitHub-hosted runners, with runner-free work pins asserted instead, until Phase 13's release machines re-enforce them strictly?
**Answer (exact plan text, phase-05h §5 "Blocking" (a)–(b) and AX38 4c's register paragraph).** "On GitHub-hosted runners the restore gate asserts what is runner-independent and prints what is not. **Asserted every run:** the exact W_pilot / W_final pins and realised work ≤ 1.02 (AX41); the solve's per-evaluation time ratio low-α / flutter on the same run ≤ 1.10 × 0.58; the synthesis work pin per gated scene (unit-decay samples per emitter and the `BandNoiseGenerator` IFFT count, exact); 14 × worst-of-10 restore ≤ 30 s at the flutter scene on every OS; and, on Linux and Windows only, median-of-10 low-α restore ≤ 1.10 × the pinned baseline median when the run's flutter median is within ±7 % of its pinned reference, else `NOT EVALUATED (runner)`. **Printed with WARNING, never asserted on hosted runners:** the low-α/flutter restore ratio above 1.20 × its pinned ratio; 14 × worst above 30 s; the absolute median above 1.10 × baseline where not asserted (macOS until Phase 13); the §5 (c) 'passes 30 s' line. The register entries (Linux 30.27 s, macOS 33.40 s, Windows 36.73 s; remedy phase-07c conditions 9–10; closing phases unchanged) stand. One machine-readable line per OS/scene per run; §0 row 05h carries the latest figures and the counts; a WARNING run is named in the PR. Baselines: `flutterRefMs` / `baselineRatio` the mean of the measured runs on file per OS (Linux 701 ms / 3.05, Windows 737 / 2.83, macOS 484 / 3.75; runs 42909003931, 42924781618, 42935789745, 42949252041, Windows also 42942694523); `baselineMedianMs` the mean of in-window runs (Linux 2 068, Windows 2 028; macOS 1 889 print only); never a red or out-of-window run; re-pinned only when the restore path changes, one run PROVISIONAL, ≥ 3 runs with a CHANGELOG reason. A broken assertion is a defect under (d): no re-run, no W_max cut, no range change, no seam. `ci.yml` runs pluginval and auval `if: always()`. Phase 13 re-enforces the strict 30 s and the 1.10 growth bound on all three OSes on the release machines (AX41); phase-07c condition 9's packet repeats the file 7 split timer on one named local box before sizing its interim rules." (c)–(d) kept with "growth bound" → "the asserted figures above"; phase-05i scope 3 carries the re-pin rule; phase-13 gains the split-timer and release-machine lines.
**PRD ids and decisions.** L101 ("but … usable in a DAW session"), NFR-2, NFR-4 (three OSes' host conformance), NFR-1, NFR-6, L20; her acceptance 2026-11-10; D-H1 (v), H1-F1, H1-F2 (file 19).
**Reasoning.** The 30 s convention bounds a user-facing wait (L101); a CHECK red on 2 of 5 identical runs measures the runner (K1) and each red removes pluginval/auval evidence on that OS (K9, NFR-4). The plan already prints timing on shared runners (K10) and already names release machines as where the bound is enforced (K11). What a hosted runner can see is work and in-window growth (K6, K7); what it cannot see below ≈ ×1.9 (K5) is printed, not pretended. NFR-1 untouched: no cut.
- *(x″) chosen:* serves L101 (wait measured every run, judged where measurable), NFR-4, NFR-1.
- *(a):* the letter of "blocking"; strains NFR-4 (K9) and CLAUDE.md's culture (red by weather).
- *(b) conditioned:* same PRD standing, more tension (sum 10), blind to the solve (K5).
- *(c), (e):* keep an absolute CHECK that cannot fire or hides the uniform case; strain the culture.
- *(d):* Phase 13's purchase, not 05h's.
**What would make her veto it.** The reading that "a blocking CI gate" (her acceptance of Challenge 1) means an absolute 30 s CHECK on every hosted run now, and that guarding it until Phase 13 removes the pressure to shorten the 100 m build (the pressure is the register, "07c next" and Phase 13, Seat 2 B2 (i)).
`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AQ10 amended (1) and AX38 4c: D-H1 (v)(a)–(b) as above; phase-05h §5 "Blocking"; phase-05i scope 3; phase-07c condition 9 packet; phase-13.)

## Exact test form (orchestrator)
- `GateEntry {scene, os, recorded14xS, listed, baselineMedianMs, baselineRatio, flutterRefMs, absoluteAsserted}`. Entries: flutter × 3 OSes (strict 30 s, as today); low-α Linux `{30.27, true, 2068, 3.05, 701, true}`, Windows `{36.73, true, 2028, 2.83, 737, true}`, macOS `{33.40, true, 1889, 3.75, 484, false}`. Named constants with provenance: `kGrowth 1.10`, `kGuardPct 7`, `kRatioWarn 1.20`, `kNsPerEvalRef 0.58`, `kNsPerEvalBound 1.10`, `kUnitDecaySamples96k {1152000, 377517}`, `kSynthIfftCount {per scene, read from a test-build counter on the generator; pinned on the first run with a CHANGELOG reason}`.
- `REQUIRE`: L331, L343–344 unchanged; flutter `fourteen <= 30.0`; low-α: `nsPerEvalLowAlpha / nsPerEvalFlutter <= 1.10 * 0.58`, `unitDecaySamples == pinned`, `ifftCount == pinned`; `if (entry->absoluteAsserted && std::abs(flutterMedian / entry->flutterRefMs - 1.0) <= 0.07) REQUIRE(rs.median <= 1.10 * entry->baselineMedianMs);`. L392 and L399 (low-α) removed; the flutter median kept in a static for the ratio.
- Summary line: `05h-records GATE os=<OS> scene=<scene> ratio=<r> ratioWarnAt=<1.20*b> x14worst=<s> median=<ms> growthBound=<ms> fullRebuildMedian=<ms> status=<asserted|reported-only|not-evaluated(runner,flutter+N%)> warnings=<none|RATIO|GROWTH|OVER30S|PASSES30S>`.
- `ci.yml`: `if: always()` on the pluginval (L425) and auval (L434) steps; `test_ci_workflow.py` updated if it pins step conditions. Constants recorded in `tests/golden/CHANGELOG.md` (not a golden).

## Load-bearing claims
D-RG-L1 = K1 (CI record). L2 = K2 (arithmetic shown). L3 = K9 (code). L4 = K10 (plan). L5 = K4 + K5 (measured split; working shown): why the ratio is a WARNING. L6 = K6 (code): why the ns/eval ratio and work pins are runner-free. L7 = K7, K8 (data; working): why 1.10 / ±7 % / x64 only. L8 (seats' costs): the cells above. L9 (product): L101, NFR-4, NFR-1, K11.

## Future-debt register (x″)
| seat | commits later phases to | undoing costs | evidence | repaid when |
|---|---|---|---|---|
| 5 (later 1) | a record that must be read; strict re-enforcement on release machines | a flag flip per entry | Phase 13 run; §0 counts | Phase 13 |
| 3 (later 1) | blind to a constant-factor synthesis slowdown < ≈ ×1.9 on hosted runners; 07c sizes on the split-timer packet | — | 07c condition 9 packet | 07c |
| 2 (later 1) | per-op slowdown at unchanged count invisible until Phase 13; re-pin at 07c (both scenes change) | one constant + CHANGELOG | 07c; Phase 13 | 07c / Phase 13 |
| 7 (later 1) | one re-pin at 07c; the §0 explanation once; release machines bought once (Raise item) | — | 07c; Phase 13 | Phase 13 |

**Strongest objection.** Seat 3's later 2 on the bare (x′): "the only asserted timing figure cannot see either term below ×1.5". It holds down to 1 by its own conditions, but the residue is real: a uniform ×1.3 `make` slowdown in 07b reaches CI only as a WARNING (K5). It is accepted because no same-run form on a hosted runner separates it from runner speed (Seats 2, 3, 5 agree), the printed line and §0 count make it visible, and 07c's packet re-measures on a named box before sizing.

## Summary
`RG-1 | (x″): runner-free pins + ns/eval ratio asserted; flutter 30 s strict; low-α absolute 1.10× asserted in a ±7 % flutter window on x64 only; ratio/30 s/macOS printed with WARNING; mean baselines; if: always(); Phase 13 strict | proposed (for Maisara) | Seats 2, 3, 7 (1 / 1) | 6 | medium | L101/NFR-2, NFR-4, NFR-1, (v)(d) | none needed | Phase 13 release-machine run; 07c split-timer packet; §0 count`

**Decided for Maisara.** RG-F1: on shared CI machines the gate judges the work it can measure exactly and the restore's growth only when the machine is at normal speed; everything else is printed with a warning and judged on the release machines at Phase 13 (L101, NFR-2, NFR-4, NFR-1). Seat 3 gave the most (a synthesis slowdown under ≈ ×1.9 reaches CI as a warning only) and gets 07c's split-timer packet and the Phase 13 strict check back. `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."`

**NEEDS MAISARA:** none. (Buying release machines for Phase 13 is a person's purchase, raised as a Phase 13 item with Seat 7's figures, not a decision for the loop.)

Files: /home/user/makroof/docs/review/phase-05h/57-seat5-restore-gate-runner-variance.md, 58-seat3-…, 60-seat7-…, 61-seat6-…, 62-seat2-…, 56-orchestrator-… (last section), /home/user/makroof/.github/workflows/ci.yml L404–472, /home/user/makroof/tests/unit/test_diffuse_records.cpp L331–399, /home/user/makroof/docs/BUILD_PLAN.md L139.
