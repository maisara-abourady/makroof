# 25: Decider on item 7 for E's speech chain, and two wording mismatches between the run sheet and the kit

To be saved as `docs/review/phase-07c-2b/25-decider-item7.md`. Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**Outcome:**
- **Item 7 is met by option (1).** The speech signal stays as it is (M3-T unchanged). The kit drops the onset boundaries that come less than one T of programme into the stimulus. "Programme" is counted from the first programme sample, so the kit's lead-in silence does not count. This is the strict reading, so the item is not loosened.
- **(i)** The heard-T30 label becomes per scene. s = 1 scenes keep the text already pinned in the kit. E uses file 8's wording.
- **(ii)** The kit's E label text (M3-S) is authoritative. The run sheet quotes it verbatim. Context about Maisara's AX21 decision may sit outside the quoted label, as reported speech.
- NEEDS MAISARA: none.

## Convening
**Seat 1 is not re-convened.** Option (1) changes no signal: same speaker, same files, same pause, same level. It applies Seat 1's own pre-registered items together, to each stimulus:
- item 7: "at least one T30 of programme before the step";
- Q5: the onset falls in the pause, no later than 0.43·T_heard after the end of speech.

That is the precedent file 18 accepted for D1: a D-W2 item that Seat 1 rated, carried over unchanged. The realised Q5 window is a recorded quantity, recomputed by the kit (file 40, 2a). It is not a choice.

Options (2) and (3) would change the signal. They are excluded below, so the item-8 signal question that is Seat 1's does not arise.

Seat 9's 0.43-ceiling debt concerns the top of the window, which does not move.

**Reversal:** Seat 1 objects to the shift at the bottom of the window (below). In that case Seat 1 is convened with this brief:
> "Item 7 on E's speech chain: onsets restricted to ≥ T of programme. Q5 window on E becomes about [0.10, 0.38]·T_heard. Rate (1) against (3) (a different MA pair with a longer first sentence, re-measured), now and later."

## Options and bounds
| option | what it does | ruling |
|---|---|---|
| (1) Restrict onsets to boundaries ≥ T of programme after the first programme sample | Applies item 7 to every drawn onset; signal unchanged; lowest Q5 boundary moves up | **in bounds. Chosen** |
| (2) Sentence 1 made from two TSP files of the same speaker | Three sentences in total | **out:** item 8 fixes "Two Harvard sentences" |
| (3) Another MA pair with a longer first sentence | Changes M3-T, which Seat 1 accepted "for its measured assertions" (9-seat1-l4); needs re-measuring | in bounds, but it reopens a decided item and costs a full re-measure, for no gain over (1) |
| (4) Count the lead-in silence, or lengthen it | Counts silence as programme | **out:** that loosens item 7 (CLAUDE.md: tolerances follow from the requirement, never loosened to pass) |

## DECISION I7: how item 7 is met
**Reading of item 7** (applies to both chains):
- "Programme before the step" is measured from the first sample of the first programme file: burst 1 for noise, sentence 1's TSP file for speech.
- The kit's lead-in silence is excluded. The noise chain already counts this way (onset minus burst 1 start ≥ T).

**⚙ Kit change: speech chain.**
- The candidate onset boundaries are the boundaries that are all of:
  - inside Q5's window (≤ end of speech + 0.43·T_heard);
  - at or after the heard end of sentence 1 (D-M3b);
  - at least lead + ⌈T·fs⌉ samples after the start of the stimulus, where T = 2.600 s on E.
- Q5's ≥ 20 dB assertion and the replace-and-record rule work over that set.
- **Asserted:**
  - item 7 on the set's first boundary and on every drawn onset;
  - the set is not empty;
  - at least 34 passing boundaries, the smallest count K4 and K7 accepted.
- **Recorded:** the new realised window, the number of passing boundaries and the replacement rate.

**Expected on E** (from builder file 12; re-measured on the rebuild):
- End of speech is at about 2.430 s from the start of the stimulus (lead 0.085 s plus 2.345 s).
- The earliest onset is at about 2.685 s, which is about 0.255 s after the end of speech, or about 0.10·T_heard.
- The window becomes about [0.10, 0.380]·T_heard.
- The 78 passing boundaries were contiguous from the first. About 10 of them fall below the new floor, so about 68 remain [Inf; arithmetic: 0.041·2.560 s / 10.67 ms per boundary].

**Fallbacks D and B:** the same rule applies; each is re-measured if one is used.

**S-A:** still passes. 2.475 − 0.085 = 2.390 s ≥ 2.009 s.

**Nothing sealed is affected**, because nothing is sealed yet. The speech chain on E is rebuilt and must pass every pre-seal check, including the B null on speech (−130.3 dB in the diagnostic run).

**Run sheet:** the item-7 reading, the new realised window and the onset rule go into the speech-chain section.

## Ruling (i): the heard-T30 label
**The text depends on the scene.**
- **s = 1 scenes** (S-A): the label stays the one Seat 9 gave and M2 pinned, "…ISO fit spanning the AX21 gap, not a decay rate". There the early part is empty, and that text is exact.
- **E, and s < 1 scenes generally:** E's early part is filled (−8.6 dB re direct), so "the AX21 gap" does not describe it. The manifest prints file 8's M3-S text, "heard-IR T30, ISO fit spanning the early part, not a decay rate", and the run sheet keeps its L56 wording for E.

**What "the heard-T30 label stays" (M3-G) meant.** It meant the label stays alongside the construction T. It did not fix the wording for every scene. This sentence corrects M3-G.

**⚙ Kit change:**
- `HEARD_T30_LABEL` becomes one entry per scene class.
- `test_preregistered_numbers` pins both texts.
- The manifest prints the entry that matches the scene.

## Ruling (ii): E's early-part line
- The kit carries M3-S's E line: "Early part −8.6 dB re direct; the scattered early energy is absent (AX21; the fix is deferred to the B11 rule)." **It is authoritative.** The run sheet's quoted E label block must match the kit word for word, as must the manifest and the listening-pack README.
- The run sheet may add context about Maisara's decision as a **separate sentence outside the quoted label**, in reported speech with no quote marks (D-M3g's correction): "Maisara decided on 2026-11-05 that the early part should contain scattered energy; the plan's AX21 row defers the fix to the B11 promotion rule."
- **Run sheet:** it also documents `--scene-name`, with E as the default and the fallback order D, then B (builder file 12).

## Load-bearing claims
- **I7-L1** (file 13 item 8): "Two Harvard sentences with a pause ≥ T30". This excludes option (2).
- **I7-L2** (builder file 12): the earliest boundary is 2.496 s, against T = 2.600 s; there are 78 contiguous passing boundaries and end of speech is at 2.345 s. S-A passes at 2.475 s.
- **I7-L3** (arithmetic): the onset floor is 0.085 + 2.600 = 2.685 s, and (2.685 − 2.430)/2.560 = 0.0996·T_heard.
- **I7-L4** (file 40, 2a): the realised Q5 window is recorded and recomputed by the kit. It is not a rule change.

## Future-debt register
| seat | commits | undo cost | evidence | repaid when |
|---|---|---|---|---|
| 1 | The lowest Q5 onsets on E (about 0.06–0.10·T_heard) are no longer drawn. This is a small shift toward later onsets, where the tail is quieter at the onset | Restore them, or switch to option (3) | The rebuilt speech chain on E: window, passing count, minimum margin | Recorded on the rebuild; Seat 1 raises no objection |
| 9 | The 0.43 ceiling (unchanged) | — | Q5 on E at rebuild | Window recorded |

## Strongest objection
Seat 1 could argue that excluding the earliest onsets removes the loudest tail levels at the onset, which makes the step slightly harder to hear. It holds anyway:
- the ≥ 20 dB assertion still governs every onset;
- the window keeps about 68 passing boundaries;
- the only alternatives either break item 8, loosen item 7, or reopen M3-T.

If Seat 1 objects, it is convened with the brief above.

**Confidence:** medium (Seat 1 has not rated this). **Reversal:** Seat 1 objects, or fewer than 34 boundaries pass on the rebuild.

## Summary
| id | decision | state | confidence | PRD bound | reversal |
|---|---|---|---|---|---|
| I7 | item 7 counted from the first programme sample; ⚙ speech onsets restricted to ≥ T of programme; signal unchanged | proposed | medium | NFR-1 | Seat 1 objects; < 34 passing boundaries |
| (i) | ⚙ heard-T30 label per scene class (S-A: AX21-gap text; E: early-part text) | proposed | high | NFR-1 | — |
| (ii) | M3-S's E line is authoritative; the AX21 decision only as reported speech outside the label | proposed | high | NFR-1 | — |

## Decided for Maisara
- **I7.** In the speech test, the step never comes before you have heard at least one full reverberation time of the room. The silence before the speech starts does not count toward that. NFR-1: the test is kept at full strictness rather than relaxed. The other options would add a third sentence, which breaks the pre-registered design, or count silence as listening time, which loosens the test. Amends nothing of yours.
- **(i) and (ii).** Every place that describes a test scene now uses the same wording. Your 2026-11-05 decision on early reflections is quoted only as context, not as label text. NFR-1. Amends nothing.

**NEEDS MAISARA:** none.

Files:
- /home/user/makroof/docs/review/phase-07c-2b/12-builder-kit-e.md
- /home/user/makroof/tools/ci/abx_kit.py
- /home/user/makroof/docs/validation/abx-07c-2-run-sheet.md
