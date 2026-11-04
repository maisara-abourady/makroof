"""The JSON Schema (docs/contract/scene-v1.schema.json) and the C++ contract reader agree on every
fixture in tests/scenes/.

- Every valid fixture is accepted by the schema (the C++ side is tests/unit/test_contract_roundtrip.cpp).
- Every invalid fixture is rejected by the schema, except those listed in
  tests/scenes/invalid/_cppOnly.json: their rule (geometry) cannot be written in JSON Schema, so the
  schema must ACCEPT them. That keeps the sidecar list honest in both directions.
- A fixture that is not even JSON (E_JSON_SYNTAX) counts as rejected.

Run: pytest tools/ci
"""

import json
import pathlib

import jsonschema
import pytest

REPO = pathlib.Path(__file__).resolve().parents[2]
SCHEMA_PATH = REPO / "docs" / "contract" / "scene-v1.schema.json"
SCENES = REPO / "tests" / "scenes"
CPP_ONLY_PATH = SCENES / "invalid" / "_cppOnly.json"


def fixtures(kind: str) -> list[pathlib.Path]:
    return sorted(p for p in (SCENES / kind).glob("*.json") if not p.name.startswith("_"))


def cpp_only() -> set[str]:
    return set(json.loads(CPP_ONLY_PATH.read_text(encoding="utf-8"))["fixtures"])


@pytest.fixture(scope="module")
def validator() -> jsonschema.Draft202012Validator:
    schema = json.loads(SCHEMA_PATH.read_text(encoding="utf-8"))
    jsonschema.Draft202012Validator.check_schema(schema)
    return jsonschema.Draft202012Validator(schema)


def load(path: pathlib.Path):
    """Returns the parsed document, or None when the file is not valid JSON."""
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except json.JSONDecodeError:
        return None


def test_schema_is_draft_2020_12():
    schema = json.loads(SCHEMA_PATH.read_text(encoding="utf-8"))
    assert schema["$schema"] == "https://json-schema.org/draft/2020-12/schema"


def test_fixture_counts():
    assert len(fixtures("valid")) >= 5
    assert len(fixtures("invalid")) >= 15


def test_cpp_only_list_names_existing_fixtures():
    names = {p.name for p in fixtures("invalid")}
    missing = cpp_only() - names
    assert not missing, f"_cppOnly.json lists fixtures that do not exist: {sorted(missing)}"


@pytest.mark.parametrize("path", fixtures("valid"), ids=lambda p: p.name)
def test_schema_accepts_valid_fixture(validator, path):
    doc = load(path)
    assert doc is not None, f"{path.name} is not valid JSON"
    errors = [f"{'/'.join(map(str, e.absolute_path))}: {e.message}" for e in validator.iter_errors(doc)]
    assert not errors, f"{path.name} rejected by the schema:\n" + "\n".join(errors)


@pytest.mark.parametrize("path", fixtures("invalid"), ids=lambda p: p.name)
def test_schema_agrees_on_invalid_fixture(validator, path):
    doc = load(path)
    schema_accepts = doc is not None and validator.is_valid(doc)
    if path.name in cpp_only():
        assert schema_accepts, (
            f"{path.name} is listed as C++-only, but the schema rejects it: either the fixture breaks "
            "more than one rule or the rule can be expressed in the schema"
        )
    else:
        assert not schema_accepts, f"{path.name} breaks a rule the schema can express, but the schema accepts it"
