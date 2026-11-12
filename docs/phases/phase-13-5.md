# Phase 13-5 — Release, licences, identity, beta

Size: **M** (remainder, if needed: `13-5b`, if notarization fights back) · Depends on: 13-1 to 13-4; and the phase-13 header in full: 00–12, including 05b, 05h, 07c (`done`, or the versioning fallback of scope 13 recorded), 05d, 05e and 05f (05f `done` or Maisara's recorded acceptance of the two-room label; 05d `done` or `blocked (reason)`, decider report 15, accepted by Maisara, 2026-11-05; with 05c, if it exists, `blocked` only on Maisara's recorded decision) · Part of: [phase-13](phase-13.md) · Lead subject matter: Seat 5 (Deadline keeper), "CI gates"; "framework and plugin-format choice" (hand-offs to Seat 7: JUCE tier, signing cost, AX8 identity, public compatibility wording) · Read first: [`phase-13.md`](phase-13.md) (umbrella), `CLAUDE.md`, `docs/BUILD_PLAN.md` (all of §2–§3), PRD NFR-2, NFR-4, NFR-6

## Raise with Maisara (she does not track these herself)

The session raises each item in its **first message** and again before the beta decision. (phase-13 R0; in this
split the first message is 13-1's and "again before the beta decision" is 13-5's: D-PS4 instruction 5. This
sub-phase raises all five before the beta decision, L5 below.)

1. **Commissioning decision (BUILD_PLAN §3 F2).** Check BUILD_PLAN §6 for Maisara's answer, recorded by
   phase 05d. If it is missing or "deferred", put the question to her again with the Phase 05/05d
   numbers before the beta decision. (phase-13 R1)
2. **DELTA panel report.** Check whether `docs/phases/phase-05d.md`'s PR recorded an answer. If not,
   remind her that the request (`docs/review/drafts/delta-report-request.md`) is still outstanding, and
   keep the Arni provenance label as is in the beta wording. (phase-13 R2)
3. **Load time with 8 instances (AX38 (iv), phase 05b).** If the recorded time until the last of 8
   instances is audible at project load at 100 m exceeds 10 s, it goes to Maisara before the first
   release. (phase-13 R3)
4. **Phase 07c not landed (conditional).** If the asynchronous diffuse solve (phase-07c) would land after
   the first release without the estimator parameters versioned in saved state, Seat 7's condition fails
   and the item returns to Maisara (decider file 47 §4, strongest objection). (phase-13 R4)
5. **Release machines for the AX38 4c strict re-check (RG-1).** Release machines bought once, no standing
   runner (Seat 7, file 60 round 1: larger hosted runners ≈ €100–130/month, a standing cost before any
   revenue, and the macOS larger runner still a shared VM; decider files 64 item 7 and 66 §7: a person's
   purchase); on them the strict 30 s and the 1.10 growth bound are asserted on all three OSes (AX41) and the
   register entries close or the absolute CHECK returns on named hardware. (phase-13 R5, added 2026-11-11 by DECISION RG-1)

## Goal

This sub-phase's share of the umbrella goal ("Turn the vertical slice into a **private-beta build**"): install
cleanly on macOS and Windows, and get every licence in order; then the beta decision. (Licensing and
subscriptions are deliberately not in v1; see BUILD_PLAN F9 and B1.)

## Assumptions in force

All of the umbrella's (phase-13 assumptions, shared: AQ10, AX5).

## Scope

1. **Release packaging** (`.github/workflows/release.yml`, on tags `v*`): (phase-13 scope 4)
   - macOS: codesign with Developer ID Application (hardened runtime), build a signed `.pkg` installer
     (VST3 + AU), **notarize** with `notarytool`, and staple. Secrets: `APPLE_DEV_ID_CERT_P12`,
     `APPLE_DEV_ID_CERT_PASSWORD`, `APPLE_NOTARY_KEY_ID`, `APPLE_NOTARY_ISSUER`,
     `APPLE_NOTARY_KEY_P8`, set by Maisara in GitHub repository secrets. The workflow skips signing with a
     clear message if they're absent.
   - Windows: Inno Setup installer for the VST3. Code signing is optional (secret-gated); document the
     SmartScreen warning if unsigned.
   - Version number from the git tag, embedded in the plugin (`JucePlugin_VersionString`) and shown in the UI.
2. **Licences and attribution:** `docs/THIRD_PARTY.md` complete (JUCE tier and terms, PFFFT,
   nlohmann/json, dr_wav, Catch2 (test only), HRTF dataset, material sources, BRAS, Arni and dEchorate (validation only,
   not shipped)). The installer includes `THIRD_PARTY_NOTICES.txt`. **Confirm the JUCE licence tier
   that will apply at commercial launch**, and the splash-screen and revenue-cap rules for that tier,
   recording it in BUILD_PLAN §6. (phase-13 scope 5)
3. **DAW compatibility matrix:** `docs/compat/v1.md` table: rows = DAW + OS + format (Logic/AU, Ableton
   macOS VST3, Reaper macOS VST3, Windows DAW(s) VST3); columns = load, play, automate, editor drag-record,
   offline bounce, reopen project, sample-rate change, 10 instances. Maisara fills it in. The public
   compatibility notes state the Bitwig sandbox gap (AX38 (i)) until scope 3 has measured it. **The
   matrix also receives the per-host trace results of phase-07c §5 condition 11** (D-H3 (e), AX38 (i)
   half (2): the thread that serves `reset()`, `setNonRealtime` and freeze / offline render, per host and
   situation, from the `SPATIAL_HOST_TRACE` build run as a person's action); they are evidence for the
   compatibility notes, never a per-host code path (NFR-8). Until measured, the notes carry AX38 (i)'s
   interim sentence (no host named, no stall figure as a product promise, not in launch copy). (phase-13 scope 6;
   "scope 3" is phase-13 scope 3, in 13-4)
   The condition 11 results also feed AX49's reversal (a hang, not-responding state or time limit at ≤ 8
   instances sends AX49 back to the board, 07d's candidates first). (phase-07c-1 decision loop, 2026-11-12)
4. Placeholder identity (`AX8`: company name, plugin/manufacturer codes, bundle ID) confirmed or changed
   **before** the first beta, since changing it later breaks users' projects. (phase-13 scope 7)
5. **Saved state and wording (AX48, AX49; phase-07c-1 decision loop, 2026-11-12; decider file
   `docs/review/phase-07c-1/12-decider-decision-r3.md` §8):**
   - The board decides AX48's engine-mismatch policy, including whether a build id joins the key, before the
     first post-release build that changes E_prec or E_model.
   - After release, a fingerprint failure blocks the build until that decision exists; bumping the id alone
     does not clear it (Seat 7).
   - Compatibility note: a v1 build rejects v2 state.
   - Wording: never "opens instantly"; no cross-machine bit-identity claim.

## Out of scope

Licensing/trial (B1), auto-update, anything listed in BUILD_PLAN §5. (phase-13 out of scope, shared)
Every item the umbrella's table assigns to 13-1 … 13-4.

## Acceptance criteria — automated

- [ ] Full CI matrix green; nightly validation green (no regression). (phase-13 C1, umbrella shared: for this
      sub-phase's PR)
- [ ] Release workflow on a test tag produces: notarized and stapled pkg (`spctl -a -vv -t install` says
      accepted), Windows installer, notices file. (If secrets are missing, the workflow produces unsigned
      builds and the phase status notes say `signing pending secrets`.) (phase-13 C5)

## Listening / manual checklist (Maisara)

- [ ] Install from the macOS pkg on a clean-ish Mac: no Gatekeeper warnings; Logic finds the AU. (phase-13 L1)
- [ ] Install on Windows: the DAW finds the VST3. (phase-13 L2)
- [ ] Fill in `docs/compat/v1.md` completely. (phase-13 L3)
- [ ] A final listening pass through all presets in both modes on the Adam monitors and headphones,
      plus a real session with 10 instances on stems. Note CPU in your DAW's meter. (phase-13 L4)
- [ ] Decide: is this build good enough to give to 3–5 beta users? The decision lists 'AQ9 met in x/y'
      and every recorded known deficit (AX16, AX21, AX22, AQ10 misses) (decider report 8, accepted by Maisara, 2026-11-05). It also
      states (BUILD_PLAN §3 F2; decider report 15, accepted by Maisara, 2026-11-05): "Second measured
      source: Arni (202 m³) and dEchorate (86 m³), CC BY 4.0, used in phase 05d. No open dataset has
      measured α for all surfaces; all measured comparisons (BRAS, Arni, dEchorate) are evidence, not
      validation of NFR-1. Input-matched distribution test: [result]. Coverage: domestic small room (one
      treated empty cuboid, dEchorate 86 m³), mid rooms 145 m³ (BRAS CR2) and 202 m³ (Arni), halls
      2 350/8 650 m³ (BRAS); none for outdoor, cars or furnished living rooms." The coverage sentence is
      corrected by decider report 16 (`docs/review/phase-04-consult/18-decider-05d-choices.md`), accepted
      by Maisara, 2026-11-05. Your decision goes in BUILD_PLAN §6. (phase-13 L5)

## Contractor review focus

the release pipeline's secret handling, and licence compliance. (phase-13 contractor review focus, clauses 3 and 4;
clause 1 in 13-1, clause 2 in 13-4)

## Risks

The umbrella's risks (phase-13 K1–K3) apply; they are read by 13-1 (D-PS4 instruction 4).

## Notes from the split

- Remainder (G3): `13-5b` (notarization). (D-PS4 Q1)
- Raise items: all four carried by 13-1 (first message) and by 13-5 ("before the beta decision"). (Five since R5, 2026-11-11.) (D-PS4 instruction
  5; final corrections list item 3)
- The installer packages both macOS slices (13-3); the beta decision lists every recorded deficit, including AQ10
  misses from 13-1 and 13-2 and the robustness results from 13-4; the compatibility notes on Bitwig use 13-4's
  measurement. (map-13 §2, order rationale)

## Definition of done

All automated criteria green (or signing explicitly pending secrets); compat matrix filled in; the v1 beta decision
is recorded. (phase-13 definition of done, clause 1 (shared: this sub-phase's criteria, with its signing clause),
clauses 2 and 4) Status row 13-5 `done` (CLAUDE.md rule 6; status row 13 stays on the umbrella). CLAUDE.md rules
apply: one sub-phase per session; if it can't be finished in two sessions, split the remainder into
`phase-13-5b.md`.
