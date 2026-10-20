from attempts import *
s='''extern u8 D_8004AA28,D_801D7DFC,D_801D7DF8,D_8004AC92,D_8004AC8E;
typedef struct { u32 w0,w1; } T054Gfx;
void func_8001BB64(T054Gfx **list) {
    s16 colors[3];
    s32 brightness, r,g,b;
    u8 amount,mode;
    u8 *src;
    s16 *dst;
    T054Gfx *cmd;
    if (D_8004AA28 == 0) {
        brightness = 0;
        if (D_801D7DFC > 0) brightness = (D_801D7DFC * 4 - 1) & 255;
        amount = (&D_801D7DF8)[0]; mode = (&D_801D7DF8)[1];
    } else { brightness = 0; amount = 0; mode = 0; }
    src = &D_8004AC92; dst = colors;
    do {
        *dst = *src++ + brightness;
        if (*dst >= 128) *dst = 127;
        dst++;
    } while (src != &D_8004AC92 + 3);
    cmd = (*list)++;
    cmd->w0 = 0xFB000000;
    cmd->w1 = (colors[0] << 24) | ((colors[1] & 255) << 16) | ((colors[2] & 255) << 8);
    switch (mode) {
    case 2:
        b = (&D_8004AC8E)[2] + amount * 4;
        if (b >= 128) b = 127;
        cmd = (*list)++;
        cmd->w0 = 0xFA000100;
        cmd->w1 = ((&D_8004AC8E)[1] << 16) | ((&D_8004AC8E)[0] << 24) | ((b & 255) << 8) | 255;
        break;
    case 1: case 4:
        r = (&D_8004AC8E)[0] + amount * 4;
        if (r >= 128) r = 127;
        g = (&D_8004AC8E)[1] + amount * 4;
        if (g >= 128) g = 127;
        b = (&D_8004AC8E)[2] + amount * 4;
        if (b >= 128) b = 127;
        cmd = (*list)++;
        cmd->w0 = 0xFA000100;
        cmd->w1 = (r << 24) | ((g & 255) << 16) | ((b & 255) << 8) | 255;
        break;
    default:
        r = (&D_8004AC8E)[0] + amount * 4;
        if (r >= 128) r = 127;
        cmd = (*list)++;
        cmd->w0 = 0xFA000100;
        cmd->w1 = ((&D_8004AC8E)[2] << 8) | (r << 24) | ((&D_8004AC8E)[1] << 16) | 255;
        break;
    }
}
'''
rows=[]
for tag,t in [('clean',s),('source_sentinel',s.replace('extern u8 D_8004AA28','extern u8 D_8004AC95;\nextern u8 D_8004AA28').replace('&D_8004AC92 + 3','&D_8004AC95')),('wide_amount',s.replace('u8 amount,mode;','s32 amount,mode;')),('short_channels',s.replace('s32 brightness, r,g,b;','s32 brightness; s16 r,g,b;'))]:
 r=probe(t,'func_8001BB64');rows.append({'tag':tag,**r});(ROOT/('func_8001BB64-'+tag+'.c')).write_text(t);print(tag,r.get('words'),r.get('bytes'))
(ROOT/'color_clean.json').write_text(json.dumps(rows,indent=2)+'\n')
