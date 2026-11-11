

---

## Round 3: Seat 3 on (x″) with the ns/evaluation CHECK demoted (interrogator file 65)

SEAT 3 POSITION — round 3, (x″) as worded by the coordinator (files 64/65 not re-read; rated on the stated form)

**Rating: (x″) holds at 1 / 1.**

Why the strike of c2 does not move me: the interrogator is right that 0.58 is a 4-thread, one-run artefact (file 1 L44–48), and the solve is 0.10 of ≈ 2.0 s, so a ×2 solve-time regression at constant work is +5 %, below anything the gate ever resolved; solve *work* stays pinned exactly (wPilot/wFinal, D7). What I asked c2 to catch is better served by accruing a per-scene solve median per run (the print) and converting it to a CHECK once ≥ 3 runs give a spread. The detector I need is the in-window absolute bound (±7 %, 1.10) on x64, which sees the synthesis from ×1.1 on a nominal runner, plus c1 (n and the unit-decay length) and c3 (WARNING above 1.10 × baseline / 30 s, counted, named in the PR). The corrected shares (0.92 / 0.51 → ratio 1.20 at ≈ ×1.65) make the ratio an even weaker synthesis detector than I stated; that is why it is a print, and I agree.

**What keeps it at 1 / 1 (inside the bounds, two lines of text, no new CHECK):**
1. The solve print is the per-scene solve median (ms) and its one-thread-equivalent is not inferred; after ≥ 3 runs the orchestrator proposes k from the spread through `/fix-plan` (the plan says so now).
2. On macOS (no in-window absolute bound), two consecutive c3 WARNINGs on the low-α entry are read as (v)(d)'s trigger (defect, remedy named), not as weather; otherwise macOS carries no synthesis detector until Phase 13 and my later rating returns to 2.

Premortem unchanged in mechanism, shortened in reach: a ×1.3 `make` slowdown is caught on x64 by the in-window bound on the next nominal run, and on macOS by c3's WARNING under condition 2.
