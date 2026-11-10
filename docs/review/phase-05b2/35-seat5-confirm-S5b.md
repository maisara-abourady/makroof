# Seat 5 — confirmation S5-b (D-T1.3 block size)

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

SEAT 5 POSITION: S5-b, D-T1.3 block size (N-3W*** with 64-history D4 blocks; 32 as the alternative)

I read `34-decider-round4-final-T1-T2-T6.md` (§C S5-b; §D-T1.3, joint accounting, W_scene = 2·W_max = 6.10 M) and `33-orchestrator-C16.md` (h). Nothing acoustic here; these are clock, determinism and CI claims.

**1. Reading**

The question is whether the D4 block of 64 histories, and the pilot overrun it allows, is acceptable on the restore clock and for determinism.

My cues:
- §10.2: worst case first.
- §4.1: bounded work on the host's synchronous thread.
- S5 / AX5: every count that decides which paths run must be identical on all platforms.
- D6: how long `quiesce()` waits.

**2. Ranking**

- **Block 64: prefer.** It is what I would pick.
- **Block 32: can live with.** No better on my clock in any way that matters.

I would not ask for 32. On my measures the two are equal within tolerance.

**3. Tension now**

**Block 64: 1.**
- **The overrun does not reach my clock.** N_cap is computed from the work left: ⌊(W_scene − W_pilot)/ē_pilot⌋, rounded down to whole blocks. So the 15.3 % overrun (layout4_s1/listener_corner, C16 (h)) takes work from the final range; it does not add work on top. The pilot can reach at most 0.653·W_scene, never W_scene.
- **The final range shrinks.** That costs accuracy, which is Seat 1's measure.
- **Total work stays near W_scene.** It is W_scene times the final range's cost scatter, which C13 measured at ≤ 1.02 in the prototype.
- **Why the rating is 1 and not 0.** The bound is statistical, not hard: N is fixed before the final range is sampled, as determinism requires. The scatter is largest where N is smallest; layout 4 runs only 128–384 final histories (C16 (f)).
- **`quiesce()` wait.** One flutter-cube history is about 2 × 2445 forward + about 2 × 2445 next-event evaluations ≈ 9 800 [Inferred from C12 (d)]. One 64-history block is then ≈ 0.63 M evaluations, about 27 ms at 42.5 ns on 1 thread. The wait is on the message or host-call side, not the callback, and inside its tolerance.

**Block 32: 1**, for the same reasons. It halves the `quiesce()` wait to about 13 ms and doubles the blocks available to threads in short pilots (layout 4: n* = 256, so 4 blocks at 64). Neither gain matters at the pinned W_max, which assumes a 1-thread pool.

**4. Tension later**

**Block 64: 1.**
- **What it commits later phases to:** the block size sets how n* and N round. Changing it after release changes every shipped estimate, so it costs a golden round and an announced change (Seat 7's register).
- **Undo cost:** a parameter change.
- **Evidence:** the C++ realised-work record against W_scene at the gated scenes.

**Block 32: 1**, the same.

**5. Evidence**

Sources:
- C16 (h): overrun 0.153 at block 64 and 0.076 at block 32; < 10.2 % at the gated 100 m scenes; 64 and 32 both divide 8 000 and 1 024.
- C16 (f): n* and N per scene.
- 34 §D-T1.3: the joint rule.
- C12 (d): evaluations per path and ns per evaluation (prototype).

[Inferred]:
- the per-block `quiesce()` arithmetic;
- that ≤ 1.02 carries over to C++.

Already met:
- W_max provisional at 3.05 M per emitter is my 1-thread derivation (round 2).
- N computed without libm and rounded to blocks is my D7.

**6. Conditions** (to hold my 1/1; none are veto-grade)

- **Integer cap arithmetic.** Compute N_cap and the pilot stop test in 64-bit integers on evaluation counts, as ⌊(W_scene − W_pilot)·n* / W_pilot⌋, with no float division. Otherwise a rounding difference at a block boundary could change N between platforms (AX5).
- **n* and N in the D5 golden.** Record per-case n* and N beside the face-sequence hash, required to be equal on all three OSes.
- **Realised work asserted in CI.** The diagnostics already report realised work against W_scene. At the gated scenes, CI should assert a pre-registered ratio, e.g. ≤ 1.05 [Hyp; to be set from C++ C13-style data before the first run]. That turns the statistical bound into a checked one.

**7. Hand-offs**

- **Seat 1:** the accuracy cost of the pilot overrun. Up to 15.3 % of W_scene moves from the final range to the pilot in layout 4/5-class rooms.
- **Seat 7:** a block-size change after release changes shipped bits.
- **Orchestrator:** the C++ cost scatter of realised against planned work, at block 64, at the gated scenes and in layout 4.

**8. Premortem**

If block 64 fails, it fails the same way 32 would: the final-range cost scatter at small N (layout 4) runs past the 1.02 the prototype saw, and a restore at a gated scene goes over 2.14 s. The CI realised-work assertion in §6 catches it first, if it is adopted.

Files: /home/user/makroof/docs/review/phase-05b2/34-decider-round4-final-T1-T2-T6.md, /home/user/makroof/docs/review/phase-05b2/33-orchestrator-C16.md, /home/user/makroof/docs/review/phase-05b2/22-orchestrator-C12.md
