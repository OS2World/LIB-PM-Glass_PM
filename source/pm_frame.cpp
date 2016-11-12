/*
 * Copyright (C) 2001-2011 Dmitry A.Steklenev
 *
 * $Id: pm_frame.cpp,v 1.18 2011/12/19 06:36:48 glass Exp $
 */

#include "pm_frame.h"
#include "pm_gui.h"

#ifndef WS_TOPMOST
#define WS_TOPMOST  0x00200000
#endif

/* Wraps the frame window object around an existing
 * presentation window handle.
 */

PMFrame::PMFrame( HWND handle )

: PMWindow    ( handle     ),
  m_client    ( WinWindowFromID( handle, FID_CLIENT )),
  m_menu      ( WinWindowFromID( handle, FID_MENU   )),
  m_extensions( NULL       ),
  m_icon      ( NULLHANDLE ),
  m_acceltable( NULLHANDLE )
{}

/* Constructs the frame window.
 */

PMFrame::PMFrame( SHORT id, const char* text, HWND howner,
                  LONG x, LONG y, LONG cx, LONG cy, ULONG frame_style, ULONG style )

: PMWindow( WC_FRAME, id, text, HWND_DESKTOP, howner,
            x, y, cx, cy, style, ( m_fcdata.cb = sizeof( m_fcdata ),
                                   m_fcdata.flCreateFlags = frame_style,
                                   m_fcdata.hmodResources = (USHORT)PMGUI::module_handle(),
                                   m_fcdata.idResources   = id,
                                  &m_fcdata )),
  m_client    ( NULLHANDLE ),
  m_menu      ( NULLHANDLE ),
  m_extensions( NULL       ),
  m_icon      ( NULLHANDLE ),
  m_acceltable( NULLHANDLE )
{
  // Change window background.
  WinSetWindowUShort( handle(), QWS_FLAGS, (USHORT)( WinQueryWindowUShort( handle(), QWS_FLAGS ) | FF_DIALOGBOX ));
  invalidate();

  // Needed for correct repainting of a frame controls.
  WinSendMsg( handle(), WM_UPDATEFRAME, MPFROMLONG( m_fcdata.flCreateFlags ), 0 );
}

/* Constructs the frame window from the dialog template.
 */

PMFrame::PMFrame( HWND howner, SHORT res_id, HMODULE hmodule )

: PMWindow    ( HWND_DESKTOP, howner, res_id, hmodule  ),
  m_client    ( WinWindowFromID( handle(), FID_CLIENT )),
  m_menu      ( NULLHANDLE ),
  m_extensions( NULL       ),
  m_acceltable( NULLHANDLE )
{
  m_icon = WinLoadPointer( HWND_DESKTOP, hmodule, res_id );

  if( m_icon != NULLHANDLE  ) {
    send( WM_SETICON, MPFROMLONG( m_icon ), 0 );
  }
}

/* Destructs the frame window object.
 *
 * Cleans up as this window object and destroying the
 * associated presentation window for this object if the object
 * was not wrapped around an existing window handle.
 */

PMFrame::~PMFrame()
{
  if( is_valid()) {
    if( m_icon ) {
      send( WM_SETICON, MPFROMLONG( NULLHANDLE ), 0 );
    }
    if( m_extensions ) {
      send( PM_SETEXTENSION, 0, MPFROM2SHORT( PMA_SE_DETACH_ALL, 0 ));
    }
    if( m_acceltable ) {
      send( PM_SETACCELTABLE, MPFROMLONG( NULLHANDLE ), 0 );
    }
  }

  if( m_icon ) {
    WinDestroyPointer( m_icon );
  }
  if( m_acceltable ) {
    WinDestroyAccelTable( m_acceltable );
  }
}

/* Sets the window used as the frame
 * window's client area.
 */

void PMFrame::client( HWND client )
{
  m_client = client;
  send( PM_FORMATFRAME, 0, 0 );

  if( has_focus()) {
    WinSetFocus( HWND_DESKTOP, m_client );
  }
}

/* Returns the handle of the window used as the
 * frame window's client area.
 */

HWND PMFrame::client() {
  return m_client;
}

/* Sets the menu used as the frame
 * window's menu bar.
 */

void PMFrame::menu( HWND hmenu )
{
  if( !WinSetWindowUShort( hmenu, QWS_ID, FID_MENU )) {
    PM_THROW_GUIERROR();
  }

  WinSendMsg( handle(), WM_UPDATEFRAME, MPFROMLONG( FCF_MENU ), 0 );
  m_menu = hmenu;
}

/* Returns the handle of the menu used as the
 * frame window's menu bar.
 */

HWND PMFrame::menu() {
  return m_menu;
}

/* Calculates a client rectangle.
 *
 * This method calculates a client rectangle from a
 * frame rectangle.
 */

PMRect PMFrame::client_rectangle() const
{
   PMRect rect = rectangle();
   RECTL  rect_client = { 0, 0, rect.cx - 1, rect.cy - 1 };

   WinCalcFrameRect( handle(), &rect_client, TRUE );
   return PMRect( rect_client, PMRect::inclusive );
}

/* Makes the frame window visible.
 *
 * The frame window is made the topmost window also.
 */

void PMFrame::show( BOOL state )
{
  PMWindow::show( state );

  if( state ) {
    if( !WinSetActiveWindow( HWND_DESKTOP, handle())) {
      PM_THROW_GUIERROR();
    }
  }
}

/* Displays the frame window modally.
 *
 * While the frame window is being shown modally, its parent or owner or
 * both windows are disabled. Other top level windows belonging to the
 * application are not disabled.
 */

ULONG PMFrame::show_modally()
{
  // Insure WinProcessDlg does not return immediately.
  WinSetWindowUShort( handle(), QWS_FLAGS, (USHORT)( WinQueryWindowUShort( handle(), QWS_FLAGS ) & ~FF_DLGDISMISSED ));
  WinSetActiveWindow( HWND_DESKTOP, handle());
  return WinProcessDlg( handle());
}

/* Dismiss the frame window.
 *
 * This method hides the modeless frame window, and causes
 * show_modally to return.
 */

void PMFrame::dismiss( ULONG rc )
{
  if( !WinDismissDlg( handle(), rc )) {
    PM_THROW_GUIERROR();
  }
}

/* Attaches a window to frame as a frame extension.
 */

void PMFrame::attach_extension( HWND hwnd, location_type location ) {
  send( PM_SETEXTENSION, MPFROMHWND( hwnd ), MPFROM2SHORT( PMA_SE_ATTACH, location ));
}

/* Detaches a frame extension from frame.
 */

void PMFrame::detach_extension( HWND hwnd ) {
  send( PM_SETEXTENSION, MPFROMHWND( hwnd ), MPFROM2SHORT( PMA_SE_DETACH, 0 ));
}

/* Attaches a window to frame as a frame extension.
 * Must be called only from a window thread.
 */

void PMFrame::win_attach_extension( HWND hwnd, location_type location )
{
  WNDEXTS* ext;
  WNDEXTS* ext_new;

  if( hwnd ) {
    for( ext = m_extensions; ext; ext = ext->next ) {
      if( ext->hwnd == hwnd ) {
        return;
      }
      if( ext->next == NULL ) {
        break;
      }
    }

    ext_new           = new WNDEXTS();
    ext_new->hwnd     = hwnd;
    ext_new->location = location;
    ext_new->next     = NULL;

    if( ext ) {
      ext->next    = ext_new;
    } else {
      m_extensions = ext_new;
    }
    win_format();
  }
}

/* Detaches a frame extension from frame. Must be called
 * only from a window thread.
 */

void PMFrame::win_detach_extension( HWND hwnd )
{
  WNDEXTS* ext;
  WNDEXTS* ext_prev = NULL;

  for( ext = m_extensions; ext; ext = ext->next ) {
    if( ext->hwnd == hwnd ) {
      break;
    } else {
      ext_prev = ext;
    }
  }

  if( ext ) {
    if( ext_prev ) {
      ext_prev->next = ext->next;
    } else {
      m_extensions   = ext->next;
    }
    delete ext;
  }
  win_format();
}

/* Detaches all frame extensions from frame. Must be called
 * only from a window thread.
 */

void PMFrame::win_detach_all_extensions()
{
  WNDEXTS* ext = m_extensions;
  WNDEXTS* ext_next;

  while( ext ) {
    ext_next = ext->next;
    delete ext;
    ext = ext_next;
  }

  m_extensions = NULL;
  win_format();
}

/* Formats a frame window.
 * Must be called only from a window thread.
 */

void PMFrame::win_format()
{
  PMRect   cli_rect = client_rectangle();
  WNDEXTS* ext;

  for( ext = m_extensions; ext; ext = ext->next )
  {
    PMWindow ext_wind( ext->hwnd );
    PMRect   ext_rect = ext_wind.rectangle();

    switch( ext->location ) {
      case left:
        ext_rect.x   = cli_rect.x;
        ext_rect.y   = cli_rect.y;
        ext_rect.cy  = cli_rect.cy;
        cli_rect.x  += ext_rect.cx;
        cli_rect.cx -= ext_rect.cx;
        break;

      case right:
        ext_rect.x   = cli_rect.x + cli_rect.cx - ext_rect.cx;
        ext_rect.y   = cli_rect.y;
        ext_rect.cy  = cli_rect.cy;
        cli_rect.cx -= ext_rect.cx;
        break;

      case below:
        ext_rect.x   = cli_rect.x;
        ext_rect.y   = cli_rect.y;
        ext_rect.cx  = cli_rect.cx;
        cli_rect.y  += ext_rect.cy;
        cli_rect.cy -= ext_rect.cy;
        break;

      case above:
        ext_rect.x   = cli_rect.x;
        ext_rect.y   = cli_rect.y + cli_rect.cy - ext_rect.cy;
        ext_rect.cx  = cli_rect.cx;
        cli_rect.cy -= ext_rect.cy;
        break;
    }

    ext_wind.rectangle( ext_rect );
  }

  if( m_client != NULLHANDLE && WinIsWindow( PMGUI::hab(), m_client )) {
    PMWindow( m_client ).rectangle( cli_rect );
  }

  WinUpdateWindow( handle());
}

/* Replaces the accelerator keys used by the window.
 */

void PMFrame::attach_accelerators( SHORT res_id, HMODULE hmodule )
{
  HACCEL hnew = WinLoadAccelTable ( PMGUI::hab(), hmodule, res_id );

  if( hnew == NULLHANDLE ) {
    PM_THROW_GUIERROR();
  }
  if( !send( PM_SETACCELTABLE, MPFROMLONG( hnew ), 0 )) {
    PM_THROW_GUIERROR();
  }
}

/* Detaches the accelerator keys used by the window.
 */

void PMFrame::detach_accelerators()
{
  if( !send( PM_SETACCELTABLE, MPFROMLONG( NULLHANDLE ), 0 )) {
    PM_THROW_GUIERROR();
  }
}

/* Sets the window as topmost window.
 */

void PMFrame::set_as_topmost( BOOL topmost )
{
  ULONG style = WinQueryWindowULong( handle(), QWL_STYLE );

  if( topmost ) {
    style |=  WS_TOPMOST;
  } else {
    style &= ~WS_TOPMOST;
  }

  WinSetWindowULong( handle(), QWL_STYLE, style );
}

/* Returns TRUE if the window is a topmost window.
 */

BOOL PMFrame::is_topmost() const {
  return ( WinQueryWindowULong( handle(), QWL_STYLE ) & WS_TOPMOST );
}

/*
 * Dispatch system native events.
 *
 * PMFrame calls this function when a system native window
 * event occurs.
 */

MRESULT PMFrame::dispatch( ULONG msg, MPARAM mp1, MPARAM mp2 )
{
  switch( msg ) {
    case WM_DESTROY:
      // Extensions must be also detached here because presentation window can
      // be destroyed before object destruction. In other cases the WM_DESTROY
      // message can not be received here.
      win_detach_all_extensions();
      break;

    case WM_ERASEBACKGROUND:
      if( m_client != NULLHANDLE ) {
        return 0;
      }
      break;

    case PM_FORMATFRAME:
      if( m_client != NULLHANDLE || m_extensions != NULL ) {
        win_format();
      }
      return 0;

    case PM_SETEXTENSION:
    {
      HWND          hwnd     = HWNDFROMMP(mp1);
      location_type location = location_type( SHORT2FROMMP(mp2));
      SHORT         action   = SHORT1FROMMP(mp2);

      switch( action ) {
        case PMA_SE_ATTACH:
          win_attach_extension( hwnd, location );
          break;

        case PMA_SE_DETACH:
          win_detach_extension( hwnd );
          break;

        case PMA_SE_DETACH_ALL:
          win_detach_all_extensions();
          break;
      }

      return 0;
    }

    case PM_SETACCELTABLE:
    {
      HACCEL hnew = LONGFROMMP(mp1);
      HACCEL hold = WinQueryAccelTable( PMGUI::hab(), handle());

      if( WinSetAccelTable( PMGUI::hab(), hnew, handle())) {
        if( m_acceltable == hold ) {
          WinDestroyAccelTable( hold );
        }

        m_acceltable = hnew;
        return MRFROMLONG( TRUE );
      }

      return FALSE;
    }

    case WM_FORMATFRAME:
      // OS/2 requires formatting the frame window after
      // processing WM_FORMATFRAME.
      post( PM_FORMATFRAME, 0, 0 );
      break;

    case PM_SETFOCUS:
    {
      if( m_client != NULLHANDLE ) {
        WinSetFocus( HWND_DESKTOP, m_client );
        return 0;
      }
      break;
    }
  }

  return PMWindow::dispatch( msg, mp1, mp2 );
}

