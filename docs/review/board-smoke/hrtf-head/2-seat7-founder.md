# D1 (dry run) — Seat 7, Keel, the indie deep-tech founder (2026-11-09)

Method: the registered `seat7-founder` agent, briefed with B7 of `1-decider-convene.md`; no dossier yet (licence facts `[Hyp]`). Verbatim.

---

SEAT 7 POSITION

**Fixed fact that fell.** `docs/PRD.md` "Business model & licensing" sets a subscription at $10–20/month with a year-one target under 500 subscribers, and FR-LIC-3 keeps saved instances rendering after lapse. My persona assumed a perpetual price; the PRD wins. Consequences for D1: the year-one gross ceiling is 500 × $20 = $10k/month by the PRD's own numbers (the N1 base rate says far less), so my tolerance for any licence that costs money, royalties or legal hours is near zero; and FR-LIC-3 + NFR-6 ("restores the render exactly") make the embedded head part of the deal with every subscriber, which is the centre of my "later" ratings.

1. **Reading.** Which dummy-head set becomes `generic-v1`, judged for licence risk, compliance cost, name exposure, fallback/swap schedule cost and recurring obligations. Cues triggered: "a deal is being changed for existing customers" (the head behind a frozen `hrtfId` is a future retroactive change, S6); "the founder's reasoning is not public" (the attribution file and testing record are visible-durability assets, criterion 7); "cost it against doing nothing per sale" (C4).

2. **Ranking** (every licence fact is `[Hyp]` until the dossier; the ranking is conditional on R1).
- (a) SADIE II KU100: *prefer*. Base rate: the one comparable tool in the corpus ships KU100 (Zotter & Frank, "IEM Plugin Suite" table row and Ch. 4 BinauralDecoder note); the book itself distributes SADIE subject-1 files in its tutorials (Zotter & Frank Fig. 1.14 note), weak evidence of a permissive record. "Same head as the IEM suite" is a sentence the founder can put in the testing record without a realism claim.
- (b) SADIE II KEMAR: *can live with*. Same record, so presumably the same licence `[Hyp]`; different trademark holder for the name.
- (c) MIT KEMAR: *can live with as fallback only*. A 1994 set whose terms, if they are an informal "use freely" note rather than a named licence `[Hyp]`, give a lawyer little to bless; 44.1 kHz source and −40° floor (Begault Ch. 4) make it the option most likely to force converter and renderer special cases (Seats 2/3).
- (d) TH Köln KU100: *can live with* if its licence is attribution-only; *cannot live with* if it is share-alike `[Hyp: my recollection is that the TH Köln sets carry a CC BY-SA licence; researcher R1 must verify first]`. The project's own precedent is that BY-SA material (BRAS) stays validation-only and is never shipped (`docs/THIRD_PARTY.md`, BRAS row). A BY-SA-derived blob inside a paid closed plugin is a recurring obligation and a litigation exposure one founder cannot carry.
- Dataset-agnostic converter and header (the condition): *prefer*, and I ask the decider to make it part of whatever is chosen.
- Any option whose terms are non-commercial or unclear: *cannot live with* (phase-08 scope 1 says the same).

3. **Tension now.**
- (a) `1`: one licence read, one attribution text in `resources/hrtf/LICENSE-generic-v1.txt`, `docs/THIRD_PARTY.md` and the Phase 13 product notices already planned for JUCE/PFFFT/nlohmann. About an hour of founder time, €0.
- (b) `1`: as (a).
- (c) `1` if its terms are clear, `3` if a lawyer calls a 1994 informal statement "unclear" (scope 1 blocks the phase; headphone mode, the PRD's headline mode, slips by an unknown number of sessions).
- (d) `1` if BY-style, `3` if BY-SA or NC.
- Agnostic condition `1`: roughly half a session of converter work (header fields: set identity, DOI, sample rate, grid, EQ state, converter version).
- Naming in marketing: `2` for any option. Nominative use in attribution is required and low-exposure; "renders through a Neumann KU100" in copy is both a trademark exposure (lawyer) and a realism claim Seat 1 forbids before a Tier A result. Trust label: withdrawal if it implies endorsement.

4. **Tension later (the debt).** The same debt for all four, rated `2`, lowered to `1` by the condition: `hrtfId` is a schema `const` and NFR-6/FR-LIC-3 promise that a saved project renders exactly as saved. The day the data behind "generic-v1" is replaced, every subscriber's saved project changes sound: that is V4's retroactive change and P11's reset without a bridge, noticed by a customer reopening a session. So the head chosen in Phase 08 is frozen for the life of v1 projects; a swap after the first paid release means a new id (`generic-v2`), v1 data retained (binary size doubles: Seat 5), and a migration note. Cost to undo before Phase 13: a parameter change plus goldens and listening pack for three scenes (one session) if the converter is agnostic; a phase of rework if the set's grid or sample rate was hard-coded. Cost to undo after Phase 13: a second embedded set forever. Evidence that could overturn arrives at: the dossier (R1–R3), the Phase 08 ITD/continuity gates on the real files, Maisara's phase-08 listening checklist, the Phase 13 licence review before first paid release, and B4 (Phase 18 SOFA import, which uses the same converter). Specific extras: (c) `2` for its data vintage and a download URL at `sound.media.mit.edu` (Vorländer §16.1.2) whose liveness AC 2's round-trip test depends on in CI (the `.bin` is committed, the source is not); (d) `3` later if BY-SA, because every converter change re-triggers the share-alike question.

5. **Evidence.**
- Year-one scale and subscription model: `docs/PRD.md` "Target users" table and "Business model & licensing" `[Observed]`.
- Typical first-launch revenue: N1 `[Self-report: incident]`.
- Compliance cost per sale as the test for any channel or obligation: C4 `[Self-report: incident, pre-outcome]`.
- Retroactive change draws the backlash: V4 `[Self-report: incident]`; reset without a bridge: P11 `[Self-report: incident]`.
- BY-SA kept out of the shipped product: `docs/THIRD_PARTY.md` BRAS row `[Observed]`.
- KU100 as the comparable tool's head: Zotter & Frank, IEM Plugin Suite table row; Ch. 4 BinauralDecoder note (corpus) `[Observed]`.
- MIT KEMAR description and URL: Begault Ch. 4 "Dummy heads"; Vorländer §16.1.2 (corpus). No licence text in the corpus.
- Visible testing record as the answer to the 2026 suspicion scan: AI1, AI2 `[Peer-report, 2026, no outcomes]`.
- All licence terms, trademark positions and the TH Köln BY-SA recollection: `[Hyp]`. Researcher: R1 (licence text per set, derived-data redistribution, attribution wording), R2 (naming), and one addition: whether each record names a persistent DOI/mirror so AC 2 does not depend on one university URL.

6. **Conditions of acceptance.**
- Any option, later `2` → `1`: the agnostic header records set identity, record version/DOI, sample rate, grid and EQ state; the plan states in writing (an AX row) that data behind a released `hrtfId` is never replaced; a different head means a new id with the old data retained.
- (c) now `3` → `1`: a named licence or a written permission from the record's owner, filed in `LICENSE-generic-v1.txt`.
- (d) now `3` → `1`: the record is attribution-only (not SA, not NC), verified by the researcher and read by the founder on the official site.
- Naming `2` → `0`: the head is named only in the attribution file, `THIRD_PARTY.md` and the public testing record, never in UI or marketing copy, pending a lawyer's view on nominative use.

7. **Hand-offs.** Licence text and trademark use: a lawyer (researcher R1/R2 first). Audibility of KU100 vs KEMAR: Seat 1. Whether the head is ever named in the UI: Seat 6. Binary size of a retained v1 set and the CI dependency on a live source URL: Seat 5. EQ state and ear-canal position: Seat 4.

8. **Premortem.** The board picks the set whose licence "looked fine", the data behind `generic-v1` has to be swapped after the first paid release, and the first person to notice is a subscriber whose saved project opens sounding different, in a forum thread about a one-person company that changed the deal.
