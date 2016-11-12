/*
 * Copyright (C) 2001-2010 Dmitry A.Steklenev
 *
 * $Id: pm_error.cpp,v 1.5 2011/03/11 12:59:31 glass Exp $
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "pm_gui.h"
#include "pm_error.h"

#ifdef   ECS
#include <progress.h>
#endif

extern const char* application_name;

/* Constructs an error object describing a
 * current GUI (PM) error.
 */

PMError::PMError( const char* file, const char* func, int line )

: m_file ( strdup( file  )),
  m_func ( strdup( func  )),
  m_group( strdup( "WIN" )),
  m_line ( line ),
  m_code ( 0    ),
  m_tid  ( PMGUI::tid())
{
  PERRINFO info = WinGetErrorInfo( PMGUI::hab());

  if( info ) {
    m_code = info->idError;
    m_what = strdup((char*)info + ((char*)info + info->offaoffszMsg)[0] );
  } else {
    m_what = strdup( "No error text is available" );
  }

  if( info ) {
    WinFreeErrorInfo( info );
  }
}

/* Constructs an error object from the specified error
 * id and information.
 */

PMError::PMError( int code, const char* group, const char* what,
                            const char* file,  const char* func, int line )
: m_file ( strdup( file  )),
  m_func ( strdup( func  )),
  m_group( strdup( group )),
  m_line ( line ),
  m_code ( code ),
  m_tid  ( PMGUI::tid())
{
  if( !what )
  {
    char   szErrInfo[1024];
    ULONG  ulMessageLength;
    APIRET rc;

    rc = DosGetMessage( 0, 0, (PCHAR)szErrInfo, sizeof(szErrInfo),
                        code, (PSZ)"OSO001.MSG", &ulMessageLength );

    szErrInfo[ulMessageLength] = 0;
    m_what = strdup( rc ? "No error text is available." : szErrInfo );
  } else {
    m_what = strdup( what );
  }
}

/* Copies the error object.
 */

PMError::PMError( const PMError& error )

: m_file ( error.m_file  ? strdup( error.m_file  ) : NULL ),
  m_func ( error.m_func  ? strdup( error.m_func  ) : NULL ),
  m_group( error.m_group ? strdup( error.m_group ) : NULL ),
  m_what ( error.m_what  ? strdup( error.m_what  ) : NULL ),
  m_line ( error.m_line ),
  m_code ( error.m_code ),
  m_tid  ( error.m_tid  )
{}

/* Destroys the error object.
 */

PMError::~PMError()
{
  free( m_what  );
  free( m_func  );
  free( m_file  );
  free( m_group );
}

/* Displays the error information.
 */

PMError& PMError::show( FILE* out )
{
  const char* msg_format = "Unexpected error at:\n"
                           "   file: %s\n"
                           "   function: %s\n"
                           "   line: %u\n\n"
                           "Error group is: %s\n"
                           "Thread Id is: %d (%x)\n"
                           "Error Id is: %u (%x)\n"
                           "Exception text is:\n\n"
                           "%s\n";
  char  msg_title[71];
  char* msg_buffer = new char[ strlen( msg_format ) +
                             ( m_file  ? strlen( m_file     ) : 0 ) +
                             ( m_group ? strlen( m_group    ) : 0 ) +
                             ( m_func  ? strlen( m_func     ) : 0 ) +
                             ( m_what  ? strlen( m_what     ) : 0 ) + 80 ];
  if( !msg_buffer ) {
    DosBeep( 1000, 100 );
    return *this;
  }

  sprintf( msg_buffer, msg_format, m_file  ? m_file  : "",
                                   m_func  ? m_func  : "", m_line,
                                   m_group ? m_group : "", m_tid, m_tid, m_code, m_code,
                                   m_what  ? m_what  : ""  );
  if( out ) {
    fwrite( msg_buffer, 1, strlen( msg_buffer ), out );
    fflush( out );
  } else {
    #ifdef ECS
    sprintf( msg_title, "%s", application_name );
    ExMessageBox ( HWND_DESKTOP, HWND_DESKTOP, "Critical Error", msg_title, 100,
                   MB_OK | MB_ERROR | MB_COMMENT | MB_APPLMODAL | MB_PREFORMAT | MB_ANIMATED, msg_buffer );
    #else
    sprintf( msg_title, "%-070s", application_name );
    WinMessageBox( HWND_DESKTOP, HWND_DESKTOP, msg_buffer, msg_title, 100,
                   MB_OK | MB_ERROR | MB_APPLMODAL | MB_MOVEABLE );
    #endif
  }

  delete[] msg_buffer;
  return *this;
}
