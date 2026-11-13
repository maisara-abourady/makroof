"""Tests for tools/ci/repin_gate.py (phase-07c-1b FM-GROWTH / FM-TRIG): the S2 pin from synthetic GATE logs."""

from __future__ import annotations

import json
import math
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parent))
import repin_gate as rg  # noqa: E402

TS = "2026-11-13T10:00:00.1234567Z "


def _gate_lines(os_name: str, fl_median: float, la_median: float, *, fl_solve=100.0, la_solve=80.0,
                fl_ns=1.00, la_ns=1.20, fl_x14=7.0, la_x14=28.0, ts=True, s_l=None, s_f=None) -> str:
    """GATE (and optional stage-split) lines in the format the C++ test prints."""
    p = TS if ts else ""
    ratio = la_median / fl_median
    out = (
        f"{p}05h-records GATE os={os_name} scene=cube100_flutter_fallback x14worst={fl_x14:.2f} "
        f"median={fl_median:.0f} fullRebuildMedian=1 solveMedianMs={fl_solve:.1f} solveWarnAt=157.4 "
        f"solveBasis=PROVISIONAL(n=1) solveK=1.200 nsPerEval={fl_ns:.2f} status=asserted(30s) flutterRef=701 "
        f"flutterRefBasis=RG-1 flutterDev=+1.0% inWindow=yes warnings=\r\n"
        f"{p}05h-records GATE os={os_name} scene=cube100_lowalpha0.05_s0.3 ratio={ratio:.3f} ratioWarnAt=3.355 "
        f"ratioRef=3.050 ratioRefBasis=RG-1(n=0) ratioOverRef=0.9500 ratioMargin=+0.1500 ratioLowAt=2.773 "
        f"ratioCheck=PROVISIONAL solveMedianMs={la_solve:.1f} solveWarnAt=97.1 solveBasis=PROVISIONAL(n=1) "
        f"solveK=1.200 nsPerEval={la_ns:.2f} nsPerEvalRatio=1.2000 x14worst={la_x14:.2f} median={la_median:.0f} "
        f"growthBound=2275 growthRef=2068 growthPct=+1.0% fullRebuildMedian=1 flutterMedian={fl_median:.0f} "
        f"flutterRef=701 flutterDev=+1.0% inWindow=yes flutterOverRef=1.0100 product=0.9595 "
        f"status=provisional(S2-pin-pending) trigger=0 triggerBasis=RG-1 warnings=PASSES30S \r\n"
        # An annotation repeating the GATE line must not count as a second run.
        f"{p}::warning title=GATE x cube100_lowalpha0.05_s0.3::GROWTH 05h-records GATE os={os_name} "
        f"scene=cube100_lowalpha0.05_s0.3 ratio=9.999 median=1\n"
    )
    for scene, share, med in (("cube100_lowalpha0.05_s0.3", s_l, la_median), ("cube100_flutter_fallback", s_f, fl_median)):
        if share is not None:
            out += (
                f"{p}07c1b-records stage split os={os_name} scene={scene} 96 kHz keyless restore (stage-hook "
                f"timestamps on the host thread, median [min max] of 10, ms): start->Plan (quiesce, snapshot) 1.0 "
                f"[1.0 1.0]; Plan->Solve (ISM + matching + gate wait) 10.0 [9.0 11.0]; Solve->Assemble (solve) "
                f"5.0 [4.0 6.0]; Assemble->Commit (synthesis + assembly + makeIrSet + D7 compare) {share * med:.1f} "
                f"[1.0 9999.0]; Commit->return 0.1 [0.1 0.1]; restore median {med:.0f}\n"
                f"{p}07c1b-records stage split replay os={os_name} scene={scene} 96 kHz (sim::StagedBuild, "
                f"parallelEmitterSynthesis = false, exact tail, median of 3, ms): plan (ISM + matching) 1.0; "
                f"solve 1.0; assemble fresh (synthesis + assembly) 1.0\n"
            )
    return out


def _write(tmp: Path, name: str, text: str) -> str:
    path = tmp / name
    path.write_text(text)
    return str(path)


# Three green runs per OS (one job log per OS and run) and one red run.
RUNS = {
    "Linux": [(700.0, 2030.0, 80.0), (690.0, 2070.0, 82.0), (710.0, 2059.0, 81.0)],
    "macOS": [(480.0, 1800.0, 84.0), (490.0, 1900.0, 83.0), (470.0, 1750.0, 85.0)],
    "Windows": [(730.0, 2000.0, 90.0), (600.0, 2100.0, 91.0), (740.0, 2050.0, 89.0)],
}


@pytest.fixture
def logs(tmp_path: Path) -> list[str]:
    specs = []
    for os_name, runs in RUNS.items():
        for i, (fl, la, la_solve) in enumerate(runs):
            text = _gate_lines(os_name, fl, la, la_solve=la_solve, fl_solve=100.0 + i, la_ns=1.2 + 0.01 * i,
                               la_x14=31.0 if (os_name == "Windows" and i == 1) else 28.0, s_l=0.92, s_f=0.51)
            specs.append("green=" + _write(tmp_path, f"{os_name}-{i}.log", text))
    red = _gate_lines("Linux", 400.0, 4000.0, la_x14=99.0)
    specs.append("red=" + _write(tmp_path, "red.log", red))
    return specs


def test_proposal_values(logs: list[str]) -> None:
    green, refused = rg.load_runs(logs)
    assert len(green) == 9 and refused and refused[0].endswith("red.log")
    p = rg.propose(green)
    lin = p["os"]["Linux"]
    ratios = [round(la / fl, 3) for fl, la, _ in RUNS["Linux"]]
    assert lin["runs"] == 3 and lin["pinnable"]
    assert lin["ratioRef"] == pytest.approx(sum(ratios) / 3)
    assert lin["ratioMaxOverMin"] == pytest.approx(max(ratios) / min(ratios))
    assert not lin["ratioPrintOnly"]
    assert lin["flutterRefMs"] == pytest.approx(700.0)
    assert lin["scenes"]["cube100_lowalpha0.05_s0.3"]["baselineMedianMs"] == pytest.approx((2030 + 2070 + 2059) / 3)
    assert lin["scenes"]["cube100_lowalpha0.05_s0.3"]["solveRefMs"] == pytest.approx(81.0)
    # k: the largest max / mean over both scenes (flutter 100, 101, 102 -> 102/101; low-alpha 82/81)
    assert lin["solveK"] == pytest.approx(max(102 / 101, 82 / 81))
    # Windows: 600 ms flutter run -> ratio 3.5 vs 2.74 -> max/min > 1.10 -> print-only; one run over 30 s (E1)
    win = p["os"]["Windows"]
    assert win["ratioMaxOverMin"] > 1.10 and win["ratioPrintOnly"]
    assert not win["scenes"]["cube100_lowalpha0.05_s0.3"]["passes30sEveryRun"]
    assert win["split"]["domainMaxMinOk"] is False
    assert p["os"]["macOS"]["ratioPrintOnly"]  # macOS always
    # f at s_L 0.92, s_F 0.51 (file 11: ~x1.28)
    sp = lin["split"]
    assert sp["sL"] == pytest.approx(0.92, abs=1e-3) and sp["sF"] == pytest.approx(0.51, abs=1e-3)
    assert sp["f"] == pytest.approx(0.459 / 0.359, rel=2e-3)
    assert sp["domainSharesOk"] and not sp["seat3Later2"]
    assert p["os"]["macOS"]["split"]["macDetectionFactor"] == pytest.approx(1 + 0.15 / 0.92, rel=1e-3)
    # macOS trigger: floor(1.15 x mean(1800, 1900, 1750)) = floor(2089.17) = 2089; 1900 is not above it
    mt = p["macTrigger"]
    assert mt["kMacGrowthTriggerMs"] == math.floor(1.15 * (1800 + 1900 + 1750) / 3) == 2089
    assert mt["runsAboveComputed"] == [] and mt["runsAboveInForce"] == []
    # G9: ns-per-eval ratios 1.20, 1.21, 1.22 lie within 1.05 of their mean
    assert lin["g9ExitMet"]


def test_report_and_main(logs: list[str], tmp_path: Path, capsys: pytest.CaptureFixture[str]) -> None:
    out_json = tmp_path / "p.json"
    assert rg.main([*logs, "--json", str(out_json)]) == 0
    text = capsys.readouterr().out
    assert "REFUSED (red run" in text
    assert "ratio check: ASSERTED" in text and "PRINT-ONLY (macOS" in text and "PRINT-ONLY (max/min > 1.10)" in text
    assert "E1 (cube100_lowalpha0.05_s0.3 Windows register entry): stays listed" in text
    assert "E1 (cube100_lowalpha0.05_s0.3 macOS register entry): closes under 4c (c)" in text
    assert "constexpr double kMacGrowthTriggerMs = 2089.0;" in text
    assert "constexpr int kMacGrowthTriggerS2Runs = 3;" in text
    # One S2Pin initializer per OS and scene; the flutter entry carries no ratio reference.
    assert "cube100_flutter_fallback   Linux    {0.0000, 0.0000, 700.0, 700.0, 101.0," in text
    # The last field is solveExitMet, the OS's G9 exit (met on every OS of this fixture); k = 82 / 81.
    assert "cube100_flutter_fallback   Linux    {0.0000, 0.0000, 700.0, 700.0, 101.0, 1.0123, 3, true}" in text
    assert "solveExitMet" in text
    data = json.loads(out_json.read_text())
    assert set(data["os"]) == {"Linux", "macOS", "Windows"} and data["refused"]


def test_seat7_sentence_when_a_run_exceeds_its_trigger(tmp_path: Path) -> None:
    specs = [
        "green=" + _write(tmp_path, f"m{i}.log", _gate_lines("macOS", 480.0, la))
        for i, la in enumerate((1700.0, 1700.0, 2300.0))
    ]
    green, _ = rg.load_runs(specs)
    p = rg.propose(green)
    assert p["macTrigger"]["kMacGrowthTriggerMs"] == math.floor(1.15 * 1900.0)
    assert len(p["macTrigger"]["runsAboveComputed"]) == 1
    assert len(p["macTrigger"]["runsAboveInForce"]) == 1  # 2300 > 2172
    assert "the board kept her factor 1.15" in rg.report(p, [])
    assert p["os"]["macOS"]["split"] == {"runsWithSplit": 0}  # no stage-split lines: f not computed


def test_domain_and_branch(tmp_path: Path) -> None:
    assert rg.uniform_slowdown_factor(0.5, 0.5) is None  # s_L <= 1.10 s_F
    assert rg.uniform_slowdown_factor(0.92, 0.51) == pytest.approx(1.2786, abs=1e-4)
    specs = [
        "green=" + _write(tmp_path, f"l{i}.log", _gate_lines("Linux", 700.0, 2000.0, s_l=0.60, s_f=0.56))
        for i in range(3)
    ]
    p = rg.propose(rg.load_runs(specs)[0])
    sp = p["os"]["Linux"]["split"]
    assert not sp["domainSharesOk"] and sp["f"] is None and sp["seat3Later2"]
    assert "Seat 3's later 2" in rg.report(p, [])


def test_not_pinnable_below_three_runs(tmp_path: Path) -> None:
    specs = ["green=" + _write(tmp_path, "a.log", _gate_lines("Linux", 700.0, 2000.0, ts=False))]
    p = rg.propose(rg.load_runs(specs)[0])
    assert not p["os"]["Linux"]["pinnable"]
    assert "NOT PINNABLE (n < 3)" in rg.report(p, [])
    assert not p["os"]["Linux"]["g9ExitMet"]
    assert rg._s2_init(p["os"]["Linux"], rg.FLUTTER).endswith(", 1, false}")


def test_solve_exit_flag_follows_g9(tmp_path: Path) -> None:
    # 07c-1b/25 Q3: the paste-ready S2Pin carries solveExitMet from the OS's G9 result. Linux: ns-per-eval ratios
    # 1.20 / 1.21 / 1.22 (within 1.05 of the mean) -> true; macOS: 0.50 / 0.72 / 0.79 (as on the S2 runs) -> false.
    specs = []
    for os_name, la_ns in (("Linux", (1.20, 1.21, 1.22)), ("macOS", (0.50, 0.72, 0.79))):
        for i, ns in enumerate(la_ns):
            specs.append("green=" + _write(tmp_path, f"{os_name}-{i}.log", _gate_lines(os_name, 700.0, 2000.0, la_ns=ns)))
    p = rg.propose(rg.load_runs(specs)[0])
    assert p["os"]["Linux"]["g9ExitMet"] and not p["os"]["macOS"]["g9ExitMet"]
    text = rg.report(p, [])
    for scene in rg.SCENES:
        assert rg._s2_init(p["os"]["Linux"], scene).endswith(", 3, true}")
        assert rg._s2_init(p["os"]["macOS"], scene).endswith(", 3, false}")
        assert f"{scene:<26} macOS    {rg._s2_init(p['os']['macOS'], scene)}" in text


def test_one_log_with_several_os_jobs(tmp_path: Path) -> None:
    text = _gate_lines("Linux", 700.0, 2000.0) + _gate_lines("Windows", 730.0, 2000.0)
    green, _ = rg.load_runs(["green=" + _write(tmp_path, "both.log", text)])
    assert sorted(r.os for r in green) == ["Linux", "Windows"]


@pytest.mark.parametrize(
    "text, spec_status, msg",
    [
        ("", "green", "no 05h-records GATE lines"),
        (_gate_lines("Linux", 700.0, 2000.0) * 2, "green", "a second GATE line"),
        (_gate_lines("Linux", 700.0, 2000.0).split("\r\n", 1)[1], "green", "no GATE line for cube100_flutter_fallback"),
        (_gate_lines("Linux", 700.0, 2000.0) + "/src/x.cpp:12: FAILED:\n", "green", "holds a Catch2 failure"),
        ("x", "amber", "green=PATH or red=PATH"),
    ],
)
def test_input_errors(tmp_path: Path, text: str, spec_status: str, msg: str, capsys: pytest.CaptureFixture[str]) -> None:
    path = _write(tmp_path, "x.log", text)
    assert rg.main([f"{spec_status}={path}"]) == 2
    assert msg in capsys.readouterr().err


def test_only_red_runs_refused(tmp_path: Path, capsys: pytest.CaptureFixture[str]) -> None:
    path = _write(tmp_path, "r.log", _gate_lines("Linux", 700.0, 2000.0))
    assert rg.main([f"red={path}"]) == 2
    assert "no green run" in capsys.readouterr().err


def test_reads_the_lines_the_cpp_test_prints() -> None:
    """The GATE and stage-split formats repin_gate.py parses are the ones test_diffuse_records.cpp prints."""
    src = (Path(__file__).resolve().parents[2] / "tests" / "unit" / "test_diffuse_records.cpp").read_text()
    for key in ("ratio=%.3f", "median=%.0f", "solveMedianMs=%.1f", "nsPerEval=%.2f", "x14worst=%.2f"):
        assert key in src
    assert '"05h-records GATE os=%s scene=cube100_lowalpha0.05_s0.3 ratio=' in src
    assert "07c1b-records stage split os=%s scene=%s 96 kHz keyless restore" in src
    assert "Assemble->Commit (synthesis + assembly + makeIrSet + D7 compare) %.1f" in src
    assert "restore median %.0f" in src
