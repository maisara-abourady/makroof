# Decider — board answers to Challenge 1, Q2a and Q2b

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

# Decider: board answers to Challenge 1, Q2a and Q2b (2026-11-10)

## Summary
- **Q2b: decided, n\*_max = 1 024 (option (i)).** This matches what was applied (AX41).
- **Challenge 1 and Q2a: not decidable on the recorded cells.**
  - Only Seat 5 has rated "Challenge 1 yes". No seat has rated Q2a (B), and no seat has rated Q2a (C) as a commitment.
  - The answers stated to Maisara ("Challenge 1 yes; Q2a (A) now and (C) later") are **not the board's answers**. They were applied without the cells to support them. I have not filled the missing cells.
  - The applied pair "Challenge 1 yes + Q2a (A)" is also **internally inconsistent as written** (D-H1, below).
  - Because phase-05h already says the restore gate is not implemented before D-H1 is recorded, the applied text can stay, marked pending, at no cost. Nothing has been built on it.

My answer differs from what was applied on Challenge 1 and Q2a, which are not yet answered by the board, and agrees on Q2b. The ratings needed to close the first two are listed at the end.

Corpus revision: `c1b171fe649f07cbeb952ef1f75d89bfaa414d0d`. Bounds: the PRD; Maisara's acceptance of every decision and of Q1 (a); for these three questions only, the AQ10 and AX36 limits lifted on her delegated authority.

---

## 1. Q2b: n\*_max

**Tension map** (cells from the D-T1.3 map: 34, 37, 30-S4a, 35-S6b):

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| **(i) 1 024**, sized so the W1 diffuse share is ≤ 25 ms | 2/2 | 0/1 | 1/1† | **1/1** | 1/1 | 1/1 (union VOV, C16b) | 1/1† | 1/1† | 1/1† | 2 | **19** |
| (ii) 8 000 fixed | 2/2 | 0/1 | 1/1† | **2/2** | 1/1 | 1/1 | 1/1† | 1/1† | 1/1† | 2 | 21 |

**Working**
1. No veto in either option.
2. Worst-off seat: both are at 2, and in both cases it is Seat 1, whose cell rests on W_max, not on n\*_max.
3. No composition lowers that 2. Seat 4's route to 1/1 under (ii) is a measured C++ W1 diffuse share of ≤ 25 ms, or an E_b refresh-interval AX. Neither exists yet.
4. Sum: 19 against 21, so **(i)**.
5. Seat 6 states a preference for 8 000, but rates both options 1/1. A preference is not a cell difference.

**Answer: Q2b = (i), n\*_max = 1 024.** It is re-derived from the C++ W1 measurement as a multiple of 64. If it comes out below 1 000, it goes back to Seats 1, 3 and 4.

**Future-debt register**

| seat | commits | undo | evidence | repaid |
|---|---|---|---|---|
| S4 | the W1 diffuse share stays ≤ 25 ms only if the C++ cost allows n\*_max ≥ 1 000 | parameter, one golden round before release | C++ W1 | AX41 value pinned |
| S6 (preference) | SE at the defaults is 0.017–0.086 dB, against 0.007–0.054 dB at 8 000 | parameter | – | – |
| S7 | n\*_max sets shipped bits | golden round before release; announced change after | – | first release |

**Reversal:** the C++ cost puts n\*_max below 1 000, or an E_b refresh AX brings Seat 4 to 1/1 at 8 000. In the second case the two options tie and are re-ranked.

---

## 2. Challenge 1: a blocking 100 m, 96 kHz restore gate (14 × t_restore ≤ 30 s)

**Tension map**

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max |
|---|---|---|---|---|---|---|---|---|---|---|
| **no** (recorded and escalated; AX38 4c as decided in D-T4c 4c-1C) | 1/1 | 1/1† | 1/1† | 0/1 | **1/2** | 1/1† | 1/1 | 1/1† | 0/1 | 2 (sum 17) |
| **yes** | unrated | unrated | unrated | unrated | **1/1** (Seat 5, files 5/13: "drops to 1 only if Maisara accepts Challenge 1") | unrated | unrated | unrated | unrated | – |

- **Not used: the round-1 4c-2 cells** (3-seat\*). 4c-2 was "block a full rebuild above a usability limit (RQ4/RQ5)". It is a different option, so its cells are not ratings of Challenge 1. They show where the eight seats may object:
  - Seat 6, 1/2: "blocking on time can force D-T3".
  - Seat 7, 2/1: it reopened AQ10, a ground now lifted by Maisara.
  - Seat 9, 1/2: it "could cut the largest-error room class".
- **D-H1** (phase-05h §3; interrogator 41, correction 1):
  - "Yes" combined with W_max sized to the same 2.143 s budget at the worst OS build leaves **no margin**.
  - The prototype restore is 2.141 s, so 14 restores take 29.98 s.
  - At the realised-work ratio AX41 allows (about 1.05), that becomes about 30.2 s: **the gate fails by design**.
  - The 1.884 s build is a best of 3, so the measurement spread adds to the risk.
  - So "yes" is coherent only together with a W_max that carries D-H1's margin for the realised-work ratio and the restore spread. That margin is decided from C++ data (phase-05h §3).

**Working.** "No" has a full map with max 2 (S5 later). "Yes" lowers S5 to 1/1, but eight cells are missing. If those eight seats rate "yes" no higher than their "no" cells, "yes" wins, at max 1 when combined with Q2b (i)… except that Seat 1's 2/2 rests on Q2a (A), so the joint max stays 2 either way, and "yes" wins on sum. Whether they do cannot be read from the record.

**Answer: not decidable yet.** It needs ratings of "yes" (in the form "yes + Q2a (A) with D-H1's margin") from Seats 1–4 and 6–9.

**Future-debt register, if "yes" holds**

| seat | commits | undo | evidence | repaid |
|---|---|---|---|---|
| S5 | the gate kept for good | CI change | C++ restore records | permanent |
| S1 | D-H1's margin shrinks W_max a little more, so the long-window error grows slightly | parameter | C++ | Q2a (C) |
| all | a block that can fail on timing noise unless D-H1 sets the margin | D-H1 AX | C++ realised-work ratio and restore spread | D-H1 recorded |

---

## 3. Q2a: W_max sizing

**Tension map** (cells from the D-T1.3 map, which was rated at W_max (A) = 3.05 M):

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| **(A)** sized to the restore watchdog | **2/2** | 0/1 | 1/1† | 1/1 | 1/1 | 1/1† | 1/1† | 1/1† | 1/1† | 2 | 19 |
| (B) about 11× (A) | unrated ×9 | | | | | | | | | – | – |
| (C) diffuse solve moved off the synchronous restore, in a later phase, with (A) meanwhile | unrated ×9 | | | | | | | | | – | – |

**Working**
1. **(B) is out of bounds if Challenge 1 is "yes".** C14 (c): under (B), every gated scene restores in 2.16–4.83 s, over the 2.14 s bound, so the blocking gate would fail. (B) is therefore only an option with Challenge 1 "no".
2. **Seat 1's 2/2 under (A)** comes from its floor failing in long-window rooms with one fully absorbing face, and in the low-α s = 1 cube (C13, C14, C16). Whether (B) lowers it is unrated:
   - C14 (a) gives a 100 m SE of 0.05–0.12 dB under (B);
   - layouts 4/5 under (B) were never computed.
3. **(C) is a later-phase rework.** Seat 5 called it about one phase of Phase 07 work. As a commitment it has no cells.
4. (A) is the only fully rated option, at max 2. I cannot rank it against (B) or (C) without their cells.

**Answer: not decidable yet.** "(A) now" is the minimum-tension option among the rated ones, but that is not a board answer until (B) is rated. "(C) in a later phase" was not chosen by the board.

**Future-debt register, for (A) as it stands**

| seat | commits | undo | evidence | repaid |
|---|---|---|---|---|
| S1 (2/2) | random tail error of about 0.3–1.3 dB SE in long-window absorbing rooms and 0.44–0.67 dB in the low-α s = 1 cube, where the switch adds error over AX16's +0.06/+0.10 dB (C16 (g)) | W_max change, or (C) | C++; Phase 12 presets | (C) or a larger W_max |
| S2, S5, S6 | W_max re-derived from C++ with D-H1's margin | one golden round | C++ | AX41 pinned |
| S7 | W_max sets shipped bits | golden round before release | – | first release |

---

## 4. Ratings the orchestrator must run (on this text)
- **R1 (Seats 1, 2, 3, 4, 6, 7, 8, 9): Challenge 1.**
  > Rate "yes" (a blocking CI gate, 14 × t_restore ≤ 30 s at 100 m, 96 kHz, with W_max (A) sized to it with D-H1's margin) against "no" (recorded and escalated, AX38 4c as decided). Give now/later ratings and conditions. Seat 5 has rated yes 1/1, no 1/2.
- **R2 (all nine, Seat 5 first): Q2a (B).**
  > W_max about 11× (A); restores 2.16–4.83 s per restore and 30.2–67.6 s for 14; 100 m SE 0.05–0.12 dB; only possible with Challenge 1 "no". Give now/later ratings and conditions. Seat 1: does (B) meet your floor?
- **R3 (all nine): Q2a (C) as a commitment now.**
  > A later phase moves the diffuse solve off synchronous restore and prepare (about one phase of Phase 07 rework), with (A) until then. Rate scheduling it now against not scheduling it.
- **Orchestrator computation, needed for R2:** layouts 4/5 at s = 1 under (B), giving SE and VOV against Seat 1's floor.

When R1–R3 are in, I decide Challenge 1 and Q2a by the same rule. If any combination carries a 3 with no alternative, it goes back to Maisara.

## 5. Plan record
- **Keep:** AX41's n\*_max value (Q2b), as the board's answer.
- **Mark pending this decider record:** the AQ10 amendment and AX38 4c (Challenge 1 "yes") and AX41's W_max basis (Q2a (A) plus (C) later). The steward's G1 finding stands until R1–R3 are rated.
- **No implementation of the restore gate** until R1 and D-H1 are recorded (already so in phase-05h §3).

**For Maisara:** the small-room limit (1 024) is the board's answer. The restore gate and the big-room limit were reported to you as board answers but were not chosen by the board. Eight seats have not rated the gate, and no seat has rated the alternatives. They are being asked now. Nothing has been built on them.

Files:
- /home/user/makroof/docs/phases/phase-05h.md
- /home/user/makroof/docs/review/phase-05b2/41-interrogator-plan-diff-check.md
- /home/user/makroof/docs/review/phase-05b2/13-decider-round4-T4a-final.md
- /home/user/makroof/docs/review/phase-05b2/34-decider-round4-final-T1-T2-T6.md
- /home/user/makroof/docs/review/phase-05b2/37-decider-round4-addendum.md
- /home/user/makroof/docs/review/phase-05b2/27-orchestrator-C14.md
- /home/user/makroof/docs/review/phase-05b2/33-orchestrator-C16.md
