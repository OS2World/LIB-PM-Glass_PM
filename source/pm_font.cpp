/*
 * Copyright (C) 2011 Dmitry A.Steklenev
 *
 * $Id: pm_font.cpp,v 1.1 2011/04/20 11:52:12 glass Exp $
 */

#include <memory.h>
#include <stdlib.h>
#include "pm_error.h"
#include "pm_debuglog.h"
#include "pm_font.h"

/* Constructs the font object from characters string.
 */

PMFont::PMFont( const char* fontname )
{
  const char* pname = fontname;
  const char* pos;
  int         size;

  HPS  ps = WinGetPS( HWND_DESKTOP );
  HDC  dc = GpiQueryDevice( ps );

  LONG rem_fonts = 0;
  LONG req_fonts = 0;
  LONG how_close = 0x7FFFFFFF;
  LONG res_horz  = 0;
  LONG res_vert  = 0;
  LONG vec_match = 0;
  LONG i;

  DevQueryCaps( dc, CAPS_HORIZONTAL_FONT_RES, 1L, &res_horz );
  DevQueryCaps( dc, CAPS_VERTICAL_FONT_RES  , 1L, &res_vert );

  memset( &m_attrs, 0, sizeof(FATTRS));
  m_attrs.usRecordLength = sizeof(FATTRS);
  m_points = 0;

  DEBUGLOG(( "PMFont: begin parse '%s'\n", fontname ));

  if(( pos = strchr( pname, '.' )) != NULL ) {
    m_points = atol( pname );
    DEBUGLOG(( "PMFont: size is %d\n", m_points ));
    pname = pos + 1;
  }
  if(( pos = strchr( pname, '.' )) != NULL ) {
    if(( size = pos - pname + 1 ) > FACESIZE ) {
      size = FACESIZE;
    }
    strlcpy( m_attrs.szFacename, pname, size );
    pname = pos;
  } else {
    strlcpy( m_attrs.szFacename, pname, FACESIZE );
  }

  DEBUGLOG(( "PMFont: face name is %s\n", m_attrs.szFacename ));

  while( *pname == '.' ) {
    if( strnicmp( pname, ".Italic", 7 ) == 0 ) {
      m_attrs.fsSelection |= FATTR_SEL_ITALIC;
      DEBUGLOG(( "PMfonts: FATTR_SEL_ITALIC\n" ));
      pname += 7;
      continue;
    }
    if( strnicmp( pname, ".Outline", 8 ) == 0 ) {
      m_attrs.fsSelection |= FATTR_SEL_OUTLINE;
      DEBUGLOG(( "PMfonts: FATTR_SEL_OUTLINE\n" ));
      pname += 8;
      continue;
    }
    if( strnicmp( pname, ".Strikeout", 10 ) == 0 ) {
      m_attrs.fsSelection |= FATTR_SEL_STRIKEOUT;
      DEBUGLOG(( "PMfonts: FATTR_SEL_STRIKEOUT\n" ));
      pname += 10;
      continue;
    }
    if( strnicmp( pname, ".Underscore", 11 ) == 0 ) {
      m_attrs.fsSelection |= FATTR_SEL_UNDERSCORE;
      DEBUGLOG(( "PMfonts: FATTR_SEL_UNDERSCORE\n" ));
      pname += 11;
      continue;
    }
    if( strnicmp( pname, ".Bold", 5 ) == 0 ) {
      m_attrs.fsSelection |= FATTR_SEL_BOLD;
      DEBUGLOG(( "PMfonts: FATTR_SEL_BOLD\n" ));
      pname += 5;
      continue;
    }
    if(( pos = strchr( pname + 1, '.' )) != NULL ) {
      pname = pos;
    }
  }

  rem_fonts = GpiQueryFonts( ps, QF_PUBLIC | QF_PRIVATE,
                             m_attrs.szFacename, &req_fonts, sizeof(FONTMETRICS), 0 );
  if( rem_fonts != GPI_ALTERROR )
  {
    FONTMETRICS* pfm = (FONTMETRICS*)calloc( sizeof( FONTMETRICS ), rem_fonts );

    if( pfm ) {
      req_fonts = rem_fonts;
      rem_fonts = GpiQueryFonts( ps, QF_PUBLIC | QF_PRIVATE,
                                 m_attrs.szFacename, &req_fonts, sizeof(FONTMETRICS), pfm );
      if( rem_fonts != GPI_ALTERROR ) {
        for( i = 0; i < req_fonts; i++ ) {
          // Vector font doesn't need to check device resolution and point size.
          if( pfm[i].fsDefn & FM_DEFN_OUTLINE )
          {
            vec_match = pfm[i].lMatch;
            continue;
          }
          // Check bitmap font for device resolution and point size.
          if(( pfm[i].sXDeviceRes == res_horz ) &&
             ( pfm[i].sYDeviceRes == res_vert ))
          {
            LONG current_how_close =
                 abs((long)(m_points*10 - pfm[i].sNominalPointSize ));

            if( current_how_close < how_close )
            {
              m_attrs.lMatch = pfm[i].lMatch;
              how_close = current_how_close;

              m_sizef.cx = MAKEFIXED( pfm[i].lEmInc, 0 );
              m_sizef.cy = MAKEFIXED( pfm[i].lEmHeight, 0 );
            }
          }
        }
        if( vec_match && ( !m_attrs.lMatch || how_close != 0 ))
        {
          m_attrs.fsFontUse |= FATTR_FONTUSE_OUTLINE;

          // Calculate the size of the character box, based on the
          // point size selected and the resolution of the device.
          // The size parameters are of type FIXED, NOT int.
          // NOTE: 1 point == 1/72 of an inch.

          m_sizef.cx = ( MAKEFIXED( m_points, 0 ) / 72 ) * res_horz;
          m_sizef.cy = ( MAKEFIXED( m_points, 0 ) / 72 ) * res_vert;
        }
      }
      free( pfm );
    } else {
      PM_THROW_GUIERROR();
    }
  }

  WinReleasePS( ps );
}

/* Returns the face name of the font.
 */

char* PMFont::name( char* result, int size ) const
{
  strlcpy( result, m_attrs.szFacename, size );
  return result;
}

