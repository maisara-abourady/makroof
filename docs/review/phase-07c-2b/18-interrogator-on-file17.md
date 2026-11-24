# Interrogator on decider file 17 (L4 rules D1, P1, P8) and commit 835e21f

D1 and P1 stand (D1 with two corrections). P8 stands only in part: its trigger 3 newly touches Seat 3 (and Seat 7), and its scheduling clause cannot be met for 07d's own remedy. Commit 835e21f closes P2–P5.

**Corpus revision:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**What I read:**
- `docs/review/phase-07c-2b/17-decider-l4-rules.md` in full.
- The current state of the files commit 835e21f touches: the run sheet §1 (L18–40) and §3 (L150–199); `docs/phases/phase-07c-2b.md` scope 2 (L124–137); BUILD_PLAN AX49 (L172); `docs/phases/phase-07d.md` L120–125.
- Background: phase-07c-2 file 13 items 4, 11, 13 and 14; builder file 32 (K6); 9-seat{1,3,7}-l4; seat file 14.

I have no shell, so I checked the commit's result in the working tree, not its diff.

## Rulings

| item | ruling |
|---|---|
| **D1** (rule (a), pre-sealed rerun block) | **SURVIVES WITH CORRECTIONS** |
| **P1** ("detected (≥ 12/16, family α 0.038)") | **SURVIVES** |
| **P8** (void triggers for sealed L4 stimuli) | **Items 1, 2 and 4 SURVIVE.** Item 3 and the scheduling clause as applied to it are **UNDERCONVENED (Seat 3; Seat 7)**, and the clause is **INCONSISTENT** for 07d's own remedy. |
| **835e21f against P2–P5** | **closes all four** |

### D1
**Claims:**
- **α: CORRECT.** Only the counted block's 16 scored trials can produce a recorded result. The void is decided on the anchor trials alone, and the voided block's scored key is never unsealed. So the chance of a false detection stays P(≥ 12/16 | p = ½) = 2517/65536 = 0.0384.
- **R-L3: CORRECT.**
  - Item 4: "A failed anchor voids that chain's block. It gets one rerun."
  - Item 14: "Same chain and tool, with the 6-trial anchor".
  - AX49: "carries the AX47 self-ABX's 6-trial 3 dB anchor".
- **Pre-sealed second block: consistent** with item 11 (every stimulus sealed before the run) and with the kit's existing refusal pattern.

**Convening: acceptable.**
- Seat 1's row covers the blind-test paradigm. The rule, however, is item 4 of D-W2, which Seat 1 rated, carried over through item 14.
- The reversal "Seat 1 objects" keeps the route open.

**Corrections:**
1. **"the rerun's time is inside K6's upper bound" is IMPRECISE.**
   - K6 (builder file 32) covers only the AX47 chains ("every block voided once and rerun" applies to those blocks). L4 is not in K6.
   - L4-T already requires "K6 is redone on the sealed L4 stimuli", and a third dated sitting if E's second sitting plus L4 exceeds 2 h.
   - Restate it: the rerun block's time enters the L4-T K6 redo and that sitting rule. It is not covered by the existing K6.
2. **No tension map is shown for (a) and (b).**
   - The cells are carried over by analogy from L-c's "unread reversal" reasons (Seats 1, 6 and 7, later 2).
   - Write the two rows as "read from conditions (L-c)": (b) at later 2 for Seats 1, 6 and 7; (a) at most 1.
   - The ordering is unchanged ((a) has the lower maximum).

### P1
- **R-L1: CORRECT.** 2517/65536 = 0.03841, which rounds to 0.038.
- The power at p = 0.75 for ≥ 12/16 is 0.630 (matching file 31 answer 4).
- "Its own family, not in the AX47 union" matches AX49 ("as its own test family").
- "inconclusive (anchor failed twice)" is consistent with D1.

### P8
**Items 1 and 2** apply D-M3h 1 and C-b to the second stimulus set.
- **R-L2: CORRECT** (AX49 L172): L_f = t_mix,e,max + 0.312·T60_max and L_p = L_f + 0.1 s, so these changes move L_f and L_p.
- Seats 2, 3 and 9 rated this rule at later 1, "minutes to a reseal". Faithful.

**Item 4 (hash backstop):**
- **R-L4: CORRECT.** CLAUDE.md, Determinism: offline rendering is "bit-identical run to run on the same platform". AX47 (a) adds "same platform and build".
- It voids only in the conservative direction. The decider's strongest objection already admits it can void after a harmless compiler change.

**Item 3 (AX49's constants: 0.312, the 0.1 s fade, the normalisation, L's rule): UNDERCONVENED, Seat 3. The decider's question is answered: yes, it newly touches Seat 3.**
- Seats 2, 3 and 9 rated only D-M3h 1's triggers (AX21 false, t_mix,e moved, decay target changed). AX49's constants are a new trigger.
- They are Seat 3's own matter: it is D-C9's owner, and in 9-seat3-l4 it took "the remedy space if L4 detects" (Seat 1's hand-off).
- Item 3 attaches a void, and through the "After a void" clause an L4 session obligation, to every change of those constants. That includes 07d's remedy, which Seats 1, 2 and 6 named as "raise 0.312 or lengthen the fade".
- **Seat 7 is touched as well.** The clause commits Maisara to a further L4 session for each such change (its row: "schedule and complexity cost of an option, founder's capacity"). Items 1 and 2 reuse D-M3h 1's clause, which was in front of Seat 7 in the M3 round; item 3 does not.

**The "After a void" scheduling clause is INCONSISTENT when the change is 07d's own remedy.**
- The clause reads: "If no L4 session follows the change before 07d decides AX49's remedy, the change's phase schedules L4 on rebuilt stimuli before that decision."
- When the change to AX49's constants *is* 07d's remedy decision, "before that decision" cannot be met: the rebuilt stimuli need the constants the decision sets.
- The clause must state which ordering applies to 07d's own change.

**Homes:** consistent with file 10's L4-W edit and the B11 homes. They wait for item 3's convening.

## Commit 835e21f against interrogator file 16
| file-16 id | what was wrong | state now | closed? |
|---|---|---|---|
| **P2** (blocker) | the speech null was attributed to fallback scene B | Run sheet §3 item 2 (L159–165): "E-render null results"; "on every sealed scene … the unstepped render B nulled within −120 dB against the offline render on every speech stimulus (builder file 4 fact 5 nulled B on noise only); the stepped render E is already nulled on speech (−130.0 dB or better)". This matches file 10 M3-T, file 4 fact 5 and M3-C 7. | **closed** |
| **P3** | §1 kept the S-A-only clause | §1 L35–40 carries D-M3f's clause ("[Scenes with s = 1 on every face:] … On an s < 1 scene … M1's reversal condition (file 34 item 2) is live there"), with E's share 0.022 / 0.001 in place of S-B\*'s example (D-M3d is dormant) and a provenance note. Faithful. | **closed** |
| **P4** | click_check shown as undecided; no form-(b) criterion or pre-seal set | Run sheet §3 item 3 (L176–185) gives form (b)'s criterion, the red tests, the bracket (−68 caught / −72 missed), the prints, and M3-C 7's pre-seal set (form (b) green; B and E nulled on noise and speech; M1 within 0.05 dB). phase-07c-2b L129–131 adds "**Decided:** form (b) … (D-M3a …; run sheet §3 item 3)". | **closed** |
| **P5** | stale phase references | AX49 L172 reads "run with the AX47 ABX in 07c-2b", and its phases column includes 07c-2b. phase-07d L124 points to phase-07c-2b. | **closed** |

Residual note, not a reopening: M3-C 6's gap-cue print (per stimulus: E − B at 1 kHz over [N, N + 100 ms) and [N, N + 300 ms), and the per-band maximum ΔG) is not on the run sheet. File 16 did not raise it, and the run sheet's silence on a kit print is not wrong in document mode. It belongs in the kit.

## Ledger
| decision | check | item | verdict | evidence | outcome | question for the decider |
|---|---|---|---|---|---|---|
| D1 | claim R-L3 | anchor and failed-anchor rule carried to L4 | CORRECT | file 13 items 4, 14; AX49 L172 | — | — |
| D1 | claim | α 0.0384 unchanged under a pre-sealed rerun | CORRECT | 2517/65536; void decided on anchors only | — | — |
| D1 | convening | Seat 1 not re-convened | acceptable | item 4 is part of D-W2, which Seat 1 rated | — | — |
| D1 | claim | rerun "inside K6's upper bound" | IMPRECISE (K6 excludes L4) | builder file 32 K6; L4-T | SWC | restate under L4-T's K6 redo and third-sitting rule |
| D1 | map | (a)/(b) cells by analogy with L-c | not shown | 9-seat1/6/7-l4 L-c later 2 | SWC | write the two rows marked "read from conditions" |
| P1 | claim R-L1 | 0.03841 → 0.038; power 0.630 | CORRECT | binomial | SURVIVES | — |
| P8 | claim R-L2 | L_f, L_p move with t_mix,e and T60 | CORRECT | AX49 L172 | — | — |
| P8 | claim R-L4 | hash backstop on the sealing platform | CORRECT | CLAUDE.md Determinism; AX5 | SURVIVES (item 4) | — |
| P8 | convening | items 1–2 (D-M3h 1, C-b) | faithful (Seats 2, 3, 9 rated later 1) | 1-seat2 Q3; D-M3h 1; C-b | SURVIVES | — |
| P8 | convening | item 3: AX49 constants | UNDERCONVENED (Seat 3, D-C9 owner and remedy space; Seat 7, session obligation) | 9-seat3-l4; 9-seat1-l4 hand-off; 9-seat7-l4 | waits | convene Seats 3 and 7, narrow |
| P8 | inference | "schedules L4 … before that decision" when the change is 07d's remedy | INCONSISTENT (cannot be met) | file 17 "After a void" | waits | state the ordering for 07d's own change |
| 835e21f | P2 | B/E renders vs scenes in the speech null | closed | run sheet L159–165 | — | — |
| 835e21f | P3 | D-M3f clause | closed | run sheet L35–40 | — | — |
| 835e21f | P4 | form (b) and the pre-seal set; "Decided" line | closed | run sheet L176–185; phase-07c-2b L129–131 | — | — |
| 835e21f | P5 | stale phase references | closed | AX49 L172; phase-07d L124 | — | — |
