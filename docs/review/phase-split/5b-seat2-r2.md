# Seat 2 (engine architect), round 2 — D-PS4 (a+5) only (2026-11-10)

Saved by the orchestrator from the seat's report.

**Rating (a+5): prefer. Now 0, later 1** (the decider's (rc) 0/0 understates the future).
- Now 0: all of 13-2 is under my row ("simulator compute and recompute time"): S13 (W_max, n*_max re-check), C2
  sentence 2 (N_cap rule), C2 sentence 3 (i₀); every output change from 13-1 and 13-2 lands before 13-3's
  cross-architecture residual (my round-1 condition).
- Later 1: if `13-1b` reopens optimisation after 13-2, rebuild time can move; W_max (restore watchdog less the D-H1
  margin), n*_max (25 ms of the W1 target, phase-13 S13) and N_cap ("with time freed by optimisation", C2) rest on
  rebuild and solve time as i₀ does. Undo: a re-run, possibly one golden round. Evidence: 13-3's S9 result.

**13-2 deserves a session:** AX22 records "cap limits accuracy", up to 39.7 jnd (BUILD_PLAN line 122), so the i₀
re-derivation is a real check; any S13 change is an output change (golden round, §6 row before release); an N_cap raise
goes through `/fix-plan` with an interrogator check. One subject.

**Condition (keeps later at 1, else 2):** plan-editor instruction 3 reads: "If `13-1b` changes rebuild time or
diffuse-solve time, 13-2's i₀ sentence, its N_cap rule and S13's W_max / n*_max re-check re-run before 13-3's records
are taken." As written it covers i₀ only; a stale W_max could reach 13-3's residual and the release.

**Hand-offs:** 13-2 states its dependency on 07c `done` or S13's versioning fallback recorded (header H already
carries it). Maisara: Apple-silicon hardware is needed by 13-2 as well as 13-3.
