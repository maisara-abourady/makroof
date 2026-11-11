# Seat 6 — D-H1 (phase 05h session 2)

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

SEAT 6 POSITION — D-H1

**Files read:** `/home/user/makroof/docs/review/phase-05h/4-decider-convene-D-H1-D-H2.md`, `3-orchestrator-D-H1-D-H2-question.md`, `1-orchestrator-cpp-costs.md`, `docs/phases/phase-05h.md` §2–§3, `docs/phases/phase-07c.md`, BUILD_PLAN AQ10 / AX38 / AX41, `docs/review/phase-05b2/{45-seat6,23-seat6,47,51,53,54,55}-*.md`, PRD "Target users" (line 20), corpus `vorlaender-auralization.md` Tables 6.1 and 15.1 (corpus present, c1b171f).

**1. Reading.** The matter, for my seat: how long a producer waits at project load and after an edit in a 100 m room, when "settling" (phase-07c) arrives, and whether the U note at a gated or default placement changes under a smaller W_max. Cues: positions that recompute heavily (S3); unpredictable settle time (W1, the 1.50–2.59 s macOS spread); a note at a default placement (my (ii)); an automatic level step after the user stops (W4); the picture, here the CI gate, never lying about the engine (criterion 6).

One fact governs all of W: **the user's wait is the non-diffuse build, not W_max.** At 3.05 M the solve is 58–162 ms of a 2.07–2.75 s restore (file 1 §3–§4), 3–7 %. Every W option gives the producer the same 2.0–2.6 s per 100 m / 96 kHz instance today, and (C) does not shorten it on macOS (14 × 2.33–2.59 s = 32.6–36.3 s, derived K15). What differs between the options for my seat is only (i) the SE until (C), (ii) when (C) and the split update land, and (iii) whether the gate stays honest on the OSes the PRD ships (macOS and Windows, PRD line 20; Linux ships nothing).

**2. Ranking and 3–4. Tension (now/later)**

*Gated cube.* **P-a (s = 0.3): prefer, 0/1.** The gated scene is a test box (NFR-8), never a preset; the floor is met via clause (d) pending O18, U silent, no standing finding. **P-b (s = 1): can live with, 1/1.** The gate's reference becomes a scene where U is already raised and Raise item 1 fires; nothing the producer sees changes (the s = 1 cube stays in the reported set either way, and U at that scene is correctly shown: criterion 6 holds). Later 1 for both: the Phase 12 (ii) check, not the gated cube, is what decides whether a preset default ever shows U.

*"Any further rise".* **R-d: prefer, 0/1** (my own reading of the decider's option). The 0.33 dB SE line is the U predicate's line (AX44: capped SE > 0.33 dB), and 1 dB p95 is 1 jnd of G (Vorländer Table 6.1): a crossing changes what the producer sees; a rise within the band does not. Gap to state: under P-b the SE starts above 0.33 dB, so only the p95 line can fire; acceptable to me because the note is already shown there. **R-c: can live with, 1/1** (0.05 dB = 1/20 jnd; escalates to Maisara on rises nobody can hear, but cheap and deterministic). **R-a / R-b: can live with, 1/1** (compare a deterministic fixed-key shift, AX40, with replicate spread; defensible, Seat 1's and 5's ground more than mine). Whichever wins, every rise should be *recorded*; only the crossing escalates.

*Realised-work ratio.* **Q-a…Q-d: no preference, 0/0 each.** 1.05 vs 1.00 moves W_max by ≤ 5 % and SE by ≤ 2.5 % (1/√0.95 = 1.026, my arithmetic on the packet's 1/√N, Vorländer §11.2.5 as cited by the decider; conditions: Poisson counts, replicates govern). Invisible to the user. Seat 5's.

*W_max and the gate.*
- **W-a (3.05 M pinned, gate run and red, (C) next, Phase 07 build named): prefer, 1/1.** Now 1: the user's wait is unchanged; SE at the capped scenes is the lowest of the (A) options; the red gate is internal and says the true thing (criterion 6). Later 1: (C) lands next, so "settling", the one-step crossfaded update (my (b)–(d)) and the Phase 12 (ii) re-check at the final W_max come earliest; undo cost of the pinned value is one golden round, which (C) pays anyway.
- **W-b (≈ 2.0–2.4 M, pinned): can live with, 1/1.** SE ×1.21 at capped scenes (2.09/3.05 = 0.685; 1/√0.685 = 1.208): s = 0.3 cube 0.092 → 0.11 dB, U silent; s = 1 cube 0.36 → 0.44 dB, U already raised; layout 4 1.33 → 1.61 dB, U already raised. The set of placements showing U should not change measurably: rooms near 100 m sit at SE ≤ 0.15 dB (C16 (f)), ×1.21 ≤ 0.18 dB, still under 0.33 dB [Inferred]. Drag step between neighbouring positions (≈ √2·SE, file 23 C12 (b)) grows 0.13 → 0.16 dB at capped scenes: inaudible, below 1/5 jnd. What it buys the user: nothing (CI green on two OSes). It passes Linux by 0.07 s of headroom; a 4 % build drift fails it anyway and (C) comes forward as under W-a. Later 1.
- **W-c ((C) before the gate; 05h blocked or split): can live with, 1/1 if split, 1/2 if 05h is blocked whole.** Merit for my seat: the (A) W_max never ships, so the U-at-default report, the clause-(d) replicates and the Phase 12 (ii) check are computed once at the final value (my condition (e) met by construction). Cost: if the whole of 05h waits, the switch that removes +3.87 / −1.17 / +2.38 dB tail-level errors (phase-05h §0) waits behind a size-M phase: 3.9 jnd of error outlives 0.4 jnd of random error. Pre-beta, so the producer never sees either, but the order is wrong for trust. Ordering knot (07c depends on 05h) is Seat 5/7's and the plan-editor's.
- **W-e (enforced on Linux, recorded on macOS/Windows): can live with, 1/2.** Now 1: nothing changes for the user. Later 2: the block is enforced on the one OS no customer runs and recorded on the two the PRD ships (line 20); the Mac producer (the AQ10 reference machine is an M1) is the one who waits longest, and the forcing function that brings (C) forward disappears if W-b's value makes Linux green. Undo: a plan-wording change, cheap, but the evidence that it was wrong arrives only at Phase 13's release-machine re-check or from the first Mac beta tester. I would accept it only under the conditions below, if the `FOR MAISARA` reading survives.

*n\*_max.* **N-a: 0/0. N-b: 0/1.** Not my matter unless a default placement's U flips: a larger pilot lowers N_cap at capped scenes, so SE at the s = 0.3 cube rises by an unmeasured amount. Seats 1, 3, 4.

*My 3 s check.* Met under every option: 3.05 M × 44.7 ns = 0.136 s per emitter at one thread (W-b: 2.09 M × 44.7 ns = 0.093 s). A correction to my own criterion for phase-07c's loop, not for here: Table 15.1's 3 s row is 3 s per move for the whole scattering part (corpus, Table 15.1, > 1 m translational movement, applied to edits by extension only), i.e. per scene, not per emitter. Two emitters solved serially at my "3 s per emitter" would give the user a 6 s settle at one thread. The 07c re-derivation should read 3 s against W_scene on the single-thread reference, or state that the emitters solve in parallel.

**5. Evidence.** Restore and solve times, SE and U flags: file 1 §2–§4 {Obs; code/measurement; H}. Phase ordering and conditions: phase-07c §3, §5 conditions 3–8; file 47 §4 (iii); file 51 §4 {Obs; plan ids}. U predicate: AX44 and my file 23 condition 3 {Obs}. Drag step ≈ √2·SE: file 23, C12 (b) reading 1 {Obs; prototype}. 1 dB jnd of G: corpus Vorländer Table 6.1 {Obs; H}. 3 s / 700 ms rows and their conditions: corpus Table 15.1 {Obs; H}. SE ∝ 1/√N: Vorländer §11.2.5 as cited in the packet; arithmetic redone above {Obs; conditions Poisson; replicates govern}. "U set unchanged under W-b": [Inferred] from C16 (f) ≤ 0.15 dB near 100 m. "Hosts restore instances serially, so 8 × 2.3–2.6 s ≈ 18–21 s at load": [Hyp] → researcher RQ-H1-3 and AX38 (iv) scope 6 record. Incidents: W1 (ASFX16: an unpredictable 50–200 ms switch forced an engine redesign; here the spread is 1.1 s), W4 (automatic level step after the user stops).

**6. Conditions of acceptance.**
- **W-e → 1/1:** (1) phase-07c is still brought forward next after 05h exactly as under W-a (the OS scope changes which CI job is red, never the schedule); (2) the macOS and Windows restore records go to Maisara in the 05h PR against the 1 / 3 / 10 s anchors (Raise item 2) with the spread stated; (3) the block is re-enforced on all three OSes at Phase 13's release-machine re-check, written into AX38 4c with the reading.
- **W-c → 1/1:** 05h is split (the switch, goldens and reported set land in 05h; only the blocking gate moves to 05i after 07c), not blocked whole.
- **N-b → 0/0:** the U-at-default report (phase-05h scope 9) and the gated-scene flags are re-run at the raised n\*_max in the same golden round, and no valid fixture's default flips U.
- **P-b → 0/1:** none needed beyond Raise item 1 being answered for Maisara with the SE, VOV and p95.

**7. Hand-offs.**
- Seat 2 / Phase 07–10: the 2.0–2.6 s non-diffuse build at 100 m / 96 kHz is the user's whole wait; its reduction, or the Phase 10 split update (phase-07c condition 4, AX38 (v)), is what shortens loads and edits; W_max cannot.
- Seat 5: the ratio (Q), CI integrity of a red-by-design block, the ordering knot under W-c.
- Seat 7: cost of W-a's red gate and of a blocked 05h; nothing may say 100 m rooms load fast.
- Seat 1: R-a…R-d in its measures; whether 0.11 / 0.44 dB SE under W-b changes its 2/1.
- Researcher RQ-H1-3: host tolerance of a 2.3–2.6 s blocked restore, and whether instances restore serially (my 8-instance arithmetic is [Hyp]).
- Phase-07c loop: the per-scene reading of my 3 s (above).
- Maisara: Raise items 1 and 2 as the decider answers them.

**8. Premortem.** If W-e wins without my conditions, the gate goes green on Linux, (C) slides toward the beta, and the first Mac tester opens a mix with a handful of 100 m instances and watches the host freeze for 15–20 s with nothing red in CI; the beta tester notices first, Maisara second at the Phase 13 release-machine re-check.

**D-H2:** no objection to "not required". Nothing user-facing turns on which case-bands are gated; the AX44 note text and the Phase 12 preset check are untouched.
