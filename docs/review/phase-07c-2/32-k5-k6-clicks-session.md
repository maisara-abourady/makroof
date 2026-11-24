# 32: Builder, K5 (the two click events) and K6 (session length)

This file holds computation only and makes no decision. Nothing in `src/`, `tools/` or `tests/` was changed or tuned
(PRD NFR-8). It answers decider file 31's "Click events: K5" and "K6" bullets.

- Binary: `build/release/render_cli`. `ninja: no work to do` at 37034d8. `src/`, `tools/ci/abx_kit.py` and
  `tools/acoustics/` are unchanged since b988327.
- Stimuli: the two K4 reruns `build/k4-alt-scenes/layout4_s1__{listener_corner,both_wall}_noclick/` (file 29,
  `k4b.py`).
- S-A: a fresh full kit build, `abx_kit.py noise`: 44 block trials and 6 familiarisation pairs, 2 min 20 s. Its 100
  WAVs are byte-identical to the earlier full build `kit3`.
- Detector: `tools.acoustics.clicks.detect_clicks` on output 0, as `click_check` calls it. `python -m tools.acoustics
  clicks A.wav` gives the same events, checked on both_wall: 39 events, the flagged one at 167552, −33.71 dBFS.

## K5: verdict

Neither event is a click. Both are **detector false positives** that come from how `click_check` compares A with B.
The cause lies in the kit's comparison (`tools/ci/abx_kit.py`, `click_check`). It is not in `src/sim` or `src/cli`, and
there is nothing to report under NFR-8.

**What the flagged frame holds.** In each case it is the **direct sound of the noise burst**, which is never stepped.
- That frame is also flagged in B, the unstepped render.
- It is bit-identical in A and B (listener_corner), or A there is the exact crossfade of B and E (both_wall).
- E is the stepped IR rendered alone from sample 0.

**How a "new" event arises.** `click_check` does not compare flagged frames. It compares the frame index of each
event's *peak sample*. The detector merges flagged frames that touch into one event. The step raises A's tail in the
gaps after N, which raises A's median baseline and so its threshold: +0.57 dB (listener_corner), +1.96 dB (both_wall).
A's flagged frames therefore group differently from B's, and a group's peak sample moves to a frame that is not a B
peak. This happens on samples that are identical in A and B:
- listener_corner: 97 of A's 182 events have a peak frame that is not a B peak, and 66 of those are before N, where
  A ≡ B bit for bit.
- both_wall: 30 of 39 such events, 21 of them before N.

The flagged content is a noise-burst property that B has too. It is not in the step or fade path.

## K5: the two events placed

The fade window is [N, N + L), L = 1440 (30 ms, AQ4). `click_check`'s step region is [N − 240, N + 1680). P = 512,
and N is a partition boundary in both cases (N mod 512 = 0). "Heard" burst edges are the input edge plus each
emitter's direct delay in the aligned IR, (directS − alignmentShiftS)·fs. The burst fades are 5 ms raised-cosine
(`FADE_S`).

| | listener_corner, familiarisation pair 3, g +0.9 dB | both_wall, 0.5 dB block trial 2, g +3 dB |
|---|---|---|
| N (step onset) | 169984 (3.541333 s), partition 332 | 166400 (3.466667 s), partition 325 |
| event sample (time, level) | 169799 (3.537479 s, −39.74 dBFS) | 167552 (3.490667 s, −33.71 dBFS) |
| event − N | **−185 samples (−3.85 ms): before the fade**, where A ≡ B bit for bit (first differing sample N + 1) | **+1152 samples (+24.0 ms): inside the fade** (j/L = 0.80) |
| partition | 331, offset 327; nearest boundary N, 185 samples away | 327, offset 128; nearest boundary 128 samples away |
| direct delay in the IR, L / R emitter | 32 / 382 samples | 1407 / 32 samples |
| heard end of burst 2 (input end = N), L / R | N + 32 / N + 382 | N + 1407 / N + 32 |
| event against that burst end | inside L's 5 ms fade-out of the direct burst (N − 208 … N + 32) | 255 samples before L's heard burst end, i.e. in L's direct burst (L's fade-out starts at N + 1167); L is the far emitter (≈ 29.9 m) |
| t_mix,e in the IR, L / R | 15146 / 15340 samples | 5125 / 15447 samples |

The table's "inside the fade" and "inside L's fade-out" rows also show a fact about the scenes (no decision drawn).
In every scene the nearer emitter's direct burst ends at N + 32 samples, because alignment puts the earliest direct
at tap 32. Its 5 ms fade-out, from N − 208 to N + 32, therefore always lies inside the step region:
- In S-A, both emitters end at N + 32.
- In listener_corner, the far emitter's burst plays until N + 382 (8 ms into the fade).
- In both_wall, it plays until N + 1407, through 29.3 ms of the 30 ms fade.

Item 7's "step at a gap start" holds for the input. In both_wall it does not hold for the far emitter as heard.

### Detector on A, B, E and A − B (output 0)

| | listener_corner | both_wall |
|---|---|---|
| A: baseline / threshold / events | −60.02 / −40.02 dBFS / 182 (all 182 inside heard bursts) | −58.40 / −38.40 dBFS / 39 (30 inside heard bursts) |
| B: baseline / threshold / events | −60.60 / −40.60 dBFS / 133 (all inside heard bursts) | −60.36 / −40.36 dBFS / 28 (15 inside; the other 13 in the first ~120 ms of reverberance after a burst ends, at 1.19, 3.55–3.60 and 5.90–5.98 s) |
| E (stepped alone): baseline / threshold / events | −59.70 / −39.70 dBFS / 185 (all inside heard bursts) | −57.36 / −37.36 dBFS / 30 |
| the event's frame in A, B, E | frame 1768: A −39.736, B −39.736, E −39.725 dBFS. **Flagged in A and B** (each above its own threshold), not in E. Region frames flagged in A: 1, also flagged in B: 1 | frame 1745: A −34.43 (thr −38.40), B −36.70 (thr −40.36), E −33.97 (thr −37.36). **Flagged in A, B and E.** Region frames flagged in A: 16; also in B: 16; also in E: 15 |
| why it is "new" | In B, frames 1762–1766 and 1768 merge into one event (1767 is a one-frame gap), with its peak at 169275 (frame 1763). A's threshold is 0.57 dB higher, so 1762, 1766 and 1767 drop out. Frame 1768 becomes its own event, peak 169799, and 1768 is not a B peak frame | B's event spanning these frames peaks at 170444 (frame 1775, after the fade). In A the group's largest sample is at 167552. There |hp(A)| = 0.0623, between |hp(B)| = 0.0457 and |hp(E)| = 0.0665, which is the convex combination companion (ii) requires: no overshoot |
| A − B: events (baseline −600: A − B is exactly 0 before N, so the −90 dBFS floor rules) | 12 events. The first is one long group from about N + 128 samples to its peak at 3.835 s (−65.7 dBFS): the scaled tail, rising smoothly. HF frame level in the region: −450 dBFS before N, −109 at N − 64, −92 at N + 32, −76 at N + 416 | 13 events. The first peaks at 3.5204 s (N + 2577, after the fade) at −44.4 dBFS. In the region the frame level rises smoothly from −56.9 to −45 dBFS |
| A − B high-passed peak in the fade [N, N + L) against the 100 ms after it | −63.02 against −57.43 dBFS (−5.6 dB) | −35.58 against −34.95 dBFS (−0.6 dB) |

A transient in the step or fade path would put the A − B peak inside the fade. In neither case is it there.

Companions (i)–(iii) passed on both stimuli (`midfade` in the K4b manifests).
- (ii) shows that A in the fade is the linear crossfade of B and E within 8u.
- (iii) shows A ≡ B before N and A ≡ E after the fade.

So A cannot contain a transient that is absent from both B and E. B and E are fixed-IR renders of the same programme.

### W-a margins

W-a margin per 1 ms window = 10 log10(bound · max(E_a, E_b) / E_o), with bound = (1 + 48/1440)² (1 + 10⁻⁵) (0.2849 dB).
A margin of 0 or more passes. There are 38 windows per output and 76 in all, with none skipped. Outputs 0 and 1 are
identical (diotic).

| | listener_corner | both_wall |
|---|---|---|
| minimum, all 76 windows | 0.2849 dB (the windows after the fade, where A ≡ E: ratio E_o / max = 1.000) | 0.2849 dB (same) |
| minimum inside the fade | 0.2991 dB (window N + 1392, ratio 0.9967) | 0.3468 dB (window N + 1392, ratio 0.9858) |
| window holding the event | N − 192: 0.4141 dB (ratio 0.9707) | N + 1152: 0.8513 dB (ratio 0.8777) |
| range inside the fade | 0.299 to 1.130 dB | 0.347 to 4.037 dB |

Rows for output 0, as (window start − N, margin dB): `k5_results.json`, key `Wa_rows_ch0`.

### S-A (layout4_s1/default): all 50 noise-chain stimuli

`click_check` passes on **50 of 50** stimuli (22 + 22 block trials, 6 familiarisation pairs), so no new event appears
in the step region. W-a's worst ratio is 1.0000 on every stimulus (windows 76), and every companion passes. This is
the kit's own run.

The same mechanism needs stating, because it bears on what "clean" means here. In every S-A stimulus the step
region's loudest high-passed frame lies 23.8 to 30.1 dB **above** A's detector threshold. That frame is the direct
burst's 5 ms fade-out ending at N + 32, and it is flagged in A and B alike. Across the 50 stimuli the counts are:

| | events |
|---|---|
| A | 695 |
| B | 736 |
| A − B | 9 to 17 per stimulus |

S-A passes because A's and B's peak frames there coincide. It does not pass because no frame in the step region is
flagged. On this noise programme the detector, used as `click_check` uses it, cannot discriminate in the step region.
`clicks.py`'s docstring lists noise as a blind spot.

The independent evidence on S-A is companions (i)–(iii) and A − B. In all 50 stimuli the high-passed A − B peak
inside the fade is **below** its peak in the 100 ms after the fade, by 0.51 to 5.69 dB; it is above it in none.

Read this way, S-A, listener_corner and both_wall are equally clean. On the detector alone, S-A passes by the same
peak-frame coincidence that the other two missed.

**Follow-up for the decider (no change made).** `click_check` could compare per-frame flags, with each render
judged against B's threshold, or run on A − B against the crossfade model. Either is a kit change under item 6, not
an `src/` change. Whether it is needed is Seat 3's and Seat 5's call.

## K6: session length for one scene

Durations come from the S-A noise chain's manifest and WAVs: each trial's A, B and X have the same length. Speech
comes from the local speech-chain build on S-A (TSP MA01_01 and MA01_02), whose stimulus length is fixed by the two
utterances.

| | stimulus length (A = B = X) |
|---|---|
| noise, block trials (44) | 11.109 to 11.418 s, mean **11.245 s** |
| noise, familiarisation (6) | mean 11.237 s |
| speech (all stimuli) | **8.774 s** |

The noise length is lead (8 + seeded 0–31 partitions) + 3 bursts (1.003 s) + 3 gaps (ceil(T30) = 2.016 s) + the IR
length (1.968 s). It therefore scales with the scene's T30; this K6 is for S-A only.

### Assumptions (`[Hyp]`; the run sheet says "listen to A, B and X, as often as you like, as whole files")

- A trial costs *plays* × stimulus length + *overhead* (choosing, answering, moving on).
- Breaks: a 2 min break after trial 11 of each block (item 2), and a 5 min rest between blocks and between chains.
- Familiarisation is once per chain: 6 labelled pairs, each A and B played *f* times.
- Setup (run-sheet checks, sealing, level setting) and voided-block reruns are excluded from the main figure.

| pace | plays per trial | overhead per trial | f | noise trial / block | speech trial / block |
|---|---|---|---|---|---|
| brisk | 3 (A, B, X once) | 5 s | 1 | 38.7 s / 16.2 min | 31.3 s / 13.5 min |
| typical | 5 | 8 s | 2 | 64.2 s / 25.5 min | 51.9 s / 21.0 min |
| slow (near threshold) | 8 | 10 s | 3 | 100.0 s / 38.7 min | 80.2 s / 31.4 min |

### Session length, one scene, both chains

| pace | 0.9 dB only (1 block per chain: 0.9 dB not detected) | **up to 2 blocks per chain (0.9 and 0.5 dB)** | every block voided once and rerun (upper bound) |
|---|---|---|---|
| brisk | 39 min (0.64 h) | **78 min (1.31 h)** | 2.6 h |
| typical | 60 min (0.99 h) | **116 min (1.94 h)** | 3.8 h |
| slow | 87 min (1.45 h) | **167 min (2.79 h)** | 5.5 h |

**Estimate: about 2 h of listening per scene** for the full design (2 chains × 2 blocks × 22 trials + familiarisation),
with a range of 1.3 to 2.8 h by pace. The audio floor (every file heard exactly once, no overhead, no breaks) is
48 min. File 30's `[Hyp]` of 1 to 1.5 h holds only at a brisk pace. At a typical pace the full design is nearer 2 h,
and with a slow pace or a voided block it does not fit one sitting of 2 h.

## Method

The scripts were run from the session scratchpad and are not committed:
`/tmp/claude-0/-home-user-makroof/15a7fe54-c3a6-56d1-bf8a-ebb6cc98172c/scratchpad/k5/k5.py` (the two events) and
`k5_sa.py` (the S-A census), in the same folder. Results are in `k5_results.json` and `k5_sa_results.json` there. The
S-A build is in `k5/kitfull/noise/`.

1. **Programme.** Regenerated with `abx_kit.noise_programme`. It uses T30 measured as `build_noise_chain` measures it
   and seed index 102 (familiarisation pair 3) or 1 (trial 2). The regenerated onset was asserted equal to the
   manifest's N.
2. **E.** The stepped IR rendered alone from sample 0, `abx_kit._render(..., g, 0)`, as `render_trial` makes it.
3. **Detector.** `detect_clicks` on A, B, E and A − B, output 0. The frame levels come from `frame_levels_dbfs(highpass(·))`.
4. **W-a.** `midfade_checks`' loop, with each window's margin recorded instead of asserted.
5. **K6.** WAV lengths of every A.wav in the S-A noise build and the local speech build; the formula is above.

Files: `/home/user/makroof/tools/ci/abx_kit.py` (`click_check`, `midfade_checks`, `noise_programme`, `render_trial`),
`/home/user/makroof/tools/acoustics/clicks.py`, `/home/user/makroof/docs/validation/abx-07c-2-run-sheet.md` §4,
`/home/user/makroof/docs/review/phase-07c-2/29-k4-candidates.md` and `30-seat7.md`.
