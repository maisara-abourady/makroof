# Seat 3 (reverb renderer) — re-run 3 on Seat 5's two-class gate

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

SEAT 3 POSITION (re-run 3)

I rate 4a-2G++ 1/2 with Seat 5's (a) and (b) as written. It drops to 1/1 if the offline-render class takes turns with builder-thread waiters instead of always going ahead of them.

| variant | rating (now / later) | reason | condition (later 2 → 1) |
|---|---|---|---|
| 4a-2G++ with Seat 5's (a)+(b) | **1 / 2** | **Agreed with Seat 5:** (b) is right. Offline builds that never coalesce keep bounces deterministic, and builder waits that cancel on quiesce() are harmless. In (a), serving prepare, restore and setNonRealtime first is fine, because they are short and rare. **The problem:** (a) also serves offline-render solves first, and those can be one per changed block for the whole of a freeze or render. While that runs, every instance playing in real time is starved: its IR stops following automation, then jumps to the latest scene when the render ends. That is a stall followed by a large step, the time-variance failure my criterion 1 exists to prevent [Hyp: assumes hosts that freeze or render while other tracks play]. An offline render has no real-time deadline, so it gains nothing from going first. | **Three classes:** (1) synchronous host calls (prepare, restore, setNonRealtime) are served first, which keeps Seat 5's bound of one running solve; (2) offline-render solves and (3) builder-thread waiters take turns, one solve each, so a real-time instance waits at most about two solves. **Record:** the staleness of a real-time instance while another instance renders offline under room-size automation, beside the 1/4/8-builder records. |

**For Seat 5:** with turns, an offline render waits about one extra solve per changed block. Bounce time grows, but the output does not change, because offline builds never coalesce.
