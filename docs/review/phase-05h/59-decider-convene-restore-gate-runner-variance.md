# 59 — Decider: convening round on the restore-gate register form against shared-runner variance (file 56)

phase-05h (session 2). Verbatim decider output (the orchestrator saved it). Seats convened: 2, 3 (file 58), 5 (file 57 + B5 follow-up), 6, 7; researcher RQ-RG-1–3.

# Decider — restore-gate register form vs shared-runner variance (file 56): CONVENING ROUND

Corpus `c1b171fe649f` (not needed this round: no acoustic claim; the matter is a CI assertion form). Files 57/58 absent at hand-back time (globbed twice), so I convene and do not decide.

## PRD digest
- **For whom:** producers/DJs on macOS+Windows in any DAW (L17, L20); no spatial-audio knowledge assumed.
- **Outcome:** a designed space rendered accurately (NFR-1), usable in a DAW session (L101), project restores exactly (NFR-6).
- **Hard constraints here:** NFR-1 (no accuracy cut: D-H1 (v)(d) "no W_max cut after pinning, no range narrowing, no seam"); NFR-2/L101 (heavy latency allowed "but … usable"); NFR-6; NFR-8; AX5; AQ10 amended (1) and AX38 4c = her recorded decision (2026-11-10, "I accept the board's answer by definition"), amended only by `FOR MAISARA`; H1-F1's 14 × t_restore ≤ 30 s convention stands; the one-phase rule (a new runner is not 05h's; a test+plan edit of 05h's own gate is); CLAUDE.md step 6 (`ci ok` on three OSes is the `done` evidence).
- **Verification culture:** every DSP behaviour auto-checked; a gate that is red by design, or that cannot fire, is a defect of the gate; tolerances follow from the requirement and the statistics, never loosened to pass.
- PRD is silent on CI mechanics; it speaks only through L101/NFR-2 (a bounded synchronous restore) and NFR-1 (no cut to pass).

## 1. Restatement
**Matter:** how the AX38 4c blocking restore gate (D-H1 (v) W-x′; `test_diffuse_records.cpp` L375–401, `kGateRegister` L68–85) is asserted on shared CI runners so that it is "never red by runner speed, the defect never hidden" (file 19 L104; H1-F2), at the pinned W_max 3.05 M, inside (v)(d). Depends on it: `ci ok` for every PR of 05h/05i/07b/07c; phase-05h §5 "Blocking" (a)–(d); AX38 4c's register paragraph; phase-05i scope 3.

**Facts from the CI record (file 56 table; from the code/CI, not corpus):** identical code, 5 runs; low-α restore median moves ×1.63 Linux (1 666→2 716 ms), ×1.43 Windows, ×1.23 macOS; the low-α/flutter same-run ratio moves Linux 2.85–3.24, Windows 2.64–3.08, macOS 3.54–3.92. Runs 9 and 10 each red on one OS by the gate alone. The 1.10× absolute growth bound (2 247 ms Linux) sits inside the runner's own spread.

**Options:**
- **(a)** keep the form (absolute strict / absolute 1.10× median growth; red = defect, no re-run).
- **(b)** runner-normalised growth bound: median(low-α restore) / median(flutter restore, same run) ≤ k × pinned ratio per OS; absolute figures printed as records; 30 s line reported not asserted on shared runners; strict form kept for Phase 13's release machines.
- **(c)** absolute bound, baseline per OS = slowest green run on file (Linux 2 716 → 2 988 ms).
- **(d)** dedicated/self-hosted runner — **out at step 1** for 05h (one-phase rule; file 56 "not 05h's"); recorded for Seat 7 / Phase 13 only.
- **(e)** absolute bound asserted only when the run's flutter median is within ±10 % of its pinned value; otherwise printed "not evaluated (runner slow)", frequency recorded in §0.
- **(f) mine, minimal composite:** (b)'s ratio bound asserted on every run (catches a solve/build regression relative to the runner) **and** (e)'s absolute 30 s / growth assertion evaluated only when the flutter reference is within its band (catches an absolute regression on a normal runner; a global synthesis slowdown that (b) is blind to); both lines printed every run; the "not evaluated" count recorded.

**Pre-computed for the seats (from file 56, my working):** mean ratio Linux 3.05 (max/mean 1.062), Windows 2.83 (max/mean **1.088**), macOS 3.80 (1.033; one row approximate). A 1.10× multiplier on the Windows mean ratio leaves ≈ 1 % margin: **k must come from the observed spread, not be chosen at 1.10 by analogy**, or (b) is as flaky on Windows as (a). The seats are asked to rate (b)/(f) with k derived (e.g. k = 1 + 3·SD/mean, or a pinned ratio = max on file ×1.05), stating the method.

## 2. Convening table
| seat | status | reason (README table item) | brief |
|---|---|---|---|
| 1 | not required | no option changes audio output, W_max, range or formulation ((v)(d) bounds them); no audibility question | — |
| 2 | **convened** | "simulator compute and recompute time; claims of … accuracy": the gate measures the build; whether a ratio form hides a build regression (the named finding is the synthesis, 95.5 % of the build); its W-x′ later 1 "remedy ladder ends in a red gate" (file 19 L121) | B2 |
| 3 | **convened** (running) | owns the restore-cost reading of D-H1 (v) and 07c's remedy; "per-instance CPU"; W-x′ later 1 "07c next" (L124) | B3 |
| 4 | not required | no delivery-chain, HRTF or format item; Phase 08 heaviest-mode gate runs under whatever form is decided (its W-x′ later 1 is unchanged by the form) | — |
| 5 | **convened** (running) | "CI gates and sanitizers; offline equals real-time; host conformance": the gate is its instrument; W-x′ later 1 "growth bound re-baselined only through plan text" (L128); mandate carries NFR-2/L101 | B5 |
| 6 | **convened** | mandate carries the user (L101): the 2.14 s convention is the producer's project-load wait; whether a normalised gate still guarantees it; "settling" / records to Maisara (L134) | B6 |
| 7 | **convened** | cost: red PRs waiting on runner luck (2 of 5 runs), contractor time; the cost and plan tier of a dedicated runner (researcher F18: larger runners not free for public repos) for the Phase 13 record; "release cadence; what one founder can sustain" | B7 |
| 8 | not required | the producer's load wait is unchanged under every option (no option moves the restore itself); records already go to Maisara (Raise item 2) | — |
| 9 | not required | no room, material or preset question | — |

## 3. Briefs (verbatim for the orchestrator)
**Common to all (B-core):** Read file 56 (data table and options), file 19 L104 (D-H1 (v)(a)–(d)), file 53/54, phase-05h §5 L368–390, `tests/unit/test_diffuse_records.cpp` L46–92 and L348–403, researcher file 5 F9–F12 (hosted-runner variance; F10: slowdowns detectable "with test and control on the same instances"), BUILD_PLAN AX38 4c register paragraph. Options (a), (b), (c), (e), (f) as above ((d) is out of 05h's bounds; you may still say what it would cost/buy for Phase 13). For **each** option: tension now / later (0–3, 3 veto-grade), one-line reason, conditions of acceptance where you rate ≥ 2. Bounds: no W_max cut, no range change, no seam, 14 × t_restore ≤ 30 s stays the convention (H1-F1), no re-run culture, tolerances from statistics.

**B5 (Seat 5):** (i) which form keeps `ci ok` meaningful on 4-vCPU x64 / 3-vCPU M1 shared VMs; (ii) derive the multiplier k for (b)/(f) from the 4–5 ratios per OS on file (state the method and the resulting k per OS; say whether a pooled k is defensible); (iii) the band for (e)/(f)'s runner guard (±10 % of flutter median: how many of the 13 rows on file would be "not evaluated"? compute it); (iv) what is printed, what is asserted, and the exact `kGateRegister` fields you want (recorded14xS, baselineMedianMs, baselineRatio, flutterRefMs, listed); (v) how the baseline is pinned (which runs, mean or per-run, CHANGELOG rule) and re-pinned at W_max/n*_max re-derivation; (vi) whether the strict form on Phase 13's release machines (AX41) is sufficient backstop for a shared-runner "not evaluated".

**B3 (Seat 3):** (i) what regression the gate must catch until 07c conditions 9–10 land (solve, synthesis, ISM+matching+mix) and which option is blind to which (the ratio is blind to a uniform factor across both scenes; the flutter scene's tail is shorter, so it is not blind to a length-dependent synthesis change — confirm or correct from the code, `tailLengthS = min(12 s, 1.5·T60)`); (ii) whether the full-rebuild and AQ4-interval records cover (b)'s blind spot adequately; (iii) does any option change 07c's remedy or its ordering ("07c next")?

**B2 (Seat 2):** (i) is a relative (same-run) bound an acceptable guard on the simulator's recompute time, or does it let the build grow unnoticed on every machine (your L27 "ends in a red gate unless the finding gets a remedy" — is a gate that never goes red worse or better for the remedy's pressure)? (ii) the flutter scene as reference workload: does its solve (pilot only, no cap) share enough of the code path to be a fair runner-speed proxy; name a better same-run reference if one exists in the records test (e.g. the full-rebuild record).

**B6 (Seat 6):** (i) under (b)/(e)/(f) the absolute 2.14 s is reported, not asserted, on shared runners until Phase 13: is the producer's load-time guarantee (L101; the 1/3/10 s anchors, AX38 (iv)) weakened in any way you rate ≥ 1? (ii) what the §0 note / PR must say to Maisara about "not evaluated" runs.

**B7 (Seat 7):** (i) contractor-time cost per option, now and until 07c lands (the red-PR tax under (a) vs the plan/test edit of (b)/(e)/(f)); (ii) for the Phase 13 record only: cost and plan tier of a dedicated or larger runner (F18) and whether it is sustainable for one founder; (iii) public wording: none of the options is customer-facing — confirm or object.

## 4. Knowledge inventory (first pass)
| id | what | source | status |
|---|---|---|---|
| K1 | per-run restore/flutter/full-rebuild medians, 13 OS-rows, 5 runs | file 56 table (CI logs) | known (from the code/CI) |
| K2 | the rule's text (a)–(d), purpose sentence | file 19 L104; phase-05h §5; AX38 4c | known |
| K3 | ratio spread per OS, mean and max/mean (above) | derived from K1 | known; **under-informed** (n = 4–5; macOS first row approximate) |
| K4 | k for the ratio bound and the guard band with a stated false-red method | Seat 5 (B5 ii–iii), researcher RQ-RG-2 | **uninformed** → needed before (b)/(e)/(f) can be pinned |
| K5 | hosted-runner variance base rate; same-instance control detects slowdowns (≥ 10 instances) | researcher F10 (read), F11 (preprint, medium), F12 not found | known as a source, **ill-informed risk** (conditions: x64 IaaS microbenchmarks, not a 2 s multithreaded build on M1) |
| K6 | remedy and timing: 07c conditions 9–10; ≈ 0.15 s left after both | plan; file 19 L104 | known |
| K7 | what the gate must catch until then | file 56 "Facts"; Seat 3 (B3 i) | under-informed until Seat 3 answers |
| K8 | the ratio's blind spot (uniform slowdown) and what covers it | file 56; code (`tailLengthS`) | under-informed → Seats 2/3 |
| K9 | larger/dedicated runner cost and tier | researcher F18 (read) | known; not load-bearing ((d) out of bounds) |
| K10 | red rate on file: 2 of the last 5 runs | file 56 | known |

## 5. RESEARCH NEEDED (alongside the seats)
- **RQ-RG-1:** Does any GitHub documentation or peer-reviewed source state that absolute wall-clock timing gates are not reproducible on hosted runners (Linux/Windows x64 included, not only macOS, F12)? Conditions: public-repo standard runners, 2024–2026. *Changes:* if documented, (a) and (c) are structurally unsound on shared runners and drop at step 1 under CLAUDE.md's verification culture; if not, they stay options scored on the seats' cells only.
- **RQ-RG-2:** For F10 (Laaber et al. 2019), quote exactly the "test and control on the same instances" result and its conditions (what counts as an instance/trial; whether the result holds for a single paired measurement per run, or needs ≥ 10 paired instances). *Changes:* whether (b)/(f)'s single-run ratio is a recognised detector or only a weak one, which decides between (b) and (e) when Seats 3/5 tie.
- **RQ-RG-3:** A citable small-sample method for setting a one-sided bound from n = 4–5 ratio samples (nonparametric tolerance bound or an explicitly conditioned normal bound), with its false-exceedance rate. *Changes:* the value of k per OS (K4); whether 1.10 can be stated or must be replaced.

## 6. What the decision round will need from the orchestrator
Seat 5 and Seat 3 cells (files 57, 58) **and** Seats 2, 6, 7 on B2/B6/B7, plus RQ-RG-1–3. If the orchestrator wants a smaller round, Seats 2 and 6 may be run on B-core only; Seat 7 is required (cost is touched by every option). The decision will be written as `FOR MAISARA` amending D-H1 (v)/AX38 4c (her acceptance of 2026-11-10), with the exact `kGateRegister` form, the assertion, the print lines and the baseline-pinning rule; NEEDS MAISARA only if a seat rates every surviving option 3.

**CONVENE:** Seats 2, 3 (running), 5 (running), 6, 7. Researcher: RQ-RG-1, RQ-RG-2, RQ-RG-3.

Files read: /home/user/makroof/docs/review/phase-05h/56-orchestrator-restore-gate-runner-variance.md, /home/user/makroof/docs/review/phase-05h/19-decider-decision-D-H1-D-H2-r2.md (L95–182), /home/user/makroof/docs/review/phase-05h/53-orchestrator-windows-restore-gate-crossing.md, /home/user/makroof/docs/review/phase-05h/54-interrogator-windows-restore-gate-crossing.md, /home/user/makroof/docs/review/phase-05h/5-researcher-RQ-H1-H2.md (F9–F20), /home/user/makroof/docs/review/phase-05h/5-seat5-D-H1-D-H2.md, 5-seat3, 5-seat7 (W cells), /home/user/makroof/docs/phases/phase-05h.md (§3 D-H1, §5 L372–391), /home/user/makroof/docs/BUILD_PLAN.md (§6 L450–474), /home/user/makroof/tests/unit/test_diffuse_records.cpp (L40–109, L340–414), /home/user/makroof/docs/board/README.md (L45–124), /home/user/makroof/docs/PRD.md, /home/user/makroof/CLAUDE.md.


---

# Decider — restore-gate register form (file 56), round 2: PROVISIONAL DECISION on Seat 5's cell; CONVENE Seats 3 (pending), 2, 6, 7 on the concrete variant

Corpus `c1b171fe649f` (no acoustic claim). PRD digest, restatement, options (a)–(f) and the nine-row table: as my round-1 hand-back; unchanged. Seat 5's cell (file 57) is in; file 58 (Seat 3) and Seats 2, 6, 7 are not. I cannot decide on one seat where my own table convened five, so the state is **proposed, pending**; the variant, the plan text and the test form are fixed now so the remaining seats rate one concrete thing.

## Knowledge inventory (update)
| id | what | source | status |
|---|---|---|---|
| K1 | per-run data, 13 OS-rows | file 56 | known (CI record) |
| K2 | rule text (v)(a)–(d) | file 19 L104; phase-05h §5 L368–390 | known |
| K3 | ratio means Windows 2.83 / Linux 3.05 / macOS ≈ 3.80; max/mean 1.088 / 1.062 / 1.033; a one-run baseline × 1.10 (2.90 / 3.14) is below the observed maxima 3.08 / 3.24 (run 42935789745) | file 56; Seat 5 §3; my arithmetic agrees | known |
| K4 | bound multiplier: × 1.15 of the mean leaves every observed ratio inside (3.25 / 3.51 / 4.37 vs max 3.08 / 3.24 / 3.92; margins 5.5 / 8 / 11 %) | Seat 5 §5–6, re-done | known as an observed-spread bound; **not** a statistical tolerance (n = 4–5): stated as such in the text; RQ-RG-3 stays open, not load-bearing |
| K5 | CI order: Benchmark step L404 precedes pluginval L425 / auval L434; first `if: always()` at L472 (artifact upload) → a red records REQUIRE removes host-conformance evidence on that OS | ci.yml, from the code (verified) | known |
| K6 | precedent: AX38 (i) quiesce record "a print, never a CHECK with a timing threshold on shared runners" | BUILD_PLAN L139 (verified by grep) | known |
| K7 | Phase 13 release-machine strict re-check exists in plan text (4 occurrences) | BUILD_PLAN AX41 / AX38 4c | known |
| K8 | remedy 07c conditions 9–10; ≈ 0.15 s left | plan | known |
| K9 | ratio blind to a uniform slowdown of both scenes; what covers it | file 56; Seat 5 §4 ("nothing on a shared runner can see a 10 % synthesis change under ×1.63 noise") | under-informed → Seats 2/3 (B2, B3) |
| K10 | flutter median spread Linux 514–880 ms (−28/+23 %): a ±10 % guard (e) evaluates on about half the runs | Seat 5 §3 from file 56 | known |

## Tension map (Seat 5's words; other convened seats pending; 1, 4, 8, 9 = 0/0 by the table)
| option | Seat 5 now / later | Seat 5's reason |
|---|---|---|
| (a) as it stands | **3** / 2 | "red on 2 of 5 runs by runner speed, each red masking pluginval/auval on that OS"; later "every PR to 07c waits on runner luck … the fingerprint skip never fires" |
| (a) + `if: always()` | 2 / 2 | "2→1 is not reachable while an absolute timing CHECK sits on a shared runner" (§6) |
| (b) as written (one-run × 1.10) | 2 / 1 | "would already have been red on run 42935789745 on both OSes" |
| (b) multi-run mean × 1.15 + `if: always()` | 1 / 1 (read from §6 conditions) | "blind to a global synthesis slowdown … re-baselined at 07c" |
| (c) slowest-run baseline | 1 / 2 | "the baseline creeps upward at every slower runner, each creep a plan edit" |
| (d) dedicated runner | 2 / 1 | out at step 1 (one-phase rule); "Phase 13's question" |
| (e) runner guard | 1 / 2 | "a regression that slows both scenes reads as 'runner slow'" |
| (g) nightly-only (Seat 5's) | 1 / 2 | "same shared runners, less coverage, and the nightly is not scheduled" |
| **(x) Seat 5's: no timing figure is a CHECK on shared runners** | **0 / 1** | "a record nobody reads is my §17 blind spot; mitigated by a machine-readable summary line and Phase 13's strict re-check" |
| (f) mine | not rated by Seat 5 | withdrawn: it contains (e)'s guard, which Seat 5 rates later 2 |

## Minimum-tension working (as far as one seat allows)
1. **Bounds:** (d) out (one-phase rule; file 56). Every other option keeps W_max, range and formulation ((v)(d)). (x) moves the 30 s line from CHECK to print on shared runners: that amends D-H1 (v)(a)/(b) → `FOR MAISARA`, inside the bounds (H1-F1's convention stands; enforced strictly at Phase 13, K7).
2. **Veto-grade:** (a) as it stands dropped (3 now).
3. **Worst-off:** (x) max 1; (b)-conditioned max 1; the rest max 2.
4. **Compose:** **(x′)** = (x) + Seat 5's (b)-conditioned ratio bound as the one asserted timing figure (relative, multi-run mean baseline × 1.15) + `if: always()` + a machine-readable summary line + §0 count. Seat 5's §2 already puts the widened (b) inside (x), so (x′) is (x) as Seat 5 wrote it, named. Cells for Seat 5: 0 / 1 (its own option).
5–6. Sum and reversibility wait for the other seats.
7. **Proposed:** (x′). Falls or changes if Seat 3, 2, 6 or 7 rates it ≥ 2 (compose from their conditions) or 3 (drop).

## Draft FOR MAISARA RG-F1 (to be interrogated once the seats are in)
**Question.** May the AX38 4c blocking restore gate's absolute timing assertions (30 s strict; 1.10 × median growth) become printed records on shared CI runners, with the only asserted timing figure a runner-normalised ratio, until Phase 13's release machines re-enforce them strictly?

**Answer (exact wording).** "On GitHub-hosted runners no absolute timing figure of the restore gate is a CHECK. Per OS and gated scene the records test prints min / median / worst of 10 restores, 14 × worst against the 30 s line, the 29.1 s strict/listed rule and the register's growth bound, every run, in one machine-readable summary line; the register entries, their remedies and closing phases stand. Asserted on every run: (1) the exact W_pilot / W_final pins and the AX41 realised-work ratio ≤ 1.02 (deterministic, runner-independent); (2) the runner-normalised bound median(low-α restore) / median(flutter restore, same run) ≤ 1.15 × the pinned ratio per OS, pinned as the mean of the runs on file (Linux 3.05 from runs 42909003931 / 42924781618 / 42935789745 / 42949252041; Windows 2.83 from those plus 42942694523; macOS 3.80 from the same four as Linux, the first row approximate), re-pinned with a CHANGELOG reason at every W_max / n*_max re-derivation and at 07c. A bound broken is a defect under (v)(d) (no re-run, no cut, no range change, no seam). The strict 30 s and the 1.10 × growth bound are re-enforced on all three OSes at Phase 13's release-machine re-check (AX41) and on any dedicated runner. `ci.yml`: the pluginval and auval steps run `if: always()` so no records failure hides host conformance. §0 row 05h records, per run, the printed 14 × worst per OS."

**PRD ids and decisions.** L101 ("but … usable in a DAW session"), NFR-2, NFR-1, NFR-6, NFR-4 (three OSes), L20; her acceptance 2026-11-10; D-H1 (v) / H1-F1 / H1-F2 (file 19).
**Reasoning.** The 30 s convention bounds a user-facing wait (L101); a CHECK that is red on 2 of 5 identical runs measures the runner, not that wait, and each red removes the pluginval/auval evidence (NFR-4) on that OS (K5). The plan already treats timing on shared runners as a print (K6) and already names Phase 13's release machines as where the bound is enforced (K7). NFR-1 is untouched (no cut). What the ratio asserts is the solve's cost relative to the same machine, the one regression a shared runner can see (K3, K4).
- *(x′) chosen:* serves L101 (the wait is still measured and reported every run, enforced where measurable), NFR-4 (host conformance evidence kept), NFR-1.
- *(a):* serves the letter of "blocking"; strains NFR-4 (K5) and CLAUDE.md's culture (red by runner).
- *(b) alone, (c), (e):* keep an absolute or guarded timing CHECK on shared runners; strain the same, less often ((c) weakens to a creep detector; (e) hides the global case).
- *(d):* a Phase 13 / Seat 7 question; not 05h's.
**What would make her veto it.** The reading that "a blocking CI gate" (her 2026-11-10 acceptance of Challenge 1) means an absolute 30 s CHECK on every CI run now, red or not, and that printing it until Phase 13 removes the pressure to shorten the 100 m build.
`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AQ10 amended (1) and AX38 4c: the restore block's (a)/(b) assertions become printed records on hosted runners, with the ratio bound asserted and strict enforcement at Phase 13; D-H1 (v)(a)–(b) and phase-05h §5 "Blocking" rewritten accordingly.)

## Exact test form (orchestrator, if (x′) survives)
- `GateEntry` gains `double baselineRatio` (mean of the runs above) and `double flutterRefMs` (print only); `listed`, `recorded14xS`, `baselineMedianMs` kept for the print.
- Per gated scene: print the existing restore line; print `05h-records restore gate <scene> <OS>: RECORD 14 x worst %.2f s (30 s line; %s) ; growth %.0f vs %.0f ms (record) ; ratio low-α/flutter %.3f <= %.3f` with `%s` = `strict` / `LISTED defect` / `WARNING passes 30 s` as today. Order the flutter scene before the low-α scene (it already is) and keep its median in a static for the ratio.
- Assert only: `REQUIRE(ratio <= 1.15 * entry->baselineRatio)` at `cube100_lowalpha0.05_s0.3`; the existing `REQUIRE`s L331, L343–344 unchanged; L392 and L399 removed (printed instead).
- One summary line per OS, grep-able: `05h-records SUMMARY <OS> low-alpha 14xworst=%.2f flutter 14xworst=%.2f ratio=%.3f bound=%.3f`.
- Constants re-pinned only with `tests/golden/CHANGELOG.md` reason (not a golden).
- `ci.yml`: `if: always()` on the pluginval (L425) and auval (L434) steps; `test_ci_workflow.py` adjusted if it pins step conditions.

## Exact plan text (plan-editor): phase-05h §5 "Blocking" (a)–(b) and AX38 4c's register paragraph replaced by the Answer's wording; (c)–(d) kept with "growth bound" → "ratio bound"; phase-05i scope 3 keeps the re-baseline; AX41's Phase 13 sentence gains "the strict 30 s and 1.10 × growth bound, as printed since 05h"; a §6 row with the AMENDS line.

## Future-debt register (chosen (x′), Seat 5 only so far)
| seat | commits later phases to | undoing costs | evidence arrives | repaid when |
|---|---|---|---|---|
| 5 (later 1) | a record that must be read: the summary line per run, §0 count; strict re-enforcement on release machines | a test edit (restore the two REQUIREs) | Phase 13 release-machine run; 07c's restore record | Phase 13, or 07c if the entries pass 30 s there |

**Strongest objection so far:** Seat 2's W-x′ later 1 (file 19 L121: the remedy ladder "ends in a red gate unless the finding gets a remedy") — under (x′) the gate never goes red on shared runners, so the pressure for 07c condition 9 is the plan's ordering alone. It holds if Seat 2 rates (x′) ≤ 1 with "07c next" unchanged; otherwise compose.

## CONVENE (one round, on (x′) exactly as worded above)
- **Seat 3** (file 58 when it lands; if it rated only (a)–(e), ask it to rate (x′) and B3 (i)–(iii)).
- **Seat 2:** B2 (i)–(ii) plus: does (x′) keep enough pressure for 07c condition 9; is the flutter restore a fair same-run reference; a deterministic `BandNoiseGenerator` operation count as a runner-independent synthesis pin (Seat 5's hand-off, §7).
- **Seat 6:** B6 (i)–(ii) on (x′): is the producer's load-time guarantee weakened by "printed until Phase 13"?
- **Seat 7:** B7 on (x′): contractor cost of the test/plan edit vs the red-PR tax; the Phase 13 dedicated-runner question (F18) for the record.
- **Researcher:** RQ-RG-1 stays (supports step 1 against (a)/(c)); RQ-RG-2/3 downgraded to non-load-bearing (the × 1.15 is an observed-spread bound, stated as such).

Summary: `RG-1 | (x′): no absolute timing CHECK on hosted runners; ratio ≤ 1.15 × mean baseline asserted; records printed; if: always(); strict at Phase 13 | proposed, pending Seats 3, 2, 6, 7 | Seat 5 (0 / 1) | pending | medium | L101/NFR-2, NFR-4, NFR-1, (v)(d) | none needed | Phase 13's release-machine run shows the 30 s line met (entries close) or broken (the absolute CHECK returns on that hardware)`.

Files: /home/user/makroof/docs/review/phase-05h/57-seat5-restore-gate-runner-variance.md, /home/user/makroof/.github/workflows/ci.yml (L404, L425, L434, L472), /home/user/makroof/tests/unit/test_diffuse_records.cpp (L331, L343–344, L392, L399), /home/user/makroof/docs/BUILD_PLAN.md L139.
