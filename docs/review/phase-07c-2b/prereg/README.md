# Phase 07c-2b ABX pre-registration (AX47 self-ABX F1/F2 and AX49 L4)

Committed before the first scored trial (run sheet `docs/validation/abx-07c-2-run-sheet.md` §3 item 4, item 11).
Nothing in this folder reveals an answer: each `*-prereg.json` holds the key's SHA-256 and a salted SHA-256 of every
A, B and X; the keys and salts are held outside the repository and outside every folder the listener can open.

## Listener and date

- Listener: Maisara (the single decision listener; item 1). Her words, 2026-11-24: "1. I will listen 2. Tonight."
- Date: 2026-11-24, evening. Sittings ≤ 2 h, split only at a chain boundary. Order (run sheet §4): S-W noise 0.9 dB,
  then S-W speech 0.9 dB; then S-B\* noise 0.9 dB, S-B\* speech 0.9 dB; then L4 alone after a rest, the same day as the
  S-B\* sitting. A 0.5 dB block is played only after a 0.9 dB detection in that chain (`score` refuses otherwise).
- Speech material: TSP speaker MA, files MA01_01 / MA01_02 (M3-6; item 8). Never committed or uploaded (item 12).

## What was sealed

| session folder (listener) | pack (unsealed; never given to the listener) | key SHA-256 | stimuli |
|---|---|---|---|
| `1-SW-noise` | noise, `layout4_s1/both_wall` (F1) | 5b4f186a48619c0a83c5e6cf3085b35efcb389f500e4d3097c259ef6eb3ea095 | 180 |
| `2-SW-speech` | speech, `layout4_s1/both_wall` (F1) | 20bee4cd159620f5b4419268a291b5d4f47041c9a0cf3e3bc18d2c4c9fad84be | 180 |
| `3-SB-noise` | noise, `layout4_s0.7/default` (F2) | 4add1fddc2ac70e5f342f9d071409fc48ea5751b77217769c5a8ede058c18277 | 180 |
| `4-SB-speech` | speech, `layout4_s0.7/default` (F2) | f320d55393feb91848a86cf061726c25c0d2020aa32bed79f6ccbc44663c3199 | 180 |
| `5-L4-chord` | L4, `ax49_l4_cube` | f0d0fb30ecea752d2ff5d2a2a43e526e75250428e0c1883bc5bbe90f3132fa3a | 66 |

- Pack manifests' SHA-256: `pack-manifest-sha256.txt` (scene hashes, measured values and every stimulus's SHA-256
  are in those manifests).
- Code the stimuli were built from: c570b59 (builder file 27, every item-6 assertion green). `src/`, `tools/` and
  `tests/` are unchanged from c570b59 to the pre-registration commit (`git diff --stat c570b59 HEAD -- src tools
  tests` is empty). A rebuild at the pre-registration head is run as a reproducibility check (hashes compared and
  recorded with the results).
- CI evidence (R5; run sheet §7 "seal evidence is a CI run … green on all three OS"): manual run 45379048605 on
  e6446ba, green on Linux, macOS and Windows (attempt 2), including `AX49 L4 gate (release)`, the kit label/run-sheet
  assertion and the `listening-pack` artifact.

## Pre-seal conditions (run sheet §3 item 4, §7)

- S-W label: confirmed by Seat 9 (`../46-seat9-seal-labels.md`).
- S-B\* label: confirmed by Seat 9; SPREAD clause present. Seat 1 has answered Seat 9's question
  (`../46-seat1-seal-answers.md` (1)): the −1.2 dB L − R spread is identical in A, B and X and is not a cue; the null
  covers its printed heard step on the recorded engine.
- L4 label: confirmed by Seat 9 (D/R −8.5 dB heard, tailSeed 12345). Checks green in CI; 16-seed ensemble print:
  `l4-ensemble-16-seeds.json` (builder file 25).
- L4 `[ax49-l4]` Debug and ASan `--durations` and peak RSS (local, Linux): `ax49-l4-debug-asan-durations.txt`
  (Debug 17.3 s, peak RSS 290 MB; ASan 14.8 s, peak RSS 612 MB; both ≤ 300 s).

## Record-wording amendments fixed before the run (no stimulus changes)

1. S-B\* §6 wording (Seat 1, file 46 (2)): "(tail share {printed} at 1 kHz;" reads "(heard tail share {printed:
   heard.bands.1000.tail_share_of_heard} at 1 kHz;" (0.032 at this build; ΔG +0.03 dB, ΔC80 −0.52 dB, from the
   manifest).
2. S-B\* record wording (Seat 9, file 46, in place of a label change): add "the tail enters at t_mix,e 0.380 s about
   27 dB above the specular early part just before it at 1 kHz (31 dB broadband; per band printed)".
3. Familiarisation (run sheet §4 blank; Seat 1, file 46 (3)): "Familiarisation is open and labelled: before each
   pack's first scored block the listener plays that pack's `familiarisation/` pairs with their labels visible (A
   stepped, B unstepped, the step size in the file name), as often as she likes; there are no practice ABX trials,
   and no feedback of any kind is given in or between scored blocks except the per-block `score` result that the
   fixed-sequence rule needs."
4. Listener instructions (Seat 1, file 46 (4)): play only the session folder's A, B, X files; no key, pack,
   manifest, log or terminal history; no file sizes, dates, hashes, compare tools, waveform, spectrum or meter
   displays; level set once before familiarisation and not touched; every trial answered, no going back, no change
   after scoring; break after presentation 15; ≤ 2 h, not on tired ears; nothing discussed with anyone until every
   block is scored.

The trial count (24 scored + 6 anchors per AX47 block; 16 + 6 for L4) and the criteria are as the run sheet states;
nothing is cut.
