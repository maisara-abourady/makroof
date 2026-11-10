T=/tmp/claude-0/-home-user-makroof/44ba3569-f338-5075-a142-3f82a248ebdb/tasks; cd /home/user/makroof && python3 /tmp/claude-0/extract_final.py $T/aca72f1785b9de0a0.output docs/review/phase-05b2/3-seat3-T5-T4.md "Seat 3 (reverb renderer) — positions on D-T5 and D-T4" && . .venv/bin/activate && python3 - <<'EOF'
import sys, json, numpy as np
sys.path.insert(0,'.')
from tools.acoustics import ref_hybrid as rh
from tools.validation import scope6
from tools.validation import phase05b2_dt1 as dt
m=scope6.air_m()
floor=[0.05,0.11,0.26,0.6,0.69,0.92,0.99,0.99]
out={}
for name,dims,src,rcv in (("open box 30x30x10 (V 9000 m3)",(30.,30.,10.),(12.,20.,3.),(15.,8.,1.7)),
                          ("open box 20x20x8 (V 3200 m3)",(20.,20.,8.),(8.,14.,3.),(10.,5.,1.7)),
                          ("open box 12x12x6 (V 864 m3)",(12.,12.,6.),(5.,8.5,2.5),(6.,3.,1.7))):
    alpha=[[1.0]*8]*4+[floor,[1.0]*8]; s=[0,0,0,0,0.4,0]
    var=rh.variant(alpha,s,m); plan=rh.phase04_plan(dims,var,src,rcv)
    mean,se,M=dt.e_diff(dims,alpha,s,m,src,rcv,plan['mix'],plan['t60'],400000)
    rd=np.linalg.norm(np.subtract(src,rcv)); direct=np.exp(-m*rd)/rd**2
    rate=rh.ENERGY_DECAY_PER_T60/plan['t60']
    tot=plan['target_specular']+mean
    lvl=10*np.log10(np.maximum(tot,1e-300)/direct); tail=10*np.log10(np.maximum(tot/(0.01*rate),1e-300)/direct)
    out[name]={'mix_s':plan['mix']['mixS'],'fallback':plan['fallback'],'tail_level_at_mix_re_direct_per10ms_db':lvl.tolist(),'tail_energy_re_direct_db':tail.tolist(),'mc_rel_se':(se/np.maximum(mean,1e-300)).tolist()}
    print(f"{name}: t_mix {plan['mix']['mixS']*1e3:.0f} ms fb {plan['fallback']}  tail energy re direct dB {np.round(tail,1)}")
d=dt.load(); d['open_boxes']=out; dt.save(d)
EOF