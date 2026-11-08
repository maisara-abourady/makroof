# Phase-07 decision loop, round 3: decider, D7 restore flag only (2026-11-08; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

Nothing else reopened; AX18 text, Phase 10 follow-up and other decisions as in round 2.

## Revised D7 bullet for phase-07 scope 3 (replaces the round-2 bullet)

> "**Switch rule and crossfade law.**
>
> *Skip rule.* A submit is skipped when the built RoomIR is bit-identical (length and taps) to the IR of the last
> successful submit since the last `prepare()` or reset. Step 3 of the reset sequence always submits. If the derived
> scene equals the last submitted one in every field, the build may be skipped as well (AX5: the same scene gives the
> same IR).
>
> *Restore flag.* `setStateInformation` advances the dirty generation and records it as the restore generation g_R,
> which sets the flag. The flag applies only to the restore's own submit decision: the first build decision whose
> scene generation is ≥ g_R. That decision either submits or skips as bit-identical, and in both cases it clears the
> flag. A build that merges the restore with parameter changes made after it is still that decision.
> - Realtime: the builder makes this decision.
> - Offline: the deferred submit in `processBlock` makes it at the next block boundary and clears the flag there. Host
>   call order fixes which block that is, so bounces stay deterministic (AX5).
> - The rule is generic: no scene fields or values are inspected beyond the IR comparison (NFR-8).
>
> *Law.* The submit made by the restore's decision uses EqualPower. Every other submit uses EqualGain (the AX18
> placeholder for position and room-size updates; Phase 10 sets the law).
>
> *Tests* (realtime and offline each; the law is checked by a −100 dB null of the output against the analytic
> crossfade of the two IRs, the Phase 06 technique):
> (a) Restoring the current state during playback starts no fade: the engine's fade counter is unchanged, the output
> is unchanged, and the flag is cleared.
> (b) After (a), the next listener_y change crosses to the new IR as an EqualGain fade.
> (c) Restoring a different state crosses as an EqualPower fade, and the next listener_y change after it is EqualGain.
> (d) A restore with a parameter change in the same block (offline) or the same build (realtime, forced by an injected
> clock) makes one EqualPower fade, and the next change is EqualGain.
> (e) Offline (c) is bit-identical across two bounces."

Load-bearing: L8 the flag cannot outlive its restore (consumed by the restore's own decision, submit or skip);
L9 offline the consuming decision falls at the first block boundary after the restore in host call order (AX5);
testability: Phase 06 analytic-crossfade nulls ≤ −133 dB vs a −100 dB gate. Confidence medium.
