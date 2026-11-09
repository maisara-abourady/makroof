# Seat 9 (room acoustician) — positions on D-T1, D-T2 and D-T6

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

SEAT 9 POSITION

Corpus is present (rev c1b171fe). My persona's dated assumptions are not contradicted by the PRD here. My ratings depend on these proposals:
- **D-T4a ceiling.** T1-A fails CR4 at any ceiling below 2.53 GB, and 100 m at any rated ceiling.
- **D-T5.1, all 8 bands.** My concerns about the outer bands wait on C3 and C9.
- **D-T5.2 and D-T4b/c.** My ratings do not change with them.

---

## D-T1: formulation, seed, path count, tolerance, case set, near-listener handling

**1. Reading.** The question is how `src/sim` computes the diffuse E_target, and how it is checked against references. It triggers these cues:
- coefficient and reference provenance (§4 row 8, C2);
- the listener position and the direct, early and late channels (C1 step 1);
- large venues near 100 m;
- real listeners against walls.

**2–4. Ranking and tensions.** Ratings are now / later.

| sub | option | label | now | later | reason |
|---|---|---|---|---|---|
| 1.1 | **T1-F** | prefer | 1 | 1 | Covers AX6 in <2 MB. Agreement is ≤0.087 dB (≈0.09 jnd of G), but only in 500 Hz–2 kHz, with no published validation (RQ-T1-4). Evidence arrives at C3, C7 and the nightly BRAS run; undoing it means fixing the estimator, not rewriting. |
| | T1-B | can live with | 1 | 2 | Identical to the reference, so it carries the reference's ℓ error: 4.75 % (0.20 dB) at the layout-4 edge. ℓ = 2.5 m is as large as or larger than every dimension of `dead_booth` (2.5×2.0×2.2 m). A rebuild takes ≈9 s in the AQ10 room and minutes to hours at 100 m [Hyp, 2 ns], so large-venue presets can't be A/B'd in a session (C3 step 4). |
| | T1-A | **cannot live with** | 3 | 3 | Needs 2.53 GB for CR4, a measured BRAS room, and 1.53 GB for the AQ10 fallback. At 100 m it needs 3–6 TB, which forces a range limit that loses cathedrals and arenas. |
| 1.2 | **S-2** | prefer | 0 | 0 | tailSeed ensembles average out the Monte Carlo deviation, so a BRAS comparison sees the model's mean. ~1 SE is ≤0.08 dB, far below 1 jnd. |
| | S-1 | can live with | 0 | 1 | A fixed per-scene offset sits inside every AX11/AX19 ensemble, and its σ is left out of the validation spread. |
| 1.3 | **N-3** | prefer | 0 | 1 | A fresh disjoint sample avoids F12's low-mean stopping bias (F14's design). |
| | N-2 | can live with | 1 | 1 | Diagnostics catch the F11 pattern. The stopping bias is unquantified. |
| | N-1 | **cannot live with** (under NW-1) | 3 | 3 | C4 at 32 000 paths reads −1.06 dB at the W1 corner and −3.9 dB at the layout-4 edge. That is 1–4 jnd, silent because N-1 only reports diagnostics. Under NW-3 the rating drops to 2/2. |
| 1.4 | **Tol-2** (0.25 dB) | prefer | 0 | 1 | ¼ jnd, matching gate (B)'s δ. The reference's own ℓ term must fit inside it in the small rooms. |
| | Tol-3 (0.1 dB) | can live with | 1 | 2 | 0.1 dB is 2.3 %. If C9 shows the outer-band or small-room ℓ term exceeding that, a correct implementation fails, which invites re-seeding (tuning). |
| | Tol-1 (1 dB) | **cannot live with** | 2 | 3 | τ = 1 jnd would admit an implementation error as large as the layout-5/6 correction itself (−1.17/−1.16 dB, phase-05b2 §0.1). It also makes B6-2 = 1.43 dB, more than 1 jnd, so "nothing audible changed" cannot be certified. |
| 1.5 | **CS-3**, or my variant **CS-2 in per-PR CI + 30 BRAS pairs nightly** | prefer | 0 | 0 | The BRAS pairs are the only agreement cases with real proportions and per-band α. |
| | CS-2 | can live with | 1 | 2 | CR3's −1.18 dB switch effect would then be checked only against measurement, where estimated α (spread ±0.1 at low frequencies) hides a 1 dB implementation error. |
| | CS-1 | can live with | 2 | 2 | All 20×30×10 m: no small room, no real mixed α. |
| | **+CS-NW** | prefer (add) | 0 | 0 | Without it, no agreement case puts the listener within 0.5 m of a surface. |
| 1.6 | **NW-3** (ρ = 0.5 m) | prefer | 1 | 1 | See the physics below. |
| | NW-2 | can live with | 1 | 1 | Bias of 1–3 % (≤0.13 dB), but little variance gain at edges and corners. |
| | NW-1 | can live with | 1 | 2 | Unbiased, but it buys precision the physics can't support. Near walls no reference can check it: the tracer's r_d = 0.5 m sphere cuts the wall (F5), and ref_hybrid is not certified there (C4). |

**D-T2 effect.** Under L2-F2, N rises 33×. That means more N_max escalations near walls (7.1 M paths at the W1 wall with NW-1). My ranking does not change, and the case for NW-3 gets stronger (it cuts variance 4–7×).

**B9: is a GA diffuse gather at 0.1 m physically meaningful?** Below ~1.7 kHz, no.
- **Corpus.** Kuttruff §2 Eq. 2.50 and Fig. 2.11: in a diffuse field the squared pressure in front of a rigid wall rises to 2× at the wall, and the phase effects reach about λ/2 out from it.
- **My arithmetic at 0.1 m, with 1 + sin(2kx)/(2kx):**

  | 125 Hz | 250 Hz | 500 Hz | 1 kHz (tone) |
  |---|---|---|---|
  | +2.9 dB | +2.7 dB | +1.8 dB | −0.6 dB |

- **GA cannot model this.** No option models it, and none should: it is Seat 2's ground, and fixing it per scene would break NFR-8.
- **Size of the remedies against it.** NW-3's +0.03 to +0.09 dB and NW-2's ≤0.13 dB are less than 1/20 of that unmodelled term.
- **Why the 0.5 m point is more honest.**
  - At 0.5 m, λ/2 is 343 Hz, so the GA gather is valid in octave bands from about 350 Hz up.
  - ρ = 0.5 m equals the tracer's r_d = 0.5 m (phase-05b2 §0.1), so near-wall cases become checkable against the independent tracer.
  - The GA mean barely depends on d (F3(2), derived; C4: ≤0.09 dB), so the tail "stops following" the listener by under 0.1 jnd.

**Real positions.**
- A head centre at 0.1 m puts a head of radius ≈0.09 m about 1 cm from the wall [Inf]. That is a validator floor, not a listening position.
- Back-row heads sit about 0.3–1 m from the rear wall [Hyp].
- Booths under ~10 m³ are outside my incident coverage (§18). `dead_booth` is ≈11 m³, at the edge.

**Large venues.**
- No reference covers 100 m, under any option.
- Real large venues are elongated (cathedral naves), not 100 m cubes [Inf].

**5. Evidence.**
- Vorländer Table 6.1: G jnd is 1 dB.
- Vorländer Fig. 11.38: diffuse rain uses a detector *sphere*.
- Kuttruff Eq. 2.50 and Fig. 2.11 (arithmetic redone above).
- C4 and C8 [Obs, in-repo]; builder evidence §3.
- F3 [derived, unsourced]; F5, F11, F12, F14 [Peer].
- §19 "ISO 354 reproducibility poor" (coefficient spread).
- `stone_box` fixture: 20×12×10 m, α 0.05.

**6. Conditions.**
- **T1-A:** nothing lowers it while CR4 doesn't fit.
- **T1-B → 1:** a finer-ℓ reference (≤0.625 m, cheap there) with a halving check below 1 % for every room with a dimension ≤ 2ℓ.
- **N-1:** becomes N-2 or N-3 (adaptive N), or is paired with NW-3 plus escalation; then 2.
- **Tol-1 → 1:** decouple D-T6 from τ and use a separate τ ≤ 0.25 dB.
- **Tol-3 → 1:** C9 shows the reference ℓ term below 1 % in the outer bands and in small rooms.
- **CS-2 → 1:** the BRAS pairs run nightly.
- **CS-1 → 1:** add the Phase 04 small rooms, with the reference at finer ℓ.
- **NW-1 → 1:** escalated cap hits are flagged in diagnostics as "near-wall, unreferenced".
- **For NW-3 itself:**
  - ρ must stay below 0.75 m, so the gather region stays non-empty at AX6's 1.5 m minimum.
  - The AX row states it as a GA validity limit.
  - Diagnostics report when the clamp is active.
  - CS-NW adds a 0.3 m position.

**7. Hand-offs.**
- **Seat 2:**
  - near-wall pressure doubling that GA leaves out;
  - NW-2 with h = ℓ against AX29;
  - whether r_d = 0.5 m in the tracer is compatible with ρ.
- **Seat 4:** a head at 0.1 m against a free-field HRTF.
- **Seat 1:** audibility of 0.03–0.09 dB.
- **Seat 5:** CI cost of CS-3 and the nightly split.
- **Seat 6:** whether users see the clamp.
- **Maisara:** any AX6 clearance change.

**Checks for the orchestrator and the researcher.**
- **(a)** ref_hybrid's patch grid when a dimension is ≤ ℓ (`dead_booth`, `small_room`, `edge_values` 1.5 m), and the 2.5 → 1.25 → 0.625 m change there.
- **(b)** NW-3 against a converged point estimate with the listener 0.1 m from the *absorbing* face (layout 4 floor, layout 5 wall). In W1 the near face is never the absorber.
- **(c)** C7: one offline tracer run on an elongated large room with an absorbing floor, about 100×35×30 m (N₀ = 254·V ≈ 2.7·10⁷).
- **(d)** Researcher: Heinz 1993 or Schröder 2011 on detector radius.

**8. Premortem.** If NW-1 and N-1 win, a producer who parks the listener in a corner gets a tail 1–4 dB low in an absorbing-floor room, with no reference able to show it. The nightly BRAS run never places a listener there, so a user's A/B against a real room catches it first.

---

## D-T2: resolution parameter

**1. Reading.** The settled < 1 % rule has to be restated for an estimator. 1 % = 0.043 dB, which is 1/23 jnd: a numerical rule, not a perceptual one (§4 row 8).

**2–4. Ranking and tensions.**

| option | label | now | later | reason |
|---|---|---|---|---|
| **L2-F2** | prefer | 0 | 1 | A repeatable criterion. It costs more escalations near walls; NW-3 cuts them 4–7×. |
| L2-F1 | can live with | 1 | 2 | Pass or fail is a coin flip at a fixed seed, and a fail invites re-seeding (tuning). |
| L2-P (if T1-A or T1-B) | can live with | 1 | 2 | Not certified near walls (4.75 %), nor where ℓ ≥ the room's dimensions; outer bands still pending (C9). |

**5. Evidence.** C4; phase-05b2 §3 D-T2; AX36.

**6. Conditions.**
- **L2-F1 → 1:** apply AX11's threshold/3, which makes it L2-F2.
- **L2-P → 1:** check (a) above, plus C9 below 1 %.

**7. Hand-offs.** Cost to Seats 3, 5 and 6.

**8. Premortem.** Under L2-F1 a correct build fails on a seed, someone changes the seed, and the interrogator finds the tuning.

---

## D-T6: regression bound in uniform-α rooms

**1. Reading.** The question is which rooms prove that "nothing audible changed", and against what bound. It triggers the occupancy and provenance cues.

**Are real rooms uniform-α?** Almost never once furnished or occupied:
- The floor carries the audience, seating or carpet, and audience area dominates absorption (§19, Beranek).
- Kuttruff §5.7 calls the absorbing-floor layout a crude model of most auditoria.

Near-uniform rooms do exist: reverberation chambers, and empty stone or concrete shells (chapels, stairwells, tanks, tiled bathrooms). `stone_box` (α 0.05, T60 ≈6 s) stands for that class. W1 is a synthetic benchmark.

**Is RS-2 representative?** Of the physics class only:
- 4 of its 5 rooms are 20×30×10 m, and all are ≥2 400 m³;
- s ranges 0.1–0.4;
- no small room, no uniform fallback, no s > 0.4.

**2–4. Ranking and tensions.**

| option | label | now | later | reason |
|---|---|---|---|---|
| **RS-2** | prefer | 0 | 1 | Covers the uniform-α class, but one size class only. |
| *my option RS-2+* | prefer | 0 | 0 | RS-2 plus one synthetic small uniform room, e.g. 3×2.5×2.5 m, α 0.03, s 0.1, fixed before C11. A short mean free path is where 0.43 dB is least proven. |
| RS-1 | can live with | 1 | 2 | One room, one s value. |
| **B6-1** | prefer | 0 | 1 | True to the validated model, with no extrapolation. |
| B6-2 | can live with at Tol-2 (0.68 dB < 1 jnd) | 1 | 2 | 0.43 dB comes from one geometry (α 0.15, s ≤ 0.4). Outside that class it may fail a correct implementation. Under Tol-1 it becomes a 3 (1.43 dB). |
| **M-2** | prefer | 1 | 0 | The tracer is the only *independent* GA check of the realistic mixed rooms. |
| M-1 | can live with | 1 | 2 | ref_hybrid is the model being ported, so an error common to both stays invisible. |

**My prediction, written before C11.**
- `stone_box`: |ΔL_ref| ≤ 0.1 dB in 500 Hz–2 kHz (bracketed by the s = 0.1 case's +0.03 dB) [Inf].
- Both rooms: |ΔG| < 1 jnd.
- W1 is not a blind prediction: the prototype already shows +0.32 / +0.27 dB at 1 kHz (builder §3). The **interrogator** should check D-T6's "before any number" condition for W1.

**6. Conditions.**
- **RS-1 → 1:** add W1 and the s-cases.
- **B6-2 → 1:** paired with B6-1, or limited to the measured class.
- **M-1 → 1:** run the tracer on at least `club` and `concert_hall_box`.
- **M-2:** the orchestrator checks the tracer's 0.5 m sphere against `dead_booth`'s listener clearance.

**7. Hand-offs.**
- **Seat 2:** whether the hit-count residual depends on mean free path and s.
- **Seat 1:** the before/after report.
- **Seat 5:** the gate and the tracer runtime.

**8. Premortem.** Under RS-1 + B6-2 + M-1, a mixed-room error shared by the reference and C++ ships. A producer comparing the club preset against a measured club hears it first.
