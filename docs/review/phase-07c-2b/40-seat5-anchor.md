SEAT 5 POSITION (narrow: A-iii only)

**A-iii, a validation-only src/cli tail-gain flag: can live with. Tension 1 now, 1 later.**
- **Now:** one more option to parse, refuse and guard, about the size of `--abx-step-db`.
- **Later:** a second validation definition of a "tail step" sits beside `--abx-step-db`. If the two drift apart, the anchor and the AX47 step no longer measure the same kind of thing. That is Seats 1 and 3's concern; on my ground it is one more field the guard must keep out of `src/plugin` and out of goldens. Undo cost: deleting the option and its tests.

My conditions for keeping 1/1:
1. **Where the gain is applied.** Apply it to the IR taps: per emitter, taps from t_mix,e + 2.5 ms on are multiplied by 10^(g/20), after `assemble()` and before any convolution, inside `src/cli`. Add no new `src/sim` API. This rules out gaining the rendered output signal, where tail and early part cannot be separated. Because the change sits in the IR, the offline and `--realtime-emulation` renders inherit it identically, and the offline = real-time rule holds by construction.
2. **Guard.** Test 1 (`src/plugin` never names the field or the flag) and test 2 (never in golden-generating or BRAS code) are extended to the new field and flag string. Only Cli.cpp reads the field.
3. **Refusals (exit 1, before any output file is opened, as with r1).**
   - Omni only.
   - Refused with `--abx-step-db`, `--ensemble`, `--tail-only`, `--tail-level ax16`, `--switch-scene` and `--diagnostics`.
   - Refused with `--provisional-ir` and `--provisional-handover-sample` unless the decider says the anchor needs the combination. In that case, say so and test it.
   - g limited to a bounded range, e.g. [−12, 12] dB, as for the step.
4. **Tests on each runner, with no hash pinned across OSes (AX5, as for test 3).**
   - Taps before the boundary are bit-identical to the default IR.
   - Taps from the boundary on equal default tap × the float gain, bit for bit.
   - Run-to-run bit-identity.
   - Offline against `--realtime-emulation`: the −120 dB null.
   - The boundary sample is printed per emitter.
5. **CI.** These are tagged ctest/pytest cases in the normal three-OS run, not hidden tests.

**Hand-offs.**
- The hard gain step at t_mix,e + 2.5 ms is a discontinuity in the IR. Whether it is audible, and whether the step should be a short ramp, is a question for Seat 3 (which scales) and Seat 1 (which is heard).
- What the gain should scale (M1, E_target) is for Seat 2.

**A-i, A-ii, A-iv, A-v: NOT MY MATTER.** They change trial roles, the anchor scene or the anchor quantity using flags that already exist, which leaves no real-time, guard or CI ground of mine. One exception: if A-v were built as a new flag, the conditions above apply to it unchanged.

**Premortem.** If the gain is applied to the output signal rather than the IR taps, the offline and real-time renders stop nulling where the block boundary straddles the gain boundary. The test 5 null catches that first.
