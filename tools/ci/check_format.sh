#!/usr/bin/env bash
# Fails when any C++ source in src/ or tests/ is not clang-format clean.
#   tools/ci/check_format.sh          # check (used by CI)
#   tools/ci/check_format.sh --fix    # reformat in place
set -euo pipefail
cd "$(dirname "${BASH_SOURCE[0]}")/../.."

CLANG_FORMAT="${CLANG_FORMAT:-$(command -v clang-format-18 || command -v clang-format)}"
"${CLANG_FORMAT}" --version

mapfile -t FILES < <(git ls-files --cached --others --exclude-standard 'src/**/*.cpp' 'src/**/*.h' 'tests/**/*.cpp' 'tests/**/*.h')
[[ ${#FILES[@]} -gt 0 ]] || { echo "no files to check"; exit 0; }

if [[ "${1:-}" == "--fix" ]]; then
    "${CLANG_FORMAT}" -i --style=file "${FILES[@]}"
    echo "formatted ${#FILES[@]} files"
else
    "${CLANG_FORMAT}" --dry-run --Werror --style=file "${FILES[@]}"
    echo "clang-format: ${#FILES[@]} files clean"
fi
