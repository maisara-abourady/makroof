# Phase 06b — researcher dossier for D1 and D3 (2026-11-07; web sources accessed 2026-11-07)

Verdict: **D1 NOT READY, D3 NOT READY** (perceptual threshold separating 6.0 ms from 11.3 ms, and the largest
legitimate host level / a clamp-vs-zero convention, have no retrievable source). Established facts below.

| id | decision | finding | reference | status |
|---|---|---|---|---|
| F1 | D1 | 10 ms upper bound for a computer instrument's reaction to a gesture, 1 ms jitter bound; a design criterion, not an experiment; gesture instruments, not monitoring | Wessel & Wright (2001), NIME-01 pp. 11–14, arXiv:2010.01570, p. NIME01-12 | read (conditions differ) |
| F2 | D1 | latency JND (key press → tone, headphones, n = 34): 48.8 ms (SD 33) at 0 ms base, 27.1 ms at 64 ms, 77.1 ms at 512 ms; lower for musically sophisticated listeners | Schmid et al. (2024), AM '24, pp. 325–331, doi:10.1145/3678299.3678331 | read (difference threshold, synthetic tone) |
| F3 | D1 | Lester & Boley: wedges tolerate more than in-ears; accepted latency 1.4–42 ms by instrument | Lester & Boley (2007) AES Conv. 123, paper 7198, reported in Schmid et al. §2.2 | unverified (primary paywalled) |
| F4 | D1 | per-instrument values (vocal in-ear ≤ 6.5 ms "fair", sax ≤ 3 ms, 11.5 ms practice) | patent FI126465B citing Lester & Boley | unverified — do not rely |
| F5 | D1 | percussionists: 0 ms rated over 10 ± 3 and 20 ms; 10 ms constant not significantly different from 0 | Jack et al. (2018), Music Perception 36(1), doi:10.1525/mp.2018.36.1.109 | unverified (abstract) |
| F6 | D1 | 50 ms total delay acceptable for acoustic VR | Vorländer, Auralization, Ch. 15 (corpus) | read (conditions differ) |
| F7 | D1 | VST3: getLatencySamples = group delay; "for player live recording this latency should be zero or small"; changing latency needs restartComponent(kLatencyChanged), may interrupt playback | Steinberg VST 3 IAudioProcessor reference | read |
| F8 | D1 | AU latency = processing delay (e.g. FFTs), not effect delay; variable latency not useful to hosts | Apple, AUAudioUnit.latency | read |
| F9 | D1 | Ableton Live 12: PDC keeps tracks in sync; "Reduced Latency When Monitoring" bypasses compensation for input-monitored tracks | Ableton Reference Manual v12 §23.3 | read |
| F10 | D1 | Logic Pro: plugins add to input-monitoring latency; Low Latency Mode bypasses plugins above a user limit while recording | Apple Support 105040 | read |
| F11 | D1 | sequencers apply automatic PDC; buffer latency matters in recording, less in mixdown | Izhaki, Mixing Audio, Ch. 11 (corpus) | read |
| F12 | D1 | Cubase/Nuendo "Constrain Delay Compensation" | Steinberg help | unverified |
| F13 | D1 | Apple Space Designer (convolution reverb): 128 samples processing latency | Logic Pro Effects 10.2 help, "Space Designer global parameters" | read (older guide) |
| F14 | D1 | Reverberate: zero or selectable latency up to 8192; Waves IR: no reported latency | reviews / forum | unverified |
| F15 | D1 | zero-delay hybrid convolution exists | Gardner (1995) JAES 43(3) 127–136 | unverified (index record) |
| F16 | D3 | binary32 FLT_MAX = 3.40282347e38 | ISO/IEC WG14 N1570 §5.2.4.2.2 EXAMPLE 2 | read (C11 draft) |
| F17 | D3 | in a float engine 1.0 = 0 dB; 2.0, 4.0, 808.0 "and much larger" fine; ≈ 764 dB boost without clipping; "some plugins … trim signals above 1.0" | Izhaki Ch. 11 "What is in it for us?" (corpus) | read |
| F18 | D3 | headroom above 1.0 = 20·log10(FLT_MAX) = 770.6 dB; "+1500 dB" is the FLT_MIN…FLT_MAX span (1529 dB) | arithmetic on F16 | derived |
| F19 | D3 | pluginval v1.0.4 feeds noise in [−1, 1) only and expects no NaN/Inf/subnormal output; no test feeds huge input | Tracktion pluginval v1.0.4 Source/TestUtilities.h | read |
| F20 | D3 | JUCE template: ScopedNoDenormals only; no clamp/NaN sanitising convention | JUCE plugin template; ScopedNoDenormals docs | read |

Not found: a readable own-voice / instrument monitoring threshold (Lester & Boley paywalled); a test of 6 vs
11 ms absolute plugin latency with music; vendor-documented latencies of spatial plugins (Altiverb,
dearVR, …); the largest level a float host legitimately passes between plugins; a documented clamp-vs-zero
convention for huge finite input. The decider must argue these from analysis and the PRD, saying so.

Corpus candidates (Maisara to decide, licence permitting): Schmid et al. 2024 (CC-BY 4.0), Lester & Boley
2007, Jack et al. 2018, Gardner 1995, Wessel & Wright 2001.
