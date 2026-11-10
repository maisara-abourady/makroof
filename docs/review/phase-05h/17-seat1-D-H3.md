# Seat 1 — D-H3 (a), (b), (d)

SEAT 1 POSITION

Corpus present (c1b171f). Yardstick as in my earlier rounds: the G jnd is 1 dB [corpus: Vorländer Table 6.1, L2060, 500–1000 Hz; other bands by extension]; a tail-only error ΔL moves G by less than ΔL. No new persona assumption falls (motion thresholds already set aside: no head tracking in v1). Files read: `16-decider-convene-D-H3.md` (items (a)–(d) and the (e) addendum); `11-`, `9-`, `12-`, `13-`, `14-`, `18-orchestrator/researcher-*.md`; BUILD_PLAN AX37, AX38 (i), AX41–AX46 and §5 B15; phase-05h §4 item 4, §5, §8, §9; phase-07 L111–160; phase-07c §5 conditions 2, 4–7 and §6; my phase-05b2 files 18 and 23; decider file 25 L180–194; from the code: `test_diffuse_agreement.cpp` L196–284, `test_diffuse_records.cpp` L303–375, `ScenePipeline.cpp` L245–327, `edge_values.json`, `open_field.json`. This delivery supersedes my first one: item (a)'s arithmetic is revised on file 18's table (K-a3), item (b) notes K-b3; items (d) and the rest are unchanged; item (e) is appended.

---

## (a) AX43's pooled bias check

**1. Reading.** Whether my pooled check |mean z| ≤ 3/√M, z = (C++ − ref)/SE_C++, should carry the reference's certified error ℓ_ref and/or pool by shared reference. Cues: a threshold that must carry its method (§4); a test that measures the system's own floor instead of the thing under test (Strategy B step 1); a check that is red by design is not evidence (criterion 3).

**What my rule was meant to catch.** An estimator bias shared across cases, relative to the true value: a wrong factor or split that would move every user's tail the same way and might be larger in untested rooms. The 0.02 dB figure was the catch size the pooled SE allowed, not a perceptual threshold: 0.02 dB is 0.02 jnd of G, which no listener on any chain with any signal detects. The pooled check's value is diagnostic, not perceptual. My per-case rule already carries ℓ_ref (z_FW·SE ≤ τ − ℓ_ref, file 18 item 2); the pooled formula omitted it. That was an oversight in my own rule, not a design: a pooled statistic whose SE is below the reference's own residual measures the reference's floor, not the estimator (K-a6). **A shared deviation the reference cannot resolve is not the bias I meant.**

**What file 18 shows (from the code, K-a3/K-a4).** The mean signed deviation at 500 Hz–2 kHz is **+0.0009 dB (+0.02 %)**: there is no shared bias to catch. The mean z of +0.44 is carried by three contributors whose SE (0.002–0.009 dB) is far below their reference's ℓ_ref: `dead_booth` (two emitters, +0.017 dB at SE 0.0021 dB, z +8.1, ℓ_ref 0.17 %), `cr4` (ten pairs, +0.010 dB, z +1.3) and `cr3` (+0.005 dB, z +0.5), with the absorbing-face layouts pulling the other way. The per-case SE is 0.0021–0.034 dB, mean 0.0077 dB, not the 0.035 dB the packet assumed; my first delivery's second reading (per-case SE ≈ 0.007 dB from AX46's SE_class) is the one borne out. Under the table: as written fails bands 3–5; (a) passes every band (0.31 vs 0.412); (b) fails the BRAS class (0.56–0.58 vs 0.548) and the reference-position class (1.0–1.2 vs 0.905, M 11, dominated by dead_booth's two z ≈ 8 case-bands); (d) fails the BRAS class; (e) passes every band with margin (|mean| ≤ 0.19 vs 0.64–0.69).

**One finding for Seat 2, not a gate matter.** `dead_booth` reads +0.017 dB (+0.4 %) above `ref_hybrid` at 2.3 ℓ_ref, and the independent tracer (file 14) also puts C++ above it, +0.02 dB on both emitters at tracer SE 0.006 dB. Two references agreeing in sign is weak evidence of a small estimator excess in the most absorbent room rather than a reference residual [Inferred]. Perceptually nothing (0.02 jnd; 12× inside τ per case); as a diagnostic it deserves one line in the record. The tracer comparison includes the specular share, so the diffuse-only figure may be larger: Seat 2's.

**Is (a) principled or a loosening?** Principled as far as it goes: it enters the same ℓ_ref the per-case gate subtracts, and the catch size for a true shared estimator bias stays ≈ 0.01–0.02 dB (3/√53 × √(SE² + ℓ_ref²) at the mean values). Nothing my rule 4 forbids changes: no reseed, no added N, no wider τ, no dropped case, the constant 3 untouched. Incomplete, because ℓ_ref is a signed residual shared by one room's pairs (Seat 2 to confirm); adding it per case-band in quadrature still lets the shared part accumulate with M. The principled form for a shared reference error is clustering by the reference that shares it: (e). The metrology form (E_n) I cannot source: [Hyp], researcher RQ-H3-1.

**2–4. Ranking and tension (now / later).**

| option | label | now | later | reason |
|---|---|---|---|---|
| (e) per reference room, z with ℓ_ref | prefer | 1 | 1 | Matches the error's structure and passes on the data with margin. Now: a clustering rule and a cluster id in the golden that nobody has written (update_goldens with reason). Later: small M_cluster loosens the limit, but the cluster means' SE is small, so the catch stays ≈ 0.01–0.03 dB (≤ 0.03 jnd). |
| (a) | can live with | 1 | 1 | Consistent with my per-case rule; passes at 0.31 vs 0.412, a 25 % margin carried by the same three contributors. Gets stricter by itself as rungs certify (ℓ_ref shrinks); the shared-room part still accumulates when the small-room and 100 m classes are gated. |
| (d) (a)+(b) | cannot live with as a CHECK | 2 | 3 | Fails the BRAS class on the data (0.59–0.60 vs 0.548): adopted, it is (c) in different words. |
| (b) | cannot live with as a CHECK | 2 | 3 | Fails two classes on the data; no ℓ_ref, so the BRAS class fails on its own rung error. |
| (c) red by design | cannot live with | 2 | 3 | Now: a CHECK that cannot pass whatever the estimator does is a measurement of ℓ_ref, not a test. Later: a real shared bias (say +0.1 dB at 2 kHz after a refactor) hides behind the known red; the check I asked for stops existing while appearing to exist (criterion 3; "a flag that always fires trains people to ignore flags", file 23). |

**Debt.** (a): a formula change in one test, ℓ_ref already in the golden (from the code: `k.lRef`); undo = one edit, no golden regeneration. (e): a cluster field in the golden; undo = a golden round. (b)/(c)/(d): every later CI run and Phase 13's accuracy wording carry an explained red. Evidence arrives: the next certified rung (ℓ_ref shrinks); the small-room and 100 m classes when gated; Seat 2's reading of dead_booth.

**5. Evidence.** [corpus] Vorländer Table 6.1 L2060. [Observed] files 9, 14, 18 (from the code). From the code: `test_diffuse_agreement.cpp` L198–203, L229, L276–283. [Inferred] the dead_booth reading and the catch sizes. [Hyp] E_n form → RQ-H3-1. Researcher: whether a shared signed reference error is clustered or added in quadrature in a pooled consistency test.

**6. Conditions.** (b), (c), (d) 3 → 1: the statistic is printed per band, per class and per reference room (not CHECKed) with a dated note that the as-written form cannot pass below ℓ_ref; that is (e) as a report, a stopgap of one golden round at most.

**7. Hand-offs.** Whether ℓ_ref is signed per room, and the dead_booth sign: Seat 2. How a round-robin pools over shared references: Seat 9. Implementability and CI gate: Seat 5. Public wording: Seat 7.

**8. Premortem.** Under (c), a refactor of the random stream adds +0.1 dB at 2 kHz, the pooled check was already red, nobody looks, and the contracted engineer finds it months later reading the CI log.

---

## (b) U raised at the default placement of two fixtures

**1. Reading.** Whether U at `edge_values` (pilot ships, SE 0.76 / 3.98 dB, the 3.98 on the +12 dB emitter) and `open_field` (cap, SE 2.4 / 2.1 dB on a tail below −60 dB after t_dir + 50 ms) triggers AX44's reversal or is read as outside Seat 6 (ii)'s scope. K-b3 (file 18, from the code) now shows U raised through the cap at every moved placement of both fixtures (edge_values 0.93–3.29 dB; open_field 1.6–4.1 dB), so "cannot be moved" is shown. Cues: the hardest signal stays fixed between versions (B2; failure library "letting the test signal drift"); a note nobody can act on is noise (criterion 2); my later-2 debt "flagged, not bounded" (B15).

**What U means at each.** At `open_field`, U is true as statistics and empty as perception: ±2.4 dB on a component ≥ 60 dB below the direct sound changes the total by ≈ 3 × 10⁻⁶ dB [Inferred], and the component sits at the decay convention's end-point (the −60 dB line, the T60 convention). No test is needed (S2 anomaly: many times a JND). A "level unreliable" note there is **truthful but noise**: nothing the user could do changes anything audible, and a note that fires on every field trains the user to ignore the one in a hall where it matters. At `edge_values`, U is true and salient: a near-rigid 100 m slot with a +12 dB emitter has an audible tail, and SE 3.98 dB at 1 SE is ≈ 4 jnd of G before the tail-share reduction. This is the current worst instance of my B15 debt and should enter that register as its evidence row.

**(d)(i), the display rule.** It costs my later-2 debt nothing, on two terms: it keys on the measured energy ratio (AX37 (5.4)'s existing −60 dB check), never on a preset category or a fixture name; and U itself stays raised in the diagnostics and the Seat 6 (iii) tier, so the record exists. On those terms I rate (d)(i) **1**, not ≥ 2; it may stand. Without the first term it is 3 (a festival preset with a stage wall behind it and an audible tail would lose its note).

**2–4. Ranking and tension.**

| option | label | now | later | reason |
|---|---|---|---|---|
| (d) (a) + the two rules | prefer | 0 | 1 | The hardest case stays in CI with its cause printed; (ii) is my K-b3 demand made standing. Later 1: Phase 12 outdoor presets meet the same cause; the display rule must be keyed as above. |
| (a) reading | can live with | 1 | 1 | Honest if both cases are listed and the pilot-ships path stays exercised. Now 1: a requirement narrowed after the result it failed (K-b3 removes the "asserted, not shown" half of my objection). |
| (b) change the fixtures | can live with | 2 | 2 | Tuning the acceptance signal to pass the test: the only fixture where the pilot ships leaves CI, and the extreme-window path becomes untested. Neither fixture can be silenced by placement (K-b3). |
| (c) reopen U to silence it here | cannot live with | 3 | 3 | A predicate that is silent at SE 3.98 dB says "level reliable" where it is not. Acceptable only as a reopening that raises U on at least the same set; then it is cost (Seat 7's), 1/1. |

**Debt.** (a)/(d) commit Phase 11 to the display rule and Phase 12 to the same reading for outdoor presets (AX41's J1 trigger stays for capped presets with U raised at every reasonable placement); undo = a display rule and a report line. (b) commits the extreme-window behaviour to being unexercised until a user finds it; undo = re-adding the fixture. Evidence arrives: Phase 12 preset checks; the B15 fallback's p95.

**5. Evidence.** From the code: both fixtures; file 9 §"AX44 Seat 6 (ii)"; file 18 K-b3. [Inferred] the 3 × 10⁻⁶ dB and the 4 jnd. [corpus] Table 6.1 for the jnd.

**6. Conditions.** (b) 2 → 1: the present `edge_values` scene stays in the reported set under another name with U expected, so the pilot-ships path is still exercised. (c) 3 → 1: as stated in the table.

**7. Hand-offs.** Scope of "valid fixture": Seat 6. Whether a producer builds either scene, and what a field note does to the story: Seat 8. Whether the pilot stopping at the first block is the rule as designed: Seat 2. The B15 register row: plan-editor via the decider.

**8. Premortem.** Under (b), the pilot-ships path leaves CI; a producer builds a long rigid corridor, the tail ships 4 dB off with a note he learned to ignore on field presets; a beta user with a corridor scene notices first.

---

## (d) "W1 both_corner asserts the cap flag"

**1. Reading.** The cap flag is 0 at W1 both_corner (pilot SE ≤ 0.086 dB, achieved 1.122 dB, VOV_union 0.567, U raised through the VOV leg) and the REQUIRE stops the club / living_room both-near rows. Cues: a systematic weakness observed, not hypothesised; the rows I need for B15 do not run.

**What the assertion protects for me.** Nothing directly: the cap path is Seat 5's benchmark. What I need is that U is raised where SE is 1.12 dB (it is), and that the under-read is recorded. **The pilot missing a heavy tail at VOV 0.6 is an audibility matter and sharpens my debt without changing its rating.** In round 2 I wrote that a small pilot under-reads the SE of a heavy-tailed variable and sets N too low [Hyp then]; file 13 makes it [Observed]: a 13× under-read. At this placement, with tail share f = 0.5 [Hyp], 1 SE gives ΔG ≈ 0.6 dB and 2 SE ≈ 1.3 dB, over the G jnd [Inferred]. B15 stays later 2 because U fires there and the debt is registered. What would raise it to 3: a case with achieved SE > 0.33 dB and U silent. The mechanism exists: at a one-end placement, a pilot under-read with cap hit 0 leaves U's second leg (cap ∧ SE > 0.33) silent whatever the SE. No instance in file 13 (every one-end row with SE > 0.33 dB has cap hit 1), but the club / living_room rows must run to show it. The predicate is out at bounds; I record this as B15 evidence, not a reopening.

**2–4. Ranking and tension.**

| option | label | now | later | reason |
|---|---|---|---|---|
| (d) cap benchmark at layout4_s1/both_corner; W1 both_corner asserts U with its flags pinned in the D5 golden; Q-3 finding recorded once | prefer | 0 | 1 | The cap is asserted where it is a property of the rule (N_need ≫ N_cap); pinning the flags makes the draw-dependence visible, which is the honest form. Later 1: a stream refactor flips the pinned flags, costing one golden round, by the rule. |
| (a) read as "U raised" | can live with | 1 | 1 | True and recorded; the deterministic cap exercise is lost unless another case carries it. |
| (c) "cap or floor-truncated or U" | can live with | 1 | 1 | (a) with a disjunction that hides which leg fired. |
| (b) keep red | can live with | 2 | 2 | Red by design, and a REQUIRE that stops my both-near rows: the per-class replicate p95 the AX44 note text needs is never sourced. |

**Debt.** (d): the golden gains W1 both_corner's exact flags (D7 already records n\*/N); undo = a golden row. (b): the Phase 11 note ships qualitative text everywhere for want of the p95. Evidence arrives: the club / living_room rows (this phase); the B15 fallback.

**5. Evidence.** [Observed] file 13; from the code: `test_diffuse_records.cpp` L342, L372–373. [Inferred] the ΔG figures. [Hyp] f = 0.5.

**6. Conditions.** (b) 2 → 1: the REQUIRE becomes a non-fatal CHECK so the remaining rows run; it stays red, so 1 only together with (d).

**7. Hand-offs.** Whether the under-read is the pilot rule as designed or a defect; Q-3: Seat 2. The benchmark's purpose: Seat 5.

**8. Premortem.** Under (b), the both-near rows never print, Phase 11 ships vague text, a producer with mic and source in a corner gets a 2 dB-weak tail and a note that names nothing; a beta user with a hall preset notices first.

---

## D-H3 (e)

Narrow: what the producer monitoring hears across a host reset under each option. Host shares, thread facts and the measurement design are Seat 5's; the time-variance rules Seat 3's; "settling" Seat 6's.

**1. Reading.** `reset()` may arrive on the VST3 processing thread (file 12 F1, F2, F6) and the project's path blocks in `quiesce()` and may build there (C1; from the code L245–265, L313–316). The question for me: which is the listener worse off with, a stall of the host's whole graph (0.18–0.80 s at 48 kHz defaults; ≈ 2.6 s at 100 m / 96 kHz) when the reset lands on the audio thread with a stale IR set, or the plugin's own output silent for the same build time until the builder delivers, then a 2P fade-in. Cues: transients and discontinuities are the most exposed artefact class (B4); a flag or state the user sees must be true (criterion 3).

**The comparison, from the code and phase-07 L128–141.** In the non-stale case (the built IrSet is scene-current) every option reuses it: nothing differs. In the stale case:
- (e-a)/(e-d) on a conforming host (reset on the UI thread, transport stopped): the build runs before processing resumes, the IR is installed at once, **no audio artefact**; the cost is a transport/UI stall of the build time.
- (e-a)/(e-d) on a host that delivers `setProcessing(false)` on the audio thread: the whole session's audio stops for the build time with buffer underruns at both ends, i.e. discontinuities on every track, plus whatever the host does on an overload. That is the worst artefact class I know of, detected by anyone at any length above a few ms; no threshold question arises.
- (e-b)/(e-c) on any host: no stall; the plugin's output (direct sound included, since the IR carries it) is silent until the builder delivers, then fades in over 2P (≈ 10.7 ms at P 256 / 48 kHz). If the user presses play after the build time has elapsed, nothing is heard; if within it (a parameter edit in flight at stop, then an immediate restart, or a reset mid-playback at a loop point or mute/unmute), one track enters late, click-free, with "settling" shown.

**Answers.** (i) The listener is worse off with the audio-thread stall: it reaches every track, it is a discontinuity rather than a fade, and it is not confined to the plugin. A late, click-free entry of one track is plainly audible (an onset delayed by 0.2–2.6 s is many times any threshold; no test needed) but confined and explained by the UI state. On a conforming host, though, (e-a) has no artefact and (e-b) has the late entry, so without K-e7 (which hosts deliver the reset on the audio thread) the net comparison is a host-share question, not a perceptual one: Seat 5 and RQ-H3-3. (ii) A 2P fade-in from silence after a transport discontinuity is not a separately detectable event: a 10 ms onset on a track that is starting anyway lies inside the discontinuity itself [Inferred; I have no incident on fade-in detection, and AQ4's 30 ms crossfade is the settled rule for mid-stream changes, Seat 3's]. What is detected is the silence before it, not the fade. (iii) (e-c)'s bounded wait helps me only if the bound is below one host block (≈ 1.3 ms at 64 samples / 48 kHz): any wait on the audio thread above that is a dropout, and a dropout is detected regardless of its length. K-e6 decides whether (e-c) is a real improvement over (e-a) in my terms; on the solve's 64-history granularity at 100 m I would not assume it [Hyp].

**2–4. Ranking and tension (now / later).**

| option | label | now | later | reason |
|---|---|---|---|---|
| (e-d) (e-a) + measured `quiesce()` bound + thread-id debug assert + per-host measurement as a 07c condition | prefer | 1 | 0 | Same exposure as (e-a) now, but the gross event becomes measurable and attributable before a user reports it; 07c removes the cause (its condition 4, no real-time waiting). |
| (e-b) `reset()` only cancels, never waits or builds | can live with | 1 | 1 | Removes the whole-session dropout on every host; adds a late entry of one track in the stale case on conforming hosts where today there is none. Later 1: 07c's interim-level rule ("never silence", condition 5) then replaces the silence; the silent window is a temporary step toward 07c, not its design. Scope pull is Seat 5's and Seat 7's. |
| (e-a) reading + recorded gap, 07c next | can live with | 1 | 1 | No artefact on conforming hosts; a whole-session dropout in the stale case on an unknown share of hosts, stated in the compatibility notes. Later 1 only if 07c lands before the first public release as D-H1 (v) has it; if it slips, later 2. |
| (e-c) never builds, cancels-and-waits | can live with | 1 | 1 | The late entry of (e-b) plus a wait on the calling thread; on the audio thread it is still a dropout unless K-e6 is sub-block, so perceptually it buys little over (e-b) and little over (e-a) unless the bound is in ms. |

**Debt.** (e-a)/(e-d): nothing audible is committed beyond the gap already named; undo = 07c. (e-b)/(e-c): commit 05h to the silent stale case until 07c's interim level; offline bit-identity must hold (X11; the offline branch rebuilds before the block, from the code L305–310). Evidence arrives: K-e6 (this phase, orchestrator); RQ-H3-3 and the per-host measurement (07c or Phase 13); 07c's interim-level test (layouts 4/5, the absorbing-floor cube).

**5. Evidence.** [Observed] file 12 F1, F2, F6, F9, C1–C3; §0 row 07 and file 16's durations (via the addendum). From the code: `ScenePipeline.cpp` L245–265, L305–327; phase-07 L128–141. [Inferred] the fade-in reading; [Hyp] the sub-block bound. The corpus has nothing on host threading (file 12 §6); no corpus claim is made here.

**6. Conditions.** None of my cells is ≥ 2. For the record: (e-a) later 1 → 2 if 07c slips past the first public release; (e-b) now 1 → 0 if the stale case keeps the last IrSet playing in realtime mode without breaking X11 (Seat 3's question in the brief; offline unaffected).

**7. Hand-offs.** Thread share per host and the measurement: Seat 5 (RQ-H3-3). The `quiesce()` bound and the cancel points: Seat 2 (K-e6). Keeping a stale IrSet across a realtime reset, and the crossfade rules: Seat 3. What "settling" says during a silent start: Seat 6. Compatibility-note wording: Seat 7.

**8. Premortem.** Under (e-a) without (e-d)'s assert and measurement, a common host delivers `setProcessing(false)` on the audio thread; a producer in a 100 m room stops the transport mid-edit and the whole session glitches for two seconds; the first report reads "the plugin freezes my DAW on stop", and nothing in CI says which path did it.
