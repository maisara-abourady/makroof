# 12 — Decider, decision round 3, final (phase 07c-1)

Saved verbatim by the orchestrator from the agent's report, 2026-11-12. Inputs: files 8–11.

# Decider, decision round 3 (final): phase 07c-1, D-C1, D-C2, D-C3, D-C9 (2026-11-12)

**Inputs read:** review files 9, 10-seat1/3/5/6/7/9-r3, 11 and 8. Re-read: 3-seat3, 3-seat5, 6-seat1-r2, 6-seat9-r2, `docs/phases/phase-07c-1.md` in full, PRD L99–112, BUILD_PLAN L158 (premise P1, the 07d clause).

**Code read:** `src/sim/tail/MixingTime.h`, `src/sim/Engine.cpp` L215–239 and L350–384, `src/sim/conv/CrossfadingConvolver.h` L1–50.

**Corpus revision:** `c1b171fe649f07cbeb952ef1f75d89bfaa414d0d` (checked in `docs/corpus/SOURCE_COMMIT`).

## 0. Outcome

- **No NEEDS MAISARA.** There is a real contradiction, and the orchestrator's question about it is answered here.
  - At T60_max ≈ 50 s, every interim tail that meets the seats' accuracy conditions costs about as much as the full synthesis.
  - So no option the seats have rated both survives their vetoes and closes condition 9's gate at the 100 m low-α cube.
- **This is not case (a).** Her recorded condition 9 already contains the exit: "If this phase's loop finds condition 9 does not fit here, a `phase-07d.md` of size S–M is created". BUILD_PLAN premise P1 states what follows from it ("phase-13 item 3 fires on it").
  - Applying that clause is a reading of her own decision. It is written as FM-2′ below, and the interrogator checks it once.
- **D-C9 is revised to D3\*‴.** Changes from round 2:
  1. L_f is counted from the tail's onset t_mix,e. This repairs rows 39, 40, 35 and 48.
  2. Where the prefix would reach the full length, the exact tail is built synchronously.
  3. All T60-changing edits use Seat 3's D5 bridge. Without it, the long-T60 edits would hold the ISM for the full synthesis time, which Seat 3 rated 3 under D2 (row 41).
  4. The two emitters' syntheses run in parallel (Seat 5's condition).
  5. The long-T60 gate corner moves to 07d.
- **D-C1 is narrowed to C5‴.**
  - Only classes (a) and (b) apply in 07c-1, and both are design-time bounds.
  - Class (c) goes to 07c-2's loop.
  - S3 is entered conservatively at 1/2, which ties C3. The tie is settled by the phase file, which assigns the bound to Seat 1's ruling, and by NFR-1.
- **D-C2 (B4-G′) and D-C3 (A1′) stand.**
  - D-C2: Seat 3 now rates K2 1/1, so B4-G′'s worst-off is 1.
  - D-C3: the key gains a platform part Π, and the bit-identity clause is limited to the scope AX5 covers.
- **FM-1, FM-3′ and FM-4′ are restated, and FM-2′ is redone.**

## 1. PRD digest

- **For whom:** producers and DJs in any DAW on macOS and Windows, with no spatial-audio knowledge.
- **Outcome:** a reopened project restores "the scene and its render exactly, on any machine" (NFR-6), and the result reaches the track by bounce.
- **Priority:**
  - "Accuracy is the top priority; CPU load and latency may be high, but the plugin must stay usable in a DAW session" (NFR preamble, L101).
  - NFR-2: heavy CPU and latency "are acceptable when they buy accuracy".
  - NFR-1: "Pass thresholds come from the Expert".
- **Hard bounds:**
  - NFR-8 (no scene-specific path), AX5, AQ4 (30 ms), AX40/AX44;
  - AX41 (W_max at (A) in 07c-1);
  - no `contractVersion` change; the Phase 07 state rules; no instance cap;
  - conditions 4, 5, 6, 9 (with its 07d split clause), 10, 12 and A2;
  - AQ10/AX38 4c: 14 × worst ≤ 30 s, register form.
- **Her recorded decisions touched:**
  - AX18 (2026-11-08);
  - H1-F2 (condition 9) and AQ10 (C), both accepted 2026-11-10.
- **Verification culture:** every DSP behaviour has an automated check; independent references are preferred; goldens are never regenerated to pass.

## 2. Knowledge inventory (changes since round 2)

| K | item | source | status |
|---|---|---|---|
| K15′ | L_p ≤ 3.82 s costs ≤ 334 ms per emitter at 96 kHz and ≤ 129 ms at 48 kHz | file 8 (this box) | known (this box) |
| K20 | t_mix,e ≥ t_dir,e + max(20 ms, √V ms), counted from emission. At 100 m (V = 10⁶ m³) that is ≥ 1.0 s; the k_eff term gives ≈ 6.8·V^(1/3) ms = 0.68 s, so it does not bind. | from the code, `MixingTime.h` L5, L20 | known |
| K21 | The unit-decay index is emission time; the tail is weighted in from t_mix,e | from the code, `Engine.cpp` L226–229, L366–377 | known |
| K22 | At the gated low-α cube (T60_max 50.5 s, exact tail L = 12 s), an interim faithful to EDT against the exact IR needs L_f ≥ 0.212·T60 = 10.7 s, i.e. the full FFT size | interrogator row 38 (working from Eq. 6.4) | known |
| K23 | Both crossfade states read one shared input history, so y_B = x * B is exact over all past input | from the code, `CrossfadingConvolver.h` L3, L33 | known |
| K24 | Provisional cost for 3.82 s < L_p < L at 96 kHz | none: only bounded, between 334 ms and the full ≈ 1.6 s per emitter | uninformed. **Not load-bearing for the choice:** at that corner every option either costs at most the pre-07c restore or is unrated; it feeds 07d. |

**K17′ (frame-corrected working).** The rule is L_f = t_mix,e,max + 0.312·T60_max.
- In every band b, T60_b ≤ T60_max, so the decay from the tail's onset to L_f is ≥ 60 × 0.312 = 18.72 dB.
- The tail-window energy past L_f is a fraction ≤ e^(−13.816 × 0.312) = 0.0134 (Vorländer §6.4.1 Eq. 6.4, the same working as row 36).
- So the truncation loss is 10·log10(1 − 0.0134) ≥ −0.06 dB **for every valid scene**.
- EDT within 5 % holds a fortiori: the prefix only gets longer, and K22 shows the requirement against a truncated exact IR is weaker.

**K18′ (row 37 restated).**
- The squared amplitude ratio of exact to provisional is 1 + (1 − f_b)·δ, with 1 − f_b ≤ 0.0136 and δ ≥ −1.
- So the normalisation step is ≥ −0.06 dB.
- Upward it is ≤ +0.17 dB at δ = 3. Reaching +0.5 dB needs δ ≥ 9, and +1 dB needs δ ≥ 19, i.e. the realised remainder energy at 10× or 20× its expectation.
- This part is statistical, not a hard bound, so the A4 test asserts it per band (Seat 3 r3 note 1).

**K23 consequence** [Inf; it informs the L4 test design and 07d, and the choice does not rest on it]:
- Under the provisional, the output equals the exact render (within K18′) for lags up to L_f.
- So the cut is in the output only if playback began more than L_f before the exact tail is swapped in.
- At one instance and T60 8 s, the exact synthesis is ≈ 1.6–3.2 s and L_f ≈ 3.5 s, so the exposure is ≈ 0. With 8 concurrent instances (record (g): 8.3 s) it is not.
- Seats 1 and 6 premised "≈ 3 s of audible early ending". That holds only past this window. I note it for them and do not re-rate.

---

## 3. D-C1: AX47 → C5‴

**Answers to the interrogator:**

| row | answer |
|---|---|
| 32 (S5) | Class (c) is removed from 07c-1, so C5‴'s admissible sources are all "bounds known at design time" (6-seat5-r2, word for word). S5 = 1/1 in its own words. |
| 33 (S3) | Taken at **1/2**, from Seat 3's own C3 reason ("07c-2 would need extra work"), which applies to the deferred class (c). Marked "read from its C3 reason". |
| 35 | Repaired by K17′: the truncation loss is ≤ 0.06 dB for every valid scene, by construction. |
| 54 | Repaired: in 07c-1 every source is ≤ 0.23 dB (0.06 + 0.17 at δ ≤ 3), so C3 and C5‴ give the same product unless δ ≥ 9 (asserted on A4). |
| 51, 55 | See FM-4′. |

**Tension map** (now/later; S2, S4 and S8 are NOT MY MATTER, 0/0):

| opt | S1 | S3 | S5 | S6 | S7 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|
| C1 | 1/2 | 1/1 | 0/0 | 1/2 | 0/0 | 1/2 | 2 | 11 |
| C2 | 0/1 | 1/2 | 2/2 | 0/1 | 1/1 | 0/1 | 2 | 12 |
| C3 | 0/1 | 1/2 | 0/1 | 0/1 | 1/1 | 0/2 | 2 | 10 |
| C4 | 2/**3** | 1/1 | 0/1 | **3/3** | 0/1 | 2/2 | veto | — |
| **C5‴** | 0/1 (r2) | 1/2 (read, C3 reason) | 1/1 (r2 C5′ words) | 0/1 (r2) | 1/1 (r2) | 0/1 (r2) | **2** | **10** |

**Working:**
1. Bounds: none broken.
2. C4 is out on vetoes.
3. Worst-off: C1, C2, C3 and C5‴ all have max 2.
4. Nothing to compose.
5. Sum: C3 and C5‴ tie at 10.
6. Reversibility ties: both bounds are re-decided by the 07c-2 ABX before any statistical source exists, and in 07c-1 they give the same product.
7. **Tie-break:** phase-07c-1 L40 assigns D-C1 to "Seat 1's ruling on the size of the level step", and NFR-1 says "Pass thresholds come from the Expert". Seat 1 ruled 1 dB with a 0.5 dB reversal. **DECISION D-C1: C5‴.**

**Load-bearing claims:**
- **D1-L1:** Table 6.1 gives jnd 1 dB for G and C80 and 5 % for EDT, at 500–1000 Hz; laboratory and real-room tests, paradigm not stated.
- **D1-L2:** a tail step x moves G (Eq. 6.5) and C80 (Eq. 6.7) by at most x.
- **D1-L3:** K17′ and K18′.
- **D1-L4:** the class (a) step is 0 within AX5's scope (same platform and build). Across builds the E_model fingerprint test guards it and the step is recorded (row 47).

**Future-debt register:**

| seat | commits | undo | evidence | repaid |
|---|---|---|---|---|
| S1 1 | 1 dB with no within-stream study | AX47 → 0.5 dB | 07c-2 self-ABX | ABX done |
| S3 2 | 07c-2 must decide class (c) admissibility and the load fallback | 07c-2 loop | 07c-2 stage-1 SE record | 07c-2 decision |
| S5 1 | step counter on the builder thread | none | A4 | green |
| S6 1 | automation-driven steps | — | Phase 10 | Seat 1 ruling |
| S7 1 | refusal path; testing record | — | 07c-2 | — |
| S9 1 | rejection rate in layouts 4/5 | — | 07c-2 | 07c-2 packet |

**Strongest objection:** Seat 3's later 2.
- It holds because C3 carries the same 2 and only defers the same 07c-2 work under a tighter gate.
- It would fall if Seat 3 rates C3 lower than C5‴ in 07c-2's loop.

**Confidence:** medium (one cell read). **Reversal:** the 07c-2 ABX detects a step below 1 dB; the bound then becomes 0.5 dB.

---

## 4. D-C2: AX48 part B → B4-G′ (stands)

**Changes:**
- Seat 3 r3 corrects K2 to **1/1**.
- Seat 5 r3 confirms K2 at 1/1, on condition that the synchronous stage-1 solve has priority at the AX38 gate (otherwise 1/2). **Adopted.**

**Recomputed:**

| opt | max | sum |
|---|---|---|
| **B4-G′** | **1** | **13** |
| B4 + K2 | 2 (S1, S9) | 15 |
| B2 + K2 | 2 | 17 |
| B1 alone; B3 | out | — |

**Row 45 (corrected strongest objection):**
- Keyless loads are not team-only after release: cross-OS reopens (now guaranteed by Π, see §5), cross-fs reopens and 07c-2's E_prec change all take the synchronous stage-1 path.
- In 07c-1 that costs 81–144 ms per instance with step 0 (K4, PROVISIONAL). From 07c-2 it is governed by AX47 and 07c-2's loop.
- The objection is Seat 5/7's load time, and it holds at 1/1.

**Confidence:** medium. **Reversal:** record (h) shows keyless restores past the AX38 4c rule.

---

## 5. D-C3: AX48 part A → A1′ + Π (stands; row 47 repaired)

**Π: platform tag** (OS family + CPU architecture; a compile-time constant), added as a fifth key part.
- The seats rated round 3 on the premise "every cross-OS reopen is keyless" (Seat 3 r3, Seat 5 r3). Π makes that premise a guarantee rather than an accident of P.
- The claim becomes: "all five parts match ⇒ the background solve is bit-identical within AX5's scope (same platform and build)".
- Across builds on one platform, E_model's fingerprint test is the guard, and any nonzero keyed step is recorded (diagnostic + counter).
- Whether a build id should join the key is added to the post-release engine-mismatch decision.

The map is unchanged: A1′ max 1, sum 11; A2+cond. 14; A0 23; A3 vetoed. **Confidence:** medium-high.

---

## 6. D-C9: AX49 → D3\*‴

**Answers to the interrogator:**

| row | answer |
|---|---|
| 38 | Correct. At the gated cube L_f > L. D3\*‴ builds the exact tail synchronously there, so the restore is the pre-07c restore minus the solve. No interim faithful to EDT is cheaper (K22). The gate closure at that corner goes to 07d (FM-2′). |
| 39 | Repaired by K17′/K21: L_f is anchored at t_mix,e,max, so every provisional carries ≥ 18.7 dB of tail decay. Dry 100 m example (ᾱ 0.7, T 2.23 s): L_f = 1.0 + 0.70 = 1.70 s > t_mix,e. |
| 40 | The depth is asserted from t_mix,e,max to L_f where L_p < L; the L_p ≥ L branch is asserted separately. |
| 41 | At the long corner, waiting for the provisional means holding the ISM for the full synthesis ≈ 3 s. That is D2's premise, which Seat 3 rated 3/3 ("the hold is about 3.3 s"). So "ISM waits for the provisional" is excluded. Edits take Seat 3's bridge (S3 1/1). |
| 42 | Corrected: D3\* + D5 summed to 21 (now recomputed below). |
| 48 | See AX18 below. |
| 53 | Declared in FM-2′. |

**Options and map** (per-seat max over the load and edit paths; S2 NOT MY MATTER, 0/0):

| opt | S1 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|
| D1 at load | 3/3 | 3/2 | 2/2 | 1/2 | 3/3 | 2/2 | 2/2 | 3/3 | veto | — |
| D2 (edits) | — | 3/3 | — | — | — | — | — | — | veto | — |
| D3\*′ (r2) | out at step 1: rows 38–40 (gate WRONG; early-only class = vetoed D1) | | | | | | | | — | — |
| D3\*″: frame fix + P, edits wait for the provisional | 1/1 | **3** (long-T60 edits; read from its D2 reason) | 1/1 | 1/1 | 1/2 | 2/2 | 0/1 | 1/1 | veto | — |
| D3\*″ + bridge only above L_p 3.82 s | ≤1/2 | 2/2 | 1/1 | 1/1 | 1/2 | 2/2 | ≤2/1 | ≤2/2 | 2 | ≤25 |
| **D3\*‴**: frame fix + P + D5 bridge on all T60 edits | 1/2 | 1/1 | 1/1 | 1/1 (rfc: S5 r3 condition) | 1/2 | 2/2 | 2/1 | 2/2 | **2** | **23** |
| D4 unit-decay state | n.r. (S4) | | | | | | | | ? | ≥ 21, incomplete |

**Sources of the D3\*‴ cells:**
- S1: D3\* 1/1 (r3, condition 1 adopted), D5 ≤ 1/2 (file 9 row).
- S3: its bridge condition (r3: "my bridge condition to reach 1/1"); load 1/1 (r3).
- S5: its r3 condition. The parallel per-emitter synthesis must be bit-identical to the serial build; record (h) flags any run over 5 s; reversal 2 is kept.
- S6: r3, "later … stands at 2" until Seat 1 confirms the cut inaudible or sets a deeper depth. Seat 1 did neither.
- S7: r3.
- S8 and S9: the D3\*+D5 row; S9's D5 cell on T60 edits is 2/2 (r2).

**Working:**
1. Bounds: D3\*′ is out.
2. Vetoes: D1, D2 and D3\*″ are out.
3. Worst-off: max 2 for both survivors.
4. Composition: P (Seat 5's condition) is applied. It raises no seat, because it is bit-identical and runs outside the gate.
5. Sum: 23 against ≤ 25. D4 cannot be ranked: Seat 4's cell is unrated and the round is the last. It is carried to 07d.

**DECISION D-C9: D3\*‴** (AX49 below).

**Load-bearing claims:**
- **D9-L1:** K2, the code fact: one PCG stream; output j depends on noise j…j+2h.
- **D9-L2:** K17′.
- **D9-L3:** K18′.
- **D9-L4:** K15′ + K20 together give L_p ≈ 3.6–3.7 s ≤ 3.82 s at T60 8 s / 100 m, so the rated 0.65–0.8 s per instance stands at that corner.
- **D9-L5:** K22.
- **D9-L6:** no restore under D3\*‴ is longer than the pre-07c restore. A keyed restore has no solve; the provisional costs ≤ the full synthesis; the emitters run in parallel.

**Future-debt register:**

| seat | commits | undo | evidence | repaid |
|---|---|---|---|---|
| S1 2 | D5 on edits; truncated interim at load | L4 blind ABX (16 trials, ≥ 12/16 = detected) | 07c-2 with the AX47 ABX; record (h) interim duration | ABX done; AX49 returns to Seat 1 if the duration is well past 3 s |
| S6 2 | depth not ruled inaudible | deeper L_f or a longer fade (Seat 1 condition 2) | L4 ABX | Seat 1's ruling after the ABX |
| S7 2 | 8-instance load possibly ≥ 5 s on Windows | provisional off the host thread or shortened (07d) | record (h); condition 11 trace | Phase 13 host matrix |
| S9 2 | T60 edits play the old decay under the new early part until the exact tail lands | Phase 10 D5/D6 update | record (g) | Phase 10 |
| S8 1 / S4 1 / S5 1 / S3 1 | realtime captures; per-mode M; record (h); bridge then exact | — | Phase 08/09/13 | per check |
| S5, S7 (unrated) | the long-T60 corner (3.82 s < L_p, up to the full synthesis) | 07d | record (h) T60 sweep | 07d decision |

**Strongest objection:** Seat 7's 2/2 together with the unrated long-T60 load corner.
- It holds because no restore is longer than before 07c (D9-L6), every rated alternative is vetoed or costs more, and 07d convenes Seats 5 and 7 on measured data.
- It would not hold if the condition 11 trace shows a hang dialog at ≤ 8 instances (reversal).

**Confidence:** medium-low.

**Reversals:**
- the gate fails at a corner where L_p ≤ 3.82 s;
- the condition 11 trace shows a hang, not-responding state or time limit at ≤ 8 instances;
- record (h) shows an 8-instance Windows load over 5 s at the rated corner (Seat 7);
- a common host does not signal offline by default;
- the L4 ABX detects the cut.

Each of these sends AX49 back to the board, and 07d's candidates come first.

---

## 7. Exact rows (BUILD_PLAN §2)

**AX18: append before "Amended by…"**
> **Same-scene steps (phase 07c-1 loop, 2026-11-12; FOR MAISARA FM-1).**
> - An IrSet that replaces an interim IrSet of the same scene, with the same `tailSeed`, the same emitter streams and the same fs, is joined **equal-gain**. This covers a saved, held or stage-1 E_b stepping to the final level, and the AX49 provisional stepping to the exact tail.
> - The early parts are identical. The tails share the band noise up to rounding, because `BandNoiseGenerator::make` draws one PCG stream and output j depends on noise j…j+2h only (from the code).
> - The two differ only by a normalisation gain and by the exact tail past L_p, which fades in from nothing.
> - Over the played window [t_mix,e, L], the share of the exact tail's energy before L_f is f_w ≥ 1 − e^(−13.82·0.312) = 0.987 (AX49 rule), so ρ ≥ 0.993. For level-only steps ρ = 1.
> - Equal-power would lift the mid-fade by 10·log10(1+ρ) ≈ +3.0 dB (Eq. 4.15 cross term). Equal-gain gives 10·log10((1+ρ)/2) ≈ 0 dB.
> - A T60-changing edit, including the AX49 D5 bridge to the exact tail, keeps the existing equal-gain edit law.
> - A `tailSeed` or fs change gives unrelated tail noise and is joined equal-power. Seeds match per output (`tailSeedForOutput`, Phase 08/09).
> - The first IrSet after a restore fades from silence. A restore over another scene's current IrSet, and the output-mode switch, stay equal-power.
> - `AMENDS her decision of 2026-11-08: "accepted, merge with no ci"`

**AX47**
> **Interim-to-final step (D-C1; Seat 1's ruling).**
>
> **Bound.** For one scene, a step from an interim IrSet to a later one changes the tail level by ≤ **1 dB in each of the 8 octave bands (63 Hz–8 kHz)**. The level is measured per band over the tail window (t_mix,e to the end); for a provisional tail it is also measured over the common window t_mix,e…L_f. G and C80 then move by ≤ 1 dB.
>
> **Admissible sources in 07c-1:**
> - **(a) By construction:**
>   - a saved E_b whose five-part AX48 key matches gives step 0. It is bit-identical within AX5's scope (same platform and build). Across builds on one platform, the E_model fingerprint test guards it and any nonzero keyed step is recorded.
>   - the synchronous stage-1 (A) solve at a keyless load is the final in 07c-1, so its step is 0.
> - **(b) The AX49 provisional against its exact tail:**
>   - The tail-window truncation loss is ≤ 0.06 dB in every band for every valid scene, by construction (decay ≥ 18.72 dB from t_mix,e,max to L_f; Vorländer §6.4.1 Eq. 6.4).
>   - The normalisation step is 10·log10(1 + (1 − f_b)·δ), with 1 − f_b ≤ 0.0136 and δ ≥ −1: ≥ −0.06 dB, and ≤ +0.5 dB unless δ ≥ 9.
>   - Asserted per band on the A4 set (several seeds, 48 and 96 kHz): both windows; EDT within 5 % at 500 and 1000 Hz on the whole IR against the exact IR.
>
> **From 07c-2.** A statistical source (a stage-1 estimate that is not the final) is admitted only by 07c-2's loop. It must meet this row and conditions 5 and 9, and never give an early-only first IrSet. Seat 1's p95 reading (SE ≤ 0.5 dB gives 1.96 × 0.5 = 0.98 dB) is the recorded input.
>
> **Measurement.** Every step is measured on the builder thread and recorded (diagnostic + counter), never in the callback. Wet pink-noise and speech renders check that no mid-fade value exceeds the louder endpoint.
>
> **Scope.** Excludes steps after a B1′ hold and after the AX49 edit bridge; those are recorded. Same-scene steps are equal-gain (AX18).
>
> **Reversal.** If the 07c-2 self-ABX (16 trials, capped layout-4 scene, noise and speech) detects a step below 1 dB, the bound becomes 0.5 dB.

Rationale column: Table 6.1; Eq. 6.4, 6.5 and 6.7; researcher R4 and D1; phase-07c-1 L40 (Seat 1's ruling); FM-4′; board D-C1. Phases: 07c-1, 07c-2, 10.

**AX48:** file 9's text, with these changes:
1. **Key:** "The key has **five** parts: P, S, E_prec, E_model and **Π, the platform tag (OS family + CPU architecture, a compile-time constant)**."
2. **Keyed load:** "all five parts match. The saved E_b is the interim. The background solve always runs; it is bit-identical within AX5's scope (step 0, no switch). Across builds on one platform, E_model's fingerprint test is the guard and any nonzero step is recorded."
3. **Keyless load with no IrSet current:** add "the stage-1 solve has priority over background solves at the AX38 gate (Seat 5's K2 condition)".
4. **Engine-mismatch policy:** add "the decision also rules whether a build id joins the key".
5. **Tests:** add "a Π mismatch → keyless synchronous stage-1 solve".

Rationale column as in file 9, plus interrogator P07C1-47. Phases: 07c-1, 07c-2, 08, 09, 12, 13.

**AX49**
> **Interim tail while the exact synthesis is pending (D-C9).**
>
> **What it is.** A provisional tail from the same `BandNoiseGenerator`, seed and emitter stream as the exact tail.
> - **Fade start:** **L_f = t_mix,e,max + 0.312·T60_max**.
>   - T60_max is the longest per-band T60 the exact tail is built with, air absorption included.
>   - t_mix,e,max is the latest emitter mixing time.
>   - Both are counted from emission.
>   - The tail therefore has ≥ 18.7 dB of decay after its onset in every band.
> - **Fade:** 0.1 s, so L_p = L_f + 0.1 s.
> - **Where L_p ≥ L** (the exact length), there is no provisional: the exact tail is built in its place, with no handover.
> - **Normalisation:** each band is divided by √(E_p,b/f_b). E_p,b is the realised energy over [0, L_f); f_b = (1 − e^(−13.82·L_f/T60_b))/(1 − e^(−13.82·L/T60_b)).
> - It is never scaled up to make up for the energy past L_p.
> - It plays at the AX48 interim level, with the ebar of the played decay.
>
> **Synchronously**, with ISM + matching + mix, wherever no IrSet valid at the current fs is current: project load, first restore, prepare with an fs change (FM-2′).
> - The two emitters' syntheses run in parallel and are tested bit-identical to the serial build.
> - Every load of a scene with a tail therefore starts with a tail (condition 9).
>
> **T60-changing edits.** The ISM is submitted at once over the current unit decays (the D5 bridge; Seat 3), then the exact tail follows in the background. There is no provisional on edits.
> - Position-only edits keep the cached unit decays (AQ4).
> - A restore of a scene equal to the current one keeps the current IrSet.
> - `reset()` follows condition 10.
> - An output-mode switch reuses the cached unit decays and never waits for a synthesis (Seat 4 M).
>
> **Handover.** One AQ4 equal-gain crossfade (AX18).
> - Offline renders, bounces in hosts that signal offline, and `render_cli` never use the provisional (AX5, condition 6).
> - It runs outside the diffuse gate.
> - Every submit passes `decide()` under `stateMutex_` with a monotonic (generation, stage) check.
>
> **Acceptance:**
> - AX47 (b) on the A4 set;
> - where L_p < L, the decay from t_mix,e,max to L_f is ≥ 18.7 dB in every band, asserted;
> - the L_p ≥ L branch (100 m low-α cube) builds the exact tail with no handover, asserted;
> - the parallel build is bit-identical to the serial one;
> - a `[pipeline]` test shows offline bypasses the provisional;
> - **record (h)**:
>   - restores in sequence on one thread, keyed and keyless, at 1, 4 and 8 instances;
>   - 100 m; 48 and 96 kHz; three OSes; a T60_max sweep of 2, 8, 12, 20, 35 and 50 s;
>   - printed: per-instance time until audible, and the time from provisional to exact;
>   - any 8-instance run over 5 s is flagged in print, not asserted.
>
> **Listening item L4:** a blind held-chord ABX of the provisional against the exact tail (T60 8 s, fully wet, 16 trials, ≥ 12/16 = detected), run with the AX47 ABX in 07c-2.
>
> **D1** (early part alone) is used only for tailless (AX22 fallback) scenes.
>
> **Long-T60 corner.** Where the interim is the full tail, condition 9's gate closure follows its split clause: phase-07d (FM-2′).
>
> **Reversal (back to the board, with 07d's candidates first):**
> - the gate fails at L_p ≤ 3.82 s;
> - the condition 11 trace shows a hang, not-responding state or time limit at ≤ 8 instances;
> - an 8-instance Windows load at the rated corner takes over 5 s;
> - a common host does not signal offline by default;
> - the L4 ABX detects the cut.
>
> **Recorded for Phase 10:** D5 restricted to edits within 5 % (Seat 9) and D6.

Rationale column: K2, K17′, K18′, K15′, K20–K23; D1, D2 and D3\*″ vetoed; FM-2′. Phases: 07c-1, 07d, 08, 09, 10, 13.

## 8. Phase-file and plan edits

**phase-07c-1:**
- **L56:** "…off the synchronous restore, prepare and `reset()`, except the stage-1 solve at keyless loads (AX48, FM-3′) and the AX49 interim tail where no valid IrSet is current (FM-2′)."
- **Condition 7 (L79–80, L84):** replace "measures restore without the solve and the synthesis" with "measures the restore as AX48/AX49 build it: ISM + matching + the AX49 interim tail + mix, plus the stage-1 solve on keyless restores".
- **Condition 9:** replace "after both moves … with 10–20× headroom" with: "after both moves the restore gate measures ISM + matching + the AX49 interim tail + mix (keyless: plus the AX48 stage-1 solve) under the unchanged worst-of-10 / 14 × worst ≤ 30 s rule, with headroom as measured (record (h)). Where the interim is the full tail (L_p ≥ L), an entry that still fails stays in the register with 'closes at' phase-07d (this condition's split clause; FM-2′)."
- **A2:** the same content: never the diffuse solve except FM-3′; the gate as in condition 9; register form, with entries that stay open naming 07d.
- **A4:** the AX47 (a)/(b) tests, the AX49 acceptance, and BRAS CR3 (Seat 9).
- **A7:** state v2 per AX48, with a five-part key.
- **A8:** the other-`outputMode` restore test; the keyless first IrSet carries a tail; a Π mismatch is keyless.
- **F3/F5:** cite AX47–AX49.
- **New record (h)** as in AX49.
- **New listening item L4:** "Reopen a saved 100 m project and play at once: the tail is there from the start; no level jump when it settles. Blind held-chord ABX as in AX49."

**New `docs/phases/phase-07d.md`** (size S–M; depends on 07c-1; BUILD_PLAN status row):
- **Scope:** close the AX38 4c macOS and Windows entries at the long-T60 corner.
- **Candidates:**
  - the constructor-spectra cache (bit-identical);
  - parallel band-pair synthesis (bit-identical);
  - a capped interim length on the K23 shared-history fact (convene Seats 1, 3, 5, 6, 7 and 9; Seat 9's L_p ≥ 0.31·T60 condition and Seat 1's depth ruling re-rated);
  - D4 in unit-decay form (Seat 4 rating);
  - the cheaper generator (output-changing; golden round; AQ10's "not optimised before Phase 13" read by the board).
- **Inputs:** record (h)'s T60 sweep and the S5/S7 long-corner ratings.
- **Release premise:** BUILD_PLAN premise P1 — if 07d lands after the first release, phase-13 item 3 fires.
- **Register:** the AX38 4c register's macOS "closes at" names 07d, and the Windows remedy names 07d.

**phase-07c-2:**
- the class (c) decision bound by AX47;
- the load fallback;
- the W_max raise makes v2 states keyless (E_prec);
- Seat 2's prefix check;
- the AX47 and L4 ABX runs.

**phase-08/09:** the provisional uses the same `tailSeedForOutput` and decorrelation as the exact tail; the AX44/AX48 test is extended to stereoSpeakers; a mode switch never re-solves or waits.

**phase-10:**
- record (g) feeds AX38 (v);
- D5 within 5 % and D6 are recorded alternatives;
- Seat 1 rules on automation-driven steps.

**phase-12:** presets never carry E_b.

**phase-13-1/13-5:**
- AX48's mismatch policy, including the build-id question;
- the fingerprint-failure block (Seat 7);
- the condition 11 results feed AX49's reversal;
- a v1 build rejects v2 state;
- wording: never "opens instantly"; no cross-machine bit-identity claim;
- the memory finding (2.25 GB at 8 × 96 kHz) goes to the memory budget, never an instance cap.

**AX38 (i):** if its classes lack the ordering, the stage-1 synchronous class gets priority (Seat 5's K2 condition; a plan default, changed by this decision).

## 9. FOR MAISARA

**FM-1 (AX18 scope): restated with the row-48 correction.**
- **Question:** does AX18's equal-power rule for restores cover the settling step after a restore?
- **Answer:** no. Same-scene interim-to-final steps are equal-gain.
- **Rests on:** NFR-6 ("restores the scene and its render exactly"); NFR-1; her AX18 choosing the law by IR relation.
- **Reasoning:** the two renders are the same scene with ρ ≥ 0.993 over the played window. Equal-power puts +3 dB mid-fade, a level that is neither the old render nor the restored one.
- **Options:** equal-power strains NFR-6 and NFR-1; equal-gain serves both.
- **What would make her veto it:** the literal reading that "every restore-related switch is equal-power".
- `AMENDS her decision of 2026-11-08: "accepted, merge with no ci"`

**FM-2′ (H1-F2: gate content, prepare, the 07d clause).**
- **Question:** may the restore gate include the AX49 interim tail? May a prepare with an fs change build it synchronously? And where the interim is the full tail, does condition 9's gate closure move to 07d?
- **Answer:** yes, to all three, exactly as worded in §8.
- **Rests on:**
  - the NFR preamble ("Accuracy is the top priority; … must stay usable");
  - NFR-2 ("acceptable when they buy accuracy");
  - NFR-1 and NFR-6;
  - H1-F2's own text: "never silence where a tail existed", and "If this phase's loop finds condition 9 does not fit here, a `phase-07d.md` … is created";
  - BUILD_PLAN premise P1.
- **Reasoning:**
  - At T60_max 50.5 s, any interim tail that is EDT-faithful costs about the full synthesis (K22). The cheaper interims are vetoed (D1) or unrated (capped).
  - The PRD ranks accuracy first and accepts the cost when it buys accuracy. No restore is longer than before 07c (D9-L6).
  - The plan's own split clause, not a new rule, carries the remainder to 07d.
  - A prepare with an fs change has no valid IrSet, so the only alternative there is D1.
- **Options:**
  - the literal gate (≈ 0.15 s) breaks NFR-6 and NFR-1 at every load (no tail, or D1);
  - a capped interim now is unrated against NFR-1 and the seats' conditions;
  - D3\*‴ with 07d serves NFR-6 and NFR-1 and spends NFR-2's allowance, inside the preamble's "usable" (30 s convention, register form).
- **What would make her veto it:** reading "usable" as condition 9's 0.15 s target, binding in 07c-1.
- `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."`

**FM-3′ (A2 / AQ10 (C) at keyless loads): citations corrected.**
- **Answer:** as in file 9.
- **Rests on:** NFR-6; NFR-1; the NFR preamble (in place of NFR-2); NFR-2, which accepts the cost because it buys accuracy.
- **Options:** K1 is vetoed (Seats 1, 3, 9) and strains NFR-6; K2 serves NFR-6 and NFR-1 at ≤ 144 ms per instance, on keyless loads only.
- **What would make her veto it:** reading AQ10 (C)'s "asynchronous" as covering every restore.
- `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."`

**FM-4′ (D-C1 acceptance).**
- **Question:** do the NFR preamble, NFR-6 or NFR-2 point to C3 (0.5 dB) over C5‴ (1 dB)?
- **Answer:** no. AX47 stays at 1 dB.
- **Rests on:**
  - NFR-1: "Pass thresholds come from the Expert" (Table 6.1's 1 dB jnd; Seat 1's ruling, as phase-07c-1 L40 assigns);
  - NFR-6;
  - NFR-2, read correctly: it accepts longer holds that buy accuracy, so it does **not** count against C3.
- **Reasoning:**
  - In 07c-1, every source is ≤ 0.06 dB by construction or ≤ 0.23 dB under the A4 test (§2), so C3 and C5‴ give the same product unless δ ≥ 9.
  - They differ only for 07c-2's statistical source, where the ABX re-decides 0.5 against 1 dB before that source exists.
- **Options** (one line each):
  - C5‴ serves NFR-1 (the Expert's threshold) and NFR-6 at the jnd;
  - C3 serves NFR-6 more tightly and, under NFR-2, costs only accuracy-buying holds in 07c-2;
  - C2 serves NFR-6 but strains NFR-1 (no Expert threshold for steps it cannot bound);
  - C1 strains NFR-6 (unbounded recorded steps);
  - C4 is vetoed.
- **What would make her veto it:** the preamble and NFR-6 read as "always the tightest feasible bound".
- Amends nothing.

## 10. Summary

| id | decision | state | worst-off | sum | conf. | PRD bound | corpus basis | reversal |
|---|---|---|---|---|---|---|---|---|
| D-C1 | AX47 C5‴: 1 dB per band, tail window; classes (a)/(b) only in 07c-1 | revised | 2 (S3 later) | 10 | medium | NFR-1, NFR-6 | Table 6.1; Eq. 6.4/6.5/6.7 | 07c-2 ABX → 0.5 dB |
| D-C2 | AX48 B4-G′ + gate priority | stands | 1 | 13 | medium | NFR-6, NFR-8, condition 9 | — | record (h) |
| D-C3 | AX48 A1′ + Π (five-part key) | stands, clause repaired | 1 | 11 | med-high | NFR-6, FR-LIC-1 | — | post-release policy |
| D-C9 | AX49 D3\*‴: L_f = t_mix,e,max + 0.312·T60_max; exact tail synchronous where L_p ≥ L; D5 bridge on T60 edits; parallel emitters; long-T60 gate → 07d | revised | 2 (S1, S6, S7, S8, S9) | 23 | med-low | NFR-6, NFR-1, NFR-2, preamble | Eq. 6.4, Table 6.1 | the five triggers in AX49 |
| FM-1, FM-2′, FM-3′, FM-4′ | §9 | for Maisara | — | — | medium | as cited | Eq. 4.15 | as cited |

**Challenges to settled decisions:** FM-1, FM-2′ and FM-3′ (§9).

### Decided for Maisara

- **AX47:** settling may move the reverb by at most 1 dB per band. In 07c-1 every source is exact or within about 0.2 dB. Statistical sources wait for 07c-2. PRD check: NFR-1, NFR-6, NFR-2; C3 equal in 07c-1; C2 and C1 strain NFR-1/NFR-6; C4 vetoed. Seat 3 gave most (07c-2 work); it gets the class (c) decision in 07c-2.
- **AX48:** the solved room level is saved with a five-part key, including the platform. A project opened on another OS or sample rate re-solves at load in about 0.1 s and plays its tail at once. PRD check: NFR-6, FR-LIC-1, NFR-8; B4+K2 and B2+K2 are costlier. Seats 5 and 7 gave most (keyless load time); they get record (h) and gate priority.
- **AX49:** a reopened project has a real tail from the start, cut where it is ≥ 18.7 dB down, then settles to the exact one. Very long rooms load as today and are fixed in a new phase 07d. Edits keep the old decay briefly. PRD check: NFR-6, NFR-1, NFR-2, preamble; the restricted bridge is not lower; D4 unrated. Seats 7 and 9 gave most (load time; edit decay); they get the Windows 5 s check, 07d and Phase 10.
- **FM-1:** same-scene settling uses equal-gain. `AMENDS her decision of 2026-11-08: "accepted, merge with no ci"`
- **FM-2′:** the restore gate counts the interim tail, a sample-rate change builds it at once, and the longest-reverb case moves to 07d under her own split clause. `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."`
- **FM-3′:** the synchronous solve runs only at loads with no usable saved level. `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."`
- **FM-4′:** the bound stays at 1 dB rather than 0.5 dB. Amends nothing.

**NEEDS MAISARA:** none. The contradiction the orchestrator anticipated is settled by her own condition 9 split clause (FM-2′). It would become case (a) only if the interrogator finds that clause does not reach a partial misfit. Even then my recommendation is the same.

**Files:**
- `/home/user/makroof/docs/review/phase-07c-1/9-decider-decision-r2.md`
- `/home/user/makroof/docs/review/phase-07c-1/11-interrogator-on-file9.md`
- `/home/user/makroof/docs/review/phase-07c-1/10-seat1-r3.md`, `10-seat3-r3.md`, `10-seat5-r3.md`, `10-seat6-r3.md`, `10-seat7-r3.md`, `10-seat9-r3.md`
- `/home/user/makroof/docs/review/phase-07c-1/8-orchestrator-provisional-cost.md`
- `/home/user/makroof/docs/phases/phase-07c-1.md`
- `/home/user/makroof/docs/BUILD_PLAN.md` (L115, L138, L158)
- `/home/user/makroof/src/sim/tail/MixingTime.h`
- `/home/user/makroof/src/sim/Engine.cpp`
- `/home/user/makroof/src/sim/conv/CrossfadingConvolver.h`