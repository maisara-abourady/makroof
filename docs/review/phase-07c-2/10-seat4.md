<!-- Saved by the orchestrator from seat 4's report, 2026-11-22. -->

SEAT 4 POSITION, D-W3 (phase 07c-2, round 2): the ISM update held behind a running solve

**Summary.** I prefer H-2 (decouple). H-0 and H-3 I cannot live with as stated, both 2/2. H-1 I can live with at 1/2. H-2 is the only option where the binaural direct-path build gets its full 700 ms regardless of W. It is also the remedy 08-4 item 8 already prescribes for Phase 10. None of my ratings is veto-grade, but H-3 becomes 3 under the condition in section 6.

**Read:** the brief in file 8 §5; file 6 (row C-1); fact sheet part 3 (M2, m\* = 6). For Table 15.1 I relied on the researcher's reading (dossier R29) and interrogator correction 9. I did not re-open the corpus.

## 1. Reading

An edit that arrives during a builder solve waits for that solve. My question is what this does to the update of the binaural direct sound and early reflections in Phase 08, against AQ4's 700 ms yardstick.

Cues it triggers:
- **Missing dynamic cue:** the direct-path update waits behind work it does not need.
- **Over-resolved periphery:** a diffuse solve sitting on the critical path.

Two facts carry most of this:
- **Table 15.1 already separates the two parts.** Its 700 ms row is for the specular part (moves > 0.25 m). Its 3 s row is for specular plus scattering (moves > 1 m). The researcher reads it that way (dossier R29), and so does interrogator correction 9. A design that updates the specular part promptly and lets the diffuse level follow within seconds matches the table's own structure. The current hold puts both parts on the 700 ms clock.
- **08-4 item 8 already names this remedy.** It says the diffuse solve inside every rebuild "is what breaks" Table 15.1's 35 ms head-rotation row. The fix it names is "a Phase 10 AX that updates the specular and directional part without waiting for the diffuse solve". H-2 is that AX, brought forward. In binaural mode with AX3's yaw following the emitter centroid, an emitter edit changes the HRTF set (08-4 item 8). Under H-0 that HRTF change waits for up to one pool solve: locally 590 ms at ×5 and 810 ms at ×6.

## 2–4. Ranking, tension now and later

| option | label | now | later | reason |
|---|---|---|---|---|
| **H-2 decouple** | prefer | 1 | 1 | The binaural B1′ build (new image sources and HRTFs over the held E_b) gets the full 700 ms, and AX33's 20 ms cadence target, at any W. It meets 08-4 item 8 in advance. The held E_b is shared by both ears (AX39), so adoption is one equal step in both ears: a level change, not a spatial one [Inferred]. Now 1: it is the larger threading change (Seat 5's to cost). Later 1: under continuous automation every solve's scene may be stale at adoption, so the stale-E_b exposure is the same as H-1's (see section 6). |
| **H-1 cancel-on-edit** | can live with | 1 | 2 | The direct path updates after cancellation at `run.stop`. The time to reach a stop point is unmeasured and adds to the binaural hold. Later 2: under continuous automation the held E_b plays until the automation stops. That held level is a stale direct-to-reverberant ratio, which is a distance cue, in both ears [Inferred]. M7b gives the fraction. |
| **H-0 no change** | cannot live with as stated | 2 | 2 | In binaural the hold is the rest of the solve plus the binaural image-source build. That build is a Phase 08 unknown and heavier than omni [Hyp]. At ×5 omni, 590 ms of solve leaves about 110 ms of the 700 ms for the binaural image sources and BRIR assembly. The omni projection already fails at ×6. Later: if Phase 10 ships the 08-4 item 8 AX after W is pinned at ×5 or less, W is re-raised. That means a second golden round in omni and binaural, after the 08-4 freeze. Cost: a full binaural golden round. |
| **H-3 relax U3** | cannot live with as stated | 2 | 2 | Read across the whole update, it lets the specular and direct-path update, and with it the HRTF-set change under AX3, lag past 700 ms. Direction is carried by the direct sound. This costs my criterion 1, cue survival. Evidence arrives at 08-4 item 8. |

## 5. Evidence

- **Table 15.1 rows (700 ms specular; 3 s specular plus scattering):** Vorländer §15.3, Table 15.1, as read by the researcher (dossier R29) and the interrogator (file 6, correction 9). It is a VR filter-update proposal, so its application here is by extension.
- **08-4 item 8 remedy and AX3 HRTF-set change:** `docs/phases/phase-08-4.md` L32–47.
- **The hold mechanism:** file 6, row C-1, from the code.
- **Hold durations (590, 810 and 813 ms at ×5, ×6 and ×8):** file 8 §2, local Linux, not CI. M7 is pending.
- **Binaural image-source and BRIR build cost:** not measured; Phase 08 is not built. [Hyp] that it exceeds omni. No number exists, and I invent none.

## 6. Conditions of acceptance

- **H-0 → 1/1:** a pinned W at ×5 or less, recorded with the 08-4 item 8 AX planned for Phase 10. The W re-raise and the binaural golden re-render become a named row in the debt register.
- **H-1 → 1/1:** measure cancellation latency (edit to `run.stop`) inside M7, and publish M7b's completion fraction. Under continuous automation, a solve completes at least every 3 s (Table 15.1's specular-plus-scattering row, applied by extension). Seats 2 and 3 set the rule.
- **H-2, later 1 → 0:** when a solve ends on a stale scene, the result is either adopted if its scene is newer than the held E_b's, or a completion guarantee as for H-1 applies, so the stale level is bounded. This is [Inferred]; the adoption semantics belong to Seats 2 and 3, determinism to Seat 5.
- **H-3 → 1/1:** relax the 700 ms only for the diffuse level, never for the specular or direct path or for updates driven by orientation or HRTF. In substance that is H-2's split. **If H-3 relaxes the specular update too, my later rating becomes 3**: it would put the HRTF update behind the solve.

## 7. Debt (07c-2, 07d, 10-1, 13)

- **H-2:** it commits 07c-2 or 07d to the threading change and its TSan tests. It removes the need for 10-1's 08-4 item 8 AX. Undoing it means returning to the serial builder, which is a code revert. Evidence arrives at M7 on CI and at 08-4 item 8.
- **H-0:** it commits 10-1 to the AX plus a W re-raise round after 08-4. Evidence arrives at 08-4 item 8 and at M7.
- **H-1:** it commits 13 to a starvation record under the AX38 (iv) automation patterns. Undoing it is cheap, a parameter or rule change.
- **H-3:** it commits 08-4 to measuring against a relaxed limit. Evidence arrives at 08-4 item 8, and the decision returns there if the 35 ms row applies.

## 8. Hand-offs

- Threading topology, gate and TSan: Seat 5.
- Adoption rule and determinism of the discarded solve: Seats 2 and 3.
- Audibility of the stale diffuse level during automation: Seat 1.
- Whether 700 ms remains AQ4's yardstick (Expert-owned, Q4 under NFR-3): the decider.

## 9. Premortem

H-0 ships at ×5. At 08-4, a binaural emitter drag in a large capped room shows the HRTF and early-pattern update lagging about 700 ms behind the drag. Maisara hears the image trail the cursor on headphones. Then Phase 10 has to decouple and re-raise W after the binaural goldens are frozen.

Files read:
- /home/user/makroof/docs/review/phase-07c-2/8-decider-rebuttal-r2.md
- /home/user/makroof/docs/review/phase-07c-2/6-interrogator-on-file5.md
- /home/user/makroof/docs/review/phase-07c-2/2-fact-sheet-part3-m2.md (L1–181: the m\* table and the raw lines for the three cubes and layout 4 default)
- /home/user/makroof/docs/phases/phase-08-4.md
