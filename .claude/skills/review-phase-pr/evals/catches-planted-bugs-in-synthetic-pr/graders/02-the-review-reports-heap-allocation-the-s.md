---
type: llm
focus: trace
weight: 1
---

The review reports heap allocation (the std::vector scratch buffer) inside processBlock as a blocker, citing the audio-thread rule.
