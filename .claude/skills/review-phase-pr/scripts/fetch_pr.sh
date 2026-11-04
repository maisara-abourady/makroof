#!/usr/bin/env bash
# Fetch the base and head of a pull request so review_context.py and `git diff` can see them.
#
#   scripts/fetch_pr.sh <pr-number>            # needs `gh` (laptop) or the GitHub MCP tools (cloud)
#   scripts/fetch_pr.sh <head-branch> [base]   # plain git, base defaults to main
#
# Prints two lines: BASE=<ref> and HEAD=<ref>, which the skill passes on to review_context.py.
# Refs that exist on origin come back as origin/<name>; a branch that only exists locally (never
# pushed, or a scratch branch) is used as is. It never checks anything out: reviewing happens
# against refs, so the working tree stays untouched.
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

# Fetch a ref from origin; on network errors retry with backoff; if origin has no such ref, fall
# back to a local branch/commit of that name (a branch that was never pushed, a scratch branch).
resolve() {
    local ref="$1" n=0 err
    while :; do
        if err="$(git fetch --quiet origin "$ref" 2>&1)"; then
            echo "origin/${ref}"; return 0
        fi
        if grep -qi "couldn't find remote ref\|not found\|invalid refspec" <<<"$err"; then
            if git rev-parse --verify --quiet "${ref}^{commit}" >/dev/null; then
                echo "$ref"; return 0
            fi
            echo "ref $ref exists neither on origin nor locally" >&2; return 1
        fi
        n=$((n + 1)); [[ $n -lt 5 ]] || { echo "fetch $ref failed: $err" >&2; return 1; }
        sleep $((2 ** n))
    done
}
base_out="$(resolve "$base_ref")" || exit 1
head_out="$(resolve "$head_ref")" || exit 1

echo "BASE=${base_out}"
echo "HEAD=${head_out}"
