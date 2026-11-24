# 39: Seat 7 sets the (a0) runner cap (M3-H)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 7 POSITION (follow-up on M3-H: the (a0) runner-time cap). I only read files and changed none. The orchestrator should save this as /home/user/makroof/docs/review/phase-07c-2b/39-seat7.md.

**1. Reading.** I am asked to set the cap on total runner hours for (a0) and to say what it costs. Cues from my persona: the cost floor sits below the worst month (Strategy E), and the founder's hour is the scarcest input.

**2. Ranking.**
- **Prefer:** H4+G as Seat 5 wrote it, with **the cap at 24 runner-hours (1,440 min) of predicted time for all of (a0)**. The 24 h covers the pilot (4 × 16 M, about 3.3 min in total) and all 4 runs at both radii, summed over shards. Two conditions go with it:
  - **Standard 2-core hosted runners only.** Larger runners are billed even on public repos.
  - **A hard spend ceiling of 36 runner-hours.** It is the 24 h cap plus Seat 5's one re-shard rerun. Reaching it counts as "over cap".
- **Can live with:** the same text with no cap but a 36 h ceiling. This is weaker because the SE fallback would trigger only on a failure, not on a prediction.
- **Cannot live with:** no cap at all. The worst case is open-ended (below), and it lands on the minutes quota that the regular CI shares.

**3. Arithmetic (redone from F9, F11 and 39-seat5).** The rate is 3.1 µs per particle.
- **Window-k gate, mid case** (about ×20 annihilation, a [Hyp] between ×6.6 and ×77, plus ×2 for the floor):
  - 0.05 m: 59 M × 40 ≈ 2.4 G particles, about 2 h per run.
  - 0.025 m: about 8 h per run.
  - Total: 2×2 + 2×8 ≈ **20 h**, which fits the cap.
- **Window-k gate, worst case** (×77 × 2):
  - 0.05 m: about 9 G particles, about 7.8 h per run.
  - 0.025 m: about 31 h per run.
  - Total: **about 78 h**, which is over the cap.
- **The fallback fits.** The SE ≤ 0.5 dB fallback needs window k ≥ 76, which is 684/76 ≈ 9× fewer particles, so the worst case drops to about **8.7 h**. The cap therefore never leaves (a0) without at least the fallback verdict.

**4. What it costs** (repo plan and visibility unverified, so all of this is [Hyp]):
- **Money:** 1,440 min at about $0.008/min on Linux comes to about $12. At the 36 h ceiling it is about $17. On a public repo, standard runners cost $0.
- **Quota:** this is the real cost. If the repo is private on Free (2,000 min/month), the cap uses about 72 % of one month's minutes, and PR CI on three OSes has to share the rest. macOS minutes count ×10, but (a0) runs on Linux only.
  - **Condition:** dispatch (a0) only when the remaining monthly quota is at least the cap plus one full PR CI run.
  - Keep the spending limit at its current value. If a shard hits the quota it fails, and that counts as over cap. Nobody raises the limit to finish (a0).
- **Maisara's time:** zero. The session dispatches the job, monitors it and merges the shards. She is involved only if someone proposes raising a spending limit, which only a person can do. That would be NEEDS MAISARA, and I advise against it.
- **Wall clock:** shards run in parallel (Free allows about 20 concurrent jobs, [Hyp]), so 24 runner-hours is roughly 4 to 6 h of elapsed time.

**5. Tension (H4+G with the 24 h cap): now 1, later 1.**
- **Now:** about $12, or up to 72 % of one month's quota on a private Free repo, all inside my tolerance.
- **Later:** every bump of the numpy or Python pin reruns (a0), at up to 24 h of quota each time. Seat 5 already lists this. The pilot's k_pilot is what could overturn the sizing. If the predicted total exceeds 24 h, bands fall to the fallback; that is the cap working as intended, not a failure.
- **Without the cap:** now 2 (an unbounded draw on a shared quota), later 3 (each pin bump could cost up to 78 h).

**6. Evidence.**
- F9 (annihilation factors ×6.6 to ×77, ×2 near the floor), F11 (59 M for window k 684 in W1 at 0.05 m, ×4 at 0.025 m, 49 s per 16 M) and 39-seat5 (SE fallback at k ≥ 76).
- The ×20 mid case is [Hyp].
- All GitHub figures are [Hyp]. **Researcher to verify:** the repo's visibility and plan, its monthly minutes quota and current usage, the Linux per-minute rate in 2026, the 6 h job limit and the concurrent-job limit.

**7. Conditions.** No option I prefer is rated 2 or more. For the no-cap variant, adding the 24 h cap and the 36 h ceiling brings it from 2/3 down to 1/1.

**8. Hand-offs.**
- Seat 5: the predicted total must be computed from the measured pilot rate before any full shard is dispatched.
- Seat 1: what an "SE ≤ 0.5 dB only" band may be claimed as.

**9. Premortem.** If there is no cap, a 0.025 m run at the worst case drains the month's quota mid-phase. The next PR's CI then queues or fails on minutes, and Seat 5's pipeline is the first to notice.
