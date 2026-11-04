#!/usr/bin/env bash
# Resolve the base and head of a review target so review_context.py and `git diff` can see them.
#
#   scripts/fetch_pr.sh <pr-number> [base]     # fetches refs/pull/<n>/head (works for merged PRs too)
#   scripts/fetch_pr.sh <head-branch> [base]   # plain git, base defaults to main
#   scripts/fetch_pr.sh <sha> [base]           # a commit that is already local
#
# Prints two lines: BASE=<ref> and HEAD=<ref>, which the skill passes on to review_context.py.
# A PR number is fetched through GitHub's refs/pull/<n>/head, which exists for open, closed and
# merged PRs even after the head branch was deleted, and needs neither gh nor the API. The base
# defaults to main; pass the PR's base branch as the second argument when it differs. Refs that
# exist on origin come back as origin/<name>; a branch or commit that only exists locally (never
# pushed, a scratch branch) is used as is. Nothing is checked out: reviewing happens against refs,
# so the working tree stays untouched.
set -euo pipefail

arg="${1:-}"
base_in="${2:-main}"
[[ -n "$arg" ]] || { echo "usage: fetch_pr.sh <pr-number | head-branch | sha> [base-branch]" >&2; exit 2; }

# Fetch a ref from origin; on network errors retry with backoff; if origin has no such ref, fall
# back to a local branch/commit of that name.
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

base_out="$(resolve "$base_in")" || exit 1

if [[ "$arg" =~ ^[0-9]+$ ]]; then
    n=0
    until git fetch --quiet origin "pull/${arg}/head:refs/remotes/origin/pr/${arg}"; do
        n=$((n + 1)); [[ $n -lt 5 ]] || { echo "fetch of PR #${arg} failed" >&2; exit 1; }
        sleep $((2 ** n))
    done
    head_out="origin/pr/${arg}"
else
    head_out="$(resolve "$arg")" || exit 1
fi

echo "BASE=${base_out}"
echo "HEAD=${head_out}"
