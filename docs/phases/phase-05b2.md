# Phase 05b, session 2 — Tail-level matching from the propagated diffuse energy (the B11 switch)

Size: **L** (one session is the second and last of phase 05b; CLAUDE.md: a remainder that does not fit
goes into `phase-05h.md`, see "Split rule" below) · Depends on: 05b session 1 (this file's "Settled"
section; branch `claude/funny-clarke-d9mv2g`, report `docs/validation/report-phase05b.md`), 04, 05,
05e, 05f, 07 `done` · Read first, in this order: `CLAUDE.md`; this file in full; `docs/BUILD_PLAN.md` §2
**AX16, AX21, AX22, AX35, AQ10, AX4, AX5, AX11, AX18, AX20, AX28, AX6**, §5 **B11, B12**; `docs/phases/phase-05b.md`
(scope 0, 4 and the AX35 notes); `docs/validation/report-phase05b.md` (all of it, ten minutes);
`docs/validation/report-phase05.md` §6a; `docs/review/ledger.md` block "Phase 05b: patch size at a compute
limit"; PRD NFR-1, NFR-2, NFR-3, NFR-8, FR-SIM-2, FR-SIM-6, FR-3D-3, FR-3D-4.

Created on Maisara's decision of 2026-11-09 (answer to session 1's question 2, option (b): "keep 05b
open into session 2 to build the switch"; her words: "Answer to q2: b. Make the dedicated phase's prompt
extremely aware with the utmost level of detailed analysis of what and why.").

---

## 0. Why this session exists (read this before anything else)

### 0.1 What the product currently does wrong, and how much

The hybrid IR (Phase 04) has three parts: the image-source (ISM) early part, a statistical noise tail,
and a crossfade at the per-emitter mixing time t_mix,e. The tail's **level** is set by **energy
matching** (`src/sim/tail/NoiseTail.cpp`, `matchTail`): per emitter and octave band, the energy of all
image-source "entries" inside a Hann window [t_dir,e + 2.5 ms, t_mix,e], each referred to t_mix,e
with the Eyring decay rate, normalised to 10 ms, gives **E_target,b**; the tail noise is scaled so its
own energy per 10 ms at t_mix,e equals E_target,b (`bandsAmplitude` = √(E_target / ē_b)).

The entries are of two kinds (`tail::energyEntries`): the **specular** energy of each image
((1−α)(1−s) per hit, as rendered), and the **AX16 scattered** energy of each image:
E_noScatter · (1 − Π_s (1 − s_s)^hits_s) **at the specular path's own arrival time, attenuated by every
wall of the specular path**. AX16 is exact when absorption is uniform (Kuttruff §5.2: specular +
scattered = (1−α)ⁿ). It is wrong when absorption is concentrated: real scattered energy leaves the
specular path at the scattering hit and then meets the walls **it** travels to next (Kuttruff §4.5;
Gilbert, §4.6), not the walls of the specular path. With one strongly absorbing face, AX16 credits
scattered energy along paths that avoid that face (too much energy), or charges it for hits it would
not make (too little), depending on geometry.

**Measured in phase 05b session 1** against an independent seeded Kuttruff §9.8 ray tracer
(`tools/acoustics/tracer.py`; energy multiplication, r_d = 0.5 m, N ≥ 3·10⁶ particles, SE ≤ 0.078 dB
per window; `phase05b.json` "gate"; report §5), ΔL_b,tr = 10·log10(E_target(AX16) / E_target(tracer)),
1 kHz band (500 Hz and 2 kHz within 0.01 dB of it):

| case (AX28 positions, AX4 air) | t_mix,e (ms) | ΔL_b,tr (dB) | hybrid vs tracer (dB) |
|---|---|---|---|
| uniform α = 0.15, 20×30×10 m, s = 0.1 / 0.25 / 0.4 | 113.5 | +0.03 / +0.26 / +0.40 | −0.08 / −0.01 / −0.03 |
| Table 5.2 layout 4 (absorbing floor), s = 0.1 / 0.25 / 0.4 / 1 | 380.4 | +0.65 / **+1.51** / **+2.41** / **+3.87** | −0.03 / −0.08 / +0.07 / +0.04 |
| layout 5 (absorbing 10×30 m wall), s = 0.1 / 0.25 / 0.4 / 1 | 380.4 / 113.5 / 113.5 / 380.4 | −0.02 / +0.16 / +0.24 / **−1.17** | +0.05 / −0.05 / −0.08 / −0.04 |
| layout 6 (absorbing 10×20 m wall), s = 0.1 / 0.25 / 0.4 / 1 | 113.5 ×3 / 380.4 | +0.02 / +0.09 / +0.19 / **−1.16** | −0.03 / −0.03 / −0.02 / −0.01 |

So: **AX16 mis-sets the tail level by up to +3.9 dB** (tail too loud) in a room with one absorbing
surface, and by −1.2 dB (too quiet) in others, while the reference hybrid (`tools/acoustics/ref_hybrid.py`,
the "propagated diffuse energy", Kuttruff Eqs. 4.24, 4.29, 4.35) agrees with the tracer within
**0.08 dB everywhere**. In the measured BRAS rooms the model-vs-model bound ΔL_b (AX16 vs hybrid) reaches
−1.18 dB (CR3, 2 kHz; −1.47 dB with per-band s); the six Phase 04 test rooms and CR2 stay ≤ 0.3 dB
(report-phase05.md §6a). 1 dB is the level jnd (Vorländer Table 6.1, 500–1000 Hz). Concentrated
absorption is common in real venues (audience areas, carpeted floors, absorbing back walls: FR-3D-3's
venue presets), which is why NFR-1 makes this matter.

### 0.2 What the plan already decided (so this session does not decide it again)

- B11 (BUILD_PLAN §5) and phase-05b scope 4: if the hybrid's window level passes against the tracer
  (it does: branch **(i)**, SE ≤ 1/3 dB) and |ΔL_b,tr| > 1 dB anywhere (it is: 3.87 dB), **tail-level
  matching switches to the hybrid's propagated diffuse energy**, even though early rendering is not
  promoted. Phase 05's own X-b result (26 of 345 case-bands > 1 dB) independently requires the switch.
- AX35 (c) (2026-11-08, vetoable by Maisara): the switch is **not** implemented until **R1** (an ℓ
  certified for the tail path in every selected BRAS room) and **R2** (a formulation whose memory and
  rebuild cost are shown across the supported room range) are settled and Maisara decides. **This
  session is where R1, R2 and the implementation happen.** Maisara has decided that it happens (option (b)).
- What does **not** switch: the early part stays specular-only (AX21 stands; gate (B) failed:
  `report-phase05b.md` §6); the tail's decay rate stays Eyring (B12 recorded outcome); the mixing-time
  rule, AX22 and N_cap stay; the noise generator and the crossfade stay.

### 0.3 Why it is hard (the core engineering problem)

The reference hybrid computes the diffuse energy by time-dependent radiosity with specular transport
between patches (Joyce's reflection matrix, Kuttruff Eq. 4.35): the boundary is split into patches of
edge ℓ, and a **dense kernel** K[k, l, τ] (energy diffusely emitted by patch k that arrives on patch l
after τ time steps, directly or via any number of specular reflections, i.e. via every lattice image
of k) is built and applied generation by generation. Memory and time grow as N²·T (N patches ∝ S/ℓ²,
T time steps ∝ t_mix,e/Δt):

| room | ℓ = 2.5 m: patches, bins, dense kernel (8 bands, float32) | ℓ = 1.25 m |
|---|---|---|
| AQ10 room 20×30×10 m | 352, 118, ≈ 0.47 GB | 1 408, ≈ 7.5 GB |
| BRAS CR4 42×42×4.9 m | 714, 155 (to the latest t_mix,e of its 10 pairs), ≈ 2.5 GB | 2 856, ≈ 40 GB |
| contract maximum 100×100×100 m (AX6) | 9 600, ≈ 1 035, ≈ 3 TB | ≈ 49 TB |

A plugin instance today adds ≈ 123 MB of RSS at 96 kHz in the maximum room (Phase 07, Linux: +122.6 MB). The reference
implementation is therefore **not portable as it is**: it is a correct model with an unusable data
structure. The model is what has been validated; the data structure is free. That is the whole of
decision D-T1 below.

Also measured (session 1, `phase05b.json` "ell", "r1"): the hybrid's **E_target** converges fast in ℓ
(5→2.5 m ≤ 1.27 %, 2.5→1.25 m ≤ 0.324 % in the 15 (A) cases; CR2, CR3 2.5→1.25 ≤ 0.37 %; a* ≤ 0.42 %),
far faster than its per-bin envelope (5.36 %), because E_target is a window integral. **CR4's 1.25 m
rung was not computable (15.2 GB per band with the current solver): R1 is open for CR4.** The time
step Δt = 1 ms is not the limiting factor (halving it changes gated bins ≤ 0.126 %).

### 0.4 What success looks like for Maisara

Rooms with concentrated absorption get a tail whose level matches physics within the B11 window
tolerance; nothing audible changes in uniform rooms (in Phase 05 X-b the six Phase 04 rooms moved ≤ 0.3 dB); the plugin
still rebuilds and fits in memory for every scene the contract accepts, or, if that is impossible, the
limit is a product decision she made with the numbers in front of her, implemented generically (NFR-8)
and without level jumps under automation (FR-SIM-6).

---

## 1. Settled — do not reopen (cite, don't re-derive)

- Gate (B) fails (initial α, three BRAS rooms: EDT Δ̂ +0.816 jnd > δ = 0.25; CR4 +1.756 > 1 jnd) →
  early rendering **not promoted**; AX21 stands.
- Gate (A) per bin and the scope 5 bias trigger: "not evaluated (compute limit, AX35 (b))".
- Window check: branch (i); hybrid E_target within 0.08 dB of the tracer; numbers in §0.1.
- Tracer (`tools/acoustics/tracer.py`, seed 0x05B7) and its committed statistics; self-checks
  (s = 0 passes; s = 1 diagnosis vs Table 5.2 column, ledger DB-1 open).
- ℓ ladder and its certification rule per quantity (AX35); compiled kernel
  `tools/validation/hybrid_fast.py` (= `ref_hybrid` to 1e-7; numba offline).
- B12: Eyring stays. AX22/N_cap: unchanged. Mixing-time rule: unchanged.
- Maisara 2026-11-09: build the switch in this session (option (b)).

## 2. Raise with Maisara (first message and PR)

1. **AX35 accept or veto** (session 1, question 1, still unanswered). If vetoed, the window check that
   makes the switch due loses its certification basis, and this session stops (status `blocked`).
2. Any room-range decision D-T3 produces (only if D-T1 finds no formulation that covers the whole
   contract range): present the numbers (memory, W1/W2 per room size) and the audible stakes (§0.1).

## 3. Open decisions — settle each through the decision loop **before** writing `src/sim` code

Run researcher → decider → interrogator → advocate (CLAUDE.md, `/fix-plan`) for each. Record each as an
AX row through `/fix-plan`. None of them may be decided by the implementer alone, and none may be
decided after seeing a test it would make pass.

- **D-T1 — Formulation of the propagated diffuse energy in `src/sim`.** It must give **the same model**
  as `ref_hybrid` (injection s(1−α) at each specular hit into the Lambert patch hit, Kuttruff Eq. 4.24;
  mixed specular/diffuse propagation, Eq. 4.35 with the §5.2 split; gathering at the listener,
  Eq. 4.29; AX4 air) to a stated tolerance, but **only the window integral E_target per band** is
  needed, not the envelope. Candidate directions the researcher must assess (none is pre-approved):
  (a) the dense kernel with memory reductions (per-band, float32, the room kernel cached across
  position-only rebuilds as in the Phase 10 tail cache; injection and gathering per emitter);
  (b) matrix-free propagation (form factors and delays computed on the fly per generation; Kuttruff §4.5
  procedure step 3 stores only K_ik and a bounded history for pure Lambert radiosity — whether the
  mixed kernel admits the same is open, interrogator P05B-23/-35);
  (c) exploiting the shoebox's structure (regular patch grids on parallel faces; lattice images as
  translations; convolution/FFT over patch indices);
  (d) an **adjoint** (listener-side) formulation: E_target is a linear functional of the diffuse
  energy, so the window weights can be propagated backwards from the listener once per emitter pair,
  replacing a time-resolved forward solve;
  (e) a transform-domain evaluation (the Hann-weighted, exponentially referred window is a short sum of
  complex exponentials on [a, b]; whether the truncation to the window allows a few steady-state-like
  complex solves of size N instead of N²·T storage is to be checked, not assumed);
  (f) a seeded Monte-Carlo estimator of the same diffuse energy (determinism by AX5; its SE must meet
  AX11's threshold/3 for the window level; note it is a different estimator of the same model and must
  be validated as such).
  The decision states: the formulation, its agreement test against `ref_hybrid` (cases and tolerance;
  the tolerance is a numeric choice: decision loop), its memory and time complexity, and the measured
  W1/W2 and peak memory for the AQ10 room, CR4, and the largest contract room (AX6: 100 m per side).
  **A coarser ℓ is not a remedy** (phase-05b scope 0). The Table 15.1 option (scattering part updated
  every 3 s or 1 m) is a Phase 10 remedy only if W1 > 700 ms (phase-05b scope 0), not a D-T1 option.
- **D-T2 — ℓ for the tail path (R1).** AX35 (c) candidate: 2.5 m (certified in the 15 (A) cases, CR2,
  CR3). **CR4 is open**: compute its 2.5→1.25 m E_target change (500 Hz–2 kHz, all 10 pairs) with the
  D-T1 formulation if it is cheaper, or with `phase05b.py r1` on a machine with ≥ 16 GB free, or with a
  per-band, chunked transform. If any change is ≥ 1 %, the next rung is needed (and its cost enters D-T1).
  If D-T1 changes the discretisation (e.g. no patches), D-T2 is restated for that discretisation's own
  resolution parameter under the same per-quantity < 1 % rule.
- **D-T3 — Supported room range and behaviour at its edge (only if D-T1 cannot cover AX6's whole
  range within the budget D-T4).** Options must be generic (NFR-8: no preset- or scene-specific logic);
  a size threshold that switches formulation must not produce an audible level step when a user
  automates room size across it (FR-SIM-6; Phase 10's −1 dB mid-fade bound is the yardstick: a step of
  ΔL_b,tr at the threshold would violate it in concentrated-absorption rooms). Narrowing AX6 is a
  contract change (major bump, CLAUDE.md "contract boundary") and Maisara's call.
- **D-T4 — Cost budget.** AQ10: rebuild ≤ 50 ms is a **target, recorded, not a blocker**; NFR-2:
  heavy CPU is acceptable when it buys accuracy, but the plugin must stay usable in a DAW session. There
  is **no memory budget anywhere** in the plan: the decision loop proposes one (per instance, at the
  largest room), with the Phase 07 baseline (≈ 123 MB at 96 kHz, maximum room) as context. W1/W2 as
  defined in AQ10 (position-only rebuilds, 20×30×10 m, 2 emitters, 48 kHz, release, median of 10).
- **D-T5 — Interaction with the matching.** Decide, with evidence: (1) the hybrid's diffuse energy
  **replaces** AX16's scattered entries in E_target (the specular entries stay), exactly as
  `ref_hybrid.target_hybrid` does; (2) what the AX22 realised-k test (`needsIsmFallback`, k_real < 19 in
  500 Hz–2 kHz) counts once scattered entries are no longer discrete entries (today k_real counts the
  AX16 entries: replacing them by a smooth envelope changes k_real and therefore the fallback decision
  and t_mix,e; the Python `phase04_plan` computes k_real from AX16 entries and is what session 1
  compared against): keep k_real on the AX16 entries (fallback unchanged), or redefine it (an AX22
  change, out of scope unless the decision loop shows it is forced); (3) `bandsAxisShares` (used for
  directional output in Phase 08) — the AX16 entries carry arrival directions, the diffuse envelope
  does not; decide what Phase 08 receives.

## 4. Scope (after section 3 is settled and committed)

1. **R1 for CR4** (D-T2) and any further rung D-T2 requires; committed before code.
2. **`src/sim` implementation** of the D-T1 formulation, generic (NFR-8), in `src/sim/tail/` (or a new
   `src/sim/diffuse/` unit), no JUCE, no allocation on the audio thread (it runs on the builder thread
   only), deterministic (AX5: any randomness keyed by `tailSeed`), no NaN/Inf/denormals, contract
   unchanged (no new scene fields: s and α already exist; if D-T1 needs more, that is a contract change
   and Maisara's).
3. **Matching switch** per D-T5 in `planEmitter`/`matchTail`; diagnostics (`render_cli --diagnostics`)
   gain the diffuse E_target per band beside the AX16 one, so the switch is observable.
4. **Agreement tests** (Catch2): C++ E_target vs `ref_hybrid.target_hybrid` (exported reference values
   as a small golden, generated by a script with its reason in `tests/golden/CHANGELOG.md`) on the cases
   D-T1 states (candidates: the 15 (A) cases, the six Phase 04 rooms, the 30 BRAS pairs), to D-T1's
   tolerance; and C++ E_target vs the
   tracer's committed window energies (`phase05b.json` cases) within the B11 window tolerance (±1 dB),
   independently of the reference hybrid.
5. **Goldens and validation:** every golden whose tail level changes is updated through
   `tools/ci/update_goldens.py --reason "phase 05b session 2: tail level from the propagated diffuse
   energy (AX16 switch)"`; the BRAS validation (`tools/validation/run_validation.py`, nightly) is re-run
   and `report-phase05.md` regenerated; AQ9 results are reported before/after (no gate change: AQ9 is
   reported, B11 (B) is not re-run unless the decision loop says the switch affects it).
6. **Costs:** W1/W2 (AQ10), peak memory per instance at the AQ10 room, CR4 and the largest supported
   room, recorded in §0.
7. **Plan bookkeeping** through `/fix-plan`: AX16 (switched, with the measured ΔL_b,tr table), AX21
   (unchanged statement, cross-reference), AX35 (c) resolved, new AX rows D-T1…D-T5, §6 rows.
8. **Listening pack:** a `phase-05b2` entry: Phase 04 tail level vs switched tail level, loudness-matched
   **not** (the level difference is the point), through the six Phase 04 rooms and two synthetic
   concentrated-absorption rooms (Table 5.2 layout 4 at s = 0.4 and layout 5 at s = 1, as scenes), clicks
   and pink bursts.

## 5. Acceptance criteria — automated

- [ ] Section 3 decisions recorded as AX rows (ledger rows linked) **before** the first `src/sim` commit.
- [ ] R1: CR4 2.5→1.25 m E_target change computed (or the D-T2 restatement's equivalent), < 1 % or the
      next rung run.
- [ ] C++ E_target = `ref_hybrid` within D-T1's tolerance on all listed cases (CI, three OSes).
- [ ] C++ E_target vs tracer within ±1 dB on the 15 (A) cases (deterministic test on committed data).
- [ ] Uniform-α rooms unchanged: the room set and the regression bound are an open decision (decision
      loop; measured in Phase 05 X-b: six Phase 04 rooms ≤ 0.3 dB, `report-phase05.md` §6a), not tuned.
- [ ] Same scene + seed → bit-identical IR on the same platform; no NaN/Inf/denormals; allocation-free
      audio thread (existing tracker test) unchanged.
- [ ] W1/W2 and peak memory recorded (AQ10; not a blocker unless D-T4 makes memory one).
- [ ] Goldens updated only through `update_goldens.py` with the reason; nightly BRAS green; report
      regenerated.
- [ ] pluginval strictness 10 and auval still pass (rebuild cost changes the builder's timing).

## 6. Listening checklist (Maisara)

- [ ] In the concentrated-absorption scenes, the switched tail's level sounds natural against the early
      part (no "reverb pasted on top", no tail that is too weak); in the six Phase 04 rooms nothing
      audible changed.
- [ ] No new seam at the handover (the level change is at t_mix,e).
- [ ] Moving a source or resizing the room under automation: no level jumps (Phase 10 will gate this;
      listen now).

## 7. Contractor review focus

Equivalence of the `src/sim` formulation to the validated model (not just to its numbers on a few
cases); the independence of the tracer comparison; the AX22 interaction (D-T5 (2)); memory scaling and
the room-range edge (D-T3); determinism; no per-scene logic.

## 8. Risks and the split rule

- D-T1 finds no formulation within D-T4 for large rooms → D-T3 goes to Maisara with numbers; the session
  may still implement the switch for the supported range.
- CR4 R1 needs a finer rung that is not computable → the switch's ℓ is certified per AX35's rule only
  where computable; the gap is recorded and goes to Maisara.
- **Split rule (CLAUDE.md):** this is phase 05b's second session. Whatever does not fit goes into
  `docs/phases/phase-05h.md` (05c is reserved for Phase 05's zero-rooms branch), written in the same
  detail as this file, with the status row and a `blocked`/`in progress` note; the session stops there.

## 9. Out of scope

Early rendering of scattered energy (not promoted; re-run rule AX35 (e)); per-band scattering (B10);
the tail decay rate (B12); Phase 08 directions beyond D-T5 (3); Phase 10 caching beyond what D-T1 needs;
any per-scene tuning.

## 10. Definition of done

Section 5 all checked with CI evidence; §0 row 05b `done (not promoted; tail-level switch implemented)`
with the numbers; PR (the single phase-05b PR, covering both sessions) with the listening checklist,
the contractor focus, the AX/ledger links and the "Raise with Maisara" items.
