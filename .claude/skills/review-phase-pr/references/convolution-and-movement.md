# Convolution and movement (K6)

Reference file of the `review-phase-pr` skill. Scope: uniformly partitioned overlap-save with a frequency-domain delay line, cost model, PFFFT contract, IR crossfades, update scheduling and staleness, tail caching, fractional delay kernels, denormals and NaN propagation, achievable residual levels in float32, allocation-tracking tests. Phases 06, 07, 10, 13.

How to use it: read the "Reviewer's checklist" section first and apply the questions the diff makes
relevant; use the earlier sections to settle a disagreement with the author or to re-derive a number.
Every fact carries its source URL and the date it was verified (researched live on 2026-11-04).
Facts marked "(unverified, from memory)" must be verified before they are cited in a review; when
you verify one, fix it here. See `knowledge-inventory.md` for which facts go stale and how to
re-check them.

## Contents

- 1. Uniformly partitioned overlap-save (UPOLS) with a frequency-domain delay line
  - 1.1 The algorithm, as published
  - 1.2 Latency
  - 1.3 N x M matrix sharing input spectra
  - 1.4 Index/ordering mistakes (the bugs a reviewer should look for)
- 2. Cost model
  - 2.1 Per-block arithmetic
  - 2.2 Non-uniform partitioning (the remedy) and why it is deferred
- 3. PFFFT specifics
  - 3.1 Verified against Julien Pommier's original `pffft.h` (Bitbucket) [S7]
  - 3.2 The maintained fork: marton78/pffft [S11][S12]
  - 3.3 Other libraries' conventions (for the Fft wrapper's tests)
- 4. IR switching and crossfades
  - 4.1 Equal-gain vs equal-power
  - 4.2 Crossfading outputs vs crossfading coefficients
  - 4.3 Click-free requirements and the analytic test
  - 4.4 Cost during the fade
  - 4.5 Why a static-IR crossfade is Doppler-free, and what it does instead
- 5. Update scheduling for moving sources (phase 10)
- 6. Fractional delay for image sources
- 7. Denormals, NaN/Inf, and what -120 dB means in float32
  - 7.1 Denormals and FTZ/DAZ
  - 7.2 NaN and Inf
  - 7.3 Is a -120 dB residual achievable in float32?
- 8. Allocation-tracking tests in C++
- 9. Reviewer's checklist
  - Convolver (`Fft`, `PartitionedConvolver`, `IrSet`)
  - Crossfade (`CrossfadingConvolver`)
  - Scheduler and automation (phase 10)
- Sources (all accessed 2026-11-04)

---

Scope: `src/sim/conv/` (Fft, PartitionedConvolver, CrossfadingConvolver, RealtimeEngine) from
`docs/phases/phase-06.md`, and the movement/scheduling work from `docs/phases/phase-10.md`
(AQ4, AQ10, AX1). Research date: 2026-11-04. Every fact carries a source tag `[Sn]` resolved in
the source list at the end (URL + access date). Facts marked **(unverified, from memory)** were not
confirmed against a live source today. Facts marked **(derived)** are my own arithmetic from sourced
inputs; check the arithmetic, not the source.

Repo-specific numbers used throughout: fs = 48 kHz, P = 512 (FFT K = 2P = 1024), 2x2 matrix,
IR lengths 1/3/6/12 s, 30 ms equal-gain crossfade (= 1440 samples = 2.81 P-blocks), builder cadence
20 ms, worst-case staleness budget 100 ms (phase-10 acceptance).

---

## 1. Uniformly partitioned overlap-save (UPOLS) with a frequency-domain delay line

### 1.1 The algorithm, as published

Wefers & Vorlaender (DAFx-11) describe the generalized uniformly partitioned algorithm with block
length B, FFT size K, sub-filter length L = K - B + 1 [S1]. With the common choice K = 2B (so
L = B + 1; engines that cut the IR into exactly B-sample partitions waste one coefficient slot, which
is fine) the per-block steps are, quoting the paper's description [S1]:

- "A time-domain input buffer acts as a sliding window of K samples on the stream of input samples.
  With each new input block, its contents are shifted K-B elements to the left and the new input
  block of B samples is then placed to the right."
- "The whole buffer is then transformed using a K-point real-to-complex FFT and the resulting DFT
  spectrum is stored in a frequency-domain delay-line (FDL). Before this step, the FDL is shifted by
  one slot."
- "All DFT spectra in the FDL are now point-wise complex-valued multiplied with the corresponding DFT
  spectra of the transformed filter parts. All results are summed up in a frequency-domain
  accumulation buffer."
- "Next the contents of this buffer are transformed back into the time-domain using a K-point
  complex-to-real IFFT. The B left values form the output block. The other K-B values are
  time-aliasing and discarded."

  NOTE the paper's wording "the B left values form the output block": that is the paper's own
  convention for where the new samples sit. In the textbook overlap-save layout used above
  (old samples left, new samples right, filter zero-padded at the END), the **first** K-B = P
  output samples are the aliased ones and the **last** P are valid. The two conventions are
  mirror images; a code base must pick one and keep IR padding, input placement and discard
  half consistent (see 1.4).
- Why overlap-save rather than overlap-add: "Overlap-Save computes more efficiently than Overlap-Add,
  because it saves extra additions of the partial outputs." [S1] (OLA must store and add the
  overlapping K-B tail of every block; OLS discards instead.) Brandtsegg & Saue (DAFx-17) build their
  time-variant convolver on OLA and concede "The Overlap-Save scheme (OLS) is found to compute more
  efficiently than OLA [14]." [S2]
- Why the FDL works: "Necessary delays for the subfilters, are directly implemented in the
  frequency-domain, using a frequency-domain delay-line (FDL) [14]. This is possible, because all DFT
  spectra share the same size." and "Using these two techniques, only one FFT and one IFFT have to be
  computed for each processed stream block. Thereby the major computational load goes back to the
  complex-valued multiplications." [S1]
- Wikipedia's overlap-save page (textbook form): input blocks overlap by M-1 samples, each block is
  circularly convolved at length N >= L+M-1, the M-1 leading outputs are dropped, the remaining L
  samples are appended to the output; "M - 1 input (or output) samples from segment k are needed to
  process segment k + 1." [S3]

Pseudo-code for P-sample partitions, K = 2P, Np = ceil(L_ir / P) partitions, one path:

```
prepare (off audio thread):
  for j in 0..Np-1:
     h_j = ir[j*P : (j+1)*P]            // last one zero-filled to P
     H[j] = FFT_K( [h_j | zeros(P)] )   // zero-pad at the END, K = 2P
  fdl = Np spectra, all zero; w = 0     // ring-buffer write index
  inbuf = zeros(2P)                     // [previous P | new P]

per P-block (audio thread):
  inbuf[0:P] = inbuf[P:2P]; inbuf[P:2P] = x_block
  X = FFT_K(inbuf)
  fdl[w] = X
  acc = 0
  for j in 0..Np-1:
     slot = (w - j) mod Np               // newest spectrum pairs with partition 0
     acc += fdl[slot] * H[j]             // complex MAC, bin-wise
  w = (w + 1) mod Np
  y_full = IFFT_K(acc) * (1/K)          // PFFFT is unscaled (section 3)
  y_block = y_full[P:2P]                 // discard the FIRST P (aliased), keep the LAST P
```

### 1.2 Latency

- Inherent latency of UPOLS = one block B (= P): an input sample that arrives at the start of a block
  can only influence output after the whole block has been collected and transformed [S1] (the paper
  treats B as "the desired input-to-output latency").
- The UHSDR notes give it as `latency = size * DF / SR` for their decimated case, i.e. one partition of
  samples at the processing rate [S4].
- When the host block n != P the engine must accumulate input into P-sized blocks and prime an output
  FIFO with P zeros so the reported latency stays exactly P independent of n **(derived)**. Phase 06's
  acceptance "latencySamples() equals the measured offset ... (exactly P + pre-roll)" tests this; the
  pre-roll is AX1's `kAlignPreRollSamples`.
- For n < P the UPOLS step (all Np MACs + 2 FFTs) runs only on every ceil(P/n)-th callback, so the
  **per-callback worst case is the whole step inside a budget of n/fs**. At n = 64 the budget is 1.33 ms
  while the average budget at P = 512 is 10.67 ms: an engine that is "15% of one core at 512" can be
  >100% of a 64-sample callback. A self-reported measurement in the Drenched project: 6 s stereo IR at
  48 kHz, worst callback at 64 samples 116-121% (uniform) vs 37-40% after staging; at 256 samples
  33-35% vs 12-19% [S5]. Reviewer consequence: AQ10 is measured at 512; the benchmark should also print
  the worst single callback at 64 and 128, or the plugin should spread the MAC over sub-blocks.
- For n > P the engine runs floor(n/P) or more sub-steps per call and must loop; the remainder is
  carried in the accumulator **(derived)**.

### 1.3 N x M matrix sharing input spectra

- Per block: N forward FFTs (one per input), N FDLs, N*M*Np complex MACs, M inverse FFTs (one per
  output, each accumulating the N inputs' contributions in the same frequency-domain accumulator)
  **(derived from [S1]'s structure)**. Garcia's abstract already notes multichannel sharing: "for
  multiple-source 3-D audio rendering, where one partition can be shared across channels" [S6].
- During a crossfade (two IR sets A and B, shared FDL) the MAC count doubles: 2*N*M*Np, and there are
  2*M IFFTs (or M IFFTs if the ramp is applied in the DFT domain, section 4.4). Budget the benchmark
  for the fade, not the steady state **(derived)**.

### 1.4 Index/ordering mistakes (the bugs a reviewer should look for)

- **Time-reversed FDL.** Pairing the newest spectrum with the LAST partition (or decrementing the
  partition index while decrementing the slot index) convolves with a time-reversed IR. UHSDR's notes
  spell out the correct pairing: "pairs the newest input spectrum with partition 0, the previous round's
  spectrum with partition 1, and so on" and warn that the ring-buffer decrement "must wrap correctly.
  Otherwise the input-to-partition pairing breaks." [S4]. Test: IR = delta at sample j*P + d; the output
  of an impulse must appear at exactly latency + j*P + d, for several j including the last partition.
- **Off-by-one in partition count.** Np = ceil(L/P); L = P gives 1, L = P+1 gives 2, L = P-1 gives 1
  with zero fill. Phase 06's IR lengths (1, P-1, P, P+1, 48 000, 144 000) are chosen to hit exactly these
  edges. 144 000 / 512 = 281.25 -> 282 partitions; 576 000 / 512 = 1125 exactly **(derived)**.
- **Forgetting to zero-pad the IR partitions to K = 2P.** Each partition is P coefficients plus P zeros.
  Without the padding the circular convolution of a 2P input window with a 2P-long filter block aliases
  everywhere and no half is clean. The UHSDR setup does the padding explicitly (zeros in one half,
  coefficients in the other) [S4]; DAFx-17: "The inputs partitions x_i(n) and h_j(n) are padded with N_P
  zeros and thereby satisfies the condition for circular convolution without time-aliasing." [S2]
- **Wrong half discarded.** Under the textbook layout (old samples first, new samples last, filter
  padded at the end), the first P output samples are aliased and the last P are valid [S3]. If the
  code pads the IR at the FRONT (zeros first, as UHSDR's `maskgen` does [S4]) the valid/aliased halves
  swap. Mixing the two conventions produces either a P-sample offset or aliasing garbage. A delta-IR
  null test with random input catches both.
- **Scaling of the inverse FFT.** PFFFT, FFTW and KissFFT are all unnormalised (section 3): the
  product of forward and backward transforms is K * x. Scale once by 1/K = 1/(2P). Scaling by 1/P or
  scaling twice is a clean +/-6.02 dB gain error that "sounds fine" but fails any null test. Scaling per
  partition inside `pffft_zconvolve_accumulate(..., scaling)` is legitimate (it is one multiply per bin
  anyway) but must not be combined with a second 1/K after the IFFT **(derived)**.
- **Accumulator not cleared per block** (or cleared only when there is one partition): old block's sum
  leaks into the next; the symptom is a growing, smeared output. Use a non-accumulating multiply for
  partition 0 or memset the accumulator each block.
- **Forward FFT layout mismatch.** Both operands of a bin-wise multiply must be in the same layout. With
  PFFFT, `pffft_transform` output is in an internal "unordered" layout usable only by
  `pffft_zconvolve_accumulate`/`pffft_zreorder`; `pffft_transform_ordered` gives the interleaved
  natural order [S7]. Transforming the IR with one and the input with the other yields noise.
- **Packed DC/Nyquist bins.** Real FFTs of size K produce K/2+1 complex bins [S8]; many libraries pack
  the purely real DC and Nyquist values into one complex slot. A hand-written complex multiply loop over
  the packed array multiplies DC by Nyquist. Use the library's convolve helper or unpack first.
- **FDL sized to the current IR, not the maximum.** When the IR switches from 282 to 1125 partitions,
  the new IR must see input history that is already 1125 slots deep; size the FDL at prepare() to the
  maximum partition count of any IrSet the engine may receive, and have both crossfade states index the
  same FDL **(derived from the phase-06 design: "two convolver states, A and B, sharing input
  history")**.
- **Input accumulator phase vs host block.** With n = 37 the P-boundary drifts relative to the host
  callback. Anything keyed to "the block boundary" (crossfade start, IR pickup, latency measurement)
  must use the internal P-block counter, not the host callback index.

---

## 2. Cost model

### 2.1 Per-block arithmetic

Wefers & Vorlaender's cost per output sample for uniform partitioning with real-valued FFTs (their
eq. 8) [S1], written out in plain text:

```
T_stream(N, B, K) = (1/B) * [ 2*k*K*ln(K)                                  // one FFT + one IFFT
                            + 6 * ceil(N/(K-B+1)) * ceil((K+1)/2)          // complex multiplies
                            + 2 * (ceil(N/(K-B+1)) - 1) * ceil((K+1)/2) ]  // spectrum additions
k ~= 1.7 (FFTW3 on a Core2, powers of two, natural log)
```

- "A complex-valued multiplication ... requires six arithmetic operations (four multiplications and
  three additions)"; Hermitian symmetry means "only ... ceil((K+1)/2) symmetric DFT coefficients out of the
  total N DFT coefficients need to be stored and processed"; "for the accumulation of P spectra only (P-1)
  spectrum additions need to be carried out." [S1]
- Their Table 1 (ops per output sample, single path) for the standard K = 2B [S1]:
  N=4096/B=512: 109.3; N=16384/B=512: 301.6; N=65536/B=512: 1071.1; N=65536/B=128: 4139.5;
  N=65536/B=1024: 562.3. Optimal K beat K = 2B by only 0-3% for N <= 16384 at B = 512 but by 39%
  (768.4 vs 1071.1) at N = 65536, B = 512. Their conclusion: K = 2B "is generally a good choice".
- Scaling to this repo **(derived, MAC-dominated so roughly linear in N)**: 12 s at 48 kHz is
  N = 576 000, Np = 1125 partitions of 512; K = 1024 has 513 bins. Per block per path:
  1125 x 513 = 577 k complex MACs; with the paper's op counts ~4.6 M ops/block, ~9 000 ops per output
  sample (1071 x 576000/65536 = 9 400 from the table). 2x2 = 4 paths: ~1.8 G ops/s at 48 kHz.
  3 s: Np = 282, ~2 300 ops/sample/path, ~440 M ops/s for 2x2.
- Why it is O(L/P) per output sample: each output sample costs (Np x bins)/P = (L/P)(P+1)/P ~ L/P
  complex MACs plus the FFT share (2 K log K)/P, which is tiny by comparison once Np >> log K
  **(derived from eq. 8)**.
- **Memory traffic, not FLOPs, is the practical limit for 12 s** **(derived)**: each spectrum is
  513 x 8 B = 4.1 kB; per block the MAC loop streams (4 paths x 1125 IR spectra + 2 FDLs x 1125
  slots) x 4.1 kB = ~28 MB, every 10.67 ms = ~2.6 GB/s, far beyond L2 and larger than most L3 caches.
  For 3 s it is ~7 MB per block, mostly cache-resident. Expect a non-linear jump in measured CPU between
  3 s and 12 s. Reviewers should ask for the benchmark's numbers at 6 and 12 s, not an extrapolation.
- Reported real-world numbers (all self-reported, none peer-reviewed): Filmcraft issue #3134, 60 s
  stereo at 48 kHz, 512-sample blocks, uniform 256-sample partitions: the complex MAC was 74% of the
  effect's time [S5]. Drenched PR #42 (6 s stereo): worst-callback figures in 1.2 [S5]. The
  Wefers thesis contains benchmark-based semi-empirical cost models on real hardware but I could not
  read the PDF today (the RWTH server returned a JavaScript challenge) **(unverified, from memory:
  thesis chapters 5-7 report per-block times for uniform/non-uniform schemes on Intel hardware)** [S9].

### 2.2 Non-uniform partitioning (the remedy) and why it is deferred

- Gardner, "Efficient Convolution without Input-Output Delay", AES preprint 3897 (Nov 1994), JAES 43(3)
  pp. 127-136 (Mar 1995): "A hybrid convolution method is proposed, which combines direct-form and block
  FFT processing" yielding "a zero delay convolver"; the IR is cut into sections of increasing size so
  that each block FFT result is ready before it is needed [S10]. Full text is paywalled at AES. A
  2005 linux-audio-dev post and a 2012 CoreAudio-list post claim Lake DSP held a patent on the scheme
  (secondhand; **unverified**) [S10].
- Garcia, "Optimal Filter Partition for Efficient Convolution with Short Input/Output Delay", AES 113th
  Convention, Oct 2002: given target I/O delay and filter length it computes the non-uniform partition
  that minimises cost; covers the multichannel case [S6]. Paywalled.
- Wefers & Vorlaender (DAFx-11) [S1] and the Wefers thesis [S9] generalise to freely chosen FFT sizes
  and non-uniform partitions. Asymptotically non-uniform schemes are O(log L) per sample instead of
  O(L/P) **(unverified, from memory; standard result quoted in the thesis)**.
- Complexity cost: sections with K > 2P have deadlines several blocks away, so their FFT/MAC work must be
  time-distributed across callbacks or run on worker threads with deadlines; a missed deadline is a
  dropout, and the scheduling makes determinism and allocation-freedom harder to prove. That is why
  phase 06 keeps it as a follow-up and why JUCE's `dsp::Convolution` exposes it as an option "if the
  impulse response size is large, or if the algorithm is too CPU intensive" without numbers [S5].

---

## 3. PFFFT specifics

### 3.1 Verified against Julien Pommier's original `pffft.h` (Bitbucket) [S7]

- Sizes: "supports only transforms for inputs of length N of the form N=(2^a)*(3^b)*(5^c), a >= 5,
  b >=0, c >= 0" and "(32, 48, 64, 96, 128, 144, 160, etc are all acceptable lengths). Performance is
  best for 128<=N<=8192." That is the REAL-transform rule (multiple of 32). The complex rule is a >= 4,
  i.e. a multiple of 16 **(unverified, from memory; the quoted line is the real-transform one)**.
  K = 1024 = 2^10 is fine; so are 256 and 512.
- Ordering: `pffft_transform_ordered` is "Similar to pffft_transform, but makes sure that the output is
  ordered as expected (interleaved complex numbers)." The plain `pffft_transform` output is in an
  internal SIMD-friendly order that is only meaningful to `pffft_zreorder` and
  `pffft_zconvolve_accumulate` [S7]. Use the unordered transform in the convolver (it is the faster one)
  and the ordered one only for analysis/tests.
- Convolution helper, verbatim signature and comment [S7]:
  `void pffft_zconvolve_accumulate(const PFFFT_Setup *setup, const float *dft_a, const float *dft_b,
  float *dft_ab, float scaling);` -- "Perform a multiplication of the frequency components of dft_a and
  dft_b and accumulate them into dft_ab." / "the operation performed is: dft_ab += (dft_a * fdt_b)*scaling".
  This is exactly the FDL inner loop. The fork's README says its inner loop compiles to FMA on
  gcc 12 / clang 14, x86-64 and i686, float (SSE) and double (AVX) [S11].
- Alignment: "all (float*) pointers in the functions below are expected to have an "simd-compatible"
  alignment, that is 16 bytes on x86 and powerpc CPUs" and "the float buffers must have the correct
  alignment (16-byte boundary on intel and powerpc)." Use `pffft_aligned_malloc`/`pffft_aligned_free`
  [S7]. The marton78 fork with AVX needs 32-byte alignment and its `pffft_aligned_malloc` aligns to
  64 bytes **(unverified, from memory)**. `std::vector<float>` is NOT guaranteed to satisfy this.
- Scaling: "Transforms are not scaled: PFFFT_BACKWARD(PFFFT_FORWARD(x)) = N*x." / "Typically you will
  want to scale the backward transform by 1/N." [S7]
- Thread safety: "the returned PFFFT_Setup structure is read-only so it can safely be shared by
  multiple concurrent threads." / "this struct can be shared by many threads as it contains only
  read-only data." [S7]. The per-call `work` buffer is per thread; passing NULL makes the function use a
  stack VLA/alloca of size N floats **(unverified, from memory)** -- fine on the audio thread for
  K = 1024 but give it an explicit aligned work buffer so the stack use is visible.
- Licence: "Copyright (c) 2013 Julien Pommier", "Based on original fortran 77 code from FFTPACKv4 from
  NETLIB", "the following FFTPACKv5 license applies to FFTPACKv4 sources. My changes are released under
  the same terms." -- a 3-condition BSD-style licence with the usual AS-IS disclaimer [S7]. Record it in
  `docs/THIRD_PARTY.md` as "FFTPACK v5 licence (BSD-like)".
- Memory: "The FFT functions don't allocate memory and take a 'work' array in their arguments." [S11]
  (`pffft_new_setup` does allocate; call it in prepare(), never in process().)

### 3.2 The maintained fork: marton78/pffft [S11][S12]

- GitHub `marton78/pffft` is a fork of Pommier's Bitbucket PFFFT; common ancestor commit 16490be
  (2014-09-03); README maps every later upstream commit to its port. 390 stars, 96 forks (page values on
  2026-11-04). "The license is BSD-like." A `LICENSE.txt` is in the tree [S11].
- Fork additions per README: double precision (`pffft_double.h`, `PFFFT_USE_TYPE_DOUBLE` default ON),
  AVX/AVX2, a C++ wrapper, PFFASTCONV (FIR filtering built on PFFFT), zero-phase convolution helpers
  (`pffft_zconvert_zp()` / `pffft_zconvolve_zp()`: "with default scaling the forward transform ->
  zconvolve_zp -> backward transform yield circular convolution at unit gain"), unscaled
  `pffft_zconvolve()` and `pffft_zconvolve_scale()`, CMake with FetchContent/add_subdirectory support
  (tests/benchmarks auto-disabled when consumed), ctest [S11].
- SIMD backends: SSE1/AVX/AVX2 (x86), AltiVec (PowerPC, float only; double runs scalar), NEON (ARM
  including Apple Silicon), WASM SIMD, RISC-V RVV 1.0 [S11].
- Latest commits as of 2026-11-04 [S12]: 7ae36e8 (Nov 4 2026) "cmake: offer MSVC /arch values as a
  dropdown ..."; 5055b93 (Nov 3 2026) "Bump the CMake package version to 1.2.0"; 9c59148 (Nov 3 2026)
  "pffft_double.c: drop the unneeded <alloca.h> include". No GitHub Releases are published; pin by
  commit hash in FetchContent (CLAUDE.md requires a pinned tag or commit; there is no tag to pin).
- NOTE: the raw header of the fork was not reachable through this session's proxy (404 via
  raw.githubusercontent and jsdelivr); the API facts above come from the original header, which the fork
  preserves, plus the fork README. Helper names such as `pffft_min_fft_size()`, `pffft_is_valid_size()`,
  `pffft_nearest_transform_size()` exist in the fork **(unverified, from memory)**.

### 3.3 Other libraries' conventions (for the Fft wrapper's tests)

- FFTW: "Like FFTW's complex DFT, these transforms are unnormalized"; r2c outputs "only ... elements
  0...n/2 of Y (n/2+1 complex numbers)"; forward then backward scales by n [S8].
- KissFFT: "neither direction is normalized" in floating-point builds (divide by nfft after the inverse);
  "The real (i.e. not complex) optimization code only works for even length ffts"; "Revised BSD License"
  [S13].
- A library-independent Fft wrapper test: FFT of a delta is all-ones; IFFT(FFT(x)) / K == x within
  1e-6; FFT of a pure cosine at bin m has energy only at m; compare against a naive O(N^2) DFT in double
  for K = 1024 **(derived)**.

---

## 4. IR switching and crossfades

### 4.1 Equal-gain vs equal-power

- Fink, Holters & Zoelzer (DAFx-16) [S14]: "It is well-known that the cross-faded signal power depends
  on the correlation of the signals to be mixed. Uncorrelated signals are cross-faded using the
  so-called Equal Power Crossfade featuring a -3 dB weighting in the transition center. In contrast,
  correlated signals are supposed to be linearly cross-faded corresponding to a weighting of -6 dB."
  Their derivation (eqs. 7-11): with equal variances sigma^2 and correlation r,
  `E[x_mix^2] = sigma^2 (w^2 + 2 w wi r + wi^2)`, so power preservation needs
  `w^2 + 2 w wi r + wi^2 = 1`; for r = 1 that is `(w + wi)^2 = 1` -> w + wi = 1 (linear, equal gain);
  for r = 0 it is `w^2 + wi^2 = 1` (sin/cos, equal power). Typical take-splice crossfades are
  "in the range of 10-30 ms".
- Two IRs of the same room with slightly moved emitter are highly correlated in the direct sound and
  early reflections (same arrival structure shifted by a few samples) and less correlated in the
  diffuse tail. AQ4's equal-gain choice is right for the parts that matter for clicks; the tail may dip
  by up to 3 dB at the fade centre when r -> 0, which over 30 ms is not audible but shows up as a
  level dip in a long-tail RMS plot **(derived from [S14])**.
- Equal gain means g_B(n) = 1 - g_A(n) for every n; the shape (linear, smoothstep, raised cosine) is free.
  A linear ramp has derivative discontinuities at its two ends; with a 30 ms ramp the spectral splatter
  is at < 33 Hz-scale modulation and inaudible, but a raised-cosine equal-gain ramp
  `g = 0.5 - 0.5 cos(pi t/T)` removes the kink at no cost. The phase-06 acceptance test fixes g to a
  **linear** ramp, so a smoother ramp would need the analytic reference changed too.

### 4.2 Crossfading outputs vs crossfading coefficients

- Wefers & Vorlaender (Forum Acusticum 2014, "Efficient time-varying FIR filtering using crossfading
  implemented in the DFT domain"): "Instantaneous switching of filters is known to cause discontinuities
  in the waveform"; output crossfading is "the common method to avoid such audible artifacts"; their
  contribution moves the linear crossfade into the DFT domain of an overlap-save convolver so that it
  costs little more than one convolver [S15]. (Abstract and secondary quotes; the PDF itself returned 403
  today.)
- Brandtsegg & Saue (DAFx-17) restate the two options [S2]: hard switching
  `y = x*hA for n < nT, x*hB for n >= nT` "is a cheap implementation, but the hard switching is known to
  cause audible artifacts from discontinuities in the output waveform"; crossfading filters "x(n) with
  both impulse responses, hA(n) and hB(n), in a transition interval and then crossfade between the two
  outputs". Their own alternative is partition-by-partition coefficient replacement (no extra cost, but
  the transition length is then fixed to the IR length and "the replacement time nT must be at a
  partition border: nT = k * N_P").
- Crossfading the IR **coefficients** (interpolating H_A -> H_B per block) is equivalent to a
  piecewise-constant per-block crossfade of outputs and therefore produces a staircase in the output
  gain at block rate (zipper). Crossfading the two **outputs** sample-by-sample is what makes the
  phase-06 analytic null hold **(derived)**.

### 4.3 Click-free requirements and the analytic test

- Both states must see the same input history. If state B starts with an empty FDL, `x*B` is missing
  its tail for Np blocks and the crossfaded output is `(1-g)(x*A) + g*(x*B_truncated)`; this fails the
  null and is audible as a tail dropout on every move. Phase 06 therefore specifies "two convolver
  states, A and B, sharing input history".
- Start at the internal P-block boundary where the mailbox is read; the ramp index must run across host
  callbacks (30 ms = 1440 samples = 2.81 P-blocks at 512, 22.5 blocks at 64). A ramp that is restarted
  or quantised per callback causes a level step at every callback boundary.
- Apply the ramp in the time domain after the overlap-save discard, i.e. on valid output samples only.
  Ramping the frequency-domain accumulators is a block-constant gain (see 4.2).
- The null test from phase 06, in formula form:

```
yref[n] = (1 - g[n]) * (x * A)[n] + g[n] * (x * B)[n],   g[n] = clamp((n - n0) / Nf, 0, 1)
n0 = first output sample of the P-block at which the swap is picked up (+ latency)
Nf = round(0.030 * fs) = 1440 at 48 kHz
pass: 10*log10( sum (y - yref)^2 / sum yref^2 ) < -100 dB
```
  Compute `x*A` and `x*B` by direct convolution in double. n0 is the internal P-block boundary, so for
  host block 37 the test needs the engine to expose the pickup sample (or the test drives n = P).
- Hard-switch negative control (phase 10 `MAKROOF_TEST_HARD_SWITCH`): replace g with a unit step. The
  reviewer's question is whether it bypasses only the ramp, keeping the same mailbox, the same pickup
  block and the same deferred release path, so that the click detector really exercises the production
  path.

### 4.4 Cost during the fade

- Two full MAC passes and two IFFTs per output while fading; with continuous automation (20 ms cadence,
  30 ms fade) the engine is fading essentially always, so the steady-state CPU is the fading CPU.
  Wefers & Vorlaender's DFT-domain crossfade avoids the second IFFT by expressing the linear ramp as a
  short frequency-domain convolution of the two accumulators [S15] **(mechanism from memory;
  only the abstract was verified)**. For this repo: measure with fades, not without.

### 4.5 Why a static-IR crossfade is Doppler-free, and what it does instead

- Doppler arises from a time-varying propagation delay; it is simulated with a delay line whose read
  pointer moves relative to the write pointer: "Moving read/write pointers simulate moving
  listener/source", with delay growth rate `D'(t) = -v_ls/c` (Smith et al., DAFx-02) [S16].
  A sequence of static IRs crossfaded over 30 ms never moves a read pointer, hence no pitch shift (AX1).
- What it does produce: during each fade the direct sound is the sum of two copies offset by the delay
  difference delta between the IRs, i.e. a comb filter with the first notch at f = fs/(2 delta)
  **(derived)**. For an emitter moving at 1 m/s with 20 ms updates delta = 2 cm = 2.8 samples at 48 kHz
  (first notch ~8.6 kHz, mild); at 10 m/s delta = 28 samples, first notch ~860 Hz, strongly audible as
  flutter at the update rate. The SMC 2024 paper by Carpentier reports exactly this: swapping/crossfading
  filters "causes comb filter effects, which become severe when differences in distance increase",
  while a fractional delay line "causes a pitch shift comparable to a Doppler effect" [S17]
  (search-engine summary; the PDF host is not reachable from this session). AX1 keeps the nearest
  emitter at t = 0 so only relative delays change, which bounds delta by the change in path-length
  differences, not absolute distance.
- Related evidence on update timing: a binaural-rendering study notes "a block size of N=1024 samples
  delays the update by more than 10 ms, which can increase temporal artifacts", and that comb-filter
  artefacts need the crossover "at least one, better two octaves lower than the comb-filter notch"; a
  navigable-VR study used a 50 ms crossfade between neighbouring RIRs for responsiveness [S18].
  The RWTH "scheduled simulation results" paper reports that "a low simulation update rate could cause a
  sudden 'jump'" and fixes it by interpolating scheduled results [S18].

---

## 5. Update scheduling for moving sources (phase 10)

Design facts from AQ4/phase 10: builder on a background thread, at most one rebuild per 20 ms,
coalesced (latest scene wins), 30 ms equal-gain crossfade, tail cached when only positions change,
synchronous rebuild in non-realtime mode, worst-case staleness <= 100 ms, no allocation in
processBlock. The literature does not give a canonical design; the following is engineering practice
**(derived unless tagged)**.

- **Coalescing:** a single-slot "pending scene" written by the parameter thread, read by the builder;
  writing overwrites (latest wins) rather than enqueuing. The mailbox into the audio thread is also a
  single slot (phase 06: "If another IR arrives during a crossfade, it waits in the mailbox (latest
  wins)"). Two levels of coalescing means at most two scenes are ever "in flight".
- **Rate limiting:** the 20 ms cadence is a minimum period between build starts, not a timer that
  fires regardless; if a build takes longer than 20 ms the next starts immediately with the newest scene
  (phase 10 text). Reviewer: a build that takes 25 ms must not "catch up" by running twice.
- **Starvation / head-of-line blocking:** with a 30 ms fade longer than the 20 ms cadence, the audio
  side cannot start a new fade until the current one ends, so under continuous automation the effective
  update period is 30 ms and every other built IR is discarded. Discarding is fine (latest wins) only if
  the discarded IrSet goes to the deferred-release queue, never freed on the audio thread.
- **Staleness metric:** time from parameter change to IR "going live"; decompose it as
  `wait_for_cadence (<= 20) + build_time + mailbox_pickup (<= one P-block, 10.7 ms) + fade_queue
  (<= 30) [+ fade (30) if "live" means fully live]`. Worst case without the fade term:
  20 + build + 10.7 + 30 = 60.7 + build, so the 100 ms acceptance leaves ~40 ms for the build; AQ10
  allows 50 ms builds for order <= 30, which can exceed the budget at high orders in large rooms (the
  phase-10 risk). Record which definition of "live" the metric uses.
- **Realtime-sim clock:** the builder runs on a real thread but a simulated clock decides when results
  are picked up; the reviewer must check that the simulated clock, not wall time, gates both the cadence
  and the pickup, otherwise CI timing noise makes the scenario suite flaky and non-reproducible.
- **Synchronous rebuild offline (determinism):** in non-realtime mode rebuild per block on the audio
  thread before processing. "Bit-identical across two runs" also needs: seeded tail noise (`tailSeed`),
  fixed floating-point summation order (no parallel reductions, no `std::unordered_*` iteration order
  feeding sums), identical FTZ/DAZ state on every thread that touches audio (section 7), no reads of
  uninitialised memory, identical SIMD dispatch (a build on a thread with a different ISA path would
  differ), and no time-based decisions. Two runs on one machine should be compared bit-wise, not in dB.
- **Tail cache key (phase 10: "room dimensions, materials, mode, seed, sample rate")** -- a complete key
  must include every input the tail depends on. Candidates that are easy to omit: sample rate (tail
  length in samples), per-surface material IDs **and** per-band coefficients (if materials.json can be
  edited), scattering coefficients, air-absorption parameters (AX4: temperature/humidity), reflection
  order / ISM-to-tail crossover time, tail length / RT target, filterbank or band-reconstruction
  settings, `tailSeed`, output mode (binaural/HRTF set vs stereo), the HRTF resource version, the
  contract version, and the build options that change arithmetic (float vs double path). Compare key
  fields bit-exactly (hash of canonical bytes), not with an epsilon, so a 1e-9 change in room width does
  not silently reuse a tail built for a different room while the early part changes.
- **Energy matching after position changes:** phase 10 keeps the tail and "re-runs energy matching";
  the matching gain depends on the early part, so caching the matched tail (instead of the raw tail plus
  a gain recomputed per build) is the classic stale-tail bug.
- **Mailbox memory safety:** `std::atomic<IrSet*>::exchange` hands ownership; the audio thread must push
  the displaced pointer to a lock-free deferred-release queue drained by a non-audio thread; the
  `shared_ptr` control block must not be released on the audio thread (its destructor frees). TSan with
  two producer threads hammering `requestIr` (phase 06 test) is the right tool; ASan for the leak.

---

## 6. Fractional delay for image sources

- Ideal fractional delay: h(n) = sinc(n - D). Windowed-sinc design: truncate to length L and apply a
  window centred on the delay. Smith: w(n) is "any real symmetric window (e.g., Hamming, Blackman,
  Kaiser)"; "For best results, Delta ~= L/2" (the window must be centred on the fractional delay, i.e. the
  kernel introduces an integer offset of (L-1)/2 that must be subtracted from the target delay) [S19].
  Laakso et al.'s review notes the windowed-sinc FD design "uses an asymmetric window function with a
  fractional offset" and that "the coefficients must be scaled to get the best approximation" (i.e.
  renormalise the truncated kernel to unit DC gain) [S20].
- **Half-length offset bug:** placing a kernel of length L so that its first tap sits at the integer
  arrival sample delays the arrival by (L-1)/2 extra samples. Every path must subtract the same offset;
  mixing a centred direct path with an un-centred reflection path shifts the ISM structure by
  (L-1)/2 samples (0.33 ms for L = 33), which shows up in arrival-time tests and in the AX1 alignment.
- **Truncation at the buffer start:** the first arrival's kernel extends (L-1)/2 samples before its
  centre; if the centre is at sample 0 the left half is cut off, the kernel no longer sums to the
  intended gain and the arrival is biased late. The pre-roll (`kAlignPreRollSamples`, AX1) exists to
  hold the left half; reviewer: is the pre-roll >= (L-1)/2 + max fractional kernel support?
- **Kaiser design equations** (Smith, after Kaiser) [S21]:
  `beta = 0.1102 (A - 8.7)` for A > 50 dB; `beta = 0.5842 (A-21)^0.4 + 0.07886 (A-21)` for
  21 < A < 50; `beta = 0` for A < 21. Order `M = (A - 8) / (2.285 * dw)`, dw = transition width in
  rad/sample. "Increasing beta widens the mainlobe and decreases the amplitude of the sidelobes" [S22].
  Worked numbers **(derived)**: A = 80 dB -> beta = 7.86; with L = 33 taps the transition is
  dw = 72/(2.285 x 32) = 0.98 rad = 0.31 pi (7.5 kHz wide at 48 kHz), so the kernel is flat only to
  roughly 0.7 Nyquist; A = 60 dB -> beta = 5.65, dw = 0.71 rad with L = 33. The Kaiser-windowed sinc
  "stopband starts out close to -80 dB" in Smith's example [S23].
- **Lagrange FIR interpolation:** coefficients `h(n) = prod_{k != n} (D - k) / (n - k)`, n, k in
  0..N; maximally flat at DC; the basis polynomial "is an order N polynomial having zeros at all of the
  samples except the kth, where it is 1", first order "reduces to linear interpolation" [S24]. Accuracy
  is best when D lies within the central interval of the filter, (N-1)/2 <= D <= (N+1)/2
  **(unverified, from memory; Laakso et al. 1996)**; magnitude error rises towards Nyquist, so
  Lagrange is a bandlimited approximation only for low orders at low frequencies.
- **Thiran allpass:** order-N IIR with "maximally flat group-delay at dc" equal to Delta; coefficients
  `a_k = (-1)^k C(N,k) prod_{n=0}^{N} (Delta - N + n) / (Delta - N + k + n)`, a_0 = 1 [S25]; stable
  only for "D > N - 1" (Laakso review as quoted by a search summary) [S20]; rule of thumb Delta ~= order
  [S25]. Not useful for building a static IR (it is IIR; you would have to run it to length), and its
  state makes it unsuitable for per-block time variation; mention it so reviewers know why it was not
  chosen.
- **Effect on arrival-time tests:** a windowed-sinc arrival with fractional part f has its sample peak
  at round(D); peak-picking therefore has +/-0.5-sample quantisation plus +/-1 sample when two taps are
  nearly equal (f ~= 0.5). Tests comparing ISM arrival times to geometry should either allow +/-1 sample
  or estimate sub-sample arrival by parabolic interpolation of the peak / cross-correlation with the
  kernel **(derived)**.

---

## 7. Denormals, NaN/Inf, and what -120 dB means in float32

### 7.1 Denormals and FTZ/DAZ

- Subnormal range in binary32: 2^-149 (~1.4e-45) up to 2^-126 (~1.18e-38, the smallest normal)
  [S26]. In dB relative to full scale that is -760 dB; nothing below -140 dB matters for a null test.
- Cost: "may take as many as 100 additional clock cycles, causing the fastest instructions to run as
  much as six times slower" on many x86 processors [S26]; a Mixxx benchmark cited in a search summary
  measured ~12x slower subnormal math with FTZ=1/DAZ=0 and normal speed with both set [S27].
- Semantics: FTZ makes operations "return zero instead of a subnormal float for operations that would
  result in a subnormal float"; DAZ makes hardware "treat subnormal input arguments to floating-point
  operations as zero" [S26]. On x86 both live in MXCSR; JUCE's `ScopedNoDenormals` ORs the mask
  `0x8040` (FTZ bit 15 | DAZ bit 6) via `_mm_getcsr`/`_mm_setcsr` and restores the saved register in
  the destructor [S28]. On AArch64 it is the FZ bit (1 << 24) of FPCR, read/written with
  `mrs %0, fpcr` / `msr fpcr, %0`; on 32-bit ARM `vmrs/vmsr fpscr`; MSVC ARM uses `_control87(_MCW_DN)`
  [S28]. "AArch32 NEON always uses a flush-to-zero mode"; for AArch64 SIMD and scalar it is optional
  via FZ [S26].
- The flags are per thread; set and restore them inside `process()` (a scoped guard), never globally:
  hosts such as Pro Tools misbehave when plug-ins leave the mode changed [S27]. In the convolver the
  tail of a long IR decays into subnormals in the time domain only after the IFFT; in the frequency
  domain accumulators subnormals arise when the input has been silent for longer than the IR (the FDL
  holds spectra of near-zero blocks). A scoped guard around the whole `process()` covers both.
- Determinism interaction: the builder thread (no FTZ) and the audio thread (FTZ) will round tiny
  values differently; if the offline bounce rebuilds synchronously on the audio thread inside the guard
  and the realtime path builds on a worker thread outside it, "static scene identical within -120 dB"
  still holds but "bit-identical across two runs" holds only if the same thread does the same work both
  runs **(derived)**.

### 7.2 NaN and Inf

- "Floating-point operations other than ordered comparisons normally propagate a quiet NaN" and NaN
  "compare as unordered, not as equal", so `x != x` tests for NaN [S29]. In an FFT every output bin
  depends on every input sample, so "one NaN in the input vector means that the output of fft will
  always be completely filled with NaNs" [S30]. In UPOLS this is worse than in direct convolution: the
  NaN spectrum sits in the FDL for Np blocks, so one NaN input sample poisons the output for the entire
  IR length (12 s for 1125 partitions) even after the input is clean, and a NaN inside an `IrSet`
  poisons the output until the next IR swap **(derived)**. `0 * Inf = NaN` means an Inf in either
  operand of the bin-wise multiply is also fatal. Pommier's `pffastconv.h` requires buffers to "contain
  valid small and non-NAN samples (ideally zero)" [S30]. A JUCE forum report describes a convolution
  plug-in with dead channels 5-10% of launches traced to NaNs in the FFT step [S30].
- Reviewer requirement: sanitise input blocks (replace non-finite with 0, cheap SIMD compare) or at least
  detect and reset the FDL; never let a NaN reach `IrSet::create` (assert finiteness of the RoomIR in
  the builder; denormal-flush does not remove NaNs).

### 7.3 Is a -120 dB residual achievable in float32?

- Machine epsilon: 2^-23 ~= 1.19e-7 (interval definition) or 2^-24 ~= 5.96e-8 (unit round-off) [S31];
  as amplitude ratios these are -138.5 dB and -144.5 dB **(derived)**; a Linux-audio post puts the
  rounding noise of a float multiply "around -144 dBFS" [S31].
- FFT roundoff: worst-case relative error of Cooley-Tukey is O(eps log n) (Gentleman & Sande 1966);
  rms error O(eps sqrt(log n)) (Schatzman 1996), vs O(eps n^{3/2}) / O(eps sqrt n) for the naive DFT
  [S32]. For n = 1024 the rms factor is sqrt(10) ~= 3.2 -> ~3.8e-7 ~= -128 dB per transform
  **(derived)**.
- The accumulation across partitions is the dominant term **(derived; simple stochastic model)**:
  sequentially summing Np independent equal-variance terms per bin in float32 gives an rms relative
  error of about eps * sqrt(Np / 6). Np = 94 (1 s): 4.7e-7 (-126 dB); Np = 282 (3 s): 8.2e-7
  (-122 dB); Np = 1125 (12 s): 1.6e-6 (-116 dB). Adding three transforms' errors in quadrature:
  ~-122 dB (1 s), ~-119.6 dB (3 s), ~-115 dB (12 s). These are for **white random IRs**, which is what
  the phase-06 test uses; real room IRs decay by 60 dB over RT60, so their effective Np is far smaller
  and the null is comfortably below -120 dB. Consequences for review:
  - The 144 000-sample random-IR case at -120 dB is marginal in float32 with sequential per-bin
    accumulation. Options: accumulate in double (`pffft_double` in the fork, or convert spectra), use
    pairwise/tree summation over partitions, give the random test IRs a decaying envelope, or document a
    -110 dB tolerance for L >= 48 000 with the derivation. Do not "fix" it by loosening to -100 dB
    silently; add a change-log row (CLAUDE.md rule).
  - The **reference** matters more: a direct convolution of 144 000 taps accumulated in float32 has rms
    relative error ~ eps * sqrt(N/6) = 1.19e-7 * 155 = 1.8e-5 ~= -95 dB, so a float32
    `sim::OfflineRender` can never null to -120 dB against anything. The reference must accumulate in
    double (or use a double FFT) and be converted to float only at the end.
  - -120 dB is a ratio of energies (10 log10) in the acceptance text, i.e. an amplitude ratio of 1e-6;
    reviewers should check the test computes `10*log10(sum(e^2)/sum(y^2))`, not `20*log10` of a peak
    ratio, and that the signal energy excludes the leading P zeros of latency.
- A rigorous bound for FFT convolution scales with log2(nN) * log2(n) * eps * ||.||_1 and "FFT-based
  convolution may be more sensitive to rounding errors, since we can only bound its absolute error"
  (arXiv 2405.01465) [S32]: small outputs next to large ones (the tail after a loud transient) carry the
  rounding of the large ones, which is another reason to specify the criterion as an energy ratio over
  the whole signal rather than per-sample.

---

## 8. Allocation-tracking tests in C++

- **Global operator new/delete replacement** is the portable C++-level approach: define the replaceable
  allocation functions once in the test binary; they take effect program-wide. Replace the whole family:
  `operator new(size_t)`, `new[]`, the `nothrow` variants, the sized `delete`s (C++14) and the aligned
  `std::align_val_t` overloads (C++17) **(unverified, from memory; cppreference returned 403 today)**.
  kunitoki's note in the JUCE thread: hooks "missed the aligned operator new overloads, which std::pmr
  uses for SIMD-aligned containers" [S33]. The replacement must itself be thread-safe and must not
  allocate (the WebKit bug: "calling Thread::current() can do a heap allocation and would cause an
  infinite loop") [S34].
- **Thread-local flag/counter**: a `static thread_local` POD (bool or int counter) armed at the start of
  the audio block, checked inside the replaced `operator new` [S33][S34]. Keep it trivially constructible
  and trivially destructible: a thread_local with a non-trivial constructor registers a destructor on
  first use and can allocate (JUCE's `ScopedThreadLocalBoolean` once did: "the initialisation of a
  ScopedThreadLocalBoolean caused an allocation, which the maintainers then fixed") [S34]. WebRTC's
  `AllocationCounter` is a reference implementation: "counts the number of heap allocations performed on
  the current thread within the scope", "must always be used from the same thread", and "isn't available
  under sanitizers, since the sanitizers override the allocators themselves" [S35]. So: the
  AllocationTracker test must be excluded (or expected to be a no-op) in the `asan`/`tsan` presets.
- **What operator-new replacement misses**: direct `malloc`/`calloc`/`realloc`/`posix_memalign` from C
  libraries and from the C++ runtime (exception objects, `std::thread` creation, `dlopen`), plus
  `mmap`. "overriding new doesn't catch all kinds of malloc calls" [S34]. PFFFT's transforms do not
  allocate [S11], but `pffft_new_setup` does; `std::function`, `std::string`, `std::vector::push_back`,
  `std::shared_ptr` control-block release and `std::map` all do.
- **Platform malloc hooks** (if the test must catch C allocations):
  - Linux/glibc: `__malloc_hook` was deprecated in 2.32 and removed in 2.34 (August 2021); the
    supported mechanism is interposition: define and export `malloc`, `free`, `realloc`, `calloc` (and
    the aligned variants) in the executable or an `LD_PRELOAD` library; glibc calls them through the PLT
    [S36]. Any interposer must handle `dlsym`'s own allocation (bootstrap with a static arena).
  - macOS: replace the function pointers of the default `malloc_zone_t` (zone introspection; ASan does
    this and notes the zone struct is mprotect'ed read-only on Lion and later) or set the global
    `malloc_logger` hook from libmalloc; neither is documented for per-thread use [S37]. Logic has
    injected its own malloc in some versions, which broke hook chains [S33].
  - Windows: `_CrtSetAllocHook` "installs a client-defined allocation function by hooking it into the
    C run-time debug memory allocation process (debug version only)"; hook signature
    `int YourAllocHook(int allocType, void *userData, size_t size, int blockType, long requestNumber,
    const unsigned char *filename, int lineNumber)`; "When _DEBUG isn't defined, calls to
    _CrtSetAllocHook are removed during preprocessing"; hooks must ignore `_CRT_BLOCK` blocks and need a
    recursion guard [S38]. Release builds get nothing; use IAT patching of `HeapAlloc`/`VirtualAlloc`
    (one developer's approach [S33]) or stick to operator-new replacement.
  - Hooks are process-wide, so in a plug-in host "multiple instances and multithreaded hosts" and
    "chained hooks from multiple plugins in one process caused hard-to-track crashes"; the JUCE thread's
    conclusion: do it in debug/CI test binaries only, "I wouldn't recommend integrating a feature like
    this on a framework level" [S33]. Phase 06's AllocationTracker lives in `tests/support`, which is the
    right place.
- **RealtimeSanitizer (RTSan)**: `clang -fsanitize=realtime`; mark the audio entry point
  `[[clang::nonblocking]]`; RTSan "intercepts system library calls such as malloc, free, and
  pthread_mutex_lock" and other non-deterministic calls, and reports `[[clang::blocking]]` functions
  called in a nonblocking context; `__rtsan::ScopedDisabler` suppresses inside a scope;
  `RTSAN_OPTIONS=halt_on_error=true` is the default [S39]. The docs show macOS and the Debian LLVM 21
  package carries it; Windows is not mentioned [S39]. It catches `malloc` from C code and the lock in
  `shared_ptr` release paths that operator-new replacement cannot. Shipped first in LLVM 20
  **(unverified, from memory)**. Worth a Linux CI job for `process()` once Catch2 can be compiled with
  clang in the `asan` preset style.
- **Why static initialisers and Catch2 itself must be excluded**: Catch2 registers every `TEST_CASE`
  during static initialisation through `AutoReg`, keeping `unique_ptr<TestCaseInfo>` and
  `unique_ptr<ITestInvoker>` per test; a 2019 commit measured 929 -> 614 allocations before `main` for
  `SelfTest --list-tests` [S40]. So the tracker must count only while armed (never assert in a global
  constructor), and the armed region must contain only the call under test: `REQUIRE`/`CHECK` build
  strings and `AssertionInfo` objects, `INFO` captures, section bookkeeping and reporters all allocate.
  Pattern: arm -> call `process()` -> disarm -> read the counter -> `REQUIRE(count == 0)`.
- **Making the test fail on allocation in process()**, concretely:
  1. Replace the global allocation family in `tests/support/AllocationTracker.cpp`; each override
     increments a `thread_local` counter when a `thread_local` armed flag is set, then forwards to
     `std::malloc`/`std::free` (aligned variants to `aligned_alloc`/`_aligned_malloc`).
  2. Provide an RAII `ScopedAllocationGuard` that arms/disarms and exposes `count()`.
  3. Run `process()` for every host block size (1, 37, 64, 512, 2048, random) across at least
     2 * ceil(maxIrLen/P) blocks so every FDL slot has been written, and across a `requestIr` pickup and
     a full crossfade and the end of the crossfade (state retirement is where `shared_ptr` resets hide).
  4. Also arm around `latencySamples()` and around the deferred-release drain **not** being called from
     process (the drain is allowed to free; process is not).
  5. Make the test a no-op with a visible SKIP under sanitizers [S35] and document that the `asan`
     preset relies on the Linux RTSan job (if added) or on the debug preset for this check.
  6. Guard against false negatives: a test that forgets to arm the flag passes trivially; add a
     self-test that allocates inside an armed region and expects `count() > 0`.

---

## 9. Reviewer's checklist

Each question names the bug it catches.

### Convolver (`Fft`, `PartitionedConvolver`, `IrSet`)

1. Is the FFT size exactly 2P and is each IR partition P samples followed by P zeros before its
   forward transform? (no padding -> aliasing in every output sample)
2. Does the input window hold [previous P | new P] and does the code keep the LAST P samples of the
   IFFT, consistent with the padding convention? (wrong half -> pre-echo/garbage, or a P-sample
   offset that the latency test will blame on something else)
3. Does FDL slot (w - j) mod Np pair with partition j, with the newest spectrum on partition 0, and does
   the ring index wrap exactly at Np? (time-reversed or scrambled IR)
4. Is Np = ceil(L/P), tested at L = P-1, P, P+1, and is the final partition zero-filled rather than
   read past the end of the IR? (dropped tail or out-of-bounds read)
5. Is the FDL sized at prepare() to the maximum partition count any IrSet may have, and shared by the
   A and B states? (tail missing after a swap to a longer IR; crossfade into an empty history)
6. Is 1/K applied exactly once (either the `scaling` argument of `pffft_zconvolve_accumulate` or once
   after the IFFT, not both)? (+/-6 dB gain error invisible to listening, visible to the null)
7. Are the input and all IR spectra produced by the same transform variant (`pffft_transform`,
   unordered) and consumed only by `pffft_zconvolve_accumulate`/`pffft_zreorder`? (bin mismatch -> noise;
   hand-written multiply mishandles the packed DC/Nyquist pair)
8. Are all PFFFT buffers from `pffft_aligned_malloc` or an equivalent 16/32/64-byte-aligned allocator,
   including the `work` buffer? (`std::vector<float>` -> crash under AVX or silent scalar fallback)
9. Is the accumulator cleared every block (or partition 0 written with a non-accumulating multiply)?
   (output grows/smears over time)
10. For host block n < P, which callback runs the UPOLS step, and is the worst single-callback time
    measured at n = 64? (AQ10 passes at 512 while 64-sample sessions glitch)
11. For n > P, does the loop produce floor(n/P) sub-blocks and carry the remainder? (output underrun or
    stale samples at large host buffers)
12. Is the reported latency exactly P + pre-roll for every n, with the output FIFO primed accordingly,
    and does the delta-IR test measure it at n = 1, 37 and 2048? (latency that depends on host block)
13. Is the -120 dB reference computed in double and the criterion an energy ratio over the aligned
    signals? (a float32 reference caps the null at ~-95 dB for 144 000 taps; a peak ratio hides tail
    errors)
14. Does the random-IR null at L = 144 000 pass with margin, or is the MAC accumulated in double /
    pairwise? (float32 sequential accumulation is ~-120 dB for white IRs of 282 partitions)
15. Is `pffft_new_setup` and every `IrSet::create` allocation confined to prepare()/the builder, with
    `pffft_destroy_setup` paired? (allocation in process; leak at sample-rate change)
16. Is the PFFFT commit pinned by hash in FetchContent and listed in `docs/THIRD_PARTY.md` with the
    FFTPACK v5 licence text? (unpinned master: the fork moved on Nov 3-4 2026; licence compliance)
17. Does the engine sanitise or detect non-finite input before the forward FFT, and does the builder
    assert the RoomIR is finite? (one NaN poisons output for the full IR length)

### Crossfade (`CrossfadingConvolver`)

18. Does the fade ramp index persist across host callbacks and advance per sample, starting at the
    internal P-block boundary where the mailbox was read? (per-callback restart or block-constant gain
    -> zipper/steps)
19. Is the ramp applied in the time domain to the valid output samples, after the overlap-save
    discard? (ramping accumulators = staircase; ramping before discard = garbage in the ramp)
20. Is g_B = 1 - g_A exactly (equal gain), and does the analytic test use the same linear g and the same
    n0 as the implementation? (equal-power would fail the null by ~3 dB mid-fade; mis-set n0 fails it
    everywhere)
21. During the fade are both states run against the same FDL with separate accumulators, and does the
    benchmark measure CPU during a fade? (tail dropout on every move; budget blown under automation)
22. When the fade ends, is state A retired by pushing its IrSet to the deferred-release queue (atomic
    pointer move), with no `shared_ptr` reset on the audio thread? (free() on the audio thread; TSan/ASan
    should see it if the test covers fade completion)
23. If a new IrSet arrives mid-fade, does it wait in the mailbox and does the superseded pending IrSet
    also go to the deferred-release queue? (leak of the displaced pointer; or a 3-way fade nobody tested)
24. Does `MAKROOF_TEST_HARD_SWITCH` replace only g with a unit step, keeping mailbox, pickup block and
    retirement identical? (a negative control that bypasses the real path proves nothing)
25. Is the 30 ms fade length derived from the sample rate at prepare() (1440 at 48 kHz, 2880 at 96 kHz)
    rather than a sample constant? (fade halves at 96 kHz)

### Scheduler and automation (phase 10)

26. Are both coalescing points single-slot latest-wins (parameter -> builder, builder -> audio) with no
    unbounded queue? (queue growth = staleness growth and allocation)
27. Is the 20 ms cadence a minimum spacing between build starts, with an over-long build followed
    immediately by one build on the newest scene, never a catch-up burst? (CPU burst, extra stale IRs)
28. Does the staleness metric define "live" (pickup vs end of fade) and does the CI log report the
    worst case per scenario? (a metric that cannot fail the 100 ms criterion)
29. In realtime-sim, do both the cadence and the pickup depend only on the simulated clock? (flaky CI,
    irreproducible scenarios)
30. In offline mode, is the rebuild synchronous on the rendering thread before the block is processed,
    with no worker threads at all? (bit-identical runs impossible)
31. Does the tail-cache key include sample rate, materials per band, scattering, air absorption (AX4),
    reflection order/crossover, tail length, seed, output mode/HRTF set and contract version, compared
    bit-exactly? (stale tail after a change that "should not matter")
32. Is energy matching recomputed from the new early part on every build, not cached with the tail?
    (level jumps or wrong early/late balance after moves)
33. Does a cache hit produce output equal to a full rebuild within -120 dB in a test that changes only
    positions AND a test that changes one cached-key field (which must miss)? (a test that only proves
    hits, never misses)
34. Are all random draws seeded from `tailSeed` and scene data, with no `std::random_device`,
    time-based seeds or thread-dependent RNG state? (non-deterministic bounces)
35. Are positions passed to the builder unsmoothed (phase 10 rule) while the output trim keeps its
    20 ms smoother, and is there no per-sample smoothing that would be applied twice? (double smoothing
    or smoothing lag added to staleness)
36. Is the FTZ/DAZ scoped guard set and restored inside process() on x86 (MXCSR 0x8040) and ARM
    (FPCR bit 24), per thread, with the previous state restored on every exit path? (host-wide mode
    change; ARM builds left with denormal stalls)
37. Does the AllocationTracker test arm only around `process()` (never around REQUIRE), replace the
    aligned/nothrow/sized overloads, run through a pickup and a full fade, and SKIP visibly under
    ASan/TSan? (a test that passes because it never counted anything)
38. Does the allocation test include a self-check that an allocating call inside the armed region is
    detected? (silent no-op tracker)
39. Are IR-affecting parameter changes (room size, mode) routed through the same builder path as
    positions, so they get the same coalescing and crossfade? (hard switch on room-size automation)
40. Is there a scenario with a 40 Hz tone and a low-band detector variant as phase 10's risk note asks,
    or is the blind spot recorded as a follow-up? (low-frequency thumps pass the click detector)

---

## Sources (all accessed 2026-11-04)

- [S1] Wefers, F. & Vorlaender, M., "Optimal filter partitions for real-time FIR filtering using
  uniformly-partitioned FFT-based convolution in the frequency-domain", DAFx-11, Paris 2011. PDF:
  https://www.dafx.de/paper-archive/2011/Papers/74_e.pdf (downloaded and text-extracted; quotes from
  sections 4-6 and Table 1).
- [S2] Brandtsegg, O. & Saue, S., "Live Convolution with Time-Variant Impulse Response", DAFx-17,
  Edinburgh 2017. https://www.dafx17.eca.ed.ac.uk/papers/DAFx17_paper_9.pdf (downloaded and
  text-extracted; sections 5-6).
- [S3] Wikipedia, "Overlap-save method". https://en.wikipedia.org/wiki/Overlap%E2%80%93save_method
- [S4] UHSDR wiki, "Low latency filtering: Partitioned Convolution".
  https://github.com/df8oe/UHSDR/wiki/Low-latency-filtering:-Partitioned-Convolution
- [S5] Self-reported project measurements found by web search: Drenched PR #42
  https://github.com/simon-lowes/Drenched/pull/42 ; Filmcraft issue #3134
  https://github.com/storytold/filmcraft/issues/3134 ; JUCE `dsp::Convolution` docs
  https://docs.juce.com/master/classdsp_1_1Convolution.html (search-result summaries; not peer reviewed).
- [S6] Garcia, G., "Optimal Filter Partition for Efficient Convolution with Short Input/Output Delay",
  AES 113th Convention, Oct 2002. Abstract: https://www.aes.org/e-lib/browse.cfm?elib=11275 (paywalled
  full text).
- [S7] Pommier, J., `pffft.h` (original). https://bitbucket.org/jpommier/pffft/raw/master/pffft.h
  (header comments quoted verbatim).
- [S8] FFTW 3 manual, "The 1d Real-data DFT".
  https://www.fftw.org/fftw3_doc/The-1d-Real_002ddata-DFT.html
- [S9] Wefers, F., "Partitioned convolution algorithms for real-time auralization", Diss. RWTH Aachen
  2014, Logos Verlag 2015, DOI 10.18154/RWTH-2015-02185. PDF:
  https://publications.rwth-aachen.de/record/466561/files/466561.pdf (record page read; PDF download
  blocked by a JavaScript challenge today, so thesis-internal statements are marked from memory).
- [S10] Gardner, W. G., "Efficient Convolution without Input-Output Delay", JAES 43(3):127-136, 1995;
  AES preprint 3897 (1994). https://www.aes.org/e-lib/browse.cfm?elib=7957 and
  https://www.aes.org/e-lib/browse.cfm?elib=6335 (abstracts); patent remark from
  https://lists.linuxaudio.org/archives/linux-audio-dev/2005-April/011732.html and
  https://lists.apple.com/archives/coreaudio-api/2012/Feb/msg00040.html (secondhand).
- [S11] marton78/pffft README. https://github.com/marton78/pffft (rendered page) and
  https://cdn.jsdelivr.net/gh/marton78/pffft@master/README.md (raw, 607 lines); file listing via
  https://data.jsdelivr.com/v1/package/gh/marton78/pffft@master/flat (shows /pffft.h, /pffft_double.h,
  /LICENSE.txt).
- [S12] marton78/pffft commit log. https://github.com/marton78/pffft/commits/master
- [S13] KissFFT README. https://github.com/mborgerding/kissfft/blob/master/README.md
- [S14] Fink, M., Holters, M. & Zoelzer, U., "Signal-matched power-complementary cross-fading and dry-wet
  mixing", DAFx-16, Brno 2016.
  https://www.hsu-hh.de/ant/wp-content/uploads/sites/699/2017/10/Fink-Holters-Zölzer-2016-Signal-matched-power-complementary-cross-fading-and-dry-wet-mixing.pdf
  (downloaded and text-extracted; section 1-2 quotes and eqs. 7-11).
- [S15] Wefers, F. & Vorlaender, M., "Efficient time-varying FIR filtering using crossfading implemented
  in the DFT domain", Forum Acusticum 2014, Krakow. ResearchGate listing
  https://www.researchgate.net/publication/280979516_Efficient_time-varying_FIR_filtering_using_crossfading_implemented_in_the_DFT_domain
  (abstract via search summary; PDF returned 403).
- [S16] Smith, J. O. et al., "Doppler Simulation and the Leslie", DAFx-02 (slides PDF).
  https://ccrma.stanford.edu/~jos/doppler/dafx02p.pdf (downloaded; text extracted for the quoted
  bullets).
- [S17] Carpentier, T., SMC 2024 paper id 118 (search-result summary; host smcnetwork.org not
  reachable from this session). https://smcnetwork.org/smc2024/papers/SMC2024_paper_id118.pdf
- [S18] Search-result summaries: "Perceptual Evaluation of Variable-Orientation Binaural Room Impulse
  Response Rendering" https://www.researchgate.net/publication/332727832 ; "Effect of Interpolation
  Artifacts on Perceived Stability of Nearby Sources in a Navigable Reverberant Virtual Environment"
  https://www.researchgate.net/publication/385000704 ; "Interpolation of scheduled simulation results
  for real-time auralization of moving sources", Acta Acustica 2024,
  https://acta-acustica.edpsciences.org/articles/aacus/full_html/2024/01/aacus230100/aacus230100.html
  (full text returned 403; quotes are from the search summary).
- [S19] Smith, J. O., "Windowed Sinc Interpolation".
  https://ccrma.stanford.edu/~jos/Interpolation/Windowed_Sinc_Interpolation.html
- [S20] Laakso, Vaelimaeki, Karjalainen & Laine, "Splitting the Unit Delay", IEEE Signal Processing
  Magazine 13(1):30-60, Jan 1996, DOI 10.1109/79.482137 (abstract and fragments via search summary of
  https://typeset.io/pdf/principles-of-fractional-delay-filters-zv6y0rtzj4.pdf ; full PDF not
  retrieved).
- [S21] Smith, J. O., "Kaiser Window design formulas (kaiserord)".
  https://ccrma.stanford.edu/~jos/sasp/Hood_kaiserord.html
- [S22] MathWorks, `kaiser`. https://www.mathworks.com/help/signal/ref/kaiser.html
- [S23] Smith, J. O., "Spectrum of Kaiser-windowed Sinc".
  https://ccrma.stanford.edu/~jos/Interpolation/Spectrum_Kaiser_windowed_Sinc.html
- [S24] Smith, J. O., "Lagrange Interpolation".
  https://ccrma.stanford.edu/~jos/pasp/Lagrange_Interpolation.html
- [S25] Smith, J. O., "Thiran Allpass Interpolators".
  https://ccrma.stanford.edu/~jos/pasp/Thiran_Allpass_Interpolators.html
- [S26] Wikipedia, "Subnormal number". https://en.wikipedia.org/wiki/Subnormal_number
- [S27] JUCE forum, "Resolving denormal floats once and for all"
  https://forum.juce.com/t/resolving-denormal-floats-once-and-for-all/8241 and Mixxx bug 1404401
  https://bugs.launchpad.net/bugs/1404401 (search summaries).
- [S28] JUCE, `juce_FloatVectorOperations.cpp` (ScopedNoDenormals, get/setFpStatusRegister).
  https://raw.githubusercontent.com/juce-framework/JUCE/master/modules/juce_audio_basics/buffers/juce_FloatVectorOperations.cpp
- [S29] Wikipedia, "NaN". https://en.wikipedia.org/wiki/NaN
- [S30] MathWorks blog (Steve Eddins) on NaN in fft https://blogs.mathworks.com/steve/ (post 1134);
  JUCE forum "Nan error in Convolution" https://forum.juce.com/t/nan-error-in-convolution/29057 ;
  `pffastconv.h` comment (mirror)
  https://os.unplugged.com/werunplugged/unplugged-system/src/branch/main/external/pffft/pffastconv.h
  (search summaries).
- [S31] Wikipedia, "Machine epsilon" https://en.wikipedia.org/wiki/Machine_epsilon ; linux-audio-user
  thread on float rounding noise
  https://lists.linuxaudio.org/hyperkitty/list/linux-audio-user@lists.linuxaudio.org/message/GOE2PLCJXC32J6AFN74O2WW2FLBCCOLS
- [S32] Wikipedia, "Fast Fourier transform", Accuracy section
  https://en.wikipedia.org/wiki/Fast_Fourier_transform ; arXiv 2405.01465 (FFT-convolution error bound,
  search summary) https://arxiv.org/pdf/2405.01465
- [S33] JUCE forum, "FR: Option for assert on audio thread allocation or syscall".
  https://forum.juce.com/t/fr-option-for-assert-on-audio-thread-allocation-or-syscall/58151
- [S34] JUCE forum, "Are thread AllocationHooks intended for JUCE internal use only?"
  https://forum.juce.com/t/are-thread-allocationhooks-intended-for-juce-internal-use-only/44432 ;
  "Possible allocation in VST3 processCallback"
  https://forum.juce.com/t/possible-allocation-in-vst3-processcallback/46976 ; WebKit bug 223226
  https://bugs.webkit.org/show_bug.cgi?id=223226 (search summaries).
- [S35] WebRTC `common_audio/allocation_counter.h`.
  https://webrtc.googlesource.com/src/+/main/common_audio/allocation_counter.h
- [S36] Red Hat Developer, "Why malloc hooks were removed from glibc" (2021-08-25).
  https://developers.redhat.com/articles/2021/08/25/securing-malloc-glibc-why-malloc-hooks-had-go ;
  man page https://man7.org/linux/man-pages/man3/malloc_hook.3.html
- [S37] Apple libmalloc source (malloc_logger) https://opensource.apple.com/source/libmalloc/libmalloc-283/src/malloc.c.auto.html ;
  `malloc_default_zone(3)`; ASan `asan_malloc_mac.cc`
  https://android.googlesource.com/toolchain/gcc/+/master/gcc-4.9/libsanitizer/asan/asan_malloc_mac.cc
  (search summaries).
- [S38] Microsoft Learn, `_CrtSetAllocHook`.
  https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/crtsetallochook?view=msvc-170 ;
  "CRT debugging techniques"
  https://learn.microsoft.com/en-us/cpp/c-runtime-library/crt-debugging-techniques?view=msvc-170
- [S39] Clang docs, "RealtimeSanitizer". https://clang.llvm.org/docs/RealtimeSanitizer.html ; Debian
  llvm-toolchain-21 copy
  https://sources.debian.org/src/llvm-toolchain-21/1%3A21.1.6-3/clang/docs/RealtimeSanitizer.rst
- [S40] Catch2 history (mirror): `catch_test_case_registry_impl.h`, `catch_test_registry.cpp`, commit
  "Do not copy around TestCaseInfo" and follow-up massif counts.
  https://gitea.hak8or.com/mirrors/Catch2/src/commit/302e2c0b06f131199b97ad33bdebacc359782ff0/include/internal/catch_test_case_registry_impl.h
  (search summaries).

Not reachable today (noted so the next researcher does not retry blindly): Wefers thesis PDF (JS
challenge at RWTH), marton78 `pffft.h` raw (404 via raw.githubusercontent and jsdelivr through this
proxy; GitHub API not enabled for the repo in this session), Wefers & Vorlaender 2014 PDF (403),
Savioja 1999 JAES PDF on core.ac.uk (403), Acta Acustica 2024 full text (403), smcnetwork.org
(DNS not allowed), cppreference (403).
