. .venv/bin/activate && python3 - <<'EOF'
import sys, json, numpy as np; sys.path.insert(0,'.')
from tools.acoustics import radiosity, ref_hybrid as rh
d=json.load(open('tools/validation/data/phase05b2_dt1.json'))
W=d['dense']['W1']
evals_w1=352**2*len(rh.lattice((20,30,10),343*0.1185).gap)*16
cost_np=W['kernel_build_s']/evals_w1
rows={}
for k,(dims,t) in {"AQ10 non-fallback":((20,30,10),0.118),"AQ10 fallback":((20,30,10),0.385),"CR4":((42.026,41.744,4.934),0.155),"100 m non-fallback":((100,100,100),1.035),"100 m fallback":((100,100,100),2.1)}.items():
    N=len(radiosity.box_patches(dims,2.5).areas); M=len(rh.lattice(dims,343*t).gap)
    ev=N*N*M*16
    rows[k]={"patches":N,"lattice_images":M,"pair_image_evals_per_generation":ev,
             "s_per_generation_numpy":ev*cost_np,"s_per_generation_at_2ns":ev*2e-9}
out={"numpy_cost_per_eval_s":cost_np,"w1_generations":W['generations'],"rows":rows,
     "note":"T1-B recomputes the patch-to-patch transfer every generation (no N²T store); time per rebuild ≈ generations × s_per_generation. 2 ns per evaluation is an assumed optimised C++ rate [Hyp]."}
d['c8']=out
# C10 classification
import glob
order=['xMin','xMax','yMin','yMax','floor','ceiling']
cls={}
for f in sorted(glob.glob('tests/scenes/valid/*.json')):
    sc=json.load(open(f)); S=sc['room']['surfaces']; A=np.array([S[k]['absorption'] for k in order])
    cls[f.split('/')[-1][:-5]]={"dims":sc['room']['geometry']['dimensions'],"uniform_alpha":bool(np.all(A==A[0])),"s":[S[k]['scattering'] for k in order]}
cls["W1 (AQ10 room)"]={"dims":[20,30,10],"uniform_alpha":True,"s":[0.3]*6}
cls["W2 (flutter)"]={"dims":[20,30,10],"uniform_alpha":False,"s":[0,0,0.1,0.1,0.1,0.1]}
cls["(A) s-cases"]={"dims":[20,30,10],"uniform_alpha":True,"s":"0.1/0.25/0.4 uniform"}
cls["(A) Table 5.2 layouts 4-6"]={"dims":[20,30,10],"uniform_alpha":False,"s":"0.1/0.25/0.4/1 uniform"}
d['c10']=cls
json.dump(d,open('tools/validation/data/phase05b2_dt1.json','w'),indent=1)
for k,v in rows.items(): print(f"{k:20s} N {v['patches']:5d} images {v['lattice_images']:5d} evals/gen {v['pair_image_evals_per_generation']:.2e} numpy {v['s_per_generation_numpy']:9.1f} s/gen  @2ns {v['s_per_generation_at_2ns']:8.2f} s/gen")
print('uniform alpha:', [k for k,v in cls.items() if v['uniform_alpha']])
EOF