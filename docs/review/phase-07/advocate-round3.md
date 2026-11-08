# Phase-07 D7 as applied: advocate, final screen (2026-11-08)

**PASS (high).** Round-2 condition met (phase-07 scope 3 "Switch rule and crossfade law"): the flag applies only to
the restore's own decision and is cleared on submit or skip, including prepareToPlay and reset step 3; tests (a), (b),
(f) require EqualGain for the next listener_y change after an identical restore, realtime and offline (no +3 dB on
recall/undo, FR-SIM-6); offline flag cleared at a host-order block boundary, test (e) bit-identical incl. a fresh
instance (AX5); generic, IR comparison only (NFR-8). No drift into Phase 10. Closes steward gap G16.
