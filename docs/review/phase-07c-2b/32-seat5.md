# 32: Seat 5 on 07e's AC clause (M3-H follow-up)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 5 POSITION (follow-up on M3-H, interrogator Q5 and Q1; for the orchestrator to save as /home/user/makroof/docs/review/phase-07c-2b/32-seat5.md)

**1. Reading.** Two questions. First, which board clause I accept at the end of the 07e AC (file 30 §5 Item A, L234). Second, whether my H4+G and H3+G cells hold now that 07e is larger. Cues: §4.5 (who owns the baseline when another phase changes the output) and criteria 2 and 4 (determinism; a gate one person can check mechanically).

**On Q5.** I did not write the decider's clause. My 29-seat5 §4 sent this kind of red to "an update with a stated reason". The two texts each leave something out:
- **Decider's clause:** it does not say who owns the red, so it is unclear who clears it.
- **My earlier text:** it would let the JSON be updated without anyone asking whether the ruling still holds. A change in a discrete field, such as `ismFallback`, k_real crossing 19, or the both-near or capped flag, can overturn 07e's ruling. That is a determinism matter, and a stated reason does not cover it.

**The exact sentence I accept.** It replaces everything after "…only through `tools/ci/update_goldens.py`":
> "A red caused by another phase's output change (e.g. 07d's C5) is resolved in that phase's PR: it re-runs the sweep on the producing runner, updates the JSON through `tools/ci/update_goldens.py` with a stated reason and a BUILD_PLAN §6 row, and puts the changed prints to the board for whether 07e's ruling still holds. It is never regenerated just to pass, and the ruling is never carried over unasked."

Why this wording:
- The red appears in the CI of the PR that caused it, so it never sits on main.
- The baseline has one owner at each crossing.
- The board decides about the ruling, and the golden mechanics stay where CLAUDE.md puts them.
- If C5 lands before 07e produces its values, nothing turns red: 07e is measured on the engine C5 leaves.

**2. Ranking.** Unchanged.
- H4+G: prefer.
- H3+G: can live with.

**3. Tension now** (with the enlarged 07e and the extra prints run in the `python` job)
- **H4+G: 0, confirmed.** No `src/sim` change and nothing on the audio thread. The per-run pytest re-runs ≥ 1 placement, not the whole sweep. The added prints (medium_room, the band-wise values, C3-a's L_f/L_p, the (c) control) are fields in the committed JSON. They add assertions, not render work in CI.
- **H3+G: 1, unchanged.**

**4. Tension later**
- **H4+G: 1, confirmed.**
  - The debt is still that scope 8 is held and 07d probably splits into 07d/07d-b. This does not depend on a fix being ruled. I accept the interrogator's Q3 correction to my 29-seat5 §2 wording.
  - The sentence above adds one board look per output-changing phase while 07e's ruling stands. That stays within 1.
  - Evidence that could change this arrives with 07e's ruling.
- **H3+G: 0, confirmed.** The prints and the clause are the same under H3+G, so they do not separate the two options.

**5. Evidence.**
- Item A AC and scope 3 (file 30 L209–234).
- My G3 text (29-seat5 §6).
- The interrogator's Q5 row (31, L73).
- AX5 (BUILD_PLAN L128): bit-identity holds only on the same OS and architecture.
- [Hyp] One `render_cli` placement adds seconds per CI job, not minutes. Not measured.
- [Hyp] A seeded tracer run at k ≥ 684 per CI job would be costly. That is why the condition below keeps it out of the pytest.

**6. Conditions of acceptance.**
- My 0/1 for H4+G holds only if the per-run pytest re-renders ≥ 1 placement and does not run the tracer reference or the full sweep.
- If the full sweep or the tracer moves into every `python` job on three OSes, my now-cell rises to 1. To bring it back to 0: run the full sweep only in a manually started job, and keep the per-run pytest to the single placement.

**7. Hand-offs.**
- Seat 7: the cost of re-running the sweep in an output-changing phase's PR.
- Seat 2 (Lead): whether the sweep plus the tracer stays size S.
- Builder: how the AX5 residual converts to a dB tolerance. I give no number.

**8. Premortem.** Suppose the decider's clause is adopted with no owner. C5 turns 07d's PR red, nobody owns the board look, and someone updates the JSON to unblock the PR. 07e's ruling then rests on values from an engine it never judged. The contracted engineer would notice first, reading the CHANGELOG reason against 07e's report.

Files read: /home/user/makroof/docs/review/phase-07c-2b/30-decider-m3h-decision.md (L186–237 and the matched lines), /home/user/makroof/docs/review/phase-07c-2b/31-interrogator-on-file30.md (matched rows and Q1–Q5), /home/user/makroof/docs/review/phase-07c-2b/29-seat5.md.
