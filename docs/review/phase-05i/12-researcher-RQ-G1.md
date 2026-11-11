# 12 — Researcher: RQ-G1 (core and RAM base rates of music-production machines) for D-G1

Phase 05i, 2026-11-11. Saved verbatim by the orchestrator. Every source accessed 2026-11-11. **Read** = fetched by the researcher during this task. **Prior dossier** = a finding from `docs/review/phase-05b2/4-researcher-T5-T4.md` not re-read here.

## 1. Decision served and question
D-G1, K-g7 / RQ-G1: the distribution of physical core counts (performance cores where relevant) and installed RAM among music-production computers, 2023–2026, with method and sample. Why it matters (file 11): if most machines have ≤ 4 performance cores, narrowing the gate buys little following for N ≥ 4; if ≥ 8 cores are typical, the benefit to NFR-3 is larger. No seat claim was routed for this question.

## 2. Findings

**G1. No producer-population survey of cores or RAM, 2023–2026.** No published survey or vendor statistic with a stated method reports CPU core counts or installed RAM for music-production computers in 2023–2026. Avanzini et al. 2025, the only academic DAW-user survey in the window (fielded Dec 2023–Jan 2024, N = 613, mostly Italian), asked no hardware questions. Ref: F. Avanzini et al., "A Study on the Adoption and Usage of Digital Audio Workstations", Proc. SMC 2025, pp. 136–143, https://avanzini.di.unimi.it/downloads/publications/avanzini_smc25.pdf; results https://www.lim.di.unimi.it/dawsurvey/results/2023/ (Table 2, per the prior dossier F9; the PDF re-fetch returned an undecodable stream). Confidence M that no such source exists. Changes: K-g7 cannot be filled from a producer population; every figure below is a proxy.

**G2. Steam survey, Physical CPUs, all platforms, October 2026 (general population).** 2 cores 2.84 %; 4 cores 12.36 %; 6 cores 27.29 %; 8 cores 28.68 %; 10 cores 7.48 %; 12 cores 4.97 %; 14 cores 4.74 %; 16 cores 5.86 %; 20 cores 2.16 %; 24 cores 2.91 %; every other row ≤ 0.30 %. Platform mix Windows 93.70 %, OSX 2.35 %, Linux 3.95 %. Method: monthly, participation "optional, and anonymous"; N not stated. Ref: Valve, Steam Hardware & Software Survey, https://store.steampowered.com/hwsurvey/ ("Physical CPUs", "OS Version"). Read. Confidence H for the gaming population; ill-informed for producers (wrong population; macOS almost absent). Changes: among gamers' PCs, 6–8 cores is the mode; nothing ties this to producers.

**G3. Steam, Physical CPUs, Windows only, October 2026.** 1 core 0.02 %; 2 cores 2.75 %; 3 cores 0.09 %; 4 cores 11.76 %; 5 cores 0.20 %; 6 cores 28.12 %; 7 cores 0.01 %; 8 cores 28.63 %; 10 cores 6.97 %; 12 cores 4.93 %; 14 cores 4.89 %; 16 cores 6.01 %; 18 cores 0.26 %; 20 cores 2.27 %; 24 cores 3.05 %; 22, 32 and 36 cores 0.01 % each. Derived: ≤ 4 cores 14.62 %; 6 cores 28.12 %; ≥ 8 cores 57.04 %; rows sum 99.99 %. Not stated by Valve: whether "physical CPUs" counts Intel hybrid E-cores with P-cores (so not performance-core counts). Ref: https://store.steampowered.com/hwsurvey/cpus/ (Windows table). Read. Confidence H as stated; ill-informed for producers. Changes: a general-PC proxy for Windows: about 1 in 7 at ≤ 4 cores, a majority at ≥ 8 total cores.

**G4. Steam, Physical CPUs, macOS only, October 2026.** 2 cores 3.40 %; 4 cores 3.64 %; 6 cores 6.41 %; 8 cores 34.20 %; 10 cores 35.54 %; 11 cores 1.55 %; 12 cores 6.15 %; 14 cores 3.60 %; 15 cores 1.36 %; 16 cores 1.47 %; 18 cores 2.42 %; 20 or more ≤ 0.08 % each. Derived: ≤ 4 cores 7.04 %; 8 cores 34.20 %; ≥ 10 cores 52.34 %. Sample: OSX 2.35 % of the survey, N not stated. Ref: https://store.steampowered.com/hwsurvey/cpus/ (macOS table). Read. Confidence M (small subsample, gaming population, ill-informed for producers). Total cores, not performance cores (see G5).

**G5. Apple Silicon performance cores (vendor specification).** M1: "an 8-core CPU consisting of four high-performance cores and four high-efficiency cores". M4: "up-to-10-core CPU consisting of up to four performance cores and now six efficiency cores". Refs: Apple Newsroom, 10 Nov 2020, https://www.apple.com/newsroom/2020/11/apple-unleashes-m1/; Apple Newsroom, 7 May 2024, https://www.apple.com/newsroom/2024/05/apple-introduces-m4-chip/. Read. Confidence H. Changes: an 8- or 10-core Mac in G4 may have only 4 performance cores; which chips make up those rows was not checked, so the share of 4-P-core Macs is **not established** (the combined 8 + 10 share, 69.74 %, is only an upper-bound lead).

**G6. Steam, System RAM, all platforms, October 2026.** < 4 GB 0.02 %; 4 GB 1.35 %; 8 GB 7.52 %; 12 GB 2.45 %; 16 GB 41.42 %; 24 GB 2.31 %; 28 GB 0.53 %; 32 GB 37.06 %; 48 GB 1.19 %; 60 GB 0.99 %; 64 GB 3.94 %; > 64 GB 0.60 %; Other 0.64 %. Derived: ≤ 8 GB 8.89 %; ≥ 16 GB 88.04 %. Ref: https://store.steampowered.com/hwsurvey/ ("System RAM"). Read (matches prior dossier F8). Confidence H as stated; ill-informed for producers. Changes: a general-PC proxy: about 9 in 10 machines at ≥ 16 GB.

**G7. Mac base RAM since Oct 2024.** The M4 MacBook Pro starts at 16 GB, and the M2/M3 MacBook Air base doubled to 16 GB. Ref: Apple Newsroom, 30 Oct 2024, https://www.apple.com/newsroom/2024/10/new-macbook-pro-features-m4-family-of-chips-and-apple-intelligence/. Prior dossier F7, not re-read. Confidence H. A floor for new MacBooks only; nothing about the installed base.

**G8. Nugen Audio Holiday Survey, Dec 2018 (outside the window).** N = 3 174 Nugen followers, about 40 % not Nugen users; invited by email and social media with a $50 voucher incentive. RAM reported only as prose ("nearly half" / "nearly two thirds" with 8–16 GB; ambiguous which applies to which group); no 32–64 GB option; no core figures. Ref: M. Thornton, Production Expert, 18 Mar 2019, https://www.production-expert.com/production-expert-1/2019/3/14/check-out-the-results-of-a-survey-conducted-by-nugen-audio-to-better-understand-our-needs-it-makes-for-interesting-reading. Read (trade press reporting a vendor survey; primary report not retrieved). Confidence L (outdated, incentive-biased, no exact figures, capped question). The only producer-population RAM figure found; too old and vague for a 2023–2026 base rate.

**G9. Production Expert Apple Silicon survey (about Feb 2022, outside the window).** "Over 1400 pro audio users", macOS and Windows; 593 (56 %) had already upgraded to Apple Silicon; no core or RAM figures; method and dates not stated. Ref: https://www.production-expert.com/production-expert-1/apple-silicon-gets-a-big-thumbs-up-from-pro-audio-users. Read. Confidence L (denominator unclear: 593/1400 is 42 %, so presumably a subset). Suggests a large Apple Silicon share among pro-audio readers in 2022; with G5, points toward 4-P-core base chips being common among Mac users; not quantified.

## 3. Not found / unresolved
- **Producer core-count distribution, 2023–2026.** Searched "music producers survey CPU cores RAM", "DAW users hardware survey", "home studio survey RAM cores", "music creator survey 2025 hardware", "plugin users hardware telemetry core count", and Production Expert, KVR, MusicRadar, Sound On Sound, MIDiA and JUCE-forum leads: buyers' guides, forum threads and DAW-share surveys without hardware questions. Would settle it: a DAW or plugin vendor's published telemetry, or a reader survey with N, dates and a hardware question.
- **Producer RAM distribution, 2023–2026.** Same searches. One uncitable lead: a Gearspace forum poll, "How much RAM is in your studio computer? (POLL 2022)", 241 self-selected voters, closed in 2023 (a forum poll: not evidence). MIDiA's 2025 creator survey (n = 2 109, per the prior dossier) is paywalled; hardware content unknown.
- **Performance-core share.** Valve does not define "physical CPUs" for hybrid Intel or Apple parts; the macOS 8- and 10-core rows were not mapped to chips (Apple publishes no installed-base mix).
- **K-g5 (what narrowing buys).** Not a literature question; measurable only in-repo after a narrowing.

## 4. Conflicts between sources
Steam 4-core share: 12.36 % on the all-platform summary vs 11.76 % in the Windows-only table (same month, different platform mix). Core distribution by platform: the Mac subsample skews to 8–10 total cores and the Windows subsample to 6–8; total cores do not compare across platforms, because Apple's 8- and 10-core base chips have 4 performance cores (G5).

## 5. Seat claims screened
None routed. File 11's premise "≤ 4 performance cores vs ≥ 8 cores typical": **unverifiable for producers.** The general-PC proxy shows ≤ 4 total cores on about 15 % of Windows machines (G3), a majority at ≥ 8 total cores; on Macs many 8–10-core machines have 4 performance cores (G4, G5), share not established.

## 6. Corpus candidates
None (statistics pages and press releases, not acoustics literature).

## 7. Readiness for the decider (D-G1, K-g7 only)

| row | status | facts available |
|---|---|---|
| K-g7 cores, producers | **uninformed** (no producer source exists); proxy only, **ill-informed** (gaming population, total rather than performance cores) | G2, G3, G4, G5 |
| K-g7 RAM, producers | **uninformed** for 2023–2026 producers; proxy G6 **ill-informed**; the only producer figure (G8) from 2018, vague and outdated | G6, G7, G8 |

**Verdict for K-g7: NOT READY.** No published, method-stated base rate of cores or RAM for music-production machines in 2023–2026. General-population proxies only, marked as such: Windows about 15 % at ≤ 4 total cores and 57 % at ≥ 8; Mac 70 % at 8–10 total cores, some with only 4 performance cores in an unknown share; RAM about 88 % at ≥ 16 GB. K-g7 should be carried as a declared unknown, or replaced by a design that does not depend on it.
