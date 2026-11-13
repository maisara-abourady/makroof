# 17 — Seat 5 position on the FM-D1-S3 lines (file 16)

2026-11-13. Saved by the orchestrator from the seat's report. Read: file 16, file 15, `src/sim/tail/NoiseTail.cpp`,
phase-08-3, BUILD_PLAN L169–171. Corpus not consulted (no acoustic claim).

**Reading.** The 07c-2 scope 9 bullet (window [t_mix,e, L) for a full-length interim; "no shared prefix" branch — correction 91)
and the CI cost and determinism of the 08-3 / 09 lines (N1, N2, coefficient bit-identity; A4 set, 48 and 96 kHz, ≥ 2 seeds). Cues
§4.1 (data crossing a clock), S5 (offline deterministic), CS-5 (one-person CI budget), §9 (a known-benign race is not a design).

**Ranking.** 08-3 / 09 lines as written (file 16 §3–§4): prefer, with C1–C3. 07c-2 bullet (§2): can live with — the window itself
defers to Seat 3; from this seat both IRs are truncated at the same L (no L_f edge) and the window adds no thread or timing dependency;
C4 on the branch. No own option.

**Now.** 07c-2 bullet 1 (conditional; adds only offline IR builds; the "no shared prefix" branch relies on PR text, not an assertion).
08-3 / 09 lines 1: per (scene, fs, seed) and mode, exact + provisional + N1 = 3 IR builds (+ N2 = 4 in two-output modes), × 2 fs ×
≥ 2 seeds × the A4 scenes ≈ 16 builds per scene per mode; IR builds only, no convolution; added CI time unmeasured [Hyp], expected
small next to the existing AX47 (b) and mid-fade checks that build the same exact IRs.

**Later.** 07c-2 1 (commits one test or one written statement; undo drop the bullet; overturned by 07c-2's class (c) / load-fallback
decision). 08-3 / 09 1 (a handful of offline tests; undo drop the lines; overturned by wall time — fix by sharing fixtures, never by
cutting seeds — or by determinism: 1, not 2, only with C1).

**Evidence.** The N1 seed assertion can never fail (NoiseTail.cpp l. 54–57 `seed ^ (k·0x9E3779B9)`) [Observed]: same index s+1 ≠ s;
crossed indices would need s ⊕ (s+1) = 0x9E3779B9, but s ⊕ (s+1) is always 2^m − 1 (incl. the wrap 0xFFFFFFFF → 0) — harmless, keep it
as a guard on a future seed-derivation change. Margins: N1 / N2 ≈ +3.01 dB vs a pass bound −18.27 dB (−24.55 dB at 0.5 dB): ≥ 20.8 dB
(file 16 S3-L2); cross-platform float differences cannot flip either control [Inferred]. Offline skips the provisional (AX49, L171;
the parallel build is bit-identical to the serial): the provisional IR can only come from the builder, never from a render taken off
the pipeline [Observed]. Bit-identity across code paths is fragile [Inferred, §4.1]: two paths computing (a_b, b_b) or filter
coefficients separately can differ by 1 ulp (FMA contraction, inlining) even on one platform; it holds by design only if both read one
computed or cached value.

**Conditions (keep the ratings at 1):** **C1 deterministic source** — provisional, exact, N1 and N2 IRs from direct serial builder
calls in one process, never from timing the async pipeline; the test asserts a repeat build is bit-identical before it compares
(CLAUDE.md determinism). **C2 coefficients by construction** — the provisional and exact paths take (a_b, b_b) and the per-ear /
per-feed filter coefficients from one shared function or cache; bit-identity compared within one process only, never across OSes.
**C3 CI placement** — reuse the exact IRs already built for the AX47 (b) and mid-fade fixtures (one build per scene, fs, seed); tagged
to run in the Release test job, not debug-only or TSan; each PR prints the added wall time per OS; "≥ 2 seeds" means exactly 2 unless
the PR gives a reason. **C4 07c-2 "no shared prefix" branch** — where it applies, the PR's statement is backed by an asserted fact (a
test showing the interim's seed, length or per-band decay differs from the final's); a sentence alone does not count.

**Hand-offs.** Seat 3 (does [t_mix,e, L) fit a full-length interim; does analysis-filterbank leakage between bands with different
(g_b − 1) change the per-band ratio); Seat 4 (closed forms; h per mode filter); Seat 1 (audibility of a coherence-only mismatch).
**Premortem.** C1 ignored: the 08-3 test takes its provisional from a pipeline snapshot with run-to-run timing; the prefix check flakes
on one runner; someone loosens the bound or adds retries; a real seed-ordering bug slips; the contracted engineer sees a red-then-green
rerun before any user hears a mid-fade dip.
