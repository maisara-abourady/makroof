# 3 — Seat 5 position (phase 07c-1, D-C1/D-C2/D-C3/D-C9)

Saved verbatim by the orchestrator from the agent's report, 2026-11-12. Brief: file 2.

SEAT 5 POSITION (phase 07c-1, matters A–D; lead)

**Reading.** The question is what plays, and what the saved state carries, between a restore or an edit and the final IrSet once the solve (81–131 ms) and the synthesis (3.14 s at 100 m / 96 kHz) leave the synchronous path. It triggers these cues: S1 (an interim and then a final snapshot arriving during playback), S5 (an offline bounce that differs from playback), 4.3 (the host's offline signal and its state polling), and CS-2 (the handoff).

**One fact from the code shapes every rating.** E_b is the cheap part. The solve is about 0.1 s and the unit-decay waveform about 3.1 s (file 1; AX38 4c). At load, a tail cannot play before the waveform exists, and by then the solve finished about 3 s earlier. So in 07c-1 a saved E_b changes almost nothing that is audible at load. It starts to matter only (a) for edits, where cached unit decays already exist (AQ4), and (b) in 07c-2, once a larger W_max makes the solve longer. The only way to remove the tail gap at load is to carry or produce the waveform (D3, D4/A3).

## Matter A (state)
- **A1 prefer.** Now 1 / later 1. The cost is about 16 doubles plus a key, state v2, a v2 fixture, and v1 fixtures still loading (phase-07 L234). Undoing it means ignoring the field. The evidence comes in 07c-2, when the solve time at (C) W_max is known.
- **A0 can live with.** Now 0 / later 1. In 07c-1 the interim gains almost nothing, but 07c-2 will need the v2 bump anyway, possibly after release.
- **A2 can live with.** Now 1 / later 2. The risk is a stale value treated as authoritative. If someone changes the estimator without bumping the version id, the saved E_b is wrong for that project forever, offline included, and nothing re-solves it. There is also an undo problem: the user edits (invalidated), then undoes back to the saved scene; it is re-solved, and across builds or OSes it can differ from the saved E_b. Two renders of one scene in one session then differ (criterion 2). Offline under A2 skips only about 0.1 s of a 3.3 s build.
- **A3 can live with only under conditions.** Now 2 / later 2. At about 18 MB raw it becomes about 24 MB of base64 inside XML (`copyXmlToBinary`, from the code). That is multiplied by every autosave and undo snapshot, and by 8 instances. The waveform depends on fs, so a reopen at another rate makes it useless. The restore still has to build the IrSet. My rating rises to 3 if R5 or R1 show a host taking state on, or blocking, the audio thread while saving [Hyp].
- **Conditions.** For A2: a CI "estimator fingerprint" test that fails when E_b on a fixed fixture scene changes without a version-id bump; E_b stored as a bit-exact hex bit pattern, not decimal text; and a saved E_b reused whenever the scene key matches again, not only until the first edit. With those, A2 drops to 1 / 1. For A3: R5 shows no size problems at ≈ 20 MB per instance, the fs is in the key, and the state is regenerated on load, never trusted across fs. That would bring it to 1 / 2.
- **Debt for A1 and A2.** Once released, a v2 state makes a v1 build reject the whole state and fall back to the default scene (`migrateState`, from the code). That matters only after release; it is Seat 7's downgrade question.

## Matter B (interim when no matching E_b)
- **B4 prefer.** Now 0 / later 1.
- **B1 can live with.** Now 0 / later 1. It is incomplete at load.
- **B2 can live with.** Now 0 / later 1. Under 07c-2 it means two solves and two steps per edit; that cost lands in 07c-2.
- **B3 can live with.** Now 1 / later 2. It adds a branch that depends on the scene class, and A4 then has to test every class. It is out unless Seat 2 shows a predictor exists.

Thread safety, for every B option:
- **Latest-wins handover.** The mailbox is a lock-free single slot where the latest request wins (`CrossfadingConvolver.h`, `is_always_lock_free` asserted), so two submits per change are safe as it stands.
- **Interim submits must not record the generation as handled.** Today `decide()` stores `handled_` on submit. An interim recorded that way would stop the builder, and the final would never arrive.
- **Submits must be ordered.** Every submit has to go through `decide()` under `stateMutex_`, with a monotonic (generation, stage) check. Without it, a slow interim from the host thread can land after the final and overwrite it. Latest-wins does not know the order.
- **Retire queue (records only).** With two fades per change, each retirement passes through the retire queue. Measure its high-water mark at 8 instances in record (d).

## Matter C (step)
Seat 1 rules on the number; my point is only how each option can be built.
- **C1 prefer.** Now 0 / later 0. The step can be measured after the final lands. The builder thread computes it from the two E_b values, and a counter records it, never in the callback.
- **C3 can live with.** Now 0 / later 1. Same mechanics as C1.
- **C4 can live with.** Now 0 / later 1. There is no test to bind it.
- **C2.** Now 2 / later 2. It cannot be checked at run time, because |interim − final| is unknown until the final exists. It can be built only as a design-time bound per source: a saved E_b with a matching key is 0 dB by construction. That design-time bound is the condition that brings it to 1.

## Matter D (tail pending)
- **D1 at load plus D5 on edits.** This is the pair I prefer. D1 alone: now 1 / later 2. D5: 1 / 1.
  - D1's sync restore is ISM + matching + mix, about 0.15 s, and the tail joins after about 3.3 s of wall-clock time.
  - D5 reuses `cachedUnitDecays`; it needs no new generator and adds one submit.
  - **Debt (R2).** If the host does not signal offline, a bounce right after load runs on the real-time path for about 3.3 s of wall-clock time. Faster than real time, that can be tens of seconds of audio with no tail. Two such bounces differ, and L3 fails. No A option fixes this; only a waveform in hand does.
- **D2 can live with.** Now 1 / later 1. At load it equals D1. On T60 edits it holds the ISM update behind the synthesis, which breaks condition 4 (Seat 3's ground). On reset, condition 10 already keeps the current IrSet.
- **D3 can live with.** Now 2 / later 2. A second generator: its cost at 8 concurrent loads is unknown [Hyp], it adds transient memory, makes a third submit, and needs a test proving offline never uses it. Conditions to bring it to 1 / 1: it runs outside the gate, its cost is measured at 1/4/8 instances in records (c), (d) and (f), and a `[pipeline]` test shows offline bypasses it.
- **D4 (needs A3).** Now 2 / later 2. Same conditions as A3.

Fallback if R1 shows a tight limit on restore: `setStateInformation` stores only, and the builder does everything. That cannot be used where it would mean silence (condition 5).

## Answers to the brief's direct questions
- **Under A1, does offline wait?** Yes. The offline `process()` runs `decide(Offline)`, which builds in full before the block (from the code). A1's interim never reaches a bounce that the host signals.
- **Under A2, does offline skip the solve?** It skips only the solve, about 3 % of the build at 100 m / 96 kHz.

**Which ratings move on the researcher's answers.**
- R2, "a common host does not signal offline by default": D1/D2/D3 later rises to 3, because a bounce would depend on wall-clock timing (criterion 2). A3/D4 then becomes my preference, provided R5 is clean.
- R5 "problems at multi-MB": A3/D4 goes to 3.
- R1 "limit ≤ 0.5 s per call": D3 run synchronously is out, and A3 is out.

**Evidence.** The code facts are from `ScenePipeline.cpp` L166–243 and L429–439, `PluginProcessor.cpp` L236–285, and `CrossfadingConvolver.h` L10–50. Timings are from AX38 4c (file 1). The handover rules are CS-2, and Steam Audio's "latest available, never block" is WI-4 [Observed]. The claim that an interim must not be recorded as handled is my reading of the code. Everything about host behaviour is [Hyp] pending R1, R2 and R5. I make no acoustic claims; I have not checked the corpus.

**Hand-offs.**
- Seat 3: the crossfade law from interim to final. Under D1 the early part is shared between the two IRs, so EqualPower (the restore law, AX18) would lift it by up to +3 dB in mid-fade [Hyp]; EqualGain looks right. Seat 3 also decides whether a progressive synthesis can be bit-identical.
- Seat 1: the number for C.
- Interrogator: whether D1 at load breaks condition 9.
- Seat 7: v1 builds rejecting v2 state after release.

**Premortem.** If D1 is chosen and R2 turns out badly, the first sign is a beta producer whose bounce right after reopening, in a host that does not signal offline, starts without its tail, and whose second bounce does not match the first.