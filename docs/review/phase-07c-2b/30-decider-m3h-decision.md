
# 30: Decider on M3-H, decision round. Phase-07c-2b, after Maisara's hand-back

Read-only. The orchestrator saves this as `/home/user/makroof/docs/review/phase-07c-2b/30-decider-m3h-decision.md`.

**Corpus:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. The PRD digest is unchanged from file 28 L10–21.

**State: DECISION, H4+G.** It goes to the interrogator next.

**What decided it:**
- Only three options keep every seat at 1 or below: H3, H3+G and H4+G. The other four each have a seat at 2.
- H3+G and H4+G tie on total tension (8 each).
- H4+G wins the tie because it is cheaper to undo. H3+G holds back phases 08-1 and 08-2 from the start, and that waiting cannot be taken back later.

**No cell is read from conditions.** Every cell below is the seat's own stated rating. Where a seat's file 22 or 14 cell still stands, the file says so.

## 1. Knowledge inventory

| K | what must be known | source | status |
|---|---|---|---|
| K1 | the finding values (a), (b), (c) | file 5 L14–37 | known (builder measurement) |
| K2 | 07d lands before 08-4's freeze; 08-3 has no 07d dependency | phase-07d L79–80; phase-08-3 L3 (re-read) | known |
| K3 | scope 8 pools earlier runs only if the restore path is unchanged | phase-07d L94–96 (re-read) | known |
| K4 | a source 0.1 m from a face is a valid scene | AX6 | known |
| K5 | bit-identity holds only per OS and architecture | AX5; ci.yml (22-seat5) | known |
| K7 | a likely fix is not level-only by construction: an AX22 fix changes restore work, while an AX44-weight fix is level-only but bumps kEstimatorModelId | 29-seat2 K7 (code: Engine.cpp L142–156, DiffuseEstimator.h L10–19, L52–55, test_diffuse_bench.cpp L122) | known (Seat 2's own-cost claim from the code) |
| K8 | a drag or an automation lane past a face lands at exactly 0.1 m | from the code: `ParameterMap.cpp` L32–36, `Validate.h` L28 `kSurfaceClearanceM = 0.1` (re-checked by me); 29-seat6 | known |
| K9 | all cells for the seven options | files 29-seat1…9; 22-seat2 and 22-seat5 where those still stand | known |
| K10 | 07d can start now; 07e waits on 07c-2b, which is `blocked` | BUILD_PLAN §0 L37–38 (re-read) | known |
| K11 | source power near rigid faces at 1 kHz, 0.1 m: less than in free field. Octave averages are about −0.5, −1.6 and −3.8 dB for 1, 2 and 3 faces; the corner pure tone is −10.7 dB. These are derived from Waterhouse 1958 Eq. 3; the d → 0 limit is Toole §12.1 | 29-researcher-RH1 F1–F7, D1–D3 (read; D2 and D3 are derived) | known as derived. **Not load-bearing for the home.** It feeds 07e's ruling. |
| K12 | an independent late-level reference for (c) exists in the repo | from the code: `tools/acoustics/tracer.py`, `tests/golden/phase05h_tracer_reference.json` | known |

No load-bearing gap remains.

## 2. Tension map (now / later, 0–3; each cell is from the seat's own report)

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| H1 | 0/2 | 0/2 | 0/2 | 0/2 | 0/2 | 0/2 | 0/2 | 0/2 | 0/2 | 2 | 18 |
| H2-c | 0/2 | 1/2 | 0/1 | 0/2 | 1/2 | 0/1 | 1/2 | 0/0 | 0/1 | 2 | 16 |
| H2-cg | 0/1 | 1/1 | 0/1 | 0/2 | 1/1 | 0/0 | 1/1 | 0/0 | 0/0 | 2 | 10 |
| H3 | 0/1 | 1/1 | 0/1 | 1/0 | 1/1 | 0/0 | 1/1 | 0/0 | 0/0 | 1 | 9 |
| H3+G | 0/1 | 1/1 | 0/1 | 1/0 | 1/0 | 0/0 | 1/1 | 0/0 | 0/0 | 1 | **8** |
| H4 | 0/1 | 1/1 | 0/1 | 0/1 | 0/2 | 0/1 | 1/1 | 0/0 | 0/0 | 2 | 10 |
| **H4+G** | 0/1 | 1/1 | 0/1 | 0/1 | 0/1 | 0/0 | 1/1 | 0/0 | 0/0 | **1** | **8** |

**Each seat's reason, in its own words:**
- **S1** (29-seat1 §3–4):
  - The gated options are at later 1: "a ruled fix fires M3-8 … the fix's cost, not the home's".
  - H2-c is 2 because F3/F4 can be "sealed and heard before the cause is ruled".
  - H1 is 2 for the same reason plus "preset tuning by ear".
- **S2** (22-seat2; 29-seat2 §2–4):
  - H1 0/2, H2-c 1/2, H3 1/1 and H4 1/1 stand from 22-seat2.
  - H4+G and H3+G are 1/1: "one S session, no change in output"; later, "one golden round … once and before the freeze".
  - H2-cg is 1/1, with the ruling "behind 07d's macOS loop and load loop".
- **S3** (29-seat3 §3–4):
  - Every option is 0 now.
  - Every pre-freeze option is later 1: the "residue is AX49 record (h)".
  - H1 is 2: Phase 10's AX22 dip gate and the 10-1 cache are "built on the pre-fix switch points".
- **S4** (29-seat4 table):
  - H2-cg is 0/2 "as worded": stimuli could be built "after the ruling but before the fix lands".
  - H3 and H3+G are 1/0: they hold 08-1 and 08-2 "for no cue reason".
  - H4 and H4+G are 0/1: "item 15 waits … checklist … may also be heard on the pre-fix engine".
  - H1 and H2-c are 0/2.
- **S5** (22-seat5; 29-seat5 §2–4):
  - H4 is 0/2 "as written": the re-pin order is unrated, and the gate is "on the freeze, not on the measurements".
  - H4+G is 0/1: "scope 8 waits … 07d may have to split".
  - H3+G is 1/0 and H2-cg 1/1 (the gate is "not on a §0 row").
  - H3 is 1/1, H2-c 1/2 and H1 0/2.
- **S6** (29-seat6 §3–4):
  - H1 is 2: 11-2, 11-3 and 12-2 are built before a 13-2 ruling.
  - H2-c and H4 are 1: the order "lives only in 07d prose" / "Notes and prose only".
  - H3, H2-cg, H3+G and H4+G are 0.
- **S7** (29-seat7 §3–4):
  - H4 is 1/1 ("one value").
  - H3 is 1/1.
  - H4+G is 1/1: "the near-certain 07d/07d-b split, about 1 session".
  - H3+G and H2-cg are 1/1.
  - H2-c is 1/2.
  - H1 is 0/2.
- **S8** (29-seat8 §3–4):
  - H1 is 0/2: presets are "designed and voiced" before the cause is known.
  - Every other option is 0/0.
- **S9** (29-seat9 §3–4):
  - H1 is 0/2: "8 presets × 2 modes" re-listening.
  - H2-c is 0/1: "one label round per scene".
  - Every other option is 0/0.

## 3. Minimum-tension working
1. **Bounds.**
   - No option tunes `src/sim` or breaks NFR-8, AX5, AX6 or a recorded decision.
   - Schedule is not a bound (L55, L174).
   - None is dropped.
2. **Veto.** No cell is 3. One cell is conditional: Seat 6 rates "move the clamp inward after release" as veto-grade. That move is not an option on the table, and the 07e text below excludes it from this ruling.
3. **Worst-off seat.**
   - Max 2: H1, H2-c, H2-cg (S4), H4 (S5).
   - Max 1: H3, H3+G, H4+G. These three go forward.
4. **Compose.** No variant brings the maximum to 0.
   - Seat 3's C3-a would take S3 to 0/0.
   - S1, S2, S4, S5 and S7 still hold a 1 with no condition that lowers it. S5's goes to 0 only on "no breach", which is the ruling's outcome, not a design choice.
   - So nothing is composed. The seats' scope texts are adopted inside H4+G (see §5) because each seat states that its text raises no cell.
5. **Sum.** H3 = 9; H3+G = 8; H4+G = 8. That leaves a tie between H3+G and H4+G.
6. **Reversibility.**
   - Under H3+G, 08-1 and 08-2 (two M phases) wait from day one behind 07c-2b's person-dependent ABX dates (S4 "now 1", S7). Waiting time already spent cannot be recovered.
   - Under H4+G the debt is conditional: S5 says it "arises only if a fix is ruled". The evidence (07e's ruling) arrives before 08-3 item 15 and 08-4, both of which are already gated.
   - If the ruling calls for a broader hold, adding it then is one §0 edit. Undoing either option before 07e starts means deleting one file (S1, S2).
   - **H4+G is cheaper to undo.**
7. **Decide: H4+G.** The texts are in §5.
   - **Confidence: medium.** Every cell is stated, no acoustic claim is load-bearing, and every product claim carries an id. But Seat 7's session counts are [Hyp], and the adopted scope prints (§5) enlarge 07e beyond the skeleton Seat 7 sized as "about 1 session".

## 4. DECISION M3-H: H4+G, `phase-07e`, report only, Lead Seat 2
**The phase:**
- 07e is report-only, with Lead Seat 2.
- It gates three things on "07e `done` and the fix phase it rules, if any":
  - 08-3 item 15's stimulus build;
  - **08-4 as a whole** (§0 Depends on, G1);
  - **07d scope 8** (G2).
- Its pytest names the platform that produced its values (G3).

**What is adopted inside it, all from the seats' conditions (none raises a cell):**
- Seat 2's scope amendments;
- C3-a (Seat 3);
- the per-distance print and the "audibility is never a ground" clause (Seat 1);
- the band-wise, rigid-column, diffuse-control and independent-reference prints (Seat 9);
- the medium_room sweep (Seat 6);
- the provisional-verdict text for 08-3 (Seat 4);
- the 07d-b inheritance (Seat 7).

**Not adopted:** Seat 4's optional AC6 layout4 cases.
- Seat 4 says they change no cell.
- They add an 08-3 CI test that Seat 5 has not rated.
- They are left to 07e's loop if a fix is ruled.

**Load-bearing claims:**
- **D-L1 [plan]:** 08-3 depends on 08-2, 04, 05b, 05h and 07, not on 07d (phase-08-3 L3). That is why H2-c leaves item 15 ungated.
- **D-L2 [plan]:**
  - Scope 8 pools runs only if "07d leaves the restore path unchanged" (07d L94–96).
  - An AX22 fix changes restore work (Seat 2, from the code).
  - So G2's order is needed, and its debt is not zero in advance.
- **D-L3 [plan]:** 07d (`not started`) depends only on 07c-1 and 07c-1b. 07c-2b is `blocked` (§0 L37–38). So a 07d/07d-b split under G2 is likely (Seat 7). It costs about 1 session [Hyp], 0 of Maisara's hours.
- **D-L4 [code, re-checked]:** `axisFromNormalized` = 0.1 + clamp01(n)·(side − 0.2). A drag past a face lands at exactly 0.1 m, so (a)'s geometry is reachable from the canvas (FR-3D-5).
- **D-L5 [seats]:** the cells in §2. Sums: H3+G = 1+2+1+1+1+0+2+0+0 = 8; H4+G = 1+2+1+1+1+0+2+0+0 = 8; H3 = 9.
- **D-L6 [PRD]:** acceptance check, below.

**Future-debt register (H4+G):**

| seat | what it commits later phases to | what undoing costs | evidence arrives | repaid when |
|---|---|---|---|---|
| 1 (L1) | a ruled fix fires M3-8: 07c-2b F1/F2 are void for their scene, and the omni rerun is needed for the cross-chain comparison | delete one file before 07e starts | 07e's ruling | "no breach", or the M3-8 rebuild done |
| 2 (L1) | one golden round plus M3-8's rebuild, once, before the freeze | delete the 07e file | 07e's ruling | the fix phase lands before 08-4 |
| 3 (L1) | a fix moves L_f/L_p, the AX21 handover and the AX22 switch points; record (h) goes stale | re-print record (h), re-assert AX49 (C3-a puts both in the fix's AC) | 07e's sweep prints (C3-a) | the fix phase's AC green |
| 4 (L1) | item 15 waits on a long fix (08-3 may split to 08-3b); checklist verdicts heard earlier are provisional | re-hear the provisional items | 07e's ruling | 07e `done` with "no breach", or the re-hear |
| 5 (L1) | scope 8 waits; a 07d/07d-b split; a fix after a re-pin carries ≥ 6 runs plus a CHANGELOG reason plus a §6 row | one /fix-plan | 07e's ruling | "no breach", or the re-pin on the final path |
| 7 (L1) | ≈ 1 session for the split; a fix of more than 1 session holds 08-4 (a delay, not extra hours) | — | 07e's ruling; 07d's start date | the split closes, or 07d is started after 07e (G2 never fires) |

**Strongest objection:**
- **S5's H3+G 1/0 ties on the sum**, and S5 says its now-cost "is certain, while H4+G's later 1 arises only if a fix is ruled". That argues for H4+G, not against it.
- **The real weak point is Seat 7's sizing.** Seat 7 sized 07e as the file 17 skeleton (about 1 session). The adopted prints (medium_room, band-wise, the (c) control and tracer run, C3-a) add work.
- **It holds anyway, for three reasons:**
  - Each print uses tools that already exist: `--diagnostics`, `--images`, `tools/acoustics/tracer.py`.
  - The two-session rule bounds any overrun (07e-b).
  - Seat 7's later 1 already counts a fix that runs past one session.
- **When it would not hold:** if Seat 7, re-asked, rates the enlarged 07e at 2, the decision falls back to H3+G with the same prints. H3+G then holds the lowest maximum alone.

**Reversal condition:**
- **Now:** as above, Seat 7 or Seat 4 rate an adopted text above 1 in a second round.
- **Later:** 07e's ruling. "No breach" on (a)–(c) zeroes the G1 and G2 debts. A fix whose order 07e's loop cannot set before item 15 goes back to the board, with Seats 4, 5 and 7.

**Accepted for Maisara (PRD check):** no hard constraint is broken, and no PRD id points to another surviving option.
- **NFR-8 L112** ("Any valid scene renders correctly"):
  - H4+G rules before 08-4, 11-2 and 12-2, with the fix ordered (G1, G2).
  - H3+G rules equally early.
  - H3 rules early too but leaves the re-pin order unrated (S5 later 1).
- **FR-3D-5 L75** ("anywhere in the scene"):
  - D-L4 makes (a)'s geometry reachable.
  - All three survivors rule before the canvas; equal.
- **NFR-1 L105** ("pass listening tests"): all three build item 15 on the ruled engine; equal.
- **L49/L101** (accuracy first):
  - H4+G orders the CPU re-pin after the acoustic fix, and "never trims or reverts the acoustic fix" (Seat 2's wording, adopted).
  - H3+G is the same. H3 has no such order.
- **L55/L174** (no deadline): H3 and H3+G hold 08-1 and 08-2. That is a schedule cost, which the PRD does not bound, so no id points to them.

## 5. FINAL texts for the plan-editor (one `/fix-plan`)

### Item A: new file `docs/phases/phase-07e.md`
> # Phase 07e — NFR-8 placement findings from the 07c-2b ABX scenes: cause ruling (report only)
>
> Size: **S** (remainder, if needed: `07e-b`) · Depends on: [07c-2b](phase-07c-2b.md) `done` (the engine its golden round leaves) · Lead subject matter: Seat 2 (Engine architect), "late-tail statistics; image-source order; … claims of physical accuracy" · Created 2026-11-24 by phase-07c-2b's M3 loop (`docs/review/phase-07c-2b/` decider files 17 §3, 28, 30 (H4+G); all nine seats, files 29-seat1…29-seat9; researcher 29-researcher-RH1; Maisara's hand-back) · Read first, in this order: `CLAUDE.md`; this file; `docs/review/phase-07c-2b/5-builder-tail-spread.md`, `14-seat9.md` §2, `29-seat1.md` … `29-seat9.md`, `29-researcher-RH1.md`, `30-decider-m3h-decision.md`; `docs/BUILD_PLAN.md` §2 AX5, AX6, AX16, AX21, AX22, AX37, AX39, AX40, AX41, AX43, AX44, AX49; PRD NFR-1, NFR-8, FR-3D-5.
>
> ## Raise with Maisara
> None.
>
> ## Goal
> Establish, for each finding below, whether NFR-8 ("Any valid scene renders correctly") is breached and why, before 08-3's ABX stimuli are built, before 07d's growth re-pin and before Phase 08-4. No `src/sim` change in this phase; nothing is tuned for a scene.
>
> ## Gates (what waits on this phase)
> - Phase-08-4 (§0 Depends on), the build of phase-08-3 item 15's stimuli, and phase-07d scope 8 (the growth re-pin) wait on this phase `done` and on the fix phase it rules, if any. Nothing else waits: 08-1, 08-2, the rest of 08-3 and 07d scopes 1–7 run in parallel; 08-3's checklist verdicts heard before then are recorded provisional (phase-08-3 item 7).
>
> ## Scope
> 1. **Findings** (builder file 5; 14-seat9):
>    - (a) `layout4_s1/both_corner`: emitter L (0.1 m from two walls and the ceiling) has a 1 kHz tail 6.20 / 6.12 dB below R's at equal absolute windows (−6.80 dB from each emitter's own t_mix,e), where Kuttruff Eq. 5.42 expects equal reverberant levels at equal power (indicative, §5.6). Listener at (0.1, 0.1, 0.1) m, 0.1 m from two walls and the α 1 floor; emitter L at (19.9, 29.9, 9.9) m; both within AX44's 0.70 m (both-near branch).
>    - (b) `layout4_s1/both_wall`: tail onsets t_mix,e 0.165 / 0.380 s; from its own onset L's 1 kHz tail energy is +9.39 dB over R's (−0.05 / −0.03 dB at equal windows). Listener 0.1 m from the y = 0 wall, L 0.1 m from the y = 30 wall.
>    - (c) lower priority: `layout4_s0.7/default`, −1.23 dB (L − R) from the common onset 0.380 s (−0.21 / −0.73 dB in the equal windows), not attributed (the room is not diffuse).
>    - The geometry of (a) is reachable from the canvas: a drag or automation lane past a face lands at exactly 0.1 m (`ParameterMap.cpp` `axisFromNormalized`; 29-seat6).
> 2. **Candidate causes:**
>    - (a): the diffuse estimator (AX39/AX41/AX44: the both-near weight w and the capped branch; AX40 fixes only its seed, whose effect is bounded near 0.083–0.33 dB); the image-source set at a corner source. The t_mix,e rule is demoted for (a): L's and R's onsets are 0.376 / 0.379 s.
>    - (b): AX22's realised-k test at a source 0.1 m from a face. From the code, `planEmitter` moves the handover to t_cap,e only when the test fails, and R's 0.380 s matches the fallback time of the other layout4_s1 scenes (Seat 2, [Inferred]). Mechanism to test [Inferred from AX22's formula, not measured]: near-coincident image pairs (about 0.58 ms apart) off a face 0.1 m away enter k_real = S²/Q as separate entries, roughly doubling k_real per such face (×4 for L with two faces against ×2 for R with one), so L can pass the k ≥ 19 test where R falls back. Measured in Python from `--images`: k_real with entries merged within 1 ms (print only). Or the t_mix,e rule.
>    - Confirm with `ismFallback`, `expectedMixS` and `capTimeS` from `--diagnostics`.
> 3. **Measurement** (Seat 2; no `src/sim` edit; deterministic, AX5):
>    - A placement sweep at 0.1, 0.2, 0.5, 0.65, 0.75, 1 and 2 m from 1, 2 and 3 faces; each placement with the listener near and with it far; corners with and without the α 1 face; and `medium_room` (8 × 12 × 4 m) at normalised 0 / 1 on 1, 2 and 3 axes (Seat 6).
>    - For each placement and each emitter: the equal-window level per band, 63 Hz–8 kHz, against Eq. 5.42; E_target against the `matchTail` energy; `--tail-level ax16` against the default; k_real and the fallback flag; the both-near and capped flags, w, n\*, N and W.
>    - Per sweep, the equal-window 1 kHz deficit at each distance, with any step > 1 dB between neighbouring distances flagged (a print threshold, not an audibility claim; Seat 1).
>    - An indicative rigid-boundary column (researcher R-H1: Waterhouse 1958 Eq. 3, image sum; derived octave averages at 0.1 m, 1 kHz about −0.5 / −1.6 / −3.8 dB for 1 / 2 / 3 faces). It is printed and is never used alone to explain a deficit away (Seat 9).
>    - Per placement and emitter: the handover time (after any AX22 fallback) and the AX21 step and dip at it, per band. L_f and L_p at the AX49 gated geometry and on `ax49_l4_cube` (Seat 3, C3-a).
>    - For (b): window energy from the full IR (not tail-only), to test whether L's ISM-to-tail energy is continuous across [0.165, 0.380) s against R's ISM-only energy.
>    - For (c): a diffuse control (the same room with its absorption spread to the same ᾱ) and an independent late-level reference at equal times from the seeded tracer (`tools/acoustics/tracer.py`), with its uncertainty stated (Seat 9).
>    - The restore-work counters on the AX38 4c gate scenes: images per emitter, handover time, W_pilot, n\*, N, W (for the fix's effect on 07d scope 8).
>    - Nothing is fitted to the compared level (no circularity).
> 4. **Board loop** (Lead Seat 2; decider; interrogator SURVIVES):
>    - It rules, per finding: NFR-8 breached / not breached (a level spread > 1 dB at equal times unexplained by the engine's model, Seat 2's test) / not decidable, with the cause. It first rules whether the engine is meant to reproduce coherent near-boundary radiation (R-H1; AX44 "GA limit"). Audibility is never a ground for "not breached" under NFR-8 (Seat 1).
>    - If the loop considers deferring a ruled fix, Seat 1's self-ABX for (a) (29-seat1 §4) is run first; its null never makes (a) "not breached".
>    - Hand-offs it convenes: Seat 1 (audibility, if deferral is weighed); Seat 6 (what the canvas or the AX44 note must say; the AX6 clamp is not a remedy within this ruling, and a change to AX6 is a separate board decision: it remaps saved automation); Seat 9 (attribution for (c); which planned 12-2 presets place a source within 0.5 m of a face); Seat 4 (whether a fix adds `both_corner` and `both_wall` to 08-3 AC6's parity cases); Seats 5 and 7 (any fix's order and cost). Already answered: K8, the drag clamp (29-seat6), and R-H1, the source power near rigid faces (29-researcher-RH1).
> 5. **If a `src/sim` change follows:**
>    - The loop writes it as its own phase file (e.g. `phase-07f.md`), ordered before 08-4 and before 07d scope 8. It is an output change (golden round, §6 row), fires phase-07c-2b M3-8 (rebuild and reseal both ABX scenes before 08-3 listening), and adds no scene- or placement-specific logic (NFR-8).
>    - The `/fix-plan` that creates the fix phase also adds its id to the Depends-on text of §0 row 08-4 and `phase-08-4.md` L3, to 08-3 item 15's stimulus sentence, and to phase-07d scope 8's order line (or 07d-b's §0 row).
>    - If a fix phase lands after 07d scope 8's re-pin is committed, its own automated acceptance criteria include that re-pin on the restore path it leaves: reference and baselines from ≥ 6 green manual runs after its last code change (no pooling of earlier runs), a `tests/golden/CHANGELOG.md` reason and a BUILD_PLAN §6 row, under phase-07d scope 8's rule, its Linux return-to-board clause included. It also prints record (h)'s 8-instance load on its own runs; an exceedance goes to the board. A growth red after the fix goes to 07d's FM-GROWTH board loop; it never trims or reverts the acoustic fix (NFR-8, PRD L49).
>    - A fix that moves the handover, L_f or L_p carries in its own acceptance criteria: AX49's acceptance re-asserted; L_p at the gated geometry printed against 3.82 s; record (h) re-printed at the rated corner if L_f moved there; and the M3-8 rebuild, which names the L4 stimuli if `ax49_l4_cube`'s IR changes (Seat 3).
>    - If the loop finds the fix cannot land before 08-4, that order is its own board ruling, never a default.
>
> ## Out of scope
> Any `src/sim` edit; tuning for a scene; preset or canvas changes (any consequence goes to 11-2, 11-3 or 12-2 by ruling); moving the AX6 clamp; 07d's work.
>
> ## Acceptance criteria — automated
> - [ ] The sweep script and its output JSON committed; the JSON holds every scope 3 print for every placement. The output JSON records the producing platform (OS, CPU architecture, CI runner label, preset, commit); values are produced by the `cli` preset on the ubuntu-24.04 x64 CI runner. A pytest in the `python` job re-runs ≥ 1 placement through `render_cli` and asserts every value bit-identically on that runner; on macOS and Windows, `ismFallback` and k_real equal, times and levels within AX5's cross-architecture bound as converted by the builder and stated in the test (AX5). A disagreement in a discrete field is a finding, never a tolerance. The JSON changes only through `tools/ci/update_goldens.py`; a red caused by another phase's output change (e.g. 07d's C5) goes to the board for whether this ruling still holds, never regenerated to pass.
> - [ ] §0 rows 07e (and 07d, 08-3 and 08-4, if the ruling adds a fix phase) updated.
>
> ## Definition of done
> The report and the board ruling for (a), (b) and (c) are committed under `docs/review/phase-07e/`, and the interrogator returns SURVIVES. If a fix is ruled, the fix phase file and its §0 row exist, and its id is in the Depends texts named in scope 5. The PR lists "Decided for Maisara". CLAUDE.md rules apply.

### Item B: BUILD_PLAN §0
- **New row after 07d:**
  > "| 07e | [NFR-8 placement findings: cause ruling (report only)](phases/phase-07e.md) | S | not started | | | Depends on 07c-2b `done`. Created 2026-11-24 by phase-07c-2b's M3 loop (decider files 17 §3, 28, 30: H4+G; all nine seats, files 29; Maisara's hand-back). Lead: Seat 2 (Engine architect). No `src/sim` change; a fix, if ruled, is its own phase before 08-4 and 07d scope 8. Gates 08-4 (Depends on), 08-3 item 15's stimulus build and 07d scope 8; runs in parallel with 08-1, 08-2 and 07d scopes 1–7. |"
- **Row 07d notes, append:**
  > "Scope 8 waits on 07e and its fix phase, if any (M3-H); if 07d reaches scope 8 first, it splits to 07d-b."
- **Row 08-3 notes, append:**
  > "Item 15's stimuli (AX47 binaural rerun) are built only after 07e `done` (and its fix phase, if any); checklist verdicts heard before then are recorded provisional (item 7; M3-H)."
- **Row 08-4:** replace "Depends on 08-3;" with:
  > "Depends on 08-3 and 07e `done` (and the fix phase 07e's ruling names, if any, added here by id when its §0 row is created);"

### Item C: `docs/phases/phase-08-4.md` L3
Replace "Depends on: 08-3;" with:
> "Depends on: 08-3 and 07e `done` (and the fix phase 07e's ruling names, if any, added here by id when its §0 row is created);"

### Item D: `docs/phases/phase-07d.md` scope 8, prepend
> "**Order against phase-07e (phase-07c-2b M3-H):** this scope runs only after phase-07e is `done` and the fix phase its ruling names, if any, is `done` (§0). If this phase reaches scope 8 first, scope 8 splits to `phase-07d-b.md` with that dependency in its §0 row; 07d-b inherits 'lands before 08-4 freezes its goldens' (scope 6) and premise P1. Scopes 6 and 7 are not held."

### Item E: `docs/phases/phase-08-3.md`
- **Item 15:** replace L74–75 ("Whether item 15's stimulus build waits … `24-m3h-for-maisara.md`).") with:
  > "Stimuli are built only after phase-07e is `done` and the fix phase its ruling names, if any, is `done` (phase-07c-2b M3-H, decider file 30; the fix phase's id is added here when its §0 row is created)."
- **Item 7, append** (Seat 4, adopted):
  > "If heard before phase-07e is `done` (and the fix phase it rules, if any), the checklist verdicts and the both-near render note are recorded 'provisional: engine before the 07e ruling'. A level or dryness remark on a near-face render goes to 07e (or, once 07e is `done`, to the board) as an NFR-8 candidate, never to the HRTF or the headphones."
- **Listening checklist:** after "Record the `hrtfId` … (scope 7).", add:
  > "Verdicts heard before phase-07e is `done` are marked 'provisional: engine before the 07e ruling' (item 7)."

### Item F: `docs/validation/abx-07c-2-run-sheet.md`, C-b bullet (L130–131)
Replace "goes to the board (home pending Maisara's answer on M3-H, `docs/review/phase-07c-2b/24-m3h-for-maisara.md`) as an NFR-8 candidate." with:
> "goes to phase-07e, or, once 07e is `done`, to the board as an NFR-8 candidate (M3-H, decider file 30; R1)."

### Item G: `docs/phases/phase-07c-2b.md`, Out of scope (L192–193)
Replace the line with:
> "- The cause ruling on the NFR-8 placement findings (both_corner, both_wall onset, s0.7 spread): phase-07e (M3-H, decider file 30, H4+G); this phase's PR lists them under Follow-ups."

### Item H: BUILD_PLAN §0 row 07c-2b
In "Waiting: M3-H (case (a), file 24);", replace "M3-H (case (a), file 24)" with "nothing on M3-H (decided for Maisara, decider file 30, H4+G)". This is bookkeeping only and keeps the row truthful.

### Item I: BUILD_PLAN §6, new row
> "| 2026-11-24 | Phase 07c-2b M3-H re-run after Maisara's hand-back (decider files 28, 30; seats files 29-seat1…9; researcher 29-researcher-RH1; corpus c1b171f): phase-07e created (report-only cause ruling on three NFR-8 placement findings, Lead Seat 2; scope with Seat 2's amendments, Seats 1/3/6/9 prints, G2 re-pin and C3-a clauses, G3 producer-platform pytest); §0 rows 07e (new), 07d, 08-3 and 08-4 (Depends on 07e, G1); phase-07d scope 8 ordered after 07e and its fix phase (G2; 07d-b split if reached first); phase-08-3 item 15 gate and item 7 provisional-verdict clause; phase-08-4 L3; run sheet C-b bullet (R1); phase-07c-2b Out of scope. Decided for Maisara; amends nothing. | phase-07c-2b session (Claude), board loop; /fix-plan (plan-editor); `docs/review/phase-07c-2b/` |"

## 6. Summary

| id | decision | state | worst-off seat (cell) | sum | confidence | PRD bound | corpus basis | reversal condition |
|---|---|---|---|---|---|---|---|---|
| M3-H | H4+G: phase-07e report-only, Lead Seat 2; gates 08-4 (Depends on), 08-3 item 15 stimuli and 07d scope 8; G3 pytest; texts §5 | proposed (to the interrogator) | 1 (S1, S2, S3, S4, S5, S7) | 8 (ties H3+G; reversibility decides) | medium | NFR-8 L112, FR-3D-5 L75, NFR-1 L105, L49/L101, L55/L174 | none load-bearing; Kuttruff Eq. 5.42 (indicative); Toole §12.1 + Waterhouse via R-H1 feed 07e only | Seat 7 or Seat 4 rate an adopted text at 2 → H3+G; 07e's ruling ("no breach" zeroes the G1 and G2 debt) |

**Challenges to settled decisions:** none.

**Record correction:** file 28 asked R-H1 whether a boundary source "radiating more power" makes (a) "point the wrong way". R-H1 corrects the premise. At 1 kHz and 0.1 m, rigid-face theory predicts less power than in free field, so the engine's deficit has the predicted sign; its size matches neither the pure-tone value nor the octave estimate. This is not load-bearing for the home.

## 7. Decided for Maisara
- **M3-H:** whether a source pushed into a corner loses its reverb, and whether one source's reverb starts early by the wall, is settled in a small report-only phase (07e).
  - **When:** before the binaural listening stimuli are built, before 07d's CPU re-pin and before Phase 08-4. Any fix lands before all three.
  - **Accepted on:** NFR-8 L112, FR-3D-5 L75, NFR-1 L105, L49/L101 and L174. H3+G serves the same ids but holds 08-1 and 08-2 for nothing the PRD asks.
  - **Who gave most:** Seat 7 (about one extra session if 07d has to split) and Seat 2 (it leads the investigation). They get back a single golden round and re-pin, once, before anything freezes.
  - Amends nothing.

**NEEDS MAISARA:** none.

**Files read:**
- `/home/user/makroof/docs/review/phase-07c-2b/`: 28-decider-m3h.md, 29-seat1.md through 29-seat9.md, 29-researcher-RH1.md, 22-seat2.md, 22-seat5.md, 14-seat7.md, 17-decider-m3-r4.md (§3, §6), 20-interrogator-on-file17.md (R1, R2)
- `/home/user/makroof/docs/PRD.md` (L49–55, L75, L101–112, L174)
- `/home/user/makroof/docs/BUILD_PLAN.md` (§0 L37–43, L55; §6 L534–535)
- `/home/user/makroof/docs/phases/phase-07d.md` (L72–106), `phase-08-3.md` (L1–95, L136–145), `phase-08-4.md` (L1–30), `phase-07c-2b.md` (L185–196)
- `/home/user/makroof/docs/validation/abx-07c-2-run-sheet.md` (L124–135)
- `/home/user/makroof/src/module3d/ParameterMap.cpp` (L10–39), `/home/user/makroof/src/contract/Validate.h` (L28)
- tracer presence checked by search in `tools/` and `tests/golden/`
