# Seat 6 — confirmation S6-a (D-T1.6 user note U)

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

SEAT 6 POSITION: S6-a, the D-T1.6 user note (round 3)

I did not re-read the corpus this round. I read `29-decider-round3-T1-T2-T6.md` (§D-T1.6, "Trigger-by-seat table", "Where U fires") and `27-orchestrator-C14.md` (b) and (d). I also read `24-orchestrator-C13.md` §1, §3 and §4, which are the tables U is checked against.

**1. Reading.** The question is which placements show the user "tail level approximate here", and what the note says. It triggers these cues:
- a flag on ordinary placements (my round-2 condition 3: if it shows there, the design has failed);
- an automatic helper with a hidden trigger (W4);
- the picture lying (criterion 6), here in two directions: a warning on good estimates, and a number that understates bad ones.

**2–4. Ratings (now/later)**

**U, as written: prefer the triggers. 2/1 because of the "±x from the achieved SE" text; 1/1 under condition (i).**
- **The triggers do what my condition 3 aimed at.** I accept the change from my literal form, because the data shows my form fired on good estimates:
  - "Both-near" alone flags the D-T6 small room, which has an SE of 0.006 dB (C14 (d)).
  - "VOV ≥ 0.1" alone flags `concert_hall_box` at 0.054 dB, which is 0.05 of the 1 dB jnd (C14 (b)).
- **Where U is silent:** the W1/CR4 reference positions, all 24 Phase 04 one-end cases, the listener grid, and the small room (29 "Where U fires").
- **Where U fires:**
  - the both-near cases that really are bad, such as W1 both_corner (replicate SD 2.04 dB, p95 4.1 dB; C13 §3);
  - `living_room` both_wall_0.1. That case has VOV 0.28 and no cap hit, and its replicate p95 of 0.15 dB may hide skew (C13 §2's mechanism), so firing there is honest.
- **Now: 2, because of the number in the note.**
  - In the both-near branch the achieved SE understates the real error by up to about 25×. At W1 both_corner the capped SE is 0.081 dB, the replicate SD 2.04 dB, and the median reads −1.2 dB against the long run (C13 §2, §3).
  - So the note would say "±0.08 dB" where the level is off by several dB. The note itself would lie.
- **Later: 1.**
  - The wording is a Phase 11 change and cheap to make.
  - The 0.70 m criterion still comes from one W1 sweep (29 debt register, S6 row). Inside U it acts only together with a cap hit or VOV, so its error matters less.
  - The pilot's VOV depends on n\*_max (Q2). Evidence arrives with the C++ reported set and the Phase 11 tests.

**U′ = cap hit OR both-near geometric: cannot live with. 3/2.**
- **Now: 3.** U′ shows "approximate" at default and ordinary placements whose estimates are good:
  - the gated 100 m cube's reference positions (cap hit; C13 §1; C14 (c) "every gated scene uses its full cap");
  - the D-T6 small room's default placement (both-near; SE 0.006 dB);
  - `club` both_wall_0.3 (capped, SE 0.071 dB, p95 0.095 dB; C13 §3);
  - most of `dead_booth`, whose default sits at d_L = 0.700 m (29 A.8). In a 2.5 × 2.0 × 2.2 m booth, any point more than 0.70 m from every surface lies in a central box of about 1.1 × 0.6 × 0.8 m [Inferred from 19 §2's dimensions].

  The first vocal-booth scene a producer builds would say "approximate". That breaks criterion 1 (trust in the first result), which I never trade. It also teaches users to ignore the note in the cases where it matters, which are the both-near corners that read 1–6 dB low (C13 §2). That is my W3/W4 failure pattern.
- **Later: 2.** Changing a predicate is cheap. But once a note that cries wolf has shipped to beta users, the trust it costs is not recovered by a later patch.

**5. Evidence**
- From the files read:
  - C14 (b) (`concert_hall_box`: VOV 0.106, SE 0.054 dB) and (d) (small room: SE 0.006 dB, VOV 0.0017);
  - C13 §1 (100 m cube capped; SE 0.14/0.20 dB; VOV 0.31/0.37), §2 (skew, both-near medians −1.2 to −6.7 dB), §3 (replicate SD and p95) and §4 (VOV crosses 0.1 at 0.65–0.70 m);
  - 29 §D-T1.6.
- Corpus: G jnd 1 dB, Vorländer Table 6.1, as cited by the decider (21 D4-L1).
- My incidents: W3 (silence and habituation), W4 (a helper firing on unrelated edits).
- [Inferred] the `dead_booth` geometry estimate.

**6. Conditions of acceptance**
- **(i) U → 1/1.**
  - In the both-near branch the note quotes no ±x taken from the achieved SE. Either it quotes a measured class bound (the replicate p95 per case class from the C++ reported set), or it is qualitative and points to an action, e.g. "level unreliable with source and listener this close to surfaces; move either one about 0.7 m away".
  - In the SE > 0.33 dB branch, ±x may use the achieved SE only if the reported set shows SE ≥ the replicate SD for that class. Layout 4 listener_wall fails this: SE 0.68 dB against an SD of 0.89 dB (C13 §3).
  - My round-2 conditions still apply: settled scene only, info view, never mid-drag.
- **(ii) A reversal check that covers the presets.** No default placement of a valid fixture or of a Phase 12 preset may raise U (this extends 29's reversal test). If one does, the preset's placement is fixed, not the predicate.
- **(iii) U′ → 1/1 only as a second tier.** "Cap hit OR both-near" may appear in an advanced or diagnostics view, labelled as a diagnostic (my §4 exception for an acoustician view). The "approximate" note itself stays driven by U. This may also meet Seat 2's C5 ("user-visible") without a veto against each other.

**7. Hand-offs**
- **Seats 1 and 2:** U is silent at the gated 100 m cube's reference positions (capped, VOV 0.31/0.37). Replicates there should check whether skew makes the default read low, beyond what an SE of 0.14/0.20 dB suggests.
- **Seat 7:** the public wording of the note.
- **Seat 5:** whether a second-tier diagnostic view costs anything on the audio thread.

**8. Premortem.** If U′ ships, the first beta user who builds a vocal booth sees "approximate" on a tail accurate to 0.01 dB and learns to ignore it. Later they back both mic and amp into a corner, the tail reads 1–6 dB low, and nobody heeds the note. Maisara would notice first, at the Phase 11 placement check.
