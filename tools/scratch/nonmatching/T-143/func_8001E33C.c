/* T-081 DRAFT: measured in owning TU; see T-081/REPORT.md. */
extern f32 D_8004A7A0[],D_8004A740[],D_8004A800[],D_8004A920[],D_8004A8C0[];
extern u8 D_8004AC88,D_8004A401; extern s32 D_800698C4;
typedef struct
{
    u32 w0, w1;
}
T081Gfx;
s32 func_8001346C(T081Gfx **, s32, s32);
void func_80016760(s32);

void func_80024B0C();
s32 func_8002F6F4(s32, s16, u8 *);
extern u8 D_80044DD4;
extern u8 D_8004A264;
extern u8 D_8004A40C;
typedef struct
{
    u8 pad[12];
    f32 x,y,z;
    u8 pad18[9];
    u8 flip;
    u16 kind;
    u8 pad24[4];
    s16 red,green,blue;
    u8 pad2e[2];
}
T081Object;

extern s16 D_8004D26E;
extern u8 D_8004D270;
extern s32 D_8004EA78;
extern u8 D_8004EAB9;
extern u8 D_8004F390;
extern s32 D_80066C40;
extern u8 D_801D3430;
extern u8 D_801D8771;
extern u8 D_801D8798;
extern u8 D_801D87AC;
extern u8 D_801D87E0;
void func_8001E33C(T081Gfx **arg0, u8 arg1)
{
    T081Gfx *command;
    s16 sp96;
    s16 sp94;

    s16 sp90;
    s16 sp8E;


    s32 sp84;
    s32 sp80;
    s32 sp7C;

    u8 *sp3C;

    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f2;
    s16 temp_t0;
    s16 temp_v0_10;
    s16 temp_v0_11;
    s16 temp_v0_9;
    s16 var_ra;
    s16 var_t4;
    s16 var_t5;
    s32 temp_t1_2;
    s32 var_a1;
    s32 var_t0;
    u16 var_t1;
    u16 var_t2;
    u32 temp_a3_2;
    u32 temp_t1;
    u8 *temp_t2;
    
    u8 temp_t6;
    u8 temp_t9;
    u8 temp_v0_8;
    u8 var_a2;
    u8 var_v1;
    T081Object *temp_a1;
    T081Object *temp_a1_2;
    T081Object *temp_a1_3;
    u8 *var_t3;
    u8 *var_t3_2;
    var_a2 = arg1;
    var_t3 = (var_a2 << 8) + &D_801D3430;
    
    if ((*(u8 *)((u8 *)(var_t3) + -0x17C)) != 0)
    {
        arg1 = var_a2;

        func_80016760(1);
        var_t3_2 = var_t3;
        if ((*(u8 *)((u8 *)(var_t3_2) + -0x17A)) != 0)
        {
            temp_a1 = &((T081Object *)D_8004A450)[arg1];
            D_8004A7A0[2] = (f32) temp_a1->y;
            D_8004A740[2] = (f32) temp_a1->x;
            D_8004A800[2] = (f32) temp_a1->z;
            if (D_8004A7A0[2] != 0.0f)
            {
                if ((D_801D87AC == 0) && (D_8004A40C == 0))
                {
                    if ((*(s16 *)((u8 *)(var_t3_2) + 0x7C)) > 0)
                    {
                        D_8004A920[2] = (f32) (D_8004A920[2] - 6.0f);
                    }
                    else
                    {
                        D_8004A920[2] = (f32) (D_8004A920[2] + 6.0f);
                    }
                }
            }
            else if (D_8004EAB9 == 0)
            {
                D_8004EAB9 = 1;

                func_8002F6F4(D_80066C40, 8, &D_8004A264);
            }
            if (D_8004A920[2] < 0.0f)
            {
                D_8004A920[2] = (f32) (D_8004A920[2] + 360.0f);
            }
            else if (359.0f < D_8004A920[2])
            {
                D_8004A920[2] = (f32) (D_8004A920[2] - 360.0f);
            }
        }
        else
        {
            temp_a1_2 = &((T081Object *)D_8004A450)[arg1];
            temp_f2 = temp_a1_2->y;
            temp_f0 = temp_a1_2->x;
            temp_f12 = temp_a1_2->z;
            D_8004EAB9 = 0;
            D_8004A7A0[2] = (f32) (temp_f2 + 100.0f);
            D_8004A7A0[0] = temp_f2;
            D_8004A7A0[1] = temp_f2;
            D_8004A740[0] = temp_f0;
            D_8004A740[1] = temp_f0;
            D_8004A740[2] = temp_f0;
            D_8004A800[0] = temp_f12;
            D_8004A800[1] = temp_f12;
            D_8004A800[2] = temp_f12;
            if ((*(u8 *)((u8 *)(&D_801D8798) + 0xC)) != 0)
            {
                (*(u8 *)((u8 *)(&D_801D8798) + 0xC)) = 0U;
                D_8004A8C0[1] = 0.0f;
                D_8004A8C0[2] = 0.0f;
                D_8004A920[2] = 0.0f;
            }
        }
        var_t0 = 0;
        do
        {
            if (var_t0 == 0)
            {
                var_a1 = 0x11;
            }
            else
            {
                var_a1 = var_t0 + 0x14;
            }
            if ((var_t0 == 2) || ((*(u8 *)((u8 *)(var_t3_2) + -0x17A)) == 0))
            {
                command = *arg0;
                *arg0 = command + 1;
                command->w1 = 0;
                command->w0 = 0xE7000000;
                command = *arg0;
                *arg0 = command + 1;
                command->w1 = 0x80000;
                command->w0 = 0xBA001301;

                func_8001346C(arg0, var_a1, 0);
                command = *arg0;
                *arg0 = command + 1;
                command->w0 = 0xE7000000;
                command->w1 = 0;
                command = *arg0;
                *arg0 = command + 1;
                command->w1 = 0;
                command->w0 = 0xBA001301;
            }
            var_t0 += 1;
        }
        while (var_t0 != 3);
        return;
    }
    if ((var_a2 == 1) && (D_8004AC88 == 0xC))
    {
        arg1 = var_a2;
        sp3C = (u8 *) var_a2;

        func_80016760(3);
        var_a2 = arg1;
    }
    temp_a1_3 = &((T081Object *)D_8004A450)[var_a2];
    if (temp_a1_3->kind == 0xBE)
    {
        command = *arg0;
        *arg0 = command + 1;
        command->w1 = 0;
        command->w0 = 0xE7000000;
        command = *arg0;
        *arg0 = command + 1;
        command->w1 = 0xFF;
        command->w0 = 0xFA000100;
        func_80024B0C(arg0, var_a2 ^ 1);
        return;
    }
    var_t1 = (*(u16 *)((u8 *)(var_t3) + 0x58));
    var_t2 = (*(u16 *)((u8 *)(var_t3) + 0x5A));
    if (var_t1 == 0)
    {
        var_t1 = 0x1000;
    }
    if (var_t2 == 0)
    {
        var_t2 = 0x1000;
    }
    command = *arg0;
    *arg0 = command + 1;
    command->w1 = 0;
    command->w0 = 0xE7000000;
    if ((s32) temp_a1_3->flip >= 0x80)
    {
        sp7C = 1;
    }
    else
    {
        sp7C = 0;
    }
    D_8004EA78 = (s32) var_a2;
    temp_t0 = D_8004CED0[var_a2].flags;
    var_ra = temp_t0;
    if ((*(u8 *)((u8 *)(var_t3) + 0x95)) & 0x10)
    {
        var_ra = 3;
        if (temp_a1_3->kind == 0)
        {
            var_v1 = D_8004D270;
            if ((s32) D_8004D270 > 0)
            {
                temp_t9 = D_8004D270 - 1;
                D_8004D270 = temp_t9;
                var_v1 = temp_t9 & 0xFF;
            }
        }
        else
        {
            var_v1 = D_8004D270;
            if ((s32) D_8004D270 < 0x10)
            {
                temp_t6 = D_8004D270 + 1;
                D_8004D270 = temp_t6;
                var_v1 = temp_t6 & 0xFF;
            }
        }
        D_8004D26E = (s16) var_v1;
    }
    else if (D_8004EA9E[var_a2] == 9)
    {
        D_8004D26E = 0xB0;
    }
    else
    {
        D_8004D26E = 0xFF;
    }
    if ((D_8004A401 == 4) && ((*(&D_80044DD4 + D_8004AC88) & 0x10) == 0x10) && (D_800698C4 < 0x80) && (var_a2 == D_801D8771))
    {
        var_ra = 3;
        D_8004D26E = D_800698C4 * 2;
    }
    if (((var_a2 + 1) == (*(u8 *)((u8 *)(&D_801D87E0) + 0))) && ((*(u8 *)((u8 *)(&D_801D87E0) + 1)) != 0))
    {
        var_ra = 3;
        D_8004D26E = (D_8004D26E - ((*(u8 *)((u8 *)(&D_801D87E0) + 1)) * 4)) + 1;
    }
    temp_v0_8 = (*(u8 *)((u8 *)(var_t3) + -0x170));
    if (temp_v0_8 != 0)
    {
        var_ra = 3;
        if ((s32) temp_v0_8 < 0x40)
        {
            D_8004D26E = 0x100 - (temp_v0_8 * 4);
        }
        else
        {
            D_8004D26E = 0;
        }
    }
    if (D_8004D26E < 0)
    {
        D_8004D26E = 0;
    }
    if (temp_t0 != 5)
    {
        temp_v0_9 = temp_a1_3->red;
        sp3C = &D_8004EA9E[var_a2];
        if (temp_v0_9 >= 0)
        {
            sp96 = temp_v0_9;
            sp90 = 0;
        }
        else
        {
            sp96 = 0;
            sp90 = -temp_v0_9;
        }
        temp_v0_10 = temp_a1_3->green;
        var_t5 = 0;
        var_t4 = 0;
        if (temp_v0_10 >= 0)
        {
            sp94 = temp_v0_10;
            sp8E = 0;
        }
        else
        {
            sp94 = 0;
            sp8E = -temp_v0_10;
        }
        temp_v0_11 = temp_a1_3->blue;
        sp84 = (s32) var_t1;
        sp80 = (s32) var_t2;
        if (temp_v0_11 >= 0)
        {
            var_t4 = temp_v0_11;
        }
        else
        {
            var_t5 = temp_v0_11 * -1;
        }
        temp_t2 = var_a2 + &D_8004F390;
        if ((s32) *temp_t2 > 0)
        {
            command = *arg0;
            *arg0 = command + 1;
            command->w1 = 0x80;
            command->w0 = 0xFA000100;
            command = *arg0;
            *arg0 = command + 1;
            command->w1 = 0;
            command->w0 = 0xFB000000;
            temp_t1 = (*(u32 *)((u8 *)(var_t3) + 0x70));


            func_8001EC74((u8 **)arg0, (s32) (*(s32 *)((u8 *)(var_t3) + 0x68)) / 16, (s32) (*(s32 *)((u8 *)(var_t3) + 0x6C)) / 16, (u32) (temp_t1 * sp84) >> 0xC, (u32) (temp_t1 * sp80) >> 0xC, (s32) var_ra, sp7C, 0);
            *temp_t2 = 0;
        }
        if (*sp3C == 9)
        {
            var_ra = 1;
            sp80 *= 3;
        }
        command = *arg0;
        *arg0 = command + 1;
        command->w0 = 0xFA000100;
        command->w1 = (s32) ((sp96 << 0x18) | ((sp94 & 0xFF) << 0x10) | ((var_t4 & 0xFF) << 8) | 0xFF);
        command = *arg0;
        *arg0 = command + 1;
        command->w0 = 0xFB000000;
        command->w1 = (s32) ((sp90 << 0x18) | ((sp8E & 0xFF) << 0x10) | ((var_t5 & 0xFF) << 8));
        temp_t1_2 = (*(s32 *)((u8 *)(var_t3) + 0x70));
        func_8001EC74((u8 **)arg0, (s32) (*(s32 *)((u8 *)(var_t3) + 0x68)) / 16, (s32) (*(s32 *)((u8 *)(var_t3) + 0x6C)) / 16, (u32) (temp_t1_2 * sp84) >> 0xC, (u32) (temp_t1_2 * sp80) >> 0xC, (s32) var_ra, (u8)sp7C, 0);
        return;
    }
    command = *arg0;
    *arg0 = command + 1;
    command->w1 = -1;
    command->w0 = 0xFA000100;
    command = *arg0;
    *arg0 = command + 1;
    command->w1 = 0;
    command->w0 = 0xFB000000;
    temp_a3_2 = (*(u32 *)((u8 *)(var_t3) + 0x70));
    func_8001EC74((u8 **)arg0, (s32) (*(s32 *)((u8 *)(var_t3) + 0x68)) / 16, (s32) (*(s32 *)((u8 *)(var_t3) + 0x6C)) / 16, temp_a3_2, temp_a3_2, 5, sp7C, 0);
}
