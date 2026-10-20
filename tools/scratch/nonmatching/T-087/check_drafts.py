"""Check all remaining assigned drafts in their complete production TUs.
Scores mask ELF relocations and include the instruction-count delta. They do
not establish resolved-image matching or rodata placement.
"""
import pathlib,re,sys
sys.path.insert(0,str(pathlib.Path(__file__).parent))
import full,tu
names=['801ACB1C','801AD114','801AD7D8','801ADA04','801CC3BC','801CC908',
       '801CCD74','801CD1F0','801AF68C','801C6D40','801C67CC',
       '801C4240','801C7310']
for name in names:
    fn='func_'+name
    path=tu.draft(fn)
    source=path.read_text()
    changes=[]
    if name=='801ACB1C':
        # Reuse the owning render layout; the later production declarations
        # use different names for the same command and context pointers.
        source=re.sub(r'typedef struct \{\s*s32 unk0;\s*s32 unk4;\s*\} T034GameState;','',source)
        source=source.replace('T034GameState','RenderState').replace('.unk0','.index')
        source=source.replace('T034Gfx','DisplayCommand')
        source=re.sub(r'typedef struct \{\s*u32 w0;\s*u32 w1;\s*\} DisplayCommand;',
                      'typedef struct DisplayCommand { u32 w0, w1; } DisplayCommand;',source)
        changes=[('typedef struct DisplayCommand { u32 w0, w1; } DisplayCommand;','')]
    if name=='801CCD74':
        # The existing rendering caller transports the pointer through s32.
        source=source.replace('u8 **arg0','s32 *arg0').replace('*arg0 = var_v1','*arg0 = (s32)var_v1')
    if name=='801AF68C':
        changes=[('extern s32 D_802A1A60[];','extern T025EffectF68C *D_802A1A60[];'),
                 ('D_802A1A60[D_802A1A80] = arg0;',
                  'D_802A1A60[D_802A1A80] = (T025EffectF68C *)arg0;')]
    if name=='801C6D40':
        source=source.replace('extern f32 D_802D3990;','').replace('D_802D3990 =','D_802D3990.x =')
    result=full.check(fn,source,changes)
    print(fn,result,flush=True)
    if result is None:sys.exit(1)
