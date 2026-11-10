"""Phase 05h, AX39 D1 and D2: source checks of the diffuse estimator (src/sim/diffuse/).

D1: no <random> anywhere in the unit, and no libm transcendental in the path-decision header Sampling.h (only
+ - * / and sqrt, which IEEE 754 rounds correctly, may decide a path). D2: the unit is compiled with fp-contract
off (gcc/clang) or /fp:precise (MSVC), and no fast-math flag is set anywhere in the build.
"""

from __future__ import annotations

import pathlib
import re

REPO = pathlib.Path(__file__).resolve().parents[2]
UNIT = REPO / "src" / "sim" / "diffuse"
LIBM = ("sin", "cos", "tan", "asin", "acos", "atan", "atan2", "exp", "exp2", "expm1", "log", "log2", "log10",
        "log1p", "pow", "cbrt", "hypot", "sinh", "cosh", "tanh", "erf", "lgamma", "tgamma")


def _code(path: pathlib.Path) -> str:
    """Source without comments."""
    text = path.read_text()
    text = re.sub(r"/\*.*?\*/", "", text, flags=re.S)
    return re.sub(r"//[^\n]*", "", text)


def test_unit_exists():
    assert (UNIT / "Sampling.h").is_file()
    assert (UNIT / "DiffuseEstimator.cpp").is_file()


def test_no_random_header():
    for p in sorted(UNIT.glob("*")):
        assert "<random>" not in _code(p), f"{p.relative_to(REPO)} includes <random> (AX39 D1, D3)"


def test_no_libm_in_path_decisions():
    code = _code(UNIT / "Sampling.h")
    for fn in LIBM:
        assert not re.search(rf"\b(std::)?{fn}f?\s*\(", code), f"Sampling.h calls {fn} (AX39 D1)"


def test_fp_contract_flags():
    cmake = (REPO / "src" / "sim" / "CMakeLists.txt").read_text()
    assert "-ffp-contract=off" in cmake and "/fp:precise" in cmake, "AX39 D2 flags missing in src/sim/CMakeLists.txt"
    for src in ("diffuse/FaceLists.cpp", "diffuse/ThreadPool.cpp", "diffuse/DiffuseEstimator.cpp"):
        assert src in cmake.split("SPATIAL_DIFFUSE_SOURCES", 1)[1], f"{src} not under the D2 flags"


def test_no_fast_math_anywhere():
    files = [REPO / "CMakeLists.txt", REPO / "CMakePresets.json", *REPO.glob("cmake/*.cmake"), *REPO.glob("src/**/CMakeLists.txt")]
    for p in files:
        text = p.read_text()
        for flag in ("-ffast-math", "-Ofast", "/fp:fast", "-funsafe-math-optimizations"):
            assert flag not in text, f"{p.relative_to(REPO)} sets {flag} (AX39 D2)"
