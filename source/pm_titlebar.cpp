/*
 * Copyright (C) 2009 Dmitry A.Steklenev
 *
 * $Id: pm_titlebar.cpp,v 1.3 2011/03/11 12:59:33 glass Exp $
 */

#include "pm_titlebar.h"

/* Wraps the title bar window object
 * around an existing presentation window handle.
 */

PMTitleBar::PMTitleBar( HWND handle )
: PMWindow( handle )
{}

/* Wraps the title bar window object around
 * an existing child window with the specified identity.
 */

PMTitleBar::PMTitleBar( HWND hparent, SHORT id )
: PMWindow( hparent, id )
{}

/* Constructs the title bar control window.
 */

PMTitleBar::PMTitleBar( SHORT id, const char* text, HWND hparent,
                        LONG x, LONG y, LONG cx, LONG cy, ULONG style )

: PMWindow( WC_TITLEBAR, id, text, hparent, hparent,
            x, y, cx, cy, style, NULL )
{}

/* Highlights or unhighlights a title-bar control.
 */

void PMTitleBar::hilite( BOOL highlight ) {
  send( TBM_SETHILITE, MPFROMSHORT( highlight ), 0 );
}

/* Returns the highlighting state of a title-bar control.
 */

BOOL PMTitleBar::is_hilited() const {
  return LONGFROMMR( WinSendMsg( handle(), TBM_QUERYHILITE, 0, 0 ));
}

/* Dispatch system native events.
 *
 * This method is called when a system native window
 * event occurs.
 */

MRESULT PMTitleBar::dispatch( ULONG msg, MPARAM mp1, MPARAM mp2 )
{
  switch( msg ) {
    case WM_BUTTON2DOWN:
    case WM_BUTTON1DOWN:
      if( !WinIsChild( WinQueryFocus( HWND_DESKTOP ), parent())) {
        PMWindow( parent()).set_focus();
      }
      break;
  }

  return PMWindow::dispatch( msg, mp1, mp2 );
}

