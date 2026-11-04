#!/usr/bin/env bash
# Fetch the base and head of a pull request so review_context.py and `git diff` can see them.
#
#   scripts/fetch_pr.sh <pr-number>            # needs `gh` (laptop) or the GitHub MCP tools (cloud)
#   scripts/fetch_pr.sh <head-branch> [base]   # plain git, base defaults to main
#
# Prints two lines: BASE=<ref> and HEAD=<ref>, which the skill passes on to review_context.py.
# It never checks anything out: reviewing happens against refs, so the working tree stays untouched.
set -euo pipefail

arg="${1:-}"
base_in="${2:-main}"
[[ -n "$arg" ]] || { echo "usage: fetch_pr.sh <pr-number | head-branch> [base-branch]" >&2; exit 2; }

if [[ "$arg" =~ ^[0-9]+$ ]]; then
    if command -v gh >/dev/null 2>&1; then
        head_ref="$(gh pr view "$arg" --json headRefName --jq .headRefName)"
        base_ref="$(gh pr view "$arg" --json baseRefName --jq .baseRefName)"
    else
        echo "gh is not available: look up the PR's head and base branch with the GitHub MCP tool" >&2
        echo "(pull_request_read, method get), then rerun: fetch_pr.sh <head-branch> <base-branch>" >&2
        exit 3
    fi
else
    head_ref="$arg"
    base_ref="$base_in"
fi

fetch() {
    local ref="$1" n=0
    until git fetch --quiet origin "$ref"; do
        n=$((n + 1)); [[ $n -lt 5 ]] || { echo "fetch $ref failed" >&2; exit 1; }
        sleep $((2 ** n))
    done
}
fetch "$base_ref"
fetch "$head_ref"

echo "BASE=origin/${base_ref}"
echo "HEAD=origin/${head_ref}"
