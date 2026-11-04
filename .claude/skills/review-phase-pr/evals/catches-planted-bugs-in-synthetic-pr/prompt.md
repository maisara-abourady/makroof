---
tags: [review-phase-pr]
max_turns: 60
timeout_seconds: 1500
allowed_tools: [Read, Glob, Grep, Skill, Write, Edit, Bash]
---
A session just pushed a branch for Phase 01 of makroof and I don't trust it. I applied its single commit as a patch on top of main at commit 96ab82a on a scratch branch called `eval/phase-01-candidate` (the patch file is planted-phase-01.patch if you need to recreate the branch: `git checkout -b eval/phase-01-candidate 96ab82a && git am planted-phase-01.patch`). There is no GitHub PR for it yet, so review the branch against main as if it were the Phase 01 PR, and write the review to review-eval-phase-01.md. Don't post anything to GitHub.
Input files: planted-phase-01.patch
