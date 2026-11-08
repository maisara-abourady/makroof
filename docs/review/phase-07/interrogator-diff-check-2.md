# Phase-07 round-2 fixes (commit 8493ac7): interrogator diff check, round 2 (2026-11-08; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

Checked against `CrossfadingConvolver.{h,cpp}` (clearAll 28–36, prepare 38–100, reset 147–170, computeBlock 260–345),
`RealtimeEngine.h`, AX31, Blauert Ch. 4 "Binaural timbre compensation". **P07-15a closed.**

| id | passage | verdict | evidence | fix | severity |
|---|---|---|---|---|---|
| P07-15a | reset() = post-prepare state, resubmit before next processBlock | CORRECT, closed | `.cpp:270–276` step 1; latest wins `.cpp:109` | — | none |
| P07-15d | entry to non-realtime: reset + resubmit vs builder drain, order unspecified | INCONSISTENT | a drained stale build submitted after the resubmit wins the mailbox and is installed at once | quiesce/join/drain before reset() and resubmit | major |
| P07-15e | "installed at once" condition | IMPRECISE | step 1 also needs next_ and retiring_ null; only if in the mailbox before the first boundary | full condition; reset leaves no retiring request | minor |
| P07-15f | generation bookkeeping after resubmit | IMPRECISE (premise) | a repeat submit of the same scene → G→G fade, `gOut·a + gIn·a` not bit-equal to a (`.cpp:312`) | resubmit marks the generation as submitted | minor |
| P07-15g | trim smoother on reset | IMPRECISE (premise) | bounce 2 may start mid-ramp | reset snaps the smoother | minor |
| P07-15h | realtime reset vs builder | staleness race (SOFTWARE) | stale in-flight build installed at once, then crossfade | quiesce around reset as P07-15d | minor |
| P07-15i | thread of reset + resubmit in realtime | NOT CHECKABLE (host); possibly INCONSISTENT | resubmit allocates; widened submitRoomIR comment | state the thread and behaviour | minor |
| P07-15j | reset before any prepare | IMPRECISE | undefined; resubmit fails rate check | no-op when unprepared | minor |
| P07-15b | mailbox emptied on reset? | IMPRECISE | matters if the resubmit fails | state it | minor |
| P07-15c | isolated-update wording | CORRECT, closed | AX31; `.cpp:333` | — | none |
| P07-14 | only submitter during a bounce | CORRECT, closed | — | — | none |
| P07-27/28 | atomic increment | CORRECT, closed | — | — | none |
| P07-16 | discriminating ACs | CORRECT, closed; achievable | step 1 for both instances | optional order note | none |
| P07-4 | "much less audible … not removed" | IMPRECISE | Blauert Ch. 4: "less or none binaurally" (Koenig 1950); "not removed" goes past the corpus | "less audible or inaudible binaurally"; drop "not removed" | minor |
| BP-389 | §6 row | CORRECT; inherits P07-4, P07-15d | — | update | minor |
