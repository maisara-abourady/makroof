"""Self-test for tools/ci/check_boundaries.py: builds small source trees in a temp directory and
checks that every rule fires (and that a clean tree passes). Run: pytest tools/ci
"""

import pathlib
import sys

import pytest

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import check_boundaries  # noqa: E402


def make_tree(root: pathlib.Path, files: dict[str, str]) -> pathlib.Path:
    for relative, text in files.items():
        path = root / relative
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text, encoding="utf-8")
    return root


CLEAN = {
    "src/contract/SceneDescription.h": "#pragma once\n#include <array>\n#include \"contract/Version.h\"\n",
    "src/contract/Version.h": "#pragma once\n",
    "src/sim/Simulator.cpp": "#include \"sim/Simulator.h\"\n#include \"contract/SceneDescription.h\"\n#include <cmath>\n",
    "src/sim/Simulator.h": "#pragma once\n#include \"../contract/Version.h\"\n",
    "src/module3d/SceneModel.cpp": "#include \"module3d/SceneModel.h\"\n#include <contract/Version.h>\n",
    "src/module3d/SceneModel.h": "#pragma once\n",
    # The plugin may include everything, JUCE included.
    "src/plugin/PluginProcessor.cpp": (
        "#include <juce_audio_processors/juce_audio_processors.h>\n#include \"sim/Simulator.h\"\n"
        "#include \"module3d/SceneModel.h\"\n"
    ),
}


def run(tmp_path, extra=None):
    root = make_tree(tmp_path, {**CLEAN, **(extra or {})})
    return check_boundaries.check(root), check_boundaries.main(["--root", str(root)])


def test_clean_tree_passes(tmp_path):
    violations, code = run(tmp_path)
    assert violations == []
    assert code == 0


def test_real_repository_passes():
    assert check_boundaries.main([]) == 0


@pytest.mark.parametrize(
    "path, text, reason",
    [
        ("src/sim/Bad.cpp", '#include "module3d/SceneModel.h"\n', "src/sim must not include from src/module3d"),
        ("src/sim/Bad.cpp", '#include "plugin/PluginProcessor.h"\n', "src/sim must not include from src/plugin"),
        ("src/sim/sub/Bad.h", '#include "../../module3d/SceneModel.h"\n', "src/sim must not include from src/module3d"),
        ("src/sim/Bad.cpp", "#include <juce_core/juce_core.h>\n", "src/sim must not include JUCE"),
        ("src/sim/Bad.cpp", '#include "JuceHeader.h"\n', "src/sim must not include JUCE"),
        ("src/sim/Bad.cpp", "  #  include <juce_dsp/juce_dsp.h>\n", "src/sim must not include JUCE"),
        ("src/module3d/Bad.cpp", '#include "sim/Simulator.h"\n', "src/module3d must not include from src/sim"),
        ("src/module3d/Bad.cpp", '#include "../sim/Simulator.h"\n', "src/module3d must not include from src/sim"),
        ("src/module3d/Bad.h", "#include <plugin/PluginProcessor.h>\n", "src/module3d must not include from src/plugin"),
        ("src/contract/Bad.cpp", "#include <juce_core/juce_core.h>\n", "src/contract must not include JUCE"),
        ("src/contract/Bad.cpp", '#include "sim/Simulator.h"\n', "src/contract must not include from src/sim"),
        ("src/contract/Bad.cpp", '#include "module3d/SceneModel.h"\n', "src/contract must not include from src/module3d"),
    ],
)
def test_violation_is_reported(tmp_path, capsys, path, text, reason):
    violations, code = run(tmp_path, {path: "// header comment\n" + text})
    assert code == 1
    assert len(violations) == 1
    assert violations[0].reason == reason
    assert violations[0].line == 2
    assert path in capsys.readouterr().err


def test_commented_out_include_is_ignored(tmp_path):
    violations, code = run(tmp_path, {"src/sim/Note.h": '// #include "module3d/SceneModel.h"\n'})
    assert violations == []
    assert code == 0


def test_module3d_may_use_juce(tmp_path):
    # The rule only bans JUCE from contract and sim.
    violations, _ = run(tmp_path, {"src/module3d/Ui.cpp": "#include <juce_gui_basics/juce_gui_basics.h>\n"})
    assert violations == []


def test_missing_src_is_an_error(tmp_path):
    assert check_boundaries.main(["--root", str(tmp_path)]) == 2
