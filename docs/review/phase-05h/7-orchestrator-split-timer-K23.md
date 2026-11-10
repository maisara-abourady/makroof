# Orchestrator — D-H1 / D-H2 inputs the seats and the decider asked for (2026-11-10)

Data only; nothing decided here.

## 1. Split timer of the non-diffuse 100 m / 96 kHz build (Seat 2's hand-off, file 5-seat2)

Hidden test `probe: split timer of the non-diffuse 100 m / 96 kHz build` (`tests/unit/test_diffuse_gate.cpp`,
tag `[.][probe-restore-split]`), Release build, this session's 4-core Linux box (a numba reference job was
running at `nice 10` at the same time, so absolute times are above CI's 2.06–2.07 s; the shares are the point).
Scene: the closed low-α cube (100 × 100 × 100 m, α 0.05, s 0.3, listener (50, 30, 1.7), emitters (45, 70, 2),
(55, 70, 2)); `BuildOptions::tailLevelAx16 = true` (no diffuse solve); median of 5.

| fs | T60_max (Eyring) | unit decay | full build, no diffuse | `BandNoiseGenerator` ctor (band spectra) | `make` × 2 emitters | position-only build (cached unit decays: ISM + matching + mix) |
|---|---|---|---|---|---|---|
| 96 kHz | 50.5 s (tail capped at 12 s) | 1 152 000 samples | **3 287 ms** | 956 ms | 2 182 ms | **147 ms** |
| 48 kHz | 50.5 s | 576 000 samples | 1 321 ms | 378 ms | 867 ms | 58 ms |

Reading: the unit-decay synthesis (constructor spectra + `make` for two emitters: 3.14 s of 3.29 s at 96 kHz,
≈ 95 %) is the non-diffuse restore cost at 100 m; the ISM list, the matching and the per-sample mix are
≈ 0.15 s. Seat 2's attribution (file 5-seat2 §5) is confirmed by measurement. Phase-07c as written moves only the
diffuse solve (58–162 ms in CI) off the synchronous restore, not the synthesis.

## 2. Repository visibility (researcher F9 / F17 condition)

`gh api repos/maisara-abourady/makroof` → `"private": false, "visibility": "public"`. The public-repository runner
table applies: Linux and Windows 4 vCPU / 16 GB, macOS 3 vCPU (M1) / 7 GB, 14 GB SSD; standard minutes free.

## 3. K23: per-case `hybrid_fast` cost this session (4 cores, one band column per kernel, 8 bands per case; wall time)

| case | 2.5 m | 1.25 m |
|---|---|---|
| dt6_small_room e0 / e1 | 1 s / 1 s | 1 s / 1 s |
| dead_booth e0 / e1 | 2 s / 2 s | 2 s / 2 s |
| living_room e0 / e1 | 1 s / 1 s | 2 s / 2 s |
| classroom e0 / e1 | 1 s / 1 s | 2 s / 2 s |
| club e0 / e1 | 2 s / 2 s | 9 s / 9 s |
| stone_box e0 / e1 | 3 s / 2 s | not yet run |
| concert_hall_box e0 / e1 | 28 s / 28 s | e0 running (chunked solver; the 1.25 m kernel is above the 0.6 GB lean limit; a first attempt with the lean solver was OOM-killed at 15 GB) |
| W1 e0 / e1 | 8 s / 7 s | not yet run |
| W1 CS-NW+ (listener wall / edge / corner 0.1 m, wall 0.3 m; emitter wall 0.1 m), both emitters | 10–12 s each | not yet run |
| W2 e0 / e1 (fallback, t_mix 0.380 s) | 124 s / 220 s | not yet run |

The 2.5 m rung exists for every case above (38 case runs); the 1.25 m rung for the five smallest rooms (both
emitters). The K20 listing (`6-orchestrator-K20-certified-listing.md`) currently counts AX43: 274 certified / 286
single-rung; AX45: 40 / 32. Memory anchors: concert_hall_box at 1.25 m ≈ 2 000–2 600 patches × 162 bins → kernel
≈ 2.7–4.4 GB float32 per band column; W1 at 1.25 m ≈ 1 408 patches × 145 bins ≈ 1.2 GB; W2 ≈ 3 GB.
