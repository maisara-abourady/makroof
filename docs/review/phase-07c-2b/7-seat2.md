SEAT 2 POSITION (round 2 of M3, phase 07c-2b, after K7-builder, file 4). Corpus present (c1b171f). I re-read Kuttruff §5.7 (Table 5.2, the Miles result above it), Vorländer Table 6.1, Vorländer Fig. 3.11 and Kuttruff §7 (Seraphim's difference limen).

**1. Reading**
The question: rate V6 on each s < 1 candidate in file 4, re-state V1–V3′ where file 4 changes a fact, rule on the gap rule for layout 5, and say whether C2 should stand. The cues it triggers:
- §4 cue 3, geometry class: one absorbing face, a different face per layout.
- §4 cue 4: placements 0.1 m from a face.
- §4 cue 5: tail decay against heard decay.

**New engine fact from the corpus: layout 5 is the better-founded layout, not an equal one.**
- Kuttruff Table 5.2 (diffusely reflecting walls, one face at α 1, the other faces at α 0) gives these iteration-to-Eyring ratios:
  - case 4 (absorbing floor, our layout 4): 1.21/1.38 = 0.877;
  - case 5 (absorbing long side wall, our layout 5): 3.06/2.99 = 1.023.
- The engine's tail follows Eyring. On layout 4 it therefore runs about 14 % long against the iteration value, which is about 3 EDT JNDs (5 %, Vorländer Table 6.1).
- On layout 5 it runs about 2.3 % short, which is under one JND and under Seraphim's 4 % decay-time difference limen (Kuttruff §7).
- So I withdraw my file-1 statement that "layout 5's provenance equals layout 4's".

**2. Ranking**
1. **V6 = layout5_s0.8/default: prefer.**
2. **V6 = layout5_s0.9/default: can live with.** Its early part is 3.4 dB emptier (−10.3 against −6.9 dB re direct), and M1's specular share is 0.001 against 0.004.
3. **V3′ (layout5_s1/default): can live with.** layout5_s0.8/default dominates it: the same tail, the same D/R within 0.2 dB, and the first orders filled instead of an early part at −76.7 dB.
4. **V6 = layout5_s0.8/emitter_wall, then layout5_s0.9/emitter_wall: can live with**, under C2′ and C4.
5. **V1 and V4: can live with.** My C1 is now met (below).
6. **V6 = layout4_s0.7/both_wall: can live with.**
7. **V2 and V3: can live with.**
8. **V6 = layout4_s0.7/listener_wall: can live with, ranked last.**

**3. Tension now / 4. Tension later (debt)**

| option | now | later | reason |
|---|---|---|---|
| L5 s0.8/default | 1 | 1 | See note A below the table. |
| L5 s0.9/default | 1 | 1 | As s0.8. M1 is barely live (specular share 0.001). |
| L5 s0.8 or s0.9/emitter_wall | 1 under C2′+C4 (2 under the old C2) | 1 | See note B below the table. |
| L4 s0.7/both_wall | 2 | 1 | Listener 0.1 m from a face, so point-receiver regime; layout-4 tail +14 % against case 4. C1 is the best handover of any candidate: S0's broadband ratio is −9.5 dB at an ISM t_mix,e of 77.5 ms. The 28.65 ms Δ is repaired by D-M3b. Later: the 08-3 binaural run needs another scene (head in the wall; Seat 4). |
| L4 s0.7/listener_wall | 2 | 1 | Listener 0.1 m from a face. The heard response is dominated by the 0.6 ms wall image: D/R −0.4 dB against an expectation of −15.0 dB. Share 0.126, so ΔG is 0.124 dB, 2.7× S-A. Layout-4 tail +14 %. |
| V3′ | 1 | 1 | Under the max gap rule, my condition ("repaid before the seal") is met by construction (file 4 Table 2: 2.624 s). |
| V1 / V4 | 1 / 1 | 1 / 1 | See note C below the table. |
| V2 | 2 | 1 | The burst-through-fade reason is gone: N − heard end ≥ 129 samples, form (b) residual ≤ −146 dBFS. What remains is the listener at 0.1 m and, at s = 1, the coherent 0.6 ms wall image zeroed (early part −67.9 dB). |
| V3 (L5 s1/emitter_wall) | 1 under C2′+C4 | 1 | The fade reason is repaired by D-M3b (N − heard end ≥ 141 samples). At s = 1 the near-wall image is absent entirely (early part −71 dB), which is the engine's worst version of that placement. |

Note A, layout5_s0.8/default, now:
- Δ is 0 ms, and every face is at least 1.7 m away.
- Both emitters are on the fallback t_mix,e of 344 ms, S-A's regime.
- Share 0.485 and ΔG 0.46 dB (10.5× S-A).
- The tail is within 2.3 % of Table 5.2 case 5.
- What remains: partial AX21. C1 broadband is −93.5 dB, and the envelope sits 60 dB below direct from about 285 ms until the tail enters at 344 ms. That is the known deficit, labelled.

Note A, later:
- the B11 trigger (minutes to reseal);
- Seat 4's layout-5 binaural label;
- the M2 re-wording.

Note B, the emitter_wall candidates:
- The 0.1 m emitter is a realistic placement (an amp against a wall).
- The engine's error there is a near-wall image scaled by a broadband s, while real s falls to about 0.07–0.10 below 125 Hz (Vorländer Fig. 3.11; one diffuser [Peer-report]). The low end is therefore under-represented.
- That error is identical in A and B (early part bit-identical), so it does not confound a tail-level ABX. It affects the label only.

Note C, V1 and V4: C1 is measured. S-B\*'s jump is −33.9 dB broadband, and the envelope is 60 dB down at 324.5 ms. That sits inside my file-1 range of 21–47 dB, so my condition is met.

**Gap rule (heard T30 against max(heard, tail T30))**
- **max: prefer, 0/0.**
- **Heard-only on layout 5: 2/1.**
- Why the tail sets the rule:
  - After the mixing time a room has one final decay slope, independent of position (Miles, cited in Kuttruff §5.7). The tail is the slowest component in the stimulus.
  - The heard T30 is an ISO fit on the combined EDC. Direct and early energy shift its −5/−35 dB window (heard D/R −1.4 dB). On layout 5 this puts the heard T30 1.6–2.4 % under the tail T30 (2.556–2.583 s against 2.582–2.617 s).
  - That difference is sub-JND, but under the heard rule the tail is still only −60 × 2.560/2.617 ≈ −58.7 dB down when the next burst starts. M2's premise is therefore false by construction.
- The max rule costs +64 ms per gap (already in K6's 2.40 h).
- On every layout-4 scene it changes nothing, because heard ≥ tail there (Table 2: identical gaps).
- Case 5's physics (about 2 % longer still) argues against any quantity shorter than the tail.
- Wording: T = max(heard T30, every tail T30) as D-M3b's construction quantity.

**C2: revise it to C2′.**
- **Drop the Δ ≤ 2.5 ms clause.**
  - It was a proxy for the far emitter's burst running into the fade.
  - D-M3b (revised) now asserts that directly: N − heard end ≥ 0, and gaps of ⌈(T·fs + Δ)/P⌉·P.
  - The measured Δ is bimodal (0 or 28.4–28.65 ms), so in this set the clause only duplicated the 0.1 m test.
- **Keep the 0.1 m clause for the listener only.**
  - A head cannot sit there.
  - The engine models an omni point receiver.
  - D-M3h 2(a) bars x = 0.1 m listeners at 08-3 for the same reason. Its letter misses y = 0.1 m (listener_wall, both_wall), which goes to Seat 4.
- **Emitters at 0.1 m are allowed**, labelled "near-wall emitter; LF image under-represented (broadband s)".

**5. Evidence**
- [Observed] Kuttruff §5.7, Table 5.2, cases 4 and 5. Ratios recomputed above.
- [Observed] Vorländer Table 6.1 (EDT JND 5 %).
- [Observed] Kuttruff §7: Seraphim, about 4 %.
- [Peer-report] Vorländer Fig. 3.11, one diffuser.
- [Observed] File 4, Tables 1–4 and Facts 1–12.
- [Peer-report] D-M3g: "the engine's tail follows Eyring".
- [Inf] The fit-window explanation of heard < tail.
- [Inf] Table 5.2's α = 0 and s = 1 differ from the scenes (α 0.01 plus air; s 0.8–0.9). At s = 0.8 specular retention is 0.198 per hit, so a grazing specular component parallel to the absorbing wall dies within about 5 hits (about 160 ms, mean free path 10.9 m). No second slope is expected.
- Researcher: verify ISO 17497-1 low-frequency s for plain walls (this is Seat 9's open item).

**6. Conditions**
- **C4 (emitter_wall, V3):** rerun the heard gaps under D-M3b (revised) with T = max. K7-builder left gap 1→2 26 ms short because its programme omitted Δ.
- **C1:** governs in broadband. The band ratios carry the s = 1 twin's filter-skirt floor (−26 to −30 dB at 1 kHz) and are printed with that floor stated.
- **both_wall and listener_wall:** no change lowers them below 2 while the listener stays at 0.1 m.

**7. Hand-offs**
- Seat 1: whether a 0.485 share meets "the hardest signal", and whether the tail entering after a 60 dB hole (partial AX21) is an extra cue.
- Seat 4: the layout-5 binaural label, and y = 0.1 m listeners under D-M3h 2(a).
- Seat 9: the layout-5 Class line ("partial-AX21" at s 0.8), and real s values.
- Validation phase, follow-up, report only (NFR-8): the engine's Eyring tail on floor-absorbing layouts runs about 14 % long against Kuttruff case 4. Kuttruff calls this the auditorium case.

**8. Premortem**
If a layout-4 wall scene is sealed alone and passes, the bound rests on a tail about 14 % longer than the corpus value for that arrangement, heard by a listener who cannot exist. The first to notice is the BRAS validation, or Seat 4 at 08-3 when no binaural twin can be built.

Files read: /home/user/makroof/docs/review/phase-07c-2b/{1-seat2,2-decider-m3,3-interrogator-on-file2,4-k7-candidates,5-decider-rebuttal-r2,6-interrogator-on-file5}.md, /home/user/makroof/docs/corpus/kuttruff-room-acoustics.md (L2740–2803), /home/user/makroof/docs/corpus/vorlaender-auralization.md (L2054–2068, L1462).
