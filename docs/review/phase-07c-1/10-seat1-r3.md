# 10 — Seat 1, round 3 (phase 07c-1, on decider file 9 §6)

Saved verbatim by the orchestrator from the agent's report, 2026-11-12. Round-3 questions: file 9 §6.

SEAT 1, addendum to round 3 (phase 07c-1): my ruling on the truncation depth of the provisional tail (AX49).

**I accept 18.7 dB as the depth for this interim. I do not claim the cut is inaudible.** Seat 6 is right that 18.7 dB comes from the EDT condition, not from whether a shortened tail can be heard. On a held-chord stop it is probably audible:
- At abrupt stops listeners hear the decaying, extended parts of the sound (Blauert ch. 4, Reichardt and Lehmann; Kuhl; Marshall).
- A tail that stops sharply is the signature of a gated reverb, an effect producers recognise by name (Gibson, the reverb envelope entry and Visual 65).

So I expect a careful listener to detect the cut at a stop in an 8 s room. That is [Hyp]: the corpus has no threshold for a truncated tail.

**Why I accept it anyway.** This is a temporary state, not a realism claim, so a design choice logged as a hypothesis is enough under my two-tier gate.
- It lasts only the remaining synthesis time, about 3 s at 100 m and 96 kHz, and less at 48 kHz and in small rooms.
- It happens once per load, or once per edit that changes the T60. A stop has to fall inside that window to expose it.
- "Settling" is shown while it plays.
- Offline never uses it (AX49), so it can never reach a bounce while the host signals offline.

Making the cut deeper means a longer prefix. A 30 dB depth would need about 0.5·T60, about 4 s at T60 8 s, which defeats a synchronous build at load. That cost is Seat 3's and Seat 5's to rate, and I would not ask them to pay it without data.

**What I set instead, as three conditions on D3\*.**
1. **Seat 6's held-chord stop goes into the L4 listening item as a blind test, not a sighted listen.**
   - The test: ABX of the provisional against the exact tail on a held-chord stop at T60 8 s, fully wet, 16 trials, scored in advance (12/16 or more counts as detected).
   - Run it with the AX47 self-ABX in 07c-2. It is the named reversal for AX49's depth.
   - If the cut is detected, the remedy is decided then, either a deeper cut or condition 2's fade. "Detected" alone does not mean a deeper L_f.
2. **A longer fade may beat a deeper cut, for Seat 3 to cost.** My hypothesis is that the ear picks up the abrupt ending, the gated-reverb envelope, more than the depth at which it ends.
   - The option: lengthen the fade beyond 0.1 s instead of moving L_f.
   - It keeps EDT within 5 %, because the fade starts after L_f.
   - It needs only a small change to K18's accounting of the expected share f_b.
3. **The interim's duration is printed as a record.** The time from the provisional tail to the exact one, per scene and sample rate, goes beside the AX38 (iv) staleness records. If it ever grows well past about 3 s (for example with 8 concurrent instances), the case for "rare and brief" weakens, and AX49 returns to me.

**Ratings unchanged.** D3\* stays at now 1, later 1, provided condition 1 is in the L4 item. Without condition 1 I rate D3\* now 1, later 2, because a cut that is probably audible would ship with no test that could overturn it.
---

## Seat 1, round 3, first answer (before the addendum above; saved from the seat's report)

SEAT 1, round 3 (phase 07c-1). I confirm both items and withdraw my −10 dB rule.

**1. L_f = 0.312·T60_max, replacing my −10 dB rule: confirmed. My rule was wrong.** EDT is read from the backward-integrated curve of the truncated tail (Vorländer §6.4.1, Eq. 6.4), which falls faster when the tail is cut early. With the cut at the −10 dB point, a = 0.1, the curve reaches −10 dB at e^(−x) = 0.19, x = 1.66 instead of 2.30, EDT ≈ 0.72·T60: fails my own 5 % condition, as K17 says. K17's bound checks out: a ≤ 0.0136 gives L ≥ 0.3113·T60 (18.7 dB of decay); 0.312 is safe. T60_max covers every band. Truncation loses ≈ 0.06 dB of tail energy.

**2. K18 normalisation as "no compensation gain": confirmed.** Dividing by √(E_p/f_b) scales the prefix to its own expected share f_b, the same realised-to-expected normalisation the exact tail gets over its full length; not an upward gain. The 0.06 dB bound (1 + (1 − f_b)·δ, 1 − f_b ≤ 0.0136) holds for |δ| ≤ 1; δ ≥ −1; above +1 negligible. The A4 test asserting ≤ 1 dB is the backstop. Band levels for the provisional-to-exact check are taken over the tail window, from t_mix.

No ratings change. D3* stays at now 1, later 1, and B4-G at now 0, later 1.
