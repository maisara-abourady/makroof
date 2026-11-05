"""WAV helpers (soundfile). Audio arrays are float64, shape (frames,) for mono or (frames, channels)."""

from __future__ import annotations

import pathlib

import numpy as np
import soundfile as sf


def read(path: str | pathlib.Path) -> tuple[np.ndarray, int]:
    """(samples as float64 with shape (frames, channels), sample rate). Always 2-D."""
    data, fs = sf.read(str(path), dtype="float64", always_2d=True)
    return data, int(fs)


def read_float32(path: str | pathlib.Path) -> tuple[np.ndarray, int]:
    """Samples exactly as stored for float32 files (for bit-exact comparisons), shape (frames, channels)."""
    data, fs = sf.read(str(path), dtype="float32", always_2d=True)
    return data, int(fs)


def write_float32(path: str | pathlib.Path, data: np.ndarray, fs: int) -> None:
    """Write IEEE float32 WAV (the format render_cli writes)."""
    path = pathlib.Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    sf.write(str(path), np.asarray(data, dtype=np.float32), int(fs), subtype="FLOAT", format="WAV")
