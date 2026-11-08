"""phase-05b: the compiled kernel (tools/validation/hybrid_fast.py) equals ref_hybrid.RoomKernel."""

import numpy as np
import pytest

pytest.importorskip("numba")

from tools.acoustics import ref_hybrid as rh  # noqa: E402
from tools.validation import hybrid_fast as hf  # noqa: E402
from tools.validation import phase05b as p  # noqa: E402


@pytest.mark.parametrize("name,size", [("s_case_s0.25", 5.0), ("s_case_s0.25", 2.5), ("t52_layout4_s1.0", 5.0)])
def test_fast_kernel_matches_reference(name, size):
    c = next(c for c in p.cases() if c["name"] == name)
    v0 = p.variant_of(c, np.zeros(8))
    t_end = p._case_t_end(c)
    a = rh.RoomKernel(c["dims"], size, t_end, [v0], bands=[3]).kernel(0, 0).astype(np.float64)
    b = hf.FastRoomKernel(c["dims"], size, t_end, v0, 3).kernel(0, 0).astype(np.float64)
    assert np.abs(a - b).max() <= 1e-6 * a.max()
    assert abs(b.sum() / a.sum() - 1) < 1e-7
