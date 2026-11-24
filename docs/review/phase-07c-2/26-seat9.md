<!-- Saved by the orchestrator from seat 9's report, 2026-11-22. -->

SEAT 9 POSITION

**1. Reading.** The ABX scene renders about 20 dB drier than the room its label names. Three questions follow: is the label honest, which room should carry the test, and does my 0.43 ceiling still hold. Cues it triggers (§4): first energy after the direct sound arrives at 0.38 s (ITDG); D/R at the seat compared with the diffuse field; coefficient and label provenance (S8); "RT right, room wrong" (W2).

**2. Ranking**
- **Label.** The decider's corrected label (file 24): *prefer*, with additions in §6. The old label "occupied mid-size hall envelope": *cannot live with*.
- **M3.**
  - S-B: *prefer*, made specific as layout-4 geometry with R0/S0/S1 unchanged and s = 0.25 on every face.
  - S-D (my addition): `concert_hall_box`: *can live with*.
  - S-A: *can live with* only on my conditions.
  - S-C (`listener_wall`): *can live with*, but it does not cure the dryness.
- **M2.** T-a: *prefer*, with a condition. T-b: *can live with*.
- **0.43 ceiling.** Keep it as the pre-registered ceiling, with its premise corrected on the record: *can live with*.

**3–4. Tension now / later**

| option | now | later | why |
|---|---|---|---|
| old label | 3 | 3 | Claims "hall" and "occupied" with no measured reference. Floor α = 1 is an absorbing plane, not occupancy by area. 6,000 m³ is recital-hall scale (TOC is 15,300 m³). |
| corrected label | 1 | 1 | Accurate. It lacks the comparisons that make the gap visible (§6). |
| S-A | 2 | 2 | ITDG 380 ms, against a first return within about 20 ms at row 15 in Beranek's good halls. D/R per emitter +10 dB, against −10 dB in the diffuse field at r/r_c 3.2. The tail sits about 10 dB under the direct sound, the least exposed corner of the scene space. Later: once B11 fills the early part (about 17.7 dB of missing energy, file 22), this stimulus no longer stands for anything the product renders, and 08-3 (item 15) inherits it. |
| S-B (s = 0.25) | 1 | 1 | Image geometry from file 22's positions, all [Inf; H]: ceiling image 23.6 ms, side-wall lateral 24.6 ms, first lateral about −5.8 dB re direct. That is a hall-like early structure. Expected per-emitter D/R about −2 to −5 dB ([Inf; M], details in §5). Cost: K3 unknown, minutes of rerun. |
| S-D `concert_hall_box` | 2 | 1 | 40 × 25 × 16 m, 16,000 m³, s 0.4–0.6, T60 about 2 s: near TOC (15,300 m³, 1.95 s occupied). But AX47 says "capped layout-4 scene", so this needs a /fix-plan change. Cap status unknown, and it is not validated either. |
| S-C | 2 | 2 | Still s = 1, so the early part is still empty. Listener 0.1 m from a wall at r = 20.13 m is not a seat. D/R ≈ +6 dB ([Inf]: direct −4.2 dB, tail about unchanged). |
| T-a | 1 | 1 | 2.009 s is a decay fit across the AX21 flat stretch, not a decay rate. Harmless because the ≥ 20 dB assertion governs and gaps ≥ 2.009 s also exceed 1.26 s. |
| T-b | 1 | 1 | It is the physical decay (tail T30 1.254 / 1.274 s against the 1.29 s target). It reseeds every stimulus. |
| 0.43 kept | 1 | 1 | Not binding on S-A (0.87 s against a realised 0.375 s). Roughly binding again on S-B. |

**5. Evidence**
- **D/R expectation.** Diffuse-field D/R = −20·log10(r/r_c), which gives −10.2 dB at r/r_c 3.22 (Kuttruff §5.6, Eqs. 5.43–5.45; r_c from Eq. 5.44). Measured per emitter: +10.7 / +9.7 dB. The gap to the label is about 20 dB (file 22). [corpus; code]
- **Eyring is not the physical T here.** For this layout (Kuttruff Table 5.2, case 4) the iteration gives 1.21 s against Eyring's 1.38 s, 12 % shorter. That is more than 2 RT JNDs of 5 % (Vorländer Table 6.1). A label that quotes "Eyring 1.29 s" quotes the engine's diffuse target, not a room prediction. [corpus]
- **Ceiling arithmetic, redone.** The 26/60 premise assumed the tail level at the end of speech equals the speech level (D/R ≤ 0) and a decay at T30.
  - Corrected form: t ≤ hold + (SNR − 20 − L_drop)/60 · T60_tail, with L_drop = 10·log10(1 + 10^(D/R/10)).
  - On S-A: L_drop = 13.3 dB, giving (46 − 20 − 13.3)/60 · 1.30 = 0.275 s. Adding file 22's 0.1 s hold gives 0.375 s, which matches the measured value. [Inf; H]
  - On S-B: L_drop is about 0.5–2 dB, giving about 0.53 s + hold, against 0.43 · T30 ≈ 0.56 s. The ceiling becomes about right again. [Inf; M]
- **S-B tail D/R estimate.** Assumes t_mix,e drops to the AX20 0.114 s. The tail from t_mix carries +10.2 − 5.3 = +4.9 dB re direct, less the measured 2–3 dB shortfall of the tail level (AX37). That gives D/R about −2 to −5 dB. [Inf; M]
- **Physics I could not source.** The 46 dB SNR is broadband while the assertion is made at 1 kHz [Hyp; researcher, R35 is not in the corpus]. Scattering values in real halls [Hyp; researcher].

**6. Conditions of acceptance**
- **Corrected label.** Add three things: "diffuse-field D/R at r/r_c 3.2 would be −10 dB"; "energy between direct and 0.38 s is −29 dB re direct"; "diffuse target, Eyring; Kuttruff Table 5.2 iteration about 12 % shorter for this layout; tail measured 1.25–1.27 s". Remove "hall" and "occupied" everywhere, the kit's `label` string included. Rating goes to 0/0.
- **S-A, to 1/1.**
  - The record names the scene class: "direct-dominated, D/R ≥ +10 dB at 1 kHz, early part empty". A non-detection is never generalised beyond that class (Seat 1 owns the wording).
  - The 08-3 rerun (item 15) is not done on this scene alone.
- **S-B, conditions to hold 1/1.**
  - Capped at m = 6, 7 and 8.
  - The tail window's specular share is 0, otherwise item 6 refuses (Seat 3).
  - K3 prints per-emitter D/R and ITDG before sealing.
  - If any of these fails, fall back to S-A on its conditions, not to S-C.
- **S-D, to 1/1.** A /fix-plan change to AX47's "layout-4" wording.
- **S-C.** No condition lowers it, because s = 1 is the fault.
- **T-a.** The manifest labels 2.009 s "heard-IR T30, ISO fit spanning the AX21 gap, not a decay rate", with the tail T30 beside it.

**7. Hand-offs**
- Seat 1: does the dry scene bias non-detection beyond item 13's wording, and how does a detection on S-A generalise?
- Seat 3: specular share in the tail window at s = 0.25; the 8 kHz tail T30 at +18 %.
- Seat 2: whether t_mix,e falls to about 0.114 s at s < 1, and the cap status.
- Builder: K3 for S-B and S-D.
- Researcher: the band basis of the 46 dB SNR.

**8. Premortem.** The risk is that S-A seals and 0.9 dB goes undetected, so the bound stays at 1 dB "for all scenes". Then, at 08-3 or after B11, a producer in an s < 1 hall preset hears the level step at the end of automation. Maisara would notice it first, on a listening checklist.

Files: /home/user/makroof/docs/review/phase-07c-2/24-decider-abx-r2-convene.md, /home/user/makroof/docs/review/phase-07c-2/22-drr-t30-check.md, /home/user/makroof/docs/corpus/kuttruff-room-acoustics.md (Table 5.2, §5.6), /home/user/makroof/tests/scenes/valid/concert_hall_box.json, /home/user/makroof/tests/unit/test_diffuse_wsweep.cpp (lines 86–102), /home/user/makroof/tools/ci/abx_kit.py (lines 120–147).
