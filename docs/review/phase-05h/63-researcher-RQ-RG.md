# 63 — Researcher: RQ-RG-1/2/3 (hosted-runner timing gates; the same-instance control; small-sample bounds) for file 56 / decision RG-1

phase-05h (session 2). Verbatim researcher output (the orchestrator saved it). It landed after the decider's DECISION RG-1 (file 64), which stated the premise; the interrogator reads both.

# Researcher dossier — RQ-RG-1/2/3 (file 59 §5; matter file 56)

All sources accessed 2026-11-11; "read" = I read the text (PDF or page) myself. Extends file 5 F9–F12/F18; nothing repeated from memory.

## 1. Served
- RQ-RG-1 → K5 (does documentation/literature make (a)/(c) structurally unsound?).
- RQ-RG-2 → K4/K5 (is a single-run same-instance ratio a recognised detector?).
- RQ-RG-3 → K3/K4 (k per OS with a stated false-red rate).

## 2. Findings

**G1 | RQ-RG-1, GitHub docs** | No sentence on performance consistency, variability or tenancy on any of the three pages. What they state: "each GitHub-hosted runner is a new virtual machine (VM) hosted by GitHub"; "Single-CPU runners are hosted in a container on a shared VM"; eligible Linux jobs "can run on either Amazon Web Services (AWS) or Microsoft Azure", "automatically scheduled across available cloud providers"; macOS "in Azure data centers". Larger-runners page: queue-time text only. | GitHub Docs: About GitHub-hosted runners, https://docs.github.com/en/actions/using-github-hosted-runners/using-github-hosted-runners/about-github-hosted-runners ; GitHub-hosted runners reference, https://docs.github.com/en/actions/reference/runners/github-hosted-runners ; Larger runners reference, https://docs.github.com/en/actions/reference/runners/larger-runners | read | high | **Nothing documentary drops (a)/(c) at step 1**; the only evidence of x64 spread is the repo's 13 rows. (Multi-cloud Linux scheduling is a new, undocumented-magnitude source of between-run heterogeneity.)

**G2 | RQ-RG-1, literature** | No peer-reviewed source states that absolute wall-clock gates are irreproducible on hosted x64 runners. Closest: Yang, Reichelt, Ingo, Hasselbring (2025), "Detection of Performance Changes in MooBench Results Using Nyrkiö on GitHub Actions", arXiv:2510.11310 (**preprint**; GitHub-hosted ubuntu-22.04/24.04 4-vCPU + four self-hosted 4-vCPU/8 GiB VMs; MooBench): "performance is not only impacted by software changes, but also by the VMs" (§1); an apparent regression appeared "although the involved commits did not contain any changes to the software" (§1; cause: runner image/kernel change, §3.1–3.3). Linux only, Linux-image effect, not timing noise per se. Bulej, Horký, Tůma, Farquet, Prokopec (2020), "Duet Benchmarking: Improving Measurement Accuracy in the Cloud", ICPE '20, pp. 100–107, DOI 10.1145/3358960.3379132 (**peer-reviewed**, generic cloud, not GitHub): cloud VMs "suffer from performance interference of neighbor workloads, which the virtualization technology cannot entirely eliminate" (§2); Fig. 1: min–max range of a benchmark's mean time ≈16 % on idle bare metal vs ≈150 % on a public-cloud VM. | https://arxiv.org/html/2510.11310 ; https://research.spec.org/icpe_proceedings/2020/proceedings/p100.pdf | read | medium (preprint) / high | Supports "shared VMs vary" generically; **no Windows x64 or GitHub-specific peer-reviewed statement exists** (searched arXiv/ACM/ICPE/EMSE phrasings; vendor blogs only, not cited).

**G3 | RQ-RG-2, definitions** | Laaber, Scheuner, Leitner (2019), EMSE 24(4):2469–2508, DOI 10.1007/s10664-019-09681-1. §3.3 p.10: *instance* = one cloud VM (50 per type); *trial* = one execution of the benchmark set on that instance, 10 per instance in randomised order (RMIT); *iteration* = 50 per benchmark per trial, each one data point (mean time over ~1 s of invocations). §5.2.2 p.23: trial-based sampling = test and control on the *same* instances with disjoint trials; "can also be seen as a paired statistical test". | https://research.chalmers.se/publication/511491/file/511491_Fulltext.pdf | read | high | The project's gate = 1 instance, 1 trial each of two workloads, 14 iterations.

**G4 | RQ-RG-2, the result, exact** | p.4: "Employing a strategy where test and control experiments are executed on the same instances, all benchmark-environment combinations find slowdowns with high confidence when utilizing ≥ 10 instances." §5.4.3 box p.35: "With trial-based sampling, already 5 instances are sufficient to find similar slowdowns". **Single instance (5 trials):** 142/190 (75 %, Wilcoxon) and 117/190 (62 %, CI test) configurations cannot detect any slowdown; only "34 (17%; Wilcoxon) and 43 (22%; CI)" detect ≤10 % (p.34). A/A false positives, Table 6 p.24 (bleve-3): 1 instance × 1 trial, same-instance: 26–67 %; 1 × 5 trials: 2–13 %; 5 × 5 trials: <5 % in 185/190 and 189/190 configs (p.26). | same, pp. 4, 24–26, 34–35 | read | high; **conditions differ** (Java/Go microbenchmarks, 2-vCPU x64 IaaS, 2017; hypothesis tests on two versions of one workload, not a ratio of two workloads) | The paper **does not** support a single paired measurement as a reliable detector; it needs ≥5 instances × 5 trials × 50 iterations. The same-instance *design* is endorsed; the single-run *sample size* is in its worst cell.

**G5 | RQ-RG-2, replication** | No direct replication found. Predecessor confirmed by Laaber (p.35 "re-confirm"): Abedi & Brecht (2017), "Conducting Repeatable Experiments in Highly Variable Cloud Computing Environments", ICPE '17, p.287, DOI 10.1145/3030207.3030229 (EC2 traces; naive methods "falsely report that the performance of two identical systems differ by 38%" at 95 % confidence; RMIT fixes it). Extension: Duet (G2): both workloads run *concurrently* in one VM, one vCPU each, barrier-synchronised, so interference "impacts both workloads simultaneously" (§3); accuracy ×2.3–12.5 (ScalaBench/DaCapo), ×23.8–82.4 (SPEC CPU 2017). | https://research.spec.org/icpe_proceedings/2017/proceedings/p287.pdf ; p100.pdf above | read | high | Sequential same-run pairing (project) is weaker than Duet's concurrent pairing; both are peer-reviewed same-machine designs.

**G6 | RQ-RG-3, nonparametric bound** | US EPA (2009), *Statistical Analysis of Groundwater Monitoring Data at RCRA Facilities: Unified Guidance*, Part III ch. 18 §18.3.1 pp. 18-17–18-18: with the jth order statistic as limit, confidence for one future value = j/(n+1); maximum → **n/(n+1)**; m future values all ≤ max → **n/(n+m)** (Gibbons 1991a); eq. [18.11] general. Assumes iid from one continuous distribution (p.18-17). p.18-6: a limit can be built from "as few as three observations" but gives an "unacceptably large" limit with "very limited statistical power"; p.18-4 recommends ≥8. | https://archive.epa.gov/epawaste/hazard/web/pdf/unified-guid-3.pdf | read | high (source); n=4–5 is below its own recommendation | **Derived:** Linux bound = 3.24 (k = 3.24/3.05 = 1.062), false-red per run 1/5 = 20 %; Windows 3.08 (k 1.088), 1/6 = 16.7 %. All of next 10 runs pass: 4/14 = 29 % (Linux), 5/15 = 33 % (Windows).

**G7 | RQ-RG-3, t-based bound** | EPA eq. [18.3] p.18-9: PL = x̄ + t_{1−α/m, n−1} · s · √(1+1/n), normal iid assumed (p.18-4), α/m for m future comparisons. t quantiles (NIST/SEMATECH e-Handbook §1.3.6.7.2): df 3: 1.638/2.353/4.541; df 4: 1.533/2.132/3.747 (0.90/0.95/0.99). | https://www.itl.nist.gov/div898/handbook/eda/section3/eda3672.htm | read | high | **My arithmetic:** Linux x̄ 3.05, s 0.162, √1.25 = 1.118 → 90 %: 3.35 (k 1.097); 95 %: 3.48 (k 1.140); 99 %: 3.87 (k 1.27). Windows x̄ 2.83, s 0.171, √1.2 = 1.095 → 90 %: 3.12 (k 1.101); 95 %: 3.23 (k 1.141); 99 %: 3.53 (k 1.25). So **k = 1.10 ≈ a 90 % one-sided per-run bound on both OSes (≈10 % false red per run); 1.14 ≈ 95 %; ≈1.25 ≈ 99 % (or 95 % jointly over 10 runs)**. Normality is untestable at n = 4–5; the iid premise (runs across days, multi-cloud Linux) is unverified.

## 3. Not found
- Any GitHub statement on runner performance consistency or host tenancy (docs, 3 pages; changelog not re-read).
- A peer-reviewed Windows-x64 or macOS hosted-runner variance figure (F12 stands).
- A direct replication of Laaber 2019.

## 4. Conflicts
None between primaries. Laaber's abstract-level "≥10 instances" vs §5.4.3 "5 instances" are both the paper's (different criteria); single-instance figures (G4) qualify both.

## 5. Claims screened
- Decider file 59 L29: means 3.05/2.83, max/mean 1.062/1.088 — **confirmed** (my recomputation).
- File 56 "±6 %/±8 %" — **confirmed** (half-range/mean 6.4 %/7.7 %).
- K5 / file 5 F10 "same-instance control detects slowdowns (≥10 instances)" — **confirmed as quoted, under-informed as applied**: single instance detects ≤10 % slowdowns in 17–22 % of configurations (G4).
- Decider "k must come from the observed spread" — the literature (G6–G7) provides the methods; n = 4–5 is below EPA's own ≥8.

## 6. Corpus candidates
Laaber 2019 (already listed); Abedi & Brecht 2017; Bulej et al. 2020; EPA Unified Guidance 2009 ch. 18; NIST e-Handbook §1.3.6.7.2 and §7.2.6.4.

## 7. Readiness
| K | status |
|---|---|
| K3 | known; **under-informed stays** (n = 4–5; macOS row approximate) |
| K4 | **now informed**: two citable methods with false-red rates (G6, G7); 1.10 is statable only as ≈90 %/run |
| K5 | **ill-informed risk confirmed**: no documentary or peer-reviewed x64/GitHub statement; Laaber endorses the design, not the n = 1 sample |

**READY** for the register-form decision on K3–K5 as qualified, with these caveats on record: (a)/(c) cannot be dropped by documentation; (b)/(f)'s single-run ratio is a weak detector by Laaber's own numbers; every k above rests on 4–5 iid samples.
