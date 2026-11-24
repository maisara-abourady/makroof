# 24: M3-H for Maisara (NEEDS MAISARA, case (a)): where the NFR-8 placement findings' cause is ruled

Orchestrator's summary of the record, 2026-11-24. It makes no decision. It assembles what the README's case (a) needs:
the question, the PRD ids, the options with every convened seat's own cells, the decider's recommendation and the
interrogator's finding.

## Why this reaches you

The corner home ("M3-H") is the one part of M3 still contested after three rounds. The decider applied the strict
reading of `docs/board/README.md` ("a ruling after 3 contested rounds that fails the interrogator's check" goes to
you), so its ruling (file 17 §3, H4) was checked once (file 20), and it did not survive: Seat 5 was not convened, Seat
2's H4 cell was read rather than stated, and a premise was false (phase-07d already "lands before 08-4 freezes its
goldens", so the 07d option could be ranked). The missing cells have since been given in the seats' own words (files
22-seat2, 22-seat5), so the material below is complete.

## The findings (builder file 5; Seat 9 file 14)

- (a) `layout4_s1/both_corner`: a source 0.1 m from two walls and the ceiling has a 1 kHz reverb tail 6.2 dB below the
  other source's at the same listener and time. A diffuse room predicts equal levels (Kuttruff Eq. 5.42, indicative).
  Probably an NFR-8 breach (Seat 2).
- (b) `layout4_s1/both_wall`: one source's tail starts at 0.165 s, the other's at 0.380 s; levels agree at equal times.
  Seat 2 traces it, from the code, to AX22's realised-k test; may not be a breach.
- (c) `layout4_s0.7/default`: −1.2 dB spread, not attributed (the room is not diffuse). Lower priority.

Nothing is tuned; this is about *when and where* the cause is ruled, and whether a `src/sim` fix (if any) lands before
the Phase 08 goldens freeze.

## Question

Where is the cause of these findings ruled, and must that happen before Phase 08's binaural ABX stimuli (08-3 item 15)
are built and before 08-4 freezes the goldens?

## PRD ids

NFR-8 L112 ("Any valid scene renders correctly; no environment-specific code paths", v1); FR-3D-5 L75 (sources
"anywhere in the scene"); NFR-1 L105; L49 / L101 ("Accuracy first"); L55 / L174 ("no fixed deadline").

## Options and cells (now / later, 0–3; each seat's own words)

| option | Seat 2 | Seat 5 | Seat 7 | max | sum |
|---|---|---|---|---|---|
| **H4 + G1–G3**: a small report-only phase-07e (Lead Seat 2), parallel with 08-1/08-2; gates 08-3 item 15's stimulus build and 08-4 (in 08-4's *Depends on*, G1); 07d's re-pin waits on 07e and any fix (G2); its pytest per AX5 (G3) | 1/1 (22-seat2) | 0/1 with G1–G3 (0/2 without) (22-seat5) | 1/0–1 (14-seat7) | **1** | **3–4** |
| H3: a phase blocking all of Phase 08 | 1/1 | 1/1 (1/0 with G1–G3) | 1/0–1 | 1 | 4–5 |
| H2-c: a named scope inside 07d (Lead Seat 2) | 1/2 as worded (1/1 if it also gates 08-3 item 15) | 1/2 (07d's closure rests on runner timing; would hold the freeze) | 1/1 | 2 | — |
| H1: an item in phase-13-2, just before release | 0/2 | 0/2 | 0/2 | 2 | — |

**Decider's recommendation (file 17, FOR MAISARA M3-H): H4.** With Seat 5's conditions G1–G3 it is the only option at
max 1 and the lowest sum. Seat 2 and Seat 5 both prefer it; Seat 7 proposed it.

**Interrogator (file 20):** H4's ruling failed on convening and one premise, not on its substance; the corrections (R2
→ G3; K16 corrected) are carried into this summary.

## What each option costs you

- H4: about one extra short session before 08-3's stimuli; no extra listening.
- H3: same session, but all of Phase 08 waits.
- H2-c: ties the ruling to 07d's macOS/runner-timing loops; the freeze can be held by runner flutter.
- H1: nothing now; if a fix is needed, a second golden round and up to about 11 h of re-listening just before the beta.

## Recommended answer

**H4 with G1–G3.** If you choose it, the plan edits are file 17 §6 items 6–8 plus G1 (08-4 *Depends on*), G2 (07d
scope 8 waits on 07e / any fix; a late fix carries its own re-pin) and G3 (pytest bit-identical on the producing
OS/architecture, AX5 bound elsewhere).
