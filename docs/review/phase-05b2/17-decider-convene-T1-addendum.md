# Decider — addendum to the D-T1/D-T2/D-T6 convening (D-T1.6 near-listener handling; amended options)

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

# Addendum to the decider's D-T1/D-T2/D-T6 convening

This addendum goes to the seats together with the original block. It brings the block up to date with C4, C5, C6, C8, C10 and the researcher's dossier. It changes:
- the T1-F and T1-B descriptions;
- D-T1.2 (determinism across machines);
- D-T1.3 (adds N-3 and the diagnostics);
- D-T1.5 (adds a near-wall flag);
- D-T2 (adds a caveat to L2-P);
- the D-T6 room set.

It adds one sub-question, D-T1.6 (near-listener handling). C3 (agreement in all 8 bands) and C7 (reference costs, 100 m check) are still running, and the seats should rate without them.

Sources: `16-orchestrator-C4-near-wall.md`, `14-researcher-T1-T2.md` (F1–F25; verdict NOT READY) and `tools/validation/data/phase05b2_dt1.json` (sections `c5`, `c6`, `c8`, `c10`).

## Option-block amendments (pass verbatim to every convened seat, after the original block)

**T1-F (amended description).** This replaces the convening sentence "its cos θ/r² term is unbounded near walls".

*What the researcher found:*
- Under AX6's 0.1 m clearance, every wall point is at least d from the listener and from all its lattice images. So a single-hit score is bounded by 1/(π d²), which is 31.8 m⁻² at d = 0.1 m.
- The variance is therefore finite. Below that bound, though, the scores are heavy-tailed (slope ≈ 5/3).
- This is the researcher's own derivation (dossier F3), with no published source. The particle-transport result that the variance is infinite assumes collisions arbitrarily close to the detector, which this geometry does not have (F1).

*What C4 measured (per emitter):*
- **Emitter at 0.1 m from a wall:** costs nothing.
- **Listener at 0.1 m from a wall, an edge or a corner, at 32 000 paths:** single paths carry 5–73 % of the estimate, and the mean can be low: −1.06 dB at the W1 corner, −3.9 dB at the layout 4 edge.
- **W1 room, 4 M paths:** the estimate converges to within 0.03–0.06 dB of `ref_hybrid` at 1.25 m. SE is 0.02–0.07 dB, VOV is 0.010–0.014, and a run takes ≈ 5 s per emitter.
- **Table 5.2 layout 4 at s = 1 (α = 1 floor, AX22 fallback):** near-wall listeners stay expensive under every remedy, at ≈ 1 M paths and ≈ 40 s per emitter for ≈ 0.1 dB.

*What the literature does not supply (RQ-T1-4 uninformed):*
- No published figure exists for the bias or variance of diffuse rain against radiosity or an exact solution.
- The literature shows only:
  - that the method belongs to a named class (F22);
  - run-to-run variance (F23);
  - an Eyring comparison (F24).
- T1-F's validation therefore rests on the in-repo agreement with `ref_hybrid` and the tracer alone.

*Continuity (C6, 101 points per sweep, largest step between neighbours over 8 bands):*

| sweep | at 8 000 paths | at 32 000 paths | N-2 | AX16 |
|---|---|---|---|---|
| source moved 1 m, W1 | ≤ 0.004 dB | ≤ 0.0014 dB | ≤ 0.006 dB | ≤ 0.0009 dB |
| source moved 1 m, layout 4, s = 1 | ≤ 0.037 dB | ≤ 0.015 dB | ≤ 0.018 dB (N changed 3 times) | ≤ 0.002 dB |
| room size ±5 %, W1 | 0.014–0.020 dB | 0.014–0.020 dB | 0.014–0.020 dB | 0.014–0.020 dB |

In the room-size sweep every column, AX16 included, shows the same steps, so the deterministic change of the room dominates there. The AX22 fallback switched in none of the sweeps.

**T1-B (amended cost, C8).** The time per generation is the number of pair-image evaluations multiplied by the cost of one. At the measured numpy rate of 21 ns per evaluation, W1's 10 generations take ≈ 99 s. At an assumed optimised C++ rate of 2 ns [Hyp]:

| room | per generation | per rebuild |
|---|---|---|
| AQ10 room | 0.92 s | ≈ 9 s (10 generations) |
| AQ10 room, fallback | 11.6 s | – |
| CR4 | 6.3 s | – |
| 100 m | 1 454 s | – |
| 100 m, fallback | 7 977 s | – |

So at 100 m a rebuild takes minutes to hours.

**D-T1.2, added to both S-1 and S-2: determinism across machines.** Bit-identical results are achievable only on the same platform. That is all AX5 requires; across architectures AX5 asks for a residual within −100 dBFS.
- **What is identical everywhere:**
  - The integer stream of a counter-based RNG is identical on every platform (F15–F17). The published practice is a known-answer test on each target.
  - The integer-to-float conversion can be made exact, e.g. (u32 >> 8)·2⁻²⁴ (F18).
- **What differs:**
  - libm functions such as cos, sin and log, between MSVC, glibc and Apple (F19);
  - FMA contraction defaults, between gcc, clang and MSVC (F20);
  - `<random>` distributions, which are not portable (F16).
- **C5:** perturbing positions by 1e-9 m changed E_target by ≤ 2.7e-10 dB. Float32 path state changed it by ≤ 7.5e-8 dB. In both runs no path changed its face sequence. Results with 1, 2 and 4 threads were bit-identical.
- **Implied by the dossier (my reading):** a known-answer RNG test in CI, an explicit FP-contraction policy, and no `<random>` distributions.
- **Unquantified:** how often a path would take a different branch on another architecture.

**D-T1.3 (amended): every N rule carries MCNP-style diagnostics.** Per band:
- the relative error R;
- the variance of the variance (VOV);
- the slope of the tail of the score distribution, plus the score statistics needed to compute VOV.

These are F8–F10. They are recorded in `--diagnostics` and printed beside N and the SE.

What the sources say about these checks:
- **F7:** MCNP grades R < 0.05 as reliable for point detectors. The derived mapping is SE 0.33 dB → R 0.079; 0.083 dB → R 0.019.
- **F11:** in one documented MCNP case, a point-detector estimate passed on R alone while sitting 4× too low; VOV and slope caught it.
- **F10:** the slope test may fail until scores near the 1/(π d²) bound have been sampled.
- **F12:** a rule that stops on small SE tends to stop on low means.
- **F13:** sequential rules are valid only asymptotically, and need a minimum effort n*.
- **F14:** they can fail for heavy tails at finite N.

The N rules:
- **N-1 (amended):** a fixed N. Diagnostics are reported only.
- **N-2 (amended):** batches until R ≤ the target **and** VOV < 0.1 **and** slope > 3 in every band, after a minimum n*, or until N_max. Hitting the cap, or ending with a failed diagnostic, is recorded and escalated to Maisara with the scene.
- **N-3 (new, mine; F14's design):** two stages. A pilot of n* paths sets N from its SE and diagnostics. The final estimate then comes from a **fresh, disjoint** path range of length N in the same deterministic sequence, which avoids N-2's prefix-reuse stopping bias (F12). N_max and escalation are as in N-2.

**D-T1.5 (amended): new flag CS-NW, combinable with CS-1, CS-2 or CS-3.** It adds C4's three W1 near-wall listener positions (wall, edge, corner) to the chosen set. There the reference's 2.5 → 1.25 m change is ≤ 0.65 %, and the 1.25 m reference is used.

Layout 4's near-wall positions cannot serve as references: the reference changes by 1.18 % (corner) and 4.75 % (edge) per halving, and the 4 M-path estimate differs from it by +0.73 dB at the edge. Without CS-NW, no agreement case places the listener within 0.5 m of a surface.

**D-T1.6 (new): near-listener handling (T1-F only).** All three options are generic (NFR-8) and continuous in the listener's position.

**NW-1: point estimator, unchanged.**
- The model is unbiased. Cost near walls is governed by D-T1.3's rule and its diagnostics.
- Paths needed for SE 0.083 dB (C4): W1 wall 0.22 M, edge 1.6 M, corner 0.09 M; layout 4 1.4–47 M.
- Under N_max, such scenes ship with SE above target and may read low (F11). Cap hits are escalated.

**NW-2: near-field cells.**
- Within r_near = 1 m of a listener image, a hit is gathered through the exact solid angle of its wall cell of edge h, Ω/(πA), instead of cos θ/(πr²).
- In W1, bias is ≲ 1–3 % at h = 0.5–1 m (−3.0 / +0.1 / −1.2 % at a wall for h = 1 / 0.5 / 0.25 m).
- Variance falls 2–4× at a wall, and little at edges and corners.
- Under that agreement, the shipped E_target differs from `ref_hybrid` by the measured bias, so τ must cover it.
- Seat 2 should say whether h = ℓ mirrors `ref_hybrid`'s own gather; AX29 gathers through each patch's exact solid angle.

**NW-3: clamp the diffuse gather point.**
- Only the point where the diffuse energy is gathered moves, to ≥ ρ = 0.5 m from every surface. The specular entries, the window and t_mix,e keep the true listener position.
- E_target changes by +0.029 / +0.093 / +0.059 dB at the W1 wall, edge and corner. Variance falls 4–7× at equal path count.
- It is a model change near walls. Clamping is a known source of bias (F4, abstract only).
- It does nothing whenever the listener is ≥ ρ from every surface, which is true of every current agreement case.
- Layout 4 near-wall cases still need ≈ 1 M paths.

**Not offered:** a larger listener clearance in AX6. That is a contract change, so it would be Maisara's call.

**D-T2, L2-P (amended caveat).** R1 is certified at the AX28 and Phase 05 positions only. Near walls the reference converges slower: in W1, ≤ 0.65 % per halving; in layout 4, 1.18 % at the corner and 4.75 % at the edge (C4). So ℓ = 2.5 m is **not** certified for a listener near a wall in that room.

**D-T2, L2-F1/L2-F2 (added cost).** With the point estimator, SE 0.0145 dB needs 7.1 M paths at the W1 wall (C4). NW-2 and NW-3 lower this by their variance factors.

**D-T6, room set (amended, C10).** The uniform-α rooms are:
- `stone_box` (s = 0.1);
- the W1 AQ10 room (s = 0.3);
- the three (A) s-cases.

Every other fixture is mixed: `asymmetric_materials`, `classroom`, `club`, `concert_hall_box`, `dead_booth`, `edge_values`, `large_hall`, `living_room`, `medium_room`, `open_field`, `small_room` and W2. So **RS-1 = {`stone_box`}** and **RS-2 = {`stone_box`, W1, s-cases 0.1 / 0.25 / 0.4}**. B6-1 and B6-2 are unchanged. C11 is still deferred until D-T6 is decided.

## Changed brief lines (added to each seat's addendum)

**B1 (Seat 1)**
- Rate D-T1.6. Is NW-3's 0.03–0.09 dB shift, or NW-2's 1–3 % bias near walls, audible?
- Is an escalated near-wall estimate, possibly 1–4 dB low (C4, F11), a listening risk you can accept as escalated rather than blocked?
- Does N-3 change your agreement-test decision rule?

**B2 (Seat 2)**
- Rate D-T1.6. Is NW-2 at h = ℓ the reference's own gather? Is NW-3 still "the same model to a stated tolerance"?
- What reference can validate a listener near a wall when `ref_hybrid` is not certified there (C4)?
- Weigh RQ-T1-4's absence of any published validation, and T1-B's C8 times.

**B3 (Seat 3)**
- C6 continuity numbers.
- Under N-2 or N-3, the build time depends on how close the listener is to a wall.

**B5 (Seat 5)**
- Rate D-T1.2's cross-architecture note: known-answer test, FP-contraction policy, libm use, no `<random>`.
- Runtime cost of the diagnostics.
- Near-wall build times: ≈ 5 s per emitter in W1 with NW-1 at 4 M paths; ≈ 40 s in layout 4. Compare them with Challenge 1's ≈ 2.1 s per restore and with D-T4c's escalation.
- Cap-hit escalation for N-2 and N-3.

**B6 (Seat 6)**
- Placing the listener against a wall is an ordinary user action. Under NW-1 it costs seconds; under NW-3 the tail level stops following the listener within 0.5 m of a wall.
- Should the user see a cap hit?

**B7 (Seat 7)**
- What can public wording say ("validated") with no published validation of diffuse rain (RQ-T1-4) and an estimator with a standard error?

**B9 (Seat 9)**
- Real listeners near walls (booths, back-row seats against a wall).
- Is a geometrical-acoustics diffuse gather at 0.1 m physically meaningful, or is NW-3's 0.5 m clamp the more honest model?
- CS-NW.

## Knowledge inventory: status changes
- **K4 (near-wall behaviour):** now known from C4 and F3. F3 is derived and unsourced; C4 measures it.
- **K7 (T1-B time):** known in arithmetic from C8; the 2 ns rate is [Hyp].
- **K9 (determinism across machines):** known. Same-platform bit identity holds; identity across architectures is not guaranteed (F19, F20, C5).
- **K10 (continuity):** known from C6.
- **K15 (uniform-α fixtures):** known from C10.
- **K12 (statistical acceptance and stopping rules):** known for the checks (F7–F14). The size of the stopping bias is uninformed (F12).
- **RQ-T1-4:** remains uninformed. It needs Schröder 2011 or Heinz 1993/1994. If T1-F wins, its confidence is capped at medium.
- **New gap, informs D-T1.6 and CS-NW:** no reference is certified for a near-wall listener in concentrated-absorption rooms (C4, layout 4). C7 may help; otherwise it is recorded as a gap.

**CONVENE (addendum)**

Files:
- /home/user/makroof/docs/review/phase-05b2/16-orchestrator-C4-near-wall.md
- /home/user/makroof/docs/review/phase-05b2/14-researcher-T1-T2.md
- /home/user/makroof/tools/validation/data/phase05b2_dt1.json
