# 39: Seat 5 on running and gating (a0) (M3-H)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 5 POSITION (follow-up on M3-H, (a0) run and gate). Read-only; I changed no files. The orchestrator should save this as /home/user/makroof/docs/review/phase-07c-2b/39-seat5.md.

**1. Reading.** The question is how (a0), the near-corner tracer at r_d 0.05 m and 0.025 m in layout 4, is run, sized and gated, and what happens when it outgrows a runner. Cues: S5 (determinism of a reference), §10.2 (size for the worst case) and CS-5 (one-person pipeline).

**2. Ranking.**
- **Prefer:** a per-window k gate, a pilot run, and a sharded manual CI job (text below). I added this option because no text on the table sized the job.
- **Can live with:** an offline one-off on Maisara's machine, but only if it uses the same sharding, pins and artifact.
- **Cannot live with:** a per-bin gate at k ≥ 684 for (a0). Using the researcher's 10⁹–10¹⁰ particles (F9) at the 05h rate of 49 s per 16 M, about 3.1 µs per particle (F11), one run takes 0.85 to 8.5 h. There are 4 runs (2 emitters × 2 radii). The 0.025 m runs cost ×4. That exceeds a hosted runner's job limit with no stated stop.

**3. Required text** (07e scope 3, under (a0)):
> "(a0) runs as a manual CI job (`workflow_dispatch`), never on PR open, with its JSON uploaded as an artifact; that artifact is the reference. The seed is TRACER_SEED and is never changed (B11). The numpy pin is hash-locked.
> **Gate per window, not per bin.** For each emitter, radius and band, k = (ΣE)²/ΣE² is computed over the same late window the verdict compares, and the window counts when k ≥ 684. Per-bin k is not used for (a0).
> **Sizing.**
> 1. A pilot at N_pilot = 16 M (the 05h precedent) runs per emitter and radius. It records k_pilot per band and the measured µs per particle.
> 2. N = N_pilot × 684 / min_band k_pilot (F7), rounded up to whole 200,000-particle chunks.
> 3. The pilot's particles are the first chunks of N. Particles are added, never redrawn.
> **Sharding.** The job splits into shards of whole chunk ranges (`first_chunk`, `total_n` = N). Each shard's predicted wall time, from the pilot rate, is at most half the runner's job limit. Shards are merged by summing e and e². The merge is checked to be bit-identical to an unsharded run on a small N (a unit test).
> **Cap.** The total predicted runner time for (a0) is capped at a figure Seat 7 sets before the pilot. If N for a band would exceed the cap, that band is gated for (a) only at SE ≤ 0.5 dB (window k ≥ 76), and the record says so. If it cannot reach that either, the band does not count.
> **On a timeout.** A shard that exceeds its limit fails the job. A partial result is never merged or used. The loop re-shards at the measured rate and reruns once. A second failure counts as 'over cap', and the cap rule applies. Compute time is not session time; 07e-c is opened only if the artifact is not back before 07e's second session ends."

**4. Tension now (H4+G with this text): 1.** The cost is a small sharded workflow and its merge test, plus runner minutes. The per-bin gate rates **3** (an unbounded job with no stop rule).

**5. Tension later: 1.** The reference depends on the numpy and Python pins. A pin bump means rerunning (a0), at the cost of one manual job. Evidence that could overturn the plan arrives with the pilot's k_pilot: if the window k still needs more than the cap, (a) falls to the SE fallback or "not decidable". The per-bin gate rates **3** later as well: whether the reference exists at all would depend on runner luck.

**6. Evidence.**
- From the code (tracer.py L30–32, L203–238): chunk j is seeded by SeedSequence([seed, j]), and `first_chunk`/`total_n` exist. That makes sharding and the pilot-as-prefix deterministic.
- F7: k ∝ N, so pilot sizing is valid.
- F9: annihilation regime, ×6.6 to ×77 late in the window.
- F11: 49 s per emitter at 16 M; window k 186–298.
- SE fallback arithmetic: 4.34/√k ≤ 0.5 gives k ≥ 75.3.
- `[Hyp]`: the per-particle cost in layout 4 is at or below W1's, because particles die at the floor. The pilot measures it.
- **Researcher to verify:** the hosted-runner job time limit (I hold 6 h, unsourced here) and the repo's minutes quota.

**7. Conditions.** For the per-bin gate, 3 → 1: switch to the per-window gate and add the cap with its fallback.

**8. Hand-offs.**
- Seat 7: the runner-time cap and minutes cost.
- Seats 2 and 9: confirm that the verdict's late window is the window k is gated on.

**9. Premortem.** Suppose the gate stays per bin with no cap. The first 0.025 m run times out at 6 h, someone merges a partial shard "to save time", and the reference is wrong without anyone noticing. The interrogator or the contracted engineer would be the first to notice, through a mismatched N in the artifact.
