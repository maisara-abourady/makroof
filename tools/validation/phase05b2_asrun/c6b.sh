T=/tmp/claude-0/-home-user-makroof/44ba3569-f338-5075-a142-3f82a248ebdb/tasks; cd /home/user/makroof && python3 /tmp/claude-0/extract_final.py $T/a1c764a24c45ec194.output docs/review/phase-05b2/18-seat6-T1-T2.md "Seat 6 (canvas designer) — positions on D-T1 and D-T2" && git add docs/review/phase-05b2 && git commit -q -m "phase-05b: D-T1/D-T2 seat 6 position

Co-Authored-By: Claude Opus 5.5 <noreply@anthropic.com>
Claude-Session: https://claude.ai/code/session_01ReHgmx1aAHGHoPiaZewQyf" && git push -q origin claude/fervent-gates-3aospw; cat > /tmp/claude-0/c6b.py <<'EOF'
import sys, json, time; sys.path.insert(0,'/home/user/makroof')
import numpy as np
from tools.validation import phase05b2_dt1 as dt
from tools.validation import scope6
from tools.acoustics import ref_hybrid as rh
m=scope6.air_m()
def clamp(c, rho=0.5):
    d=np.asarray(c['dims'],float); r=np.clip(np.asarray(c['rcv'],float), rho, d-rho); return tuple(r)
def est(c, n, nw3):
    var=rh.variant(c['alpha'],c['s'],m); plan=rh.phase04_plan(c['dims'],var,c['src'],c['rcv'])
    cc=dict(c, rcv=clamp(c)) if nw3 else c
    o,_,_,_=dt.paths_run(cc,n,plan=plan); return o,plan
w1=dt.bench_scenes()[0]
sweeps={
 'W1_off_wall_0.1_to_1.0m': [dict(w1, rcv=(10.0, 0.1+0.01*i, 1.7)) for i in range(91)],
 'W1_along_wall_at_0.1m_1m': [dict(w1, rcv=(10.0+0.01*i, 0.1, 1.7)) for i in range(101)],
 'W1_into_corner_1m_to_0.1m': [dict(w1, rcv=(1.0-0.009*i, 1.0-0.009*i, 1.7)) for i in range(101)],
}
out={}
for name,seq in sweeps.items():
    for nw3 in (False, True):
        tot={'32000':[], '256000':[], 'N2':[]}; n2s=[]
        for c in seq:
            o,plan=est(c,256000,nw3)
            for n in (32000,256000):
                tot[str(n)].append(plan['target_specular']+o[:n].sum(axis=0)*256000/n)
            n2=1000
            while True:
                s=dt.summarise(o[:n2]*256000/n2, plan)
                if np.max(s['se_db'][3:6])<=0.083 or n2>=256000: break
                n2+=1000
            tot['N2'].append(s['total']); n2s.append(n2)
        key=f"{name}_{'NW3' if nw3 else 'NW1'}"
        out[key]={k: float(np.max(np.abs(np.diff(10*np.log10(np.asarray(v)),axis=0)))) for k,v in tot.items()}
        out[key]['N2_paths_min_max']=[min(n2s),max(n2s)]
        print(key, out[key], flush=True)
# NW-3 effect in layout 4 s = 1 near walls: totals, point (4 M paths) vs clamp (1 M)
_, l4=dt.p5.layout_alpha(4)
l4s={"dims":(20.,30.,10.),"alpha":[[a]*8 for a in l4],"s":[1.0]*6,"src":(7.,20.,2.)}
for nm,rcv in (('wall',(10.,0.1,1.7)),('edge',(0.1,0.1,1.7))):
    c=dict(l4s,rcv=rcv)
    o,plan=est(c,4_000_000,False); sp=dt.summarise(o,plan)
    o2,_=est(c,1_000_000,True); sc=dt.summarise(o2,plan)
    out[f'layout4_{nm}_NW3_vs_point']={'point_total_1k':float(sp['total'][4]),'point_se_db':float(sp['se_db'][4]),'clamp_total_1k':float(sc['total'][4]),'clamp_se_db':float(sc['se_db'][4]),'change_db':float(10*np.log10(sc['total'][4]/sp['total'][4]))}
    print(nm, out[f'layout4_{nm}_NW3_vs_point'], flush=True)
d=dt.load(); d['c6b']=out; dt.save(d)
EOF
echo okimport sys, json, time; sys.path.insert(0,'/home/user/makroof')
import numpy as np
from tools.validation import phase05b2_dt1 as dt
from tools.validation import scope6
from tools.acoustics import ref_hybrid as rh
m=scope6.air_m()
def clamp(c, rho=0.5):
    d=np.asarray(c['dims'],float); r=np.clip(np.asarray(c['rcv'],float), rho, d-rho); return tuple(r)
def est(c, n, nw3):
    var=rh.variant(c['alpha'],c['s'],m); plan=rh.phase04_plan(c['dims'],var,c['src'],c['rcv'])
    cc=dict(c, rcv=clamp(c)) if nw3 else c
    o,_,_,_=dt.paths_run(cc,n,plan=plan); return o,plan
w1=dt.bench_scenes()[0]
sweeps={
 'W1_off_wall_0.1_to_1.0m': [dict(w1, rcv=(10.0, 0.1+0.01*i, 1.7)) for i in range(91)],
 'W1_along_wall_at_0.1m_1m': [dict(w1, rcv=(10.0+0.01*i, 0.1, 1.7)) for i in range(101)],
 'W1_into_corner_1m_to_0.1m': [dict(w1, rcv=(1.0-0.009*i, 1.0-0.009*i, 1.7)) for i in range(101)],
}
out={}
for name,seq in sweeps.items():
    for nw3 in (False, True):
        tot={'32000':[], '256000':[], 'N2':[]}; n2s=[]
        for c in seq:
            o,plan=est(c,256000,nw3)
            for n in (32000,256000):
                tot[str(n)].append(plan['target_specular']+o[:n].sum(axis=0)*256000/n)
            n2=1000
            while True:
                s=dt.summarise(o[:n2]*256000/n2, plan)
                if np.max(s['se_db'][3:6])<=0.083 or n2>=256000: break
                n2+=1000
            tot['N2'].append(s['total']); n2s.append(n2)
        key=f"{name}_{'NW3' if nw3 else 'NW1'}"
        out[key]={k: float(np.max(np.abs(np.diff(10*np.log10(np.asarray(v)),axis=0)))) for k,v in tot.items()}
        out[key]['N2_paths_min_max']=[min(n2s),max(n2s)]
        print(key, out[key], flush=True)
# NW-3 effect in layout 4 s = 1 near walls: totals, point (4 M paths) vs clamp (1 M)
_, l4=dt.p5.layout_alpha(4)
l4s={"dims":(20.,30.,10.),"alpha":[[a]*8 for a in l4],"s":[1.0]*6,"src":(7.,20.,2.)}
for nm,rcv in (('wall',(10.,0.1,1.7)),('edge',(0.1,0.1,1.7))):
    c=dict(l4s,rcv=rcv)
    o,plan=est(c,4_000_000,False); sp=dt.summarise(o,plan)
    o2,_=est(c,1_000_000,True); sc=dt.summarise(o2,plan)
    out[f'layout4_{nm}_NW3_vs_point']={'point_total_1k':float(sp['total'][4]),'point_se_db':float(sp['se_db'][4]),'clamp_total_1k':float(sc['total'][4]),'clamp_se_db':float(sc['se_db'][4]),'change_db':float(10*np.log10(sc['total'][4]/sp['total'][4]))}
    print(nm, out[f'layout4_{nm}_NW3_vs_point'], flush=True)
d=dt.load(); d['c6b']=out; dt.save(d)
