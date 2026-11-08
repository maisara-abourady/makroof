# Phase 07 Definition of done (D4, recorded, not gated): maximum octave-band gain of the summed omni IR
# of the extreme scene. Usage (repo root, analysis venv): python docs/review/phase-07/extreme_scene.py build/debug/render_cli <out-dir>
import json, subprocess, sys, numpy as np, soundfile as sf
cli, out = sys.argv[1], sys.argv[2]
# Extreme scene (phase-07 Definition of done, D4): 1.5 m cube, alpha = 0.01, gainDb +12 on both
# emitters, L and R at the same point 0.3 m from the listener, identical L = R input.
s = json.load(open("tests/scenes/valid/medium_room.json"))
s["room"]["geometry"]["dimensions"] = [1.5, 1.5, 1.5]
for k in s["room"]["surfaces"]:
    s["room"]["surfaces"][k]["absorption"] = [0.01] * 8
s["listener"]["position"] = [0.75, 0.6, 0.75]
for e in s["emitters"]:
    e["position"] = [0.75, 0.9, 0.75]; e["gainDb"] = 12.0
json.dump(s, open(out + "/extreme.json", "w"))
subprocess.run([cli, "--scene", out + "/extreme.json", "--mode", "omni", "--ir", out + "/extreme_ir.wav"], check=True)
ir, fs = sf.read(out + "/extreme_ir.wav", always_2d=True)
print("channels", ir.shape, "fs", fs)
h = ir[:, 0] + ir[:, 2]          # output 0: L + R paths (identical L = R input)
n = 1 << int(np.ceil(np.log2(len(h))))
H = np.fft.rfft(h, n)
f = np.fft.rfftfreq(n, 1 / fs)
P = np.abs(H) ** 2
res = {}
for fc in [63, 125, 250, 500, 1000, 2000, 4000, 8000]:
    sel = (f >= fc * 2 ** -0.25) & (f <= fc * 2 ** 0.25)   # AX14: central half octave
    res[fc] = 10 * np.log10(P[sel].mean())
for fc, g in res.items():
    print(f"{fc:5d} Hz  {g:+.1f} dB")
print(f"max octave-band gain {max(res.values()):+.1f} dB at {max(res, key=res.get)} Hz; IR length {len(h)/fs:.2f} s")
