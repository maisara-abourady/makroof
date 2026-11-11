# 48 — Listening-pack README of CI run 42935789745 (artifact `listening-pack`, folder `phase-05h/`), verbatim

Saved by the orchestrator for Maisara and the reviewer (review file 39 Q4, steward round 14 G7); the renders are in the artifact (236 MB).

```
SPATIAL SCENE LISTENING PACK - phase-05h
============================================================

Phase 05h: the late tail's LEVEL is now set from the propagated diffuse energy
(AX37) instead of the Phase 04 AX16 entries. Every scene folder holds, per
signal, <signal>_phase04_ax16.wav (the Phase 04 level) and
<signal>_switched.wav (the new level). They are NOT loudness-matched: the
level difference of the tail is the point. Mono omni preview (both ears the
same). What to listen for (phase-05h listening checklist): (1) in the
concentrated-absorption scenes t52_layout4_s0.4, t52_layout4_s1 and
t52_layout5_s1 the switched tail sounds natural against the early part (no
'reverb pasted on top', no tail that is too weak); (2) in the uniform-material
room stone_box nothing audible changed; (3) in the mixed-material rooms (club,
concert_hall_box, ...) any change sounds like a correction, not an artefact;
(4) no new seam where the early echoes hand over to the tail; (5)
club_both_near_0.3 has the listener and one source within 0.7 m of a wall
(AX44). open_field has only the floor's scattering: nearly dry.
bras_cr3_ls1_mp2 is the measured BRAS room with the largest real level change.
The t52_* rooms render Kuttruff Table 5.2's rigid faces at the contract's
minimum absorption 0.01 (the references use 0). The reference status below
says, per room, whether its tail level is gated against a certified reference,
reported against an uncertified one, or without a reference yet (decision
D-H2): the listening judgement is listening content, not an accuracy result.

SIGNALS: clicks.wav (sharp clicks), pink_bursts.wav (pink-noise bursts).

TAIL-LEVEL CHANGE PER SCENE (from render_cli --diagnostics; positive = Phase 04 was louder)
------------------------------------------------------------
dead_booth/pink_bursts_switched.wav: SCALED by -12.5 dB for playback
dead_booth/pink_bursts_phase04_ax16.wav: SCALED by -12.5 dB for playback
dead_booth emitter L: Phase 04 (AX16) minus switched tail level per band (dB): -0.17 -0.18 -0.21 -0.24 -0.26 -0.27 -0.27 -0.27; approximate note U: no
dead_booth emitter R: Phase 04 (AX16) minus switched tail level per band (dB): -0.18 -0.19 -0.21 -0.24 -0.26 -0.27 -0.27 -0.27; approximate note U: no
living_room/pink_bursts_switched.wav: SCALED by -7.1 dB for playback
living_room/pink_bursts_phase04_ax16.wav: SCALED by -7.1 dB for playback
living_room emitter L: Phase 04 (AX16) minus switched tail level per band (dB): +0.14 +0.14 +0.14 +0.13 +0.12 +0.11 +0.09 +0.09; approximate note U: no
living_room emitter R: Phase 04 (AX16) minus switched tail level per band (dB): +0.11 +0.11 +0.11 +0.10 +0.09 +0.08 +0.07 +0.07; approximate note U: no
classroom emitter L: Phase 04 (AX16) minus switched tail level per band (dB): +0.01 +0.00 +0.00 +0.00 +0.00 -0.00 -0.00 -0.00; approximate note U: no
classroom emitter R: Phase 04 (AX16) minus switched tail level per band (dB): -0.01 -0.01 -0.01 -0.01 -0.01 -0.01 -0.01 -0.01; approximate note U: no
club emitter L: Phase 04 (AX16) minus switched tail level per band (dB): -0.27 -0.27 -0.27 -0.27 -0.27 -0.27 -0.28 -0.28; approximate note U: no
club emitter R: Phase 04 (AX16) minus switched tail level per band (dB): -0.26 -0.26 -0.26 -0.26 -0.26 -0.27 -0.27 -0.27; approximate note U: no
concert_hall_box emitter L: Phase 04 (AX16) minus switched tail level per band (dB): +0.33 +0.34 +0.37 +0.39 +0.40 +0.41 +0.40 +0.39; approximate note U: no
concert_hall_box emitter R: Phase 04 (AX16) minus switched tail level per band (dB): +0.12 +0.15 +0.20 +0.24 +0.26 +0.27 +0.26 +0.25; approximate note U: no
stone_box emitter L: Phase 04 (AX16) minus switched tail level per band (dB): +0.01 +0.01 +0.01 +0.01 +0.01 +0.01 +0.01 +0.01; approximate note U: no
stone_box emitter R: Phase 04 (AX16) minus switched tail level per band (dB): +0.01 +0.01 +0.01 +0.01 +0.01 +0.01 +0.01 +0.01; approximate note U: no
open_field emitter L: Phase 04 (AX16) minus switched tail level per band (dB): n/a n/a n/a n/a n/a n/a n/a n/a; approximate note U: yes
open_field emitter R: Phase 04 (AX16) minus switched tail level per band (dB): n/a n/a n/a n/a n/a n/a n/a n/a; approximate note U: yes
bras_cr3_ls1_mp2 emitter L: Phase 04 (AX16) minus switched tail level per band (dB): -0.99 -1.02 -1.00 -1.07 -1.11 -1.16 -1.16 -1.20; approximate note U: no
bras_cr3_ls1_mp2 emitter R: Phase 04 (AX16) minus switched tail level per band (dB): -1.01 -1.05 -1.03 -1.09 -1.14 -1.19 -1.19 -1.22; approximate note U: no
t52_layout4_s0.4 emitter L: Phase 04 (AX16) minus switched tail level per band (dB): +2.10 +2.10 +2.10 +2.10 +2.10 +2.10 +2.10 +2.10; approximate note U: no
t52_layout4_s0.4 emitter R: Phase 04 (AX16) minus switched tail level per band (dB): +2.17 +2.17 +2.17 +2.17 +2.17 +2.17 +2.17 +2.17; approximate note U: no
t52_layout4_s1 emitter L: Phase 04 (AX16) minus switched tail level per band (dB): +3.37 +3.37 +3.37 +3.37 +3.37 +3.37 +3.37 +3.37; approximate note U: yes
t52_layout4_s1 emitter R: Phase 04 (AX16) minus switched tail level per band (dB): +3.32 +3.32 +3.32 +3.32 +3.32 +3.32 +3.33 +3.33; approximate note U: yes
t52_layout5_s1 emitter L: Phase 04 (AX16) minus switched tail level per band (dB): -0.83 -0.83 -0.83 -0.83 -0.83 -0.83 -0.83 -0.83; approximate note U: yes
t52_layout5_s1 emitter R: Phase 04 (AX16) minus switched tail level per band (dB): -1.39 -1.39 -1.39 -1.39 -1.39 -1.39 -1.39 -1.39; approximate note U: yes
club_both_near_0.3 emitter L: Phase 04 (AX16) minus switched tail level per band (dB): -0.12 -0.13 -0.14 -0.14 -0.14 -0.15 -0.14 -0.15; approximate note U: yes
club_both_near_0.3 emitter R: Phase 04 (AX16) minus switched tail level per band (dB): -0.78 -0.77 -0.77 -0.77 -0.77 -0.77 -0.77 -0.77; approximate note U: no

REFERENCE STATUS PER ROOM (D-H2)
------------------------------------------------------------
bras_cr3_ls1_mp2: bras_cr3_ls1_mp2: 3/8 bands gated
classroom: classroom_e0: 8/8 bands gated; classroom_e1: 8/8 bands gated
club: club_e0: 8/8 bands gated; club_e1: 8/8 bands gated
club_both_near_0.3: reported set (AX43: club both-near at 0.3 m), not gated
concert_hall_box: concert_hall_box_e0: 8/8 bands gated; concert_hall_box_e1: 8/8 bands gated
dead_booth: dead_booth_e0: 8/8 bands gated; dead_booth_e1: 8/8 bands gated
living_room: living_room_e0: 8/8 bands gated; living_room_e1: 8/8 bands gated
open_field: the finite-floor integral check (AX37 (5.4)), not a ref_hybrid reference
stone_box: stone_box_e0: 8/8 bands gated; stone_box_e1: 8/8 bands gated
t52_layout4_s0.4: t52_layout4_s0.4: 8/8 bands gated
t52_layout4_s1: t52_layout4_s1.0: 8/8 bands gated
t52_layout5_s1: t52_layout5_s1.0: 8/8 bands gated
(gated = certified ref_hybrid reference at two rungs, AX43; reported = one rung, no l_ref; the t52 rooms are the (A) cases at alpha = 0 on the rigid faces.)
```
