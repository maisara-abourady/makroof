# Phase-07 decisions D1–D4, D6–D9: decider report, round 1 (2026-11-08; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

Inputs: interrogator-option-check.md, research-dossier.md, ledger section "docs/phases/phase-07.md — interrogation
(2026-11-08)". D5 already verified (option A). Next free AX id: AX33.

## PRD digest
For producers/DJs who don't understand spatial audio. Outcome: place listener and sources in a designed space, automate
positions (FR-3D-5, FR-3D-8), scene follows every change (FR-3D-10), saved in the project (FR-LIC-1). Priority: NFR-1
accuracy, NFR-3/FR-SIM-6 artifact-free movement, NFR-6 exact restore, NFR-2 CPU/latency acceptable if reported, NFR-8
generic engine. Hard: AX2, AX5, AX6, AX9, AQ4, AX18, AX31, AQ10; host IDs/ranges frozen at release (F11).

## D1 (P07-5) push-away: **C, nearest valid point, fixed tie-break**
B rejected (CONDITIONS VIOLATED). A and C valid; C avoids A's side jumps (FR-SIM-6; Vorländer §15.1 fades vs abrupt
direction changes) and has an independent brute-force reference.
Scope-2 text: "Listener–emitter distances below 0.3 m: each emitter e is replaced by the point p of the margin box B
with |p − l| ≥ 0.3 m that is nearest to e; the listener never moves and the two emitters are treated independently.
If |e − l| ≥ 0.3 m, p = e. Otherwise p = l + 0.3·u, where u maximises u·d over unit vectors with l + 0.3·u ∈ B,
d = (e − l)/|e − l|, or d = +y (AQ1 forward) if e = l exactly; exact ties are broken by the largest u·ŷ, then u·x̂,
then u·ẑ. When l + 0.3·d lies in B this is the push along the listener→emitter direction. Tests: (a) 10⁵ seeded random
cases (1.5 m rooms, l in corners, e = l) all validate; (b) independent reference: bruteMin − 4 mm ≤ |p − e| ≤
bruteMin + 1e−9 m, bruteMin over a Fibonacci sampling of 10⁵ points of the 0.3 m sphere inside B (spacing ≈ 3.4 mm);
(c) the interrogator's case (1.5 m cube, l = (0.25, 0.75, 0.75), e = (0.1, 0.75, 0.75)) gives (0.1, 1.01, 0.75)."
Mirror in `docs/contract/README.md` as a 3D Module behaviour (phase session).
Load-bearing: L1 a valid p exists (box side ≥ 1.3 m); L2 nearest point on the sphere when e is inside the ball
(convexity of B); L3 A jumps sides; L4 direction jumps are what FR-SIM-6 prevents; L5 brute-force bound.
Objection: C still jumps on exact ties; any valid pure function jumps somewhere (P07-6 forbids hysteresis).
Reversal: audible jumps in Phase 08/10 → Phase 10 smoothing AX. Confidence medium.

## D2 (P07-7) resize: **A, keep relative positions**
Both valid (PRODUCT MATTER). Relative keeps all slider travel live; absolute leaves e.g. 3.8 % live height travel in
the default room (usable share (side − 0.2)/99.8) and can't be undone after the freeze (F11). DRR unchanged under
uniform scaling (Kuttruff Eq. 5.44).
Add to scope 2: "Consequence (documented): resizing scales distances and heights with the room; the default scene
stretched to 100 m³ puts the listener 52.9 m from L (−18.8 dB direct, AX2) at 42 m ear height. A UI resize that keeps
absolute positions, if wanted, is a Phase 11 gesture that rewrites the position parameters, not a mapping change."
Checklist room-size line: "positions scale with the room, so at maximum size everything is quieter and farther away;
use output_trim_db." Objection: users may expect the band to stay put (unsourced) → Phase 11 gesture.
Confidence medium.

## D3 (P07-8) 12 s cap: **(a) accept and document in 07; end treatment RESEARCH NEEDED → Phase 13**
(c) rejected (CONDITIONS VIOLATED: only default materials). Checklist: "Shrink room_w/d/h to minimum, then maximum:
small booth vs very large hall. At maximum size the IR is cut at 12 s (AX6): every band with T60 > 8 s is cut, and
with the default materials the 63 Hz band is only ≈ 12 dB below its start when it stops. Expected in 07; describe
what you hear." AX6 add: "reachable from host parameters from Phase 07." Phase 13 follow-up: Q1 audibility of a
rectangular cut vs remaining decay depth per band (music); Q2 fade length; Q3 CPU/memory of a 20–30 s cap at 96 kHz.
Confidence high for 07.

## D4 (P07-3) headroom: **B, output_trim_db −48…+24 dB**
A rejected (premise: gainDb +12 → +28.5 dB direct > 24); hidden normalisation rejected (AX2). Worst case (63 Hz,
1.5 m cube, α = 0.01, gainDb +12, both at 0.3 m, coherent): direct +28.5, reverberant 25.7 + 6 + 12 = 43.7 dB,
power sum +43.9 dB (Kuttruff Eq. 5.44). Parameters alone (gainDb 0, default materials) ≈ +25.8 dB.
Assumptions text: "The plugin's gain can exceed 0 dB: up to +28.5 dB direct (gainDb +12, both emitters at 0.3 m) and
≈ +44 dB band level in a 1.5 m α = 0.01 booth (Kuttruff Eq. 5.44 estimate); output_trim_db (−48…+24) covers it;
float does not clip before the master (Izhaki Ch. 11)." DoD (recorded, not gated): render that extreme scene and
record the maximum band output gain. Phase 11 follow-up: over-0 dB indicator (display only).
Objection: diffuse formula in a modal booth; direction rests on the geometric +28.5 alone. Reversal: measured > 48 dB.

## D6 (P07-12) 20 ms cap: **A, new AX33**
"**AX33 — IR-build rate cap (AQ4):** the 20 ms cap is a minimum spacing between the starts of successive background
builds. A request with no build running and none started in the last 20 ms starts at once; requests during a build or
within 20 ms of the last start are coalesced into one build starting at max(last start + 20 ms, end of the running
build). Non-realtime mode has no cap (synchronous, AQ4). | Isolated updates reach the output after rebuild + 2P (AX31)
with no slot wait; steady-state spacing unchanged (AQ4); within Vorländer Table 15.1 (700 ms); AQ4's recommendation.
Phase 10 confirms or replaces it. | 07, 10". AQ4: "settled by AX33 (Phase 07); Phase 10 confirms or replaces it."
Scope 3: "It applies AX33" + injected-clock test (isolated request starts at once; requests 5 ms apart start ≥ 20 ms
apart; final state built). Record full-rebuild time at default and maximum room in §0. Confidence high.

## D7 (P07-13) crossfade law: **AX18 per class + no-op rule + corrected premise**
No single-gain law exact when ρ differs per band. Under automation the aligned direct sound and low bands (ρ ≈ 1)
dominate; equal-power would pump +3 dB every ~32 ms.
Scope 3: "Crossfade laws (AX18): parameter-driven rebuilds (positions and room size) use EqualGain; a
setStateInformation during playback whose derived scene differs from the current one uses EqualPower; if the derived
scene equals the last submitted scene (contract equality), nothing is submitted. Known 07 limit (not gated): moves
that change the nearest emitter's distance decorrelate the tail's upper bands (AX18 note), so EqualGain dips there
mid-fade (e.g. Δr = 16 cm: −10.6 dB in the 1 kHz tail band). The PR records the per-band expected mid-fade output
power relative to the power-linear interpolation (AX22's P(g) / R(g) from the two IRs) for a 3 cm listener_y step and
a 10 % resize of the default scene."
AX18 amendment: replace "where consecutive IRs are highly correlated" with "correlated in the aligned direct sound and
low bands; when the nearest emitter's distance changes, AX1 shifts the shared tail by Δr/c, decorrelating its upper
bands (ρ_b ≈ cos(2π·1.06 f_c τ)·sinc(0.707 f_c τ)), as real tails do between positions (Vorländer Eq. 6.14);
equal-gain then dips there. Phase 10 resolves."
Phase 10 follow-up: gate per-band mid-fade deviation 500 Hz–2 kHz ≤ 1 dB vs power-linear interpolation; choose a
per-band/segment or correlation-matched law (Fink 2016) as a new AX. Confidence medium.

## D8 (P07-19) unsupported rate: **B, delayed dry pass-through, new AX34**
"**AX34 — Unsupported host sample rate:** if prepareToPlay gets a rate outside AX6, the plugin catches the engine's
refusal, outputs the input delayed by the reported latency (P + 32 samples, unchanged, so delay compensation stays
aligned), sets the warning flag (shown in Phase 11) and starts no IR build; a later prepareToPlay at a supported rate
restores the room render. No resampling in v1. | Hosts cannot be refused (F5–F8) and auval drives 11.025/22.05/192 kHz
(M1); silence would drop the track from the mix; delaying keeps delay compensation aligned (Izhaki Ch. 11). | 07, 11, 13"
Test: at 11025, 22050, 176400, 192000 Hz prepareToPlay doesn't throw, output bit-equals input delayed by 544, flag set;
a following prepareToPlay(48000) renders the room and clears the flag. Replace the Risks clause about pluginval's
sample-rate test (defaults 44.1/48/96 only, F1); add unsupported rates to `run_pluginval.sh` if v1.0.4 accepts the
option. Phase 13 follow-up: internal resampling. Confidence medium.

## D9 (P07-22) room-size mapping: **C, true log map**
Scope 2: "room_w/d/h: L = 1.5·(100/1.5)^x (NormalisableRange with lambdas, F10), result clamped to [1.5, 100] so x = 0
and x = 1 give exactly 1.5 and 100 m (AX9 compares dimensions exactly); the formula is recorded in
parameter_ids_v1.json." Test: endpoints exact, monotone. Basis: 1 % travel = +4.29 % L ≈ one T jnd for all three axes
(Kuttruff §7.6, Eq. 4.12; Vorländer Table 6.1); log map minimises the largest relative step (∫ d ln L/dx = ln 66.67).
Confidence medium-high.

## Challenge to a settled decision
AX18's "position updates → highly correlated" does not hold for the tail (AX1 shift, Vorländer Eq. 6.14). Wording fix +
Phase 10 duty; no settled value changes.
