# 5 — Decider: Q1–Q5 of file 4 (convene or decide)

Phase 05i, 2026-11-11. Read: file 4 (Q1–Q5); file 3 (CI run 43007183782, all three OS sections); file 2 L3–6 and L29; phase-05i §§0–9; phase-05h §5 L366–406; BUILD_PLAN AX38 (row L158); phase-05h file 31 L444–730 (CI runs 42924781618, 42964823518, 42975074716); decider file 36; `tests/unit/test_diffuse_records.cpp` L70–116 and L452–549; PRD L38–125; `docs/board/README.md` "Who answers Maisara's questions"; session brief.

**Corpus:** `docs/corpus/` is **not present** in this checkout (`SOURCE_COMMIT` was not found). No acoustic or psychoacoustic fact carries weight in any answer below: they read CI records into existing rules. If the interrogator needs a corpus passage, run `tools/ci/fetch_corpus.sh` first. Table 15.1 and Card et al. are cited only as AX38 4c's own labels.

## PRD digest

- **For whom:** producers and sound designers placing tracks in a designed 3D space, one or several instances per project (PRD L42, FR-3D-6, FR-SIM-7).
- **Outcome:** accurate rendering that stays usable in a DAW session: "Accuracy is the top priority; CPU load and latency may be high, but the plugin must stay usable" (L101).
- **Hard constraints that bear here:** NFR-1 (accuracy; no W_max cut); NFR-2 (heavy latency acceptable when it buys accuracy); NFR-6 (exact restore); NFR-8 (no scene logic).
- **Her recorded decisions that bear here:** AX38 (i) release rule (no build reaches a producer outside the team while the (i) entry is open; team = PRD L55); AX38 4c with D-H1 (v) and RG-1 (accepted for her, `AMENDS her decision of 2026-11-10`); AX38 (iv) with decider file 36 R3.
- **Plan rules:** phase-05i §1 ("Nothing here reopens a decision"); §7 ("A record above an anchor is a finding … never a range change").
- **Out of scope here:** τ, N, W_max, the case list, ranges, the engine (phase-05i §8).
- **Verification culture:** every DSP behaviour is checked automatically; goldens are never regenerated to pass; records are printed, never asserted, with their condition stated.

## Classification

| Q | type | why |
|---|---|---|
| Q1 register exits | (a) a reading of AX38 4c (c) and phase-05i §3.3 (ii); answered as FOR MAISARA because AX38 4c is her recorded decision | (c) is mechanical, and AX38 4c names "05i's first run" for Linux |
| Q2 K-e12 vs Raise item 1 | (a) Raise item; FOR MAISARA | §3.2 and AX38 4c already route the finding; item 1's condition is false |
| Q3 Raise item 2 on 05i's records | (a) Raise item; FOR MAISARA | file 36 R3's rule applies; the new records fit findings F-a and F-b |
| Q4 Raise item 3 (M-d) | (a) Raise item; did not arise | it is an action, and its condition is false (file 2) |
| Q5 solve-median bound k | (a) for form, assertion and re-derivation (settled text); the value is delegated by plan text to the orchestrator's `/fix-plan` proposal (interrogator check); I give a recommended value | phase-05h §5 L378–379, L392–393; phase-05i §3.3 (iv)–(v) |

## Convening (all five questions; every seat not required)

| seat | status | reason |
|---|---|---|
| 1 Perceptual | not required | No audibility or realism claim. AX38 4c labels the 1/3/10 s marks "UI response-time anchors … not audibility limits". |
| 2 Engine | not required | Geometry→response, compute and recompute paths do not change. The records are read, not chosen, and each states its condition. |
| 3 Renderer | not required | No rendering, time-variance or CPU-design change. |
| 4 Chain | not required | No delivery or format matter. |
| 5 Deadline | not required | No assertion changes. Q1 flips a print-only flag; strict30s and absoluteAsserted are untouched (code L460–476, L547–548). Q5's form (printed, never asserted on hosted runners) was fixed by RG-1 with Seat 5 convened (file 57). The host-thread waits in Q3 are records under D-H3 (e), whose remedy Seat 5 helped set. |
| 6 Canvas | not required | No control, range or default changes. The waits are findings under existing remedies, and the "settling" hand-off (AX38 (iii), Phase 11) is unchanged. |
| 7 Founder | not required | No public wording or release rule is written. The release rule (AX38 (i)) is unchanged. Notes content stays Phase 13's question with Seat 7 convened (file 36 addendum register row). |
| 8 Storyteller | not required | No workflow requirement is decided. |
| 9 Room acoustician | not required | No room, material or preset matter. |

Why these are mine alone: each answer applies a rule the board already decided (D-H1 (v), D-H3 (e), RG-1, file 36 R3) to new CI numbers, with no new option on the table. Q5's value is routed by plan text to the orchestrator and the interrogator, not to the board.

## Knowledge inventory

| K | what | source | status |
|---|---|---|---|
| K1 | low-α 14 × worst per OS, run 43007183782: L 27.61 PASSES30S (in-window, flutter −3.7 %, median 1 892 ≤ 2 275); M 43.54 OVER30S (median 1 905 < trigger 2 172); W 28.74 PASSES30S (in-window, flutter +1.3 %, median 1 996 ≤ 2 231) | file 3 L9, L207, L361 | known |
| K2 | earlier Linux / Windows values: L 29.62 / 30.18 / 24.31 / 27.81 / 25.29 / 24.75 s; W 29.04 / 29.50 / 28.57 / 36.73 (slow runner) / 29.51 / 44.83 (flutter +43.6 %) s | AX38 4c; file 31 L541, L611, L615, L684, L690–691 | known |
| K3 | (c): a listed entry passing 30 s "leaves the register through `/fix-plan` before the next phase is `done`"; the assertion form is fixed until Phase 13; Linux removal is "phase-05i scope 3's call on 05i's first run" | AX38 4c; phase-05h §5 L396–401 | known |
| K4 | `listed` changes only the print ("LISTED defect" against "register entry closed, hosted-runner form"); strict30s stays false on low-α (interrogator file 69 item 2) | from the code, L82–85, L106–108, L471 | known |
| K5 | K-e12, 96 kHz, low-α worst / median of 10: L 3 276 / 2 370; M 2 648 / 1 967; W 3 231 / 2 377 ms; idle 1 799 / 1 803 / 1 939; flutter worst 793 / 675 / 1 031 | file 3 L70, L81, L220, L231, L338, L349 | known |
| K6 | the (iv) records at 8 instances, 100 m low-α, 96 kHz, and the other classes | file 3 L35–103, L171–219, L273–319 | known |
| K7 | 05h answer R3 and findings F-a and F-b | decider file 36 §2–§3; AX38 (iv) and 4c | known |
| K8 | M-d did not arise: produced on the session machine; 560/560, 72/72 gated | file 2 L3–6, L29; file 3 L120, L336 | known |
| K9 | solve medians on the three RG-1-form CI runs | file 31 L610–615, L679–684; file 3 L8–9, L206–207, L360–361 | known |
| K10 | form of the solve bound: printed with WARNING, never asserted on hosted runners; proposed once ≥ 3 runs give its spread; re-derived from ≥ 3 in-window runs at the 07c re-pin | phase-05h §5 L377–379, L392–393; phase-05i §3.3 (iv)–(v) | known |

No research is needed.

---

## Q1 — FOR MAISARA Q1 (register exits under §5 (c))

**Question.** On 05i's run, does the Linux entry, the Windows entry, both or neither leave the AX38 4c register, given phase-05i §3.3 (ii)'s "the Linux …, macOS … and Windows … entries stay listed"? Does `kGateRegister.listed` change?

**Answer.** "Both the **Linux** and **Windows** low-α entries leave the register under §5 (c). CI run 43007183782, 05i's first run, printed 14 × worst 27.61 s on Linux and 28.74 s on Windows. Both are PASSES30S, both in the ±5 % flutter window, both with the growth bound asserted and met.

- Their register text closes, with the recorded value, median, remedy and closing phase kept as history and 'closed under (c), phase 05i, run 43007183782' appended.
- The **macOS** entry stays listed: 43.54 s OVER30S, its recorded state until phase-07c; median 1 905 ms, below the 2 172 ms trigger.
- Nothing asserted changes. The low-α scene keeps its hosted-runner form until Phase 13 (in-window growth bound on Linux and Windows, printed on macOS). The strict 30 s applies to the low-α scene only on the release machines at Phase 13.
- In `kGateRegister`, `listed` becomes `false` for Linux and Windows low-α. That flag changes only what is printed ('register entry closed, hosted-runner form'). `recorded14xS`, the baselines, `absoluteAsserted` and `strict30s` stay as they are.
- The phase-07c conditions 9–10 remain scheduled through the macOS entry, the K-e12 finding, F-a and F-b."

**Rests on.** Her recorded decision AX38 4c (c) with RG-1, and the explicit hand-off "its removal under (c) is phase-05i scope 3's call on 05i's first run". Also phase-05i §1 ("every rule is phase-05h's"), PRD NFR-1 (W_max untouched), NFR-2 and L101. The PRD itself is silent on CI register bookkeeping. Her recorded decision settles the point, so this is not case (a).

**Reasoning.**
- §3.3 (ii) is one sentence. The leaving branch comes first, then "otherwise it stays listed and the run is recorded; the Linux …, macOS … and Windows … entries stay listed". Reading "stay listed" as unconditional would void the branch the same sentence opens, and would contradict §1. So it describes the "otherwise" state.
- §4 criterion 3 ("register entries unchanged in substance") is met: the substance fields stay as history and only the state changes, by the rule's own exit.
- Windows qualifies on the same rule. Every Windows value on file outside the two slow-runner runs is 28.57–29.51 s.

**Options.**
- (A) Both leave (chosen). Serves NFR-1 and NFR-2 (no assertion or W_max touched) and keeps her (c) rule operative.
- (B) Linux only. Within the PRD, but misreads (c), which applies to "a listed entry", not only to Linux.
- (C) Neither. Reads "stay listed" as overriding (c); contradicts her recorded rule and phase-05i §1.
- (D) Both leave and the strict 30 s is re-armed on hosted runners. Barred by (c) ("stays in this form … until Phase 13") and interrogator file 69 item 2. A runner-speed red would then strain NFR-1 by pressure to cut W_max, which D-H1 (v)(d) bars.

**Veto reading.** The strongest reading against this answer: closing on one run is premature, because Linux read 30.18 s on in-window run 42924781618 and Windows sits within 1 s of 30 s. It holds anyway: (c) has no stability condition, AX38 names 05i's first run for Linux, closure changes no assertion, and Phase 13 re-checks strictly on the release machines.

`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX38 4c register: Linux and Windows entries closed under its own (c). No rule change.)

**Text for the plan-editor.**
- **AX38 4c register:** append to the Linux entry: "**Closed under (c)** (phase 05i, CI run 43007183782, in-window, flutter −3.7 %: 14 × worst 27.61 s, median 1 892 ≤ 2 275 ms; RG-1-form runs before it 25.29 / 24.75 s); hosted-runner assertion unchanged until Phase 13."
- Append to the Windows entry: "**Closed under (c)** (phase 05i, CI run 43007183782, in-window, flutter +1.3 %: 14 × worst 28.74 s, median 1 996 ≤ 2 231 ms; values on file outside the slow-runner runs 42942694523 (36.73 s) and 42975074716 (44.83 s, flutter +43.6 %) are 28.57–29.51 s; the runner stays the recorded likely cause of the listing, AX41); hosted-runner assertion unchanged until Phase 13."
- In the RG-1 paragraph, "The register entries (Linux 30.27 s, macOS 33.40 s, Windows 36.73 s; …) stand." becomes: "The macOS entry (33.40 s; remedy phase-07c conditions 9–10; closing phase unchanged) stands; the Linux and Windows entries closed under (c) in phase 05i (run 43007183782)."
- **phase-05h §5 L384–386 and phase-05i §3.3 (ii):** add the bracket "(Linux and Windows closed in 05i under (c), AX38 4c)".
- **§0 rows 05h and 05i:** the same.
- **Test (scope 3):** L106 and L108 `listed` → `false`; update the comment at L104–105. Recommended, print only: when `!listed`, the PASSES30S suffix should not say "remove it through /fix-plan".

---

## Q2 — FOR MAISARA Q2 (Raise item 1 and the K-e12 record)

**Question.** Does the K-e12 record above 3 s re-open Raise item 1, or is it the AX38 4c finding §3.2 names?

**Answer.** "Raise item 1 does not re-open. Its condition ('if the full-rebuild records were not in phase 05h's CI run') is false: they were in run 42909003931, answered in 05h (decider file 36 R2).

The K-e12 record is the AX38 4c finding that phase-05i §3.2 names. On CI run 43007183782, restoring the gated low-α 100 m cube at 96 kHz while a room edit was still being processed took a worst of 3.28 / 2.65 / 3.23 s of 10 (Linux / macOS / Windows). The medians were 2.37 / 1.97 / 2.38 s, against an idle restore of 1.80 / 1.80 / 1.94 s. That is above the 2.143 s per-restore budget on every OS. The flutter scene stayed within it (0.79 / 0.68 / 1.03 s).

Against AX38 4c's anchors: these are UI response-time anchors (Card et al. 1991), not audibility limits, and Table 15.1 has no row for room or material edits, so it applies by extension only. Linux and Windows are above 3 s and are named as a finding (worst of 10 on one run; the medians are below 3 s). The measured worst stays inside the ≈ 4.8 s estimate that AX38 4c gave as a hypothesis.

The remedy is unchanged: phase-07c conditions 9 (or 07d) and 10, re-measured by 07c condition 7. It is never a CHECK, a W_max cut, a range change or a seam. The build never reaches a producer (AX38 (i) release rule). The finding is written into AX38 4c's K-e12 paragraph and the record line against the anchors, and listed in the 05i PR."

**PRD ids and decisions.** L101; NFR-2; NFR-1; NFR-6; AX38 (i) release rule, 4c and D-H3 (e) (accepted for her 2026-11-10); file 36 R2 (Escalation reads "the numbers", every record); phase-05i §3.2, §7.

**Reasoning.** §3.2 fixes the class: a finding, never a CHECK. AX38 4c's Escalation names "any room above 3 s" a finding over all its records (file 36 R2, accepted reading), so the 3 s crossing is also named. A 2–3.3 s stall on one restore at the heaviest build is latency that buys accuracy (NFR-2). L101's "usable" is protected because this build is barred from producers until 07c's cancel points and synthesis move land.

**Options.**
- (A) AX38 4c finding plus named against the anchors, remedy as scheduled (chosen). Serves L101, NFR-1, NFR-2 and NFR-6.
- (B) Re-open item 1 as NEEDS MAISARA. Outside the three cases: the PRD and her AX38 4c settle it.
- (C) Treat it as a gate failure or cut W_max. §3.2 says "never a CHECK"; D-H1 (v)(d) bars it; strains NFR-1.
- (D) Record it only against 2.143 s. Misreads her AX38 4c Escalation (file 36 R2's corrected reading).

**Veto reading.** A host-thread stall above 3 s on a restore is "not usable" (L101) and should hold 05i back. It holds anyway because the build is barred from producers and 07c is the next phase with the cure.

`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX38 4c: a recorded finding, no rule change.)

**Text for the plan-editor.** Append to AX38 4c's K-e12 finding: "*Record (phase 05i, CI run 43007183782):* low-α worst / median of 10 3 276 / 2 370, 2 648 / 1 967, 3 231 / 2 377 ms (Linux / macOS / Windows; idle 1 799 / 1 803 / 1 939 ms): above 2.143 s on every OS, a finding under the register's form; above 3 s on Linux and Windows, named against the anchors; flutter 793 / 675 / 1 031 ms, within; remedy unchanged." Add one line to the record against the anchors citing the same.

---

## Q3 — FOR MAISARA Q3 (Raise item 2 on 05i's records)

**Question.** Does 05h's answer (file 36 R3, recorded in AX38 (iv)) stand for 05i's records?

**Answer.** "It stands unchanged; no new record changes it.

**The load, 8 instances, 100 m low-α cube, 96 kHz:** 19.5 / 16.3 / 23.0 s (Linux / macOS / Windows), still above the 10 s line and within 05h's range.
- Ratio to the single-instance load: 7.9× / 7.5× / 9.3×.
- The per-instance print now carried (file 36 Q4) puts the only excess over 8× on Windows, in instances 5–8 (restore 2.42–2.67 s against 1.93–2.04 s for instances 1–4). The cause is not established.
- At 48 kHz the 8-instance load is now 8.3 / 8.4 / 9.9 s, under 10 s on every OS.

**The new record classes extend the named findings; they do not add a new one:**
- **F-b** (about linear in instance count) now also covers:
  - joint and room-size staleness at 8 × 100 m / 96 kHz, up to 16.4 s;
  - real-time staleness while another instance renders offline, up to 29.4 / 27.9 / 31.8 s. This is about 2× the joint staleness at every instance count, which matches the gate's turn-taking in AX38 (i).
- **The offline wait** is about linear in M (7.6–7.8× at M = 8: per-block median 15.5 / 14.5 / 15.3 s). It is recorded under F20: offline has no deadline and its output is identical, and its cost shows in the bounce ratio in 07c's packet.
- **F-a** (a synchronous host call contended by other instances' rebuilds) now recurs on all three OSes, no longer a one-run outlier. From 4 instances at 100 m / 96 kHz, the worst prepare / restore / offline-switch wait is 3.6–5.0 s, about 1.5–2× the single-instance wait and not growing from 4 to 8. At 48 kHz it is ≤ 2.3 s; at the AQ10 room it is < 1 s.

**Remedy for all of it, unchanged:** phase-07c conditions 9 (or 07d) and 10. Staleness is shown as AX38 (iii) 'settling'. Everything is re-measured by 07c condition 7 with time-to-audible and time-to-settle. Phase-13 Raise item 3 applies the 10 s line to the release build. No W_max cut, range change or seam, and no figure in the compatibility notes (Phase 13, with Seat 7)."

**PRD ids and decisions.** L101; NFR-2; NFR-1; NFR-6; L42 and FR-SIM-7 (several instances is a PRD use); L55 (team); AX38 (i), (iii), (iv) and 4c with file 36 R2/R3 (accepted for her 2026-11-10).

**Reasoning.** R3's rule depends on the load figure's class (above 10 s, a build barred from producers, cured at the cause in 07c). 05i's figures leave that class unchanged. The new classes are the same cost seen through other records (n rebuilds in turn, or one contended build), and AX38 4c names them as findings rather than gates.

**Options.**
- (A) R3 stands, records appended, F-a and F-b extended (chosen). Serves NFR-1, NFR-2 / L101 and NFR-6.
- (B) A fresh answer or NEEDS MAISARA. Outside the three cases: her AX38 (iv) and file 36 R3 settle it.
- (C) A cap on instances or on W_max. Strains NFR-1 and L42; barred by D-H1 (v)(d).

**Veto reading.** About 30 s of real-time staleness during an offline bounce is a new user cost that R3 never weighed. It is still F-b's mechanism (AX38 (i) turn-taking; R2 already named staleness up to 17.8 s), and it never reaches a producer before 07c.

`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX38 (iv) and 4c: 05i record lines appended. No rule change.)

**Text for the plan-editor (AX38 (iv), after the 2026-11-10 record).** "*Record (phase 05i, CI run 43007183782):* 8 × 100 m low-α / 96 kHz load 19.5 / 16.3 / 23.0 s (7.9× / 7.5× / 9.3× the single load; the per-instance print places Windows' excess in instances 5–8); 48 kHz 8.3 / 8.4 / 9.9 s; R3 stands. F-b extended: staleness during another instance's offline render up to 29.4 / 27.9 / 31.8 s (≈ 2× the joint staleness); offline wait ≈ linear in M (F20). F-a recurs: contended host-thread waits 3.6–5.0 s from 4 instances at 100 m / 96 kHz on every OS. Remedy unchanged."

---

## Q4 — FOR MAISARA Q4 (Raise item 3, M-d)

**Answer.** "Did not arise. Every BRAS outer-band reference was produced on the session machine (4 cores, 15 GB; file 2 L3–6). The CI run gates 560 of 560 AX43 and 72 of 72 AX45 case-bands (file 3 L120). Neither the 16 GB-runner job nor a larger machine was needed. Nothing for Maisara."

**Basis.** phase-05i §2 item 3 is conditional, and the condition is false. It is an action, not a decision, under README §3's last paragraph. PRD NFR-1 is served: every case-band is gated.

**Options.** (A) Record as "did not arise" (chosen). (B) List an action anyway: an action with no need.

**Veto reading:** none. No AMENDS.

---

## Q5 — FOR MAISARA Q5 (solve-median bound k): form settled, value delegated

**Answer (form; settled text).** "The per-scene solve median is printed with a WARNING and never asserted on hosted runners (phase-05h §5 L377–379). Its bound k is proposed by the orchestrator through `/fix-plan` now that ≥ 3 runs exist (§3.3 (iv)). k and its means are re-derived from ≥ 3 in-window runs at the 07c re-pin (§5 L392–393; §3.3 (v))."

**Value (my recommendation for the orchestrator's `/fix-plan` proposal; the interrogator's numeric check applies).** Add the token `SOLVE` to the GATE line's `warnings=` field when the run's `solveMedianMs` is greater than k × the per-OS, per-scene mean of CI runs 42964823518, 42975074716 and 43007183782, with **k = 1.20**.

| OS | low-α mean (ms) | threshold at k = 1.20 | flutter mean (ms) | threshold at k = 1.20 |
|---|---|---|---|---|
| Linux | 80.83 | 97.0 | 130.90 | 157.1 |
| macOS | 82.33 | 98.8 | 96.77 | 116.1 |
| Windows | 91.30 | 109.6 | 146.13 | 175.4 |

- The flutter deviation already printed beside it attributes a runner effect.
- The line is labelled "3 runs, 1 in-window on all OSes; re-derived at the 07c re-pin".
- One-sided only: the exact work pins are asserted, so a faster solve cannot hide skipped work.

**Working.**
- The largest observed max/mean is 1.086 (macOS flutter). k = 1.20 clears it by about 10 %.
- k = 1.20 equals RG-1's printed-warning factor `kRatioWarn`. A print-only line belongs to that family, not to the 1.15 defect-trigger family.
- macOS flutter's 3-run SD is 12.4 ms (CV 12.8 %), so 1.20 is mean + 1.56 SD. Expect a SOLVE print on roughly 1 in 17 macOS runs if the spread is normal. That is acceptable for a print named in the PR. The other cells have CV ≤ 2 %.
- A per-cell 3-SD rule from n = 3 is too unstable to pin.
- The local loaded-box runs (file 31 L575, L762) are not CI runs and are not used.

**Basis.** Her recorded AX38 4c (RG-1, accepted 2026-11-10). PRD NFR-2 (a print, no gate pressure on accuracy) and NFR-1 (no W_max consequence).

**Options.**
- Printed, k = 1.20 (recommended).
- Asserted. Barred by §5's "never asserted on hosted runners".
- k = 1.15. Fits the data but borrows the defect-trigger factor for a print.
- No bound. Leaves §3.3 (iv) undone.

**Veto reading.** A shared macOS runner will print SOLVE now and then. That is a print, and the flutter deviation beside it gives the context.

No AMENDS (a value inside her rule's delegated slot).

---

## Load-bearing claims

- **Q1-L1.** (c) and AX38 4c's "05i's first run" hand-off. Plan text, BUILD_PLAN L158.
- **Q1-L2.** The 05i run's Linux and Windows values are PASSES30S and in-window. File 3 L9 and L361.
- **Q1-L3.** `listed` is print-only. From the code, L460–476 and L547.
- **Q2-L1.** Item 1's condition is false. Phase-05i §2.1; file 36.
- **Q2-L2.** The K-e12 values. File 3 L70, L81, L220, L231, L338, L349.
- **Q2-L3.** The ≈ 4.8 s figure is AX38 4c's own [Hyp] upper estimate.
- **Q3-L1.** The load values and per-instance sums. Linux: 3 602 + 15 923 = 19 525 ms, against 19 523 printed. Windows: 4 887 + 18 123 = 23 010 ms, against 23 009 printed.
- **Q3-L2.** The about-2× ratio of offline-render staleness to joint staleness. Linux 1 instance: 3 572 / 1 812 = 1.97. Linux 8 instances: 29 412 / 15 705 = 1.87. Windows 8 instances: 31 849 / 15 128 = 2.11.
- **Q3-L3.** The host-thread waits are 3.6–5.0 s from 4 instances on every OS. File 3 L64, L69, L200, L205, L302, L307.
- **Q4-L1.** File 2 L3–6; file 3 L120.
- **Q5-L1.** The means and spreads. File 4's table, re-checked against file 31 L610–615, L679–684 and file 3 L8–9, L206–207, L360–361.

## Future-debt register

| item | commits later phases to | undoing costs | evidence arrives | repaid when |
|---|---|---|---|---|
| Q1 | No re-entry rule exists for a closed entry that later prints OVER30S in-window. Such a run is named in the PR and §0; re-listing would be a new `/fix-plan` reading under (a). | a register line | the 05i PR's CI run; later runs | Phase 13 strict re-check on the release machines |
| Q2 / Q3 | The findings (K-e12, F-a, F-b) hang on 07c conditions 9–10. P1 (condition 9 before the first release) stays open as in file 36. | nothing (records) | 07c condition 7 re-measure | 07c `done`; Phase 13 item 3 |
| Q5 | k rests on 3 runs, 1 in-window on all OSes | a constant | ≥ 3 in-window runs | 07c re-pin |

**Strongest objection.** On Q1, Linux once read 30.18 s in-window (run 42924781618). Closure holds because (c) is unconditional and changes no assertion. It would fall only if the plan meant "stay listed" as overriding (c). §3.3 (ii)'s sentence order and §1 say it does not.

## Summary

| id | decision | state | worst-off seat | sum | confidence | PRD bound | corpus basis | reversal |
|---|---|---|---|---|---|---|---|---|
| Q1 | Linux and Windows low-α entries close under (c); macOS stays listed; `listed` → false (print only) | proposed (FOR MAISARA) | none convened | 0 | high | NFR-1, NFR-2, L101 | none needed | an in-window OVER30S on a closed entry before `done`: re-read under (a) |
| Q2 | Item 1 does not re-open; the K-e12 finding is written into AX38 4c and named above 3 s on Linux and Windows | proposed (FOR MAISARA) | none | 0 | high | L101, NFR-1, NFR-2, NFR-6 | none needed | 07c condition 7 record |
| Q3 | R3 stands; F-a recurs, F-b extended; records appended | proposed (FOR MAISARA) | none | 0 | high | L101, NFR-1, NFR-2, NFR-6, L42 | none needed | a record outside F-a/F-b's mechanism; Phase 13 item 3 |
| Q4 | Did not arise | proposed (FOR MAISARA) | none | 0 | high | NFR-1 | none | none |
| Q5 | Printed `SOLVE` at k = 1.20 × the 3-run per-OS/scene mean; never asserted; re-derived at 07c | proposed (form FOR MAISARA; value for the orchestrator's `/fix-plan`) | none | 0 | medium (n = 3) | NFR-1, NFR-2 | none | 07c re-pin |

## Challenges to settled decisions

None.

## Decided for Maisara

- **Q1:** the Linux and Windows restore-gate register entries close under their own rule (both under 30 s on 05i's first run). The macOS entry stays. No test assertion changes (NFR-1, NFR-2, L101). `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX38 4c register).
- **Q2:** a restore that arrives while a room edit is still processing waits up to 3.3 s at the heaviest 100 m / 96 kHz room (Linux, Windows). This is recorded as a finding with the fix already scheduled in 07c. Raise item 1 is not re-opened (L101, NFR-2, NFR-1, NFR-6). `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX38 4c).
- **Q3:** the 8-instance 100 m load (16–23 s) and the new multi-instance records fall under the findings already named in 05h. The answer stands and nothing new is decided (L101, NFR-2, NFR-1, NFR-6, L42). `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX38 (iv) and 4c record lines).
- **Q4:** the larger-machine action was not needed. Every reference was produced and gated (NFR-1).
- **Q5:** the solve-time warning is a printed line at 1.20 × the 3-run mean, never a CI failure, and re-derived at 07c (NFR-1, NFR-2). The value goes through `/fix-plan` with the interrogator.

**NEEDS MAISARA:** none.

---

Saved verbatim by the orchestrator from the decider's report (the decider reads only). Orchestrator note: `tools/ci/fetch_corpus.sh` fails in this session ("no corpus/*.md in ../audio-resources": the private corpus repository is not attached); the decider states no answer rests on the corpus.
