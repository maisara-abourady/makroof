# Seat 2 — D-H3 (a), (b), (c), (d)

SEAT 2 POSITION

Corpus present (`SOURCE_COMMIT` c1b171f per the decider); no corpus line was re-read this round, so the few acoustic facts below are from my register or the code and tagged. Everything numeric is from file 18 (K-a3/K-b3), files 9/13/14, the plan rows, or the code, cited as such. Settled items are not rated.

## D-H3 (a) — AX43's pooled bias check vs the references' rung error

**Reading.** Whether the pooled |mean z| ≤ 3/√M keeps its z, carries ℓ_ref, or regroups. Cues: S6 (a claim of accuracy and its circularity trap) and my validity map, "validation design: kind with a trap".

**What ℓ_ref is.** The patch-discretisation residual of `ref_hybrid` is a deterministic, signed, systematic error of one mesh: identical in sign and similar in size across the 10 pairs of one BRAS room and across both emitters of one Phase 04 room; uncorrelated between rooms. The stored `l_ref` is the magnitude of the last halving (from the code: `db(1.0 + k.lRef[b])`, used as a positive allowance), i.e. a Richardson-type bound on the residual (for first-order convergence the residual at the fine rung ≈ the last change) [Inferred; the convergence order of the hybrid was never fitted]. It is not a 1-σ random term. Consequences: (i) a per-item quadrature (option (a)) is the E_n form and is defensible per item; (ii) when pooling, a within-room systematic term does not shrink by 1/√M, so the correct pooled treatment groups by the object that carries the error, the reference room: option (e). File 18 confirms the mechanism: the +0.44 is carried by `dead_booth` (z +8, SE 0.002 dB, ℓ_ref 0.17 %), `cr4` (ten pairs, z +1.3) and `cr3`, while the s = 1 absorbing layouts (ℓ_ref 0.19–0.33 %, the ℓ-sensitive cases of AX36) pull −1.9 to −2.2; the mean signed deviation is +0.0009 dB. The file 16 premise SE ≈ 0.035 dB fell: mean SE is 0.0077 dB, so at 500 Hz–2 kHz the pooled check resolves 0.001 dB, 30× finer than AX46's accepted 1 % (0.043 dB) bias bound. A test whose power grows with M against a fixed systematic floor must fail eventually whatever the estimator does; that is the structural fault, not the estimator.

**My dilution argument in reverse.** Yes: per-class limits 0.548 / 0.775 / 1.061 vs 0.412 lose power against a bias shared by every class (z 0.45 everywhere would pass each class and fail the pool). But the current failure is not that pattern (classes have opposite signs), and the data show (b) and (d) still red (BRAS 0.56–0.60 vs 0.548; reference class 1.0–1.2 vs 0.905): regrouping by class neither explains nor passes. (e) passes with ≤ 0.19 vs 0.64 and keeps Seat 1's catch: a shared 0.02 dB estimator bias gives z_(a) ≈ 0.02/√(SE² + ℓ²) ≈ 2–2.5 per cluster, mean ≫ 0.64 [arithmetic on file 18's SE and ℓ_ref].

**Ranking and tension (now / later).**

| option | rank | now | later | reason |
|---|---|---|---|---|
| (e) per reference room, z_(a) | prefer | 1 | 1 | the grouping matches the error's carrier; passes with 3× margin; the catch survives; costs a room-id field in the golden (derivable from the case name) |
| (a) quadrature per case-band, pooled M = 53 | can live with | 1 | 1 | passes (0.31 vs 0.412); right per item, under-counts the within-room correlation of cr4's ten pairs (a conservative direction here: it over-penalises them, not under) |
| (d) per class + ℓ_ref | cannot live with | 2 | 2 | red at the push by data (BRAS 0.59–0.60 vs 0.548) with no path to green except a finer rung |
| (b) per class, z as written | cannot live with | 2 | 2 | red at the push in two classes; loses pooled power |
| (c) keep, red by design | cannot live with | 2 | 3 | a check that cannot pass once SE_pooled < ℓ_ref is uninformative; every added case worsens it; the next engineer loosens it or ignores all red |

**Commitments and undoing.** (e)/(a): a `test_diffuse_agreement.cpp` formula/grouping change, no golden regeneration (ℓ_ref already per case-band); undoing is the same edit. (c): a permanent finding beside Phase 13's accuracy wording. All: the AMENDS line on AX43.

**The finding that must be recorded whichever wins (my condition for any option at 1).** `dead_booth`: C++ − ref = +0.39 % at z 8, i.e. 2.3× its ℓ_ref: the one place where the data speak about the estimator and not only the reference. It is 1/60 of G's jnd (1 dB, Vorländer Table 6.1 via AX42) and inside AX46's 1 % with 2.5× margin; not a product defect. The non-circular check is cheap: AX36 (e)'s 0.625 m rung costs 15–49 GB in a 20 × 30 × 10 m (A) case; a booth's surface is ~40× smaller, so its kernel is ~1 000× smaller [derived from AX36 (c)'s per-patch² scaling; Hyp on the exact size]. Ask the orchestrator to (i) compute the 0.625 m rung for dead_booth, living_room, classroom, club and record whether the reference moves toward the C++; (ii) one script line: sign(C++ − ref_1.25) against sign(ref_1.25 − ref_2.5) per case-band (the ladder's direction); same sign = the residual explanation holds, opposite sign on a room = an estimator-bias candidate. These are K-a4's real reconciliation.

**Evidence.** [Observed] file 18 K-a3/K-a4; file 9; from the code L196–284; AX36, AX42, AX43, AX46 (plan ids). [Inferred] the Richardson reading of ℓ_ref; cluster-power arithmetic. Researcher RQ-H3-1 to confirm the E_n / correlated-reference treatment.

**Hand-offs.** Seat 1: whether (e)'s catch (≈ 0.02 dB shared) is still its 0.02 dB. Seat 9: the BRAS rung on CR4 (the largest room, the costliest next rung). Seat 5: implementability; no golden regeneration. Orchestrator: the two code tasks above.

**Premortem.** (c) is chosen: the suite is red on every run for a year, a real +0.3 dB estimator bias arrives with a refactor, and nobody sees it because the pooled line was already red; Seat 9's BRAS nightly notices, months later.

## D-H3 (b) — U raised at the default placement of `edge_values` and `open_field`

**Reading.** Is a shipping pilot at a contract-limits slot, and a cap at an open field's near-zero total, the rule as designed or a defect; does any generic rule change either. Cues: §4-7 (cost growth with the window) and criterion 5 (honesty, never false precision).

**Engine reading.** `edge_values` (1.5 × 100 × 4 m, V 600 m³, S 2 300 m²): mean free path 4V/S ≈ 1.0 m [register: Kuttruff's 4V/S; section not re-read], so ≈ 330 hits per second of window; at each hit the gather runs over the lattice images within the remaining range, whose count grows with (c·t_rem)³/(8V) — about 4 000 per gather at 0.5 s in this cell [derived]. One history costs ~10⁶ evaluations; the first 64-history block exceeds W_scene (N_cap 0, from file 18: N_need 147 242), so AX41's "if N_cap is under one block, the pilot estimate ships, flagged" fires exactly as written. The pilot stops on work, not on its own SE, so no SE-coupled stopping bias (my S2-a reading); the estimate is honest at SE 0.76 / 3.98 dB and U says so. Correct outcome, not a defect. To reach the 0.083 dB target it needs ≈ 1 000 × W_scene; no pinned constant reaches it. `open_field`: the total is the floor's single scatter (every other face α = 1 kills a path at its second hit, `reflectOnly > 0` from the code), the score is sparse, so N_need (1.4–2.4 M, file 18) is 500× N_cap: a cap on a tail that AX37 (5.4) puts > 60 dB below the direct sound. U is true and inaudible; whether to display it is a Seat 1/6 question. File 18 shows U at every moved placement of both fixtures through the capped branch: "cannot be moved" is now shown.

**Would any generic rule change either?** No parameter-level rule: W_max and n\*_max are pinned (AX41) and 1 000× short. A formulation-level change (energy-pruned gather lists, applied everywhere) might cut the slot's cost, but it changes E_target (a golden round), is unmeasured, is out of 05h and would be tuning only if measured on these fixtures alone. Nothing in (a) or (d) touches `src/sim`.

| option | rank | now | later | reason |
|---|---|---|---|---|
| (a) read (ii) as rooms/presets; list both as known, correct U cases | prefer | 0 | 1 | the flag is the stated edge working; later: an outdoor preset meets the same cause and must be read the same way |
| (d) (a) + outdoor-preset rule + CI cause line | prefer | 0 | 1 | the cause line (cap / both-near / VOV; movable or not) is the badge my §2 asks for; (d)(i) is a display rule, Seats 1/6 |
| (b) change the fixtures | can live with for edge_values only | 2 | 2 | edge_values is the contract-limits fixture; softening it weakens validation; open_field is AX37 (5.4)'s and no placement silences it |
| (c) reopen U | cannot live with | 3 | 3 | the only outcome that "resolves" (b) through (c) is a predicate silent at SE 3.98 dB: false precision, the never-traded criterion |

**Conditions.** (b) → 1 only if edge_values keeps its materials and the moved placement is additional, not a replacement. (c) → 1 if the reopening is confined to the display tier (Seat 6 (i)), which is (d)(i).

**Commitments.** (a)/(d): a CI list and an AX44 reading; Phase 12 inherits the same reading for outdoor presets. Undoing: a plan-text change.

**Evidence.** [Observed] file 18 K-b3; file 9; fixtures (from the code); AX41, AX44, AX37 (5.4). [Derived] the cost law. [Hyp] "formulation-level pruning would help".

**Hand-offs.** Seat 1/6: showing U where the tail is inaudible. Seat 9: an open field has no diffuse tail. Seat 3: the rendered tail when the pilot ships (SE 3.98 dB at a −60 dB emitter).

**Premortem.** (c) wins: U goes quiet at both-near + cap, a producer's booth corner reads 6 dB low with no note; Seat 9's Phase 08 corner listening notices.

## D-H3 (c) — the denormal premise of the FTZ test

**Reading.** Where on the IR path a denormal can arise and why none reaches the IR. Cue: §4-6 (a claim with no instance behind it).

**From the code, the hybrid path is double end to end and flushes at the only float boundary.** `planEmitter` / `renderImageSources` (double), the estimator (double; weights are products of (1−α) over the hits a window allows: ≤ ~100 hits at reflect 0.001 in the thinnest AX6 room → ≥ 1e-300, still normal; α = 1 gives exactly 0), the Eyring referral `exp(−rate·(end − t))` (bounded by the window: ≥ 1e-120), the unit-decay synthesis in double (NoiseTail.cpp L139–151), the IR sum in double (Engine.cpp L368–371), then `toFloatNoDenormal` (L49–55, L373), which zeroes |v| < FLT_MIN explicitly. So a float denormal cannot exist in a hybrid IR, guard or no guard. My file 3 L74 hand-off ("compute in double, or flush") was implemented as both; that, not luck, is why the probe is negative. The guard's real work is in the convolver (its own guards, PartitionedConvolver L227, CrossfadingConvolver L359): Seat 5's.

**Where a double denormal does arise, invisibly.** NoiseTail.cpp L145: `exp(−rate·j)` with rate = 6.91/(T60_b·fs), over a tail of min(12 s, 1.5·max T60) (kTailDecayRangeDb 90, kMaxIrLengthS 12). When one band's T60 exceeds another's by > ~100× and the cap does not bind, the short band's envelope crosses [exp(−708), exp(−745)] (≈ 5.4 T60 ≈ 2 600 samples at 48 kHz in a booth) and `out[j]` is a double denormal with FTZ off and 0 with FTZ on. The IR is unchanged because the long band's normal value absorbs it in the double sum (below the ulp). **Named scene:** `dead_booth` with every surface at α {0.01, 0.999 × 7} (Eyring, Decay.cpp L49–51, clamp 0.999): T60 ≈ 7 s at 63 Hz vs ≈ 0.01 s above, ratio ≈ 700, tail ≈ 10 s. The probed "100 m cube 0.01/0.999" misses it because the 12 s cap holds the ratio to ≈ 27 T60s there. Prediction: a status-flag detector (MXCSR DE / FPSR IDC) reads positive on this scene, the bit-identity still holds; a positive control for the detector, which "negative on all" cannot provide.

| option | rank | now | later | reason |
|---|---|---|---|---|
| (d) + my positive-control scene | prefer | 0 | 1 | the clause becomes true in both halves: "denormals arise in the synthesis at scene X; the IR is bit-identical"; re-run when the path changes |
| (a) read as satisfied by the negative probe | can live with | 1 | 1 | true as far as the bit criterion sees; records nothing about the mechanism |
| (b) bounded search | can live with | 1 | 1 | one run, three OSes; it will find my scene; then (d) anyway |
| (c) synthetic injection | cannot live with | 2 | 2 | asserts nothing about the engine; passes forever |

**Also note:** `buildOmni` (OmniEarly, validation only) casts without the flush (L441); harmless for the product, worth one line for Seat 5.

**Evidence.** From the code throughout; [Observed] file 11 addendum; [Derived] the T60-ratio arithmetic; [Hyp] libm returns gradual-underflow results (glibc/MSVC do, by my register).

**Premortem.** (a) alone: a later float-path optimisation in the synthesis introduces real float denormals; the test still passes (the flush at L373 hides them) while the builder thread slows 10–100× on the host; Seat 5's profiler notices first.

## D-H3 (d) — W1 both_corner's cap flag

**Reading.** Is "the pilot missed the heavy tail" the rule behaving or a weakness. Cue: S7's anomaly ("metallic or over-diffuse after a cut → N = 0") generalised: a flag that depends on a draw.

**Engine reading.** N_need = n\*·(SE_pilot/0.083)²; cap hit := N_need > N_cap. At W1 both_corner N_cap = 1 088 ≈ n\*, so the cap fires iff the pilot's SE exceeds 0.0856 dB. The achieved SE is 1.12 dB at VOV_union 0.57: the pilot's variance estimate was ≈ 170× too small, which is what VOV 0.5–0.6 means (the variance estimator's own variance is of the estimate's order; F14: CLT rules fail). So the flag at this placement is a coin toss fixed by the key (AX40): expected behaviour of any pilot-sized rule at a heavy-tailed score, and the design already says so: AX41's CI escalation "VOV ≥ 0.1 where the pilot SE > target/3" (0.086 > 0.028, VOV 0.57: it fires) and AX44's VOV leg of U. The honest assertion at W1 both_corner is U plus the VOV escalation, not the cap. Weakness to record, not a defect: N_need from a pilot at VOV > 0.1 carries no information, and Seat 1's "flagged, not bounded" debt (§5 B15) is the repayment path. **Q-3** (N_cap 1 088 vs 2 624): from N_cap = (W_scene − W_pilot)·n\*/W_pilot, the C++ pilot spends 0.485 W_scene for 1 024 histories against the prototype's 0.281: 1.7× evaluations per history, a counting-definition difference (the C++ counts every attempted image evaluation, from the code L140) to record once; W_max is re-derived in C++ units (scope 6), so it is not a defect, but every prototype-derived figure in AX41's rationale (0 cap hits at defaults, 15.3 % overrun) must be re-measured, as the reported set now does.

| option | rank | now | later | reason |
|---|---|---|---|---|
| (d) cap benchmark at layout4_s1/both_corner; W1 both_corner asserts U, flags pinned in D5 | prefer | 0 | 1 | there N_cap 128 and SE 1.28 dB: the cap fires for any pilot SE > 0.059 dB, i.e. unless the pilot reads 20× low; a property of the rule |
| (a) read as "U is raised" | can live with | 1 | 1 | true; loses the deterministic cap exercise Seat 5 wanted |
| (c) "cap or floor or U" | can live with | 1 | 1 | (a) in weaker words |
| (b) keep, red | cannot live with | 2 | 2 | red on a draw; the club / living_room rows never run |

**Commitments.** (d): one row flag in the records test and D5 pins; undoing is the same edit. All: the Q-3 finding recorded once.

**Evidence.** [Observed] files 13, 18; AX40, AX41, AX44; from the code L362–405, L465–467. [Derived] the SE thresholds.

**Premortem.** (b): the records test stays red, the both-near replicate p95 that the AX44 note text needs is never produced, Phase 11 ships the qualitative text everywhere; Seat 6 notices.

## D-H3 (e) — `reset()` on the audio thread; the quiesce wait

**Reading.** Where the build observes the cancel flag, so the worst `quiesce()` wait is bounded. Cue: §4-7 and P5 ("precompute what does not move").

**From the code: the cancel flag is checked only inside the diffuse solve.** `options.cancel` is consumed at Engine.cpp L324 (`run.stop`) and tested between 64-history blocks (DiffuseEstimator.cpp L497, L518, L552). Not checked: `planEmitter` / `renderImageSources` (before the solve), `BandNoiseGenerator`'s constructor and `make` (after the solve; the four band-pair IFFTs and the sample loops, NoiseTail.cpp L120–153), the IR assembly loop (Engine.cpp L360–374), and the pipeline's `makeIrSet` after `buildRoomIR` (`quiesce()` waits on `busy_`, which spans the whole `decide`). Build order: ISM → solve → synthesis → assembly. So a cancel during the solve is seen within one block (ms; the solve is 58–162 ms at 100 m / 96 kHz); a cancel during the synthesis is seen only when the build returns: the worst wait is the whole non-diffuse build, 2.0–2.6 s at 100 m / 96 kHz (file 7 via file 8: ≈ 95 % of it in the synthesis), in seconds, not ms. Two engine facts the decider's framing misses: (i) phase-07c moves the solve, which is < 10 % of that time; after 07c, `reset()` on the audio thread still waits up to ≈ 2.5 s for an in-flight synthesis, so "the remedy is 07c's `reset()` half" is only true if 07c also stops building/waiting in `reset()`; (ii) `resetSequence` discards an in-flight build after waiting for it and then rebuilds the same scene synchronously (L247, L261): the stale case costs the wait plus a build. Mitigation already in the code: position-only builds reuse cached unit decays (L355–358), so a stale set after a position change rebuilds in far less than 2 s; the 2–2.6 s case needs a room or material edit in flight.

**(e-c) as written is therefore no improvement on (e-a) in the worst case.** It becomes one only with cancel points in the synthesis. **My option (e-e):** (e-a) or (e-b) plus cancel checks in `buildHybridOmni` (before the solve, between emitters, between the four band-pair IFFTs in `make`, every 2¹⁶ samples in the sample and assembly loops), throwing `BuildCancelled`, output untouched (a cancel only aborts; bit-identity unaffected, no golden); the K-e6 record then has a granularity of about one 2.3 M-point IFFT, of order 50–150 ms at 100 m / 96 kHz [Hyp; measure], and it becomes a gate (worst quiesce ≤ a measured bound). About twenty lines in `src/sim`, generic (NFR-8). It also shortens every quiesce: restore, prepare, release, destructor.

| option | rank | now | later | reason |
|---|---|---|---|---|
| (e-e) cancel points + (e-a)/(e-b) | prefer | 1 | 1 | the only option that bounds the wait in ms; cheap; no output change; whether 05h carries it is Seats 5/7's |
| (e-b) cancel, never wait or build | prefer | 1 | 1 | engine-side correct; the in-flight build finishes on the builder and is discarded at submit (L203); X11 kept by the offline rule; the silent stale case is Seats 1/3/6's |
| (e-d) (e-a) + measured bound + assert | can live with | 1 | 2 | the measurement will read seconds and name the synthesis; the record is honest but the exposure stays |
| (e-a) keep as built, correct the premise | can live with | 1 | 2 | later 2: the named remedy (07c) removes < 10 % of the wait; the gap outlives 07c unless reset stops waiting/building |
| (e-c) never build, still wait | can live with | 1 | 2 | as built the wait is the 2–2.6 s synthesis; with (e-e) it drops to ms and I rate it 1/1 |

**Conditions (every 2 → 1).** Add the (e-e) cancel points, or write into AX38 (i) / 07c that `reset()`'s remedy covers the non-diffuse build too.

**A hand-off with arithmetic (Seat 5, D-H1).** `restore()` quiesces first (L344). If a builder is mid-synthesis at 100 m / 96 kHz when a restore arrives, the restore pays up to 2.6 s of wait before its own ≈ 2.14 s build; 14 × 4.7 s = 66 s against the 30 s watchdog, if pluginval's state tests can arrive while the builder is in flight [Hyp on pluginval's sequence]. AX38 4c measured restore "contended by a second pipeline", not by the same pipeline's in-flight builder. (e-e) removes this; otherwise it belongs in D-H1's margin.

**Commitments.** (e-e): none beyond the ms bound as a record/gate; undoing is deleting the checks. (e-a)/(e-d): the gap into the compatibility notes and 07c's scope text.

**Evidence.** From the code (Engine.cpp L255–374, NoiseTail.cpp L110–155, DiffuseEstimator.cpp, ScenePipeline.cpp L102–133, L245–327, IrBuilderThread.cpp L44–50); [Observed] file 12 F1, F2, F6, C1–C3; file 7 via file 8 K2/K18; phase-07 L111–141; phase-07c §5. [Hyp] IFFT time per band pair; pluginval's sequence.

**Hand-offs.** Seat 5: thread-id assert, measurement design, scope pull. Seat 3: keeping a stale IrSet across a realtime reset. Seats 6/8: "settling" vs a stall.

**Premortem.** (e-a) ships and a VST3 host calls `setProcessing(false)` on its processing thread at transport stop during a 100 m material edit: the whole graph stalls ≈ 2.5 s then rebuilds 2 s more; a producer reports "the DAW freezes when I press stop in the big room"; Seat 7 reads the support ticket first.


---

## Round 2: (g) cell

**SEAT 2, round 2 (D-H3 (c), P05H-56).** Only what changed: the (g) cell, rated from my own criteria, not inferred.

**(g) = (f) + every pool share under `ScopedFlushDenormals`: 0 now / 1 later, prefer over (f) (0 / 1) by a hair.** Reason now (0): the line (`ThreadPool.cpp` L36–39, in the tree) is generic, scene-free, allocation-free, one MXCSR/FPCR write per share; it is not tuning, so my earlier "nothing touches `src/sim`" (a virtue I named for items (b)/(d), where the interrogator must rule out scene-specific logic, NFR-8) is not violated by it. Reason later (1), the same as (f)'s: the standing probe re-run on each path change, plus one new convention to write into `ThreadPool.h`: everything that ever runs on the process pool runs flushed, which a later phase reusing the pool for float DSP must know (a benefit there, but a rule to remember).

**Why I prefer (g) and why its reversal clause will not fire (from the code, my analysis, not only the probe).** The estimator's path is double, and no quantity in it approaches the double subnormal range in any AX6 room: the per-reflection weights are products of (1−α) over the hits a window admits (dead_booth, the worst case: ≈ 4–5 hits at reflect 0.001 in a 23 ms window → ≈ 1e-14); the decay factor exp(−13.8·(b−t)/T60) is bounded by window/T60 (≈ 37 in dead_booth → 1e-16; in a 100 m room the shortest T60 is ≈ 0.4 s, so smaller still); air and geometry factors are ≥ 1e-10. Without subnormals, FTZ on a worker is output-neutral, the D5 hashes are integer face sequences plus the RNG and cannot move, and E_target is unchanged to the bit. So the same-run re-check is the right trigger, and I expect it green; the guard's value is NFR-6 insurance against a worker inheriting a different FP mode from the thread that first touched the static pool [Hyp on which mode a new `std::thread` inherits per OS; irrelevant while no subnormal arises]. Choose (g).

**Commitment and undo.** Commits later phases to the pool-wide-FTZ convention and the standing probe; undoing is deleting one line and re-running the probe (minutes). No golden, no scene logic, no audio-thread exposure (the pool never runs on the audio thread, AX38 (i)).

**Condition.** None needed at 0 / 1. If the same-run re-check does move a hash or E_target on any OS, that is a finding about a subnormal I have ruled out above, and I would want its scene named before (f) is taken as the fallback.


---

## Round 3: (f9) cell

**SEAT 2, round 3 (D-H3 (a), P05H-77).** Only the (f9)-as-CHECK cell.

**(f9) as the CHECK (|mean (C++ − ref)| dB per band ≤ 3·SE_pool + mean ℓ_ref; the as-written and per-room statistics printed as records): 0 now / 1 later; prefer over (e′) (my 1 / 1).**

*Now 0, reason:* it is the per-case test's own reading of ℓ_ref (τ − ℓ_ref: a bounded, signed, systematic residual added, never a 1-σ term in quadrature) carried into the pooled test, so one reading throughout; it passes on the data (1 kHz: 0.0008 dB against 0.0040 + 0.0051 dB), needs no cluster key in the golden, and is what the tree already prints (L312–319). Power against a shared estimator bias is kept: the catch threshold is 0.009 dB (≈ 0.2 %) at 500 Hz–2 kHz, 2× inside Seat 1's 0.02 dB and 5× inside AX46's 1 %; (e′)'s is ≈ 0.005 dB [derived: 0.64 × a typical √(SE² + ℓ²) of 0.008 dB], a sharpness nobody's criterion asks for, bought with a second reading of ℓ_ref.

*Later 1, reason (two debts to write into the test comment and the register, no new constant):* (i) the allowance is a mean of magnitudes, so adding ℓ-sensitive cases (the s = 1 layouts at 0.19–0.33 %) loosens the bound for the whole band by their share; the catch threshold in dB must be restated at each golden round. (ii) An unweighted mean in dB loses the cluster structure: a one-room estimator defect (dead_booth at +0.017 dB, z 8, 2.3 ℓ_ref) is invisible to this CHECK, so the per-room table stays a printed record and my round-1 condition stands (the dead_booth / AX36 finding in the register; the cheap 0.625 m rung for the small rooms; the ladder-direction sign check). Undo: the same test edit as (e′), smaller.
