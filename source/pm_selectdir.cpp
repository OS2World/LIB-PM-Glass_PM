/*
 * Copyright (C) 2010 Dmitry A.Steklenev
 *
 * $Id: pm_selectdir.cpp,v 1.3 2011/03/11 12:59:33 glass Exp $
 */

#include "pm_selectdir.h"
#include "pm_gui.h"
#include "pm_error.h"
#include "pm_frame.h"
#include "pm_debuglog.h"

/* Constructs the directory selection dialog object.
 *
 * This constructor create file dialog object. You must use show_modally
 * to activate it.
 */

PMSelectDir::PMSelectDir( const char* caption,  HWND howner,
                          const char* pathname, ULONG style )
: m_owner ( howner     ),
  m_handle( NULLHANDLE )
{
  memset( &m_seldir, 0, sizeof( FOCSELDIR ));

  m_seldir.cbSize   = sizeof( FOCSELDIR );
  m_seldir.fl       = style;
  m_seldir.pszTitle = strdup( caption );
  m_seldir.ulUser   = (ULONG)this;

  strlcpy( m_seldir.szFullDir, pathname, sizeof( m_seldir.szFullDir ));

  if( m_seldir.pszTitle == NULL ) {
    PM_THROW_CLIBERROR();
  }
}

/* Destructs the directory selection dialog object.
 *
 * Cleans up as this dialog object and destroying the
 * associated presentation window for this object.
 */

PMSelectDir::~PMSelectDir() {
  free( m_seldir.pszTitle );
}

/**
 * Displays the file dialog.
 *
 * While the dialog window is being shown modally, its parent or owner or
 * both windows are disabled. Other top level windows belonging to the
 * application are not disabled.
 */

ULONG PMSelectDir::show_modally()
{
  m_handle = NULLHANDLE;

  if( FOCSelectDir( HWND_DESKTOP, m_owner, &m_seldir ) == NULLHANDLE ) {
    PM_THROW_GUIERROR();
  }

  return m_seldir.lReturn;
}

/* Returns the chosen directory.
 */

BOOL PMSelectDir::selected( char* pathname, int size )
{
  strlcpy( pathname, m_seldir.szFullDir, size );
  return TRUE;
}

