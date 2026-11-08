# Phase 06b — advocate, round 1 (2026-11-07, corpus c1b171f)

| id | item | verdict | evidence | who must act | condition for PASS |
|---|---|---|---|---|---|
| D1 | keep P = 512, reword AQ10 | **REDIRECT** | NFR-4: Linux is not a shipping platform; the 12 s / host 64 overload at P = 256 (103.2 %) is Linux-only (Windows 64.2 %, macOS 48.9 %); Izhaki Ch. 11 "The playback buffer": host 64 is the recording regime, not mixing | decider | (1) restate D1 and the For-Maisara line so they don't imply dropouts on the shipping platforms; (2) state the case left for (a) from the PRD; (3) answer P06B-39 (item 9 remedy) in the same round |
| D2 | confirm AX31 | PASS (wording) | FR-3D-9 / AX3: head yaw follows the emitter centroid; phase-08 item 8 plans the Table 15.1 head-rotation (35 ms) check, so "35 ms rows out of v1 scope" is wrong for that row. AX31's extra partition decides that row only if the rebuild falls in (35 − 2P, 35 − P] = (13.7, 24.3] ms at P 512; W2 28.5 ms exceeds 35 ms both ways (39.2 / 49.8 ms) | decider (wording) | record "head-rotation row deferred to phase-08 item 8", not out of scope |
| D3 | AX32 B = 2²⁰, zero | PASS | Izhaki Ch. 11: "a million tracks at integer full scale" is the theoretical extreme; 1e6 < 2²⁰. Zeroing turns garbage into a gap; clamping into seconds of full-scale output (T ≳ 0.6 s halls/churches, FR-3D-3), in headphones in binaural mode (FR-SIM-3). NFR-7 ("never silence") is about licence lapse, no conflict. Rest "zero" on the product reason; "keeps the −120 dB precedent valid" is a test convenience | interrogator majors stand (P06B-47, 55) | none from the product side |
| D4 | 50 ulp rule | PASS | the order effect is a residual ≈ −125…−130 dB, ≈ 29 dB below a 16-bit bounce floor (Izhaki); protects a gate margin, cheap, in the scope Maisara set | – | – |

Intervention to the decider (D1): premise grounded more firmly than cited: the PRD key decision "heavy
CPU/latency acceptable", A4 (result reaches the track by bounce), Izhaki Ch. 11 automatic PDC; PRD silence on
tracking correctly labelled. Question: with the Linux overload treated as a CI-runner fact only, does (a) still
follow from the PRD? Candidates: latency costs a playback/bounce user nothing (Izhaki App. A: PDC misalignment
applies to any non-zero latency, 288 as much as 544); halving P costs 1.5–2.1× CPU per instance, multiplied
across FR-SIM-7/A5 instances (phase-13 scope 3: 10 instances); on macOS even P = 512 is unproven at host 64 /
12 s (item 9, thread-CPU p99.9 109.9 %) and P = 256 roughly doubles per-callback work (P06B-39), so it cannot be
item 9's remedy. Compare like with like (mean vs p99.9). Rewrite the For-Maisara line; restate item 9.
