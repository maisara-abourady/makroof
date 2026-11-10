T=/tmp/claude-0/-home-user-makroof/44ba3569-f338-5075-a142-3f82a248ebdb/tasks; cd /home/user/makroof && python3 /tmp/claude-0/extract_final.py $T/a9c47b659aa90d262.output docs/review/phase-05b2/18-seat1-T1-T2-T6.md "Seat 1 (perceptual gatekeeper) — positions on D-T1, D-T2 and D-T6" && . .venv/bin/activate && python3 - <<'EOF'
import sys; sys.path.insert(0,'.')
import numpy as np
from tools.validation import phase05b2_dt1 as dt
cs={x['name']:x for x in dt.near_wall_scenes()}
res={}
for name,c in (('W1_reference',dt.bench_scenes()[0]),('W1_listener_corner',cs['W1_listener_corner']),('CR4_ls1_mp1',[x for x in dt.bench_scenes() if x['group']=='CR4'][0]),('layout4_s1_reference',cs['layout4_s1_reference_positions'])):
    o,_,plan,_=dt.paths_run(c,32000)
    C=np.corrcoef(o.T)
    off=C[np.triu_indices(8,1)]
    res[name]={'min_corr':float(off.min()),'mean_corr':float(off.mean())}
    print(name, 'per-path contribution correlation across bands: min', round(off.min(),4), 'mean', round(off.mean(),4))
d=dt.load(); d['band_correlation']=res; dt.save(d)
EOF