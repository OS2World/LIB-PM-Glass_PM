/*
 * Copyright (C) 2010 Dmitry A.Steklenev
 *
 * $Id: pm_initfoc.cpp,v 1.2 2011/03/11 12:59:32 glass Exp $
 */

#include "pm_initfoc.h"
#include "pm_gui.h"
#include "pm_error.h"

ULONG   PMFOCInit::m_initialized = 0;
HMODULE PMFOCInit::m_hmodule     = NULLHANDLE;

/* Registers the FOC control window classes.
 */

PMFOCInit::PMFOCInit()
{
  if( !m_initialized++ )
  {
    APIRET rc;
    char   error[512];

    rc = DosLoadModule( error, sizeof( error ), "foc", &m_hmodule );

    if( rc != NO_ERROR ) {
      PMGUI gui;
      throw PMError( rc , "DOS", "Unable to load FOC.DLL module.", PM_ERROR_LOCATION ).show();
    }
  }
}

/* Deregisters the FOC control window classes.
 */

PMFOCInit::~PMFOCInit()
{
  if( !--m_initialized ) {
    DosFreeModule( m_hmodule );
  }
}
