"""fetch_bras.py: checksums are verified and a corrupted cached file is detected (phase-05
acceptance). Offline: the archive download is replaced by a local zip, so no network is needed."""

import hashlib
import io
import json
import pathlib
import zipfile

import pytest

from tools.validation import fetch_bras


def _manifest(tmp_path: pathlib.Path) -> tuple[dict, bytes]:
    payload = b"0.05, 0.10, 0.20\n"
    buf = io.BytesIO()
    with zipfile.ZipFile(buf, "w") as z:
        z.writestr("3 Surface descriptions/_csv/initial_estimates/mat_X.csv", payload)
    (tmp_path / "archive.zip").write_bytes(buf.getvalue())
    manifest = {
        "source": {"bitstream_url": "unused/{uuid}"},
        "archives": {"archive.zip": {"uuid": "u", "kind": "zip"}},
        "files": [{
            "group": "materials", "archive": "archive.zip",
            "member": "3 Surface descriptions/_csv/initial_estimates/mat_X.csv",
            "path": "materials/initial/mat_X.csv",
            "sha256": hashlib.sha256(payload).hexdigest(), "size": len(payload),
        }],
    }
    return manifest, payload


@pytest.fixture
def local_archive(monkeypatch, tmp_path):
    """Serve archive.zip from disk instead of DepositOnce."""
    def fake_range_file(url):
        return io.FileIO(tmp_path / "archive.zip", "rb")
    monkeypatch.setattr(fetch_bras, "_HttpRangeFile", fake_range_file)


def test_fetch_verifies_and_caches(tmp_path, local_archive):
    manifest, payload = _manifest(tmp_path)
    cache = tmp_path / "cache"
    paths = fetch_bras.fetch(["materials"], cache, manifest, log=lambda *_: None)
    local = paths["materials/initial/mat_X.csv"]
    assert local.read_bytes() == payload
    # second call uses (and re-verifies) the cache: no download needed
    fetch_bras.fetch(["materials"], cache, manifest, verify_only=True, log=lambda *_: None)


def test_tampered_cache_file_is_detected(tmp_path, local_archive):
    manifest, _ = _manifest(tmp_path)
    cache = tmp_path / "cache"
    paths = fetch_bras.fetch(["materials"], cache, manifest, log=lambda *_: None)
    local = paths["materials/initial/mat_X.csv"]
    local.write_bytes(local.read_bytes().replace(b"0.05", b"0.06"))  # tamper one value
    with pytest.raises(fetch_bras.BrasChecksumError):
        fetch_bras.fetch(["materials"], cache, manifest, log=lambda *_: None)
    with pytest.raises(fetch_bras.BrasChecksumError):
        fetch_bras.fetch(["materials"], cache, manifest, verify_only=True, log=lambda *_: None)


def test_wrong_manifest_hash_rejects_download(tmp_path, local_archive):
    manifest, _ = _manifest(tmp_path)
    manifest["files"][0]["sha256"] = "0" * 64
    with pytest.raises(fetch_bras.BrasChecksumError):
        fetch_bras.fetch(["materials"], tmp_path / "cache", manifest, log=lambda *_: None)
    assert not (tmp_path / "cache" / "materials/initial/mat_X.csv").exists()


def test_committed_manifest_is_complete():
    manifest = fetch_bras.load_manifest()
    groups = {f["group"] for f in manifest["files"]}
    assert {"docs", "materials", "parameters", "rirs", "geometry"} <= groups
    for f in manifest["files"]:
        assert len(f["sha256"]) == 64 and f["size"] > 0, f["path"]
        assert f["archive"] in manifest["archives"]
    # 10 omni (dodecahedron) RIRs per CR room, CR1 excluded (coupled)
    rirs = [f["path"] for f in manifest["files"] if f["group"] == "rirs"]
    for room in ("CR2", "CR3", "CR4"):
        assert sum(p.startswith(room + "/") for p in rirs) == 10
    assert not any(p.startswith("CR1") for p in rirs)
    json.dumps(manifest)  # serialisable
