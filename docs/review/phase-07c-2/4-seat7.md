<!-- Saved by the orchestrator from seat 7's report, 2026-11-22. -->

SEAT 7 POSITION. Phase 07c-2, round 1. D-W1 and D-W2. The corpus is present (dossier: SOURCE_COMMIT c1b171f). I state no acoustic fact of my own.

# D-W1: the W_max value and the keyless path

**Reading.** We are choosing the shipped W_max. The choice triggers one golden round, sets the release timing (condition 1) and fixes what we may say in public about load, settle and bounce in large rooms.
- Cues it hits: a deal change for saved states (S6/V4; pre-release, so nobody is affected yet); visible durability (S8, AI2); the cost of a second CI round (cost floor).

**Two facts drive my ratings.**
1. **The gated cubes saturate.** Low-α s0.3 stops growing from ×2 and flutter from ×4 (F3 finding 2). Under K-a the 14 × worst figure rises by at most +0.37 s / +5.6 s (T5).
   - Above ×4, W changes only the s = 1 cube, layouts 4/5 and the D5 fixtures that are capped or work-stopped.
   - The macOS PR #33 run is already at 30.50 s at today's pin (T5, F13), whatever W we pick.
2. **W-4 and W-6 cannot be met as written.**
   - W-4: at 96 kHz the 8-instance settled time is already 9.7–13.3 s at the pin (F6(b)). It includes about 1.1–1.4 s of synthesis per instance (F6). No W at or above (A) gives ≤ 10 s on Linux or macOS, and going below (A) is out of bounds (condition 3).
   - W-6: the both-near cases stay U = 1 and keep SE at 0.5–1.2 dB at every W (finding 5).
   - If either is left binding, the matter stalls and timing slips.

| option | now | later | reason |
|---|---|---|---|
| W-1 | 1 | 1 | One sentence we can defend. Its Table 15.1 basis is "by extension" only (R29: conditions differ), so public wording must not cite it as a standard. |
| W-2 | 1 | 2 | About twice W-1. Restore on the s = 1 cube passes 30 s at about ×8 on Linux and macOS (T5). A user meets a 40 s load as a complaint, not as a test result. |
| W-3 | 1 | 1 | The basis rests on core counts (R21: Steam gamers, ≥ 4 cores in 97 % of machines; no survey of DAW users). The behaviour is still deterministic, because W is a work count. |
| W-4 | 2 | 2 | Infeasible at or above (A) (fact 2). As a binding term it forces another round. |
| W-5 | 1 | 1 | **Prefer**, with my bounce term below. |
| W-6 | 1 | 2 | Infeasible for the both-near cases (fact 2). Accepted as written, it delays the golden round. |

**My bounce term for W-5.**
- At 96 kHz the bounce already runs at 0.76–1.36 × real time at the pin (F7). At ×16 the projection adds about +0.27 × (F7, linear projection).
- The VST3 API and the manuals of six hosts treat a slow offline render as a wait, not a fault (R14–R20). REAPER and Studio One are unverified.
- So the term is: no host failure, and the public wording states the ratio. No ratio cap from my seat.

**Conditions of acceptance.**
- **W-4 → 1:** restate it as the solve's share of settled time, or at 48 kHz (5.2–6.0 s today, F6(b)).
- **W-6 → 1:** restrict it to the classes W can fix. The both-near cases go on record as a known limitation (U flag); their cause is variance, not W.
- **W-2 → 1:** only if the 30 s restore bound covers the ungated s = 1 cube.

**Keyless path.**
- **K-a: 1 / 1.** It is what the code already does (F9: one `DiffuseLimits`). It keeps a single class, and the restore cost is bounded by saturation.
- **K-b: 1 / 2.** It adds a statistical interim gated on a human ABX. If the ABX slips, the golden round slips.
- **K-c:** cannot rate; it is unspecified.
- **Sequencing.** I accept "value now, keyless path after the ABX, one golden round after both", on one condition: if the ABX has not run by an agreed point in 07c-2, K-a ships by default. Without that condition I rate the sequencing later 2, because a person's listening session would hold the release.

**Debt.**
- One golden round costs about what the 07c-1b S2 exercise cost: ≥ 3 green manual CI runs (43389296112, 43402114873, 43412038058) plus at least one run to read the three OS fingerprint hashes (F10). That is about 4 CI runs. [Hyp on founder hours]
- A second round doubles that.
- After the first release, any W change alters the tail level of saved projects. That is a retroactive deal change (V4): it would need versioned state and has to be disclosed.
- **Evidence that could overturn this:** the 07c-2 CI per-OS sweep (F3 so far is Linux-only and local), then 08-4 and 12-2.

**Companion items.**
- (b) Not my matter, but I flag it: every public or plan figure for ns per evaluation must use the per-scene basis. The double count (F1) goes in the change log; an honest testing record is a trust deposit (AI2).
- (c) S2 form: accept. Cost about 3 runs.
- (d) Seat 2's matter. Wording point: the changelog must not say "raising W only refines". That is false for work-stopped fixtures (F11).
- (e) **Keep v2.** It is pre-release, so no customer state exists. A v3 bump adds fixtures we must keep loading forever. The v2 fixtures already load keyless without a warning (F10).
- (f) Confirm. Landing before the Phase 08 goldens freeze keeps this to one round.
- (g) Bookkeeping: `listed` is false on main and true on HEAD (F13). Record it.

**Public wording I require (Seat 1 holds the realism gate).**
- Settle and bounce times per OS, measured on the CI hardware with the core count stated.
- "Very large, very absorbent rooms can take several seconds to settle."
- "96 kHz offline bounces of such rooms can run slower than real time."
- Never "instant", and no restore-time claim on macOS while the 30.50 s case stands.

**Premortem.** W-6 or W-4 stays binding, so the round repeats, 07c-2 slips into Phase 08's goldens, and the contractor notices the second regeneration first.

# D-W2: the AX47 self-ABX design

**Reading.** We are fixing the ABX design before the run. Cues: the listener's hours are a person's scarcest input; the speech licence in a public repo of a commercial product (V6; my earlier 07c-1b file 7); and what a "not detected" record lets us say in public (Seat 1's Tier A rule; marketing restraint, criterion 1).

**Listener time.** BS.1116-3 sets 10–15 trials per session and 20–30 min sessions, with familiarization mandatory (R4).
- X-1: 32 trials, plus 16 for L4, is 48 trials, about 4 sessions.
- X-2 at k = 3: 96 + 16 = 112 trials, about 8 sessions.

| option | now | later | reason |
|---|---|---|---|
| X-1 | 1 | 2 | Uncorrected family-wise error 0.075 (R §2a). A false detection triggers the 0.5 dB reversal, which tightens the bound and can force another golden round. |
| X-2 | 2 | 1 | About 2.3× the listener time. At 13/16 the power is 0.405 at p = 0.75. |
| X-3 | 1 | 1 | Family-wise error 0.038, and it stops early. |
| X-4 | 2 | 1 | Needs a board DECISION amending AX47, so one more round, plus new tooling. Trial count varies. |
| X-5 | 1 | 1 | **Prefer**, on X-3. |

**Conditions of acceptance.**
- **X-1 → 1:** via X-5 (13/16 per stimulus).
- **X-2 → 1:** k = 2 sizes.
- **X-4 → 1:** only if AX47 is amended in this round.

**Sub-items in my mandate.**
- **Speech source**
  - Choose LibriSpeech (CC BY 4.0) or its LibriVox original (public domain in the US only; R23, R24). Add a THIRD_PARTY row with attribution.
  - The CC BY legal code is unread: the researcher should read it before commit.
  - Excluded:
    - EARS (non-commercial, R27): our product is commercial.
    - SQAM (R&D use only; redistribution not addressed, R25): local use only.
    - P.501 and ARU: terms unknown.
- **Distribution**
  - Do not commit audio, and do not fetch the 337 MB archive in CI.
  - Take one utterance of ≤ 10 s and mirror it as the project's own release asset, pinned by SHA-256 we compute ourselves (upstream gives only MD5).
  - Stimuli are built locally. If they go into the listening pack, an attribution file goes with them.
- **Blind procedure.** Use a script that writes a sealed answer file. Commit the seed, the stimulus hashes and the answers; that is a deposit to the public testing record.
- **Record wording.**
  - "Not detected" is written only with an audible anchor step in the design (BS.1116 §6; the anchor step size is Seat 1's call). Otherwise the record says "inconclusive".
  - The record always carries the listener count (1) and the power (0.63 at p = 0.75; it misses a real effect 37 % of the time).
  - Public copy never says "inaudible".

**Debt.**
- A wrong design is challenged in the class (c) round, and a re-run costs another person-session of about 4 sessions.
- If omni or stereo results do not carry over to binaural, 08-3 repeats the test (Seat 4).
- In Phase 13 the wording is fixed by what this record licenses.

**Hand-offs.**
- Seat 1: anchor size, paradigm, and the fact that LibriSpeech is not anechoic.
- Seat 4: the chain.
- Researcher: the CC BY legal code; consent terms for LibriVox speakers [Hyp: voice rights].
- Lawyer: only if a voice reaches a marketing asset.

**Premortem.** X-1 gives a 7.5 % false detection, the bound tightens to 0.5 dB, another W round follows, and the interrogator notices first.
