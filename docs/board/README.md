# The board

Nine subject-matter seats, built as ideal-performer personas under the Expert Modelling Directive
(second edition) on 9 November 2026, sit behind the project's decision loop. Each seat is its own
advocate: it argues its mandate's interest when a subject matter touches it. The **decider** convenes
the seats a subject matter requires and decides at the point of minimum tension among all nine, now
and in the future; the **interrogator** pushes back on the decider; the **researcher** equips the
decider with external evidence. There is no advocate agent. The loop is run by `/fix-plan`
(`.claude/commands/fix-plan.md`); the roles are defined in `.claude/agents/`.

## Files

| Seat | Persona (audit trail, verbatim as uploaded) | Agent (generated) | Name in the persona |
|---|---|---|---|
| 1 | `seat-1-limen-the-perceptual-gatekeeper.md` | `.claude/agents/seat1-perceptual-gatekeeper.md` | Limen |
| 2 | `seat-2-scene-to-response-architect.md` | `.claude/agents/seat2-engine-architect.md` | the scene-to-response architect |
| 3 | `seat-3-the-reverb-renderer.md` | `.claude/agents/seat3-reverb-renderer.md` | the reverb renderer |
| 4 | `seat-4-the-chain-keeper.md` | `.claude/agents/seat4-chain-keeper.md` | the chain keeper |
| 5 | `seat-5-the-deadline-keeper.md` | `.claude/agents/seat5-deadline-keeper.md` | the deadline keeper |
| 6 | `seat-6-the-canvas-designer.md` | `.claude/agents/seat6-canvas-designer.md` | the canvas designer |
| 7 | `seat-7-keel-the-indie-deep-tech-founder.md` | `.claude/agents/seat7-founder.md` | Keel |
| 8 | `seat-8-vantage-the-spatial-storyteller.md` | `.claude/agents/seat8-storyteller.md` | Vantage |
| 9 | `seat-9-the-audible-room.md` (+ `seat-9-build-log.md`) | `.claude/agents/seat9-room-acoustician.md` | the audible room |

Also here: `board.md`, the slate the personas were built from ("Spatial Scene VST: The Board of
Experts to Model"; its §1 is the accomplishment every seat shares, used as the stand-in validity map
where a persona says so), and `seat-protocol.md`, the protocol every seat follows in a convening.

**Generating the agents.** An agent file is the shared protocol plus the persona's sections 0 to 18
(the runnable part; sections 19 and 20 and the appendices are the audit trail and stay here, as the
personas themselves instruct). The persona files are never edited. After changing a persona, the
protocol or the seat table:

```bash
python3 .claude/board/build_agents.py            # write the nine agent files
python3 .claude/board/build_agents.py --check    # exit 1 if any is stale
```

`docs/board/` is inert for the CI fingerprint (`tools/ci/ci_fingerprint.py`): nothing in `src/`,
`tests/`, `tools/` or the workflows reads it, and the generator lives under `.claude/` for the same
reason. A new agent type may not be listed by the Agent tool at once (ledger, phase-07 row 1191; on
2026-11-09 the nine seat types were picked up mid-session, but not immediately): try the type first, and
if it is not found a `general-purpose` worker given the file verbatim stands in, saying so in its output.

## Convening table

The decider uses this table to fill its nine-row convening table for every subject matter: a seat is
**convened** when the matter touches any item in its row; otherwise it is recorded **not required**
with the reason. When in doubt, convene: a seat's `NOT MY MATTER` answer is cheap. The interrogator
checks every "not required" row against this table. Each row is a compression of the persona's §18
(scope and limits); the persona wins where they differ.

| Seat | Convene when the subject matter touches | Hands off to |
|---|---|---|
| 1 Perceptual gatekeeper | what the target listener can hear or prefers: audibility of a detail, parameter or error; JNDs and the conditions they hold under; which bar applies (plausibility, authenticity, preference); blind-test paradigm, listeners, signal, strictness, sample size; keep/cut/test of a detail; acceptance tests for other seats; any claim of realism, plausibility or preference, including marketing wording | listening and panels (a human); which controls to expose (6) |
| 2 Engine architect | how geometry and materials become a room response: GA/wave/hybrid and the Schroeder-frequency split; image-source order; scattering; diffraction; late-tail statistics; material words to coefficient ranges; validation against measured rooms (BRAS, round robins, circularity); the representation handed to the renderer; simulator compute and recompute time; claims of physical accuracy | rendering smoothness (3); threading and hosts (5); controls (6); delivery (4); audibility (1) |
| 3 Reverb renderer | turning a response into audio at the listener: FDN/convolution/hybrid architecture; decay matching; early-reflection rendering; time variance under motion and automation (crossfades, zipper, clicks, metallic tails); coloration; channel spreading; per-instance CPU; listening validation of a rendering design | externalisation, HRTF, height (4); thread topology and host matrix (5); which controls (6); pricing (7); the response and where its physics stops (2) |
| 4 Chain keeper | how the render reaches the listener: binaural architecture; HRTF dataset choice and licence; headphone compensation; externalisation; head tracking and latency; loudspeaker decoding and layouts; Ambisonics order per IR segment; object and scene export; cross-format loudness and timbre parity; the listening tests for these | the format bet and pricing (7); user-facing controls (6); audio-thread integration (5); whether a detail is audible (1); licence law (a human) |
| 5 Deadline keeper | anything on or beside the audio thread: real-time safety; lock-free hand-off; worst-case callback time; threading topology; host conformance (pluginval, auval, state, automation, undo, buses, latency); offline equals real-time; framework and plugin-format choice; CI gates and sanitizers; platform transitions; review of real-time code; the host matrix | DSP design (3); the response (2); audibility (1); control model (6); pricing, AAX, Linux, support staffing (7) |
| 6 Canvas designer | anything user-facing: which controls exist and which stay hidden; names, ranges, defaults, couplings; canvas metaphor and interaction; presets and profiles; automation and motion model; DAW workflow; time-to-first-plausible-scene; competitor teardowns on these dimensions | what is audible (1); what recomputes live (2); artefact-free rendering (3); what the host allows (5); what sells (7) |
| 7 Founder | the business and the founder's capacity: price and tiers; free product; copy protection; channels and partnerships; licensing; platform order; release cadence; cost floor and runway; capital and exit; public wording and marketing claims; what one founder can sustain; schedule and complexity cost of an option | tax, registration, sanctions (an accountant); licence text (a lawyer); realism claims (1); architecture cost that changes the floor (2, 3, 5) |
| 8 Storyteller | what a producer or sound designer does with the product: whose ears the audience hears through; point of view; anchor; depth; density; contrast; transitions; translation to the listener's chain; workflow requirements; which features serve storytellers and which will never be used | thresholds and parameter values (1); rendering (3); delivery (4); pricing (7); engine (2); hosts (5) |
| 9 Room acoustician | real rooms as references: which geometry and material choices are audible at a position and by how much; early structure vs decay; occupancy; bass and seat-dip; material-library provenance and uncertainty bounds; preset validation against measured rooms; diagnosing complaints; which room and material controls are worth exposing | hearing, measuring, scale models, panels (a human); audibility ownership (1); engine (2); canvas (6) |

Seats and the roles around them, in one line each:
- the **decider** decides (minimum tension, now and later, inside the PRD's hard constraints) and answers
  for Maisara from the PRD;
- the **interrogator** pushes back (convening, tension map, future debt, facts against `docs/corpus/`, and
  the PRD reading of answers given for her);
- the **researcher** finds and verifies external evidence;
- the **plan-editor** applies verified decisions to the plan;
- the **steward** keeps the session's objectives.

Maisara has the final say: she may veto any decision after it is applied.

## Who answers Maisara's questions

Maisara, 2026-11-10: "i created it particulary to answer when you need his answer"; "If it is capable of
reasoning, my north star is the prd that drives my decision making"; and, on this rule, "Do it".

1. **The decider answers for her.** It reasons from `docs/PRD.md` the way she would, and answers every
   question the loop would otherwise stop to ask her. Examples:
   - accepting or vetoing a surviving decision;
   - choosing between options the board left open;
   - an item still contested after the interrogator's 3 rounds;
   - a product trade-off or judgement;
   - the scope or the reading of one of her earlier answers or recorded decisions, and an amendment of one
     when the PRD calls for it (as the phase-05b2 brief's questions Q1 (AX36) and Q2 (AQ10) did on
     2026-11-10);
   - an ambiguity in her words that the PRD settles;
   - a question in a phase file's "Raise with Maisara" section.

   Each answer meets these conditions:
   - It cites the PRD ids it rests on (goals, FR/NFR, out-of-scope items) and her recorded decisions.
   - It shows how each option considered serves or strains those requirements, one line per option (her
     approved wording: "name the PRD requirements it relies on … and show how each option serves them").
   - It does not lean on the board's minimum-tension ordering alone.
   - The interrogator checks its reasoning (PRD MISREAD).
   - If it amends one of her recorded decisions, its line says so:
     `AMENDS her decision of <date>: "<her words>"`.

   **Her recorded decisions** are:
   - her words, verbatim, in the session briefs;
   - the BUILD_PLAN §2/§6 rows, or parts of rows, that cite her by date.

   The other AQ/AX rows are plan defaults. A board DECISION may change them through `/fix-plan`, as before.

   **Accepting a surviving DECISION for her** is a PRD check:
   - it breaks no hard constraint;
   - no PRD goal or ranked requirement points to another surviving option.

   Each surviving option is shown against the check's PRD ids.

   **PRD open questions.** Q-ids from the PRD may be cited; their defaults are AQ rows. Answering a PRD
   open question itself stays with its owner:
   - Q1–Q10: the Spatial Audio Expert;
   - the Engineering questions: the board, as today;
   - the Product questions (Q11, Q14, Q15): case (a), because the PRD leaves them open.

   **Where questions come from.** A question that arises outside `/fix-plan` goes straight to the decider,
   run by the main session with the question and its context. Such a question might be a Raise item, a
   steward gap or a brief ambiguity. The decider's output and the interrogator's check are saved under
   `docs/review/<target>/`, as in `/fix-plan`.
2. **Applied, then reported.** An answer that survives the interrogator is applied without waiting for her.
   The session report and the PR list it under "Decided for Maisara": one plain line per answer, with its
   PRD ids, so she can veto any of them afterwards. A veto is recorded in the ledger and undone through
   `/fix-plan`.
3. **Only three things still go to her** (NEEDS MAISARA). Each comes with the decider's recommendation and its
   PRD reasoning:
   - **(a) The PRD is silent or contradicts itself** on the point, and none of her recorded decisions
     settles it. The decider names the PRD passages it searched. This case also covers a ruling after 3
     contested rounds that fails the interrogator's check.
   - **(b) The answer would change the PRD itself:** a requirement, a hard constraint or an out-of-scope
     item. The north star does not edit itself.
   - **(c) Overriding a seat's veto-grade rating.** A `3` is a seat's judgement that an option is
     unacceptable. Overruling it stays hers; she may hand it to the decider later.

   Her answer to (a) or (b) that calls for a PRD edit counts as her asking for that edit. It is applied
   through `/fix-plan` (step 4's PRD guard).

   Things only a person can do are not decisions and stay hers as before: listening checklists, accounts,
   access, payments, legal signatures. So does a gap that is not a decision and is still failing after 3
   steward rounds.
4. **Plan text that routes a question to her is read under this rule.** This covers a "Raise with Maisara"
   item, and an AX/AQ row or phase file that says something "goes to Maisara". The decider answers the
   question unless it falls in one of the three cases. Such text is not rewritten for this rule. When it
   is next edited through `/fix-plan`, it may say "the decider (for Maisara)".
