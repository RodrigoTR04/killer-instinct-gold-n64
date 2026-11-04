import sys, itertools, re
sys.path.insert(0,'tools/scratch/nonmatching/T-158')
sys.argv=[sys.argv[0]]
exec(open('tools/scratch/nonmatching/T-158/r2b8c12.py').read().split("keys=")[0])
base=variant(0,0,6,0,0,0)
def feat(bits):
    t=base
    a,b,c,d=bits
    if a: # drop phase
        t=t.replace("    f64 phase;\n","").replace("phase = (f64)arg3;\n    eye.y = (f32)(phase * D_80292970);","eye.y = (f32)((f64)arg3 * D_80292970);")
    if b: # drop color: inline
        t=t.replace("    u8 color;\n","").replace("color = (u16)value;","").replace("(color & 0xFF)","((u16)value & 0xFF)")
    if c: # drop eye struct -> floats ex,ey
        t=t.replace("    CameraEye eye;\n","    f32 ex; f32 ey;\n").replace("eye.x","ex").replace("eye.y","ey").replace("eye.z, ","220.0f, ").replace("    eye.z = 220.0f;\n","")
    if d: # tick directly
        t=t.replace("arg3 = D_801D30BC;","").replace("arg3","D_801D30BC").replace("D_801D30BC = ++D_801D30BC;","D_801D30BC += 1;")
    return t
keys=list(itertools.product((0,1),repeat=4))
def run2(k):
    try:
        t=feat(k); a=asm_of(t); return k,regs(a)
    except SystemExit:
        return k,None
with cf.ThreadPoolExecutor(8) as ex: res=list(ex.map(run2,keys))
for k,r in res: print(k,r)
print('---')
outs=lib.run('func_801B2B8C',[feat(k) for k in keys])
for k,r in zip(keys,outs): print(k,r)
for k in [(1,0,0,0),(0,1,1,0),(1,0,1,0),(1,1,0,0)]:
    open('tools/scratch/nonmatching/T-158/w_2b8c_np6_%s.c'%''.join(map(str,k)),'w').write(feat(k))
