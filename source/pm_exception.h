/*
 * Copyright (C) 2010 Dmitry A.Steklenev
 *
 * $Id: pm_exception.h,v 1.2 2011/03/11 12:59:31 glass Exp $
 */

#ifndef PM_EXCEPTION_H
#define PM_EXCEPTION_H

#include <setjmp.h>
#include "pm_os2.h"

#pragma pack(4)
typedef struct _PMEXCEPTION
{
  EXCEPTIONREGISTRATIONRECORD exreg;
  jmp_buf env;

} PMEXCEPTION;
#pragma pack()

#ifdef __cplusplus
extern "C" {
#endif

ULONG EXPENTRY PMExceptionHandler( PEXCEPTIONREPORTRECORD,
                                   PEXCEPTIONREGISTRATIONRECORD,
                                   PCONTEXTRECORD,
                                   PVOID );
#ifdef __cplusplus
}
#endif

#define PM_BEGINSEQUENCE                                \
  {                                                     \
    PMEXCEPTION pmex;                                   \
    if( setjmp( pmex.env ) == 0 ) {                     \
      pmex.exreg.ExceptionHandler = PMExceptionHandler; \
      DosSetExceptionHandler( &pmex.exreg );

#define PM_RECOVER                                      \
      DosUnsetExceptionHandler( &pmex.exreg );          \
    } else {

#define PM_END                                          \
    }                                                   \
  }

#endif
