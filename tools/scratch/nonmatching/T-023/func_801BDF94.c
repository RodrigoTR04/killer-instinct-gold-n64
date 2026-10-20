/* DRAFT. Remaining diff: Matrix/vector buffer types, float arguments, stack and rendering scheduling differ. */
typedef struct { u32 w0, w1; } T023801BDF94Gfx;
typedef union { u64 align; u8 bytes[64]; } T079Matrix;
typedef struct { u32 image; f32 width; } T023801BDF94Glyph;
f32 cosf(f32);
extern void guLookAtReflect(void *, void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
extern void guRotate(void *, f32, f32, f32, f32);
extern void guScale(void *, f32, f32, f32);
extern void guTranslate(void *, f32, f32, f32);
f32 sinf(f32);
extern T023801BDF94Glyph D_80282C48[];
extern u8 D_80282D28[];
extern s32 D_80282DC0;
extern f32 D_80292B58;
extern f64 D_80292B60;
extern f64 D_80292B68;
extern f64 D_80292B70;
extern f64 D_80292B78;
extern f64 D_80292B80;
extern u8 D_802D36B0[];
extern u8 D_802D36C0[];

s32 func_801BDF94(T023801BDF94Gfx **dl, T079Matrix *matrices, u8 *text,
                    f32 x, f32 y, f32 z, s32 mode, f32 scale, f32 angle)
{
    T079Matrix reflection;
    T079Matrix *matrix;
    T023801BDF94Gfx *cmd;
    T023801BDF94Glyph *glyph;
    s32 count = 0;
    s32 fixed = 0;
    s32 index = 0;
    s32 length = 0;
    s8 character;
    u8 *end;
    f32 sine;
    f32 center;
    f32 rotation;
    f64 advance;
    f64 width;

    if (scale != 1.0f && scale != -1.0f) {
        if (scale < 0.0f) {
            guScale(matrices, 1.0f, -scale, 1.0f);
            scale = D_80292B58;
        } else {
            guScale(matrices, scale, scale, 1.0f);
        }
        count = 1;
    }
    if (mode == 2) {
        matrix = &matrices[count];
        guRotate(matrix, angle, 0.0f, 1.0f, 0.0f);
        cmd = (*dl)++;
        count++;
        cmd->w1 = (u32)matrix;
        cmd->w0 = 0x01020040;
    }
    sine = sinf(D_80282DC0 * D_80292B60);
    guLookAtReflect(&reflection, D_802D36B0, sine * 60.0f,
                    cosf(D_80282DC0 * D_80292B60) * 60.0f,
                    220.0f, 6.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    cmd = (*dl)++;
    cmd->w1 = (u32)D_802D36B0;
    cmd->w0 = 0x03840010;
    cmd = (*dl)++;
    cmd->w0 = 0x03820010;
    cmd->w1 = (u32)D_802D36C0;
    cmd = (*dl)++;
    cmd->w0 = 0x06000000;
    cmd->w1 = (u32)D_80282D28;
    D_80282DC0++;
    end = text;
    while (*end) {
        length++;
        end++;
    }
    angle -= length * 30;
    while (*text) {
        character = *text - 'A';
        if (character == -19) character = 26;
        if (character < 27 && character >= 0 &&
            (glyph = &D_80282C48[character], matrix = &matrices[count], glyph->image)) {
            rotation = 0.0f;
            advance = scale;
            if (fixed) width = D_80292B68;
            else width = glyph->width * 9.0f;
            center = x + advance * width;
            if (mode == 1) {
                rotation = index * 30 + angle;
                if (rotation < 360.0f) {
                    z -= (rotation - 360.0f) / 8.0f;
                    y += (rotation - 360.0f) / 32.0f;
                }
            }
            guTranslate(matrix, center, y, z);
            cmd = (*dl)++;
            count++;
            cmd->w1 = (u32)matrix;
            if (mode == 2) cmd->w0 = 0x01040040;
            else cmd->w0 = 0x01020040;
            if (rotation < 360.0f && mode == 1) {
                matrix = &matrices[count];
                guRotate(matrix, rotation, 1.0f, 0.0f, 0.0f);
                cmd = (*dl)++;
                count++;
                cmd->w1 = (u32)matrix;
                cmd->w0 = 0x01000040;
            }
            if (scale != 1.0f) {
                cmd = (*dl)++;
                cmd->w1 = (u32)matrices;
                cmd->w0 = 0x01000040;
            }
            cmd = (*dl)++;
            cmd->w0 = 0x06000000;
            cmd->w1 = glyph->image;
            if (fixed) width = D_80292B70;
            else width = glyph->width * 10.0f;
            x = center + advance * width;
            if (mode == 2) {
                cmd = (*dl)++;
                cmd->w1 = 0;
                cmd->w0 = 0xBD000000;
            }
        } else if (character == 41) {
            fixed = 1;
        } else {
            if (fixed) width = D_80292B78;
            else width = D_80292B80;
            x += scale * width;
        }
        index++;
        text++;
    }
    return count;
}
