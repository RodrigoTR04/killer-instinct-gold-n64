#define alGlobals D_80048440
#include "libaudio/libaudio.h"
#include "libaudio/synthInternals.h"
#include "libaudio/cseqp.h"
#define assert(x) ((void)0)
typedef u32 OSIntMask;
#define OS_IM_NONE 1
extern u32 osSetIntMask(u32);
extern u32 osVirtualToPhysical(void *);
/*====================================================================
 * syndelete.c
 *
 * Copyright 1995, Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics,
 * Inc.; the contents of this file may not be disclosed to third
 * parties, copied or duplicated in any form, in whole or in part,
 * without the prior written permission of Silicon Graphics, Inc.
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to
 * restrictions as set forth in subdivision (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS
 * 252.227-7013, and/or in similar or successor clauses in the FAR,
 * DOD or NASA FAR Supplement. Unpublished - rights reserved under the
 * Copyright Laws of the United States.
 *====================================================================*/


void alSynDelete(ALSynth *drvr)
{
    drvr->head = 0;
}
