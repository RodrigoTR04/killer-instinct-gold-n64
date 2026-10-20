#include "boot.h"

extern void *memcpy(void *, void *, u32);

/* gzip names are retained to make comparison with inflate.c straightforward. */
#define NEEDBITS(n) while (k < (n)) { b |= (u32)inflate_input[inflate_inptr++] << k; k += 8; }
#define DUMPBITS(n) { b >>= (n); k -= (n); }

/* Build lookup tables in caller-supplied scratch instead of using malloc. */
s32 huft_build(u32 *b, u32 n, u32 s, u16 *d, u8 *e, huft **t, s32 *m)
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
    huft *q;
    huft r;
    huft *u[16];
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
        *t = (huft *)0;
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
    u[0] = (huft *)0;
    q = (huft *)0;
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

                q = inflate_huft_pool + hufts;
                hufts += z + 1;
                *t = q + 1;
                *(t = &(q->v.t)) = (huft *)0;
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


/* Output is contiguous: no gzip sliding-window flush or wrap is needed. */
s32 inflate_codes(huft *tl, huft *td, s32 bl, s32 bd)
{
    unsigned e;
    unsigned n, d;
    unsigned w;
    huft *t;
    unsigned ml, md;
    u32 b;
    unsigned k;

    b = bb;
    k = bk;
    w = wp;

    ml = mask_bits[bl];
    md = mask_bits[bd];
    for (;;)
    {
        NEEDBITS((unsigned)bl)
        if ((e = (t = tl + ((unsigned)b & ml))->e) > 16)
            do {

                DUMPBITS(t->b)
                e -= 16;
                NEEDBITS(e)
            } while ((e = (t = t->v.t + ((unsigned)b & mask_bits[e]))->e) > 16);
        DUMPBITS(t->b)
        if (e == 16)
        {
            inflate_output[w++] = (u8)t->v.n;

        }
        else
        {

            if (e == 15)
                break;

            NEEDBITS(e)
            n = t->v.n + ((unsigned)b & mask_bits[e]);
            DUMPBITS(e);

            NEEDBITS((unsigned)bd)
            if ((e = (t = td + ((unsigned)b & md))->e) > 16)
                do {
                    DUMPBITS(t->b)
                    e -= 16;
                    NEEDBITS(e)
                } while ((e = (t = t->v.t + ((unsigned)b & mask_bits[e]))->e) > 16);
            DUMPBITS(t->b)
            NEEDBITS(e)
            d = w - t->v.n - ((unsigned)b & mask_bits[e]);
            DUMPBITS(e)

            do {
                n -= (e = n);
                if (w - d >= e)
                {
                    memcpy(inflate_output + w, inflate_output + d, e);
                    w += e;
                    d += e;
                }
                else
                    do {
                        inflate_output[w++] = inflate_output[d++];
                    } while (--e);

            } while (n);
        }
    }

    wp = w;
    bb = b;
    bk = k;

    return 0;
}


s32 inflate_stored(void) {
    u32 length;
    u32 bits = bb;
    u32 count = bk;
    s32 out = wp;
    length = count & 7;
    bits >>= length;
    count -= length;
    while (count < 16) {
        bits |= inflate_input[inflate_inptr++] << count;
        count += 8;
    }
    length = bits & 0xFFFF;
    bits >>= 16;
    count -= 16;
    while (count < 16) {
        bits |= inflate_input[inflate_inptr++] << count;
        count += 8;
    }
    bits >>= 16;
    count -= 16;
    while (length--) {
        while (count < 8) {
            bits |= inflate_input[inflate_inptr++] << count;
            count += 8;
        }
        inflate_output[out++] = bits;
        bits >>= 8;
        count -= 8;
    }
    wp = out;
    bb = bits;
    bk = count;
    return 0;
}

s32 inflate_fixed(void) {
    int i;
    huft *tl;
    huft *td;
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
    huft_build(l, 288, 257, cplens, cplext, &tl, &bl);
    for (i = 0; i < 30; i++)
        l[i] = 5;
    bd = 5;
    huft_build(l, 30, 0, cpdist, cpdext, &td, &bd);
    inflate_codes(tl, td, bl, bd);
    return 0;
}


s32 inflate_dynamic(void)
{
    int i;
    unsigned j;
    unsigned l;
    unsigned m;
    unsigned n;
    huft *tl;
    huft *td;
    int bl;
    int bd;
    unsigned nb;
    unsigned nl;
    unsigned nd;
    unsigned k;
    u32 b;
    unsigned ll[286 + 30];

    b = bb;
    k = bk;

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
        ll[border[j]] = (unsigned)b & 7;
        DUMPBITS(3)
    }
    for (; j < 19; j++)
        ll[border[j]] = 0;

    bl = 7;
    huft_build(ll, 19, 19, 0, 0, &tl, &bl);

    n = nl + nd;
    m = mask_bits[bl];
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

    bb = b;
    bk = k;

    bl = lbits;
    huft_build(ll, nl, 257, cplens, cplext, &tl, &bl);
    bd = dbits;
    huft_build(ll + nl, nd, 0, cpdist, cpdext, &td, &bd);

    inflate_codes(tl, td, bl, bd);

    return 0;
}


s32 inflate_block(s32 *last) {
    u32 type;
    u32 bits = bb;
    u32 count = bk;
    while (count < 1) {
        bits |= inflate_input[inflate_inptr++] << count;
        count += 8;
    }
    *last = bits & 1;
    bits >>= 1;
    count--;
    while (count < 2) {
        bits |= inflate_input[inflate_inptr++] << count;
        count += 8;
    }
    type = bits & 3;
    bits >>= 2;
    count -= 2;
    bb = bits;
    bk = count;
    if (type == 2) return inflate_dynamic();
    if (type == 0) return inflate_stored();
    if (type == 1) return inflate_fixed();
    return 2;
}

s32 inflate(void) {
    s32 last;
    s32 status;
    u32 maximum;
    wp = 0;
    bk = 0;
    bb = 0;
    maximum = 0;
    do {
        hufts = 0;
        status = inflate_block(&last);
        if (status != 0) return status;
        if (maximum < hufts) maximum = hufts;
    } while (!last);
    while (bk >= 8) {
        bk -= 8;
        inflate_inptr--;
    }
    return 0;
}
