/*
 * Copyright (C) 2008-2011 Dmitry A.Steklenev
 *
 * $Id: pm_splitcanvas.cpp,v 1.15 2011/07/01 10:59:25 glass Exp $
 */

#include "pm_splitcanvas.h"
#include "pm_debuglog.h"
#include "pm_gui.h"

/* Constructs the split canvas window.
 */

PMSplitCanvas::PMSplitCanvas( SHORT id, const char* text, HWND hparent,
                                        LONG x, LONG y, LONG cx, LONG cy, ULONG style )

: PMWindow         ( id, "", hparent, hparent, x, y, cx, cy, style & 0xFFFFFFF0UL ),
  m_titlebar       ( FID_TITLEBAR, text, handle(), 0, 0, 0, 0, 0 ),
  m_percentage     ( 50    ),
  m_style          ( style ),
  m_moved          ( FALSE ),
  m_drag_percentage( 50    ),
  m_drag_start     (  0    ),
  m_drag_x         (  0    ),
  m_drag_y         (  0    )
{
  m_panes[0] = NULL;
  m_panes[1] = NULL;

  m_bar_cx = WinQuerySysValue( HWND_DESKTOP, SV_CXSIZEBORDER );
  m_bar_cy = WinQuerySysValue( HWND_DESKTOP, SV_CYSIZEBORDER );

  if( m_style & SP_2D ) {
    m_bar_cx -= 1;
    m_bar_cy -= 1;
  }

  if( m_style & SP_TITLEBAR ) {
    m_titlebar.show();
  }

  send( PM_FORMATFRAME, 0, 0 );
}

/* Destructs the split canvas window.
 */

PMSplitCanvas::~PMSplitCanvas()
{
  if( is_valid()) {
    send( PM_SETEXTENSION, 0, MPFROM2SHORT( PMA_SE_DETACH, 0 ));
    send( PM_SETEXTENSION, 0, MPFROM2SHORT( PMA_SE_DETACH, 1 ));
  }
}

/* Sets the window used as the split canvas pane area.
 */

void PMSplitCanvas::pane( HWND hwnd, SHORT id ) {
  send( PM_SETEXTENSION, MPFROMHWND( hwnd ), MPFROM2SHORT( PMA_SE_ATTACH, id ));
}

/* Returns the window used as the split canvas pane area.
 */

HWND PMSplitCanvas::pane( SHORT id ) const {
  return (HWND)WinSendMsg( handle(), PM_GETEXTENSION, 0, MPFROM2SHORT( id, 0 ));
}

/* Sets the the split canvas title text.
 */

void PMSplitCanvas::text( const char* text ) {
  m_titlebar.text( text );
}

/* Returns the split canvas title text.
 */

char* PMSplitCanvas::text( char* result, int size ) const {
  return m_titlebar.text( result, size );
}

/* Sets the percentage of the first split canvas pane.
 */

void PMSplitCanvas::percentage( unsigned int percentage )
{
  m_percentage = percentage;
  send( PM_FORMATFRAME, 0, 0 );
}

/* Sets the orientation of the split bars.
 */

void PMSplitCanvas::orientation( int style )
{
  m_style = ( m_style & ~( SP_VERTICAL | SP_HORIZONTAL )) |
            (   style &  ( SP_VERTICAL | SP_HORIZONTAL ));

  send( PM_FORMATFRAME, 0, 0 );
}

/* Returns the orientation of the split bars.
 */

int PMSplitCanvas::orientation() const {
  return m_style & ( SP_VERTICAL | SP_HORIZONTAL );
}

/* Makes the canvas title bar visible.
 */

void PMSplitCanvas::show_title( BOOL state )
{
  if( state ) {
    if(!( m_style & SP_TITLEBAR )) {
      m_style |= SP_TITLEBAR;
      m_titlebar.show();

      if( WinIsChild( WinQueryFocus( HWND_DESKTOP ), handle())) {
        m_titlebar.hilite();
      }

      send( PM_FORMATFRAME, 0, 0 );
    }
  } else {
    if( m_style & SP_TITLEBAR ) {
      m_titlebar.hide();
      m_style &= ~SP_TITLEBAR;
      send( PM_FORMATFRAME, 0, 0 );
    }
  }
}

/* Makes the canvas title bar invisible.
 */

void PMSplitCanvas::hide_title() {
  show_title( FALSE );
}

/* Reformats the split canvas panes.
 * Must be called only from a window thread.
 */

void PMSplitCanvas::win_format()
{
  PMRect canvas = rectangle();

  if( m_style & SP_TITLEBAR )
  {
    PMRect rect( 0,
                 canvas.cy - PMGUI::metric( SV_CYTITLEBAR ),
                 canvas.cx,
                 PMGUI::metric( SV_CYTITLEBAR )
                );

    m_titlebar.rectangle( rect );
    canvas.cy -= rect.cy;
  }

  if( m_style & SP_HORIZONTAL )
  {
    m_rects[0].x  = 0;
    m_rects[0].y  = 0;
    m_rects[0].cy = ( canvas.cy - m_bar_cy ) * m_percentage / 100;
    m_rects[0].cx = ( canvas.cx );

    m_splitbar.x  = 0;
    m_splitbar.y  = m_rects[0].cy;
    m_splitbar.cy = m_bar_cy;
    m_splitbar.cx = m_rects[0].cx;

    m_rects[1].x  = 0;
    m_rects[1].y  = m_rects[0].cy + m_splitbar.cy;
    m_rects[1].cy = canvas.cy - m_splitbar.cy - m_rects[0].cy;
    m_rects[1].cx = canvas.cx;
  } else {
    m_rects[0].x  = 0;
    m_rects[0].y  = 0;
    m_rects[0].cy = ( canvas.cy );
    m_rects[0].cx = ( canvas.cx - m_bar_cx ) * m_percentage / 100;

    m_splitbar.x  = m_rects[0].cx;
    m_splitbar.y  = 0;
    m_splitbar.cy = m_rects[0].cy;
    m_splitbar.cx = m_bar_cx;

    m_rects[1].x  = m_rects[0].cx + m_splitbar.cx;
    m_rects[1].y  = 0;
    m_rects[1].cy = canvas.cy;
    m_rects[1].cx = canvas.cx - m_splitbar.cx - m_rects[0].cx;
  }

  if( m_style & SP_BORDER1 ) {
    m_rects[0].shrink_by(2);
  }
  if( m_style & SP_BORDER2 ) {
    m_rects[1].shrink_by(2);
  }

  if( m_panes[0] && m_panes[0]->is_valid()) {
    m_panes[0]->rectangle( m_rects[0] );
  }
  if( m_panes[1] && m_panes[1]->is_valid()) {
    m_panes[1]->rectangle( m_rects[1] );
  }

  if( m_style & SP_BORDER1 ) {
    m_rects[0].expand_by(2);
  }
  if( m_style & SP_BORDER2 ) {
    m_rects[1].expand_by(2);
  }

  invalidate();
}

/* Identify the type of control.
 * Must be called only from a window thread.
 */

LONG PMSplitCanvas::win_pdlgcode( SHORT id )
{
  if( id < 0 || id > 1 || !m_panes[id] || !m_panes[id]->is_valid()) {
    return DLGC_STATIC;
  } else {
    return LONGFROMMR( m_panes[id]->send( WM_QUERYDLGCODE, 0, 0 ));
  }
}

/* Returns the pane window which user can tab.
 * Must be called only from a window thread.
 */

HWND PMSplitCanvas::win_penum( SHORT code, HWND hwndbase )
{
  SHORT i1 = ( m_style & SP_HORIZONTAL ) ? 1 : 0;
  SHORT i2 = (SHORT)( i1 ^ 1 );
  LONG  dlgcode;
  HWND  hwnd;

  switch( code ) {
    case PMA_GE_LAST:
      i2 ^= 1;
      i1 ^= 1;
      // continue to PMA_GE_FIRST...

    case PMA_GE_FIRST:
    {
      dlgcode = win_pdlgcode(i1);

      if( dlgcode == DLGC_SPCANVAS ) {
        return (HWND)m_panes[i1]->send( PM_GETEXTENSION, 0, MPFROM2SHORT( code, 0 ));
      }
      if( dlgcode != DLGC_STATIC ) {
        return m_panes[i1]->handle();
      }

      dlgcode = win_pdlgcode(i2);

      if( dlgcode == DLGC_SPCANVAS ) {
        return (HWND)m_panes[i2]->send( PM_GETEXTENSION, 0, MPFROM2SHORT( code, 0 ));
      }
      if( dlgcode != DLGC_STATIC ) {
        return m_panes[i2]->handle();
      }

      break;
    }

    case PMA_GE_NEXT:
    {
      if( m_panes[i1] &&
          m_panes[i1]->is_valid() &&
          WinIsChild( hwndbase, m_panes[i1]->handle()))
      {
        dlgcode = win_pdlgcode(i2);

        if( dlgcode == DLGC_SPCANVAS ) {
          return (HWND)m_panes[i2]->send( PM_GETEXTENSION, 0, MPFROM2SHORT( PMA_GE_FIRST, 0 ));
        }
        if( dlgcode != DLGC_STATIC ) {
          return m_panes[i2]->handle();
        }
      }

      hwnd = WinEnumDlgItem( owner(), handle(), EDI_NEXTTABITEM );

      if( hwnd ) {
        if((LONG)WinSendMsg( hwnd, WM_QUERYDLGCODE, 0, 0 ) == DLGC_SPCANVAS ) {
          return (HWND)WinSendMsg( hwnd, PM_GETEXTENSION, 0, MPFROM2SHORT( PMA_GE_FIRST, 0 ));
        } else {
          return hwnd;
        }
      }
      break;
    }

    case PMA_GE_PREV:
    {
      if( m_panes[i2] &&
          m_panes[i2]->is_valid() &&
          WinIsChild( hwndbase, m_panes[i2]->handle()))
      {
        dlgcode = win_pdlgcode(i1);

        if( dlgcode == DLGC_SPCANVAS ) {
          return (HWND)m_panes[i1]->send( PM_GETEXTENSION, 0, MPFROM2SHORT( PMA_GE_LAST, 0 ));
        }
        if( dlgcode != DLGC_STATIC ) {
          return m_panes[i1]->handle();
        }
      }

      hwnd = WinEnumDlgItem( owner(), handle(), EDI_PREVTABITEM );
      DEBUGLOG2(( "PMSplitCanvas [%08X] WinEnumDlgItem( %08X, %08X, EDI_PREVTABITEM ) return %08X\n",
                   handle(), owner(), handle(), hwnd ));

      if( hwnd ) {
        if((LONG)WinSendMsg( hwnd, WM_QUERYDLGCODE, 0, 0 ) == DLGC_SPCANVAS ) {
          return (HWND)WinSendMsg( hwnd, PM_GETEXTENSION, 0, MPFROM2SHORT( PMA_GE_LAST, 0 ));
        } else {
          return hwnd;
        }
      }
      break;
    }

  }

  return NULLHANDLE;
}

/* Dispatch system native events.
 *
 * This method is called when a system native window
 * event occurs.
 */

MRESULT PMSplitCanvas::dispatch( ULONG msg, MPARAM mp1, MPARAM mp2 )
{
  switch( msg ) {
    case WM_DESTROY:
      // Panes must be also detached here because presentation window can
      // be destroyed before object destruction. In other cases the WM_DESTROY
      // message can not be received here.
      send( PM_SETEXTENSION, 0, MPFROM2SHORT( PMA_SE_DETACH, 0 ));
      send( PM_SETEXTENSION, 0, MPFROM2SHORT( PMA_SE_DETACH, 1 ));
      break;

    case WM_SIZE:
      win_format();
      WinUpdateWindow( handle());
      return 0;

    case PM_FORMATFRAME:
      win_format();
      return 0;

    case PM_SETEXTENSION:
    {
      HWND  hwnd = HWNDFROMMP(mp1);
      SHORT i,id = SHORT2FROMMP(mp2);

      if( id < 0 && id > 1 ) {
        return MRFROMLONG( FALSE );
      }

      if( SHORT1FROMMP(mp2) == PMA_SE_ATTACH ) {
        for( i = 0; i <= 1; i++ ) {
          if( m_panes[i] && m_panes[i]->handle() == hwnd ) {
            delete m_panes[i];
            m_panes[i] = NULL;
          }
        }

        m_panes[id] = new PMWindow( hwnd );

        if( handle() != m_panes[id]->parent()) {
          m_panes[id]->parent( handle());
        }
      } else if( SHORT1FROMMP(mp2) == PMA_SE_DETACH )  {
        if( m_panes[id] ) {
          delete m_panes[id];
          m_panes[id] = NULL;
        }
      }

      win_format();
      return MRFROMLONG( TRUE );
    }

    case PM_GETEXTENSION:
    {
      SHORT id = SHORT1FROMMP(mp2);

      switch( id ) {
        case 0:
        case 1:
          if( m_panes[id] ) {
            return MRFROMLONG( m_panes[id]->handle());
          }
          break;

        case PMA_GE_FIRST:
        case PMA_GE_LAST:
        case PMA_GE_NEXT:
        case PMA_GE_PREV:
          return (MRESULT)win_penum( id, HWNDFROMMP( mp1 ));
      }

      return NULLHANDLE;
    }

    case WM_PAINT:
    {
      HPS    hps = WinBeginPaint( handle(), NULL, NULL );
      RECTL  rect;
      POINTL pos;
      int    i;

      GpiCreateLogColorTable( hps, 0, LCOLF_RGB, 0, 0, 0 );

      for( i = 0; i < 2; i++ ) {
        if( !m_panes[i] ) {
          rect.xLeft   = m_rects[i].x;
          rect.xRight  = m_rects[i].x + m_rects[i].cx;
          rect.yBottom = m_rects[i].y;
          rect.yTop    = m_rects[i].y + m_rects[i].cy;

          WinFillRect( hps, &rect, color( CCI_BACKGROUND ));
        }
      }

      if( m_style & SP_BORDER1 ) {
        draw_3d_border( hps, &m_rects[0], 2 );
      }
      if( m_style & SP_BORDER2 ) {
        draw_3d_border( hps, &m_rects[1], 2 );
      }

      rect.xLeft   = m_splitbar.x;
      rect.xRight  = m_splitbar.x + m_splitbar.cx;
      rect.yBottom = m_splitbar.y;
      rect.yTop    = m_splitbar.y + m_splitbar.cy;

      WinFillRect( hps, &rect, color( CCI_BUTTONBACKGROUND ));

      if(!( m_style & SP_2D )) {
        if( m_style & SP_HORIZONTAL ) {
          GpiSetColor( hps, color( CCI_BUTTONBORDERLIGHT ));
          pos.y = m_splitbar.y + m_splitbar.cy - 1;
          pos.x = m_splitbar.x;
          GpiMove( hps, &pos );
          pos.x = m_splitbar.x + m_splitbar.cx - 1;
          GpiLine( hps, &pos );
          GpiSetColor( hps, color( CCI_BUTTONBORDERDARK ));
          pos.y = m_splitbar.y;
          pos.x = m_splitbar.x;
          GpiMove( hps, &pos );
          pos.x = m_splitbar.x + m_splitbar.cx - 1;
          GpiLine( hps, &pos );
        } else {
          GpiSetColor( hps, color( CCI_BUTTONBORDERLIGHT ));
          pos.y = m_splitbar.y;
          pos.x = m_splitbar.x;
          GpiMove( hps, &pos );
          pos.y = m_splitbar.y + m_splitbar.cy - 1;
          GpiLine( hps, &pos );
          GpiSetColor( hps, color( CCI_BUTTONBORDERDARK ));
          pos.y = m_splitbar.y;
          pos.x = m_splitbar.x + m_splitbar.cx - 1;
          GpiMove( hps, &pos );
          pos.y = m_splitbar.y + m_splitbar.cy - 1;
          GpiLine( hps, &pos );
        }
      }
      WinEndPaint( hps );
      return 0;
    }

    case WM_MOUSEMOVE:
    {
      SHORT x = SHORT1FROMMP(mp1);
      SHORT y = SHORT2FROMMP(mp1);

      if( m_moved && ( m_drag_x != x || m_drag_y != y ))
      {
        PMRect rect = rectangle();

        if( m_style & SP_HORIZONTAL ) {
          if( rect.cy != m_bar_cy )
          {
            m_percentage = m_drag_percentage +
              ((float)( y - m_drag_start )/( rect.cy - m_bar_cy )) * 100;

            if( m_percentage > 100 ) {
              m_percentage = 100;
            } else if( m_percentage < 0 ) {
              m_percentage = 0;
            }
          }
        } else {
          if( rect.cx != m_bar_cx )
          {
            m_percentage = m_drag_percentage +
              ((float)( x - m_drag_start )/( rect.cx - m_bar_cx )) * 100;

            if( m_percentage > 100 ) {
              m_percentage = 100;
            } else if( m_percentage < 0 ) {
              m_percentage = 0;
            }
          }
        }
        win_format();
        WinUpdateWindow( handle());
        m_drag_x = x;
        m_drag_y = y;
      }

      if( m_moved || m_splitbar.contains( x, y )) {
        WinSetPointer( HWND_DESKTOP,
          WinQuerySysPointer( HWND_DESKTOP,
            m_style & SP_HORIZONTAL ? SPTR_SIZENS : SPTR_SIZEWE, FALSE ));

        return 0;
      }
      break;
    }

    case WM_BUTTON2DOWN:
      if( !WinIsChild( WinQueryFocus( HWND_DESKTOP ), handle())) {
        WinSetActiveWindow( HWND_DESKTOP, handle());
      }
      break;

    case WM_BUTTON1DOWN:
    {
      POINTS pos = *((POINTS*)&mp1);

      if( !WinIsChild( WinQueryFocus( HWND_DESKTOP ), handle())) {
        WinSetActiveWindow( HWND_DESKTOP, handle());
      }

      if( m_splitbar.contains( pos.x, pos.y ))
      {
        m_moved = TRUE;
        m_drag_percentage = m_percentage;
        m_drag_start = m_style & SP_HORIZONTAL ? pos.y : pos.x;
        m_drag_x = pos.x;
        m_drag_y = pos.y;

        capture_pointer();
      }
      break;
    }

    case WM_BUTTON1UP:
      if( m_moved )
      {
        m_moved = FALSE;
        release_pointer();
      }
      break;

    case PM_SETFOCUS:
      if( mp2 ) {
        HWND hwnd = win_penum( PMA_GE_FIRST );
        if( hwnd ) {
          WinSetFocus( HWND_DESKTOP, hwnd );
        }
      }
      return 0;

    case WM_QUERYDLGCODE:
      if(( m_panes[0] && m_panes[0]->is_valid() && ((LONG)m_panes[0]->send( msg, mp1, mp2 ) != DLGC_STATIC )) ||
         ( m_panes[1] && m_panes[1]->is_valid() && ((LONG)m_panes[1]->send( msg, mp1, mp2 ) != DLGC_STATIC )))
      {
        DEBUGLOG2(( "PMSplitCanvas [%08X] return DLGC_SPCANVAS as result of WM_QUERYDLGCODE\n", handle()));
        return (MRESULT)DLGC_SPCANVAS;
      } else {
        DEBUGLOG2(( "PMSplitCanvas [%08X] return DLGC_STATIC as result of WM_QUERYDLGCODE\n", handle()));
        return (MRESULT)DLGC_STATIC;
      }

    case WM_QUERYCTLTYPE:
      return MRFROMLONG( CCT_COMBOBOX );

    case WM_CHAR:
      if(!( SHORT1FROMMP(mp1) & KC_KEYUP )) {
        if( SHORT2FROMMP(mp2) == VK_TAB )
        {
          HWND hwnd = win_penum( PMA_GE_NEXT, WinQueryFocus( HWND_DESKTOP ));
          if( hwnd ) {
            WinSetFocus( HWND_DESKTOP, hwnd );
            return MRFROMLONG( TRUE );
          }
        }
        else if( SHORT2FROMMP(mp2) == VK_BACKTAB )
        {
          HWND hwnd = win_penum( PMA_GE_PREV, WinQueryFocus( HWND_DESKTOP ));
          if( hwnd ) {
            WinSetFocus( HWND_DESKTOP, hwnd );
            return MRFROMLONG( TRUE );
          }
        }
      }
      return WinSendMsg( owner(), msg, mp1, mp2 );

    case WM_FOCUSCHANGE:
      if( m_style & SP_TITLEBAR ) {
        m_titlebar.hilite( SHORT1FROMMP( mp2 ));
      }
      break;
  }

  return PMWindow::dispatch( msg, mp1, mp2 );
}

/* Draws the 3D border.
 */

void PMSplitCanvas::draw_3d_border( HPS ps, PMRect* rect, LONG thickness )
{
  POINTL pos;
  GpiSetLineWidth( ps, LINEWIDTH_NORMAL );

  pos.y = rect->y;
  pos.x = rect->x;
  GpiMove( ps, &pos );

  GpiSetColor( ps, color( CCI_BORDERLIGHT ));
  pos.x = rect->x + rect->cx - 1;
  GpiLine( ps, &pos );
  pos.y = rect->y + rect->cy - 1;
  GpiLine( ps, &pos );

  GpiSetColor( ps, color( CCI_BORDERDARK ));
  pos.x = rect->x;
  GpiLine( ps, &pos );
  pos.y = rect->y;
  GpiLine( ps, &pos );

  if( thickness > 1 )
  {
    pos.y = rect->y + 1;
    pos.x = rect->x + 1;
    GpiMove( ps, &pos );

    GpiSetColor( ps, color( CCI_BORDER2LIGHT ));
    pos.x = rect->x + rect->cx - 2;
    GpiLine( ps, &pos );
    pos.y = rect->y + rect->cy - 2;
    GpiLine( ps, &pos );

    GpiSetColor( ps, color( CCI_BORDER2DARK ));
    pos.x = rect->x + 1;
    GpiLine( ps, &pos );
    pos.y = rect->y + 1;
    GpiLine( ps, &pos );
  }
}

