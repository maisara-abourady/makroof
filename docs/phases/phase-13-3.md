# Phase 13-3 — Platforms

Size: **M** (remainder, if needed: `13-3b`) · Depends on: 13-2; and the phase-13 header in full: 00–12, including 05b, 05h, 07c (`done`, or the versioning fallback of scope 13 recorded), 05d, 05e and 05f (05f `done` or Maisara's recorded acceptance of the two-room label; 05d `done` or `blocked (reason)`, decider report 15, accepted by Maisara, 2026-11-05; with 05c, if it exists, `blocked` only on Maisara's recorded decision) · Part of: [phase-13](phase-13.md) · Lead subject matter: Seat 5 (Deadline keeper), "platform transitions"; "worst-case callback time"; "CI gates" · Read first: [`phase-13.md`](phase-13.md) (umbrella), `CLAUDE.md`, `docs/BUILD_PLAN.md` (all of §2–§3), PRD NFR-2, NFR-4, NFR-6

## Goal

This sub-phase's share of the umbrella goal ("Turn the vertical slice into a **private-beta build**"): meet the
performance budget on real Apple-silicon hardware, and build for every platform it is to install on (macOS and
Windows), with the render the same across machines (AX5).

## Assumptions in force

- **AQ10** budget (partition P ≤ 512 samples at 48 kHz; reported latency P + 32 = 544 samples (11.3 ms)
  at the default P = 512 (phase-06b D1); ≤ 15% of one core per instance for a 3 s tail;
  IR rebuild ≤ 50 ms for the AQ10 workloads W1 and W2 (position-only), in every output mode
  (decider report 8, accepted by Maisara, 2026-11-05)). **AX5**: the definition of "exactly as saved" across machines.
  (phase-13 assumptions, shared)

## Scope

Order: scope 4 (phase-13 scope 9) runs first, before C3's residual and S8 are recorded (D-PS4 instruction 2, Notes).

1. **macOS universal binary** (arm64 + x86_64) via `CMAKE_OSX_ARCHITECTURES`. Test both slices in CI (the
   x86_64 slice runs through Rosetta on the arm64 runner). (phase-13 scope 2)
2. Cross-architecture determinism (AX5): render the reference projects on arm64 and x86_64; the
   residual is ≤ −100 dBFS (compare CI artifacts in a final job). (phase-13 scope 3, last bullet, under
   "**Robustness tests** (Catch2 + pluginval options)"; the other bullets in 13-4)
3. **Flush-to-zero guard for MSVC on ARM64** (Windows on Arm): `sim/conv/Denormals.h` is a no-op there;
   implement with `_ReadStatusReg`/`_WriteStatusReg` (FPCR.FZ) together with an ARM64 Windows CI runner
   that can test it (Phase 06 follow-up). Until then **Windows-on-ARM runs unguarded**: the guard is a
   no-op on MSVC ARM64, so the AX37 (5.1) (i) guard and the phase-05h pool-worker guard do not apply there
   and the `[pipeline]` FTZ test SKIPs (D-H3 (c), decider files 20, 25; the public compatibility notes say
   so until this scope lands). (phase-13 scope 8)
4. **Small-buffer callback timing on real macOS hardware** (Phase 06 follow-up, brief
   `docs/sessions/2026-11-07-phase-06-followups.md` O3(b)): with the Phase 06 work spreading (AX31), the
   worst callback at host buffer 64, 12 s IR, P = 512, while crossfading must stay under its real-time
   budget (p99.9 < 100 %). CI measured it below the target on Linux (wall 66.6 %, thread-CPU 65.9 %, run
   42397114233) and Windows (wall 32.2 %, same run), but could not show it on the shared macOS runner:
   wall p99.9 75.5 % (run 42390056623), 609 % (42392204088), 161.8 % (42394370942) and 657.4 %
   (42397114233), with thread-CPU p99.9 109.9 % in 42397114233 (most of the wall overshoot is the runner
   taking the thread off the CPU). Measure it on an Apple-silicon Mac with the `[benchmark]` test (it
   prints wall and thread-CPU p99.9 per case); if it misses, the remedy is non-uniform partitioning
   (new AX entry, 13b, per scope 1) or another scope 1 optimisation that leaves the output unchanged
   within −100 dB (e.g. SIMD in the accumulation loops), not P = 256 (it raises convolution work per
   sample 1.5–2.1×, run 42397114233, host 512) and not a change to the target (phase-06b D1).
   (phase-13 scope 9; "13b, per scope 1" is `13-1b`, phase-13 scope 1 being in 13-1)
   Also the 8-concurrent-builder sweep with 07c-1b's instrument (buffer 64; 0/1/2/4/8 builders; priority
   obtained and callback count printed), also on the R5 Windows release machine; a residual opens 13-1b with B1-d = a
   process-wide limit on running background builds ≤ hardware threads − 1, class (1) and offline exempt, slot taken
   before the gate and never under `stateMutex_`, `quiesce()` waking slot waiters. (AX38 (i) cond. 12 (c) note;
   phase-07c-1b loop, 2026-11-13, D-B1 B1-b)

## Out of scope

Licensing/trial (B1), auto-update, anything listed in BUILD_PLAN §5. (phase-13 out of scope, shared)
Every item the umbrella's table assigns to 13-1, 13-2, 13-4 or 13-5; an S9 remedy is `13-1b`.

## Acceptance criteria — automated

- [ ] Full CI matrix green; nightly validation green (no regression). (phase-13 C1, umbrella shared: for this
      sub-phase's PR)
- [ ] Robustness test: cross-architecture ≤ −100 dBFS residual. (phase-13 C3, clause "including
      cross-architecture ≤ −100 dBFS residual", with the subject it needs to stand alone (G2); the clause
      "Robustness tests above pass" in 13-4)

## Listening / manual checklist (Maisara)

None. (All of phase-13's listening and manual items are in 13-5.)

## Contractor review focus

None of phase-13's contractor review focus clauses is assigned here (umbrella coverage table).

## Risks

The umbrella's risks (phase-13 K1–K3) apply.

## Notes from the split

- 13-3 runs S9 first, before C3's residual and S8 are recorded. A miss opens `13-1b`; 13-3's records are taken after
  `13-1b` lands. (D-PS4 instruction 2; S9 = scope 4 here, S8 = scope 3 here)
- If `13-1b` changes rebuild time or diffuse-solve time, 13-2's i₀ sentence, its N_cap rule and S13's W_max / n*_max
  re-check re-run before 13-3's records are taken. (D-PS4 instruction 3, final wording, Addendum)
- S13's 'release machines', in 13-2, and S9, in 13-3, need Apple-silicon hardware; Maisara provides it (follow-up).
  (D-PS4 instruction 6, final wording, Addendum)

## Definition of done

All automated criteria green (phase-13 definition of done, clause 1, shared: this sub-phase's criteria); status
row 13-3 `done` (CLAUDE.md rule 6; status row 13 stays on the umbrella). CLAUDE.md rules apply: one sub-phase per
session; if it can't be finished in two sessions, split the remainder into `phase-13-3b.md`.
