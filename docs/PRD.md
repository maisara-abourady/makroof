# Spatial Scene VST — Product Requirements Document

Nov 4, 2026 · @Maisara

## Overview & vision

A commercial VST3/AU plugin that makes any track sound as if it were played in a 3D space the user designs. The user invests in building the scene; the plugin handles all spatial audio design.

- **The user's job:** envision a space (a club, a chapel, a mountainside, a living room), build or pick it visually, and place the listener and sound sources in it.
- **The plugin's job:** work out *what* that space does to sound and *how* to reproduce it, then render the result at the listener's position with the highest achievable accuracy.
- **Core principle:** the engine is generic. It derives the sound from the scene's geometry and materials alone and never depends on presets. Presets are editable starting scenes, not engine inputs.

The plugin has two logically separate parts joined by a defined contract: a **3D Module** (scene building and translation) and a **Simulator** (acoustic simulation and rendering). This PRD defines product requirements and the questions to be answered. Acoustic and psychoacoustic decisions belong to the dedicated Spatial Audio Expert project.

## Target users, problem & success metrics

The plugin is for producers and DJs who want to hear their track as it would sound in a specific imagined space, without having to understand spatial audio.

- **Problem:** today's reverbs and spatializers expose acoustic parameters. They make the user translate a mental image of a space into decay times and early reflections. This plugin reverses that: the user describes the space, and the plugin does the translation.
- **Primary users:** music producers and DJs on macOS and Windows, in any DAW.

| Metric | Year-one target |
| --- | --- |
| Paying subscribers | Under 500 |
| Price | $10–20 per month |
| Accuracy (quality gate, not a success metric) | Measured match against real impulse responses + listening tests |

Success for v1 is defined by paying subscribers and revenue.

## Key product decisions

These 20 decisions were settled in the discovery interview and are the baseline for the rest of this PRD.

| Area | Decision |
| --- | --- |
| Delivery | Own standalone plugin, VST3 + AU, any DAW (Ableton no longer a constraint) |
| Platforms | macOS + Windows |
| Scene detail | Full scene: shape, materials, objects, any environment (indoor or outdoor) |
| Scene creation | Built-in 3D editor + import from external 3D tools |
| Presets | Editable 3D presets as starting scenes; engine never depends on them |
| Preset categories (v1) | Clubs & warehouses; halls, chapels & churches; outdoor; domestic |
| Sources | All three: single L/R pair; one stereo track through a multi-speaker layout; multiple stems at different positions |
| Speakers | Generic ideal speakers (position only); speaker types with dispersion as an advanced option |
| Movement | Listener and sources movable, automatable in the DAW |
| Listener orientation | Always faces the sources; no head-orientation control |
| Output | User picks headphones (binaural) or stereo speakers |
| Headphone profile | Personalized head/ear profile (e.g. from ear photos or measurements) |
| Speaker mode | Assumes a neutral playback setup; no user-room calibration |
| Accuracy vs CPU | Accuracy first; heavy CPU/latency acceptable |
| Validation | Measured match against real impulse responses + listening tests |
| Scene storage | Saved inside the DAW project only; no export or sharing |
| Module coupling | 3D Module and Simulator logically separate, built and shipped as one |
| Atmosphere | Not user-controlled; a fixed standard atmosphere (air absorption) is always applied (see BUILD_PLAN AX4) |
| Audience/crowd | Not modeled; spaces are always empty |
| Team | Maisara + contracted DSP and 3D engineers; no fixed deadline |

## System architecture

The 3D Module turns whatever the user builds, imports or automates into one contract. The Simulator defines that contract and renders from it alone.

&#91;embedded content: plugin architecture · 2 modules, 1 contract\]

Both modules ship in one plugin, but the contract boundary stays explicit and versioned so each side can evolve independently. The contract's contents are question Q1 for the Spatial Audio Expert.

## Functional requirements

Requirements are grouped by module; IDs are for traceability in the Expert question list and engineering specs.

**3D Module: scene building**

- **FR-3D-1** Built-in 3D editor to build, view and edit a full scene: geometry, surfaces, objects.
- **FR-3D-2** Import scenes from external 3D tools (formats to be decided; see Open decisions).
- **FR-3D-3** Ship editable presets across four categories: clubs & warehouses; halls, chapels & churches; outdoor (festivals, mountains, fields); domestic (living rooms, cars, small rooms).
- **FR-3D-4** Let users adjust preset dimensions and per-surface acoustic properties (absorption, reflectivity, permeability, and any others the Expert defines).
- **FR-3D-5** Place one listener and any number of sources anywhere in the scene.
- **FR-3D-6** Support three source setups: a single L/R pair; one stereo track through a multi-speaker layout; multiple stems at different positions in one shared scene.
- **FR-3D-7** Speakers are generic and ideal by default; an advanced option assigns a speaker type (e.g. bookshelf, PA top, sub) with its own dispersion.
- **FR-3D-8** Expose listener and source positions as DAW-automatable parameters.
- **FR-3D-9** Keep the listener facing the sources at all times.
- **FR-3D-10** Translate the scene into the Simulator's input contract on every scene or position change.

**Simulator: acoustic simulation & rendering**

- **FR-SIM-1** Define its own versioned input contract; the 3D Module conforms to it.
- **FR-SIM-2** Simulate generically from scene data; no preset-specific logic.
- **FR-SIM-3** Render in two user-selectable modes: binaural (headphones) and stereo speakers.
- **FR-SIM-4** In headphone mode, use a personalized head/ear profile created from ear photos or measurements.
- **FR-SIM-5** In speaker mode, assume neutral playback; no user-room calibration.
- **FR-SIM-6** Follow automated listener and source movement without audible artifacts.
- **FR-SIM-7** For multi-stem scenes, combine audio from several plugin instances into one shared scene.

**Licensing & persistence**

- **FR-LIC-1** Scene, settings and render state are saved in the DAW project.
- **FR-LIC-2** An active subscription or trial is required to create or change anything.
- **FR-LIC-3** Without an active subscription or trial, every existing instance keeps rendering exactly as saved, including after a trial that ended unpaid.
- **FR-LIC-4** New users get a full-feature, time-limited free trial.

## Non-functional requirements

Accuracy is the top priority; CPU load and latency may be high, but the plugin must stay usable in a DAW session.

| ID | Requirement |
| --- | --- |
| NFR-1 Accuracy | Rendering must match impulse responses measured in real spaces and pass listening tests. Pass thresholds come from the Expert. |
| NFR-2 Performance | Heavy CPU and latency are acceptable when they buy accuracy. The plugin must report its latency to the DAW for compensation. |
| NFR-3 Real-time movement | Automated movement must render smoothly despite heavy processing. This tension goes to the Expert. |
| NFR-4 Platforms | VST3 and AU on macOS and Windows (AU is macOS-only by nature). |
| NFR-5 3D technology | Choose the lightest, simplest, most accurate and most usable real-time 3D stack available. |
| NFR-6 Persistence | Reopening a DAW project restores the scene and its render exactly, on any machine with the plugin installed. |
| NFR-7 Licence resilience | A licence lapse must never silence, alter or bypass a saved instance. |
| NFR-8 Generic engine | Any valid scene renders correctly; no environment-specific code paths. |

## Business model & licensing

The model is a subscription at $10–20 per month that unlocks editing, while rendering of saved work is never taken away.

| State | Create/edit scenes | Existing instances render |
| --- | --- | --- |
| Active subscription | Yes | Yes |
| Free trial (full features, time-limited) | Yes | Yes |
| Trial ended unpaid | No | Yes, exactly as saved |
| Subscription lapsed | No | Yes, exactly as saved |

Open question: since rendering never stops, the trial's conversion pressure comes only from the need to make *new* changes. Monitor trial-to-paid conversion against the under-500 subscriber target.

## Out of scope

These were explicitly excluded during discovery:

- Multichannel or immersive output (5.1, Dolby Atmos); output is stereo or binaural only.
- User control of atmospheric conditions (temperature, humidity, wind). A fixed standard atmosphere (air absorption) is always applied (see BUILD_PLAN AX4).
- Audience or crowd presence; all spaces are empty.
- Listener head orientation control and headphone head tracking.
- Calibration to the user's own room or speakers.
- Real-world branded speaker models.
- Scene export, sharing, or a community/marketplace library.
- Delivery as a Max for Live device or as configured stock Ableton devices.

## Assumptions

These are working assumptions to confirm; each one changes requirements if it turns out false.

- **A1** When sources sit at different positions, the listener faces their center point.
- **A2** All four v1 priorities ship in v1: multi-stem scenes, personalized head/ear profiles, 3D import, and multi-speaker venue layouts. Phasing is not yet decided.
- **A3** One listener per scene.
- **A4** The rendered result reaches the final track through the DAW's normal bounce/export; the plugin has no export of its own.
- **A5** Multi-stem scenes are built from several plugin instances in one DAW project that share one scene.

## Open decisions & questions for the Spatial Audio Expert

The first 10 questions go to the Spatial Audio Expert project; its answers set the Simulator's design and the 3D Module's contract.

| # | Question | Owner | Unblocks |
| --- | --- | --- | --- |
| Q1 | What exactly must the Simulator receive from the 3D Module (geometry, materials, positions, speaker data, profile) to simulate any scene? Define the input contract. | Expert | FR-SIM-1, FR-3D-10 |
| Q2 | Which simulation method(s) give the highest accuracy across rooms, large halls and outdoor spaces with one generic engine? | Expert | FR-SIM-2, NFR-8 |
| Q3 | Which per-surface material properties must users control, and what are their valid ranges? | Expert | FR-3D-4 |
| Q4 | How do we keep heavy, accuracy-first processing smooth when positions are automated? | Expert | NFR-3, FR-SIM-6 |
| Q5 | Where should computation run: fully local, cloud-assisted, or hybrid? | Expert | NFR-2 |
| Q6 | How should a personalized head/ear profile be captured (ear photos, measurements), and how accurate is each method? | Expert | FR-SIM-4 |
| Q7 | How should the stereo-speaker mode reproduce the scene on a neutral speaker setup (e.g. crosstalk handling)? | Expert | FR-SIM-3, FR-SIM-5 |
| Q8 | What does a speaker type's dispersion need to describe, and which types should v1 include? | Expert | FR-3D-7 |
| Q9 | What measured-match and listening-test thresholds count as "accurate", and which reference impulse responses do we use? | Expert | NFR-1 |
| Q10 | What is the realistic latency and CPU budget for the chosen method? | Expert | NFR-2 |
| Q11 | Which 3D import formats should be supported? | Product + Engineering | FR-3D-2 |
| Q12 | Which real-time 3D technology should power the editor? | Engineering | NFR-5 |
| Q13 | How do several plugin instances share one scene reliably across DAWs? | Engineering | FR-SIM-7 |
| Q14 | How should the four v1 priorities be phased, if at all? | Product | A2 |
| Q15 | What trial length best converts toward the subscriber target? | Product | FR-LIC-4 |

## Team, timeline & next steps

Maisara leads product, with contracted DSP and 3D engineers; there is no fixed v1 deadline.

- [ ] Send Q1–Q10 to the Spatial Audio Expert project
- [ ] Turn the Expert's answer to Q1 into the versioned 3D Module → Simulator contract
- [ ] Decide v1 phasing (Q14)
- [ ] Pick the real-time 3D stack and import formats (Q11, Q12)
- [ ] Write the brief for contracting DSP and 3D engineers
