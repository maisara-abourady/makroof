# Decider — round 4 (final): D-T4a = 4a-2G3C; final summary of D-T5/D-T4

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

# Decider: round 4 (final), D-T4a and the remaining corrections

D-T4a is revised to **4a-2G3C**, max 1, sum 17, with every cell rated by its seat or read from its stated conditions. The other six decisions survived the interrogator's round 2 and stand as written. Only Challenge 1 (the 100 m state-restore gate, an AQ10 amendment) and Maisara's accept or veto remain open.

Corpus revision `c1b171fe649f07cbeb952ef1f75d89bfaa414d0d`. Inputs: `12-interrogator-T5-T4-round2.md`, `6-seat5-rerun2-T4a.md`, `6-seat5-rerun3-T4a.md`, `6-seat3-rerun3-T4a.md`, `6-seat6-rerun4-T4a.md`, `6-seat1-rerun-T4a.md`, `6-seat7-rerun-T4a.md`, `6-seat9-rerun-T4a.md`.

## Answer to the interrogator's question (row 40)

Seat 5 rated 4a-2G++ **1/2** as written. Plain FIFO lets a host-thread wait (prepare, restore, `setNonRealtime`/`quiesce()`, offline `processBlock`) grow to about K solves. Seat 5 proposed a two-class rule (a) and cancellable builder waits (b).

Seats 3 and 6 then rated the two-class rule **1/2**: offline renders would starve real-time instances. Both reach 1/1 with a **three-class rule**. Seat 5 re-run 3 confirms the three-class rule plus (b) at **1/1**. It supersedes Seat 5's (a). Seat 5 asks that its earlier conditions stay part of the rule, and that the AX text state that M offline renders in parallel bound the offline wait at about 2M solves, which is recorded.

On Seat 3's hand-off, Seat 5 rules that a non-realtime `processBlock` waiting at the gate **is allowed**, under conditions 1–6 of its re-run 2, all written into (i) below.

## Naming

**4a-2G3C** is round 4's one composed variant for D-T4a. It is 4a-2G++ plus:
- Seat 5's (b) and its offline-path conditions;
- the three-class rule (Seats 3 and 6, confirmed by Seat 5);
- the late conditions of Seats 1, 7 and 9 (correction 41);
- Seat 6's restored wording (correction 42).

The two-class version was Seat 5's own proposal, not a composed variant of mine.

## D-T4a: tension map (final)

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| 4a-1 | 0/2 | 2/2 | 1/2 | 1/1 | 1/1 | 1/2 | 2/2 | 1/2 | 2/2 | 2 | 27 |
| 4a-2 | 0/1 | 1/1 | 1/1 | 0/1 | 2/2 | 1/1 | 1/1 | 1/2 | 1/1 | 2 | 19 |
| 4a-3 | – | – | – | – | 3/3 | – | 1/3 | – | – | veto | – |
| 4a-2G++ as written | 0/1 | 1/1 | 1/1 | 1/1 | **1/2** (Seat 5 re-run 2) | 1/1 | 1/1 | 1/1 | 1/1 | 2 | 18 |
| 4a-2G++ with Seat 5's two-class (a) + (b) | 0/1 | 1/1 | **1/2** (Seat 3 re-run 3) | 1/1 | 1/1 | **1/2** (Seat 6 re-run 4) | 1/1 | 1/1 | 1/1 | 2 | 19 |
| **4a-2G3C** | 0/1 | 1/1 | 1/1 | 1/1 | 1/1 | 1/1 | 1/1 | 1/1 | 1/1 | **1** | **17** |

Source of each 4a-2G3C cell:
- **S1:** rated by Seat 1 in its re-run; its conditions (1) and (2) are in the text.
- **S2:** confirmed on 4a-2G. The interrogator accepted the carry (row 47 text): the added terms are ordering, records and visibility, none of which bears on Seat 2's measures.
- **S3:** read from conditions. Seat 3 re-run 3: with "three classes" plus the offline-staleness record, "1/1".
- **S4:** read from conditions. Seat 4's round-3 conditions (iv) binaural and (v) item 8 are in the text. The three-class ordering was not put to Seat 4. Seat 4's own words bound it: "Its whole cost is delay, and the conditions above make that delay measurable per output mode."
- **S5:** rated by Seat 5 in re-run 3 (1/1).
- **S6:** read from conditions. Seat 6 re-run 4: alternation plus its kept terms plus the freeze record, "1/1".
- **S7:** rated by Seat 7 in its re-run; conditions (1)–(3) are in the text.
- **S8:** confirmed on 4a-2G; carry accepted (row 47).
- **S9:** rated by Seat 9 in its re-run; conditions (a) and (b) are in the text.

**Working.** Bounds hold for every option. 4a-3 is vetoed. Every other option reaches max 2. 4a-2G3C brings the max to 1 and raises no seat. Sum 17.

## DECISION D-T4a = 4a-2G3C (text for the AX row)

This is a working memory ceiling per plugin instance for the diffuse computation, at the largest AX6 room (100 m per side), at every supported sample rate, with both emitters. phase-13 scope 1 owns the memory budget. The customer-side unknowns stay declared unknown: K8 (customer RAM), K9 (comparable plugins), K10 (instances per project).

**(i) Transient memory and the gate**

- **Ceiling.** The transient peak of one diffuse solve is at most **1 GB**. At most **one diffuse solve runs at a time per process**, through a gate.
- **Gate implementation.**
  - The gate is JUCE-free.
  - It is a sleeping wait (mutex plus condition variable), with no spin lock, and the builder's priority is not raised to compensate.
  - It is held only around the solve, never while holding `stateMutex_` or the builder mutex.
  - It is never reachable from a real-time `process()`. The only build in `process()` stays the `nonRealtime_` branch (`ScenePipeline.cpp` L400–402). A debug assert guards this, and a test runs one real-time pipeline beside one solving at the gate: the real-time pipeline makes zero allocations and never touches the gate.
- **Three-class service order.**
  1. Synchronous host calls (prepare, restore, `setNonRealtime`) are served first. Their wait is at most the one solve already running.
  2. Offline-render waiters and (3) builder-thread waiters take turns, one solve each. A real-time instance's builder therefore waits about two solves while another instance renders offline. An offline waiter waits about two solves, or about 2M with M offline renders in parallel. This is recorded; offline has no deadline (F20).
  - Within a class, waiters are served in arrival order (FIFO), one solve at a time.
- **Coalescing and cancellation.**
  - Builder-thread waiters keep coalescing and solve their newest scene when their turn comes.
  - Offline waiters never coalesce: each solves exactly the scene of its block (AQ4, AX5).
  - A builder waiting at the gate leaves the queue when `quiesce()` is called; the condition-variable predicate checks the stop flag.
  - The offline path takes the gate only after `quiesce()` has returned.
- **Output independence.** Gate order never changes any output, because each solve is a pure function of its scene. It is tested with two pipelines in either order, and also with one of them offline.
- **Concurrency test.** TSan `[pipeline]` with two pipelines, one switching to offline in the middle of a solve.
- **Known gap.** Under Bitwig's per-plugin sandbox the transient counts per instance. It is stated in the public compatibility notes until Phase 13 measures it (Seat 7 (3)).

**(ii) Resident memory**

At most **128 MB of additional** memory kept between rebuilds per instance, on top of the Phase 07 CI baseline (+122.6 MB at 96 kHz in the maximum room, Linux).

**(iii) Visibility of the gate wait**

- Time spent waiting at the gate counts in Phase 10's IR-staleness metric.
- It drives the UI "settling" state on **every** instance waiting at the gate, project load included (Seat 7 (1)).

**(iv) Records** (filed with D-T4c, this session; from Phase 08 on, also in binaural mode with the gate wait shown separately)

With 1, 4 and 8 instances, in the AQ10 room and at 100 m, at 48 and 96 kHz:
- per-instance staleness when rebuilding together;
- the time until the last instance is audible at project load;
- staleness when the instances are automated together (**position and room size**);
- staleness of real-time instances while another instance renders or freezes offline under room-size automation;
- the offline wait, including the M-parallel case;
- the worst `quiesce()` latency;
- the worst host-thread wait (prepare, restore, offline);
- callback p99.9 of the instances playing during an offline render.

Each record states the automation speed or rebuild step it was taken at (Seat 1 (2)). The 1 / 3 / 10 s marks are escalation points and are labelled **UI response-time anchors (Card et al. 1991), not audibility limits** (Seat 1 (1)). If the 8-instance, 100 m time until the last instance is audible at load exceeds 10 s, it goes to Maisara before the first release (Seat 7 (2)).

**(v) Phase 08 item 8**

- Item 8 measures the delay of one isolated update with the gate wait included.
- It records that the diffuse solve inside every rebuild, not the gate, is what breaks Table 15.1's 35 ms head-rotation row.
- If that row applies, the remedy is a Phase 10 AX that updates the specular and directional part without waiting for the diffuse solve. The remedy is not a change to the gate.
- Seat 1 reads AX3's centroid-following yaw under the source-movement rows, not the head-rotation row [Inferred]. Item 8 still measures.

**(vi) D-T3 escalation**

Any D-T3 pass that this ceiling triggers:
- states its cost per scene class (a closed reverberant box against an open-face outdoor box), not per side length (Seat 9 (a));
- reaches Maisara before Phase 12 builds the FR-3D-3 presets (Seat 9 (b)).

**Couplings**

- Seat 2's cell relies on D-T4b (4b-2, no cache credit).
- D-T4c's memory block uses this ceiling.
- If D-T1 chooses a cached-kernel candidate, (ii) and D-T4b reopen together.

**Register (later ≥ 1; seats' words where they gave them)**

| seat | commits later phases to | undo | evidence arrives | repaid when |
|---|---|---|---|---|
| S1 | "the same D-T3 risk as 4a-2 (it depends on D-T1)"; queued lag that "widens the gap between what is monitored and what is bounced" | D-T3 route | (iv) records; D-T1 at 100 m | D-T1/D-T3 settled |
| S2 | the 128 MB cap rules out a mid-size kernel cache (≈ 0.47 GB in the AQ10 room) | parameter change via a Phase 10 AX and the Phase 13 budget | Phase 10 | Phase 10 |
| S3 (read from conditions) | the three-class rule; offline-staleness record | builder rework | (iv), this session | when recorded |
| S4 (read from conditions) | binaural (iv) records; item 8 with gate wait; split-update remedy route | Phase 10 AX | Phase 08 item 8 | Phase 08/10 |
| S5 | the gate and its offline conditions. Open researcher check [Hyp]: whether any host runs a freeze or offline render on a thread that also serves the real-time graph. If one does, the about-two-solves bound needs tightening. | gate rework | no scheduled source | – |
| S6 (read from conditions) | alternation; staleness metric and "settling"; freeze record | builder rework in Phase 10/13 | (iv), Phase 10 | Phase 10 / UI phase |
| S7 | "slower project loads and memory that grows with instance count"; "some stems may be silent at load until their turn"; 8 × 128 MB ≈ 1.0 GB plus 8 × 122.6 MB ≈ 0.98 GB [Inferred]; fit to customer machines [Hyp] until RQ1 and RQ3 | Phase 13 budget | (iv); proposed phase-13 multi-instance RSS record | first release |
| S8 | "a delay before the last instance's room is heard … loses no work" | – | (iv) | this session |
| S9 | conditions (a) per-scene-class D-T3 cost and (b) before Phase 12; "if either fails, later rises to 2" | – | the D-T3 packet | before Phase 12 |
| (row 25) | 128 MB additional resident × K10, plus the Bitwig case | Phase 13 budget | proposed phase-13 scope 3 RSS record | Phase 13 |

**Strongest objection.** S4's cell is read from round-3 conditions, and the three-class order was not re-put to Seat 4. Only a 3 changes the winner; a 2 gives max 2, and 4a-2G3C (18) still beats 4a-2 (19).

**Confidence:** low (K8–K10 unknown; four cells read from conditions). **Reversal:** Phase 13 RSS or the (iv) records exceeding the escalation anchors, or D-T1's measured peak at 100 m above (i) or (ii).

## D-T4c additions (corrections 49 and row 40)

- For both gated 100 m builds, the record states per emitter whether the AX22 fallback triggered (`ismFallback`). The fallback scene asserts that it fell back. If the closed low-α cube also fell back, the record says so, and the non-fallback horizon is reported as not covered.
- The 1 / 3 / 10 s marks are labelled UI response-time anchors, not audibility limits.

D-T4c otherwise stands as written in round 2.

## Final summary (all seven ids)

| id | decision (exact) | state | worst-off (cell) | sum | confidence | PRD bound | corpus basis | reversal condition |
|---|---|---|---|---|---|---|---|---|
| D-T5.1 | **5.1-A\*.** E_target = specular entries plus propagated diffuse energy in all 8 bands: s(1−α) injected per hit (Kuttruff §5.2/§2.7 split, Lambert Eq. 4.24), transported by Eq. 4.35, gathered by Eq. 4.29, AX4 air; same window, referral and t_mix,e as `ref_hybrid.target_hybrid`. RAII FTZ/DAZ in `buildRoomIR` that also restores on a throw; double sums; a denormal-producing `[pipeline]` test where FTZ on and off are bit-identical per platform. Tracer check at 125 Hz, 4 kHz and 8 kHz on layouts 4 and 5 at s = 1, reported before goldens; a failure goes to D-T2 and Maisara, never to AX16. | stands | 1 | 14 | medium | NFR-1, NFR-6/AX5 | Kuttruff §4.5, §5.2 | the tracer check fails in a band |
| D-T5.2 | **5.2-A.** k_real, the fallback and t_mix,e use the specular plus AX16 entries; AX22 unchanged; over-trigger: no scheduled evidence | stands | 1 | 14 | high | AX22 (settled) | Kuttruff §4.1–4.2 | a scheduled over-trigger test shows one |
| D-T5.3 | **5.3-D.** `bandsAxisShares` from specular entries only, labelled; Phase 08 gets E_b and t_mix,e only; Phase 08 may precede 05h on Seat 4's (i)–(iv); directional tail goes to the backlog behind Seat 1's blind test, in Seat 4's 2×2 covariance form | stands | S3 0/1 | 1 | high | NFR-6, NFR-8 | Kuttruff Eq. 4.29 | the blind test passes |
| D-T5.4 | **5.4-A\*.** Generic outcome. Double, log-domain check against a finite-floor single-scatter integral (it does not import `ref_hybrid`; PR CI on three OSes). The −60 dB check is kept. Golden updated only through `update_goldens.py` with a ≥ 10 dB sentinel margin. Phase 12 two-branch check, reported not tuned. Ghost-tail reversal (Seat 9's 60 dB). Seat 3's condition is met by the C1 addendum. | stands | 1 | 17 | medium | NFR-8, FR-SIM-6 | Vorländer §4.4.1, §1.5; C1 | the ghost tail fires |
| D-T4a | **4a-2G3C**, as written above | revised (final) | 1 (S4 read from conditions) | 17 | low | NFR-2, AX6, phase-13 scope 1 | – | Phase 13 RSS, (iv), D-T1 peak at 100 m |
| D-T4b | **4b-2.** AQ10 unchanged; W1/W2 include the whole diffuse computation, no cache credit; per-mode W1/W2 with the diffuse share from Phase 08; coupled to D-T4a (ii) | stands | 1 | 13 | high | AQ10 | Table 15.1 (context) | Phase 10 cache AX, after D-T4a (ii) reopens |
| D-T4c | **4c-1C.** Blocks: the memory gate at the larger of the two 100 m, 96 kHz builds (fallback asserted, the fallback flag recorded for both), plus Seat 5's CI list. Records: full rebuilds (six Phase 04 rooms, AQ10 room, CR4, both 100 m builds; 48 and 96 kHz); the AQ4 intervals against 100 ms, 700 ms and 3 s; restore alone and contended, with the pluginval silent stretch; the 3-minute bounce with its real-time ratio; callback p99.9 with 1, 4 and 8 builders; D-T4a (iv). Escalation to Maisara against 1 / 3 / 10 s, labelled UI anchors, with Table 15.1's conditions stated. Hand-offs: "settling", stepwise room-size automation, no Eyring T60 shown for an open field. | stands | S5 1/2 | 17 | medium | AQ10 (settled) | Table 15.1; F21 | Challenge 1 answer |

## NEEDS MAISARA

1. **Challenge 1 (ledger row 50).** Should a CI gate on the synchronous state restore at 100 m and 96 kHz become blocking? The limit would be 14 × t_restore under pluginval's 30 s watchdog, about 2.1 s per restore; today it is 1.51–1.88 s. Making it blocking amends AQ10's "full rebuilds recorded, not budgeted". Yes moves Seat 5 from 1/2 to 1/1; no keeps it as recorded debt.
2. **Accept or veto** each of the seven decisions before the plan-editor applies them (fix-plan step 3).
3. **Conditional, later.** The 8-instance, 100 m load-time record above 10 s comes to her before the first release (D-T4a (iv)). Any D-T3 pass comes to her per scene class before Phase 12 (D-T4a (vi)).

**/fix-plan list, beyond the seven AX rows:**
- **phase-05b2 §3:** the Phase 08 wording correction (D-T5.3).
- **phase-08:**
  - may precede 05h on Seat 4's (i)–(iv) (D-T5.3);
  - (iv) binaural multi-instance records with the gate wait shown separately (D-T4a);
  - (v) item 8: isolated-update delay with the gate wait included, the breach attributed to the diffuse solve, the remedy route a Phase 10 split-update AX, plus Seat 1's AX3 reading (D-T4a);
  - per-mode W1/W2 with the diffuse share (D-T4b).
- **phase-10:**
  - gate wait counted in the IR-staleness metric (D-T4a (iii));
  - stepwise room-size automation at large rooms documented (D-T4c);
  - a kernel cache only through an AX, reopening D-T4a (ii) and D-T4b (D-T4b).
- **UI phase:** "settling" on every gate waiter, project load included (D-T4a (iii)); no Eyring T60 shown for an open field (D-T4c).
- **phase-12:** the outdoor two-branch check and the ghost-tail reversal (D-T5.4); the D-T3 per-scene-class packet before preset building (D-T4a (vi)).
- **phase-13:** scope 3 records multi-instance RSS on three OSes, including Bitwig's sandbox (D-T4a); the Bitwig gap in the public compatibility notes until Phase 13 (D-T4a (i)).
- **Backlog:** the directional late tail behind the blind test (D-T5.3).

## For Maisara (D-T4a, one line)

The 1 GB per-build ceiling is unchanged. Builds now queue in three classes: your host's own calls first, then offline renders and live instances taking turns, so a bounce cannot freeze the other tracks' rooms. Waiting instances show "settling". Load-time and memory-growth records come to you before release, and a room-range cut would come to you per room type before the presets are built.

Files:
- /home/user/makroof/docs/review/phase-05b2/12-interrogator-T5-T4-round2.md
- /home/user/makroof/docs/review/phase-05b2/6-seat5-rerun2-T4a.md
- /home/user/makroof/docs/review/phase-05b2/6-seat5-rerun3-T4a.md
- /home/user/makroof/docs/review/phase-05b2/6-seat3-rerun3-T4a.md
- /home/user/makroof/docs/review/phase-05b2/6-seat6-rerun4-T4a.md
- /home/user/makroof/docs/review/phase-05b2/6-seat1-rerun-T4a.md
- /home/user/makroof/docs/review/phase-05b2/6-seat7-rerun-T4a.md
- /home/user/makroof/docs/review/phase-05b2/6-seat9-rerun-T4a.md
