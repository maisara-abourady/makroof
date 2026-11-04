"""Acoustic analysis tooling for the Spatial Scene VST (Phase 02).

These are the project's measuring instruments: every DSP phase proves its behaviour with an
offline render (``render_cli``) plus an automatic measurement from this package.

Modules:
    signals  test-signal generators (pink bursts, clicks, Farina sweep, sustained tones, decays)
    bands    octave-band filterbank matching ``contract::kOctaveBandsHz``
    metrics  ISO 3382-1 room-acoustic parameters with Lundeby noise compensation
    compare  IR comparison (arrival times, per-peak amplitude, per-band energy, metric deltas)
    clicks   click/discontinuity detector for sustained-tone renders
    golden   golden-file comparison with per-metric tolerances
    wav      small WAV read/write helpers (soundfile)

Command line: ``python -m tools.acoustics {metrics,compare,clicks} ...`` (see cli.py).
"""
