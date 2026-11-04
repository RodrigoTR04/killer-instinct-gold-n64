import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
s=open('tools/scratch/nonmatching/T-158/w_2b8c_dw.c').read()
old="if (D_801D3094 < 0) D_802C87D0 = D_801D3094 + 255; else D_802C87D0 = 255;"
assert old in s
alts={
'base':old,
'tern':"D_802C87D0 = (D_801D3094 < 0) ? D_801D3094 + 255 : 255;",
'tern2':"D_802C87D0 = D_801D3094 < 0 ? (s16)(D_801D3094 + 255) : 255;",
'neg':"if (D_801D3094 >= 0) D_802C87D0 = 255; else D_802C87D0 = D_801D3094 + 255;",
'neg2':"if (!(D_801D3094 < 0)) { D_802C87D0 = 255; } else { D_802C87D0 = D_801D3094 + 255; }",
'sh':"D_802C87D0 = 255; if (D_801D3094 < 0) D_802C87D0 = D_801D3094 + 255;",
'sh2':"if (D_801D3094 < 0) { D_802C87D0 = D_801D3094 + 255; } else { D_802C87D0 = 255; }",
'le0':"if (D_801D3094 <= -1) D_802C87D0 = D_801D3094 + 255; else D_802C87D0 = 255;",
'cast':"if ((s32)D_801D3094 < 0) D_802C87D0 = (s32)D_801D3094 + 255; else D_802C87D0 = 255;",
}
cands=[(k,s.replace(old,a)) for k,a in alts.items()]
out=lib.run('func_801B2B8C',[c[1] for c in cands])
for r,(k,x) in zip(out,cands): print(r,k)
