# Golden file change log

Every change to a golden file in `tests/golden/` is recorded here by `tools/ci/update_goldens.py`,
which is the only supported way to update them (CLAUDE.md "Tests and golden files"). An entry
gives the date, the reason, and which goldens were created or which values moved out of their
tolerance. A golden change also needs an explanation in the PR and a row in `docs/BUILD_PLAN.md` §6.

Golden file format: see `tools/acoustics/golden.py`.

