# Seat 8 (storyteller) — positions on D-T5 and D-T4

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

SEAT 8 POSITION (D-T5, then D-T4)

Corpus present (revision c1b171fe). Whose ears: a producer with no acoustics training puts the listener in a club, a hall or an open field, on headphones first, and expects the space to set the track's distance and size the way she chose them. I found no fallen persona assumption: the PRD's producers and DJs match my music-producer assumption.

=== D-T5 ===

1. **Reading.** Once AX16 stops setting the tail level, decide what sets it, the fallback count, the axis shares and the outdoor outcome. Cues: §4 cue 3 (sharp edges / depth), cue 2 (the logjam in the low end) and S5 (distance by the direct-to-reflected balance).

2. **Ranking.**
- (1) 5.1-A prefer; 5.1-C can live with.
- (2) 5.2-A prefer; 5.2-B and 5.2-C not rated (out of bounds).
- (3) 5.3-D prefer; 5.3-A can live with; 5.3-B can live with; 5.3-C can live with, on its condition.
- (4) 5.4-A prefer, conditional on C1; 5.4-B can live with.

3. **Tension now** and 4. **Tension later**

| opt | now | later | reason, in my measures |
|---|---|---|---|
| 5.1-A | 0 | 0 | It removes a tail error of up to +3.87 / −1.17 dB in rooms with one absorbing face. That error is a shift in the reverb ratio, which is the producer's depth cue, so the source moves without her touching a distance control. Typical carpeted clubs and halls with seating are the cases. |
| 5.1-C | 2 | 2 | The low bands (63–250 Hz) keep a model known to err with concentrated absorption. That is where a club tail goes muddy (WM6), and the result is a coloured tail tilted between bands. Later: a second switch, a second golden update and two models kept alive. |
| 5.2-A | 0 | 1 | The fallback decisions and t_mix,e are unchanged, so nothing new is audible. The debt is a counter list kept only to count (Seats 2 and 7). |
| 5.3-D | 0 | 0 | An honest diagnostic. No producer ever sees it. |
| 5.3-A | 0 | 1 | It keeps a diagnostic of a model that no longer sets the level, and a later phase could read it as true. |
| 5.3-B | 0 | 1 | It widens D-T1's output for a diagnostic that no producer uses. |
| 5.3-C | 1 | 2 | It is a feature with no use I can trace (see below). It ties Phase 08 (binaural, the producer's first chain) to 05b/05h and so delays headphones. |
| 5.4-A | 1 | 1 | Outdoors, the "nearly dry with a ground reflection" result holds if C1 confirms that the tail is inaudible. Debt: Phase 12's partly open scenes (a stage with a back wall, a courtyard) inherit an Eyring-rate tail outdoors. |
| 5.4-B | 1 | 1 | A new threshold AX with no producer meaning. It could cut a faint diffuse tail that a partly open scene wants. Evidence arrives at Phase 12 listening. |

**Does a directional tail serve any storytelling use?** None in my record. The exemplars build depth and externalisation from the direct/early balance and real-room early reflections (WM10, GM3, GF2). The direction of the late field appears in none of the incidents. A late field that pulls energy sideways or behind could work against the anchor: it draws attention to the speaker rather than the field, and listeners face forward (GM2, GM7). One possible use, an open-sided venue heard as asymmetric, is [Hyp] with no incident. 5.3-C fails ST7 item 2: as things stand it is decoration.

5. **Evidence.**
- Distance is set by the reverb ratio: Izhaki Ch. 24 "Reverb ratios and depth"; Rumsey §2.2 (in reflective spaces, the direct-to-reverberant ratio relates to source distance). The ΔL figures come from phase-05b2 §0.1. I make no audibility claim; that goes to Seat 1.
- Arithmetic for open_field, [Inf] (my own calculation; C1 must confirm):
  - Every single-scatter floor path in a 100×100 m footprint is shorter than about 2 × 141 m, so its energy arrives before about 0.83 s.
  - Referring it to t_mix,e = 1404 ms at T60 0.636 s attenuates it by at least 60 × 0.58 / 0.636 ≈ 55 dB.
  - That attenuation comes on top of the ledger OF level of −23 to −43 dB, and the Hann window further down-weights early arrivals.
  - So the tail at 1.4 s plausibly lies at least about 75 dB below the level reference ledger OF uses.
- Researcher: RQ6. Also ask whether any listening study uses late-field anisotropy as a perceived distance or envelopment cue in music.

6. **Conditions.**
- 5.1-C: apply 5.1-A in all 8 bands, which brings it to 0. Alternatively, keep 5.1-C only as a fallback if D-T1's agreement test fails outside 500 Hz–2 kHz, with the seam measured, which brings it to 1.
- 5.3-C: record it as a Phase 08 follow-up gated on RQ6 and a stated producer use, not as a dependency. That brings it to 0 now and 1 later.
- 5.4-A: if C1 or Seat 1 finds the 1.4 s tail audible at loud playback, my rating rises to 3, because an outdoor scene with a room tail loses its point of view (criterion 1). In that case 5.4-B is the remedy.

7. **Hand-offs.** Audibility of the seam and of the outdoor tail: Seat 1. Seam behaviour: Seat 3. What Phase 08 receives and the ±1 dB parity: Seat 4. Outdoor physics: Seats 9 and 2. Coupling with the controls and the presets: Seat 6.

8. **Premortem.** If 5.1-C ships, club presets get a boomy tail in the low bands. Maisara hears it first at the §6 listening item ("reverb pasted on top").

Workflow requirement most affected: depth by the direct-to-reflected balance per source.

=== D-T4 ===

1. **Reading.** The memory ceiling, how W1/W2 are read, and what blocks. Cues: §4 cue 10 (where it was judged: CI runs one instance) and the speed requirement in §8.

2. **Ranking.**
- (a) 4a-1 prefer, if Seat 2 shows that at least one candidate class fits at 100 m; otherwise 4a-2. 4a-3 can live with.
- (b) 4b-1 prefer; 4b-2 can live with.
- (c) 4c-2 prefer; 4c-1 can live with; 4c-3 can live with.

3/4. **Tension now / later**

| opt | now | later | reason |
|---|---|---|---|
| 4a-1 | 1 | 2 | It fits sessions of 8 to 20 instances. If no candidate fits at 100 m, D-T3 follows, and arena, festival and outdoor points of view are lost or given a size seam (FR-3D-3). |
| 4a-2 | 1 | 2 | The workflow I recommend (one shared space, many sources) puts every instance in the same large room. Eight instances building together at session load means 8 GB transient [Hyp]. |
| 4a-3 | 2 | 2 | Eight instances × 4 GB = 32 GB at load, which crashes or swaps most producer machines [Hyp, RQ1]. A crash that loses work is the moment a producer abandons the plugin. |
| 4b-1 | 0 | 1 | It measures what she actually waits for when she moves a source. |
| 4b-2 | 1 | 1 | It overstates the delay of a move and could trigger the Table 15.1 remedy unnecessarily. |
| 4c-2 | 1 | 1 | It goes to Maisara as a challenge, which is correct. |
| 4c-1 | 1 | 2 | Room-size and material edits are how a space gets established (S2, and the dead-end streets of RT11). The full rebuild is already 1.5–1.9 s at 96 kHz, the diffuse part adds to it, and nothing bounds it. |
| 4c-3 | 2 | 2 | Nothing protects against a crash at load. |

**Bounce times** [Hyp]; the update rate under AQ4 offline is for Seat 5 to confirm.
- A 3-minute song with room-size automation, rebuilt synchronously about every 32 ms, needs about 5 600 rebuilds.
- At the maximum room that takes about 56–75 min at 48 kHz (0.6–0.8 s per rebuild) and about 2.3–3 h at 96 kHz (1.5–1.9 s per rebuild), before the diffuse part is added.
- Offline bouncing exists to be faster than real time, and real-time bouncing is the recommended default (Izhaki App. A). Producers also freeze tracks to free CPU when they run many instances (Izhaki App. A), so freezing multiplies this cost.

**Instances per session** (corpus base rate, qualitative): eight reverbs in a mix "is not lavish"; many mixes use five or fewer; up to 100 are possible. Source: Izhaki Ch. 24 "Reverb quantity and allocation".

**When a producer abandons a slow scene.** No incident in my record carries a number. [Hyp]: a slow update still plays, since it crossfades (AQ10). A crash or freeze at load loses work. So memory triggers abandonment more sharply than time.

**Does a ceiling force D-T3?** Only the dense class (3–6 TB) is ruled out under every ceiling. The other classes are unmeasured, and that is Seat 2's call. On the present evidence, no ceiling forces D-T3 by itself [Inf].

5. **Evidence and researcher requests.**
- RQ3: does a quantitative instance-count base rate exist beyond Izhaki?
- RQ4: do hosts render freeze and bounce-in-place non-realtime, and how often do they update automation offline?
- RQ5: the 1 s and 10 s limits (Nielsen 1993) and the conditions they hold under.
- There is probably no published base rate for how long producers tolerate a bounce. That needs a producer test, which only Maisara can run.

6. **Conditions.**
- 4a-2 and 4a-3: count the peak at session level. Either serialise concurrent builds across instances, or share the resident data of identical rooms (Seat 5). That brings both to 1.
- 4a-1: if Seat 2 shows a class fits at 100 m, it comes down to 1 later.
- 4c-1 and 4c-3: record a full rebuild and an offline-bounce time for a 3-minute song with room-size automation at 100 m, at 48 and 96 kHz, and put them in front of Maisara before Phase 08. That brings both to 1.

7. **Hand-offs.** Concurrency and timeouts: Seat 5. Customer hardware and support: Seat 7. Whether candidates fit: Seat 2. The edit-to-hear delay: Seat 6.

8. **Premortem.** If 4a-3 or 4c-3 is chosen and fails, a producer opens a session with eight instances in one arena scene and the DAW crashes. Beta users notice it first, through support (Seat 7); CI, which runs one instance, does not.

Workflow requirement most affected: speed, meaning a scene that a producer can reach and audition within minutes.
