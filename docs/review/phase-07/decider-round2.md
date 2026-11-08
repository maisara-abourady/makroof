# Phase-07 decision loop, round 2: decider report (2026-11-08; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

Responds to interrogator-decision-round1.md (D7 FALLS; corrections) and advocate-round1.md (D7 REDIRECT; PASS
conditions). Re-read: Kuttruff Eq. 3.53, 5.26, 5.45, Table 6.1; Vorländer §15.3.

## 1. D7 redecided
- **No-op:** a submit is skipped when the built RoomIR is bit-identical (length, taps) to the IR of the last
  successful submit since the last prepare() or reset. Generic (NFR-8), deterministic (AX5). Code ignores
  `maxReflectionOrder` for Omni (`Engine.cpp` 368–383; AX20); outputMode, hrtfId, extensions ignored in 07. Optional
  shortcut: skip the build when the derived scene equals the last submitted in every field (AX5). Also makes R3-1's
  redundant G→G resubmit harmless.
- **Restore law:** a flag set when a setStateInformation is applied; the next successful submit (realtime, or the
  deferred offline submit in processBlock read at a block boundary in host call order) uses EqualPower and clears the
  flag; every other submit uses EqualGain.
- **Positions:** a move δ per update changes each path by ≤ δ; AX1 shifts the tail by τ ≤ δ/c; pure-delay band
  correlation ρ_b = cos(2π·1.06·f_c·τ)·sinc(0.707·f_c·τ), sinc(x) = sin(πx)/(πx) (signal theory). EqualGain is closer
  where ρ_b ≥ 0.414 ⇔ f_c·τ ≤ 0.170 (cos 1.133 × sinc 0.120 = 0.424 × 0.976) ⇔ δ ≤ ≈ 58 m·Hz/f_c (5.8 cm at 1 kHz,
  2.9 cm at 2 kHz, 1.5 cm at 4 kHz). **No product document gives an automation speed in m/s** (PRD, phase-07
  checklist; phase-10 "1 m to 15 m and back over 8 bars", no tempo). Vorländer §15.3 VR speeds (not product) with
  32 ms updates: δ ≤ 1.6 cm → holds below ≈ 3.6 kHz; 07 full rebuilds up to ≈ 160 ms (§0 row 04): δ ≤ 8 cm → below
  ≈ 0.73 kHz. **No corrected premise supports EqualGain or EqualPower for positions across bands.** EqualGain kept as a
  **placeholder** within 07's ACs (no fade gate; zipper accepted): Phase 06 default (no code change); never raises a
  band above the louder endpoint (P(g) ≤ ((1−g)√E₁ + g√E₂)² ≤ max(E₁, E₂), Cauchy–Schwarz on |C₁₂|), whereas
  EqualPower can add +3.01 dB. Phase 10 sets the law and gate.
- 07 per-band measurement dropped (no P(g)/R(g) tool in `tools/`; Phase 10 deliverable).
- Load-bearing: L1 code ignores maxReflectionOrder for Omni; L2 AX5; L3 (1+ρ)/2 vs (1+ρ), break-even 0.414; L4 the
  58 m·Hz/f_c bound; L5 no m/s speed in product docs; L6 Cauchy–Schwarz; L7 07 has no fade gate.
- Objection: EqualGain dips up to ≈ −10.7 dB per band (Δr = 16 cm, 1 kHz) kept in 07; tested by Phase 10's gate.
  Confidence: medium (rule), low (position law, placeholder by design).

## 2. Answers
- **Q3 (D4):** the trim matches programme level (band mean), not a full-scale sine on one mode. Power sum cites
  Kuttruff Eq. 5.45 (5.44 only for r_c). Eq. 3.53 (≈ 7.1 dB peak, ≈ +51 dB) is stated above the Schroeder frequency;
  a 63 Hz band in a 1.5 m booth is below it, so no corpus source bounds that peak; float doesn't clip before the
  master (Izhaki Ch. 11). −48 kept (band-mean estimate +43.9 dB). **+24 check** (default scene at 100 × 100 × 100 m;
  Eq. 5.45, Sabine A + 4mV, Kuttruff Table 6.1 50 % RH): direct −18.8 dB; reverberant 10·log10(16π/A) −2.4 → −24.4 dB
  at 1 kHz (A ≈ 87 → 13 920 m²), −1.4 → −23.0 dB at 500 Hz: drop ≈ 21.6–22.0 dB, covered by +24. 4/8 kHz drop ≈ 25.6 /
  29.2 dB is air absorption (AX4), timbre, deliberately not compensated (AX2).
- **Q4 (D9):** per axis, d ln T / d ln w = 1 − (share of A scaling with w) ∈ [0, 1] (Eq. 5.26 with 4mV), so 1 % of
  single-axis travel (×1.0429) changes T by 0 … +4.3 %, at most ≈ one T jnd (4 %, Kuttruff §7.6), any materials;
  default room 1 kHz: w 0.15 %, d 0.10 %, h 4.05 %. "≈ one jnd for three axes" withdrawn; minimax carries it.
  Endpoints by explicit branches (x ≤ 0 → 1.5, x ≥ 1 → 100), interior 1.5·pow(100/1.5, x) clamped; inverse likewise;
  test on three OSes.
- **Q5 (D8):** in the AX34 state: reset step 1 no-op (builder never started), step 2 no-op (unprepared), step 3
  skipped (buildRoomIR throws at unsupported rates, `Engine.cpp` 393–395; no record, R3-2), step 4 runs but the
  fallback doesn't use the smoother, step 5 doesn't start the builder; offline processBlock does no build (generation
  stays pending); setStateInformation validates and stores; trim not applied (unity, like a host bypass); AX32 guard
  not applied (it protects the convolver's FDL; a delay line has none). Bit-equality test: non-zero output_trim_db and
  a NaN sample, NaN at the delayed index (isnan). Latency 544 at every rate.

## 3. Final texts for the plan-editor

**D1 (phase-07 scope 2; mirror in `docs/contract/README.md` by the phase session).** Replace the push-away bullet:
> "Listener–emitter distances below 0.3 m: each emitter e is replaced by the point p of the margin box B with
> |p − l| ≥ 0.3 m that is nearest to e; the listener never moves; the two emitters are treated independently. If
> |e − l| ≥ 0.3 m, p = e. Otherwise p = l + 0.3·u, where u maximises u·d over unit vectors with l + 0.3·u ∈ B,
> d = (e − l)/|e − l|, or d = +y (AQ1 forward) if e = l exactly; exact ties are broken by the largest u·ŷ, then u·x̂,
> then u·ẑ. When l + 0.3·d lies in B this is the push along the listener→emitter direction. p moves the least
> possible distance; it jumps only where two nearest points tie (up to 0.52 m, e.g. across the line through l normal
> to a wall). Tests: (a) 10⁵ seeded cases (1.5 m rooms, l in corners, e = l): toContract() validates; (b) independent
> reference: |p − e| ≤ bruteMin + 1e−9 m, bruteMin over 10⁵ Fibonacci points of the 0.3 m sphere inside B plus 10⁴
> points on each circle where a face plane of B cuts the sphere (with (a) this bounds p between the true minimum and
> the sampled one); (c) 1.5 m cube, l = (0.25, 0.75, 0.75), e = (0.1, 0.75, 0.75) → p = (0.1, 0.75 + 0.15√3, 0.75)
> within 1e−12 m. Reversal: Phase 10 traversal scenarios or Phase 08 listening find the tie jumps objectionable →
> Phase 10 proposes an AX."

**D2 (phase-07 scope 2, after "Resizing the room keeps relative positions").**
> "Consequence (documented in the README): resizing scales distances and heights with the room. The default scene
> stretched to 100 × 100 × 100 m puts the listener 52.9 m from L at 42.1 m ear height: direct sound −18.8 dB re the
> default scene (−34.5 dB re 1 m, AX2). DRR is unchanged only for uniform scaling without air absorption (Kuttruff
> Eqs. 5.44/5.45); per-axis resizing or air changes it. With absolute positions the in-room share of a 0.1–99.9 m
> slider would be 1.3 % in a 1.5 m room and 3.8 % for the default height. A UI resize that keeps absolute positions
> is a Phase 11 gesture, not a mapping change."
Checklist room-size line add: "positions scale with the room, so at maximum size everything is ≈ 19–22 dB quieter;
restore it with output_trim_db."

**D3 (phase-07 checklist; AX6).** Room-size line:
> "Shrink room_w/d/h to minimum, then maximum: small booth vs very large hall. At maximum size the IR is cut at 12 s
> (AX6): every band with T60 > 8 s is cut; with the default materials the 63 Hz band is only ≈ 12 dB below its start
> when it stops. Expected in 07; describe what you hear."
AX6 append: "Reachable from host parameters from Phase 07."

**D4 (phase-07 scope 2 range; "Assumptions in force" after AX2).** `output_trim_db` −48…+24 dB, linear in dB,
default 0.
> "The plugin's band-mean gain can exceed 0 dB: up to +28.5 dB direct (gainDb +12, both emitters at 0.3 m) and
> ≈ +44 dB in the 63 Hz band in a 1.5 m α = 0.01 booth (Kuttruff Eq. 5.45, a diffuse-field estimate);
> output_trim_db −48…+24 covers programme level, and +24 covers the ≈ 19–22 dB mid-band drop at maximum room
> (4–8 kHz fall further by air absorption, AX4, not compensated). Single-mode peaks above the band mean are not
> bounded by any source below the Schroeder frequency; float does not clip before the master (Izhaki Ch. 11)."
DoD (recorded, not gated): "render the extreme scene (1.5 m cube, α = 0.01, gainDb +12 on both emitters, both at
0.3 m, identical L = R input) and record the maximum octave-band gain of the summed omni IR (AX14 bands) in the PR;
if it exceeds 48 dB, widen before release."

**D6 (BUILD_PLAN §2 new AX33; AQ4 pointer; phase-07 scope 3).**
> "**AX33 — IR-build rate cap (AQ4):** the 20 ms cap is a minimum spacing between the starts of successive
> background builds. A request with no build running and none started in the last 20 ms starts at once; requests
> during a build or within 20 ms of the last start are coalesced into one build starting at max(last start + 20 ms,
> end of the running build). Non-realtime mode has no cap (synchronous, AQ4). | An isolated update reaches the output
> after at most rebuild + 2P (AX31), with no slot wait; steady-state spacing is unchanged (AQ4); within Vorländer
> Table 15.1 (700 ms); AQ4's recommendation. Phase 10 confirms or replaces it. | 07, 10"
AQ4: "settled in Phase 10 by an AX entry" → "settled by AX33 (Phase 07); Phase 10 confirms or replaces it".
phase-07 scope 3: "It runs at most every 20 ms" → "It applies AX33"; injected-clock test: isolated request starts at
0 ms; requests 5 ms apart start ≥ 20 ms apart; final state built. Record full-rebuild time at default and maximum
room in §0.

**D7 (phase-07 scope 3, new bullet).**
> "**Switch rule.** A submit is skipped when the built RoomIR is bit-identical (length and taps) to the IR of the last
> successful submit since the last prepare() or reset (the reset sequence's step 3 always submits); if the derived
> scene equals the last submitted one in every field, the build may be skipped as well (AX5). Law: EqualPower if a
> setStateInformation has been applied since the last successful submit (flag cleared by that submit; offline, the
> deferred submit in processBlock reads the flag the same way), otherwise EqualGain (AX18 placeholder for position
> and room-size updates; Phase 10 sets the law). Test: restoring the current state during playback starts no fade
> (fade counter unchanged, output unchanged); restoring a different state starts an EqualPower fade, realtime and
> offline."

**AX18 full replacement:**
> "**AX18 — Crossfade law by IR relation:** IR switches keep the 30 ms length (AQ4). A switch to a bit-identical IR is
> not made (Phase 07). **Equal-power** (sin/cos ramps) for switches between unrelated responses: a state restore that
> changes the IR (Phase 07), the output-mode switch (Phase 09), large jumps (Phase 10). **Equal-gain** (linear
> complementary ramps) for position and room-size updates, **as a placeholder until Phase 10 sets the law and its
> gate**. The same equal-power law joins the ISM to the stochastic tail inside one IR (Phase 04: 5 ms centred on
> t_mix, cos on the ISM, sin on the tail, squares summing to 1), since the two parts are uncorrelated. | Uncorrelated
> broadband signals add in power (Vorländer §4.3 Eq. 4.14–4.16; cf. §9.2.1). Mid-fade band power relative to equal
> endpoint powers is (1+ρ)/2 for equal-gain and 1+ρ for equal-power (Vorländer §1.7, Eq. 1.37 cross term), so
> equal-gain is the closer of the two where ρ ≥ 0.414 and equal-power below; fading trades colouration against
> clicks (§15.1). **Correlation of position updates** (Phase 07 decision loop): a listener or emitter move δ changes
> each path length by at most δ, and AX1 shifts the shared tail by τ = Δr_nearest/c ≤ δ/c; for a pure delay τ an
> octave band of flat noise has ρ_b = cos(2π·1.06·f_c·τ)·sinc(0.707·f_c·τ), sinc(x) = sin(πx)/(πx) (signal theory,
> not corpus; amplitude and envelope changes ignored). ρ_b ≥ 0.414 needs f_c·τ ≤ 0.170, i.e. δ ≤ ≈ 58 m·Hz / f_c per
> update (5.8 cm at 1 kHz, 1.5 cm at 4 kHz); larger moves give lower, down to negative, ρ (Δr = 16 cm: ρ_1k ≈ −0.83,
> equal-gain −10.7 dB mid-fade in that band). Room-size updates change each path r_i by (k−1)·r_i. The product
> documents state no automation speed in m/s, so no band limit is guaranteed. Equal-gain never raises a band above
> the louder endpoint (P(g) ≤ ((1−g)√E₁ + g√E₂)², Cauchy–Schwarz). | 04, 06, 07, 09, 10"

**D8 (BUILD_PLAN §2 new AX34; phase-07 scope 3 and Risks).**
> "**AX34 — Unsupported host sample rate:** if prepareToPlay gets a rate outside AX6, the plugin catches the engine's
> refusal and enters the fallback: output = input delayed by the reported latency (P + 32 samples, 544 at P = 512, at
> every rate), unchanged (no output trim, no AX32 guard: like a host bypass, so delay compensation stays aligned);
> the warning flag is set (shown in Phase 11). In the fallback no IR is built anywhere (buildRoomIR throws at these
> rates): the builder is not started, reset steps 1–3 and 5 do nothing (step 3 records no submitted generation),
> offline processBlock does not build, and setStateInformation only validates and stores. A later prepareToPlay at a
> supported rate runs the normal path (synchronous build, flag cleared, builder started). No resampling in v1
> (Phase 13 decides). | Hosts cannot refuse a rate (F5–F8); auval renders at 11.025/22.05/192 kHz (M1); silence
> would drop the track from the mix; the delay keeps delay compensation aligned (Izhaki Ch. 11). | 07, 11, 13"
Test (Catch2, three OSes): at 11025, 22050, 176400, 192000 Hz with output_trim_db = −12 and one NaN input sample: no
throw; every output sample bit-equals the input delayed by getLatencySamples() (= 544), NaN at the delayed index
(isnan); flag set; prepareToPlay(48000) then renders the room (output differs from the delayed input) and clears the
flag; also 48 → 96 → 44.1 → 192 → 48 kHz without re-instantiation.
Risks: "test the second with pluginval's sample-rate test" → "pluginval's default rates are 44.1/48/96 kHz only (F1);
unsupported rates are covered by the AX34 test and auval (M1)".

**D9 (phase-07 scope 2: replace "skewed").**
> "room_w/d/h: L = 1.5·(100/1.5)^x with explicit endpoints (x ≤ 0 → 1.5, x ≥ 1 → 100), interior clamped to
> [1.5, 100]; the inverse likewise; formula recorded in parameter_ids_v1.json. One per cent of travel = ×1.0429 in L,
> the smallest possible largest relative step for any map onto [1.5, 100]; per axis it changes T by 0 … +4.3 %
> (Kuttruff Eq. 5.26 with 4mV), at most ≈ one T jnd (4 %, §7.6). Test (ctest, all three OSes): x = 0 and x = 1 give
> exactly 1.5 and 100.0, the inverse of 1.5 and 100 gives exactly 0 and 1, and the map is strictly monotone on 10⁴
> points."

## 4. Follow-up texts
**phase-10.md**
- Scope 8 → "**Isolated-update cap:** confirm or replace AX33 (Phase 07: minimum 20 ms spacing between build starts;
  an isolated request starts at once) and state the resulting isolated-update delay (at most rebuild + 2P, AX31)."
- Assumptions, AX18 line: "equal-gain for position updates is a placeholder (AX18 amendment); this phase sets the law."
- New AC: "**Position-fade gate (AX18 amendment):** every movement scenario states its speed in m/s and its measured
  update interval. At each IR switch, per output channel and octave band 500 Hz, 1 kHz, 2 kHz (AX14 rule as above):
  P(g) = a(g)²E₁ + b(g)²E₂ + 2a(g)b(g)C₁₂ for the law's ramps a, b, against R(g) = (1−g)E₁ + gE₂ at every ramp sample.
  **Gate:** max_g |10·log10(P/R)| ≤ 1 dB (dips and bumps; G's jnd, Vorländer Table 6.1, 500–1000 Hz, extended to
  2 kHz and a 30 ms fade). Report ρ_b = C₁₂/√(E₁E₂) per band. If equal-gain fails, propose a law as a new AX, e.g. a
  per-band or time-segment crossfade, or a correlation-matched law applied per band (Fink, Holters, Zölzer 2016,
  DAFx-16, Eq. 11, ρ from the two IRs; researcher F20)."

**phase-11.md**
1. Room-resize UI gesture that keeps absolute listener and emitter positions by rewriting the position parameters
   (automation of room_* still scales them; D2).
2. "Output above 0 dB" indicator: display only, no auto-gain (AX2; D4).
3. Show the AX34 unsupported-rate warning flag with the supported rates listed (D8).

**phase-13.md**
1. D3 end treatment at the 12 s cap. Answer first: (Q1) audibility threshold of a rectangular cut at a given
   remaining decay depth, per band, for music; (Q2) fade length that removes cut artefacts without shortening the
   perceived decay; (Q3) CPU and memory of a 20–30 s cap at 96 kHz. Then choose: keep the cut; an end fade (new AX,
   goldens via update_goldens.py, §6 row); or a longer cap.
2. AX34: decide whether to add internal resampling for unsupported rates (quality verifiable), replacing the
   bypass-like fallback.

## Summary
| id | decision | state | confidence | reversal |
|---|---|---|---|---|
| D1 | nearest valid point; tie-break y, x, z; tests (a)–(c) | revised | medium | Phase 10 / 08 tie jumps |
| D2 | relative positions; consequence text | revised | medium | Maisara veto / Phase 11 |
| D3 | 07 accept + document; Q1–Q3 to phase-13 | stands | high (07) | Q1–Q3 |
| D4 | trim −48…+24; band-mean basis | stands (corrections) | medium | extreme-scene gain > 48 dB |
| D6 | AX33, "at most rebuild + 2P" | stands | high | Phase 10 |
| D7 | IR-identity skip; restore flag → EqualPower; EqualGain placeholder; AX18 rewritten; Phase 10 gate | revised | medium / low | Phase 10 gate |
| D8 | AX34 bypass-like fallback with reset/builder gating | revised | medium | auval fails / Maisara |
| D9 | log map, explicit endpoints; per-axis 0–4.3 % | revised | medium-high | non-log law before release |
