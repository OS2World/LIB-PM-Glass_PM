/*
 * Copyright (C) 2001-2008 Dmitry A.Steklenev
 *
 * $Id: pm_gui.cpp,v 1.6 2011/05/25 10:53:54 glass Exp $
 */

#include <stdlib.h>

#include "pm_gui.h"
#include "pm_fileutils.h"
#include "pm_error.h"

APIRET APIENTRY DosQueryModFromEIP( HMODULE *phMod, ULONG *pObjNum, ULONG BuffLen,
                                    PCHAR pBuff, ULONG *pOffset, ULONG Address );

HAB PMGUI::m_hab[ PM_MAX_THREADS ];
HMQ PMGUI::m_hmq[ PM_MAX_THREADS ];

/* Constructs the GUI object and initializes the
 * GUI facilities for use by an application.
 */

PMGUI::PMGUI()
{
  TID cur_tid = tid();

  if( cur_tid > PM_MAX_THREADS ) {
    PM_THROW_ERROR( 0, "PMLIB", "Too many threads" );
  }

  m_hab[cur_tid] = NULLHANDLE;
  m_hmq[cur_tid] = NULLHANDLE;

  if(( m_hab[cur_tid] = WinInitialize(0)) == NULLHANDLE ) {
    PM_THROW_ERROR( 0, "PMLIB", "Unexpected error in WinInitialize()" );
  }
  if(( m_hmq[cur_tid] = WinCreateMsgQueue( m_hab[cur_tid], 0 )) == NULLHANDLE ) {
    PM_THROW_GUIERROR();
  }

  m_wrapped = FALSE;
}

/* Constructs the GUI object from an existing GUI environment.
 */

PMGUI::PMGUI( HAB hab )
{
  TID cur_tid = tid();

  if( cur_tid > PM_MAX_THREADS ) {
    PM_THROW_ERROR( 0, "PMLIB", "Too many threads" );
  }

  m_hab[cur_tid] = hab;
  m_hmq[cur_tid] = HMQ_CURRENT;
  m_wrapped      = TRUE;
}

/* Destroys the GUI object.
 *
 * Releases all of associated GUI resources if the object
 * was not created from an existing environment.
 */

PMGUI::~PMGUI()
{
  TID cur_tid = tid();

  if( !m_wrapped ) {
    if( m_hmq[cur_tid] ) {
      WinDestroyMsgQueue( m_hmq[cur_tid] );
    }
    if( m_hab[cur_tid] ) {
      WinTerminate( m_hab[cur_tid] );
    }

    m_hab[cur_tid] = NULLHANDLE;
    m_hmq[cur_tid] = NULLHANDLE;
  }
}

/* Returns the current thread identifier.
 */

TID PMGUI::tid()
{
  PTIB ptib;
  DosGetInfoBlocks( &ptib, NULL );
  return ptib->tib_ptib2->tib2_ultid;
}

/* Returns the current process identifier.
 */

PID PMGUI::pid()
{
  PPIB ppib;
  DosGetInfoBlocks( NULL, &ppib );
  return ppib->pib_ulpid;
}

/* Returns the anchor block handle of the current thread.
 */

HAB PMGUI::hab() {
  return m_hab[ tid()];
}

/* Returns the message queue handle of the current thread.
 */

HMQ PMGUI::hmq() {
  return m_hmq[ tid()];
}

/* Returns a system metric.
 *
 * Allows the application to ask for details about
 * the user interface element sizes.
 */

LONG PMGUI::metric( LONG id ) {
  return WinQuerySysValue( HWND_DESKTOP, id );
}

/* Returns a current screen resolution.
 */

static LONG PMGUI::dpi()
{
  HPS  hps;
  HDC  hdc;
  LONG dpi = 96;

  hps = WinGetPS( HWND_DESKTOP );
  hdc = GpiQueryDevice( hps );
  DevQueryCaps( hdc, CAPS_HORIZONTAL_FONT_RES, 1L, &dpi );
  WinReleasePS( hps );

  return dpi;
}

/* Returns the current module handle.
 */

HMODULE PMGUI::module_handle()
{
  ULONG   obj_num = 0;
  ULONG   offset  = 0;
  HMODULE handle  = 0;
  char    name[_MAX_PATH];

  DosQueryModFromEIP( &handle, &obj_num, sizeof( name ), name,
                      &offset, (ULONG)(&PMGUI::module_handle));
  return  handle;
}

/* Returns the current module name.
 */

char* PMGUI::module_name( char* result, int size )
{
  if( result && size )
  {
    ULONG   obj_num = 0;
    ULONG   offset  = 0;
    HMODULE handle  = 0;

    DosQueryModFromEIP( &handle, &obj_num, size, result,
                        &offset, (ULONG)(&PMGUI::module_name));
    DosQueryModuleName( handle, size, result );
  }

  return result;
}

/* Returns the current program name.
 */

char* PMGUI::program_name( char* result, int size )
{
  if( result && size )
  {
    PPIB ppib;
    PTIB ptib;

    DosGetInfoBlocks( &ptib, &ppib );
    DosQueryModuleName( ppib->pib_hmte, size, result );
  }

  return result;
}

/* Returns the current program startup path.
 */

char* PMGUI::program_path( char* result, int size )
{
  char pathname[_MAX_PATH];
  program_name( pathname, sizeof( pathname ));
  return sdrivedir( result, pathname, size );
}

/* Dispatches messages.
 */

void PMGUI::run()
{
  QMSG qms;
  HAB  cur_hab = hab();

  while( WinGetMsg( cur_hab, &qms, 0, 0, 0 )) {
    WinDispatchMsg( cur_hab, &qms );
  }
}

