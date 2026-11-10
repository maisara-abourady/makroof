T=/tmp/claude-0/-home-user-makroof/44ba3569-f338-5075-a142-3f82a248ebdb/tasks; cd /home/user/makroof && python3 /tmp/claude-0/extract_final.py $T/acd8867c3377ad4dd.output docs/review/phase-05b2/18-seat9-T1-T2-T6.md "Seat 9 (room acoustician) — positions on D-T1, D-T2 and D-T6" && git add docs/review/phase-05b2 tools/validation/data && git commit -q -m "phase-05b: D-T1 seats 1 and 9; band correlation of (f)

Co-Authored-By: Claude Opus 5.5 <noreply@anthropic.com>
Claude-Session: https://claude.ai/code/session_01ReHgmx1aAHGHoPiaZewQyf" && git push -q origin claude/fervent-gates-3aospw; cat > /tmp/claude-0/smallref.py <<'EOF'
import sys, json, time; sys.path.insert(0,'/home/user/makroof')
import numpy as np
from tools.validation import phase05b2_dt1 as dt
from tools.validation import scope6
from tools.acoustics import ref_hybrid as rh
m=scope6.air_m(); out={}
# (a) ref_hybrid ℓ ladder in the small Phase 04 rooms against (f)
for r in ("dead_booth","living_room","classroom","small_room"):
    si=scope6.scene_inputs(dt.REPO/"tests"/"scenes"/"valid"/f"{r}.json")
    dims=tuple(float(x) for x in si['dims']); alpha=np.asarray(si['alpha']).reshape(6,8).tolist(); s=list(np.asarray(si['s']).reshape(-1))
    var=rh.variant(alpha,s,m); plan=rh.phase04_plan(dims,var,si['src'],si['rcv'])
    t_end=plan['mix']['mixS']+0.0045
    vals={}
    for ell in (2.5,1.25,0.625,0.3125):
        if min(dims)/ell>40: continue
        rk=rh.RoomKernel(dims,ell,t_end,[var]); env,_=rh.solve(rk,rh.injection(rk,si['src'])[None,None][:, 0][None] if False else np.stack([rh.injection(rk,si['src'])]),np.stack([rh.gather_kernel(rk,si['rcv'])]))
        vals[str(ell)]={'patches':rk.N,'E_1k':float(rh.target_hybrid(plan,env[0,:,0])[4])}
        if rk.N>2500: break
    c={"dims":dims,"alpha":alpha,"s":s,"src":tuple(si['src']),"rcv":tuple(si['rcv'])}
    o,_,_,_=dt.paths_run(c,1_000_000,plan=plan); sm=dt.summarise(o,plan)
    out[r]={'dims':list(dims),'ladder':vals,'f_1M_E_1k':float(sm['total'][4]),'f_se_db':float(sm['se_db'][4])}
    print(r, dims, {k:(v['patches'],round(v['E_1k'],6)) for k,v in vals.items()}, 'f', round(sm['total'][4],6), 'SE', round(sm['se_db'][4],4), flush=True)
# (b) listener 0.1 m from the ABSORBING face: layout 4 floor, layout 5 xMin wall; point (1 M) vs NW-3 clamp
for L,rcv in ((4,(10.,8.,0.1)),(5,(0.1,8.,1.7))):
    _,al=dt.p5.layout_alpha(L)
    c={"dims":(20.,30.,10.),"alpha":[[a]*8 for a in al],"s":[1.0]*6,"src":(7.,20.,2.),"rcv":rcv}
    var=rh.variant(c['alpha'],c['s'],m); plan=rh.phase04_plan(c['dims'],var,c['src'],rcv)
    o,_,_,_=dt.paths_run(c,1_000_000,plan=plan); sp=dt.summarise(o,plan)
    cl=tuple(np.clip(np.asarray(rcv),0.5,np.asarray(c['dims'])-0.5))
    o2,_,_,_=dt.paths_run(dict(c,rcv=cl),1_000_000,plan=plan); sc=dt.summarise(o2,plan)
    out[f'layout{L}_s1_listener_at_absorber']={'point_E_1k':float(sp['total'][4]),'point_se_db':float(sp['se_db'][4]),'point_maxshare':float(sp['max_path_share'][4]),'clamp_E_1k':float(sc['total'][4]),'clamp_se_db':float(sc['se_db'][4]),'change_db':float(10*np.log10(sc['total'][4]/sp['total'][4]))}
    print(f'layout{L} at absorber', out[f'layout{L}_s1_listener_at_absorber'], flush=True)
d=dt.load(); d['seat9_checks']=out; dt.save(d)
EOF
. .venv/bin/activate && timeout 3500 python /tmp/claude-0/smallref.py 2>&1 | tail -8