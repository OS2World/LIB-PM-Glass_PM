/*
 * Copyright (C) 2009-2010 Dmitry A.Steklenev
 *
 * $Id: pm_png.cpp,v 1.7 2011/04/19 13:11:32 glass Exp $
 */

#include <stdlib.h>
#include "pm_png.h"
#include "pm_error.h"
#include "pm_debuglog.h"

#define SM_LOADIMAGE  0x0110
#define SM_AUTOSIZE   0x0111
#define TID_ANIMATE   0xFFF0

/* Wraps the static image control window object around
 * an existing presentation window handle.
 */

PMPNG::PMPNG( HWND handle )

: PMWindow     ( handle ),
  m_phbm2_owner( FALSE  ),
  m_count      ( 0      ),
  m_phase      ( 0      ),
  m_phbm2      ( NULL   )
{
  HBITMAP2 hbm2 = (HBITMAP2)send( SM_QUERYHANDLE, 0, 0 );

  if( hbm2 ) {
    if(( m_phbm2 = (HBITMAP2*)malloc( sizeof( HBITMAP ))) != NULL ) {
      m_phbm2[0] = hbm2;
      m_count    = 1;
    } else {
      PM_THROW_CLIBERROR();
    }
  }
}

/* Wraps the static image control window object around
 * an existing child window with the specified identity.
 */

PMPNG::PMPNG( HWND hparent, SHORT id )

: PMWindow     ( hparent, id ),
  m_phbm2_owner( FALSE  ),
  m_count      ( 0      ),
  m_phase      ( 0      ),
  m_phbm2      ( NULL   )
{
  HBITMAP2 hbm2 = (HBITMAP2)send( SM_QUERYHANDLE, 0, 0 );

  if( hbm2 ) {
    if(( m_phbm2 = (HBITMAP2*)malloc( sizeof( HBITMAP ))) != NULL ) {
      m_phbm2[0] = hbm2;
      m_count    = 1;
    } else {
      PM_THROW_CLIBERROR();
    }
  }
}

/* Constructs the static image control window.
 */

PMPNG::PMPNG( SHORT id, HWND hparent, LONG x, LONG y,
                        LONG cx, LONG cy, SHORT res_id, HMODULE hmodule, ULONG style )

: PMWindow     ( id, "", hparent, hparent, x, y, cx, cy, style ),
  m_phbm2_owner( FALSE  ),
  m_count      ( 0      ),
  m_phase      ( 0      ),
  m_phbm2      ( NULL   )
{
  if( res_id ) {
    image( res_id, hmodule );
  }
}

/* Destructs the static image control window.
 */

PMPNG::~PMPNG() {
  if( is_valid()) {
    send( SM_SETHANDLE, MPFROMLONG( NULLHANDLE ), 0 );
  }
}

/* Sets the image.
 */

void PMPNG::image( SHORT res_id, HMODULE hmodule ) {
  send( SM_LOADIMAGE, MPFROMLONG( hmodule ), MPFROM2SHORT( res_id, 1 ));
}

/* Sets an animation sequence.
 */

void PMPNG::animate( SHORT res_id, HMODULE hmodule, SHORT count, ULONG ms )
{
  send( SM_LOADIMAGE, MPFROMLONG( hmodule ), MPFROM2SHORT( res_id, count ));
  if( count > 1 ) {
    start_timer( TID_ANIMATE, ms );
  }
}

/* Dispatch system native events.
 *
 * This method is called when a system native window
 * event occurs.
 */

MRESULT PMPNG::dispatch( ULONG msg, MPARAM mp1, MPARAM mp2 )
{
  switch( msg ) {
    case WM_DESTROY:
      // The bitmap handle must be also deleted here because presentation
      // window can be destroyed before object destruction. In other cases
      // the WM_DESTROY message can not be received here.
      send( SM_SETHANDLE, MPFROMLONG( NULLHANDLE ), 0 );
      break;

    case SM_LOADIMAGE:
    {
      SHORT   res_id  = SHORT1FROMMP(mp2);
      SHORT   count   = SHORT2FROMMP(mp2);
      HMODULE hmodule = LONGFROMMP(mp1);
      PVOID   png_data;
      APIRET  rc;
      int     i;

      if( m_phbm2_owner && m_phbm2 ) {
        for( i = 0; i < m_count; i++ ) {
          if( m_phbm2[i] ) {
            Gpi2DeleteBitmap( m_phbm2[i] );
          }
        }
      }
      if( m_count > 1 ) {
        stop_timer( TID_ANIMATE );
      }

      m_phbm2_owner = FALSE;
      m_count = 0;
      m_phase = 0;

      if(( m_phbm2 = (HBITMAP2*)malloc( count * sizeof( HBITMAP ))) == NULL ) {
        PM_THROW_CLIBERROR();
      }

      DEBUGLOG(( "DosGetResource %08X %d %d\n", hmodule, RT_PNG, res_id ));

      for( i = 0; i < count; i++ ) {
        if(( rc = DosGetResource( hmodule, RT_PNG, res_id + i, &png_data )) != NO_ERROR ) {
          PM_THROW_DOSERROR( rc );
        }

        m_phbm2[i] = Gpi2ReadPng((PBYTE)png_data, 0, 0 );

        if(( rc = DosFreeResource( png_data )) != NO_ERROR ) {
          PM_THROW_DOSERROR( rc );
        }
      }

      m_phbm2_owner = TRUE;
      m_count = count;

      send( SM_AUTOSIZE, 0, 0 );
      return 0;
    }

    case SM_AUTOSIZE:
      if( m_phbm2 && m_phbm2[0] != NULLHANDLE ) {
        if( WinQueryWindowULong( handle(), QWL_STYLE ) & SS_AUTOSIZE )
        {
          PMRect rect = rectangle();

          BITMAP2HEADER bmp2h;
          Gpi2QueryBitmapInfo( m_phbm2[0], &bmp2h );

          rect.cx = bmp2h.usCx;
          rect.cy = bmp2h.usCy;
          rectangle( rect );
        } else {
          invalidate();
        }
      }
      return 0;

    case SM_QUERYHANDLE:
      if( m_phbm2 && m_phbm2[0] != NULLHANDLE ) {
        return MRFROMLONG( m_phbm2[0] );
      } else {
        return MRFROMLONG( NULLHANDLE );
      }

    case SM_SETHANDLE:
    {
      int i;

      if( m_phbm2_owner && m_phbm2 ) {
        for( i = 0; i < m_count; i++ ) {
          if( m_phbm2[i] ) {
            Gpi2DeleteBitmap( m_phbm2[i] );
          }
        }
      }
      if( m_count > 1 ) {
        stop_timer( TID_ANIMATE );
      }

      m_phbm2_owner = FALSE;
      m_count = 0;
      m_phase = 0;

      if(( m_phbm2 = (HBITMAP2*)malloc( sizeof( HBITMAP ))) == NULL ) {
        PM_THROW_CLIBERROR();
      }

      m_phbm2[0] = LONGFROMMP( mp1 );
      m_phbm2_owner = FALSE;
      m_count = 1;

      send( SM_AUTOSIZE, 0, 0 );
      return 0;
    }

    case WM_ERASEBACKGROUND:
      return FALSE;

    case WM_QUERYDLGCODE:
      return MRFROMLONG( DLGC_STATIC );

    case WM_TIMER:
      if( SHORT1FROMMP(mp1) == TID_ANIMATE ) {
        if( ++m_phase >= m_count ) {
          m_phase = 0;
        }
        invalidate();
        return 0;
      }
      break;

    case WM_PAINT:
    {
      HPS hps = WinBeginPaint( handle(), NULL, NULL );

      if( m_phbm2 && m_phbm2[m_phase] != NULLHANDLE )
      {
        POINTL pos   = { 0, 0 };
        PMRect rect  = rectangle();
        ULONG  style = WinQueryWindowULong( handle(), QWL_STYLE );

        BITMAP2HEADER bmp2h;
        Gpi2QueryBitmapInfo( m_phbm2[m_phase], &bmp2h );

        if( style & DT_CENTER ) {
          pos.x = ( rect.cx - bmp2h.usCx ) / 2;
        } else if( style & DT_RIGHT ) {
          pos.x = ( rect.cx - bmp2h.usCx );
        }
        if( style & DT_VCENTER ) {
          pos.y = ( rect.cy - bmp2h.usCy ) / 2;
        } else if( style & DT_TOP ) {
          pos.y = ( rect.cy - bmp2h.usCy );
        }

        Gpi2DrawBitmap( hps, m_phbm2[m_phase], 1, &pos );
      }

      WinEndPaint( hps );
      return 0;
    }
  }

  return PMWindow::dispatch( msg, mp1, mp2 );
}
