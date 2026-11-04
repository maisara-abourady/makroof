# Real-time audio C++ and JUCE plugin engineering (K3)

Reference file of the `review-phase-pr` skill. Scope: audio-thread rules and hidden allocators, lock-free handover and memory reclamation, denormals, floating-point determinism, JUCE 8 AudioProcessor lifecycle and API facts (latency, non-realtime, bypass, parameters and versioned IDs, state ordering quirks), pluginval and auval, VST3 identity and bus layouts, JUCE release status. Phases 00, 06, 07, 10, 11, 13.

How to use it: read the "Reviewer's checklist" section first and apply the questions the diff makes
relevant; use the earlier sections to settle a disagreement with the author or to re-derive a number.
Every fact carries its source URL and the date it was verified (researched live on 2026-11-04).
Facts marked "(unverified, from memory)" must be verified before they are cited in a review; when
you verify one, fix it here. See `knowledge-inventory.md` for which facts go stale and how to
re-check them.

## Contents

- 1. Audio-thread rules: what is forbidden in `processBlock` and why
  - 1.1 The canonical statements
  - 1.2 Hidden allocators and blockers to flag in a diff (what each one does)
- 2. Lock-free handover patterns
  - 2.1 Memory-order vocabulary (the standard's words)
  - 2.2 Single-slot atomic pointer mailbox ("latest wins")
  - 2.3 Deferred release / garbage queue
  - 2.4 SPSC FIFOs and `juce::AbstractFifo`
  - 2.5 ABA and CAS loops
  - 2.6 Spinlocks
- 3. Denormals (subnormals)
  - 3.1 x86: MXCSR FTZ and DAZ
  - 3.2 ARM64: FPCR.FZ, and why "NEON ignores FZ" is an AArch32 fact
  - 3.3 Why convolution/reverb tails are prone to denormals
- 4. Floating-point determinism
  - 4.1 FMA contraction defaults
  - 4.2 `-ffast-math` and `/fp:fast` dangers
  - 4.3 SIMD vs scalar reductions, libm, and why cross-platform bit-identity is unrealistic
  - 4.4 Random numbers
- 5. JUCE 8/9 `AudioProcessor` lifecycle and API facts
  - 5.1 `prepareToPlay` / `releaseResources` / `processBlock`
  - 5.2 Latency
  - 5.3 Non-realtime (offline) mode
  - 5.4 Bypass and tail
  - 5.5 Parameters: `ParameterID`, version hints, IDs, ranges, gestures
  - 5.6 State
  - 5.7 Threads and UI
- 6. pluginval
  - 6.1 Versions (verified 2026-11-04 from tags fetched into the clone and the GitHub releases pages)
  - 6.2 Strictness-level semantics (test → minimum level), from the sources
  - 6.3 Flags
  - 6.4 Reading the log
- 7. auval basics
- 8. VST3 specifics
- 9. JUCE versions and breaking changes (verified from tags fetched 2026-11-04)
- 10. Reviewer's checklist for diffs touching `src/plugin` or the real-time engine
- Appendix: source list with access dates (all 2026-11-04)

---

Compiled 2026-11-04 for the makroof code-review skill (C++20, JUCE, VST3/AU, `src/sim` + `src/plugin`).
Every fact carries its source and the access date. "(verified: source)" means the text was read on
2026-11-04 from that URL or from a fresh clone; "(unverified, from memory)" means it could not be
checked live today. Secondary sources (forum posts) are labelled as such.

Repo context checked today: `cmake/SpatialDependencies.cmake` pins `SPATIAL_JUCE_TAG "8.0.17-security"`;
`tools/ci/run_pluginval.sh` pins pluginval `v1.0.4`; `src/plugin/PluginProcessor.cpp` already uses
`juce::ScopedNoDenormals`; Phase 06 requires a JUCE-free FTZ/DAZ guard in `src/sim`.

---

## 1. Audio-thread rules: what is forbidden in `processBlock` and why

### 1.1 The canonical statements

- Bencina, "Real-time audio programming 101: time waits for nothing" (2011; "Lightly updated for
  clarity 13 August, 2011"). Cardinal rule: **"If you don't know how long it will take, don't do it."**
  The explicit list for the callback: "Don't allocate or deallocate memory", "Don't lock a mutex",
  "Don't read or write to the filesystem or otherwise perform i/o.", "Don't call OS functions that
  may block waiting for something", "Don't call *any* code that does or may do any of the above".
  Reason given for locks: a lower-priority thread holding the lock delays the high-priority audio
  callback, "This is called priority inversion." Recommended instead: "Do pre-allocate or
  pre-compute data in a non-time-critical thread", "use lock-free FIFO queues to communicate commands
  and data between real-time and non-real-time contexts", "atomic data access (requires great care)".
  (verified via reader mirror https://hn.jakechampion.name/reader/http://www.rossbencina.com/code/real-time-audio-programming-101-time-waits-for-nothing
  on 2026-11-04; the origin http://www.rossbencina.com/code/real-time-audio-programming-101-time-waits-for-nothing
  returned HTTP 503 twice on 2026-11-04.)
- Doumler, "Real-time programming with the C++ standard library", CppCon, 29 Oct 2021, slides
  (verified: PDF https://cppcon.digital-medium.co.uk/wp-content/uploads/2021/09/talk.pdf,
  text-extracted 2026-11-04). Definition of real-time-safe code: "The worst-case execution time is
  deterministic, known in advance, independent of application data, shorter than the given deadline.
  The code does not fail." Slide 16 rules, verbatim:
  - "don't call anything that might block (non-deterministic execution time + priority inversion!)"
  - "don't try to acquire a mutex"
  - "don't allocate / deallocate memory"
  - "don't do any I/O"
  - "don't interact with the thread scheduler"
  - "don't do any other system calls"
  - "don't call any 3rdparty code if you don't know what it's doing"
  - "don't use algorithms with > O(1) complexity"
  - "don't use algorithms with amortised O(1) complexity"  (this is the rule that bans `push_back`)
- Same talk: "Exceptions are not 'real-time safe'." Entering and leaving a `try` block without
  throwing *is* safe on zero-cost ABIs (Itanium gcc/clang, MSVC 64-bit, ARM); MSVC 32-bit generates
  unwind info at runtime. Throwing is never safe (allocates the exception object, unwinds with
  unbounded cost).
- Same talk, containers and utilities: `std::array` is safe "(except at() which can throw)"; "all
  others use dynamic memory → not realtime-safe"; `std::pair/tuple/optional/variant` are safe
  ("but boost::variant is not!"); "Everything using type erasure is not real-time safe: std::any,
  std::function"; lambdas themselves are fine (stack objects). Not safe among algorithms:
  `std::stable_sort`, `std::stable_partition`, `std::inplace_merge`, `std::execution::parallel_*`
  (they allocate temporary buffers). General-purpose allocators (tcmalloc, rpmalloc) are not
  real-time safe: "minimising average cost, not worst case", "multithreaded (locks)", "eventually go
  to OS". A safe allocator is "constant time, single-threaded, only use memory allocated upfront"
  (e.g. `std::pmr::monotonic_buffer_resource` over a `std::array` with `null_memory_resource()` as
  upstream, so exhaustion throws instead of calling malloc).
- Same talk on randomness: "The std::uniform_*_distributions have amortised O(1) complexity. They
  can discard the generated random number and generate another one." → not real-time safe. Use the
  engine's raw output and scale it. `std::rand()` is not safe either (global state, may lock).
- Same talk on synchronisation: "C++ has exactly one 'real-time safe' thread synchronisation
  mechanism: std::atomic", "'atomic' doesn't mean lock-free, it means 'no data race'",
  `static_assert(std::atomic<T>::is_always_lock_free);` "if this fails, your compiler will add locks".
- Talk abstract (verified: https://cppcon2021.sched.com/event/nvCy/real-time-programming-with-the-c-standard-library,
  2026-11-04): a program "has to not only produce the correct result, but to do so reliably in a
  deterministic amount of time."
- JUCE's own `processBlock` doc: it is called on "the audio thread, so any kind of interaction with
  the UI is absolutely [forbidden]"; send an async message (`ChangeBroadcaster`/`AsyncUpdater`) instead.
  "The number of samples in these buffers is NOT guaranteed to be the same for every callback",
  some hosts pass blocks of "zero samples, so make sure that your algorithm can deal with that!"
  (verified: `modules/juce_audio_processors_headless/processors/juce_AudioProcessor.h` lines 175-221
  in JUCE master d60b7a7 = 9.0.5, cloned 2026-11-04; same text in the docs.juce.com page).

### 1.2 Hidden allocators and blockers to flag in a diff (what each one does)

| Construct | Why it is not real-time safe | Source / status |
|---|---|---|
| `std::vector::push_back/emplace_back/resize/insert`, `reserve` inside process | amortised O(1) growth = occasional realloc + copy | Doumler slide 16 (verified) |
| `std::string`, `juce::String` construction/concatenation, `String::formatted`, `std::to_string`, `std::format`, `snprintf` into a `String` | heap allocation (SSO may hide it for short strings only); `juce::String` is heap + ref-counted | Doumler containers slide (verified); juce::String internals (unverified, from memory) |
| `std::map/set/unordered_*`, `std::list`, `std::deque` | node allocation on insert; `operator[]` on a map inserts | Doumler containers slide (verified) |
| lambda with captures assigned to `std::function` | type erasure may heap-allocate the callable; calling is an indirect call through an erased target | Doumler "type erasure" slide (verified) |
| `std::any`, `boost::variant` | type erasure / heap | Doumler (verified) |
| `std::shared_ptr` copy on the audio thread | atomic refcount RMW (usually lock-free) **but** if the audio thread drops the last reference the deleter runs there → free() on the audio thread | JUCE forum, dave96 (secondary, verified 2026-11-04: https://forum.juce.com/t/timur-doumler-talks-on-c-audio-sharing-data-across-threads/26311) |
| `std::atomic_load(shared_ptr*)`, `std::atomic<std::shared_ptr>` | "existing implementations are typically not lock-free" (locks/spinlocks inside) | Doumler ACCU 2022 abstract (verified: https://accu.org/conf-previous/2022/sessions/a-lock-free-atomic-shared_ptr/session/index.html) |
| `DBG(...)`, `juce::Logger::writeToLog`, `std::cout`, `printf` | string building + I/O + possibly locks; `DBG` compiles out in release but still a code smell in process code | Bencina "don't perform i/o" (verified); JUCE Logger internals (unverified, from memory) |
| `juce::AudioBuffer::setSize(...)` | allocates unless the existing allocation is large enough and `avoidReallocating` is true | JUCE API (unverified, from memory; check the signature in the pinned JUCE) |
| `juce::MemoryBlock`, `juce::Array::add` (growth), `juce::OwnedArray`, `juce::ValueTree` ops, `juce::var` with strings/objects | heap; `ValueTree` is also not thread-safe | JUCE (unverified, from memory) |
| `APVTS::copyState()/replaceState()` | "This method uses locks to synchronise thread access, so whilst it is thread-safe, it is not realtime-safe." | verified: https://docs.juce.com/master/classAudioProcessorValueTreeState.html |
| `std::mutex::lock`, `juce::CriticalSection`, `ScopedLock`, `MessageManagerLock` | blocking + priority inversion | Bencina, Doumler (verified) |
| `std::this_thread::sleep_for`, `yield`, `Thread::wait/notify`, `WaitableEvent::wait` | interacts with the scheduler | Doumler slide 16 (verified) |
| `std::stable_sort`, `std::stable_partition`, `std::inplace_merge`, parallel algorithms | allocate temporaries | Doumler (verified) |
| `std::uniform_real_distribution` and friends, `std::rand` | rejection sampling (amortised O(1)); global state | Doumler (verified) |
| `throw`, `new`/`delete`, `std::make_unique/make_shared`, `dynamic_cast` on huge hierarchies | exception object allocation; heap; RTTI walk is bounded but non-trivial | Doumler (verified for throw/alloc); dynamic_cast is a judgement call |
| file/network/`std::filesystem`, `juce::File`, `URL` | I/O | Bencina (verified) |
| unbounded loops (`while (!flag)` spin waiting on another thread, retry loops on CAS without bound) | execution time depends on another thread's progress | Doumler "don't call anything that might block" (verified) |
| data-dependent work (e.g. "rebuild IR if dirty" inside process in realtime mode) | breaks "independent of application data" | Doumler definition (verified) |

Tools that catch these automatically:
- **RealtimeSanitizer (RTSan)**: `clang++ -fsanitize=realtime`, mark the callback
  `[[clang::nonblocking]]`; at run time it reports `malloc`, `free`, `pthread_mutex_lock` and other
  non-deterministic calls reached from that function; `[[clang::blocking]]` marks your own blocking
  functions; `__rtsan::ScopedDisabler` (from `<sanitizer/rtsan_interface.h>`) silences a scope;
  `RTSAN_OPTIONS=halt_on_error=...,suppressions=...,print_stats_on_exit=...`. Requires LLVM/Clang 20+
  (verified: https://clang.llvm.org/docs/RealtimeSanitizer.html and https://github.com/realtime-sanitizer/rtsan, 2026-11-04).
- **pluginval** level 9 "Allocations during process" test and the 2.0 `--rtcheck` option (see §6).
- The project's own `tests/support/AllocationTracker` (Phase 06).

---

## 2. Lock-free handover patterns

### 2.1 Memory-order vocabulary (the standard's words)

- `memory_order::relaxed`: "no operation orders memory." `release`: "a store operation performs a
  release operation on the affected memory location" (also `acq_rel`, `seq_cst`). `acquire`: "a load
  operation performs an acquire operation" (also `acq_rel`, `seq_cst`). "An atomic operation A that
  performs a release operation on an atomic object M synchronizes with" an acquire operation B on M
  that reads a value from A's release sequence. (verified: https://eel.is/c++draft/atomics.order, 2026-11-04)
- Practical rule for a pointer handover: the producer finishes building the object, then publishes
  the pointer with `release` (or `seq_cst`); the consumer loads/exchanges with `acquire`. A `relaxed`
  publish of a freshly built object is a real bug on ARM (weak ordering): the audio thread can see
  the pointer before the object's contents. x86 hides it (TSO) so CI on x86 will not catch it; TSan may.

### 2.2 Single-slot atomic pointer mailbox ("latest wins")

- Shape: `std::atomic<IrSet*> pending{nullptr}`. Producer: `old = pending.exchange(newPtr, acq_rel)`;
  if `old != nullptr` the producer owns and disposes it (it was never picked up). Consumer (audio):
  `p = pending.exchange(nullptr, acq_rel)`; if non-null, it becomes the new current state and the
  *previous* current must be handed to a release queue, never deleted on the audio thread.
- Properties: wait-free for both sides (one RMW each), no ABA problem (no CAS loop, no reuse
  assumption), no lost update (exchange returns what was displaced). This is the Phase 06 design.
- Bugs reviewers see in this pattern:
  - `load()` then `store(nullptr)` instead of a single `exchange` (TOCTOU: producer stores in between → leak or double-consume).
  - Using `std::atomic<std::shared_ptr<T>>` or `std::atomic_load(&sp)` here: typically implemented
    with a lock (Doumler ACCU 2022 abstract, verified; JUCE forum: "upon looking at how
    std::atomic_load(shared_ptr) works, we see there are locks" (matkatmusic, secondary)). The
    standard only says `is_always_lock_free` is implementation-defined for it
    (verified: https://eel.is/c++draft/util.smartptr.atomic.shared).
  - `std::atomic<T*>` is lock-free on every mainstream desktop ABI, but still `static_assert
    (std::atomic<T*>::is_always_lock_free)` so a future type change cannot silently add a lock
    (Doumler slide, verified).
  - Letting the audio thread drop the last `shared_ptr` (destructor → `delete` → free on the audio
    thread). JUCE forum fix: "dispatch the delete to the message thread via some kind of garbage
    collection" (dave96, secondary, verified).
  - Raw `unique_ptr::release()` into the mailbox with a code path that can return early before the
    exchange → leak under ASan only if the test exercises that path.
  - Reading the mailbox more than once per block (e.g. in a helper and again in the caller).
  - Non-atomic `bool dirty` flags or `volatile` as a substitute for atomics (data race = UB).

### 2.3 Deferred release / garbage queue

- The audio thread never frees. It pushes the displaced pointer into an SPSC FIFO (bounded, pre-sized);
  a non-audio thread drains and deletes. If the FIFO is full the audio thread must not block: either
  size the queue for the worst case (bounded by the producer's maximum submit rate × crossfade
  length) or keep the object alive in a fallback slot and retry next block. Review question: what
  happens when the garbage FIFO is full?
- Alternative: producer keeps ownership and the audio thread only "borrows" the pointer plus an
  acknowledge counter (epoch); producer frees only after the audio thread's published epoch passes.
  Simpler to get wrong; the FIFO is preferred for the convolver.
- Micah Johnston's Basedrop (Rust) describes the same idea: handing a node to a queue in "an
  allocation-free, wait-free operation" (secondary, verified via search result 2026-11-04,
  https://glowcoil.com/posts/basedrop).

### 2.4 SPSC FIFOs and `juce::AbstractFifo`

- `juce::AbstractFifo` "doesn't actually hold any data itself"; it manages read/write positions for a
  buffer you own; "handles the logic needed when building a single-reader, single-writer FIFO"; "The
  maximum number of items managed by the FIFO is 1 less than the buffer size." `prepareToWrite`
  returns up to two index ranges (wrap-around), "you must call finishedWrite() to tell the FIFO how
  much data you actually added"; `write()/read()` return `ScopedWrite/ScopedRead` that finish on
  scope exit. (verified: https://docs.juce.com/master/classAbstractFifo.html, 2026-11-04)
- Reviewer checks for any SPSC queue: exactly one producer thread and one consumer thread (the IR
  builder thread *and* a `setStateInformation` path both pushing = two producers = corruption);
  capacity is a power of two or masked correctly; the "full" case is handled without blocking; the
  stored element type is trivially copyable or the handover is of pointers only; the index loads use
  acquire and the stores use release (JUCE's class does this for you).

### 2.5 ABA and CAS loops

- ABA only arises with compare-exchange on reusable addresses (lock-free stacks/queues with node
  recycling). A single-slot exchange mailbox and an index-based SPSC ring are ABA-free by
  construction. If a diff introduces a CAS loop on a pointer with recycled nodes, require a tagged
  pointer/epoch or reject. (Reasoning from the standard's semantics above; general literature,
  unverified live.)
- Any CAS retry loop on the audio thread is an unbounded loop if the other side can win
  repeatedly; prefer exchange or a bounded retry with a fallback.

### 2.6 Spinlocks

- Doumler, ADC'20 "Using locks in real-time audio processing, safely": a spinlock with `try_lock` on
  the audio thread (never spin-wait unboundedly; the non-audio side spins/yields, the audio side
  tries once and skips) is acceptable where data is tiny; referenced from the 2021 slides (verified
  slide text "spinlocks → efficient implementation: see my talk at ADC'20"). Content of the ADC'20
  talk itself: unverified today.

---

## 3. Denormals (subnormals)

### 3.1 x86: MXCSR FTZ and DAZ

- Intel: "the flush-to-zero (FTZ) and denormals-are-zero (DAZ) flags in the MXCSR register are used
  to control floating-point calculations." FTZ: results that would be denormal are set to zero.
  "FTZ only applies to Intel® SSE and Intel® AVX instructions. If the application generates denormals
  using x86 instructions, FTZ does not apply" (i.e. x87 is unaffected). DAZ: denormal inputs are
  treated as zero. Macros: `_MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON)` (xmmintrin.h),
  `_MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON)` (pmmintrin.h). "DAZ and FTZ flags are not
  compatible with the ISO/IEC/IEEE 60559 standard". (verified: Intel oneAPI compiler guide
  https://www.intel.com/content/www/us/en/docs/dpcpp-cpp-compiler/developer-guide-reference/2025-0/set-the-ftz-and-daz-flags.html, 2026-11-04)
- Bit positions: FTZ = MXCSR bit 15, DAZ = MXCSR bit 6; both reset to 0 (disabled) at power-up;
  DAZ support must be checked via the FXSAVE `MXCSR_MASK` field (writing bit 6 on a CPU without DAZ
  can raise #GP; only very early Pentium 4 steppings lack it). (verified from an SDM Vol. 1 mirror
  §11.6.3-11.6.4 https://xem.github.io/minix86/manual/intel-x86-and-64-manual-vol1/o_7281d5ea06a5b67a-274.html
  and secondary sources listing bit 15/bit 6, 2026-11-04.)
- JUCE's implementation (verified: `modules/juce_audio_basics/buffers/juce_FloatVectorOperations.cpp`
  lines 1511-1563, JUCE master 2026-11-04): on SSE builds the mask is `0x8040` = (1<<15)|(1<<6) =
  FTZ|DAZ; `ScopedNoDenormals` saves `getFpStatusRegister()`, ORs the mask in, restores the saved
  value in the destructor; both `noexcept`. It is a **per-thread** register, so the guard must be
  created inside the callback on the audio thread (as `PluginProcessor.cpp` does), not once in
  `prepareToPlay`. On platforms without SSE/NEON/AArch64 it does nothing.

### 3.2 ARM64: FPCR.FZ, and why "NEON ignores FZ" is an AArch32 fact

- FPCR fields (verified: Arm System Register mirror https://df.lth.se/~getz/ARM/SysReg/AArch64-fpcr.html,
  2026-11-04): `FZ` = bit 24, "Flushing denormalized numbers to zero control bit"; `FZ16` = bit 19
  (FEAT_FP16) "applies to both scalar and Advanced SIMD floating-point half-precision calculations";
  `AH` = bit 1 (FEAT_AFP) "Controls alternate handling of floating-point numbers"; `FIZ` = bit 0
  (FEAT_AFP) "Flush Inputs to Zero": "Denormalized single-precision and double-precision inputs to
  most floating-point instructions flushed to zero". With `AH == 1`, `FZ` flushes **outputs only**;
  with `AH == 0` (the default on every shipping core today) `FZ` behaves like FTZ+DAZ combined.
- AArch64 Advanced SIMD honours FPCR.FZ exactly like scalar FP. An Arm engineer on the Arm forum:
  in A64 (unlike A32) "the Advanced-SIMD/Neon can support both FtZ and full denormal operation,
  controlled by the same bit that determines the regular FP operation mode"; the AArch32 rule was
  "NEON always uses flush-to-zero mode" (secondary, verified via search 2026-11-04:
  https://community.arm.com/support-forums/f/architectures-and-processors-forum/6470/i-m-not-seeing-any-flush-to-zero-ftz-effects-with-neon-intrinsics-on-an-arm-a9-any-advice/25704).
  FreeBSD had to stop setting FZ at process start because an AArch64 SIMD `strlen` broke when
  denormals became indistinguishable from zero (secondary, https://reviews.freebsd.org/D48442).
  Consequence for review: on Apple Silicon and Linux arm64 the convolver *will* hit denormals in
  decaying tails unless FZ is set; the 2017 JUCE-forum claim "on arm, NEON registers never use
  denormals" (fr810, https://forum.juce.com/t/scopednodenormals-issue/24425) is AArch32-era and
  must not be used to skip the ARM64 guard.
- JUCE on ARM sets only `(1 << 24)` (FZ) via `msr fpcr` (AArch64) / `vmsr fpscr` (32-bit NEON)
  (verified: same cpp file lines 1546-1554).
- A JUCE-free equivalent for `src/sim` (Phase 06 item 5): x86 `_mm_getcsr()/_mm_setcsr(csr | 0x8040)`;
  AArch64 `__asm__ volatile("mrs %0, fpcr" : "=r"(v)); v |= (1u << 24); __asm__ volatile("msr fpcr, %0" :: "r"(v));`
  (MSVC arm64: `_ReadStatusReg(ARM64_FPCR)` / `_WriteStatusReg` — unverified, from memory). Always
  restore the previous value; tests should assert `areDenormalsDisabled()`-style by reading the
  register, not by multiplying numbers (fr810's advice in that thread: "checking the actual cpu status
  register is a better idea").
- Clang: `-ffast-math` (or `-funsafe-math-optimizations`) "without -shared" auto-links `crtfastmath.o`,
  "a static constructor that sets the FTZ/DAZ bits in MXCSR, which affects all linked code"; control
  with `-mdaz-ftz` / `-mno-daz-ftz` (verified: https://clang.llvm.org/docs/UsersManual.html, 2026-11-04).
  A plugin is built with `-shared`, so the plugin itself does not get it, but the Standalone target
  and `render_cli` would, and it would change the FP environment of every thread in the process.

### 3.3 Why convolution/reverb tails are prone to denormals

- IIR/feedback and long FIR tails decay geometrically toward zero; once |x| < 2^-126 (~1.2e-38 for
  float) every multiply-add becomes a subnormal operation, which on x86 takes a microcode assist
  (tens to >100 cycles instead of 1) and on some cores is also slow in SIMD lanes. A 3-12 s IR in UPOLS
  keeps multiplying spectra whose late partitions are 60-120 dB down, and silence at the input makes
  the whole state ring down into the subnormal range. (Mechanism: standard DSP knowledge; the
  "performance penalty" and "not IEEE-compliant" statements are verified from the Intel page above;
  the cycle counts are unverified, from memory.)
- pluginval's "Audio processing" test counts subnormals in the output: "Checks for NaNs, Infs,
  subnormals"; the "Fuzz parameters" test at strictness > 5 says "Subnormals treated as errors"
  (verified: pluginval `source/tests/BasicTests.cpp` lines 283-299 and `ParameterFuzzTests.cpp`
  description strings, clone 286684f of 2026-10-15).

---

## 4. Floating-point determinism

### 4.1 FMA contraction defaults

- GCC: "-ffp-contract=off disables floating-point expression contraction"; "fast enables ... forming
  of fused multiply-add operations if the target has native support"; "on enables ... if allowed by
  the language standard"; "The default is -ffp-contract=off for C in a standards compliant mode
  (-std=c11 or similar), -ffp-contract=fast otherwise." (verified: https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html, 2026-11-04).
  Note the wording says *C*; for C++ (including `-std=c++20`) GCC keeps `fast` (inference from the
  doc text; unverified by experiment).
- Clang: `-ffp-contract=on` is the default for C/C++ ("enable C and C++ standard compliant fusion in
  the same statement unless dictated by pragmas"); `fast` fuses across statements; `off` disables;
  `fast-honor-pragmas` is the HIP default. (verified: https://clang.llvm.org/docs/UsersManual.html).
- MSVC: "By default, the /fp:precise option ... Floating-point contractions aren't generated by
  default under /fp:precise. This behavior is new in Visual Studio 2022. Previous compiler versions
  could generate contractions by default under /fp:precise." `/fp:contract` opts in; "By default, the
  /fp:fast option enables /fp:contract"; `/fp:strict` never contracts. (verified:
  https://learn.microsoft.com/en-us/cpp/build/reference/fp-specify-floating-point-behavior, 2026-11-04)
- Hardware reality: x86-64 baseline has no FMA instruction (needs `-mfma`/`-march=haswell`/`/arch:AVX2`),
  so x86 CI builds will not contract regardless of the flag; **AArch64 has FMA in the baseline ISA**,
  so macOS arm64 and Linux arm64 builds contract `a*b + c` by default under both GCC (`fast`) and
  Clang (`on`, within a statement). That alone makes bit-identical results between an x86 runner and
  an Apple Silicon runner impossible without `-ffp-contract=off` on every translation unit of
  `src/sim` (and in third-party code such as PFFFT). (Architecture facts: unverified live, from memory.)
- `#pragma STDC FP_CONTRACT OFF` is honoured by Clang (`fast-honor-pragmas` note) and MSVC
  (`fp_contract` pragma, verified), ignored by GCC (unverified, from memory). Prefer the compiler flag
  on the target.

### 4.2 `-ffast-math` and `/fp:fast` dangers

- GCC `-ffast-math` "Sets the options -fno-math-errno, -funsafe-math-optimizations,
  -ffinite-math-only, -fno-rounding-math, -fno-signaling-nans, -fcx-limited-range and
  -fexcess-precision=fast", defines `__FAST_MATH__`, "is not turned on by any -O option besides
  -Ofast". `-funsafe-math-optimizations` "Enables -fno-signed-zeros, -fno-trapping-math,
  -fassociative-math and -freciprocal-math". `-ffinite-math-only`: "assume that arguments and results
  are not NaNs or +-Infs." `-fassociative-math`: "Allow re-association of operands ... This violates
  the ISO C and C++ language standard by possibly changing computation result." (verified GCC page).
- Clang `-ffast-math` implies `-fno-honor-infinities -fno-honor-nans -fapprox-func -fno-math-errno
  -ffinite-math-only -fassociative-math -freciprocal-math -fno-signed-zeros -fno-trapping-math
  -fno-rounding-math -ffp-contract=fast`, plus `-fcx-limited-range`, and links `crtfastmath.o` (§3.2)
  (verified Clang page).
- MSVC `/fp:fast` example output: `NAN == NAN : 1`, `INFINITY - INFINITY : 0.000000` (verified MS page).
  Under `/fp:fast` and `/fp:precise` the compiler "assumes the floating-point environment isn't accessed
  or modified at runtime" and "is free to ignore the calls to _controlfp_s"; only `/fp:strict`
  (or `#pragma fenv_access`) guarantees that FP-environment changes are respected by the compiler.
  Relevance: FTZ/DAZ writes via `_mm_setcsr` are still executed as intrinsics, but code that *reads*
  the status word or depends on rounding mode is unreliable under precise/fast.
- Concrete failure a reviewer should name: with `-ffinite-math-only`, `std::isnan(x)`/`x != x` can
  be folded to `false`, so NaN-guarding code and pluginval's NaN checks become meaningless.

### 4.3 SIMD vs scalar reductions, libm, and why cross-platform bit-identity is unrealistic

- A vectorised sum changes the association order (4 or 8 partial sums then a horizontal add);
  compilers only auto-vectorise FP reductions when reassociation is allowed (`-fassociative-math`),
  so with default flags scalar loops stay in source order, but **hand-written SIMD** (PFFFT, JUCE
  `FloatVectorOperations`, `juce::dsp::SIMDRegister`) and runtime-dispatched kernels (SSE vs AVX vs
  NEON, `PFFFT_SIMD_DISABLE`) produce different roundings than the scalar reference. (Reassociation
  requirement: GCC `-fassociative-math` text verified; PFFFT specifics unverified, from memory.)
- `sin/cos/exp/pow/log` come from the platform libm (glibc, Apple libm, MSVC UCRT) and differ in the
  last ulp; `std::sqrt` is correctly rounded everywhere but transcendental functions are not required
  to be (unverified, from memory; the C++ standard sets no accuracy requirement).
- 32-bit x87 excess precision (`-fexcess-precision=fast` is the GCC default: "operations may be
  carried out in a wider precision", verified) vs 64-bit SSE; denormal mode; FMA; SIMD width; all
  contribute. Hence the project's AX5 wording "bit-identical run to run on the same platform" is the
  right contract; across OS/CPU use metric tolerances (the golden-file policy in CLAUDE.md).

### 4.4 Random numbers

- Engines are fully specified: "The 10000th consecutive invocation of a default-constructed object of
  type mt19937 produces the value 4123659995"; `mt19937_64` → 9981545732273789042; `minstd_rand0` →
  1043618065. (verified: https://eel.is/c++draft/rand.predef, 2026-11-04)
- Distributions are **not**: `uniform_real_distribution` is specified only by its density
  p(x|a,b) = 1/(b−a) for a ≤ x < b; no algorithm is prescribed (verified: https://eel.is/c++draft/rand.dist.uni.real).
  Therefore `std::uniform_real_distribution`/`std::normal_distribution` sequences legitimately differ
  between libstdc++, libc++ and MSVC STL for the same seed and engine (the standard permits it;
  implementations are known to differ — unverified live, from memory). Any "seeded from `tailSeed`"
  code that must match across OSes needs its own distribution code (e.g. take the top 24/53 bits of
  the engine output and multiply), not a `std::*_distribution`.
- xoshiro/xoroshiro (Vigna): for a 64-bit output x use `(x >> 11) * 0x1.0p-53` to get a double in
  [0,1) ("my implementations now use the multiplicative version, everywhere"); for floats use the
  upper bits (verified: https://prng.di.unimi.it/, 2026-11-04). Licence (CC0) not shown on the page
  today → unverified.
- PCG family: "Very fast", "Very compact", "Arbitrary" period with multiple streams, reproducible
  results "Yes", "permissive license (the Apache license)" (verified: https://www.pcg-random.org/,
  2026-11-04). PCG32 state 64-bit, output 32-bit, period 2^64 (unverified, from memory).
- Real-time note: `std::mt19937` has a 2.5 KB state and a block-refill every 624 draws (O(1)
  amortised, not worst case); xoshiro128**/PCG32 are O(1) with a handful of ops and are the sane
  choice inside process code (mt19937 size/refill: unverified, from memory).

---

## 5. JUCE 8/9 `AudioProcessor` lifecycle and API facts

All quotes verified 2026-11-04 from the JUCE master clone (d60b7a7, version 9.0.5) unless noted; the
docs.juce.com pages carry identical text. The project pins `8.0.17-security`; none of the quoted
APIs changed between 8.0.x and 9.0.5 (checked against `BREAKING_CHANGES.md`, §9).

### 5.1 `prepareToPlay` / `releaseResources` / `processBlock`

- `prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock)`: "Called before playback
  starts, to let the processor prepare itself. The sample rate is the target sample rate, and will
  remain constant until playback stops." `maximumExpectedSamplesPerBlock` "is a strong hint ... You
  should program defensively in case a buggy host exceeds this value. The actual block sizes that
  the host uses may be different each time the callback happens: completely variable block sizes can
  be expected from some hosts." (header lines 121-140)
- `releaseResources()`: "Called after playback has stopped, to let the object free up any resources
  it no longer needs." Hosts may call `prepareToPlay` again *without* `releaseResources` in between:
  pluginval's level-6 "Non-releasing audio processing" test "calls prepareToPlay() at new sample rate
  WITHOUT calling releaseResources() first" (verified pluginval description string).
- `processBlock`: variable and zero-length blocks (§1.1); runs on the audio thread; bypass semantics
  via `getBypassParameter()`.
- pluginval level 8 "Process called with a larger than prepared block size": the source comment says
  passing a larger block than prepared is "technically undefined" for VST/VST3/AU "However,
  juce::AudioProcessor specifically states that this could happen" (verified `ExtremeTests.cpp`).
  The `PartitionedConvolver::process` contract "accepts any n (1…maxBlock)" must therefore be paired
  with a plugin-level guard (split or clamp) for n > maxBlock.

### 5.2 Latency

- `getLatencySamples()`: "The host will call this to find the latency - the processor itself should
  set this value by calling setLatencySamples() as soon as it can during its initialisation."
  `setLatencySamples(int)`: "The processor should call this as soon as it can during initialisation,
  and can call it later if the value changes." (header lines 840-853)
- Implementation: `if (latencySamples != newLatency) { latencySamples = newLatency;
  updateHostDisplay (ChangeDetails().withLatencyChanged (true)); }` (verified
  `juce_AudioProcessor.cpp` line 415-422). So a no-op call is free; a changed value triggers
  listeners.
- VST3 wrapper path: `audioProcessorChanged` ORs `Vst::kLatencyChanged` if
  `details.latencyChanged && latencySamples != lastLatencySamples`, then
  `componentRestarter.restart (flags)`. `ComponentRestarter` is an `AsyncUpdater`: "if
  (MessageManager::getInstance()->isThisTheMessageThread()) handleAsyncUpdate(); else
  triggerAsyncUpdate();" and finally `handler->restartComponent (flags)` on the message thread.
  While inside `setupProcessing` the flags are masked to `kLatencyChanged` only. (verified
  `juce_audio_plugin_client_VST3.cpp` 1503-1575, 1621-1630; `juce_VST3Common.h` 1625-1663)
- The VST3 SDK: `restartComponent` "must be called in the UI-Thread context!"; `kLatencyChanged`:
  "The plug informs the host that its latency has changed" and the host should deactivate/reactivate
  the plug-in and query the new latency; `getLatencySamples` is called on the "UI thread, Setup Done"
  state. (verified: https://steinbergmedia.github.io/vst3_doc/vstinterfaces/classSteinberg_1_1Vst_1_1IComponentHandler.html,
  .../namespaceSteinberg_1_1Vst.html, .../classSteinberg_1_1Vst_1_1IAudioProcessor.html, 2026-11-04)
- AU wrapper path: latency change → `AsyncUpdater` → on the message thread
  `PropertyChanged (kAudioUnitProperty_Latency, kAudioUnitScope_Global, 0)`; `GetLatency()` returns
  `getLatencySamples() / rate` using the output bus stream format sample rate (44100 if no buses);
  `GetTailTime()` returns `getTailLengthSeconds()` (verified `juce_audio_plugin_client_AU_1.mm`
  1206-1232, 2015-2044). Apple: `kAudioUnitProperty_Latency` is "A read-only Float64 value valid on
  the audio unit global scope. The time, in seconds, that it takes an audio unit to move an audio
  sample from its input to its output." `kAudioUnitProperty_TailTime`: "a time estimate, in seconds,
  between the last valid input being received by an audio unit and the audio unit's output becoming
  silent ... usually a conservative estimate that you can depend on." (verified:
  https://developer.apple.com/documentation/audiotoolbox/kaudiounitproperty_latency.md and
  .../kaudiounitproperty_tailtime.md, 2026-11-04)
- Where to call it: JUCE's wrappers make a call from `processBlock` *technically* safe (atomic
  OR + async trigger; `triggerAsyncUpdate` posts a message — allocation-free in JUCE (unverified,
  from memory)). But jules (JUCE, 2018): calling from the process callback is "not the kind of
  operation you'd expect to be real-time-safe"; from `prepareToPlay` "is also a bad place ... as far
  as hosts are concerned" because the host has already built its graph; PreSonus: "This should be
  called in the UI-Thread context!" (secondary, verified: https://forum.juce.com/t/vst3-latency-reporting-in-presonus-studio-one-fails/28249).
  JUCE's own wrapper comment: "Wavelab 11.1 calls setBusArrangements in the same call stack when the
  AudioProcessor calls setLatencySamples inside prepareToPlay" (verified VST3 wrapper 2754-2758).
  Project policy (Phase 07): latency is constant per instance at a given sample rate and set in
  `prepareToPlay` — acceptable; reviewers should check it is only *re-set* when the value actually
  changes and never from `processBlock` in realtime mode.

### 5.3 Non-realtime (offline) mode

- `isNonRealtime()`: "Returns true if the processor is being run in an offline mode for rendering.
  ... If the mode is unknown, this will assume it's realtime and return false. This value may be
  unreliable until the prepareToPlay() method has been called, and could change each time
  prepareToPlay() is called." (header 966-976)
- VST3 sets it in `setupProcessing`: `setNonRealtime (newSetup.processMode == Vst::kOffline)` and
  then calls `preparePlugin(...)` (verified wrapper 3517-3532). AU sets it from the offline-render
  property under `getCallbackLock()` and re-runs `prepareToPlay` if already prepared (verified AU
  wrapper 807-815). Some hosts (Ableton, per the forum thread "Ableton offline rendering at altered
  sample rate issue") change sample rate for the bounce without re-instantiating; pluginval's
  sample-rate loop covers that.
- Phase 07's "synchronous IR rebuild in `processBlock` when `isNonRealtime()`" is allowed by this
  contract but the reviewer must check: the realtime branch never takes that path even if the host
  flips the flag mid-stream; the flag is read once per block; the synchronous path is exercised by
  the offline-determinism test.

### 5.4 Bypass and tail

- `processBlockBypassed`: "The default implementation of this method will pass-through any incoming
  audio, but you may override this method e.g. to add latency compensation to the data to match the
  processor's latency characteristics. This will avoid situations where bypassing will shift the
  signal forward in time, possibly creating pre-echo effects and odd timings." (header 295-305).
  With reported latency P + pre-roll, a pass-through bypass is misaligned by exactly that amount;
  either delay the dry signal or accept and document.
- `getTailLengthSeconds()`: "Returns the length of the processor's tail, in seconds." (pure virtual).
  VST3 wrapper: `<= 0` → `kNoTail`; `std::isinf` → `kInfiniteTail`; else seconds × sample rate
  (verified wrapper 3545-3553). A convolver's correct answer is IR length (+ crossfade) in seconds;
  returning 0 makes hosts truncate bounces at the last input sample.

### 5.5 Parameters: `ParameterID`, version hints, IDs, ranges, gestures

- `ParameterID (StringLike&& identifier, int versionHint = 0)`: "identifier: A string that uniquely
  identifies a single parameter"; "versionHint: Influences parameter ordering in Audio Unit plugins.
  Used to provide backwards compatibility of Audio Unit plugins in Logic and GarageBand." (verified
  `juce_AudioProcessorParameterWithID.h` 38-60)
- What the AU wrapper actually does with it: the parameter list handed to the host is sorted by
  identifier and then `std::stable_sort`ed by `versionHint` (`vec.push_back ({ generateAUParameterID
  (*param), param->getVersionHint() })` ... `std::sort(... identifier ...)`; `std::stable_sort (...
  versionHint ...)`). So parameters added later must carry a **higher** version hint, otherwise they
  are interleaved by ID and Logic/GarageBand, which key automation by parameter *index* in some
  paths, map old automation onto the wrong parameter (verified code `juce_audio_plugin_client_AU_1.mm`
  2351-2358; the Logic-by-index behaviour is the stated rationale, unverified beyond the doc string).
- AU numeric parameter IDs are `String::hashCode()` of the paramID string (negative bit cleared with
  `JUCE_USE_STUDIO_ONE_COMPATIBLE_PARAMETERS`); `jassert` on hash collision; with
  `JUCE_FORCE_USE_LEGACY_PARAM_IDS` the index is used (verified 2448-2460). VST3 IDs are derived the
  same way via `LegacyAudioParameter::getParamID` (unverified, from memory). Hence: renaming a
  paramID string changes the AU and VST3 numeric IDs and orphans automation and some saved state;
  reordering parameters only matters under legacy IDs. The `JUCE_FORCE_USE_LEGACY_PARAM_IDS` doc:
  "Changing this setting may mess up user's DAW projects, see
  VST3ClientExtensions::getCompatibleParameterIds() for a way to overcome this issue on newer VST3
  hosts." (verified `juce_audio_plugin_client.h` 79-90)
- Discrete parameters: the AU wrapper asserts in debug that `isDiscrete()` parameters do not use the
  default step count ("Some hosts can't handle the huge numbers of discrete parameter values"), and
  requires `PLUGIN_CODE`/`MANUFACTURER_CODE` with an upper-case letter (verified 2394-2400; CMake docs §8).
- `NormalisableRange`: `skew = 1` default; "If you have used lambda functions for convertFrom0to1Func
  and convertFrom0to1Func in the constructor of this class then the skew value is ignored."; invariants
  `end > start`, `interval >= 0`, `skew > 0` are `jassert`ed; `setSkewForCentre(centre)` requires
  `start < centre < end`; `symmetricSkew` applies the skew from the middle to both ends (verified
  `juce_NormalisableRange.h` 204-257). Review: `room_w/d/h` "1.5-100, skewed" must choose skew or a
  centre, and the freeze test must record it (changing skew changes what a stored normalised 0.5
  means → silently moves every saved project).
- `setValueNotifyingHost`: "A processor should call this when it needs to change one of its
  parameters ... Note that to make sure the host correctly handles automation, you should call the
  beginChangeGesture() and endChangeGesture() methods"; `beginChangeGesture`: "If you call this, it
  must be matched by a later call to endChangeGesture()"; `endChangeGesture`: "A call to this method
  must follow a call to beginChangeGesture()" (verified `juce_AudioProcessorParameter.h` 131-157).
  VST3 side: `beginEdit/performEdit/endEdit` "must be called in the UI-Thread context!" (verified
  IComponentHandler page). Never call these from the audio thread or from a parameter listener.
- APVTS: `getRawParameterValue` returns `std::atomic<float>*` "which a realtime process can read";
  inside `Listener::parameterChanged` "retrieving the value ... is not guaranteed to return the
  up-to-date value ... use the newValue parameter" (verified header 340-362). `parameterChanged` is
  invoked synchronously on whichever thread changed the parameter — for host automation that is the
  audio thread (unverified, from memory; the docs do not state the thread). Review rule: a listener
  may only flip an atomic "dirty" flag or push to an SPSC queue; it must not rebuild, allocate or
  lock. `copyState/replaceState` use locks (§1.2).
- pluginval 2.0's level-8 "Discrete parameter state restoration" fails "for parameters that keep the
  raw normalised value, such as juce::AudioParameterBool" (verified release notes v2.0.0-beta2/3,
  https://github.com/Tracktion/pluginval/releases/tag/v2.0.0-beta3). If the project moves to
  pluginval 2, `output_mode` (choice) must snap to its step on restore.

### 5.6 State

- `getStateInformation(MemoryBlock&)`: "The host will call this method when it wants to save the
  processor's internal state. This must copy any info about the processor's state into the block of
  memory provided ... The resulting state should generally include all parameter values. If you have
  implemented getBypassParameter(), ensure that the value of the bypass parameter is included".
  `setStateInformation(const void*, int)`: "This must restore the processor's state from a block of
  data previously created using getStateInformation()" and "VST3ClientExtensions::getCompatibleParameterIds()
  will always be called after setStateInformation()" (verified header 1146-1204).
- Call-order quirks (secondary, JUCE forum 2018, verified 2026-11-04
  https://forum.juce.com/t/calling-order-of-setstateinformation-and-preparetoplay/28834): chkn:
  "unfortunately there is no standard behaviour."; Reaper calls `prepareToPlay` first and does not
  call `setStateInformation` at all for a freshly inserted plugin; dave96: "you need to be able to
  deal with anything at any time". Another thread reports Logic calling state methods off the UI
  thread and deadlocking if the plugin takes the message-manager lock there (secondary,
  https://forum.juce.com/t/phenomenon-with-juce-based-au-plugins-in-juce-based-hosts-like-tracktion/15188).
  Pro Tools reportedly calls `prepareToPlay` once, before `setStateInformation` (secondary,
  https://forum.juce.com/t/protools-preparetoplay-only-called-once-before-setstateinformation/36061).
  Phase 07's risk note ("Logic calls setStateInformation before prepareToPlay") is therefore one of
  several orders; the code must handle *both* orders and a call from a non-message thread.
- pluginval level 7 "Background thread state": "Opens editor on message thread. From background
  thread: getStateInformation(), randomise params, setStateInformation(). Sleeps 2s for async
  updates" (verified description string) — this is exactly the Logic scenario.
- JUCE 9.0.5 (and 8.0.17-security): `ValueTree::readFromStream/readFromData/readFromGZIPData` return
  an invalid tree for nesting > 256 levels and no longer preallocate from counts in the data; JSON
  and XML parsers reject nesting > 256 (XML: entity nesting > 40, > 8 MB expansion); `XmlDocument`
  loads external entities only through a supplied `InputSource` (verified `BREAKING_CHANGES.md`
  "Version 9.0.5" and the 8.0.17-security release notes). Corrupt-state fuzzing (Phase 07) now gets
  an *invalid* tree instead of a crash — code must check `isValid()` rather than assume.
- Versioning: store `pluginStateVersion` and the full scene JSON; treat the APVTS tree as derived
  data; migrate forwards only; fixtures per version (project policy, Phase 07).

### 5.7 Threads and UI

- Message-thread-only: anything touching `Component`s, `MessageManager`, `updateHostDisplay`
  semantics for parameter-info changes (VST3 `restartComponent` must be UI thread — JUCE defers it,
  §5.2), `updateTrackProperties` "may only be called on the message thread" (verified docs page).
  `audioWorkgroupContextChanged` "will only be called on the audio thread" (Apple only).
- `juce::Thread` vs `std::thread` (verified: https://docs.juce.com/master/classThread.html,
  2026-11-04): `startThread(Priority)` — "priority ... is ignored on Linux" for non-realtime
  threads; `Priority::background` "Restricted to efficiency cores on platforms that have them";
  `startRealtimeThread(RealtimeOptions)`: "You cannot change the options of a running realtime
  thread, nor switch a non-realtime thread to a realtime thread"; "You must never attempt to delete
  a Thread object while it's still running"; `stopThread(timeout)` kills the thread after the
  timeout, "which is a very bad thing to happen"; `wait()/notify()` pattern — call `notify()` after
  `signalThreadShouldExit()`. `std::thread` is fine for the IR builder if the destructor joins and
  the thread checks an atomic stop flag; `juce::Thread` adds naming, priority and the
  wait/notify coalescing Phase 07 wants. Either way: the builder must be stopped in the processor
  destructor *before* the engine it writes into is destroyed, and must never be joined from the
  audio thread.
- `createPluginFilter`: declared `juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter();` in
  `juce_audio_processors.h` ("If you're implementing a plugin, you should supply a body for this
  function in your own code"); the wrappers call it through `createPluginFilterOfType` and
  `jassert (pluginInstance != nullptr && pluginInstance->wrapperType == type)` (verified
  `juce_audio_processors.h` 85-89, `detail/juce_CreatePluginFilter.h` 40-48). It is called on the
  host's instantiation thread (not necessarily the message thread); do no GUI work there.

---

## 6. pluginval

### 6.1 Versions (verified 2026-11-04 from tags fetched into the clone and the GitHub releases pages)

- **v1.0.4** — latest stable release, tag commit 2024-12-04; GitHub marks it "Latest". Notes: LV2
  support, CTest CMake module, JUCE 8.0.3, Ubuntu 22.04 minimum, auval stress test capped at 20 s
  (was 600), fixed a false "ALL TESTS PASSED" when validating out of process. This is the version the
  repo's `run_pluginval.sh` pins.
- **v2.0.0-beta1/2/3** — pre-releases, 2026-10-13 / 10-14 / 10-14 (beta3 fixes the macOS app not
  finding `librtcheck.dylib`). Built against JUCE 9.0.3. CLI restructured into subcommands
  (`validate` default, `run-tests`, `strictness-help [level]`, `test <config.json>`); old flat flags
  deprecated; unknown options now error; `--junit-xml`, `--json-results`, `--config` (repeatable,
  precedence defaults < env < config < CLI); every option available as an env var
  (`--skip-gui-tests` → `SKIP_GUI_TESTS=1`); falsy env values now turn flags off; new `--rtcheck`.
  (verified: `docs/Command line options.md` in clone 286684f, release pages)

### 6.2 Strictness-level semantics (test → minimum level), from the sources

Verified by grepping `PluginTest ("name", level` in `source/tests/*.cpp` of 2.0 (clone 286684f) and
of tag v1.0.4. Level N runs every test with level ≤ N.

| Level | Tests (2.0; same in 1.0.4 unless noted) | What it does (2.0 description strings) |
|---|---|---|
| 1 | Plugin info; Locale check (2.0 only) | logs name, double-precision support, latency, tail |
| 2 | Automatable Parameters; Editor; Plugin programs; Plugin state | opens editor cold/warm; cycles programs; get/setState round trip |
| 3 | Audio processing; Automation; Editor DPI Awareness | "Processes 10 blocks at each sample rate / block size combo ... Checks for NaNs, Infs, subnormals" |
| 4 | Basic bus; Bus layout processing; Open editor whilst processing | enumerates layouts, `enableAllBuses/disableNonMainBuses`; "Starts async thread calling processBlock() repeatedly, then calls createEditor() on message thread" |
| 5 | Editor Automation; auval; vst3 validator | `auval -strict -v`, Steinberg `vstvalidator` (if built with it) |
| 6 | Fuzz parameters; Editor stress; Non-releasing audio processing; Plugin state restoration | 32-sample sub-blocks with up to 10 random param changes between blocks, "Subnormals treated as errors" above 5; `prepareToPlay` at new rate without `releaseResources`; save → randomise → restore |
| 7 | Parameters; Parameter thread safety; Background thread state | "Message thread calls setValueNotifyingHost() 500x on all params. Simultaneously, this thread calls setValue() and processBlock() 500x"; state calls from a background thread while the editor is open |
| 8 | Process called with a larger than prepared block size; Discrete parameter state restoration (2.0 only) | oversized block; exact binary state match in "Plugin state restoration" (2.0: "Also requires exact binary state match" at ≥ 8); two-step params get arbitrary normalised values at ≥ 8 |
| 9 | Allocations during process | counts heap allocations inside `processBlock` |
| 10 | (no additional named test) | `auval -strict -stress 20 -v` at > 5 and `vstvalidator -e` at > 5 already; level 10 simply runs everything |

Caveats: in v1.0.4 `EditorTests.cpp` and `ExtremeTests.cpp` existed in the tree but were **not in
the CMake source list** (verified `git show v1.0.4:CMakeLists.txt` lines 55-67 list only
`BasicTests.cpp`, `BusTests.cpp`, `ParameterFuzzTests.cpp`); the 2.0 notes confirm "Editor stress and
extreme tests (real-time allocation and oversized block) that were in the source tree are now
compiled into the build". So with the pinned v1.0.4, "strictness 10" does **not** run the level-9
allocation test or the level-8 oversized-block test — the project's own AllocationTracker test is
the only allocation guard until pluginval is bumped. README: "5 being generally recognised as the
lowest level for host compatibility. Lower levels are generally quick tests, mainly checking call
coverage for crashes. Higher levels contain tests which take longer to run such as parameter fuzz
tests and multiple state restoration." (verified README)

### 6.3 Flags

- 2.0 `validate` options (verified `docs/Command line options.md`): `--strictness-level INT`
  (1-10, default 5), `--timeout-ms INT` (default 30000, -1 never), `--repeat INT`, `--randomise`,
  `--verbose`, `--skip-gui-tests` ("for headless CI"), `--sample-rates FLOAT,...` (default
  44100,48000,96000), `--block-sizes INT,...` (default 64,128,256,512,1024), `--data-file`,
  `--output-dir`, `--output-filename`, `--junit-xml`, `--json-results`, `--disabled-tests` (names or
  a file), `--random-seed` (hex 0x.. or int, "for replicable test runs"), `--config`, `--rtcheck
  {disabled,enabled,relaxed}` ("relaxed: Checks for realtime safety after the first audio callback
  (to allow initialisation)"), `--version`, `-h`. Exit code 0/1.
- `--validate-in-process`: added in 0.1.2; in 2.0 it is **not** a CLI option any more — "validate in
  process" is a GUI preference (`MainComponent.cpp` `getValidateInProcess`) and the README says
  "Validation is performed in a separate process to avoid crashing". The debugging doc still says: build
  pluginval in Debug, "Set validate in process to on", match the strictness level of the failed log,
  break in `UnitTestRunner::addFail` or flip `testRunner.setAssertOnFailure (false)` to true; replicate
  with the log's random seed, timeout, repeats and randomise setting. (verified docs)
- v1.0.4 CLI (the pinned version; verified `git show v1.0.4:Source/CommandLine.cpp`): `--validate
  <path>`, `--strictness-level`, `--random-seed`, `--timeout-ms`, `--verbose`, `--skip-gui-tests`,
  `--repeat`, `--randomise`, `--data-file`, `--output-dir`, `--output-filename`, `--disabled-tests`,
  `--sample-rates`, `--block-sizes`, `--vst3validator [pathToValidator]` ("If specified, this will run
  the VST3 validator as part of the test process"), `--run-tests`, `--help`, `--version`. There is
  **no** `--validate-in-process`, `--junit-xml`, `--json-results`, `--config` or `--rtcheck` in
  1.0.4; in-process validation is GUI-only. The repo's `run_pluginval.sh` must therefore not pass 2.0
  flags until it bumps the pin, and 1.0.4 ignores unknown options silently (2.0 errors on them).
- `--rtcheck` is implemented with the `rtcheck` library (`PLUGINVAL_ENABLE_RTCHECK`,
  `rtc::realtime_context`), wrapped around `processBlock` in the audio-processing, fuzz, thread-safety
  and allocation tests; mutex lock/unlock checks are disabled for the thread, so it flags
  malloc/free/syscalls but tolerates uncontended locks (verified `source/RTCheck.h`, grep of
  `RTC_REALTIME_CONTEXT_IF_ENABLED`).

### 6.4 Reading the log

- The log header prints the settings needed to replicate (random seed, timeout, repeats, randomise);
  each test prints `Starting test: <name>` style lines and failures from `UnitTestRunner::addFail`;
  the run ends with `ALL TESTS PASSED` or `FAILED!!` (v1.0.4 fixed a case where "ALL TESTS PASSED" was
  printed wrongly out of process). 2.0 adds per-test `<testcase>` entries in JUnit XML and a JSON
  report with `status` `passed|failed|error`; if pluginval does not finish (plugin crash/timeout) the
  report "contains a single error entry saying so, so a report left over from an earlier run is never
  mistaken for a pass." (verified `docs/Adding pluginval to CI.md`, v1.0.4 notes; exact log line
  wording unverified beyond those strings).
- Common failures seen in the wild (from the test descriptions above, secondary forum reports):
  NaN/Inf/subnormal counts in output (uninitialised buffers, denormal tails, division by zero on
  degenerate parameters such as zero room size), state round trip not restoring parameters within
  0.1, crashes when `prepareToPlay` is re-entered without `releaseResources`, timeouts because a
  test's 30 s budget is exceeded by slow synchronous work in `setStateInformation` (the project's
  synchronous IR rebuild!), editor tests failing headless (use `--skip-gui-tests`), AU "No types"
  when the component is not in `~/Library/Audio/Plug-Ins/Components` or the registrar is stale
  (secondary, https://forum.juce.com/t/pluginval-au-plugins-returning-no-types-but-play-fine-in-logic/36687).

---

## 7. auval basics

- Command: `auval -v TYPE SUBT MNFR` validates one unit (e.g. `auval -v aufx Spsc Mkrf` as in
  CLAUDE.md); `auval -a` lists all installed units; `auval -s TYPE` lists units of a type; `-h` help;
  `-w` keeps auval alive (for leak checks), `-q` quiet. (verified: Apple TN2204
  https://developer.apple.com/library/archive/technotes/tn2204/_index.html, archived doc last updated
  2008-09-08, read 2026-11-04). `-strict` and `-stress N` are the options pluginval uses: `auval
  -strict -v` at level ≤ 5, `auval -strict -stress 20 -v` above (verified pluginval description
  strings; the flags are not documented in TN2204).
- Phases (TN2204): VALIDATING AUDIO UNIT (type must be an Apple type; manufacturer code must contain
  an upper-case letter); TESTING OPEN TIMES (cold/warm); VERIFYING DEFAULT SCOPE FORMATS (44.1 kHz
  default, supported channel config); REQUIRED / RECOMMENDED (warnings) / OPTIONAL PROPERTIES;
  SPECIAL PROPERTIES (class info = persistence format, view discovery, factory presets); PUBLISHED
  PARAMETER INFO; FORMAT TESTS (accepts supported, rejects unsupported channel layouts); RENDER TESTS
  (varying `MaxFramesPerSlice`, `AudioUnitReset`, connection semantics, atomic and ramped parameter
  changes during render). "AU VALIDATION SUCCEEDED" = every phase PASS with no ERROR; WARNINGs do not
  fail it. auval checks "operational correctness and interface semantics, not implementation quality
  or UI".
- Common failure causes (TN2204 phases + secondary reports): wrong/absent upper-case letter in codes
  (JUCE CMake doc: `PLUGIN_CODE` "must contain exactly one upper-case letter", `PLUGIN_MANUFACTURER_CODE`
  "at least one upper-case letter", "GarageBand 10.3 requires the first letter to be upper-case"), a
  bus layout accepted by `isBusesLayoutSupported` that then crashes in render, latency/tail returning
  nonsense (negative, NaN; `GetLatency` asserts `rate > 0`), class-info (state) round-trip producing a
  different state, slow open times, parameter info with a huge discrete step count, and the registrar
  cache: a rebuilt component with the same version may not be rescanned — bump the version or clear the
  cache (`killall -9 AudioComponentRegistrar`) (the registrar tip: unverified, from memory). Under
  Rosetta, run `arch -x86_64 auval` to validate the x86_64 slice (unverified, from memory).
- auval must be run from a GUI login session; CI on macOS runners works with pluginval's wrapper.

---

## 8. VST3 specifics

- Bundle layout (verified: https://steinbergmedia.github.io/vst3_dev_portal/pages/Technical+Documentation/Locations+Format/Plugin+Format.html,
  2026-11-04): macOS: a standard bundle `X.vst3/Contents/MacOS/X` (universal Mach-O),
  `Contents/Info.plist`, `Contents/Resources/moduleinfo.json`, optional `PkgInfo`. Windows: a
  bundle-like folder `X.vst3/Contents/x86_64-win/X.vst3` (also `x86-win`, `arm64-win`, `arm64ec-win`,
  `arm64x-win`), `Contents/Resources/moduleinfo.json`, optional `desktop.ini` + `Plugin.ico`; "The
  folder and the DLL must have the same name." Linux: `X.vst3/Contents/x86_64-linux/X.so` (or
  `<uname -m>-linux`), same name rule. JUCE generates `moduleinfo.json` in a POST_BUILD step when
  `VST3_AUTO_MANIFEST` is `TRUE` (default); "does require that the plugin can be successfully loaded
  immediately after building"; set `FALSE` and call `juce_enable_vst3_manifest_step` later if signing
  is needed (verified JUCE `docs/CMake API.md`).
- Plugin identity: VST3 identifies classes by 16-byte FUIDs. JUCE derives them from
  `JucePlugin_ManufacturerCode` and `JucePlugin_PluginCode` in `VST3Interface::jucePluginId`: word0
  is a per-interface constant (`0xABCDEF01` for component/controller/ara/compatibility, `0x0101ABAB`
  for the processor class), word1 another per-interface constant (controller `0x1234ABCD`,
  compatibility `0xC0DEF00D`, ara `0xA1B2C3D4`, ...), then the two four-char codes; a
  `JUCE_VST3_COMPONENT_CLASS` define (32 hex chars) overrides the component ID (verified
  `juce_VST3Interface.h` 179-211). With `JUCE_VST3_CAN_REPLACE_VST2` (default **1**) the component
  and controller IDs are instead built from `JucePlugin_VSTUniqueID` and the plugin name
  (`vst2PluginId`), so flipping that flag changes the IDs: "If you change this option then your VST3
  plug-in will, by default, be incompatible with previous versions." (verified
  `juce_audio_plugin_client.h` 63-77; forum thread "FR: Allow custom VST3 UIDs" confirms "the whole UID
  must be the same" for a host to treat it as the same plugin). Changing `PLUGIN_CODE`,
  `PLUGIN_MANUFACTURER_CODE`, the VST2 unique ID, the product name (under CAN_REPLACE_VST2) or the
  flag therefore makes every saved project show "plugin missing"; AU identity is the
  type/subtype/manufacturer triple, so the same codes orphan AU sessions. JUCE's CMake default
  `PLUGIN_CODE` is "a random code that changes each time the build is configured" — a project that
  does not set it explicitly ships a different plugin every build (verified CMake doc).
  `JUCE_FORCE_USE_LEGACY_PARAM_IDS` and `JUCE_VST3_CAN_REPLACE_VST2` are frozen together: a warning
  (`JUCE_IGNORE_VST3_MISMATCHED_PARAMETER_ID_WARNING`) fires if VST2 replacement is on without legacy
  IDs, because VST2 used indices (verified header 141-148).
- Processing precision: the host asks `canProcessSampleSize(kSample32|kSample64)`; JUCE answers
  `kSample64` only if `supportsDoublePrecisionProcessing()` returns true, and `setupProcessing` then
  calls `setProcessingPrecision(doublePrecision)` so `processBlock(AudioBuffer<double>&)` is used
  (verified wrapper 3505-3530). JUCE doc: "If you return true, you must override the
  double-precision processBlock"; query `getProcessingPrecision()` in `prepareToPlay` to allocate.
  For this project the engine is float; keep `supportsDoublePrecisionProcessing() == false` (default)
  unless a double path is tested.
- Bus negotiation: `setBusArrangements` may (1) accept and adapt its buses → `kResultTrue`; (2)
  partially adapt (prefer `kMain` over `kAux`) → `kResultFalse`; (3) keep or fall back to a default
  → `kResultFalse`; called on the UI thread in Initialized/Connected/Setup Done; `setupProcessing`
  "Called in disable state (setActive not called with true)"; `setProcessing` may run on the UI or
  processing thread so "only light operation (no memory allocation or big setup reconfiguration)";
  `process` on the processing thread (verified IAudioProcessor page). JUCE maps this through
  `isBusesLayoutSupported` ("The default implementation accepts any layout"); the stereo-only rule in
  Phase 07 must be implemented there and pluginval's "Bus layout processing" (level 4) walks every
  mono/stereo combination including sidechains, so rejecting must not crash.
- Restart flags the host may receive from JUCE: `kParamTitlesChanged`, `kParamValuesChanged`,
  `kLatencyChanged`, `kParamIDMappingChanged`; `kIoChanged` means the host must "deactivate,
  renegotiate, and reactivate"; `kReloadComponent` unloads the plug-in completely (verified
  RestartFlags page).

---

## 9. JUCE versions and breaking changes (verified from tags fetched 2026-11-04)

- JUCE master = **9.0.5** (tag commit 2026-11-02 12:32 UTC). 9.0.0 was tagged 2026-07-21. The 8.0
  line: **8.0.15** (2026-07-21) is the last feature release; **8.0.16-security** (2026-10-12) and
  **8.0.17-security** (2026-11-02) are security back-ports (String input hardening; ZipFile link
  confinement; XmlDocument entity/nesting limits; JSON/ValueTree nesting limits; WAV/AIFF/PNG/GIF
  parsing hardening; OSC nesting). A `7.0.14-security` also shipped 2026-11-02. The repo's pin
  `8.0.17-security` is current for the 8.x line. (Dates from `git log` of the fetched tags; headline
  notes from https://github.com/juce-framework/JUCE/releases.)
- Breaking changes since 8.0.0 touching `AudioProcessor`/parameters/VST3/AU/CMake/threading (verified
  `BREAKING_CHANGES.md` in master):
  - 8.0.4: `VST3ClientExtensions::getCompatibleClasses()` returns a 16-byte array, not `String`.
  - 8.0.5: `AudioProcessor::TrackProperties` members are `std::optional`; `AudioTransportSource::hasStreamFinished` fixed.
  - 8.0.9: `TrackProperties::colour` → `colourARGB` (uint32) so headless `AudioProcessor` builds need
    no `juce_graphics`; `AudioPluginFormatManager::addDefaultFormats()` removed → free function
    `addDefaultFormatsToManager()`; parts of `VST3ClientExtensions` moved to `VST3Interface` behind
    `JUCE_VST3_COMPATIBLE_CLASSES`; CMake on Windows switched from `/Z7` to `/Zi` (set
    `CMAKE_MSVC_DEBUG_INFORMATION_FORMAT`/`CMP0141` if your cache tooling needs embedded debug info);
    `AudioFormat::createWriterFor` has a single virtual overload.
  - 8.0.11: `var` equality is deep for `DynamicObject`; `JUCE_ASIO` defaults to bundled sources.
  - 8.0.13: `AudioProcessor::createEditor()` is private → use `createEditorAndMakeActive()`;
    `AudioPluginInstance::getPlatformSpecificData()` and `ExtensionsVisitor` removed → `getVSTClient()/
    getVST3Client()/getAudioUnitClient()/getARAClient()`; `VSTPluginFormatHeadless` API changes;
    ARA SDK 2.3.0 required.
  - 9.0.0: `Drawable` no longer inherits `Component`; EGL instead of GLX on Linux; `libxi-dev`
    required unless `JUCE_USE_XINPUT=0`; Windows multi-touch off by default; CMake "improved ... for
    headless environments".
  - 9.0.2: `ThreadPool::addJob` takes one callable returning `void` or `JobStatus`.
  - 9.0.5: ValueTree/JSON/XML nesting limits (§5.6), macOS 12 / iOS 15 minimum deployment targets in
    Projucer defaults, `NativeMessageBox` API renames, `Component::createNewPeer` signature.
  - Module layout: in 9.x the processor classes live in `juce_audio_processors_headless/` (the
    path `modules/juce_audio_processors/processors/juce_AudioProcessor.h` no longer exists); include
    paths via module headers are unchanged. (observed in the clone)
- `juce_add_plugin` option keys (verified `docs/CMake API.md`): `PRODUCT_NAME`, `VERSION`,
  `BUILD_VERSION`, `BUNDLE_ID`, `COMPANY_NAME`, `COMPANY_COPYRIGHT`, `PLUGIN_NAME`, `PLUGIN_CODE`,
  `PLUGIN_MANUFACTURER_CODE`, `FORMATS` (`Standalone Unity VST3 AU AUv3 AAX VST LV2`), `IS_SYNTH`,
  `NEEDS_MIDI_INPUT/OUTPUT`, `IS_MIDI_EFFECT`, `EDITOR_WANTS_KEYBOARD_FOCUS`, `VST3_CATEGORIES`
  (`Fx`, `Reverb`, `Spatial`, `Stereo`, ... default `Fx`), `AU_MAIN_TYPE`, `AU_SANDBOX_SAFE`,
  `AU_EXPORT_PREFIX`, `VST3_AUTO_MANIFEST`, `VST3_CAN_REPLACE_VST2` (not documented in the option
  list today; the preprocessor flag is `JUCE_VST3_CAN_REPLACE_VST2`, default 1), `COPY_PLUGIN_AFTER_BUILD`,
  `VST3_COPY_DIR`/`AU_COPY_DIR`, `HARDENED_RUNTIME_ENABLED` ("Required for notarisation"),
  `MICROPHONE_PERMISSION_ENABLED`, `PLUGINHOST_AU`, `USE_LEGACY_COMPATIBILITY_PLUGIN_CODE`,
  `LV2_URI`, `AAX_IDENTIFIER`. Properties are exposed as `JUCE_<KEY>` on the target; "changing their
  values [after creation] might not have any effect (or might even break things in unexpected ways!)".
- pluginval 2.0 is built on JUCE 9.0.3; a JUCE 8 plugin is still validated by it (host/plugin ABI is
  the VST3/AU API, not JUCE), so bumping pluginval does not require bumping JUCE.

---

## 10. Reviewer's checklist for diffs touching `src/plugin` or the real-time engine

Each question names the failure it catches. "Audio path" = `processBlock`, `RealtimeEngine::process`,
`CrossfadingConvolver`, anything reachable from them in realtime mode.

Real-time safety
1. Does any function reachable from the audio path call `new`, `delete`, `malloc`, `make_unique`,
   `make_shared`, `std::vector` growth, `AudioBuffer::setSize`, `MemoryBlock`, `juce::String`,
   `std::string`, `std::function` assignment, `std::map` access? → heap allocation on the audio
   thread (glitches; AllocationTracker/pluginval level 9/RTSan will fail).
2. Any `std::mutex`, `CriticalSection`, `ScopedLock`, `MessageManagerLock`, `copyState/replaceState`,
   `getCallbackLock()` in the audio path? → priority inversion; APVTS `copyState` is documented
   "not realtime-safe".
3. Any `DBG`, `Logger`, `printf`, file/URL access, `jassert` with string formatting in the audio
   path? → I/O and allocation (debug builds glitch; TSan/RTSan noise).
4. Any loop whose trip count depends on another thread (`while (!ready)`, CAS retry without bound,
   `wait()`)? → unbounded execution time, deadlock if the other thread is lower priority.
5. Any `throw`, `.at()`, `std::stoi`, `std::variant::emplace` with throwing ctors, in the audio path?
   → exceptions are not real-time safe; a thrown exception escaping `processBlock` crashes the host.
6. Any `std::shared_ptr` *copied or reset* on the audio thread? → last-reference release frees
   memory on the audio thread; use raw pointer + deferred release.
7. Any `std::atomic<std::shared_ptr<T>>`, `std::atomic_load(&sp)`? → typically lock-based; must
   be a `std::atomic<T*>` with `static_assert(is_always_lock_free)`.
8. Does `processBlock` read `isNonRealtime()` once and take exactly one of two paths, with the
   synchronous rebuild only in the non-realtime branch? → realtime glitch if the host flips the flag
   or the branch is mis-nested.
9. Does the code handle `numSamples == 0`, `numSamples > maximumExpectedSamplesPerBlock`, and
   channel counts wider than the layout? → host quirks, pluginval level 8, JUCE doc warnings.
10. Is `ScopedNoDenormals` (or the sim equivalent) created inside the callback on every call, and
    does the sim guard set FZ on AArch64 (bit 24) and FTZ|DAZ (0x8040) on x86, restoring on exit?
    → denormal CPU spikes in tails on Apple Silicon/Linux arm64; leaked FP mode into the host.

Handover and lifetime
11. Is every cross-thread handover a single `exchange`/SPSC FIFO with release/acquire (or seq_cst)
    ordering, not `load` + `store` or `relaxed`? → lost updates, torn reads on ARM.
12. Who disposes an un-consumed mailbox entry when the producer overwrites it? → leak (ASan in the
    100-requests test).
13. Where does the displaced current `IrSet` go, and what happens when the release FIFO is full?
    → free on the audio thread, or blocking, or silent leak.
14. Is there exactly one producer per SPSC queue? (builder thread *and* `setStateInformation` path
    pushing?) → corrupted FIFO indices.
15. Is the builder thread stopped/joined before the engine it writes into is destroyed, and never
    joined from the audio thread? → use-after-free at plugin unload; audio-thread block.
16. Are atomics used for every flag read on one thread and written on another (`dirty`, `prepared`,
    `latencySamples`)? → data race (TSan), stale reads.
17. Does the crossfade state machine handle "new IR arrives during a fade" and "IR arrives before
    `prepare`"? → double-fade, null deref.

Lifecycle, latency, state
18. Is `setLatencySamples` called only from `prepareToPlay`/initialisation and only when the value
    changes; never from `processBlock` in realtime? → host graph rebuild mid-playback; Studio One/Wavelab quirks.
19. Does `getLatencySamples()` equal the measured impulse offset (P + pre-roll) at every sample rate
    and block size pluginval uses (44.1/48/96 kHz; 64-1024)? → PDC misalignment.
20. Does `getTailLengthSeconds()` return the IR length (not 0)? → bounces truncated; VST3 `kNoTail`.
21. Does `processBlockBypassed` either delay the dry signal by the reported latency or document the
    pre-echo? → bypass toggles shift timing.
22. Can `setStateInformation` arrive before `prepareToPlay`, after it, twice, from a non-message
    thread, with garbage bytes, with a future `pluginStateVersion`? → crash/deadlock in Logic/Reaper
    /Pro Tools; corrupt-state fuzz; Phase 07 fixtures.
23. Does `setStateInformation`'s synchronous IR rebuild finish well within pluginval's 30 s test
    timeout for the largest room and the 96 kHz rate? → timeouts at level 6/7.
24. Does `prepareToPlay` tolerate being called again without `releaseResources` and with a new
    sample rate? → pluginval level 6 "Non-releasing audio processing".
25. Does `releaseResources` leave the object in a state where `processBlock` (some hosts still call
    it) is harmless? → null derefs after stop.
26. Does `ValueTree`/JSON/XML parsing check `isValid()`/`Result` and fall back to the default scene,
    given JUCE 8.0.17/9.0.5 now return invalid trees for deep nesting? → silent empty scene.

Parameters
27. Are all parameter ID strings, ranges, skews, step counts and `versionHint`s unchanged versus
    `tests/state/parameter_ids_v1.json`? → AU/VST3 numeric IDs are hashes of the string; automation
    and saved projects orphaned.
28. Do newly added parameters carry a strictly higher `versionHint` than every existing one?
    → Logic/GarageBand AU automation mapped to the wrong parameter.
29. Does any `NormalisableRange` use lambdas *and* a skew (skew is ignored), or `skew <= 0`,
    `interval < 0`, `end <= start`? → assertion / wrong mapping.
30. Does the APVTS listener only set an atomic flag or push to a queue (no rebuild, allocation or
    lock), and does it use `newValue` rather than re-reading the parameter? → audio-thread work in a
    listener; stale value per JUCE docs.
31. Are `beginChangeGesture/endChangeGesture` paired, called from the message thread only, and never
    from the audio thread or a listener? → VST3 `beginEdit` must be UI-thread; host automation
    recording breaks.
32. Do choice/bool parameters restore to exact step values? → pluginval 2.0 level-8 discrete
    restoration test.

Identity, build, determinism
33. Did `PLUGIN_CODE`, `PLUGIN_MANUFACTURER_CODE`, `PRODUCT_NAME`, `BUNDLE_ID`, `AU_MAIN_TYPE`,
    `JUCE_VST3_CAN_REPLACE_VST2`, `JUCE_FORCE_USE_LEGACY_PARAM_IDS` change? → every saved project
    shows "plugin missing"; test must assert the codes.
34. Is `PLUGIN_CODE` set explicitly (JUCE's default is random per configure) and does it contain
    exactly one upper-case letter, with the manufacturer code having at least one? → auval failure,
    new identity each build.
35. Any `-ffast-math`, `-Ofast`, `/fp:fast`, `-ffinite-math-only`, `-funsafe-math-optimizations` in a
    CMake target? → NaN checks folded away, reassociation, crtfastmath FTZ leak into the host process.
36. Is `-ffp-contract=off` (and MSVC's default no-contract) applied to `src/sim` and PFFFT if the
    goldens are compared bitwise across architectures; otherwise are goldens tolerance-based?
    → arm64 FMA vs x86 non-FMA mismatch.
37. Any `std::uniform_*_distribution`/`std::normal_distribution` in seeded, determinism-critical
    code? → sequences differ per standard library; not real-time safe.
38. Does the offline path avoid runtime SIMD dispatch differences (or are the determinism tests
    scoped to "same platform")? → spurious golden failures across runners.
39. Does the change bump `pluginStateVersion`/`contractVersion` and add a fixture when the serialised
    form changed? → old projects fail to load.
40. Does `supportsDoublePrecisionProcessing()` remain false, or is the double `processBlock` fully
    implemented and tested? → VST3 host selects kSample64 and gets silence/garbage.

---

## Appendix: source list with access dates (all 2026-11-04)

- JUCE sources, tags and docs: clone of https://github.com/juce-framework/JUCE (master d60b7a7 =
  9.0.5; tags 9.0.0, 8.0.15, 8.0.16-security, 8.0.17-security fetched); files cited:
  `modules/juce_audio_basics/buffers/juce_FloatVectorOperations.{h,cpp}`,
  `modules/juce_audio_plugin_client/juce_audio_plugin_client_VST3.cpp`,
  `modules/juce_audio_plugin_client/juce_audio_plugin_client_AU_1.mm`,
  `modules/juce_audio_plugin_client/juce_audio_plugin_client.h`,
  `modules/juce_audio_plugin_client/detail/juce_CreatePluginFilter.h`,
  `modules/juce_audio_processors_headless/processors/juce_AudioProcessor.{h,cpp}`,
  `modules/juce_audio_processors_headless/processors/juce_AudioProcessorParameter.h`,
  `modules/juce_audio_processors_headless/utilities/juce_AudioProcessorParameterWithID.h`,
  `modules/juce_audio_processors_headless/utilities/juce_VST3Interface.h`,
  `modules/juce_audio_processors_headless/format_types/juce_VST3Common.h`,
  `modules/juce_audio_processors/utilities/juce_AudioProcessorValueTreeState.h`,
  `modules/juce_core/maths/juce_NormalisableRange.h`, `docs/CMake API.md`, `BREAKING_CHANGES.md`.
- docs.juce.com: classAudioProcessor.html, classAudioProcessorValueTreeState.html,
  classParameterID.html, classAbstractFifo.html, classScopedNoDenormals.html, classThread.html.
- pluginval: clone of https://github.com/Tracktion/pluginval (develop 286684f, 2026-10-15; tags
  v1.0.4, v2.0.0-beta1, v2.0.0-beta3); `README.md`, `docs/*.md`, `source/PluginTests.h`,
  `source/RTCheck.h`, `source/tests/*.cpp`; release pages for v1.0.4 and v2.0.0-beta3.
- Steinberg VST3: Plugin Format page; IAudioProcessor, IComponentHandler, namespace Steinberg::Vst
  (RestartFlags, SymbolicSampleSizes) at steinbergmedia.github.io/vst3_doc.
- Apple: TN2204 (archived), kAudioUnitProperty_Latency.md, kAudioUnitProperty_TailTime.md.
- Compilers: GCC Optimize-Options; Clang UsersManual and RealtimeSanitizer; MSVC /fp page.
- Standard: eel.is/c++draft (atomics.order, util.smartptr.atomic.shared, rand.predef, rand.dist.uni.real).
- Intel oneAPI "Set the FTZ and DAZ flags"; Intel SDM Vol.1 mirror (xem.github.io) §11.6.
- Arm FPCR register description mirror (df.lth.se/~getz); Arm community forum answer on A64 NEON FZ;
  FreeBSD review D48442.
- Bencina article via reader mirror (origin 503 today); Doumler CppCon 2021 PDF, CppCon sched page,
  ACCU 2022 session page; JUCE forum threads 26311, 61490, 28834, 28249, 24425, 36687, 15188, 36061.
- PRNGs: pcg-random.org, prng.di.unimi.it.
