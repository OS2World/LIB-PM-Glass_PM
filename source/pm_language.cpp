/*
 * Copyright (C) 2001-2008 Dmitry A.Steklenev
 *
 * $Id: pm_language.cpp,v 1.10 2011/03/11 12:59:32 glass Exp $
 */

#include <stdlib.h>
#include <string.h>

#include "pm_language.h"
#include "pm_gui.h"
#include "pm_fileutils.h"

static PMLanguage* PMLanguage::instance = NULL;

/* Constructs the messages management object.
 *
 * Opens the specified by filename messages catalog file
 * and loads all messages of the current language into the
 * program memory.
 */

PMLanguage::PMLanguage( const char* filename )

: m_handle( NULLHANDLE )

{
  LngLoadDialect((char*)filename, &m_handle );
}

/**
 * Constructs the messages management object of a current module.
 *
 * Opens the specified as <i>modulename.nls</i> messages catalog file
 * and loads all messages of the current language into the
 * program memory.
 */

PMLanguage::PMLanguage()

: m_handle( NULLHANDLE )

{
  char nls_filename[_MAX_PATH];
  char mod_filename[_MAX_PATH];

  PMGUI::module_name( mod_filename, sizeof( mod_filename ));

  sdrivedir( nls_filename, mod_filename, sizeof( nls_filename ));
  sfname   ( mod_filename, mod_filename, sizeof( mod_filename ));
  strlcat  ( nls_filename, mod_filename, sizeof( nls_filename ));
  strlcat  ( nls_filename, ".nls", sizeof( nls_filename ));

  LngLoadDialect( nls_filename, &m_handle );
}

/* Destructs the messages management object.
 */

PMLanguage::~PMLanguage()
{
  if( m_handle != NULLHANDLE  ) {
    LngCloseDialect( m_handle );
  }
}

/* Retrieves a message from the messages catalog.
 */

char* PMLanguage::message( char* result, int size, const char* key )
{
  char* mangled = (char*)malloc( strlen( key ) * 2 + 1 );

  if( !mangled ) {
    strlcpy( result, key, size );
    return result;
  }

  const char* source = key;
  char* target = mangled;

  while( *source ) {
     if( *source == '\n' ) {
       *target++ = '\\'; *target++ = 'n';
     } else if( *source == '\r' ) {
       *target++ = '\\'; *target++ = 'r';
     } else if( *source == '\t' ) {
       *target++ = '\\'; *target++ = 't';
     } else if( *source == '\\' ) {
       *target++ = '\\'; *target++ = '\\';
     } else {
       *target++ = *source;
     }
     ++source;
  }
  *target = 0;

  LngGetString( m_handle, mangled, result, size );

  source = result;
  target = result;

  while( *source ) {
    if( source[0] == '\\' ) {
      if( source[1] == 'n' ) {
        *target++ = '\n'; source += 2;
      } else if( source[1] == 'r' ) {
        *target++ = '\r'; source += 2;
      } else if( source[1] == 't' ) {
        *target++ = '\t'; source += 2;
      } else if( source[1] == '\\' ) {
        *target++ = '\\'; source += 2;
      } else {
        *target++ = *source++;
      }
    } else {
      *target++ = *source++;
    }
  }
  *target = 0;

  free( mangled );
  return result;
}

/* Retrieves a pointer to message from the messages catalog.
 */

char* PMLanguage::message_ptr( const char* key ) const {
  return LngGetStringPointer( m_handle, (PSZ)key );
}

