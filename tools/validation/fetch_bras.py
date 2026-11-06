"""Download the parts of the BRAS dataset that Phase 05 needs, verified by SHA-256.

BRAS — Benchmark for Room Acoustical Simulation (Aspöck, Brinkmann, Ackermann, Weinzierl,
Vorländer; TU Berlin / RWTH Aachen), DepositOnce, DOI 10.14279/depositonce-6726.3, licence
CC BY-SA 4.0. The data is never committed to this repository (CLAUDE.md); it is cached under
``~/.cache/makroof/bras`` (override with ``MAKROOF_BRAS_CACHE`` or ``--cache``).

The dataset is published as large zip archives (0.4–0.8 GB per room). Only a few members of each
are needed (material tables, omni RIRs, geometry), so this script reads each archive's central
directory with HTTP range requests and extracts just those members. Every file is checked against
the SHA-256 in ``bras_manifest.json``; zipfile also checks each member's CRC-32 from the archive.
A cached file is re-verified on every use, so a corrupted or tampered cache is detected
(``BrasChecksumError``) instead of being used.

Usage::

    python tools/validation/fetch_bras.py                    # fetch + verify the default groups
    python tools/validation/fetch_bras.py --groups rirs      # only some groups
    python tools/validation/fetch_bras.py --verify-only      # verify the cache, no network
    python tools/validation/fetch_bras.py --record           # maintainer: (re)record SHA-256s

Stdlib only, so the nightly job needs nothing beyond the analysis requirements.
"""

from __future__ import annotations

import argparse
import hashlib
import io
import json
import os
import pathlib
import sys
import time
import urllib.error
import urllib.request
import zipfile

HERE = pathlib.Path(__file__).resolve().parent
MANIFEST = HERE / "bras_manifest.json"
DEFAULT_GROUPS = ("docs", "materials", "parameters", "rirs")


class BrasChecksumError(RuntimeError):
    """A file's SHA-256 does not match the manifest."""


class BrasFetchError(RuntimeError):
    """A download failed or the archive does not contain an expected member."""


def cache_dir(override: str | os.PathLike | None = None) -> pathlib.Path:
    if override:
        return pathlib.Path(override)
    env = os.environ.get("MAKROOF_BRAS_CACHE")
    if env:
        return pathlib.Path(env)
    return pathlib.Path.home() / ".cache" / "makroof" / "bras"


def load_manifest(path: pathlib.Path = MANIFEST) -> dict:
    with open(path, encoding="utf-8") as f:
        return json.load(f)


def sha256_file(path: pathlib.Path) -> str:
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def _open_url(url: str, headers: dict | None = None, retries: int = 4):
    delay = 2.0
    for attempt in range(retries + 1):
        try:
            req = urllib.request.Request(url, headers={"User-Agent": "makroof-validation", **(headers or {})})
            return urllib.request.urlopen(req, timeout=120)
        except (urllib.error.URLError, TimeoutError, ConnectionError) as e:
            if attempt == retries:
                raise BrasFetchError(f"{url}: {e}") from e
            time.sleep(delay)
            delay *= 2
    raise AssertionError("unreachable")


class _HttpRangeFile(io.RawIOBase):
    """Seekable read-only view of a remote file through HTTP Range requests."""

    def __init__(self, url: str):
        super().__init__()
        self.url = url
        self.pos = 0
        with _open_url(url, {"Range": "bytes=0-0"}) as r:
            cr = r.headers.get("Content-Range")
            if r.status != 206 or not cr:
                raise BrasFetchError(f"{url}: server does not honour range requests")
            self.size = int(cr.split("/")[1])

    def readable(self) -> bool:
        return True

    def seekable(self) -> bool:
        return True

    def tell(self) -> int:
        return self.pos

    def seek(self, offset: int, whence: int = io.SEEK_SET) -> int:
        base = {io.SEEK_SET: 0, io.SEEK_CUR: self.pos, io.SEEK_END: self.size}[whence]
        self.pos = base + offset
        return self.pos

    def readinto(self, buf) -> int:
        n = len(buf)
        if n == 0 or self.pos >= self.size:
            return 0
        end = min(self.size, self.pos + n) - 1
        with _open_url(self.url, {"Range": f"bytes={self.pos}-{end}"}) as r:
            data = r.read()
        buf[: len(data)] = data
        self.pos += len(data)
        return len(data)


def _bitstream_url(manifest: dict, uuid: str) -> str:
    return manifest["source"]["bitstream_url"].format(uuid=uuid)


def _local_path(cache: pathlib.Path, entry: dict) -> pathlib.Path:
    return cache / entry["path"]


def verify(entry: dict, path: pathlib.Path) -> None:
    got = sha256_file(path)
    if got != entry["sha256"]:
        raise BrasChecksumError(
            f"{path}: SHA-256 {got} does not match the manifest ({entry['sha256']}); "
            "delete the file and fetch again"
        )


def _write_atomic(path: pathlib.Path, data: bytes) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    tmp = path.with_suffix(path.suffix + ".part")
    tmp.write_bytes(data)
    tmp.replace(path)


def fetch(groups=DEFAULT_GROUPS, cache: pathlib.Path | None = None, manifest: dict | None = None,
          record: bool = False, verify_only: bool = False, log=print) -> dict[str, pathlib.Path]:
    """Ensure every manifest file in ``groups`` is cached and verified; return {path: local path}.

    A cached file whose SHA-256 differs from the manifest raises BrasChecksumError (it is never
    silently replaced: a tampered or corrupted cache must be noticed). ``record`` (maintainer only)
    writes the SHA-256 of freshly downloaded files into the manifest instead of checking them.
    """
    manifest = manifest if manifest is not None else load_manifest()
    cache = cache or cache_dir()
    out: dict[str, pathlib.Path] = {}
    by_archive: dict[str, list[dict]] = {}
    for entry in manifest["files"]:
        if entry["group"] not in groups:
            continue
        local = _local_path(cache, entry)
        out[entry["path"]] = local
        if local.exists() and not record:
            verify(entry, local)
            continue
        if verify_only:
            raise BrasFetchError(f"{local}: not in the cache (run fetch_bras.py without --verify-only)")
        by_archive.setdefault(entry["archive"], []).append(entry)

    for archive_name, entries in by_archive.items():
        archive = manifest["archives"][archive_name]
        url = _bitstream_url(manifest, archive["uuid"])
        if archive.get("kind") == "file":
            for entry in entries:
                log(f"download {archive_name}")
                with _open_url(url) as r:
                    data = r.read()
                if archive.get("md5") and hashlib.md5(data).hexdigest() != archive["md5"]:
                    raise BrasChecksumError(f"{archive_name}: MD5 does not match the repository's checksum")
                _store(entry, data, cache, record, log)
            continue
        log(f"open {archive_name} (range requests)")
        with zipfile.ZipFile(io.BufferedReader(_HttpRangeFile(url), 1 << 20)) as z:
            names = {i.filename: i for i in z.infolist()}
            for entry in entries:
                member = entry["member"]
                if member not in names:
                    raise BrasFetchError(f"{archive_name}: no member {member!r}")
                log(f"  extract {member}")
                data = z.read(names[member])  # checks the member's CRC-32
                _store(entry, data, cache, record, log)
    if record:
        with open(MANIFEST, "w", encoding="utf-8") as f:
            json.dump(manifest, f, indent=2, ensure_ascii=False)
            f.write("\n")
    return out


def _store(entry: dict, data: bytes, cache: pathlib.Path, record: bool, log) -> None:
    digest = hashlib.sha256(data).hexdigest()
    if record:
        entry["sha256"] = digest
        entry["size"] = len(data)
    elif digest != entry["sha256"]:
        raise BrasChecksumError(f"{entry['path']}: downloaded SHA-256 {digest} != manifest {entry['sha256']}")
    _write_atomic(_local_path(cache, entry), data)


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--groups", nargs="+", default=list(DEFAULT_GROUPS),
                    help="manifest groups (docs materials parameters rirs geometry)")
    ap.add_argument("--cache", help="cache directory (default ~/.cache/makroof/bras)")
    ap.add_argument("--verify-only", action="store_true", help="verify the cache; no network")
    ap.add_argument("--record", action="store_true", help="maintainer: record SHA-256s into the manifest")
    args = ap.parse_args(argv)
    try:
        paths = fetch(args.groups, cache_dir(args.cache), record=args.record, verify_only=args.verify_only)
    except (BrasChecksumError, BrasFetchError) as e:
        print(f"error: {e}", file=sys.stderr)
        return 2
    print(f"ok: {len(paths)} files verified in {cache_dir(args.cache)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
