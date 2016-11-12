/*
 * Copyright (C) 2001-2008 Dmitry A.Steklenev
 *
 * $Id: pm_profile.cpp,v 1.8 2012/06/26 12:07:42 glass Exp $
 */

#include "pm_profile.h"
#include "pm_error.h"
#include "pm_fileutils.h"
#include "pm_gui.h"

/* Constructs a profile object.
 */

PMProfile::PMProfile( const char* filename )
{
  m_handle  = PrfOpenProfile( PMGUI::hab(), filename );
  m_wrapped = FALSE;

  if( m_handle == NULLHANDLE ) {
    PM_THROW_GUIERROR();
  }
}

/* Constructs a profile object from an existing profile handle.
 */

PMProfile::PMProfile( HINI handle )
{
  m_handle  = handle;
  m_wrapped = TRUE;
}

/* Constructs a profile object of a current module.
 */

PMProfile::PMProfile()
{
  char ini_filename[_MAX_PATH];
  char mod_filename[_MAX_PATH];

  PMGUI::module_name( mod_filename, sizeof( mod_filename ));

  sdrivedir( ini_filename, mod_filename, sizeof( ini_filename ));
  sfname   ( mod_filename, mod_filename, sizeof( mod_filename ));
  strlcat  ( ini_filename, mod_filename, sizeof( ini_filename ));
  strlcat  ( ini_filename, ".ini", sizeof( ini_filename ));

  m_handle  = PrfOpenProfile( PMGUI::hab(), ini_filename );
  m_wrapped = FALSE;

  if( m_handle == NULLHANDLE ) {
    PM_THROW_GUIERROR();
  }
}

/* Destructs the profile object.
 */

PMProfile::~PMProfile()
{
  if( m_handle != NULLHANDLE && !m_wrapped ) {
    if( !PrfCloseProfile( m_handle )) {
      PM_THROW_GUIERROR();
    }
  }
}

/* This method writes a binary data into the profile.
 */

void PMProfile::put_data( const char* app,  const char* key,
                          const void* data, unsigned long len )
{
  if( !PrfWriteProfileData( m_handle, app, key, (PVOID)data, len )) {
    PM_THROW_GUIERROR();
  }
}

/* This method writes a long integer value
 * into the profile.
 */

void PMProfile::put_integer( const char* app, const char* key, long value ) {
  put_data( app, key, &value, sizeof( value ));
}

/* This method writes a unsigned long integer
 * value into the profile.
 */

void PMProfile::put_integer( const char* app, const char* key, unsigned long value ) {
  put_data( app, key, &value, sizeof( value ));
}

/* This method writes a short integer value
 * into the profile.
 */

void PMProfile::put_integer( const char* app, const char* key, short value ) {
  put_data( app, key, &value, sizeof( value ));
}

/* This method writes a unsigned short
 * integer value into the profile.
 */

void PMProfile::put_integer( const char* app, const char* key, unsigned short value ) {
  put_data( app, key, &value, sizeof( value ));
}

/* This method writes a character string
 * into the profile.
 */

void PMProfile::put_string( const char* app, const char* key, const char* string )
{
  if( !PrfWriteProfileString( m_handle, app, key, string )) {
    PM_THROW_GUIERROR();
  }
}

/* Returns the size in bytes of the value of a specified key for
 * a specified application in the profile.
 */

unsigned long PMProfile::get_size( const char* app, const char* key ) const
{
  ULONG size;

  if( PrfQueryProfileSize( m_handle, app, key, &size )) {
    return size;
  } else {
    return 0;
  }
}

/* Returns a binary data from the profile.
 */

BOOL PMProfile::get_data( const char* app,  const char* key,
                                void* data, unsigned long* len ) const
{
  return PrfQueryProfileData( m_handle, app, key, data, len );
}

/* Returns a long integer value from the profile.
 */

BOOL PMProfile::get_integer( const char* app, const char *key, long* value ) const
{
  long  data;
  ULONG len = sizeof( data );

  if( PrfQueryProfileData( m_handle, app, key, &data, &len ) &&
      len == sizeof( data ))
  {
    *value = data;
    return TRUE;
  }

  return FALSE;
}

/* Returns a unsigned long integer value
 * from the profile.
 */

BOOL PMProfile::get_integer( const char* app, const char *key, unsigned long* value ) const
{
  unsigned long data;
  ULONG len = sizeof( data );

  if( PrfQueryProfileData( m_handle, app, key, &data, &len ) &&
      len == sizeof( data ))
  {
    *value = data;
    return TRUE;
  }

  return FALSE;
}

/* Returns a short integer value from the profile.
 */

BOOL PMProfile::get_integer( const char* app, const char *key, short* value ) const
{
  short data;
  ULONG len = sizeof( data );

  if( PrfQueryProfileData( m_handle, app, key, &data, &len ) &&
      len == sizeof( data ))
  {
    *value = data;
    return TRUE;
  }

  return FALSE;
}

/* Returns a unsigned short integer value
 * from the profile.
 */

BOOL PMProfile::get_integer( const char* app, const char *key, unsigned short* value ) const
{
  unsigned short data;
  ULONG len = sizeof( data );

  if( PrfQueryProfileData( m_handle, app, key, &data, &len ) &&
      len == sizeof( data ))
  {
    *value = data;
    return TRUE;
  }

  return FALSE;
}

/* Returns a character string from the profile.
 */

BOOL PMProfile::get_string( const char* app, const char *key,
                            char* string, unsigned long  len ) const
{
  unsigned long done = len;
  BOOL rc = FALSE;

  if( len ) {
    if(( rc = PrfQueryProfileData( m_handle, app, key, string, &done )) == TRUE ) {
      string[( done < len ) ? done : ( len - 1 )] = 0;
    }
  }

  return rc;
}

/* Copies the specified data from one profile to another.
 */

BOOL PMProfile::copy( HINI ini_from, const char* app_from, const char* key_from,
                      HINI ini_to,   const char* app_to,   const char* key_to )
{
  ULONG size;
  PVOID data;
  BOOL  rc = FALSE;

  if( PrfQueryProfileSize( ini_from, app_from, key_from, &size )) {
    data = malloc( size );
    if( data ) {
      if( PrfQueryProfileData( ini_from, app_from, key_from, data, &size )) {
        if( PrfWriteProfileData( ini_to, app_to, key_to, data, size )) {
          rc = TRUE;
        }
      }
      free( data );
    }
  }

  return rc;
}

/* Moves the specified data from one profile to another.
 */

BOOL PMProfile::move( HINI ini_from, const char* app_from, const char* key_from,
                      HINI ini_to,   const char* app_to,   const char* key_to )
{
  if( copy( ini_from, app_from, key_from, ini_to, app_to, key_to )) {
    return PrfWriteProfileData( ini_from, app_from, key_from, NULL, 0 );
  } else {
    return FALSE;
  }
}

/* Saves the current size and position of the window
 * specified by hwnd. This function will also
 * save the presentation parameters.
 */

BOOL PMProfile::save_window( const char* app, const char *key,
                                         HWND hwnd, int options )
{
  char   key1st[128];
  char   key2st[128];
  char   key3st[128];
  BOOL   rc = FALSE;
  SWP    swp;
  POINTL pos[2];

  snprintf( key1st, sizeof( key1st ), "%s@%08lX", key, PMGUI::pid());
  snprintf( key2st, sizeof( key2st ), "%s@pos",   key );
  snprintf( key3st, sizeof( key3st ), "%s@map",   key );

  if( WinStoreWindowPos( app, key1st, hwnd )) {
    if( move( HINI_PROFILE, app, key1st, m_handle, app, key2st )) {
      rc = TRUE;
    }
  }
  if( rc && ( options & map_points )) {
    if( WinQueryWindowPos( hwnd, &swp )) {
      pos[0].x = swp.x;
      pos[0].y = swp.y;
      pos[1].x = swp.x + swp.cx;
      pos[1].y = swp.y + swp.cy;

      WinMapDlgPoints( hwnd, pos, 2, FALSE );
      rc = PrfWriteProfileData( m_handle, app, key3st, pos, sizeof( pos ));
    }
  }

  return rc;
}

/* Restores the size and position of the window specified
 * by hwnd to the state it was in when save_window
 * was last called. This function will also restore presentation
 * parameters.
 */

BOOL PMProfile::rest_window( const char* app, const char *key,
                                         HWND hwnd, int options )
{
  char   key1st[128];
  char   key2st[128];
  char   key3st[128];
  BOOL   rc    = FALSE;
  BOOL   fixed = FALSE;
  POINTL pos[2];
  SWP    swp;
  SWP    desktop;
  ULONG  len = sizeof(pos);

  snprintf( key1st, sizeof( key1st ), "%s@%08lX", key, PMGUI::pid());
  snprintf( key2st, sizeof( key2st ), "%s@pos",   key );
  snprintf( key3st, sizeof( key3st ), "%s@map",   key );

  if(!((ULONG)WinSendMsg( hwnd, WM_QUERYFRAMEINFO, 0, 0 ) & FI_FRAME ) ||
     !( WinQueryWindowULong( hwnd, QWL_STYLE ) & FS_SIZEBORDER ))
  {
    fixed = TRUE;
    WinQueryWindowPos( hwnd, &swp );
  }

  if( copy( m_handle, app, key2st, HINI_PROFILE, app, key1st )) {
    rc = WinRestoreWindowPos( app, key1st, hwnd );
    PrfWriteProfileData( HINI_PROFILE, app, key1st, NULL, 0 );
  }

  if( rc && ( options & map_points )) {
    if( PrfQueryProfileData( m_handle, app, key3st, pos, &len ))
    {
      WinMapDlgPoints( hwnd, pos, 2, TRUE );
      // Without SWP_NOADJUST flag the WinSetWindowPos produces some strange effects
      // at using ePager.
      WinSetWindowPos( hwnd, 0, pos[0].x, pos[0].y,
                       pos[1].x-pos[0].x, pos[1].y-pos[0].y, SWP_MOVE | SWP_SIZE | SWP_NOADJUST );
    } else {
      rc = FALSE;
    }
  }

  if( fixed ) {
    WinSetWindowPos( hwnd, 0, 0, 0, swp.cx, swp.cy, SWP_SIZE );
  }

  if( rc && WinQueryWindowPos( hwnd, &swp )
         && WinQueryWindowPos( HWND_DESKTOP, &desktop ))
  {
    if( swp.y + swp.cy > desktop.cy )
    {
      swp.y = desktop.cy - swp.cy;
      WinSetWindowPos( hwnd, 0, swp.x, swp.y, 0, 0, SWP_MOVE );
    }
  }

  return rc;
}

