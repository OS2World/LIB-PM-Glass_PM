/*
 * Copyright (C) 2010 Dmitry A.Steklenev
 *
 * $Id: pm_exception.cpp,v 1.2 2011/03/11 12:59:31 glass Exp $
 */

#include "pm_exception.h"

ULONG EXPENTRY
PMExceptionHandler( PEXCEPTIONREPORTRECORD       pRep,
                    PEXCEPTIONREGISTRATIONRECORD pReg,
                    PCONTEXTRECORD,
                    PVOID  )
{
  if( pRep->ExceptionNum == XCPT_ACCESS_VIOLATION ) {
    longjmp(((PMEXCEPTION*)pReg)->env, 1 );
  }

  return XCPT_CONTINUE_SEARCH;
}

