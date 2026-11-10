# 36 — Decider: round 2 on Raise items 2 and 3 (answers interrogator file 34)

phase-05h (session 2). Verbatim decider output (the orchestrator saved it). Orchestrator note: the decider read Seat 7's file 35 as absent (the two ran in parallel; file 35 landed while this round was in flight) and stripped the notes clause; the addendum below, written after it read file 35, settles the clause on the seat's cells (CONVENE row, tension map, (A) by the tie-break).

# Decider — round 2 on file 33 (Raise items 2 and 3), answering interrogator file 34

Corpus c1b171f. `docs/review/phase-05h/35-seat7-raise-item-3-notes-clause.md` was absent when read: the notes clause is **stripped** from R3 and from the AX38 (iv) addition; Phase 13's notes stay with Phase 13 (its scope 6) and Seat 7. No file written.

## 1. Answers to the five questions

**Q1 (R2, contended restore).** Yes, it covers it. AX38 4c's *Records* list (BUILD_PLAN L139) names "the synchronous restore time at 100 m and 96 kHz, alone and contended … the (iv) records", and its *Escalation* sentence applies to "the numbers" with no subset named; no sentence limits "any room above 3 s" to full rebuilds (phase-05h §2 item 2's "full-rebuild records" is the phase file's paraphrase, and the row governs). File 33 read the subset: **PRD MISREAD accepted; R2 revised** (section 2). The 4.079 s record is named as a finding.

**Q2 (R3, condition 9 → 07d).** If condition 9 moves to `phase-07d.md`, the post-07c synchronous restore still carries the unit-decay synthesis, so the interim-audible time per instance is the non-diffuse restore: on this run's CI figures 2.0–2.7 s at 100 m / 96 kHz (file 31 L198 median 2.043 s, L279 macOS worst 2.669 s, L341 Windows 2.075 s; the solve itself is ≈ 0.1 s: 30.27 / 14 − 2.07, D-H1 (v)), so 8 sequential instances stay ≈ 16–22 s, above 10 s. **No plan line binds 07d before the first release**: 07c L37/L140–142 only create it and re-point the register's macOS "closes at"; phase-13 item 4 binds the diffuse move (07c), not the synthesis; the AX38 4c macOS entry also allows closing at Phase 13's re-check. P1 is therefore a premise, recorded as a debt row (section 4) and caught by phase-13 item 3 on the release machines. Setting 07d's timing is the 07c loop's call (Seat 7 on cadence), not this answer's.

**Q3 (R3, notes).** None. No seat and no plan text authorises a load-time figure in the compatibility notes; AX38 (i)'s sentence covers the stop stall. Clause stripped; the figure reaches her through phase-13 Raise item 3, not through the notes by my ruling. If Phase 13 wants a figure in the notes, that is a Seat 7 convening then.

**Q4 (R3, Windows 10×).** From the code (`tests/unit/test_diffuse_records.cpp` L645–651) the timed loop holds only `prepare(fs, 512, false)`, `beginRestore()`, `restore()` per instance; nothing else runs on that thread, and the staleness phase starts after the load timer stops. The excess over 8 × the single load is +2.0 s Linux (21.1 vs 19.1), +0.7 s macOS (20.4 vs 19.8), +5.4 s Windows (25.6 vs 20.2): per-OS ratios 8.8× / 8.3× / 10.1×. The record does not establish the cause (one run each; candidates, unverified: resident memory growing with instance count, AX38 (ii) ≤ 128 MB per instance plus the baseline, Seat 7's ≈ 2 GB at 8 instances; runner variance). It is not load-bearing: at 8× or 10× the figure is above 10 s and the answer is the same. Routed as a record task: the 07c condition 7 re-measure prints per-instance restore times inside the loop (phase-05i scope 2 carries it if 07c does not).

**Q5 (R3, no saved E_b).** At *project load* the shipping build is post-07c (AX38 (i) release rule), so saved state carries E_b (07c condition 5.1) and the restore level equals the final level (NFR-6); the (iv) record is a project load, so Seat 7's "audible" is met at the correct level and the 10 s line applies to the interim-audible time. Condition 5.2's fallback (the (A)-budget estimate or the previous level) arises for an import or an edit inside a live session (FR-3D-2, FR-3D-1), which is not the (iv) load record; there too the output is audible (never silence, never a known > 1 dB AX16 level, condition 5), which is what Seat 7's condition (2) protects against ("stems silent at load until their turn", file 6 L9). The settle time is named as a finding if above 10 s in either case; it is not a gate.

## 2. R2 re-read against the whole AX38 4c Records list (CI run 42909003931, file 31 CI section)

| record class | vs 1 s | vs 3 s | vs 10 s |
|---|---|---|---|
| full rebuilds, 48 kHz | all < 1 s (100 m cubes 0.69–0.96 s) | — | — |
| full rebuilds, 96 kHz | 100 m cubes 1.75–2.15 s medians (worst run 2.20 s); rest < 1 s | none | — |
| AQ4 intervals | R+2P 31–90 ms (100 ms); 2R+2P 51–160 ms (700 ms); full+2P 1.75–2.13 s (3 s) | none | — |
| restore alone, 100 m / 96 kHz | worst 2.06–2.67 s per OS (gated and reported cubes); flutter 0.64–0.76 s | none | — |
| restore contended | gated cube worst 2.04–2.13 s; **reported-set cube `cube100_lowalpha0.05_s1`, Linux, worst 4.079 s of 3 runs** (L207; the other two 2.03–2.05 s; macOS 1.81 s, Windows 2.07 s) | **F-a, above 3 s** | — |
| (iv) load, 1 instance | 100 m: 48 kHz 1.04–1.27 s, 96 kHz 2.39–2.53 s | none | — |
| (iv) load, 4 and 8 instances | AQ10 48 kHz 4 inst 2.0–2.3 s | **F-b**: 4 × 100 m 4.1–11.5 s; 8 × AQ10 3.9–8.9 s; 4 × AQ10 / 96 kHz 3.0–4.0 s | **8 × 100 m / 96 kHz 20.4–25.6 s** (the (iv) line; 48 kHz 7.8–11.1 s, Windows over) |
| (iv) staleness when rebuilding together (max) | 1 × 100 m / 96 kHz 1.9–2.0 s | **F-b**: 4 × 100 m 3.0–9.5 s; 8 × 100 m 6.2–17.8 s; 8 × AQ10 / 96 kHz 3.5–4.0 s (Linux, Windows) | 8 × 100 m / 96 kHz 16.8–17.8 s |
| bounce, callback p99.9 | no anchor applies: the bounce is reported by its real-time ratio (0.23–0.32× at 48 kHz, 0.73–1.22× at 96 kHz, Seat 8's record for 07c's packet); callback p99.9 under its own rule (§0 row 06; macOS 1-builder 2.2 ms is the shared runner, recorded not gated) | — | — |

**Findings named (new).** **F-a** the contended restore of the reported-set cube on Linux, worst 4.079 s (a worst-of-3 outlier; cause not established in the record). **F-b** multi-instance project load and joint-rebuild staleness scale about linearly with instance count (sequential synchronous restores, from the code; the staleness figures are consistent with the rebuilds running in turn, ≈ n × one rebuild, a derived observation): above 3 s from 4 instances at 100 m and from 4 (96 kHz) or 8 instances at the AQ10 room; above 10 s at 8 × 100 m / 96 kHz. Remedy for both, already scheduled: phase-07c conditions 9 (or 07d if 07c cannot carry it) and 10, after which the synchronous restore is ≈ 0.15 s and the solve and synthesis times move to the (iv) staleness records under AX38 (iii) "settling"; re-measured by 07c condition 7; never a W_max cut, range change or seam (D-H1 (v)(d)). The per-operation findings of F-b are the same cause as the AX38 4c synthesis finding seen n times; F-a may be too, unproven.

### FOR MAISARA R2 (revised) — phase-05h §2 item 2

**Question.** Which records exceed the 1 / 3 / 10 s anchors, and what is named as a finding?

**Answer.** "Against AX38 4c's whole Records list on CI run 42909003931: at 48 kHz every full rebuild is under 1 s (100 m cubes 0.69–0.96 s); at 96 kHz the 100 m cubes rebuild in 1.75–2.15 s (medians; worst run 2.20 s), every other room under 1 s; the AQ4 intervals are under their anchors (R + 2P 31–90 ms of 100 ms, 2R + 2P 51–160 ms of 700 ms, full + 2P 1.75–2.13 s of 3 s); the restore alone at 100 m / 96 kHz is 2.06–2.67 s worst per OS; the single-instance load 2.39–2.53 s. **Two findings above 3 s:** (F-a) the contended restore of the reported-set cube `cube100_lowalpha0.05_s1` on Linux, worst 4.079 s of 3 runs (the other two 2.03–2.05 s; the gated cube's contended worst 2.13 s; cause not established); (F-b) multi-instance load and joint-rebuild staleness, about linear in instance count: above 3 s from 4 instances at 100 m and from 4 (96 kHz) or 8 instances at the AQ10 room, up to 16.8–17.8 s staleness at 8 × 100 m / 96 kHz; its 8-instance load above 10 s is item 3. No single-instance record exceeds 3 s. Both findings share the remedy already scheduled, phase-07c conditions 9 (or 07d) and 10, and the 07c condition 7 re-measure; the 100 m / 96 kHz single rebuild has its cause named in AX38 4c (the unit-decay synthesis, 95.5 % of the non-diffuse restore). The marks are UI response-time anchors (Card et al. 1991, visual UI), not audibility limits; Table 15.1's 3 s row covers translational movement > 1 m, derived from 30–50 cm/s VR movement, and is applied to a rebuild by extension only, and to n instances' rebuilds in turn by a further extension."

**PRD ids.** L101; NFR-2; NFR-3 / FR-SIM-6; FR-3D-1; L42 (several instances of one scene is a PRD use); AX38 4c and (iii) (her acceptance 2026-11-10).

**Reasoning.** AX38 4c escalates "the numbers" and names "any room above 3 s" a finding; two classes cross it and are named. A 1.7–2.7 s single-operation wait at 100 m / 96 kHz is heavy latency that buys accuracy (NFR-2) with the session usable (L101: the previous IR keeps playing; the position path is 31–90 ms). The n-instance figures are the same build n times in turn, cured at the cause by 07c, not by a cap. Options: *name F-a and F-b, remedy as scheduled* (chosen) — serves L101 / NFR-2, NFR-1 (uncut); *name nothing* (file 33) — misreads her row; *cut W_max or the range* — barred by D-H1 (v)(d), strains NFR-1; *pull 07c into 05h* — breaks the one-phase rule, 07c is next.

**Veto reading.** That "a room above 3 s" must block 05h `done` or force a cap rather than be named with its remedy; AX38 4c says "named as a finding", and D-H1 (v)(d) bars the cap. No AMENDS (a reading; the findings are record lines).

## 3. FOR MAISARA R3 (revised; notes clause stripped) — phase-05h §2 item 3

**Question.** The 8-instance, 100 m load at 96 kHz is 21.1 / 20.4 / 25.6 s (Linux / macOS / Windows), over the 10 s line; at 48 kHz 9.9 / 7.8 / 11.1 s (Windows over). What does "goes to Maisara before the first release" require now, and what reaches her?

**Answer.** "The condition fired. 'Goes to Maisara before the first release' is an escalation of information to her, so that the figure is never found by customers first (Seat 7's own purpose); the decision it carries, whether the first release may ship that load, is answered here from the PRD and re-asked once on the shipping build. **Record now, as a finding under AX38 (iv):** 8 instances at the 100 m low-α cube, 96 kHz, 20.4–25.6 s; 48 kHz 7.8–11.1 s; AQ10 room 96 kHz 5.9–8.9 s; taken as 8 sequential synchronous restores on one thread, 8.8× / 8.3× / 10.1× the single-instance load (2.39 / 2.47 / 2.53 s; the excess over 8× is unexplained in the record and is re-measured per instance), the restore that D-H1 (v) already lists as a registered defect. **No new remedy:** the scheduled one applies: phase-07c conditions 9 (or phase-07d if 07c cannot carry it) and 10 move the unit-decay synthesis and the diffuse solve off the synchronous restore (≈ 0.15 s left on it after both moves), and the build measured here never reaches a producer (AX38 (i) release rule, closed by condition 10). **Re-measured after 07c** (condition 7): the (iv) record then states two times per instance, until it is audible at the interim level (07c condition 5; at project load the saved E_b, so the restore level is the final level) and until its final tail has settled; **phase-13 Raise item 3 applies the 10 s line to the first on the release machines and names the second as a finding if it is above 10 s.** If condition 9 lands in 07d or later, the interim-audible time stays the non-diffuse restore (≈ 2.0–2.7 s per instance at 100 m / 96 kHz) and phase-13 item 3 fires on it. What goes in the first release's compatibility notes is Phase 13's question, with Seat 7; this answer puts no figure there."

**PRD ids and decisions.** L101; NFR-2; NFR-1 (W_max uncut); NFR-6 (restore level = final level, 07c condition 5.1); L20; L42; AX38 (i), (iii), (iv), 4c and D-H1 (v) (her acceptance 2026-11-10); phase-07c §5 conditions 1, 5, 7, 9, 10.

**Reasoning.** A 20–26 s one-time project load, each instance audible in turn, nothing lost, is heavy latency that buys accuracy (NFR-2) and leaves the session usable afterwards (L101); but the number belongs to a build the plan already bars from producers and already remedies, so a release decision on it decides nothing real. The PRD ranks accuracy above the wait (L49, L101), so cutting W_max to pass 10 s is out twice over. Options: *record + scheduled remedy + re-measure, Phase 13 item 3 applies the line* (chosen) — serves NFR-1, NFR-2 / L101, NFR-6; strains nothing; *NEEDS MAISARA now* — outside the three cases (the PRD and her AX38 (iv) rule settle it; the build cannot ship); *cut W_max / range* — barred by D-H1 (v)(d), strains NFR-1; *pull 07c into 05h* — breaks the one-phase rule; *a figure in the notes now* — no seat or plan text authorises it (stripped).

**Veto reading.** That the 10 s line is a release gate on the settled tail, not on audibility, so a post-07c settle time above 10 s must block the first release rather than be named as a finding; the PRD does not say so and NFR-2 points the other way.

`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX38 (iv): the 2026-11-10 record and the answer appended; the remedy clause "condition 9, or 07d"; the post-07c record's two times; the 10 s line applied at Phase 13 to the interim-audible time, the settle time named as a finding.)

**Convening.** Still no seat on R2/R3 as revised (readings of her row against records; the stripped clause was the only new public-wording rule). If the orchestrator's parallel Seat 7 run (file 35) lands, its cell goes to Phase 13's notes question, not to this answer.

## 4. Corrections applied and the P1 debt row

- "95.5 %" → "of the non-diffuse restore (AX38 4c finding, 3.14 of 3.29 s)", not of the full rebuild.
- "≈ 8 ×" → per-OS 8.8× / 8.3× / 10.1× (Q4).
- Seat 6 register row re-sourced: Seat 7's condition (1) and AX38 (iii) (file 12 L52; BUILD_PLAN L340), not L56.
- Remedy clause everywhere: "condition 9, or 07d if 07c cannot carry it".

**Future-debt register (R3, revised).**
| seat | commits later phases to | undoing costs | evidence arrives | repaid when |
|---|---|---|---|---|
| 7 (1/1 on file) | the 10 s line waits on 07c's figure; the per-instance excess re-measured | nothing (a record) | 07c condition 7 record; Phase 13 item 3 | Phase 13 |
| 7 (condition (1)) / AX38 (iii) | "settling" shown on every instance waiting at the gate at load | a Phase 10/11 UI item already scheduled | 07c / Phase 11 | Phase 11 |
| **P1 (Seats 5, 7)** | **condition 9 lands in 07c, not 07d, and before the first release**; if not, the interim-audible time stays the non-diffuse restore (≈ 2.0–2.7 s per instance at 100 m / 96 kHz; 8 instances ≈ 16–22 s > 10 s) | nothing extra: Phase 13 item 3 fires on the release-machine figure and is answered then | 07c's loop (fit of condition 9); Phase 13 item 3 | 07c `done` with condition 9, or 07d with a "before the first release" timing line set by 07c's loop (Seat 7 on cadence) |
| 1 | none (anchors labelled, not audibility) | — | — | — |

**Strongest objection (unchanged, extended).** Seat 7 L9 "slower project loads … a support ticket and a lost trial if nothing explains it". Holds because the shipping build is post-07c with the interim tail at the saved level and "settling"; it would not hold if condition 9 slipped past the first release (P1) — which phase-13 item 3 catches by re-firing on the release-machine figure, and phase-13 item 4 catches for the diffuse half.

**Confidence** high for the records and the PRD reading; medium on R3's timing (P1 open). **Reversal:** the post-07c (iv) record on Phase 13's release machines above 10 s to the interim-audible time; or 07c's loop sending condition 9 to 07d without a release-timing line.

## 5. Text for the plan-editor

**AX38 (iv) addition (replaces file 33's).** "Recorded (CI run 42909003931, 2026-11-10, phase 05h; 8 sequential synchronous restores on one thread, `test_diffuse_records.cpp` L645–651; Linux / macOS / Windows runners, one run each): 8 instances at the 100 m low-α cube, 96 kHz 21.1 / 20.4 / 25.6 s (8.8× / 8.3× / 10.1× the single-instance load 2.39 / 2.47 / 2.53 s; the excess over 8× is unexplained and the 07c condition 7 re-measure prints per-instance restore times); 48 kHz 9.9 / 7.8 / 11.1 s; AQ10 room 96 kHz 7.8 / 5.9 / 8.9 s. The 10 s line fired (decider file 33 R3, answered for Maisara): a finding of a build that never reaches a producer (AX38 (i) release rule); remedy phase-07c conditions 9 (or 07d if 07c cannot carry it) and 10; re-taken after 07c (condition 7) with, per instance, the time until audible at the interim level (07c condition 5; the saved E_b at project load) and the time until its final tail has settled; phase-13 Raise item 3 applies the 10 s line to the former on the release machines and names the latter as a finding if above 10 s. Premise P1 on the register: condition 9 lands before the first release; if it goes to 07d, the interim-audible time stays the non-diffuse restore and phase-13 item 3 fires on it."

**AX38 4c record line (R2 findings; after the *Escalation* sentence).** "*Record against the anchors (CI run 42909003931, 2026-11-10, decider file 33 R2):* at 48 kHz every full rebuild < 1 s; at 96 kHz the 100 m cubes 1.75–2.15 s (medians), all other rooms < 1 s; AQ4 intervals under their anchors (R + 2P ≤ 90 ms, 2R + 2P ≤ 160 ms, full + 2P ≤ 2.13 s); restore alone at 100 m / 96 kHz worst 2.06–2.67 s; single-instance load 2.39–2.53 s. Findings above 3 s: (F-a) the contended restore of `cube100_lowalpha0.05_s1` (reported set) on Linux, worst 4.079 s of 3 runs (others 2.03–2.05 s; gated cube contended worst 2.13 s; cause not established); (F-b) multi-instance load and joint-rebuild staleness, about linear in instance count: above 3 s from 4 instances at 100 m (4.1–11.5 s) and from 4 (96 kHz, 3.0–4.0 s) or 8 instances (3.9–8.9 s) at the AQ10 room; staleness up to 16.8–17.8 s at 8 × 100 m / 96 kHz; the 8-instance load above 10 s is under (iv). Remedy for both: phase-07c conditions 9 (or 07d) and 10, re-measured by 07c condition 7; never a W_max cut, range change or seam (D-H1 (v)(d)). The bounce ratio and callback p99.9 are reported under their own rules (07c packet; §0 row 06)."

**Decided for Maisara (revised lines).**
- R2: against AX38 4c's whole Records list, no single-instance record exceeds 3 s; two findings are named — the contended restore of the reported-set 100 m cube on Linux (4.08 s, one outlier run) and multi-instance load / joint-rebuild staleness, which grows about linearly with instance count (above 3 s from 4 instances at 100 m); the 100 m cubes at 96 kHz rebuild in 1.75–2.15 s, every other room under 1 s; remedy already scheduled in phase-07c (L101, NFR-2, NFR-3, FR-3D-1, L42). Seat 6's user gives a 1–2.7 s wait at 100 m / 96 kHz; repaid at 07c conditions 9–10. No AMENDS.
- R3: the 8-instance 100 m load at 96 kHz (20.4–25.6 s, CI run 42909003931) crossed the 10 s line; recorded as a finding of a build that never ships; remedy phase-07c conditions 9 (or 07d) and 10; re-measured there with time-to-audible and time-to-settle shown; Phase 13 item 3 applies the 10 s line to the release build; nothing decided about the compatibility notes (Phase 13, with Seat 7) (L101, NFR-2, NFR-1, NFR-6, L42). Seat 7 gives the most (the wait outlives this phase, and P1 is open); repaid at 07c and Phase 13. `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX38 (iv).)

**NEEDS MAISARA:** none. **State:** R2 revised (PRD MISREAD accepted, findings named); R3 revised (clause stripped, corrections and P1 row applied); both proposed for the interrogator's round-2 check.


---

# Decider — round-2 addendum: R3's notes clause settled on Seat 7's cell (file 35)

Supplements my round-2 report (same decisions R2 and R3; only the notes clause and its convening change here). Corpus c1b171f. No file written.

## CONVENE row (one row, the clause only)

`7 Founder | convened (the notes clause of R3 only) | README convening table, Seat 7: "public wording and marketing claims"; a load-time sentence or figure in the first release's compatibility notes is public wording, and AX38 (i)'s scoped sentence covers only the stop stall (interrogator file 34 Q3) | brief: file 33 L19/L25 clause; options (A) strip now, Phase 13 decides with Seat 7 convened; (B) keep as written (a figure in AX38 (i)'s scoped form if Phase 13's interim-audible time is above 10 s); (C) a weaker form (plan text committing Phase 13 to decide the sentence with Seat 7, no number as a promise, no host, not in launch copy); read phase-13 L15–20, L81–89, BUILD_PLAN L139 AX38 (i); rate now/later, conditions of acceptance | answered: file 35`

All other seats: not required for the clause (Seat 6's "settling" wording is a hand-off recorded below, not a rating on notes content).

## Tension map (the clause; Seat 7 from file 35 word for word)

| option | Seat 7 now / later | Seat 7's reason |
|---|---|---|
| (A) strip | 0 / 1 | now: "Nothing lost; the rule lives in file 6 and phase-13 items 3–4 instead of plan text" (L18); later: "Same debt plus the small risk Phase 13 reads the notes as scope-6 bookkeeping and writes them without a seat round; caught by the decider's convening table" (L23) |
| (B) as written | 1 / 2 | now: "A public-wording rule set without me, on a form borrowed from a different fact, before the figure exists" (L19); later: "commits the notes to carry a *number* measured on release machines, which is not the customer's machine … after publication: a public correction, the costly kind" (L24); conditions L35: "figure" → a sentence in (i)'s form, trigger → what a customer would notice before the settling state explains it; then 0 / 1 |
| (C) weaker form | 0 / 1 | now: "writes down the two rules I actually hold … and leaves the sentence to the moment the number and the 'settling' UI exist" (L17); later: "Commits Phase 13 to convene me on scope 6; undo is a plan edit (hours)" (L22) |

Other eight seats 0 / 0 (not required; reason in the convening row).

## Working

1. Bounds: none broken by (A) or (C); (B) as written conflicts with AX38 (i)'s "no stall figure as a product promise" by form (Seat 7 L9: "internally contradictory"), and the PRD is silent on notes content — not a PRD reading, so (B) could not be answered for her without a seat (file 34).
2. Veto-grade: none.
3. Worst-off: (A) max 1, (C) max 1, (B) max 2 → (B) out as written.
4. Compose: (B) with Seat 7's two edits (L35) is, in the seat's words, "(C) and I would rate it 0/1" — it is (C), not a new variant; nothing lowers the maximum below 1.
5. Sum: (A) 1, (C) 1 — tie.
6. Reversibility: (A) writes nothing, so there is nothing to undo when Phase 13 item 3's record arrives; (C)'s undo is "a plan edit (hours)" (L22). (A) is cheaper → **(A) strip**, with (A)'s later-1 risk closed by a register row rather than plan text.
7. Decided: **(A).** The notes clause is struck from R3's answer and from the AX38 (iv) addition (as my round-2 report already has it). Seat 7's preference for (C) "by a hair" is recorded; the cells tie and the ordering's tie-break, not my taste, picks (A). Seat 7's hand-off L40 ("Phase 13's convening table must list Seat 7 for scope 6 whichever option wins") is adopted as the register row below, which is exactly what Seat 7 says catches (A)'s risk (L23).

**R3's quoted answer stands as in my round-2 report**, ending: "What goes in the first release's compatibility notes is Phase 13's question, with Seat 7; this answer puts no figure there." No AX38 (iv) or phase-13 text on notes content is proposed. Phase-13 scope 6 is touched only through the register row; if the plan-editor prefers one line of plan text there ("notes content on project load: decided at Phase 13 with Seat 7 convened"), that is (C) and needs no new seat round (Seat 7 rated it 0 / 1), but it is not what this decision asks for.

## Register rows added (R3)

| seat | commits later phases to | undoing costs | evidence arrives | repaid when |
|---|---|---|---|---|
| 7 ((A) later 1) | Phase 13's convening table lists Seat 7 on scope 6 (the compatibility notes, project load included); no number as a product promise, no host, not in launch copy, unless Seat 7 rates otherwise then | nil (nothing written now) | Phase 13 item 3's release-machine record; the first beta tickets (Seat 7 L24) | Phase 13's notes decided with Seat 7 convened |
| 6 (hand-off, Seat 7 L38) | the "settling" state at project load (AX38 (iii), Phase 11) is what makes any notes sentence true; its wording is Seat 6's | a Phase 11 UI item already scheduled | Phase 11 | Phase 11 |
| 5 (hand-off, Seat 7 L39) | the release-machine measurement and the meaning of "audible at the interim level" on the first load of an imported scene (my Q5 answer: a project load carries the saved E_b; an import in a live session takes condition 5.2's fallback, never silence) | nil | 07c condition 7; Phase 13 item 3 | Phase 13 |

**Strongest objection on the clause.** Seat 7 L43 premortem: "Phase 13 pastes 'up to 12 s' into the notes, a producer with 16 GB and eight 100 m stems measures 40 s, posts both numbers". (A) removes the rule that would have licensed the number; the residual risk (notes written as bookkeeping) is the register row, checked by the interrogator at Phase 13's convening.

**Confidence** high (one seat, three options, no cell read from conditions, no acoustic claim; product claims cite AX38 (i) L139 and phase-13 L15–20, L81–89). **Reversal:** Phase 13 item 3's record plus a Seat 7 round there rating a sentence as needed — then Phase 13 writes it; nothing here to undo.

## Revised "Decided for Maisara" line for R3 (replaces the round-2 one; R2 unchanged)

- R3: the 8-instance 100 m load at 96 kHz (20.4–25.6 s, CI run 42909003931) crossed the 10 s line; recorded as a finding of a build that never ships; remedy phase-07c conditions 9 (or 07d) and 10; re-measured there with time-to-audible and time-to-settle shown; Phase 13 item 3 applies the 10 s line to the release build; the compatibility notes get no load-time rule or figure now — Phase 13 decides them with Seat 7 convened (L101, NFR-2, NFR-1, NFR-6, L42). Seat 7 gives the most (the wait outlives this phase, P1 open); repaid at 07c and Phase 13. `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX38 (iv).)

**State:** R2 revised (findings F-a, F-b named); R3 revised (clause stripped on Seat 7's cells, corrections and P1 row applied, notes row added); both proposed for the interrogator's round-2 check. NEEDS MAISARA: none.
