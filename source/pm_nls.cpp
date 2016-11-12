/*
 * Copyright (C) 2010-2011 Dmitry A.Steklenev
 *
 * $Id: pm_nls.cpp,v 1.4 2012/04/24 11:22:41 glass Exp $
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "pm_nls.h"

COUNTRYINFO PMNLS::m_country_info;
CHAR        PMNLS::m_mapcase[256];
UconvObject PMNLS::m_uco_curcp;

/* Converts the long long integer to the
 * decimal ASCII string separated by thousands.
 */

char* PMNLS::lltoa( char* result, int size, long long number )
{
  char  string[32];
  int   count;
  char* s;
  char* p;

  ::lltoa( number, string, 10 );
  count = strlen( string );

  if( size ) {
    for( s = string, p = result; *s && size > 1; s++, p++, count--, size-- )
    {
      *p = *s;

      if( count > 3 && ( count - 1 ) % 3 == 0 && size > 1 ) {
        *++p = m_country_info.szThousandsSeparator[0];
        size--;
      }
    }
    *p = 0;
  }

  return result;
}

/* Converts time to formatted character string containing
 * separated hours, minutes and seconds.
 */

char* PMNLS::timetohms( char* result, int size, unsigned long seconds )
{
  snprintf( result, size, "%02d%s%02d%s%02d",
            seconds / 3600, m_country_info.szTimeSeparator,
            seconds % 3600 / 60, m_country_info.szTimeSeparator,
            seconds % 60 );

  return result;
}

/* Converts time to formatted character string containing
 * separated hours, minutes and seconds.
 */

char* PMNLS::timetoms( char* result, int size, unsigned long seconds )
{
  snprintf( result, size, "%02d%s%02d",
            seconds / 60, m_country_info.szTimeSeparator,
            seconds % 60 );

  return result;
}

/* Compare strings without case sensitivity.
 */

int PMNLS::stricmp( const char* string1, const char* string2 )
{
  int relationship = 0;

  do {
    relationship = m_mapcase[(unsigned char)*string1] -
                   m_mapcase[(unsigned char)*string2];

  } while( *string1++ && *string2++ && relationship == 0 );

  return relationship;
}

/* Compare strings without case sensitivity.
 */

int PMNLS::strnicmp( const char* string1, const char* string2, int n )
{
  int relationship = 0;

  if( n > 0 ) {
    do {
      relationship = m_mapcase[(unsigned char)*string1] -
                     m_mapcase[(unsigned char)*string2];
    } while( *string1++ && *string2++ && --n && relationship == 0 );
  }

  return relationship;
}

/* Converts any lowercase letters in string to uppercase.
 * Other characters are not affected.
 */

char* PMNLS::strupr( char* string )
{
  char* p = string;

  while( *p ) {
    *p = m_mapcase[(unsigned char)*p];
     p++;
  }

  return string;
}

/* Converts the string from current codepage to the unicode string.
 */

int PMNLS::strtoucs( const char* string, UniChar* result, int size )
{
  if( m_uco_curcp ) {
    if( UniStrToUcs( m_uco_curcp, result, (char*)string, size ) == ULS_SUCCESS ) {
      return UniStrlen( result );
    }
  }
  return -1;
}

/* Converts the unicode string to current codepage string.
 */

int PMNLS::ucstostr( const UniChar* string, char* result, int size )
{
  if( m_uco_curcp ) {
    if( UniStrFromUcs( m_uco_curcp, result, (UniChar*)string, size ) == ULS_SUCCESS ) {
      return strlen( result );
    }
  }
  return -1;
}

