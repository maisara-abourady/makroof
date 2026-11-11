# Phase 05i — Tail-level switch: remainder of 05h

Size: **M** · Depends on: 05h (`done`, with this split; its CI run green on Linux, macOS and Windows) ·
Read first, in this order: `CLAUDE.md`; this file in full; `docs/phases/phase-05h.md` in full (§1 settled,
§3 D-H1, §5 and §8: its rules and atomicity apply here unchanged); `docs/BUILD_PLAN.md` §2 **AX36 (the
caveat), AX38 (i) and 4c, AX41, AX43, AX44, AX45, AX46**, §0 rows 05h and 05i; `docs/review/phase-05h/`
decider files 19 (D-H1, D-H2), 25 and 27 (D-H3 (a)–(e), H3-F1…F6) with interrogator files 21, 26 and 28;
`docs/review/ledger.md` blocks "phase-05h (session 2)"; PRD NFR-1, NFR-2, NFR-6, NFR-8.

Created on 2026-11-10 under CLAUDE.md's split rule ("If a phase can't be finished in two sessions, split the
remainder into `phase-XXb.md`"): phase 05h's second session landed the switch, the gate and the seam, the
golden round and the local records; the items below did not fit. Nothing here reopens a decision: every
rule is phase-05h's (AX37–AX46 as amended by D-H1, D-H2 and D-H3), applied to the work that remains.

---

## 0. What this phase does

Finishes phase 05h: produces and gates the remaining agreement references in the order the board fixed
(D-H2 (c)), produces the multi-instance and contention records phase 05h could not (AX38 (iv), the K-e12
finding of AX38 4c), pins the restore-gate baselines from the first three-OS run if phase 05h's CI run did
not, evaluates phase-05h §2 items 2 and 3 on the CI records, and keeps the AX41 lists current. The engine,
the estimator, the tolerances, the case list and the goldens' values do not change here; a newly certified
case-band is gated through `update_goldens.py --extend` with its reason, never by editing a value.

## 1. Settled — do not reopen (cite, don't re-derive)

- Everything in phase-05h §1 and §3 (AX37–AX46; D-H1 (i)–(v); D-H2 (a)–(d); H1-F1…F3, H2-F1).
- D-H3 (a)–(e) and H3-F1…F6 (decider files 25 and 27, interrogator files 26 and 28, 2026-11-10): AX43's
  pooled bias check is the additive bound (f9), the catch printed per band and restated at each golden
  round; the AX36 caveat (dead_booth's ladder, ratio 1.50–1.63) is a recorded note; the two contract-limits
  fixtures are known, correct U cases (AX44 reading); `layout4_s1/both_corner` asserts the cap and W1
  both_corner's flags are pinned constants; AX38 (i)'s premise is corrected with its register entry and
  release rule; the K-e12 finding is a record task (AX38 4c); phase-07c §5 conditions 10 and 11.
- The four small rooms are referenced at the 0.625 m rung (H3-F6, the 05h golden round).
- phase-07c follows this phase where phase 05h's gate and records land here (phase-07c §3).

## 2. Raise with Maisara (first message and PR)

1. **The AX38 4c escalation** (phase-05h §2 item 2), if the full-rebuild records were not in phase 05h's
   CI run: the records go to Maisara against the 1 / 3 / 10 s marks, labelled **UI response-time anchors
   (Card et al. 1991), not audibility limits**, with Table 15.1's conditions stated; any room above 3 s is
   named as a finding. The decider answers it for her from the PRD under `docs/board/README.md` ("Who
   answers Maisara's questions") unless one of its three cases applies.
2. **AX38 (iv) load time** (phase-05h §2 item 3), conditional, the same way: if the 8-instance, 100 m
   time until the last instance is audible at project load exceeds 10 s, it goes to Maisara before the
   first release (also phase-13 "Raise with Maisara" item 3).
3. **M-d, an action, not a decision** (AX43 (c)): if the development machine does not fit the 15 GB
   reference class (the BRAS pairs' outer bands) and the 16 GB-runner artifact job does not either, a
   larger machine for a few days is listed for her as an action.

## 3. Scope (carried from phase 05h, exactly)

1. **D-H2 (c)'s remaining references, in the committed priority order** (AX43 (c); decider file 19):
   the CS-NW+ emitter-1 cases, the 0.3 m wall case and W2 both emitters landed in phase 05h's last push
   (410 of 560 gated); what remains is the BRAS pairs' 250 Hz and 4 kHz, then 125 Hz and
   8 kHz, 63 Hz last (the 15 GB class: gated when certified, never claimed as a room validation below the
   Schroeder frequency). Produced offline by
   `tools/validation/hybrid_fast.py` at two rungs per band column, committed by script with provenance
   (tool commit, hash-pinned numba/numpy, rungs, ℓ_ref) and the CHANGELOG reason, never computed live in a
   gate. **Gating:** whatever certifies under D-H2 (a) (the finer-rung change < 1 %, ℓ_ref recorded) is
   gated through `update_goldens.py --extend` with its reason; the rest stays reported and listed, never
   dropped, and every item not finished here gets a **named owner phase before Phase 12 freezes presets
   and before Phase 13 writes copy**. Routes for the 15 GB class: the manual, Linux-only, hash-pinned
   `workflow_dispatch` job on the public 16 GB standard runner that uploads the small reference JSON as an
   artifact for a person to commit (never a live gate input), or M-d (section 2 item 3). AX43's pooled
   catch and room counts are restated in §0 at each golden round (D-H3 (a)); the per-room watch is read.
2. **The AX38 (iv) records not produced in phase 05h** (1, 4 and 8 instances, the AQ10 room and 100 m,
   48 and 96 kHz; each record states the automation speed or rebuild step it was taken at): staleness when
   the instances are automated together (position and room size); staleness of real-time instances while
   another instance renders offline under room-size automation; the offline wait, including the M-parallel
   case; the worst host-thread wait for prepare, restore and offline. **The K-e12 record (AX38 4c
   finding, D-H3 (e)):** a room-or-material edit in flight, then a restore, at the two gated builds, worst
   of 10, three OSes, printed once as a record, never a CHECK; H1-F1's convention stands on the condition
   the gate measures (builder idle) and is not read as met for this case; a record above 2.143 s is a
   finding under the register's form, remedied by phase-07c conditions 9 and 10.
3. **Restore-gate register (AX38 4c, D-H1 (v)):** the growth-bound baselines were pinned in phase 05h from CI
   run 42909003931 (Linux 2 043 ms, macOS 2 106 ms; CHANGELOG reason) and the register's medians re-baselined.
   What 05i carries: the Linux listed entry read 29.62 s (passes 30 s: the §5 (c) warning) on run
   42909003931 and 30.18 s (growth bound met) on the final 05h run 42924781618; if 05i's first run passes 30 s
   again, the entry leaves the register through `/fix-plan` before 05i is `done` (AX38 4c's register text and
   `kGateRegister`'s Linux row to the strict form), else it stays listed and the run is recorded; the macOS
   entry (37.37 s, median 2 106 ms) stays listed with its remedy. The Windows entry, listed from CI run
   42942694523 (36.73 s, median 2 589 ms; strict 28.6–29.5 s on the three earlier runs), is read the same way:
   if 05i's runs read it under 30 s again, its removal under (c) is 05i's call; the runner's speed is the
   recorded likely cause, to be shown at Phase 13 (file 53). The 29.1 s strict / listed rule unchanged; no
   W_max cut, no range change, no seam.
4. **Phase-05h §2 items 2 and 3 on the CI records**: answered for Maisara in phase 05h on CI run
   42909003931 (decider files 33/36, interrogator files 34/37, Seat 7 file 35): findings F-a (the contended
   restore of the reported-set 100 m cube on Linux, worst 4.079 s of 3) and F-b (multi-instance load and
   joint-rebuild staleness, about linear in instance count) recorded in AX38 4c, the 8-instance load above
   10 s recorded in AX38 (iv) with the remedy (phase-07c conditions 9, or 07d, and 10) and the post-07c
   two-time record; what 05i carries is the per-instance restore times inside the (iv) loop if 07c
   condition 7 does not print them (file 36 Q4), and nothing else.
5. **The AX41 lists kept current:** every fixture or preset where the pilot estimate ships
   (`edge_values` at the time of writing) and the known U cases (`edge_values`, `open_field`: cap; K-b3),
   as the reference set and the fixtures change; U at every user-reachable room stays asserted by the D5
   golden (D-H3 (b)).
6. **Plan bookkeeping** through `/fix-plan`: §0 rows 05h and 05i; the 'at the time of writing' counts in
   AX43 / AX45 / phase-05h §5; the AX43 §0 record (the catch per band, the room counts); §6 rows; the
   ledger links.

## 4. Acceptance criteria — automated

- [ ] Every newly certified case-band gated through `update_goldens.py --extend` with its CHANGELOG reason;
      the agreement suite green on three OSes (Release, hidden tag) with AX43's additive pooled check
      'within' in every band and the catch printed; the report prints '<gated> of 560' and '<gated> of 72'
      with the new counts; no reference value edited by hand; every unfinished reference listed with its
      owner phase.
- [ ] The AX38 (iv) records of scope 2 and the K-e12 record printed in the CI job summary on three OSes,
      each with its condition stated; none asserted.
- [ ] The restore gate (AX38 4c) in its register form with the baselines pinned (scope 3), green on three
      OSes; the register entries unchanged in substance (recorded value, median, remedy, closing phase).
- [ ] The AX41 lists (scope 5) match the D5 golden and the reports test.
- [ ] Nightly BRAS green; `report-phase05.md` regenerated if a BRAS reference was gated.
- [ ] pluginval strictness 10 and auval still pass.

## 5. Listening checklist (Maisara)

None new: phase-05h §6's checklist stands on the switched tail level; this phase changes no shipped
output. If a gated BRAS reference changes the listening-pack README's per-room label (gated / reported /
without reference), the README is updated and the change named in the PR.

## 6. Contractor review focus

Provenance of every committed reference (tool commit, pins, rungs, ℓ_ref); that gating only ever extends
the golden; the record conditions (builder idle against mid-build; automation speeds) stated beside each
number; the baselines' CHANGELOG reasons; no per-scene logic.

## 7. Risks and atomicity

- Phase-05h §8's atomicity rule applies: a reference lands with its gating in the same push; no golden is
  regenerated to pass; a case-band that fails on a newly certified reference (|C++ − ref| > τ) is a finding
  for the board (AX43's reversal), never a dropped case.
- The 15 GB class may not fit any machine available: the item keeps its owner phase and the routes above.
- A record above an anchor is a finding for Maisara (section 2), never a range change.

## 8. Out of scope

Everything phase-05h §9 excludes; any change to AX37–AX46's rules, τ, z_FW, N or the case list; Q2a (C)
(phase-07c, which follows this phase); phase-05h's listening pack.

## 9. Definition of done

Section 4 all checked with CI evidence; §0 row 05i `done` with the new counts and the records; this phase's
PR with the contractor focus, the AX/ledger links and the "Raise with Maisara" items that apply.
