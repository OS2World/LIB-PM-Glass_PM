/*
 * Copyright (C) 2010 Dmitry A.Steklenev
 *
 * $Id: pm_windowset.cpp,v 1.2 2011/03/11 12:59:33 glass Exp $
 */

#include "pm_windowset.h"
#include "pm_window.h"

HMTX             PMWindowSet::m_mutex;
PMWindowSet::map PMWindowSet::m_map[PM_MAX_WINDOWS];

/* Inserts a new window object to the windows set.
 */

void PMWindowSet::insert( HWND hwnd, PMWindow* window )
{
  int i;

  DosRequestMutexSem( m_mutex, SEM_INDEFINITE_WAIT );

  for( i = 0; i < sizeof( m_map ) / sizeof( m_map[0] ); i++ ) {
    if( m_map[i].handle == NULLHANDLE ) {
        m_map[i].handle =  hwnd;
        m_map[i].window =  window;
        break;
    }
  }

  DosReleaseMutexSem( m_mutex );

  if( i >= sizeof( m_map ) / sizeof( m_map[0] )) {
    PM_THROW_ERROR( 0, "PMLIB", "Too many strangers." );
  }
}

/* Removes a window object from the windows set.
 */

void PMWindowSet::remove( HWND hwnd )
{
  int i;

  DosRequestMutexSem( m_mutex, SEM_INDEFINITE_WAIT );

  for( i = 0; i < sizeof( m_map ) / sizeof( m_map[0] ); i++ ) {
    if( m_map[i].handle == hwnd ) {
        m_map[i].handle =  NULLHANDLE;
        m_map[i].window =  NULL;
        break;
    }
  }

  DosReleaseMutexSem( m_mutex );
}

/* Queries a window object.
 */

PMWindow* PMWindowSet::query( HWND hwnd )
{
  PMWindow* window = NULL;
  int i;

  DosRequestMutexSem( m_mutex, SEM_INDEFINITE_WAIT );

  for( i = 0; i < sizeof( m_map ) / sizeof( m_map[0] ); i++ ) {
    if( m_map[i].handle == hwnd ) {
      window = m_map[i].window;
      break;
    }
  }

  DosReleaseMutexSem( m_mutex );
  return window;
}

