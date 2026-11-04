#!/usr/bin/env bash
# Downloads a pinned pluginval release (verified by SHA-256) and validates one or more plugins at
# strictness level 10. Used by CI on Linux, macOS and Windows (Git Bash) and usable locally:
#
#   tools/ci/run_pluginval.sh [--output-dir DIR] <plugin> [<plugin>...]
#
# The pinned pluginval CLI (1.0.4) always validates in the calling process, so there is no separate
# in-process flag. On Linux the run is wrapped in `xvfb-run -a` when no display is available.
# Exit code: 0 when every plugin passes, 1 otherwise. Logs are written to the output directory.
set -euo pipefail

PLUGINVAL_VERSION="v1.0.4"
# SHA-256 of the release zips at github.com/Tracktion/pluginval/releases/tag/v1.0.4
SHA_LINUX="c01c49d8063965c4c2dea8324468336768f5c9139e0b1caebde14c2400b55352"
SHA_MACOS="3c4c533bda0c5059eea3ddaea752d757ee2025041f0f47e6bcb0e87f6082b29f"
SHA_WINDOWS="c08e61ce3b96db41636f8ec7e76f4c7e2c13ebdac7fa1b5a1f52b4f32ec715ab"

STRICTNESS="${PLUGINVAL_STRICTNESS:-10}"
TIMEOUT_MS="${PLUGINVAL_TIMEOUT_MS:-120000}"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TOOL_DIR="${PLUGINVAL_DIR:-${SCRIPT_DIR}/.pluginval/${PLUGINVAL_VERSION}}"
OUTPUT_DIR=""

usage() {
    sed -n '2,10p' "${BASH_SOURCE[0]}" | sed 's/^# \{0,1\}//'
    exit 2
}

while [[ $# -gt 0 ]]; do
    case "$1" in
        --output-dir) OUTPUT_DIR="$2"; shift 2 ;;
        -h|--help) usage ;;
        --) shift; break ;;
        -*) echo "unknown option: $1" >&2; usage ;;
        *) break ;;
    esac
done
[[ $# -ge 1 ]] || usage
OUTPUT_DIR="${OUTPUT_DIR:-${PWD}/build/pluginval-logs}"
mkdir -p "${OUTPUT_DIR}" "${TOOL_DIR}"

case "$(uname -s)" in
    Linux*)  ASSET="pluginval_Linux.zip";   EXPECTED_SHA="${SHA_LINUX}";   BIN="${TOOL_DIR}/pluginval" ;;
    Darwin*) ASSET="pluginval_macOS.zip";   EXPECTED_SHA="${SHA_MACOS}";   BIN="${TOOL_DIR}/pluginval.app/Contents/MacOS/pluginval" ;;
    MINGW*|MSYS*|CYGWIN*) ASSET="pluginval_Windows.zip"; EXPECTED_SHA="${SHA_WINDOWS}"; BIN="${TOOL_DIR}/pluginval.exe" ;;
    *) echo "unsupported OS: $(uname -s)" >&2; exit 1 ;;
esac

sha256_of() {
    if command -v sha256sum >/dev/null 2>&1; then sha256sum "$1" | awk '{print $1}'
    else shasum -a 256 "$1" | awk '{print $1}'; fi
}

if [[ ! -x "${BIN}" ]]; then
    ZIP="${TOOL_DIR}/${ASSET}"
    URL="https://github.com/Tracktion/pluginval/releases/download/${PLUGINVAL_VERSION}/${ASSET}"
    echo "Downloading pluginval ${PLUGINVAL_VERSION}: ${URL}"
    curl -fsSL --retry 4 --retry-delay 3 -o "${ZIP}" "${URL}"
    ACTUAL_SHA="$(sha256_of "${ZIP}")"
    if [[ "${ACTUAL_SHA}" != "${EXPECTED_SHA}" ]]; then
        echo "pluginval checksum mismatch for ${ASSET}: expected ${EXPECTED_SHA}, got ${ACTUAL_SHA}" >&2
        rm -f "${ZIP}"
        exit 1
    fi
    if command -v unzip >/dev/null 2>&1; then
        unzip -o -q "${ZIP}" -d "${TOOL_DIR}"
    else
        # Git Bash on Windows may lack unzip; PowerShell is always there.
        powershell.exe -NoProfile -Command "Expand-Archive -Force -LiteralPath '$(cygpath -w "${ZIP}")' -DestinationPath '$(cygpath -w "${TOOL_DIR}")'"
    fi
    chmod +x "${BIN}" || true
    if [[ "$(uname -s)" == Darwin* ]]; then
        xattr -dr com.apple.quarantine "${TOOL_DIR}/pluginval.app" 2>/dev/null || true
    fi
fi

# Empty unless xvfb is needed. Expanded as ${RUNNER[@]+"${RUNNER[@]}"} because bash 3.2 (macOS) treats
# an empty array as unbound under set -u.
RUNNER=()
if [[ "$(uname -s)" == Linux* && -z "${DISPLAY:-}" ]] && command -v xvfb-run >/dev/null 2>&1; then
    RUNNER=(xvfb-run -a --server-args="-screen 0 1280x1024x24")
fi

${RUNNER[@]+"${RUNNER[@]}"} "${BIN}" --version

STATUS=0
for PLUGIN in "$@"; do
    PLUGIN_PATH="${PLUGIN}"
    if [[ "$(uname -s)" == MINGW* || "$(uname -s)" == MSYS* ]]; then
        PLUGIN_PATH="$(cygpath -w "${PLUGIN}")"
        OUT_PATH="$(cygpath -w "${OUTPUT_DIR}")"
    else
        OUT_PATH="${OUTPUT_DIR}"
    fi
    echo "::group::pluginval ${PLUGIN}"
    echo "pluginval --strictness-level ${STRICTNESS} --timeout-ms ${TIMEOUT_MS} --output-dir ${OUT_PATH} ${PLUGIN_PATH}"
    if ${RUNNER[@]+"${RUNNER[@]}"} "${BIN}" --strictness-level "${STRICTNESS}" --timeout-ms "${TIMEOUT_MS}" \
            --output-dir "${OUT_PATH}" --validate "${PLUGIN_PATH}"; then
        echo "PASS: ${PLUGIN}"
    else
        echo "FAIL: ${PLUGIN}" >&2
        STATUS=1
    fi
    echo "::endgroup::"
done

echo "pluginval logs: ${OUTPUT_DIR}"
ls -la "${OUTPUT_DIR}" || true
exit "${STATUS}"
