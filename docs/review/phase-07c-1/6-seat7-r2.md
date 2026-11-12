# 6 — Seat 7, round 2 (phase 07c-1, on decider file 5)

Saved verbatim by the orchestrator from the agent's report, 2026-11-12. Round-2 questions: file 5 §7.

SEAT 7, round 2 (phase 07c-1). Only what changed.

1. **C5′ (AX47): now 1 / later 1.** Now 1: it adds a refusal path and its tests (decider file 5, debt register S7). Later 1: every recorded step feeds the public testing record and support triage (AI2), so I can live with it.

2. **Saved format carries both key parts now; policy "any mismatch: saved E_b not used"; the board decides the engine-mismatch policy before the first post-release build that changes E:** this **meets my condition**. **A1 under it: now 1 / later 1.**
   - **Why it meets it:** before release no customer project exists, so the policy has no effect on anyone (your L3). The format is where the trust cost would have been, and it is fixed now.
   - **One proviso, or later goes back to 3:** the CI fingerprint test in AX48 already fails when E_b changes without a version bump. After the first release, that failure must also block the build until the board's decision exists. Bumping the version id alone must not clear it. Without that block, a post-release build could change E under the "not used" policy and move saved mixes. That is the V4 failure and my condition 1.
   - **Where to record it:** one line in phase-13-1 and 13-5 next to "the board decides AX48's engine-mismatch policy…".