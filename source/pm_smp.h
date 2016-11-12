/*
 * Copyright (C) 2010 Dmitry A.Steklenev
 *
 * $Id: pm_smp.h,v 1.2 2011/03/11 12:59:33 glass Exp $
 */

#ifndef PM_SMP_H
#define PM_SMP_H

#include "pm_os2.h"

extern  unsigned int xchg( unsigned int* p, unsigned int x );
#pragma aux xchg = "xchg [esi],eax" parm [ESI][EAX] value [EAX];
extern  unsigned int xadd( unsigned int* p, unsigned int x );
#pragma aux xadd = "lock xadd [esi],eax" parm [ESI][EAX] value [EAX];

#endif
