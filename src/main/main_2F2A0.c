#include "common.h"

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2F2A0/__osAiDeviceBusy.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2F2A0/alSaveNew.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2F2A0/alMainBusNew.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2F2A0/alAuxBusNew.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2F2A0/alResampleNew.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2F2A0/alLoadNew.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2F2A0/alEnvmixerNew.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2F2A0/init_lpfilter.s")

/* SDK alFxNew, adapted from n64decomp/libreultra src/audio/drvrNew.c. */
typedef struct ALFilter {
    struct ALFilter *source;
    void (*handler)(void);
    void (*setParam)(void);
    s16 inp, outp;
    s32 type;
} ALFilter;

typedef struct {
    ALFilter filter;
    void *state;
    f32 ratio;
    s32 upitch;
    f32 delta;
    s32 first;
    void *ctrlList, *ctrlTail;
    s32 motion;
} ALResampler;

typedef struct {
    s16 fc, fgain;
    union {
        s16 fccoef[16];
        s64 force_aligned;
    } fcvec;
    void *fstate;
    s32 first;
} ALLowPass;

typedef struct {
    u32 input, output;
    s16 ffcoef, fbcoef, gain;
    f32 rsinc, rsval;
    s32 rsdelta;
    f32 rsgain;
    ALLowPass *lp;
    ALResampler *rs;
} ALDelay;

typedef void (*ALSetFXParam)(void);
typedef struct {
    ALFilter filter;
    s16 *base, *input;
    u32 length;
    ALDelay *delay;
    u8 section_count;
    ALSetFXParam paramHdl;
} ALFx;

typedef struct {
    u8 pad[0x1C];
    u8 fxType;
    u8 pad2[3];
    s32 *params;
} ALSynConfig;
typedef void ALHeap;

extern s32 D_80048480[], D_800484E8[], D_80048570[];
extern s32 D_80048598[], D_800485C0[], D_800485E8[];
extern void alFxParam(void), alFxPull(void), func_80042198(void);
extern void init_lpfilter(void *);
extern void alFilterNew(void *, s32, void (*)(void), s32);
extern void *alHeapDBAlloc(s32, s32, void *, s32, s32);

#define alHeapAlloc(h,n,s) alHeapDBAlloc(0,0,h,n,s)
void func_8003EF90(ALFx *r, ALSynConfig *c, ALHeap *hp)
{
    u16		i, j, k;
    s32		*param = 0;
    ALFilter	*f = (ALFilter *) r;
    ALDelay	*d;

    alFilterNew(f, 0, alFxParam, 5);
    f->handler = alFxPull;
    r->paramHdl = (ALSetFXParam)func_80042198;

    switch (c->fxType) {
      case 1:	param = D_80048480;	break;
      case 2:	param = D_800484E8;		break;
      case 5:		param = D_80048570;		break;
      case 3:	param = D_80048598;		break;
      case 4:	param = D_800485C0;		break;
      case 6:	param = c->params;		break;
      default:			param = D_800485E8;		break;
    }


    j = 0;

    r->section_count = param[j++];
    r->length 	     = param[j++];

    r->delay = alHeapAlloc(hp, r->section_count, sizeof(ALDelay));
    r->base = alHeapAlloc(hp, r->length, sizeof(s16));
    r->input = r->base;

    for ( k=0; k < r->length; k++)
	r->base[k] = 0;

    for ( i=0; i<r->section_count; i++ ){
	d = &r->delay[i];
	d->input  = param[j++];
	d->output = param[j++];
	d->fbcoef = param[j++];
	d->ffcoef = param[j++];
	d->gain   = param[j++];

	if (param[j]) {
	    d->rsinc = ((f32)param[j++])/16777215.0f;

	    /*
	     * the following constant is derived from:
	     *
	     *		ratio = 2^(cents/1200)
	     *
	     * and therefore for hundredths of a cent
	     *			           x
	     *		ln(ratio) = ---------------
	     *			    (120,000)/ln(2)
	     * where
	     *		120,000/ln(2) = 173123.40...
	     */
#define LENGTH	(d->output - d->input)
	    d->rsgain 	 = (((f32) param[j++])/173123.404906676) * LENGTH;
	    d->rsval	 = 1.0;
	    d->rsdelta	 = 0.0;
	    d->rs 	 = alHeapAlloc(hp, 1, sizeof(ALResampler));
	    d->rs->state = alHeapAlloc(hp, 1, 0x20);
	    d->rs->delta = 0.0;
	    d->rs->first = 1;
	} else {
	    d->rs = 0;
	    j++;
	    j++;
	}

	if (param[j]) {
	    d->lp = alHeapAlloc(hp, 1, sizeof(ALLowPass));
	    d->lp->fstate = alHeapAlloc(hp, 1, 8);
	    d->lp->fc = param[j++];
	    init_lpfilter(d->lp);
	} else {
	    d->lp = 0;
	    j++;
	}
    }
}

#undef LENGTH
#undef alHeapAlloc
