#!/usr/bin/env bash
# Populates docs/corpus/ (git-ignored) with the reference corpus used by the interrogator subagent.
# Source: the private repository maisara-abourady/audio-resources (corpus/*.md). Copyrighted book texts:
# never commit them to this repository.
#
#   tools/ci/fetch_corpus.sh                 # clone or update the source, then copy into docs/corpus/
#   AUDIO_RESOURCES_DIR=/path tools/ci/fetch_corpus.sh   # use (or clone into) another checkout
#   AUDIO_RESOURCES_REF=<commit|tag|branch> tools/ci/fetch_corpus.sh   # pin a revision (default: main)
#
# In a Claude Code cloud session, attach the audio-resources repository to the session first; its
# default checkout path /home/user/audio-resources is picked up automatically.
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
url="${AUDIO_RESOURCES_URL:-https://github.com/maisara-abourady/audio-resources.git}"
ref="${AUDIO_RESOURCES_REF:-main}"
if [[ -n "${AUDIO_RESOURCES_DIR:-}" ]]; then
  src="$AUDIO_RESOURCES_DIR"
elif [[ -d /home/user/audio-resources/.git ]]; then
  src=/home/user/audio-resources
else
  src="$repo_root/../audio-resources"
fi
dest="$repo_root/docs/corpus"

if [[ -d "$src/.git" ]]; then
  git -C "$src" fetch --depth 1 origin "$ref"
  git -C "$src" checkout --quiet --detach FETCH_HEAD
else
  git clone --depth 1 --branch "$ref" "$url" "$src" 2>/dev/null \
    || { git clone --depth 1 "$url" "$src" && git -C "$src" fetch --depth 1 origin "$ref" \
         && git -C "$src" checkout --quiet --detach FETCH_HEAD; }
fi

shopt -s nullglob
files=("$src"/corpus/*.md)
if (( ${#files[@]} == 0 )); then
  echo "error: no corpus/*.md in $src" >&2
  exit 1
fi

mkdir -p "$dest"
rm -f "$dest"/*.md
cp "${files[@]}" "$dest"/
printf '%s\n' "$(git -C "$src" rev-parse HEAD)" > "$dest/SOURCE_COMMIT"
echo "docs/corpus: ${#files[@]} files from $url @ $(git -C "$src" rev-parse --short HEAD)"
