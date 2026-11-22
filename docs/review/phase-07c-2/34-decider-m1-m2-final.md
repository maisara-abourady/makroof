# 34 — Decider: M1 and M2 final wording (closes file 33)

These are the four corrections from file 33 for M1 and M2, ready to apply. M3 is not ruled on; it moves to phase-07c-2b.

**1. Item-5 sentence (run sheet and PR; replaces file 27's sentence)**
"Item 5 scales the whole tail target E_target = E_spec + E_diff by k = 10^(g/10). Cli L788, read with Engine L181–183, sets E′_diff = k·E_diff + (k−1)·E_spec, so E′_target = k·E_target. A band with E_spec = 0 is scaled directly (L776–779), with the same result. The rendered window from t_mix,e + 2.5 ms onward holds no images (NoiseTail L278–279; MixingTime.h L27). So the whole window waveform scales by 10^(g/20), and item 6's identity is exact at any specular share of E_target (test_cli.cpp L350–358 asserts it at share ≈ 0.74). The only unscaled energy in [t_mix,e, L) is the 2.5 ms ISM fade-out. It lies inside the 0.1 dB window tolerance whenever its share s_w ≤ 2.3 %; s_w is printed and asserted. The kit refuses three cases:
- (a) a scene with no diffuse tail level, at any g (L755–758);
- (b) a step that would need negative diffuse energy, i.e. k < share of E_target (L788–795);
- (c) a band with a specular-only tail, i.e. E_spec ≠ 0 with E_diff ≤ 0 or no diffuse reference, when g ≠ 0 (L762, L781–786).

[S-A only, as long as layout4_s1/default is the ABX scene:] On layout4_s1/default the share is 0 in every band, so this equals scaling E_b alone (file 5's wording)."

The layout4_s1/default clause stays, marked as specific to S-A. M3's scene choice re-examines it.

**2. M1 reversal condition**
M1 reverses if item 6's identity assertions fail on a rendered A/B pair:
- 10·log10(E(stepped − unstepped)/E(unstepped)) = 20·log10|10^(g/20) − 1| over the tail window;
- the per-band step equals g.

The trigger is a failure on any scene with E_target specular share > 0, where A and B differ. Click-detector results do not count. K4 fact 6's two failures are on s = 1 scenes with share 0, where A and B render the same stimuli, so they cannot tell A from B.

**3. M2 debt register (T-a), corrected**

| seat | commits | undo cost | evidence arrives | repaid when |
|---|---|---|---|---|
| 1 | The pauses and onset window of item 15(i) (the S-A binaural rerun) and of any scene M3 chooses use that scene's heard-IR T30. T-a's 0 rests on the gap being longer than the tail's own decay, which holds on S-A (2.009 s against tail 1.25–1.27 s). It fails on layout 5 (heard 2.557–2.575 s against tail-alone 2.58–2.62 s, K4 fact 9). | Minutes for a Q5 rerun; a reseal if a gap fails | At M3's scene choice (phase-07c-2b) and at item 15(i), before each seal | For each sealed scene, the manifest prints the minimum gap, the heard-IR T30 and the tail T30, asserts minimum gap ≥ tail T30, and passes Q5's ≥ 20 dB onset assertion |
| 9 | 2.009 s is a fit across the AX21 gap, not a decay rate. Its harmlessness rests on the S-A-specific premise "gaps ≥ 2.009 s also exceed 1.26 s", which is false on layout 5. | Relabel and re-check | At M3's scene choice and item 15(i) | The manifest carries Seat 9's label, and the Seat 1 row's gap-versus-tail-T30 assertion passes on that scene |

**4.** No threshold, α, trial count or item-4 rule changes.

File: /home/user/makroof/docs/review/phase-07c-2/33-interrogator-on-file31.md
