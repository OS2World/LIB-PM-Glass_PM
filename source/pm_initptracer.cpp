/*
 * Copyright (C) 2010 Dmitry A.Steklenev
 *
 * $Id: pm_initptracer.cpp,v 1.2 2011/03/11 12:59:32 glass Exp $
 */

#include "pm_initptracer.h"
#include "pm_gui.h"
#include "pm_error.h"

ULONG   PMPTracerInit::m_initialized = 0;
HMODULE PMPTracerInit::m_hmodule     = NULLHANDLE;

/* Registers the log messages collector window class.
 */

PMPTracerInit::PMPTracerInit()
{
  if( !m_initialized++ )
  {
    APIRET rc;
    char   error[512];

    rc = DosLoadModule( error, sizeof( error ), "ptrace", &m_hmodule );

    if( rc != NO_ERROR ) {
      PMGUI gui;
      throw PMError( rc , "DOS", "Unable to load PTRACE.DLL module.", PM_ERROR_LOCATION ).show();
    }
  }
}

/* Unregisters the log messages collector window class.
 */

PMPTracerInit::~PMPTracerInit()
{
  if( !--m_initialized ) {
    DosFreeModule( m_hmodule );
  }
}

