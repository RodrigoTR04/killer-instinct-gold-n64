"""Adapt old drafts to established declarations, without changing production TUs."""
import re

def reconcile(fn,s):
 changes=[]
 n=fn[8:]
 # Reuse the established stage layouts rather than introducing identical copies.
 for typename in re.findall(r'typedef struct \{ void \*display; s16 flags, pad; s32 transform; \} (\w+);',s):
  if n not in ['12B7C','131A4','1346C','1373C']:
   s=re.sub(r'typedef struct \{ void \*display; s16 flags, pad; s32 transform; \} '+typename+';', '',s).replace(typename,'T0331383CStagePart')
 for typename in re.findall(r'typedef struct \{ f32 pitch, yaw, roll, speed, scale; \} (\w+);',s):
  if n not in ['12B7C','131A4','1346C','1373C']:
   s=re.sub(r'typedef struct \{ f32 pitch, yaw, roll, speed, scale; \} '+typename+';', '',s).replace(typename,'T0331383CStageRotation')
 if n in ['12B7C','131A4']:
  s=s.replace('extern s8 D_8004A730, D_8004A5E0;','').replace('extern s8 D_8004A738, D_8004A688;','')
  s=s.replace('(&D_8004A738)[','D_8004A738[').replace('(&D_8004A688)[i * 7 + part]','D_8004A688[i][part]')
 if n=='1373C':changes=[('extern void func_8001373C(void *, f32, f32, f32, s32, s32, s32);','extern void func_8001373C(T020ForceTarget *, f32, f32, f32, u8, u8, u8);')]
 if n=='15450':
  # Keep the extended rotating-object view; the established actor is a partial view.
  s=s.replace('extern T033RotatingObject D_801D3430[], D_801D5C30[];', 'extern T033RotatingObject D_801D5C30[];').replace('obj = D_801D3430;', 'obj = (T033RotatingObject *)D_801D3430;')
 if n=='15594':
  decl='typedef struct { u32 command,value; } T03315594Command;'
  s=s.replace(decl,'');changes=[('extern void func_80015594();',decl+'\nextern void func_80015594(T03315594Command **,s32 *,f32,s32,f32,f32,f32);')]
 if n in ['17A68','1808C','18AE0','193DC']:
  for name in ['D_8004A5E0','D_8004A730','D_8004A738','D_8004AC89','D_8004AC8A','D_8004AA29','D_8004AC8D','D_800614D8','D_80061520','D_80061CB8']:
   s=re.sub(r'extern (?:s8|u8) '+name+r';','',s)
  for name in ['D_8004A730','D_8004A738']:s=re.sub(name+r'\s*=',name+'[0] =',s)
  s=re.sub(r'D_8004A5E0\s*=', 'D_8004A5E0[0][0] =',s)
 if n=='1808C':
  s=s.replace('typedef struct { u8 pad[0x28]; s16 x, y, z; } T022Position;','').replace('T022Position','T020Position')
 if n=='191F0':s=s.replace('extern u8 D_801D3430;','').replace('&D_801D3430','(u8 *)D_801D3430')
 if n=='1BB64':s=s.replace('D_801D7DF8,D_8004AC92,D_8004AC8E;','D_801D7DF8;').replace('&D_8004AC92','D_8004AC92').replace('(&D_8004AC8E)','D_8004AC8E')
 if n=='1D47C':s=s.replace('extern u8 D_8004CE90[];','').replace('+ D_8004CE90','+ (u8 *)D_8004CE90')
 if n in ['1D080','1CD50']:
  sprite=re.search(r'typedef struct \{.*?\} T022Sprite;',s,re.S).group(0)
  s=s.replace(sprite,'');changes.append(('extern void func_8001C05C(u8 *);','extern void func_8001C05C(u8 *);\n'+sprite+'\nextern T022Sprite D_8004CED0[];'))
  changes.insert(0, (sprite, ''))
 if n=='1D080':s='extern u8 D_8004AC88;\n'+s
 if n=='1CD50':
  s='extern u8 D_8004EA9C[];\n'+s
  s=s.replace('s32 func_8001CF1C(s8 *, u8 *, s8 *, s32);','void func_8001CF1C(void);').replace('s32 func_8001D080();','void func_8001D080(void);').replace('s32 func_8001D37C(u8, u8);','void func_8001D37C(u8, u8);')
  s=s.replace('func_8001CF1C(&D_8004F398, &D_8004F396, &D_8004F395, 1);','func_8001CF1C();')
 if n=='21B6C':
  s='typedef struct { u8 pad[0x28]; s16 x,y,z; } T020Position;\n'+s
  s=s.replace('func_800249DC(u8,u8,u8 *)','func_800249DC(s32,s32,u8 *)')
 if n in ['17A68','1808C','18AE0','193DC']:
  s=s.replace('(&D_8004A5E0)[','((s8 *)D_8004A5E0)[')
 if n=='1808C':changes.append(('void func_800183CC(T022Position *arg0)', 'void func_800183CC(T020Position *arg0)'))
 if n=='15450':s='extern u8 D_801D3430[];\n'+s
 if n=='21B6C':s='extern u8 D_8004AC88,D_8004AA28,D_8004A9D8,D_8004A998,D_8004AC89;\n'+s
 if n in ['1D7E4','241BC','245B4','24714','21B6C','216D4']:
  # The newly integrated bank view is only a prefix view of this larger cache.
  changes.append(('extern struct { u8 pad[0x12A8]; T032Bank banks[2]; } D_8004D278;', 'extern u8 D_8004D278[];'))
  changes.append(('D_8004D278.banks[player].data', '((T032Bank *)(D_8004D278 + 0x12A8))[player].data'))
  changes.append(('D_8004D278.banks[player].zero', '((T032Bank *)(D_8004D278 + 0x12A8))[player].zero'))
  if n in ['1D7E4','245B4','21B6C','216D4']:changes.append(('extern u8 D_8004D278[];', ''))
 if n=='1D7E4':s=s.replace('extern s32 func_800244F0(s32);','void func_800244F0(s32);')
 if n=='245B4':changes.append(('extern void func_800245B4(s32, void *, s32);','extern void func_800245B4(s32, u32, s32);'))
 if n=='1CD50':s=s.replace('extern s8 D_8004F394;', 'extern u8 D_8004F394;')
 if n=='15450':
  s=s.replace('extern u8 D_801D3430[];', 'extern T033RotatingObject D_801D3430[];').replace('extern T033RotatingObject D_801D3430[];\n','')
  at=s.index('extern T033RotatingObject D_801D5C30[];');s=s[:at]+'extern T033RotatingObject D_801D3430[];\n'+s[at:]
  changes.append(('extern T05518664Obj D_801D3430[40];',''))
  changes.append(('((u8 *)D_801D3430)', '((u8 *)D_801D3430)'))
 if n=='245B4':
  decl='extern T032Cache245 D_8004D278[];'
  s=s.replace(decl,'');changes.append(('typedef struct { s32 zero; void *data; } T032Bank;', 'typedef struct { s32 zero; void *data; } T032Bank;\ntypedef struct { u8 *data; s32 offset; } T032Cache245;\n'+decl))
  s=s.replace('typedef struct { u8 *data; s32 offset; } T032Cache245;','')
 if n=='21B6C':
  s='extern u8 D_8004AC8A;\n'+s;s=s.replace('D_8004EA9A,','').replace('extern s8 D_8004EAB8', 'extern s8 D_8004EAB8')
 if n=='170C4':
  for decl in ['extern u8 D_80045030;','extern T033170C4Vertex *D_80045060;','extern u8 D_8004AC8D;','extern T033170C4Vertex D_8004AD28;','extern T033170C4Vertex D_8004ADE8;','extern T033170C4Object D_801D3430;']:s=s.replace(decl,'')
  s=s.replace('T033170C4Vertex','T05516BE0Vtx').replace('var_s','var_s')
  s=s.replace('*D_80045060', '*D_80045060[0]').replace('&D_8004ADE8', 'D_8004ADE8').replace('&D_8004AD28','D_8004AD28').replace('= D_8004ADE8;', '= D_8004ADE8[0];').replace('&D_80045030','D_80045030')
  s=s.replace('&D_801D3430','(T033170C4Object *)D_801D3430')
 if n=='170C4':s=s.replace('typedef struct { s32 words[4]; } T05516BE0Vtx;','')
 if n=='1D7E4':s=s.replace('s32 func_800244F0(u8, u8);','void func_800244F0(s32);').replace('func_800244F0(temp_t6, temp_t6);','func_800244F0(temp_t6);')
 if n=='21B6C':s='extern u8 D_8004EA9A;\n'+s
 return s,changes
