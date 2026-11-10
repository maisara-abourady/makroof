# Decider — two definitions in J1 (Seat 1 floor escalation; phase-12 reopening)

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

# Decider: two definitions in J1 (interrogator 52, corrections 1 and 2; ledger P05B2-J1FX-06, -07)

Both definitions are settled below as exact plan text. Neither changes J1.
- **Trigger 1:** I take none of the three readings offered. The trigger uses Seat 1's own operational floor, including the replicate alternative Seat 1 itself gave, and therefore does not fire at the provisional W_max (A).
- **Trigger 2:** I confirm the interrogator's proposal and add Seat 6 (ii)'s remedy order: move the placement first, and reopen J1 only if that cannot silence the note.

## 1. Escalation trigger (AQ10 amendment / AX38 4c; 47 §4 (i); 51 §3)

**Plan text:**
> **Seat 1's floor at a gated scene.** At each gated 100 m build of AX38 4c, Seat 1's floor counts as **met** when the achieved SE is ≤ 0.33 dB per emitter and band and at least one of these holds:
> - (a) the pilot SE is ≤ target/3 (0.028 dB), so the VOV test does not apply;
> - (b) the pilot VOV is < 0.1;
> - (c) the final-range VOV is < 0.1;
> - (d) 30 replicates of the shipping rule against a long run give p95 |error| ≤ 1 dB.
>
> **Escalation.** If, after D-H1's margin or any growth of the non-diffuse build, the re-derived W_max leaves a gated scene where this floor is **not met**, the result goes to Maisara before any range change, with the SE, the VOV and the replicate p95. It is never fixed by a time cap, a narrower range or a formulation seam.
>
> **Starting state.** The joint-rule replicates at the gated scenes (phase-05h reported set) establish the provisional (A) state. If the floor already fails there, that is recorded as a finding and escalated once. After that, the trigger fires on any further rise of the achieved SE or the replicate p95 at that scene.

**Why it does not fire on day one** [from C16 and C15; C15 ran on the per-emitter rule, and the joint-rule replicates are owed in phase-05h]:
- **Closed 100 m cubes:** SE 0.09–0.15 dB, pilot VOV 0.47–0.59. They meet the floor through (d): C15 gives replicate p95 ≤ 0.28 dB.
- **Flutter fallback cube:** SE 0.002 dB. It meets the floor through (a).

**Seats' words supporting this definition:**
- **Seat 6 (a):** "if the non-diffuse build alone leaves W_max below Seat 1's floor at a gated scene, the gate result goes to Maisara before any range changes". The trigger refers to Seat 1's floor, so Seat 1's definition governs.
- **Seat 1, round 2:** "VOV must be < 0.1 wherever the pilot SE is above 1/3 of the target". This is clause (a).
- **Seat 1, R2:** "report VOV on the final range, or replicate p95 as in C13 and C15 … if the final VOV is < 0.1 or p95 ≤ 1 dB, I count the floor met". These are clauses (c) and (d).

**Why the other readings are declined:**
- **"SE part only"** drops Seat 1's heavy-tail check (F11). No seat asked for that.
- **"Further below than at (A)"** would make the floor relative to whatever (A) happens to give. Seat 6 (a) refers to Seat 1's floor itself, and the starting-state clause covers a pre-existing failure.
- **"An explicit list"** would have to be re-derived whenever the gated set changes.

## 2. Phase 12 reopening trigger (47 strongest objection; 51 §2 L5)

**Plan text (phase-12, with a cross-reference in AX41):**
> **Hall presets and J1.** Before Phase 12 presets are frozen, every preset's default placement is computed at the final W_max, reporting SE, cap hit and U (Seat 9).
> - A preset whose default placement raises U is first fixed by changing its placement, never the predicate (Seat 6 (ii)).
> - If U stays raised through the capped branch (cap hit AND achieved SE > 0.33 dB) at every reasonable placement, because the whole window is long, the preset **reopens J1** (bring (C) forward, or re-size W_max), and no preset is relabelled or re-materialed to hide it.
> - Capped presets with achieved SE ≤ 0.33 dB, where U is silent (for example rooms near 100 m at SE ≤ 0.15 dB, C16 (f)), are **reported only**, with their SE.

**Seats' words supporting this definition:**
- **Seat 9 (R1):** every hall preset's default "is computed at the final W_max for SE and U, and none raises U". Its premortem warns against a late relabel or a late change of materials.
- **Seat 6 (ii):** "No default placement of a valid fixture or of a Phase 12 preset may raise U … If one does, the preset's placement is fixed, not the predicate."
- **Seat 6 (R2):** under (A), "(ii) cannot be met in a cube of that type by moving the default placement, because the whole window is long". This is why the reopening applies only after the placement fix has failed.
- **Seat 8 (50-seat8):** the silent capped cubes are "about 0.1 of the 1 dB jnd … No note is owed there". This supports "reported only" for SE ≤ 0.33 dB.

**/fix-plan:** apply both texts.
- **Trigger 1:** AQ10 amendment, AX38 4c, phase-05h §3 (D-H1).
- **Trigger 2:** phase-12, with the cross-reference in AX41.

Close ledger rows P05B2-J1FX-06 and P05B2-J1FX-07 on these definitions.

Files:
- /home/user/makroof/docs/review/phase-05b2/52-interrogator-J1-plan-diff-check.md
- /home/user/makroof/docs/review/phase-05b2/45-seat1-R1-R3.md
- /home/user/makroof/docs/review/phase-05b2/45-seat6-R1-R3.md
- /home/user/makroof/docs/review/phase-05b2/45-seat9-R1-R3.md
- /home/user/makroof/docs/review/phase-05b2/31-orchestrator-C15.md
- /home/user/makroof/docs/review/phase-05b2/33-orchestrator-C16.md
