/*
 * Copyright (C) 2009 Dmitry A.Steklenev
 *
 * $Id: pm_helpwindow.cpp,v 1.4 2011/03/11 12:59:32 glass Exp $
 */

#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "pm_helpwindow.h"
#include "pm_fileutils.h"
#include "pm_gui.h"
#include "pm_error.h"

/* Constructs the help window object.
 */

PMHelpWindow::PMHelpWindow( SHORT res_id, const char* title, const char* library )

: m_owner  ( NULLHANDLE ),
  m_wrapped( FALSE      )
{
  HELPINIT init = { 0 };

  init.cb = sizeof( init );
  init.phtHelpTable = (PHELPTABLE)MAKELONG( res_id, 0xFFFF );
  init.hmodHelpTableModule = PMGUI::module_handle();
  init.pszHelpWindowTitle = (PSZ)title;
  init.fShowPanelId = CMIC_SHOW_PANEL_ID;
  init.pszHelpLibraryName = "";

  m_handle = WinCreateHelpInstance( PMGUI::hab(), &init );

  if( m_handle == NULLHANDLE ) {
    PM_THROW_GUIERROR();
  }

  PMHelpWindow::library( library );
}

/* Wraps the help window object around an existing
 * associated application window.
 */

PMHelpWindow::PMHelpWindow( HWND hwnd )

: m_owner  ( hwnd ),
  m_wrapped( TRUE )
{
  m_handle = WinQueryHelpInstance( hwnd );
}

/* Destructs the help window object.
 */

PMHelpWindow::~PMHelpWindow()
{
  if( m_handle != NULLHANDLE && !m_wrapped )
  {
    detach();
    WinDestroyHelpInstance( m_handle );
  }
}

/* Associates the help window with the specified application window.
 */

void PMHelpWindow::attach( HWND hwnd )
{
  if( m_handle != NULLHANDLE ) {
    if( !WinAssociateHelpInstance( m_handle, hwnd )) {
      PM_THROW_GUIERROR();
    }
    m_owner = hwnd;
  }
}

/* Disassociates the help window from a window.
 */

void PMHelpWindow::detach()
{
  if( m_owner != NULLHANDLE && m_handle != NULLHANDLE ) {
    WinAssociateHelpInstance( NULLHANDLE, m_owner );
    m_owner = NULLHANDLE;
  }
}

/** Identifies a help window library name. */
void PMHelpWindow::library( const char* filename )
{
  char helpfile[_MAX_PATH];
  char progname[_MAX_PATH];
  struct stat fi;

  if( m_handle && filename ) {
    strlcpy( helpfile, filename, sizeof( helpfile ));

    if( stat( helpfile, &fi ) != 0  ) {
      PMGUI::program_name( progname, sizeof( progname ));
      sdrivedir( helpfile, progname, sizeof( helpfile ));
      strlcat( helpfile, filename, sizeof( helpfile ));

      if( stat( helpfile, &fi ) != 0  ) {
        // If the file of the help does not placed together with the program,
        // we shall give to the help manager to find it.
        sfnameext( helpfile, filename, sizeof( helpfile ));
      }
    }

    WinSendMsg( m_handle, HM_SET_HELP_LIBRARY_NAME, MPFROMP( helpfile ), 0 );
  }
}

/* Tells the help manager to display a specific help window.
 */

void PMHelpWindow::show( SHORT res_id )
{
  if( m_handle ) {
    WinSendMsg( m_handle, HM_DISPLAY_HELP, MPFROMLONG( MAKELONG( res_id, NULL )),
                                           MPFROMSHORT( HM_RESOURCEID ));
  }
}

