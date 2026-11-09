# Seat 2 (engine architect) — re-run on the decider's composed variants (4a-2G, 4c-1C)

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

SEAT 2 POSITION (re-run)

I confirm both cells at 1/1. The 128 MB resident cap is not a 2 for my seat. 4c-1C stays at 1/1 only if one point is made explicit: the gated 100 m build must use the longest diffuse time horizon (see the second row).

| variant | now | later | reason (my measures) |
|---|---|---|---|
| **4a-2G** | **1** (confirmed) | **1** (confirmed) | **Transient, 1 GB:** this covers my 4a-1 condition (161 MB plus headroom). At 100 m, the per-patch-history classes (b) and (d) fit band by band: 80.6 MB per band per emitter, so 161 MB for both emitters. The Monte-Carlo class (f) needs well under 1 MB. So the ceiling does not pre-decide D-T1 among the classes that could be viable, and memory alone does not force D-T3 [Hyp until D-T1 measures]. **Resident, 128 MB, not a 2:** at 100 m, any useful room-only cache is far above 128 MB anyway. A single float32 per patch pair is already 9 600² × 4 B ≈ 369 MB, and the dense kernel is 381 GB or more per band. So the cap removes nothing that could have existed at that size. Under D-T4b = 4b-2 no cache credit exists, and phase-05b2 §9 puts caching beyond D-T1's needs out of scope. **What stays a 1 later:** if Phase 10 proposes a kernel cache for mid-size rooms (the AQ10-room dense kernel is ≈ 0.47 GB), the 128 MB cap rules it out. Changing that is a parameter change through Phase 10's AX and Phase 13's budget, not a rework. The diffuse part's memory does not depend on the sample rate (1 ms energy bins), so the 96 kHz clause costs it nothing. |
| **4c-1C** | **1** (confirmed) | **1** (confirmed, under one condition) | **Met:** my condition was that the 100 m full-rebuild time is recorded and flagged to Maisara. It is: the times are recorded for the six Phase 04 rooms, the AQ10 room, CR4 and 100 m. The D-T1 packet escalates them against 1 s, 3 s and 10 s, and any room above 3 s is named as a finding. So a formulation that fits in memory but takes minutes at 100 m [Hyp: ≈ 1.4·10¹¹ kernel terms per generation for (b)/(d)] reaches Maisara before shipping, not first in Phase 13. **Condition for later = 1:** the gated 100 m, 96 kHz, 2-emitter build must be in the AX22 fallback, or both cases must be measured. The fallback is the longest time horizon: t_cap ≈ 2.1 s, ≈ 2 100 bins, against ≈ 1 035 bins without it. Every non-Monte-Carlo class's memory and time scale with that horizon, so a 100 m scene without the fallback measures about half the peak. If the gated scene is not in the fallback, later becomes **2**, because the block would then check a case that is not the worst one. |

Evidence: [Plan] phase-05b2 §0.3 (patch counts, bins, the dense-kernel sizes) and AX22 (t_cap). [Inferred] My arithmetic: N·T·4 B; 9 600² × 4 B; Kuttruff Eq. 4.6 integrated for the path count.

Hand-off: Seat 5 owns the Bitwig sandbox gap, where the transient memory counts per instance.
