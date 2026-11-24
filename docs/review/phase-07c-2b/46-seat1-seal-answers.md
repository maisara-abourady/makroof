# 46: Seat 1's pre-seal answers for the ABX (S-B* spread question, wording, familiarisation, listener instructions)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 1 POSITION: pre-seal answers for the S-B* (`layout4_s0.7/default`) ABX, phase 07c-2b. Read-only; for saving as /home/user/makroof/docs/review/phase-07c-2b/46-seat1-seal-answers.md.

**Reading.** Before the S-B* seal I have to settle four things: (1) answer Seat 9's question from 14-seat9 §5, whether the −1.2 dB L − R tail spread changes what an S-B* null covers; (2) confirm or correct the §6 S-B* wording; (3) fix familiarisation feedback; (4) say what a self-listener must be told. The cues are S4 (a threshold carries its method), T1 (a null is recorded at the minimum effect it reached) and O1/R5 (the maker is the listener). I checked whether this was already answered. No Seat 1 file answers it: 14-seat1 covers only S-W, and 17-decider and 20-interrogator route this question to me as still open.

**Facts from the sealed manifest** (`build/listening-pack/phase-07c-2b/noise/layout4_s0.7__default/manifest.json`):
- The label matches run sheet §1 word for word, with `spread_clause_present: true`.
- The spread from the common onset 0.380 s is −1.234 dB, and −1.106 dB in [0.380, 0.45) s. Seat 9's inference holds: the spread sits early.
- At the 0.9 dB step, per emitter, `step_db` is 0.900 at 1 kHz for both L and R.
- Heard values at 1 kHz: `tail_share_of_heard` 0.0320, ΔG +0.032 dB, ΔC80 −0.52 dB.
- `target_specular_share` at 1 kHz is 0.0295, a different quantity that is numerically close to the heard tail share.

**(1) Answer to Seat 9, for the record (one sentence):**
"No: the −1.2 dB L − R tail spread is identical in A, B and X, because item 5 scales both emitters' tails by the same k (the manifest's per-emitter step_db is 0.900 for L and R) and the omni diotic render sums them, so it is not a cue and does not change the contrast the listener judges; it reaches the null only through the heard tail share, whose printed effect (1 kHz: share 0.032, ΔG +0.03 dB, ΔC80 −0.52 dB for the 0.9 dB tail step) the wording already carries, and removing the spread would move ΔG by about 0.004 dB and ΔC80 by about 0.03 dB, so the null covers its printed heard step on the recorded engine, no more and no less, and stays void after an M3-8 trigger."

- Arithmetic [Inferred]: equalising the tails multiplies tail energy by 2/1.759, which puts the share at about 0.036. Then ΔG = 10·log10(1 + 0.036 × 0.2303) = 0.036 dB, against 0.032 dB now. ΔC80 assumes the tail is about 0.55 of the late energy, back-solved from −0.52 dB.

**(2) §6 S-B* wording: confirmed, with one correction.** Replace "(tail share {printed} at 1 kHz;" with:
"(heard tail share {printed: heard.bands.1000.tail_share_of_heard} at 1 kHz;"
- Reason: on this scene `target_specular_share` (0.0295) sits next to the heard share (0.032) and is easy to type in its place. The S-W wording's 0.667 is the heard share as well. The rest of the text is confirmed as written.
- Filled at this build, the clause reads "heard tail share 0.032 … ΔG +0.03 dB, ΔC80 −0.52 dB". Both values still come from the manifest, never typed by hand.

**(3) Familiarisation feedback, fixed now:**
"Familiarisation is open and labelled: before each pack's first scored block the listener plays that pack's `familiarisation/` pairs with their labels visible (A stepped, B unstepped, the step size in the file name), as often as she likes; there are no practice ABX trials, and no feedback of any kind is given in or between scored blocks except the per-block `score` result that the fixed-sequence rule needs."
- Rationale: more sensitivity makes a null stronger, and it only tightens a detection's bound, which is the safe direction. The familiarisation seeds (100 and up) are separate from the scored seeds 0–29, from the code (`abx_kit.py` L799–805). Record this sentence in the §4 blank.

**(4) What the self-listener must be told before she sits:**
1. Play only `<session>/<level>dB/trial_NN/{A,B,X}.wav`. Do not open the key, the unsealed pack, `manifest.json`, the build or seal logs, or the terminal history (the logs print each trial's step).
2. Do not inspect the files: no sizes, dates, hashes, file-compare tools, waveform, spectrum or meter displays. X is a byte copy of A or B, so any of these can give it away.
3. Set the level once, before familiarisation, and do not touch it for the rest of the session. Record the headphone model, the level setting, the device at 48 kHz and the player (§2).
4. Answer every trial, guessing if unsure. Never go back to an earlier trial. Score a block only after all 30 answers are written, and do not change any answer after scoring.
5. Take the break after presentation 15. Do not sit after a mixing session or on tired ears; sittings are ≤ 2 h. If an anchor feels inaudible, keep going: the rule decides whether the block is void, not her.
6. A result holds for her alone. She must not talk about or listen to the stimuli with anyone before every block is scored.

**Tension.** Now 0, later 1, unchanged with correction (2). Without it, later rises to 2: a null recorded with the specular share would state the wrong minimum effect, which breaks my criterion 1.

**Hand-offs.**
- Seat 4 / 08-3 item 15: binaurally, the spread becomes a per-ear tail-level difference. It is still identical across A, B and X, so the per-ear ΔG and ΔC80 cover it.
- Decider: the heard ΔG of the 3 dB anchor is only +0.14 dB at 1 kHz on S-B*, but in the noise gap the tail alone is heard, stepped by the full g. I am not reopening this; an anchor void is already recorded as "inconclusive", not as a null.

**Premortem.** If the clause is filled with 0.0295 (the specular share), the null is cited at a heard step that was never measured. The first to notice is whoever checks the results row against the manifest at 08-3.

Files read:
- /home/user/makroof/docs/validation/abx-07c-2-run-sheet.md
- /home/user/makroof/docs/review/phase-07c-2b/14-seat9.md
- /home/user/makroof/docs/review/phase-07c-2b/19-seat9.md
- /home/user/makroof/docs/review/phase-07c-2b/14-seat1.md
- /home/user/makroof/docs/review/phase-07c-2b/17-decider-m3-r4.md (grep)
- /home/user/makroof/docs/review/phase-07c-2b/20-interrogator-on-file17.md (grep)
- /home/user/makroof/build/listening-pack/phase-07c-2b/noise/layout4_s0.7__default/manifest.json
- /home/user/makroof/tools/ci/abx_kit.py (L790–809)
