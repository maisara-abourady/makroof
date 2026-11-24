<!-- Saved by the orchestrator from seat 7's report, 2026-11-22. -->

SEAT 7, ROUND 2 (phase 07c-2). These are answers to the decider's §6 questions for this seat, plus my ratings on D-W3. My round-1 position is not restated.

**Overall:** U2 is acceptable as a record, but must not become the term that sets W. The slip to 07c-2b is acceptable if Phase 08's goldens are blocked behind it. TSP stimuli stay local-only. On D-W3, H-2 is my preferred option.

## (a) U2 (Seat 8's bounce cap) as a term in W-C1′ and W-C2

**My reading.** What the bounce costs is waiting time; no host fails. The VST3 API and six host manuals treat a slow offline render as allowed behaviour, with no timeout (R14–R20). REAPER and Studio One are not verified. So I still put no ratio cap of my own on W. What I can accept is U2 as written, as long as it is a ceiling that does not bind.

**Projection, so U2 can be rated (*derived*, my arithmetic, Seat 8 re-projects):**
- The 48 kHz clause (≤ 1 × real time) has wide margin: 0.22–0.42 × on file (F7).
- The "+0.25 ×" clause at layout 4 s = 1: local pool medians are 123 ms at ×1 and 778 ms at ×8 for the default placement (T1). That is 36 × 0.655 s ≈ 23.6 s over 180 s ≈ +0.13 ×.
- At ×6, with the capped-set maximum of 810 ms (file 8 §2), it is 36 × about 0.69 s ≈ +0.14 ×.
- So U2 is projected not to bind for m ≤ 8. CI per scene is about equal to local (the corrected H-2).

| U2 as | now | later | reason |
|---|---|---|---|
| a recorded ceiling that does not bind for m ≤ 8 | 0 | 1 | It costs nothing now. The debt is a sentence in public wording that states the 96 kHz ratio. |
| the binding term below m\* = 6 | 1 | 2 | It would trade a measured accuracy shortfall at a reported class for a wait that hosts tolerate. That shortfall then has to be disclosed in public. |

**Condition:** U2 may bind only above m\*. If M9 shows it binding at or below 6, the bounce ratio becomes a disclosed figure, not a cap. That keeps my rating at 1.

## (b) Sequencing without the backstop: slip to 07c-2b, still before release

**Rating: 1 now / 1 later, on two conditions.**
1. **Phase 08 waits for 07c-2b.** BUILD_PLAN §0 must record that 08-x goldens are frozen only after 07c-2 (or 07c-2b) is `done`. Today this holds only because 08-1…08-4 are "not started". If it is not written down, the probable failure is two golden rounds: about 4 CI runs each (the 07c-1b S2 precedent), so about 8 manual runs in all. On that failure I rate later 2.
2. **The listening session is booked.** 07c-2b opens with the ABX and the class (c) round, and the listening session is a dated item in the session brief, not an open-ended wait. If 07c-2b cannot fit it either, the item becomes a NEEDS MAISARA scheduling question; a seat does not decide a person's time.

**Why the slip is acceptable now.** Nothing has been released, so no customer state changes (V4 does not apply). The cost is one split file. Moving the W change past the first release is a different matter: it would need versioned state, and I would rate that 3.

## (c) McGill TSP: local-only or the public listening pack?

**Local-only: 0 / 0. Prefer.**
- BSD covers copyright only. By analogy with CC BY §2(b)(1), personality rights in a voice are not licensed (R38), and TSP gives no consent statement (R35).
- Putting that voice in a public artifact of a commercial product's repository exposes us to a complaint. It would arrive as a complaint, not as a test failure (V4).
- Local-only costs the testing record nothing. Anyone can rebuild bit-identical stimuli if we publish:
  - the build script;
  - our own SHA-256 of `48k.zip` and of the excerpt;
  - the seed;
  - the sealed answer file.

**Public pack with the BSD notice: 1 / 2.**
- Removing it later means deleting artifacts and publishing a correction. A consent problem, if it comes, comes after the audio has been distributed.

**What lifts it to 1 / 1:** a written consent or redistribution statement from the corpus author (P. Kabal), or the archive's own files, recorded in the THIRD_PARTY row. Then the pack may carry the stimuli with the BSD notice and the product listed nowhere as endorsed. The researcher can ask; Maisara or a lawyer can rule on it.

## (d) D-W3: the ISM update held behind a running solve

**Reading.** Condition 4 of 07c-1 holds only after a quiet spell, so this is a 07c-1 defect found in 07c-2. It decides W, and W decides the golden round. My cue: work borrowed from a later phase.

**Routing.** Sending the defect to 07d or 10-1 means pinning W now under U3 and pinning it again after the fix. That is two golden rounds, and the second could fall after release. **I cannot live with routing past the golden round (later 3).** The fix must land in 07c-2 or 07c-2b, before the golden round.

| option | now | later | reason |
|---|---|---|---|
| H-0 | 1 | 2 | No code cost now. It ships a known accuracy shortfall at `layout4_s1/listener_corner` e1 (0.375 dB, U raised). Raising W later is the second round, or a versioned change after release. |
| H-1 | 1 | 2 | Moderate code. If continuous automation starves every solve, producers report "the room doesn't update", which reaches us as support tickets, not test failures (R3). |
| H-2 | 2 | 0 | **Prefer.** It meets condition 4 literally and adds no debt, but it is the largest threading change and probably forces 07c-2b. |
| H-3 | 1 | 2 | No code. We lose the right to say "updates within 700 ms" in public. The hold comes back at Phase 08's binaural ISM cost (Seat 4). It also touches an Expert-owned default (Q4, AQ4). |

**Conditions of acceptance.**
- **H-2 → 1 now:** scheduled as the first work of 07c-2b, ahead of the golden round. Seat 5's TSan and `[pipeline]` gates are part of its acceptance.
- **H-1 → 1 later:** M7b shows that solves finish under the AX38 (iv) automation patterns, and the "settling" state during automation is visible to the user (Seat 6).
- **H-0 → 1 later:** the shortfall is recorded in AX41's flags and in the public testing record.
- **H-3 → 1 later:** the board's DECISION on AQ4 is cited, and public copy never states an update interval.

**Hand-offs.**
- Seat 5: the H-2 topology and real-time safety.
- Seat 3: time variance under H-1.
- Seat 6: what the user sees during automation.
- Seat 4: Phase 08 build cost under U3.
- Decider: the BUILD_PLAN §0 dependency in (b).
- Researcher: TSP consent.

**Premortem.** H-0 or H-1 ships, a producer's long room automation sounds stale or stays approximate, and a forum thread is the first to notice. The fix then costs a second golden round, or a versioned change after release.
