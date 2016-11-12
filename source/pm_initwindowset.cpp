/*
 * Copyright (C) 2010 Dmitry A.Steklenev
 *
 * $Id: pm_initwindowset.cpp,v 1.2 2011/03/11 12:59:32 glass Exp $
 */

#include "pm_initwindowset.h"
#include "pm_windowset.h"

ULONG PMInitWindowSet::m_initialized = 0;

/* Initializes the windows set class.
 */

PMInitWindowSet::PMInitWindowSet()
{
  if( !m_initialized++ ) {
    DosCreateMutexSem( NULL, &PMWindowSet::m_mutex, 0, 0 );
  }
}

/* Termnates the windows set class.
 */

PMInitWindowSet::~PMInitWindowSet()
{
  if( !--m_initialized ) {
    DosCloseMutexSem( PMWindowSet::m_mutex );
  }
}
