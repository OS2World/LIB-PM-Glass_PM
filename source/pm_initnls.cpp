/*
 * Copyright (C) 2010-2011 Dmitry A.Steklenev
 *
 * $Id: pm_initnls.cpp,v 1.3 2012/04/24 11:22:41 glass Exp $
 */

#include <string.h>
#include "pm_initnls.h"
#include "pm_nls.h"

ULONG PMInitNLS::m_initialized = 0;

/* Initializes the national language support class.
 */

PMInitNLS::PMInitNLS()
{
  if( !m_initialized++ )
  {
    COUNTRYCODE countrycode = { 0, 0 };
    int   i;
    ULONG bytes;

    for( i = 0; i < 256; i++ ) {
      PMNLS::m_mapcase[i] = (CHAR)i;
    }

    DosMapCase( 256, &countrycode, PMNLS::m_mapcase );

    if( DosQueryCtryInfo( sizeof( PMNLS::m_country_info ), &countrycode,
                                 &PMNLS::m_country_info, &bytes ) != NO_ERROR )
    {
      strcpy( PMNLS::m_country_info.szThousandsSeparator, " " );
      strcpy( PMNLS::m_country_info.szTimeSeparator, ":" );
    }

    ULONG   cpage[1] = { 0 };
    ULONG   cb = sizeof( cpage );
    UniChar cpname[16];

    DosQueryCp( cb, cpage, &cb );
    if( UniMapCpToUcsCp( cpage[0], cpname, 16 ) == ULS_SUCCESS ) {
      UniCreateUconvObject( cpname, &PMNLS::m_uco_curcp );
    }
  }
}

/* Termnates the national language support class.
 */

PMInitNLS::~PMInitNLS() {
  // FIX ME!!!
  --m_initialized;
}

