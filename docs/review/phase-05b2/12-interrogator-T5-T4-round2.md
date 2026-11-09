# Interrogator — decision mode, round 2, D-T5 and D-T4

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

## Interrogator, rebuttal round 2 (decision mode): D-T5.1–5.4 and D-T4a–c

Six of the seven decisions now stand. D-T4a gets one more narrow TENSION MISREAD: the Seat 5 cell on 4a-2G++ was carried from 4a-2G without being re-asked. Separately, the seats' late conditions (Seats 1, 7 and 9) must be written into D-T4a's text. That matters because Seats 7 and 9 tie their 1/1 to those conditions, and Seat 9 says its later rises to 2 if either of its conditions fails.

**Corpus revision:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**Read this round:**
- the decider's replies `10-decider-rebuttal-T5-T4.md` (round 2) and `11-decider-round3-T4a-T54.md` (round 3);
- the seat re-runs: `6-seat3-rerun2-T4a.md`, `6-seat6-rerun2-T4a.md`, `6-seat6-rerun3-T54.md`, `6-seat4-rerun-T4a.md`, `6-seat1-rerun-T4a.md`, `6-seat7-rerun-T4a.md`, `6-seat9-rerun-T4a.md`;
- C1 line 32, now fixed;
- `tools/acoustics/tracer.py`, which exists and is seeded; it is the shoebox tracer of Kuttruff §9.8.

Following the rebuttal rule, I rate only what is new or revised.

### Verdicts

| id | outcome | basis |
|---|---|---|
| D-T5.1 (5.1-A*) | **SURVIVES** | Corrections 04–06 are applied faithfully: the Eq. 4.24 citation is fixed with the §5.2/§2.7 split; bit-identity is now per platform with an RAII guard that also restores on a throw; the test room is asserted to produce denormals; and the text states what (ii) does and does not test. The register shows S1's 63 Hz debt as not repaid, and band-varying α as having no independent evidence (S1, S2, S4). Map unchanged: max 1, sum 14. |
| D-T5.2 (5.2-A) | **SURVIVES** | The register now has one row per seat. I checked all nine quotes against the seats' reports and they match. The over-trigger debt is honestly marked "no scheduled evidence", and the reversal condition follows from that. |
| D-T5.3 (5.3-D) | **SURVIVES** | Unchanged. |
| D-T5.4 (5.4-A*) | **SURVIVES** | Correction 16: Phase 12 uses two checks. (a) is the single-scatter floor integral, used only where every non-ground face has α = 1, as Kuttruff Eq. 4.28 requires. (b) is the seeded tracer within ±1 dB for everything else. Correction 17: the reversal now fires only on a "ghost tail" (the reference puts the energy after t_mix,e more than 60 dB below the direct sound while the rendered tail is within 60 dB). The courtyard's real reverberation no longer triggers it. Correction 18: E_target and the window sums are kept in double; 1.19e−41 is a normal double (the smallest normal double is about 2.2e−308), so FTZ leaves it alone. The inaudibility claim carries the level conditions I set. Seat 6 confirmed 1/1 on the restated check, so the map is max 1, sum 17. The C1 typo is fixed (C1 L32: "−152 dB at 500 Hz, −166 dB at 1 kHz"). |
| D-T4a (4a-2G++) | **TENSION MISREAD (narrow: S5 cell)**, with corrections | See below. |
| D-T4b (4b-2) | **SURVIVES** | Correction 27 is applied: §9 excludes only caching beyond what D-T1 needs, and D-T1 (a) includes a cached room kernel. The coupling note is applied too: if D-T1 picks a cached-kernel candidate, D-T4a (ii) and D-T4b reopen together. |
| D-T4c (4c-1C) | **SURVIVES** | Seat 2's condition is carried: there are two 100 m, 96 kHz builds, one asserted to be in the fallback and one a closed low-α cube, and the gate is checked against the larger peak. The contended-restore record and the bounce-to-real-time ratio are added, and Table 15.1's conditions are stated. Max 2 (S5 later), sum 17. Challenge 1 still waits for Maisara. Two minor items: record whether the closed cube actually stays out of the AX22 fallback, and add Seat 1's label wording (row 40). |

### D-T4a in detail

**Map check.**
- **Rated by the seat or read from its conditions, and faithful to its words:**
  - S1: 0/1, rated in its re-run.
  - S7: 1/1, rated in its re-run.
  - S9: 1/1, rated in its re-run.
  - S3: 1/1, read from conditions ("With these the rating is 1/1"); all three of Seat 3's terms are in (i) and (iv).
  - S6: 1/1, read from conditions; FIFO, the wait shown in the staleness metric and as "settling", and the records are all present.
  - S4: 1/1, read from conditions ("1/1 if the two conditions below are added"); these are (iv) and (v).
- **Sum:** 8 now + 9 later = 17. Max 1.
- **Arithmetic I re-checked:**
  - Seat 4's band: 35 − 512/48 000·1000 = 24.3 ms, and 35 − 2·10.67 = 13.7 ms. This uses Vorländer Table 15.1, head rotation 35 ms; §15.3's text gives 20 ms "as printed".
  - Seat 7's figures: 8 × 128 MB = 1.02 GB and 8 × 122.6 MB = 0.98 GB.
- **(v) is consistent with Table 15.1.** It has separate rows for the specular part (700 ms) and for specular plus scattering (3 s).

**The misread.** S5 is shown as 1/1 with no mark. Seat 5 confirmed 4a-2G, but it never rated the terms added since then: the FIFO order at solve granularity, coalescing while waiting, and the gate wait feeding the staleness metric. These change the gate's design, which is Seat 5's subject (threading, real-time safety, hosts). Seat 3's re-run also sent Seat 5 an open hand-off: "A non-realtime processBlock would then wait on a gate held by another instance's builder thread. Seat 5 should check that this is allowed." No round addressed it. The offline path takes the gate (decision (i); `ScenePipeline::process` L400–402). This is the same defect I found for S3 and S6 in round 1. The winner changes only if Seat 5 rates a 3. A one-line Seat 5 re-run on 4a-2G++, including Seat 3's hand-off, closes it. S2 and S8 were also confirmed on 4a-2G rather than 4a-2G++, but the added terms are records, ordering and visibility, which do not bear on their measures, so I accept those carries.

**Corrections.**
- **Late conditions not yet in the text:**
  - Seat 1: (1) label 1 / 3 / 10 s as UI response-time anchors, not audibility limits; (2) every (iv) record states the automation speed or rebuild step it was taken at.
  - Seat 7: (1) "settling" on every instance waiting at the gate, project load included; (2) if 8 instances at 100 m take more than 10 s until the last is audible at load, it goes to Maisara before the first release; (3) the Bitwig sandbox gap goes in the public compatibility notes until Phase 13.
  - Seat 9: (a) any D-T3 pass states cost per scene class (closed reverberant box against open-face box), not per side length; (b) it reaches Maisara before Phase 12 builds presets.

  If Seat 9's conditions are left out, its later is 2 and the max is 2. If Seat 7's are left out as well, 4a-2G++ ties 4a-2 at a sum of 19 and the outcome falls to the reversibility tie-break. These are records, escalations and wording, they raise no other seat, and they should be added as the conditions under which those cells were rated.
- **Seat 6 wording lost in round 3:** (iv) dropped "(position and room size)" after "automated together". Round 2 had it and Seat 6's condition requires it.
- **Register:** replace the S7 and S9 rows with their re-run words. S7: "slower project loads and memory that grows with instance count", plus stems silent at load until their turn. S9: its conditions (a) and (b).
- **/fix-plan list:** the NEEDS MAISARA /fix-plan list must also name the Phase 08 commitments from (iv) (binaural records with the gate wait shown separately) and (v) (item 8 measured with the gate wait; findings attributed to the diffuse solve; the remedy route is a Phase 10 split-update AX). Round 3 adds them to the decision but not to the list.

### Seats' conditions the plan-editor must write into the AX text

- **D-T5.1:**
  - Seat 5's FP condition: RAII FTZ/DAZ in `buildRoomIR` that also restores on a throw; window sums and E_target in double; a `[pipeline]` test whose room is asserted to produce denormals, with FTZ-on and FTZ-off builds bit-identical per platform.
  - Seat 9's proviso: the tracer check at 125 Hz, 4 kHz and 8 kHz on Table 5.2 layouts 4 and 5 at s = 1 is reported before any golden is updated; a failure goes to D-T2 and Maisara, never back to AX16.
- **D-T5.2:** no seat conditions; the register line "no scheduled evidence".
- **D-T5.3:**
  - Seat 4's (i)–(iv) for letting Phase 08 go before 05h;
  - Seat 1's blind-test protocol and Seat 4's per-band 2×2 covariance form as the entry condition for the backlog item;
  - the "specular entries only" label.
- **D-T5.4:**
  - Seat 5: the finite-floor reference does not import `ref_hybrid`; it is compared in the log domain on double values; it runs in PR CI on three OSes; the golden is updated only through `update_goldens.py` after confirming a ≥ 10 dB sentinel margin.
  - Seat 6: the Phase 12 two-branch check, reported, not tuned.
  - Seat 9: the kept ≥ 60 dB check, and the ghost-tail reversal on its 60 dB convention.
  - Seat 3's condition (the smaller open boxes) is already met by the C1 addendum; cite it.
- **D-T4a:**
  - Seat 5: the gate is JUCE-free; held only around the solve, never under `stateMutex_` or the builder mutex, never in the realtime callback; TSan test with two pipelines; ≤ 128 MB additional resident; callback p99.9 recorded under concurrent builders; the Bitwig gap.
  - Seat 3: coalescing to the newest scene; FIFO; per-instance staleness records with 1, 4 and 8 instances, in the AQ10 room and at 100 m, at 48 and 96 kHz; gate order never changes output, tested in both orders.
  - Seat 6: FIFO at solve granularity; the gate wait counted in Phase 10's staleness metric and driving the UI "settling" state; records with 4 and 8 instances of the time until the last instance is audible at load, and of staleness under joint automation (position and room size), escalated against 1 / 3 / 10 s.
  - Seat 4: conditions (1) and (2), i.e. (iv) binaural and (v) item 8.
  - Seat 1: conditions (1) and (2) above.
  - Seat 7: conditions (1), (2) and (3) above.
  - Seat 9: conditions (a) and (b) above.
  - Seat 8 is satisfied by the gate; nothing new to write.
- **D-T4b:** no conditions; write the coupling note into the text.
- **D-T4c:**
  - Seat 2: both 100 m builds, with the fallback asserted, gated on the larger peak.
  - Seat 3: the AQ4 intervals against 100 ms, 700 ms and 3 s; anything above 3 s goes to Maisara.
  - Seat 6 (its 4c-1E): full rebuilds recorded for the six Phase 04 rooms; escalation as information, not a block; the "settling" and stepwise-automation hand-off; no Eyring T60 shown for an open field.
  - Seat 7: the report variant.
  - Seat 8: the 3-minute, 100 m bounce time with its ratio to real time, before Phase 08.
  - Seat 5: the CI block list; the contended-restore record; the pluginval silent-stretch record.
  - Table 15.1's conditions and Seat 1's "UI anchors, not audibility limits" label.
  - Challenge 1 stays pending.

### Question for the decider (one)

What does Seat 5 rate 4a-2G++? Include the FIFO and coalescing terms, and Seat 3's hand-off: a non-realtime `processBlock` (freeze or offline render) waiting on a gate that another instance's real-time builder holds. Only a 3 changes the winner.

### Ledger rows (continuing)

| id | item | verdict | status |
|---|---|---|---|
| P05B2-T5T4-33 | Corrections 04, 05, 06 (D-T5.1) applied | faithful | closed |
| P05B2-T5T4-34 | D-T5.1 corrected register: S1 63 Hz not repaid; band-varying α has no independent evidence | faithful | closed |
| P05B2-T5T4-35 | Correction 09 (D-T5.2): one row per seat in their words, "no scheduled evidence" | faithful | closed |
| P05B2-T5T4-36 | Corrections 16, 17, 18 (D-T5.4): two-branch Phase 12 check, ghost-tail reversal, double precision (1.19e−41 is a normal double) | CORRECT / faithful | closed |
| P05B2-T5T4-37 | D-T5.4 S6 1/1 on the restated check (re-run 3) | faithful | closed |
| P05B2-T5T4-38 | Correction 19: C1 typo fixed (L32) | fixed | closed |
| P05B2-T5T4-39 | D-T4a 4a-2G++ cells S1 0/1, S7 1/1, S9 1/1 (rated); S3, S4, S6 read from conditions; max 1, sum 17 | faithful | closed |
| P05B2-T5T4-40 | D-T4a S5 cell carried from 4a-2G; FIFO and coalescing terms and Seat 3's hand-off on non-realtime `processBlock` waiting at the gate never rated by Seat 5 | TENSION MISREAD (narrow) | open |
| P05B2-T5T4-41 | D-T4a: the late conditions of Seats 1, 7 and 9 must be written into the text (Seat 9's later is 2 without its conditions) | correction | open |
| P05B2-T5T4-42 | D-T4a (iv): "(position and room size)" dropped in round 3 (Seat 6's condition) | correction | open |
| P05B2-T5T4-43 | D-T4a register: S7 and S9 rows in their re-run words | correction | open |
| P05B2-T5T4-44 | D-T4a /fix-plan list: add the Phase 08 commitments (iv) binaural and (v) item 8 | correction | open |
| P05B2-T5T4-45 | D-T4a Seat 4 arithmetic (24.3 ms, 13.7 ms; Table 15.1 35 ms, "20 ms as printed") and Seat 7 (1.02 GB + 0.98 GB) | CORRECT | closed |
| P05B2-T5T4-46 | Corrections 22–25 (D-T4a): additional resident; K8–K10 closure claim struck; phase-13 multi-instance RSS proposed; 128 MB × K10 + Bitwig debt | faithful | closed |
| P05B2-T5T4-47 | Correction 27 and coupling note (D-T4b) | faithful | closed |
| P05B2-T5T4-48 | Corrections 28, 29, 31 (D-T4c): both 100 m builds, contended restore, bounce ratio, Table 15.1 conditions | faithful | closed |
| P05B2-T5T4-49 | D-T4c: record whether the closed low-α 100 m cube actually avoids the AX22 fallback | minor correction | open |
| P05B2-T5T4-50 | Challenge 1 (AQ10, 100 m restore gate) | NEEDS MAISARA | open |

Files:
- /home/user/makroof/docs/review/phase-05b2/10-decider-rebuttal-T5-T4.md
- /home/user/makroof/docs/review/phase-05b2/11-decider-round3-T4a-T54.md
- /home/user/makroof/docs/review/phase-05b2/6-seat3-rerun2-T4a.md
- /home/user/makroof/docs/review/phase-05b2/6-seat1-rerun-T4a.md
- /home/user/makroof/docs/review/phase-05b2/6-seat7-rerun-T4a.md
- /home/user/makroof/docs/review/phase-05b2/6-seat9-rerun-T4a.md
- /home/user/makroof/docs/review/phase-05b2/6-seat4-rerun-T4a.md
