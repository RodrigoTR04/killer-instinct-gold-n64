/* DRAFT. Remaining diff: 120 positional differing words; 448/480 bytes */
typedef struct { u32 command, value; } T033DisplayCommand;
extern u8 D_80044A24, D_8004AA28, D_8004ACC5, D_8004ACC6, D_8004ACC7;
extern u32 D_8004A428[];
extern T033DisplayCommand D_80068930[][200];

void func_80016078(T033DisplayCommand **arg0, s32 *arg1, s32 arg2, s32 arg3) {
    T033DisplayCommand *g;
    s32 color;
    g = D_80068930[D_80044A24];
    *arg0 = g;
    g->command = 0xE7000000;
    g->value = 0;
    g++;
    g->command = 0xED000000;
    g->value = (((s32)((f32)(320 << D_8004AA28) * 4.0f) & 0xFFF) << 12) |
               ((s32)((f32)(240 << D_8004AA28) * 4.0f) & 0xFFF);
    g++;
    g->value = 0xFFFE793C;
    g->command = 0xFCFFFFFF;
    g++;
    g->command = (((320 << D_8004AA28) - 1) & 0xFFF) | 0xFF100000;
    g->value = D_8004A428[D_80044A24];
    g++;
    g->command = 0x2F300000;
    g->value = 0;
    g++;
    g->command = 0xF7000000;
    color = ((D_8004ACC5 << 8) & 0xF800) | ((D_8004ACC6 << 3) & 0x7C0) | ((D_8004ACC7 >> 2) & 0x3E) | 1;
    g->value = (color << 16) | color;
    g++;
    g->value = 0;
    g->command = (((((320 << D_8004AA28) - 1) & 0x3FF) << 14) | 0xF6000000 |
                  ((((240 << D_8004AA28) - 1) & 0x3FF) << 2));
    g++;
    g->command = 0xE9000000;
    g->value = 0;
    g++;
    *arg1 = (g - *arg0) * 8;
}
