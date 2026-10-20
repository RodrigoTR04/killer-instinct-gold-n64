#include "common.h"

typedef struct Huft {
    u8 e, b;
    union { u16 n; struct Huft *t; } v;
} Huft;
extern void bzero(void *, s32);
extern void *memcpy(void *, void *, u32);
extern Huft *D_8000BF90;
extern u32 D_8000BF9C;
extern u8 *D_8000BF80, *D_8000BF84;
extern s32 D_8000BF88;
extern u32 D_8000BF8C, D_8000BF94, D_8000BF98;
extern u8 D_80006560[], D_800065B4[], D_80006610[];
extern u16 D_80006574[], D_800065D4[], D_80006630[];
extern s32 D_80006654, D_80006658;
#define NEEDBITS(n) while (k < (n)) { b |= (u32)D_8000BF80[D_8000BF88++] << k; k += 8; }
#define DUMPBITS(n) { b >>= (n); k -= (n); }

s32 func_80001410(void), func_80001564(void), func_800016CC(void);
s32 func_80001BF0(s32 *);

s32 func_80000960(u32 *b, u32 n, u32 s, u16 *d, u8 *e, Huft **t, s32 *m)
{
    unsigned a;
    unsigned c[16 + 1]; /* Code counts by bit length. */
    unsigned f;
    int g;
    int h;
    unsigned i;
    unsigned j;
    int k;
    int l;
    unsigned *p;
    Huft *q;
    Huft r;
    Huft *u[16];
    unsigned v[288]; /* Symbols sorted by bit length. */
    int w;
    unsigned x[16 + 1];
    unsigned *xp;
    int y;
    unsigned z;

    bzero(c, sizeof(c));
    p = b;  i = n;
    do {
        c[*p]++;
        p++;
    } while (--i);
    if (c[0] == n)
    {
        *t = (Huft *)0;
        *m = 0;
        return 0;
    }

    l = *m;
    for (j = 1; j <= 16; j++)
        if (c[j])
            break;
    k = j;
    if ((unsigned)l < j)
        l = j;
    for (i = 16; i; i--)
        if (c[i])
            break;
    g = i;
    if ((unsigned)l > i)
        l = i;
    *m = l;

    for (y = 1 << j; j < i; j++, y <<= 1)
        y -= c[j];
    y -= c[i];
    c[i] += y;

    x[1] = j = 0;
    p = c + 1;  xp = x + 2;
    while (--i) {
        *xp++ = (j += *p++);
    }

    p = b;  i = 0;
    do {
        if ((j = *p++) != 0)
            v[x[j]++] = i;
    } while (++i < n);

    x[0] = i = 0;
    p = v;
    h = -1;
    w = -l;
    u[0] = (Huft *)0;
    q = (Huft *)0;
    z = 0;

    for (; k <= g; k++)
    {
        a = c[k];
        while (a--)
        {

            while (k > w + l)
            {
                h++;
                w += l;

                z = (z = g - w) > (unsigned)l ? l : z;
                if ((f = 1 << (j = k - w)) > a + 1)
                {
                    f -= a + 1;
                    xp = c + k;
                    while (++j < z)
                    {
                        if ((f <<= 1) <= *++xp)
                            break;
                        f -= *xp;
                    }
                }
                z = 1 << j;

                q = D_8000BF90 + D_8000BF9C;
                D_8000BF9C += z + 1;
                *t = q + 1;
                *(t = &(q->v.t)) = (Huft *)0;
                u[h] = ++q;

                if (h)
                {
                    x[h] = i;
                    r.b = (u8)l;
                    r.e = (u8)(16 + j);
                    r.v.t = q;
                    j = i >> (w - l);
                    u[h-1][j] = r;
                }
            }

            r.b = (u8)(k - w);
            if (p >= v + n)
                r.e = 99;
            else if (*p < s)
            {
                r.e = (u8)(*p < 256 ? 16 : 15);
                r.v.n = (u16)(*p);
        p++;
            }
            else
            {
                r.e = (u8)e[*p - s];
                r.v.n = d[*p++ - s];
            }

            f = 1 << (k - w);
            for (j = i >> w; j < z; j += f)
                q[j] = r;

            for (j = 1 << (k - 1); i & j; j >>= 1)
                i ^= j;
            i ^= j;

            while ((i & ((1 << w) - 1)) != x[h])
            {
                h--;
                w -= l;
            }
        }
    }

    return y != 0 && g != 1;
}


s32 func_80000FA0(Huft *tl, Huft *td, s32 bl, s32 bd)
{
    unsigned e;
    unsigned n, d;
    unsigned w;
    Huft *t;
    unsigned ml, md;
    u32 b;
    unsigned k;

    b = D_8000BF94;
    k = D_8000BF98;
    w = D_8000BF8C;

    ml = D_80006630[bl];
    md = D_80006630[bd];
    for (;;)
    {
        NEEDBITS((unsigned)bl)
        if ((e = (t = tl + ((unsigned)b & ml))->e) > 16)
            do {

                DUMPBITS(t->b)
                e -= 16;
                NEEDBITS(e)
            } while ((e = (t = t->v.t + ((unsigned)b & D_80006630[e]))->e) > 16);
        DUMPBITS(t->b)
        if (e == 16)
        {
            D_8000BF84[w++] = (u8)t->v.n;

        }
        else
        {

            if (e == 15)
                break;

            NEEDBITS(e)
            n = t->v.n + ((unsigned)b & D_80006630[e]);
            DUMPBITS(e);

            NEEDBITS((unsigned)bd)
            if ((e = (t = td + ((unsigned)b & md))->e) > 16)
                do {
                    DUMPBITS(t->b)
                    e -= 16;
                    NEEDBITS(e)
                } while ((e = (t = t->v.t + ((unsigned)b & D_80006630[e]))->e) > 16);
            DUMPBITS(t->b)
            NEEDBITS(e)
            d = w - t->v.n - ((unsigned)b & D_80006630[e]);
            DUMPBITS(e)

            do {
                n -= (e = n);
                if (w - d >= e)
                {
                    memcpy(D_8000BF84 + w, D_8000BF84 + d, e);
                    w += e;
                    d += e;
                }
                else
                    do {
                        D_8000BF84[w++] = D_8000BF84[d++];
                    } while (--e);

            } while (n);
        }
    }

    D_8000BF8C = w;
    D_8000BF94 = b;
    D_8000BF98 = k;

    return 0;
}


s32 func_80001410(void) {
    u32 length;
    u32 bits = D_8000BF94;
    u32 count = D_8000BF98;
    s32 out = D_8000BF8C;
    length = count & 7;
    bits >>= length;
    count -= length;
    while (count < 16) {
        bits |= D_8000BF80[D_8000BF88++] << count;
        count += 8;
    }
    length = bits & 0xFFFF;
    bits >>= 16;
    count -= 16;
    while (count < 16) {
        bits |= D_8000BF80[D_8000BF88++] << count;
        count += 8;
    }
    bits >>= 16;
    count -= 16;
    while (length--) {
        while (count < 8) {
            bits |= D_8000BF80[D_8000BF88++] << count;
            count += 8;
        }
        D_8000BF84[out++] = bits;
        bits >>= 8;
        count -= 8;
    }
    D_8000BF8C = out;
    D_8000BF94 = bits;
    D_8000BF98 = count;
    return 0;
}

s32 func_80001564(void) {
    int i;
    Huft *tl;
    Huft *td;
    s32 bl;
    s32 bd;
    u32 l[288];

    for (i = 0; i < 144; i++)
        l[i] = 8;
    for (; i < 256; i++)
        l[i] = 9;
    for (; i < 280; i++)
        l[i] = 7;
    for (; i < 288; i++)
        l[i] = 8;
    bl = 7;
    func_80000960(l, 288, 257, D_80006574, D_800065B4, &tl, &bl);
    for (i = 0; i < 30; i++)
        l[i] = 5;
    bd = 5;
    func_80000960(l, 30, 0, D_800065D4, D_80006610, &td, &bd);
    func_80000FA0(tl, td, bl, bd);
    return 0;
}


s32 func_800016CC(void)
{
    int i;
    unsigned j;
    unsigned l;
    unsigned m;
    unsigned n;
    Huft *tl;
    Huft *td;
    int bl;
    int bd;
    unsigned nb;
    unsigned nl;
    unsigned nd;
    unsigned k;
    u32 b;
    unsigned ll[286 + 30];

    b = D_8000BF94;
    k = D_8000BF98;

    NEEDBITS(5)
    nl = 257 + ((unsigned)b & 0x1f);
    DUMPBITS(5)
    NEEDBITS(5)
    nd = 1 + ((unsigned)b & 0x1f);
    DUMPBITS(5)
    NEEDBITS(4)
    nb = 4 + ((unsigned)b & 0xf);
    DUMPBITS(4)

    for (j = 0; j < nb; j++)
    {
        NEEDBITS(3)
        ll[D_80006560[j]] = (unsigned)b & 7;
        DUMPBITS(3)
    }
    for (; j < 19; j++)
        ll[D_80006560[j]] = 0;

    bl = 7;
    func_80000960(ll, 19, 19, 0, 0, &tl, &bl);

    n = nl + nd;
    m = D_80006630[bl];
    i = l = 0;
    while ((unsigned)i < n)
    {
        NEEDBITS((unsigned)bl)
        j = (td = tl + ((unsigned)b & m))->b;
        DUMPBITS(j)
        j = td->v.n;
        if (j < 16)
            ll[i++] = l = j;
        else if (j == 16)
        {
            NEEDBITS(2)
            j = 3 + ((unsigned)b & 3);
            DUMPBITS(2)

            while (j--)
                ll[i++] = l;
        }
        else if (j == 17)
        {
            NEEDBITS(3)
            j = 3 + ((unsigned)b & 7);
            DUMPBITS(3)

            while (j--)
                ll[i++] = 0;
            l = 0;
        }
        else
        {
            NEEDBITS(7)
            j = 11 + ((unsigned)b & 0x7f);
            DUMPBITS(7)

            while (j--)
                ll[i++] = 0;
            l = 0;
        }
    }

    D_8000BF94 = b;
    D_8000BF98 = k;

    bl = D_80006654;
    func_80000960(ll, nl, 257, D_80006574, D_800065B4, &tl, &bl);
    bd = D_80006658;
    func_80000960(ll + nl, nd, 0, D_800065D4, D_80006610, &td, &bd);

    func_80000FA0(tl, td, bl, bd);

    return 0;
}


s32 func_80001BF0(s32 *last) {
    u32 type;
    u32 bits = D_8000BF94;
    u32 count = D_8000BF98;
    while (count < 1) {
        bits |= D_8000BF80[D_8000BF88++] << count;
        count += 8;
    }
    *last = bits & 1;
    bits >>= 1;
    count--;
    while (count < 2) {
        bits |= D_8000BF80[D_8000BF88++] << count;
        count += 8;
    }
    type = bits & 3;
    bits >>= 2;
    count -= 2;
    D_8000BF94 = bits;
    D_8000BF98 = count;
    if (type == 2) return func_800016CC();
    if (type == 0) return func_80001410();
    if (type == 1) return func_80001564();
    return 2;
}

s32 func_80001D10(void) {
    s32 last;
    s32 status;
    u32 maximum;
    D_8000BF8C = 0;
    D_8000BF98 = 0;
    D_8000BF94 = 0;
    maximum = 0;
    do {
        D_8000BF9C = 0;
        status = func_80001BF0(&last);
        if (status != 0) return status;
        if (maximum < D_8000BF9C) maximum = D_8000BF9C;
    } while (!last);
    while (D_8000BF98 >= 8) {
        D_8000BF98 -= 8;
        D_8000BF88--;
    }
    return 0;
}
