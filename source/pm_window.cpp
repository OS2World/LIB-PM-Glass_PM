/*
 * Copyright (C) 2001-2011 Dmitry A.Steklenev
 *
 * $Id: pm_window.cpp,v 1.35 2011/05/03 11:48:36 glass Exp $
 */

#include "pm_window.h"
#include "pm_gui.h"
#include "pm_language.h"
#include "pm_windowset.h"

#include <string.h>

#ifndef PMERR_CANNOT_SET_FOCUS
#define PMERR_CANNOT_SET_FOCUS 0x1037
#endif

#if defined(__WATCOMC__)

  typedef struct _CTLCOLOR
  {
    LONG clrIndex;
    LONG clrValue;

  } CTLCOLOR;

  typedef CTLCOLOR* PCTLCOLOR;

  extern "C" {
  LONG APIENTRY WinQueryControlColors( HWND hwnd, LONG clrType, ULONG flCtlColor,
                                       ULONG cCtlColor, PCTLCOLOR pCtlColor );
  }
#endif

/* Wraps the window object around an existing
 * presentation window handle.
 */

PMWindow::PMWindow( HWND handle )

: m_handle         ( handle     ),
  m_wrapped        ( TRUE       ),
  m_default_handler( NULL       ),
  m_pointer        ( NULLHANDLE ),
  m_pointer_id     ( 0          ),
  m_acceltable     ( NULLHANDLE ),
  m_auto_delete    ( FALSE      ),
  m_drop_types     ( drop_none  )
{
  if( handle ) {
    m_id = WinQueryWindowUShort( handle, QWS_ID );
  }
}

/* Wraps the window object around an existing
 * child window with the specified identity.
 */

PMWindow::PMWindow( HWND hparent, SHORT id )

: m_id             ( id         ),
  m_wrapped        ( TRUE       ),
  m_default_handler( NULL       ),
  m_pointer        ( NULLHANDLE ),
  m_pointer_id     ( 0          ),
  m_acceltable     ( NULLHANDLE ),
  m_auto_delete    ( FALSE      ),
  m_drop_types     ( drop_none  )
{
  m_handle = WinWindowFromID( hparent, id );

  if( m_handle == NULLHANDLE ) {
    PM_THROW_GUIERROR();
  }
}

/* Constructs the presentation window.
 */

PMWindow::PMWindow( SHORT id, const char* text, HWND hparent, HWND howner,
                    LONG x, LONG y, LONG cx, LONG cy, ULONG style )

: m_id             ( id         ),
  m_wrapped        ( FALSE      ),
  m_default_handler( NULL       ),
  m_pointer        ( NULLHANDLE ),
  m_pointer_id     ( 0          ),
  m_acceltable     ( NULLHANDLE ),
  m_auto_delete    ( FALSE      ),
  m_drop_types     ( drop_none  )
{
  static BOOL  initialized = FALSE;

  if( !initialized ) {
    if( !WinRegisterClass( PMGUI::hab(), "PMWindow", def_proc,
                                          CS_HITTEST | CS_SIZEREDRAW, 4 )) {
      PM_THROW_GUIERROR();
    }

    initialized = TRUE;
  }

  if( style & WS_DLGPOINTS )
  {
    POINTL p[2] = {{ x, y }, { x + cx, y + cy }};

    WinMapDlgPoints( hparent, p, 2, TRUE );
    x  = p[0].x;
    y  = p[0].y;
    cx = p[1].x - x;
    cy = p[1].y - y;

    style &= ~WS_DLGPOINTS;
  }

  m_handle = WinCreateWindow( hparent, "PMWindow", text, style,
                              x, y, cx, cy, howner, HWND_BOTTOM, id, NULL, 0 );

  if( m_handle == NULLHANDLE ) {
    PM_THROW_GUIERROR();
  }

  handle_events();
}

/* Constructs the presentation window from the dialog template.
 */

PMWindow::PMWindow( HWND hparent, HWND howner, SHORT res_id, HMODULE hmodule )

: m_id             ( res_id     ),
  m_wrapped        ( FALSE      ),
  m_default_handler( NULL       ),
  m_pointer        ( NULLHANDLE ),
  m_pointer_id     ( 0          ),
  m_acceltable     ( NULLHANDLE ),
  m_auto_delete    ( FALSE      ),
  m_drop_types     ( drop_none  )
{
  m_handle = WinLoadDlg( hparent, howner, WinDefDlgProc, hmodule, res_id, 0 );

  if( m_handle == NULLHANDLE ) {
    PM_THROW_GUIERROR();
  }

  handle_events();
}

/* Constructs the presentation window of the specified class.
 */

PMWindow::PMWindow( const char* classname, SHORT id, const char* text, HWND hparent, HWND howner,
                    LONG x, LONG y, LONG cx, LONG cy, ULONG style, PVOID classdata )

: m_id             ( id         ),
  m_wrapped        ( FALSE      ),
  m_default_handler( NULL       ),
  m_pointer        ( NULLHANDLE ),
  m_pointer_id     ( 0          ),
  m_acceltable     ( NULLHANDLE ),
  m_auto_delete    ( FALSE      ),
  m_drop_types     ( drop_none  )
{
  if( style & WS_DLGPOINTS )
  {
    POINTL p[2] = {{ x, y }, { x + cx, y + cy }};

    WinMapDlgPoints( hparent, p, 2, TRUE );
    x  = p[0].x;
    y  = p[0].y;
    cx = p[1].x - x;
    cy = p[1].y - y;

    style &= ~WS_DLGPOINTS;
  }

  m_handle = WinCreateWindow( hparent, classname, text, style,
                              x, y, cx, cy, howner, HWND_BOTTOM, id, classdata, 0 );

  if( m_handle == NULLHANDLE ) {
    PM_THROW_GUIERROR();
  }

  handle_events();
}

/* Destructs the window object.
 *
 * Cleans up as this window object and destroying the
 * associated presentation window for this object if the object
 * was not created from an existing window handle.
 */

PMWindow::~PMWindow()
{
  if( is_valid()) {
    if( m_acceltable ) {
      send( PM_SETACCELTABLE, MPFROMLONG( NULLHANDLE ), 0 );
    }
  }
  if( !m_wrapped ) {
    destroy();
  }
  if( m_acceltable ) {
    WinDestroyAccelTable( m_acceltable );
  }
}

/* Destroys the presentation window.
 */

void PMWindow::destroy()
{
  if( WinIsWindow( PMGUI::hab(), m_handle )) {
    if( !WinDestroyWindow( m_handle )) {
      PM_THROW_GUIERROR();
    }
  }
}

/* Returns the parent window handle.
 */

HWND PMWindow::parent() const {
  return WinQueryWindow( m_handle, QW_PARENT );
}

/* Returns the owner window handle.
 */

HWND PMWindow::owner() const {
  return WinQueryWindow( m_handle, QW_OWNER );
}

/* Sets the parent window.
 */

void PMWindow::parent( HWND hparent, BOOL redraw )
{
  if( !WinSetParent( m_handle, hparent, redraw )) {
    PM_THROW_GUIERROR();
  }
}

/* Sets the owner window.
 */

void PMWindow::owner( HWND howner )
{
  if( !WinSetOwner( m_handle, howner )) {
    PM_THROW_GUIERROR();
  }
}

/* Return the handle of the first frame window associated
 * with this window.
 */

HWND PMWindow::frame() const
{
  char classname[64];

  WinQueryClassName( m_handle, sizeof( classname ), classname );

  if( strcmp( classname, "#1" ) == 0 ) { // WC_FRAME
    return m_handle;
  } else {
    return (HWND)WinSendMsg( m_handle, WM_QUERYFOCUSCHAIN, MPFROMSHORT( QFC_FRAME ), 0 );
  }
}

/* Sets the window text. */
void PMWindow::text( const char* text ) {
  WinSetWindowText( m_handle, text );
}

/* Returns the window text.
 */

char* PMWindow::text( char* result, int size ) const
{
  WinQueryWindowText( m_handle, size, result );
  return result;
}

/* Returns the length of the window text.
 */

int PMWindow::text_len() const {
  return WinQueryWindowTextLength( m_handle );
}

/* Translates the window text and all the child text using
 * for this purpose the current instance of the messages
 * management object.
 */

void PMWindow::translate()
{
  HENUM  henum;
  HWND   hnext;
  char   current[1024] = "";
  char   message[1024];

  if( PMLanguage::instance ) {
    if( *text( current, sizeof( current ))) {
      PMLanguage::instance->message( message, sizeof( message ), current );
      text( message );
    }

    henum = WinBeginEnumWindows( handle());

    while(( hnext = WinGetNextWindow( henum )) != NULLHANDLE ) {
      PMWindow( hnext ).translate();
    }

    WinEndEnumWindows( henum );
  }
}

/* Sets the window shape. */
void PMWindow::rectangle( const PMRect& rect )
{
  if( !WinSetWindowPos( m_handle, 0, rect.x, rect.y, rect.cx, rect.cy, SWP_SIZE | SWP_MOVE )) {
    PM_THROW_GUIERROR();
  }
}

/* Centers the window concerning his owner window.
 */

void PMWindow::center_at()
{
  HWND   hparent     = parent();
  HWND   howner      = owner ();
  PMRect rect        = rectangle();
  PMRect rect_screen = PMWindow( HWND_DESKTOP ).rectangle();

  if( howner != NULLHANDLE )
  {
    PMWindow wind_owner( howner );
    PMRect   rect_owner = wind_owner.rectangle();

    rect_owner.map( wind_owner.parent(), hparent );
    rect.x = ( rect_owner.cx - rect.cx ) / 2 + rect_owner.x;
    rect.y = ( rect_owner.cy - rect.cy ) / 2 + rect_owner.y;
  }
  else
  {
    PMRect   rect_parent = PMWindow( hparent ).rectangle();

    rect.x = ( rect_parent.cx - rect.cx ) / 2;
    rect.y = ( rect_parent.cy - rect.cy ) / 2;
  }

  // Constrain the window so that its height and its width is wholly
  // visible on the desktop.

  rect.map( hparent, HWND_DESKTOP );

  if( rect.x < 0 ) {
    rect.x = 0;
  }
  if( rect.y < 0 ) {
    rect.y = 0;
  }
  if( rect.x + rect.cx > rect_screen.cx ) {
    rect.x = rect_screen.cx - rect.cx;
  }
  if( rect.y + rect.cy > rect_screen.cy ) {
    rect.y = rect_screen.cy - rect.cy;
  }

  rect.map( HWND_DESKTOP, hparent );

  // Without SWP_NOADJUST flag the WinSetWindowPos produces some strange effects
  // at using ePager.

  if( !WinSetWindowPos( m_handle, 0, rect.x, rect.y, 0, 0, SWP_MOVE | SWP_NOADJUST )) {
    PM_THROW_GUIERROR();
  }
}

/* Sets a new font to be used by the window.
 */

void PMWindow::font( const char* font )
{
  static int   have_warpsans = -1;
  const  char* used_font = font;

  if( strnicmp( font, "9.WarpSans", 10 ) == 0 ) {
    if( have_warpsans == -1 )
    {
      LONG rc;
      LONG fonts = 0;
      HPS  hps;

      hps = WinGetPS( HWND_DESKTOP );
      rc  = GpiQueryFonts( hps, QF_PUBLIC, "WarpSans", &fonts, 0, NULL );
      WinReleasePS( hps );

      have_warpsans = ( rc > 0 && rc != GPI_ALTERROR );
    }

    if( !have_warpsans ) {
      if( stricmp( font, "9.WarpSans" ) == 0 ) {
        used_font = "8.Helv";
      } else if( stricmp( font, "9.WarpSans Bold" ) == 0 ) {
        used_font = "10.System Proportional";
      }
    }
  }

  if( !WinSetPresParam( m_handle, PP_FONTNAMESIZE, strlen( used_font ) + 1, (PVOID)used_font )) {
    PM_THROW_GUIERROR();
  }
}

static LONG os2_cct( HWND hwnd )
{
  LONG ctltype = LONGFROMMR( WinSendMsg( hwnd, WM_QUERYCTLTYPE, 0, 0 ));
  char classname[64];

  if( !ctltype ) {
    // The container control doesn't return a correct control type
    // and here I try to deduce it from name of the window class.
    WinQueryClassName( hwnd, sizeof( classname ), classname );
    if( strcmp( classname, "#37" ) == 0 ) { // WC_CONTAINER
      return CCT_CONTAINER;
    }
  }

  return ctltype;
}

static ULONG os2_pp_to_cci( LONG ctltype, LONG cci_id )
{
  switch( ctltype ) {
    case CCT_MENU:
      switch( cci_id ) {
        case CCI_FOREGROUND:              return PP_MENUFOREGROUNDCOLOR;
        case CCI_BACKGROUND:              return PP_MENUBACKGROUNDCOLOR;
        case CCI_DISABLEDFOREGROUND:      return PP_MENUDISABLEDFGNDCOLOR;
        case CCI_DISABLEDBACKGROUND:      return PP_MENUDISABLEDBGNDCOLOR;
        case CCI_HIGHLIGHTFOREGROUND:     return PP_MENUHILITEFGNDCOLOR;
        case CCI_HIGHLIGHTBACKGROUND:     return PP_MENUHILITEBGNDCOLOR;
      }
      break;

    case CCT_VALUESET:
      switch( cci_id ) {
        case CCI_BORDERDEFAULT:           return PP_HILITEBACKGROUNDCOLOR;
      }
      break;

    case CCT_SLIDER:
      switch( cci_id ) {
        case CCI_BACKGROUND:              return PP_HILITEBACKGROUNDCOLOR;
      }
      break;

    case CCT_TITLEBAR:
      switch( cci_id ) {
        case CCI_INACTIVEFOREGROUND:      return PP_INACTIVETEXTFGNDCOLOR;
        case CCI_ACTIVEFOREGROUND:        return PP_ACTIVETEXTFGNDCOLOR;
      }
      break;

    case CCT_NOTEBOOK:
      switch( cci_id ) {
        case CCI_FIELDBACKGROUND:         return PP_PAGEBACKGROUNDCOLOR;
        case CCI_BORDERDEFAULT:           return PP_HILITEBACKGROUNDCOLOR;
      }
      break;

    case CCT_FRAME:
      switch( cci_id ) {
        case CCI_ICONFOREGROUND:          return PP_INACTIVETEXTFGNDCOLOR;
        case CCI_ICONBACKGROUND:          return PP_INACTIVETEXTBGNDCOLOR;
        case CCI_ICONBACKGROUNDDESKTOP:   return PP_INACTIVETEXTBGNDCOLOR;
      }
      break;
  }

  switch( cci_id ) {
    case CCI_FOREGROUND:                  return PP_FOREGROUNDCOLOR;
    case CCI_FOREGROUNDREADONLY:          return PP_FOREGROUNDCOLOR;
    case CCI_BACKGROUND:                  return PP_BACKGROUNDCOLOR;
    case CCI_BACKGROUNDDIALOG:            return PP_BACKGROUNDCOLOR;
    case CCI_DISABLEDFOREGROUND:          return PP_DISABLEDFOREGROUNDCOLOR;
    case CCI_DISABLEDFOREGROUNDREADONLY:  return PP_DISABLEDFOREGROUNDCOLOR;
    case CCI_DISABLEDBACKGROUND:          return PP_DISABLEDBACKGROUNDCOLOR;
    case CCI_DISABLEDBACKGROUNDDIALOG:    return PP_DISABLEDBACKGROUNDCOLOR;
    case CCI_HIGHLIGHTFOREGROUND:         return PP_HILITEFOREGROUNDCOLOR;
    case CCI_HIGHLIGHTBACKGROUND:         return PP_HILITEBACKGROUNDCOLOR;
    case CCI_HIGHLIGHTBACKGROUNDDIALOG:   return PP_HILITEBACKGROUNDCOLOR;
    case CCI_INACTIVEFOREGROUND:          return PP_INACTIVECOLOR;
    case CCI_INACTIVEFOREGROUNDDIALOG:    return PP_INACTIVECOLOR;
    case CCI_INACTIVEBACKGROUND:          return PP_INACTIVECOLOR;
    case CCI_INACTIVEBACKGROUNDTEXT:      return PP_INACTIVETEXTBGNDCOLOR;
    case CCI_ACTIVEFOREGROUND:            return PP_ACTIVECOLOR;
    case CCI_ACTIVEFOREGROUNDDIALOG:      return PP_ACTIVECOLOR;
    case CCI_ACTIVEBACKGROUND:            return PP_ACTIVECOLOR;
    case CCI_ACTIVEBACKGROUNDTEXT:        return PP_ACTIVETEXTBGNDCOLOR;
    case CCI_PAGEBACKGROUND:              return PP_PAGEBACKGROUNDCOLOR;
    case CCI_PAGEFOREGROUND:              return PP_PAGEFOREGROUNDCOLOR;
    case CCI_FIELDBACKGROUND:             return PP_FIELDBACKGROUNDCOLOR;
    case CCI_BORDER:                      return PP_BORDERCOLOR;
    case CCI_BORDERLIGHT:                 return PP_BORDERLIGHTCOLOR;
    case CCI_BORDERDARK:                  return PP_BORDERDARKCOLOR;
    case CCI_BORDER2:                     return PP_BORDER2COLOR;
    case CCI_BORDER2LIGHT:                return PP_BORDER2LIGHTCOLOR;
    case CCI_BORDER2DARK:                 return PP_BORDER2DARKCOLOR;
    case CCI_BORDERDEFAULT:               return PP_BORDERDEFAULTCOLOR;
    case CCI_BUTTONBACKGROUND:            return PP_BUTTONBACKGROUNDCOLOR;
    case CCI_BUTTONBORDERLIGHT:           return PP_BUTTONBORDERLIGHTCOLOR;
    case CCI_BUTTONBORDERDARK:            return PP_BUTTONBORDERDARKCOLOR;
    case CCI_ARROW:                       return PP_ARROWCOLOR;
    case CCI_DISABLEDARROW:               return PP_ARROWDISABLEDCOLOR;
    case CCI_ARROWBORDERLIGHT:            return PP_ARROWBORDERLIGHTCOLOR;
    case CCI_ARROWBORDERDARK:             return PP_ARROWBORDERDARKCOLOR;
    case CCI_CHECKLIGHT:                  return PP_CHECKLIGHTCOLOR;
    case CCI_CHECKMIDDLE:                 return PP_CHECKMIDDLECOLOR;
    case CCI_CHECKDARK:                   return PP_CHECKDARKCOLOR;
    case CCI_ICONFOREGROUND:              return PP_FOREGROUNDCOLOR;
    case CCI_ICONBACKGROUND:              return PP_ICONTEXTBACKGROUNDCOLOR;
    case CCI_ICONHILITEFOREGROUND:        return PP_HILITEFOREGROUNDCOLOR;
    case CCI_ICONHILITEBACKGROUND:        return PP_HILITEBACKGROUNDCOLOR;
    case CCI_MAJORTABFOREGROUND:          return PP_MAJORTABFOREGROUNDCOLOR;
    case CCI_MAJORTABBACKGROUND:          return PP_MAJORTABBACKGROUNDCOLOR;
    case CCI_MINORTABFOREGROUND:          return PP_MINORTABFOREGROUNDCOLOR;
    case CCI_MINORTABBACKGROUND:          return PP_MINORTABBACKGROUNDCOLOR;
  }

  return 0;
}

/* Returns the specified color value
 */

LONG PMWindow::color( LONG type ) const
{
  CTLCOLOR color   = { 0 };
  LONG     ctltype = os2_cct( m_handle );
  ULONG    pp_id   = os2_pp_to_cci( ctltype, type );

  if( !pp_id || !WinQueryPresParam( m_handle, pp_id, pp_id, NULL, sizeof( ULONG ),
                                    &color.clrValue, QPF_NOINHERIT | QPF_PURERGBCOLOR ))
  {
    color.clrIndex = type;

    if( !ctltype || !WinQueryControlColors( m_handle, ctltype, CCF_APPLICATION, 1, &color )) {
      color.clrValue = CLR_DEFAULT;
    }
  }

  if( color.clrValue == CCV_NOTFOUND ||
      color.clrValue == CCV_IGNORE   ||
      color.clrValue == CCV_DEFAULT  )
  {
    color.clrValue = CLR_DEFAULT;
  }

  return color.clrValue;
}

/* Sets the specified color value
 */

void PMWindow::color( LONG type, LONG color )
{
  LONG  ctltype = os2_cct( m_handle );
  ULONG pp_id   = os2_pp_to_cci( ctltype, type );

  if( pp_id ) {
    if( color == CLR_DEFAULT ) {
      WinRemovePresParam( m_handle, pp_id );
    } else {
      if( color < 0 ) {
        color = WinQuerySysColor( HWND_DESKTOP, color, 0 );
      }

      WinSetPresParam( m_handle, pp_id, sizeof( RGB ), &color );
    }
  }
}

/* Returns the window rectangle.
 */

PMRect PMWindow::rectangle() const
{
  SWP    swp_rect;
  PMRect rect;

  if( !WinQueryWindowPos( m_handle, &swp_rect )) {
    PM_THROW_GUIERROR();
  }

  rect.x  = swp_rect.x;
  rect.y  = swp_rect.y;
  rect.cx = swp_rect.cx;
  rect.cy = swp_rect.cy;

  return rect;
}

/* Makes the window visible.
 */

void PMWindow::show( BOOL state )
{
  if( !WinShowWindow( m_handle, state )) {
    PM_THROW_GUIERROR();
  }
}

/* Makes the window invisible.
 */

void PMWindow::hide() {
  show( FALSE );
}

/**
 * Is the window visible.
 *
 * If the window's style is set to visible, TRUE is returned.
 * Otherwise, FALSE is returned. A window can have the style visible
 * and yet not be showing if it is covered by another window.
 */

BOOL PMWindow::is_visible() {
  return WinQueryWindowULong( handle(), QWL_STYLE ) & WS_VISIBLE;
}

/* Sets the input focus to the window.
 */

void PMWindow::set_focus()
{
  if( !WinSetFocus( HWND_DESKTOP, m_handle )) {
    if( ERRORIDERROR( WinGetLastError( PMGUI::hab())) != PMERR_CANNOT_SET_FOCUS ) {
      PM_THROW_GUIERROR();
    }
  }
}

/* Has focus.
 *
 * If the window has the input focus, TRUE is returned.
 * Otherwise, FALSE is returned.
 */

BOOL PMWindow::has_focus() const {
  return WinIsChild( WinQueryFocus( HWND_DESKTOP ),  m_handle );
}

/* Enables the window to accept keyboard and mouse input.
 */

void PMWindow::enable( BOOL state )
{
  if( !WinEnableWindow( m_handle, state )) {
    PM_THROW_GUIERROR();
  }
}

/* Prevents keyboard and mouse input from being sent
 * to the window.
 */

void PMWindow::disable() {
  enable( FALSE );
}

/* Enables the window to accept dropped objects.
 */

void PMWindow::enable_drop( LONG type )
{
  m_drop_types = type;
  handle_events();
}

/* Is the window valid.
 *
 * If this object represents a valid window in the
 * window system, TRUE is returned. If the window has yet to be
 * created or has already been destroyed, FALSE is returned.
 */

BOOL PMWindow::is_valid() const {
  return WinIsWindow( PMGUI::hab(), m_handle );
}

/* This method adds a region to a window's update region.
 *
 * The update region is a subregion of a window that is
 * deemed "invalid" or incorrect in visual terms and is
 * in need of redrawing.
 */

void PMWindow::invalidate( const PMRect& rect )
{
  // Invalidation must use inclusive-exclusive rectangles
  RECTL sys_rect = rect.as_sys_value( PMRect::exclusive );

  if( !WinInvalidateRect( m_handle, &sys_rect, TRUE )) {
    PM_THROW_GUIERROR();
  }
}

/* This method adds the whole window to a window's update region.
 *
 * The update region is a subregion of a window that is
 * deemed "invalid" or incorrect in visual terms and is
 * in need of redrawing.
 */

void PMWindow::invalidate()
{
  if( !WinInvalidateRect( m_handle, NULL, TRUE )) {
    PM_THROW_GUIERROR();
  }
}

/* Captures mouse pointer.
 *
 * If capture is true, pointer events are sent only to this window
 * even if the pointer is outside of this window. If capture is false,
 * the window releases the pointer capture. If you attempt to capture
 * the pointer when another window currently is capturing the pointer,
 * an exception is thrown.
 */

void PMWindow::capture_pointer( BOOL capture )
{
  if( !WinSetCapture( HWND_DESKTOP, capture ? m_handle : NULLHANDLE )) {
    PM_THROW_GUIERROR();
  }
}

/* Release mouse pointer.
 *
 * Causes the window to release the pointer capture (pointer capture
 * is set with the function capture_pointer).
 *
 * This function causes mouse events to again be dispatched to the window
 * underneath the mouse pointer.
 */

void PMWindow::release_pointer() {
  capture_pointer( FALSE );
}

/* Has pointer captured.
 *
 * If this window is currently capturing pointer events, TRUE is
 * returned. Otherwise, FALSE is returned.
 */

BOOL PMWindow::has_pointer_captured() const {
  return ( WinQueryCapture( HWND_DESKTOP ) == m_handle );
}

/* Sets the appearance used by the mouse pointer when it is
 * over the window.
 */

void PMWindow::pointer( LONG id )
{
  if( id > 0 ) {
    m_pointer_id = id;
    m_pointer    = WinQuerySysPointer( HWND_DESKTOP, id, FALSE );
  } else {
    m_pointer_id = 0;
    m_pointer    = NULL;
  }

  POINTL pos;
  WinQueryPointerPos( HWND_DESKTOP, &pos );

  if( WinIsChild( WinWindowFromPoint( HWND_DESKTOP, &pos, TRUE ), m_handle )) {
    if( m_pointer ) {
      WinSetPointer( HWND_DESKTOP, m_pointer );
    } else {
      WinSetPointerPos( HWND_DESKTOP, pos.x, pos.y );
    }
  }
}

/* Returns the mouse pointer used when the mouse is over
 * the window.
 */

LONG PMWindow::pointer() const {
  return m_pointer_id;
}

/* Replaces the accelerator keys used by the window.
 */

void PMWindow::attach_accelerators( SHORT res_id, HMODULE hmodule )
{
  HACCEL hnew = WinLoadAccelTable( PMGUI::hab(), hmodule, res_id );

  if( hnew == NULLHANDLE ) {
    PM_THROW_GUIERROR();
  }

  // Need handler for non-frame windows, since PM only supports
  // accelerator tables for frames. The handler emulates frame window
  // behavior by processing WM_TRANSLATEACCEL messages using the
  // accelerator table we store in this method.

  handle_events();

  if( !send( PM_SETACCELTABLE, MPFROMLONG( hnew ), 0 )) {
    PM_THROW_GUIERROR();
  }
}

/* Detaches the accelerator keys used by the window.
 */

void PMWindow::detach_accelerators()
{
  if( !send( PM_SETACCELTABLE, MPFROMLONG( NULLHANDLE ), 0 )) {
    PM_THROW_GUIERROR();
  }
}

/* This method starts a timer.
 *
 * This method creates a timer identified by id, set to
 * time out every timeout milliseconds. When a timer times out,
 * a WM_TIMER message is posted.
 */

void PMWindow::start_timer( ULONG id, ULONG timeout )
{
  if( WinStartTimer( PMGUI::hab(), m_handle, id, timeout ) == 0 ) {
    PM_THROW_GUIERROR();
  }
}

/* This method stops a timer.
 *
 * When this method is called, no further messages are received
 * from the stopped timer, even if it has timed out.
 */

void PMWindow::stop_timer( ULONG id )
{
  if( !WinStopTimer( PMGUI::hab(), m_handle, id )) {
    PM_THROW_GUIERROR();
  }
}

/* Handle events.
 *
 * Attaches the handler to the PMWindow object. The windows's
 * dispatch function is called to process all events sent or posted to the
 * window.
 */

void PMWindow::handle_events()
{
  if( !m_default_handler )
  {
    char classname[64];
    BOOL fast_map = FALSE;

    if( !m_wrapped ) {
      WinQueryClassName( m_handle, sizeof( classname ), classname );

      if( strcmp( classname, "PMWindow" ) == 0 ||
          strcmp( classname, "#1"       ) == 0 || // WC_FRAME
          strcmp( classname, "#2"       ) == 0 || // WC_COMBOBOX
          strcmp( classname, "#3"       ) == 0 || // WC_BUTTON
          strcmp( classname, "#4"       ) == 0 || // WC_MENU
          strcmp( classname, "#6"       ) == 0 || // WC_ENTRYFIELD
          strcmp( classname, "#7"       ) == 0 || // WC_LISTBOX
          strcmp( classname, "#8"       ) == 0 || // WC_SCROLLBAR
          strcmp( classname, "#9"       ) == 0 || // WC_TITLEBAR
          strcmp( classname, "#10"      ) == 0 || // WC_MLE
          strcmp( classname, "#32"      ) == 0 || // WC_SPINBUTTON
          strcmp( classname, "#37"      ) == 0 || // WC_CONTAINER
          strcmp( classname, "#38"      ) == 0 || // WC_SLIDER
          strcmp( classname, "#39"      ) == 0 || // WC_VALUESET
          strcmp( classname, "#40"      ) == 0 || // WC_NOTEBOOK
          strcmp( classname, "#65"      ) == 0  ) // WC_CIRCULARSLIDER
      {
        fast_map = TRUE;
      }
    }

    if( fast_map ) {
      if( !WinSetWindowPtr( m_handle, 0, this )) {
        PM_THROW_GUIERROR();
      }
      m_default_handler = WinSubclassWindow( m_handle, PMWindow::win_proc_via_ptr );
    } else {
      PMWindowSet::insert( m_handle, this );
      m_default_handler = WinSubclassWindow( m_handle, PMWindow::win_proc_via_map );
    }
    if( !m_default_handler ) {
      PM_THROW_GUIERROR();
    }
  }
}

/* Stop handling events.
 *
 * Detaches the handler from the PMWindow object. The window's
 * dispatch function is no longer called to process events sent or
 * posted to the window.
 */

void PMWindow::stop_handling_events()
{
  if( m_default_handler && WinIsWindow( PMGUI::hab(), m_handle )) {
    if( WinSubclassWindow( m_handle, m_default_handler ) == 0 ) {
      PM_THROW_GUIERROR();
    }

    if( WinQueryWindowPtr( m_handle, 0 ) == this ) {
      if( !WinSetWindowPtr( m_handle, 0, 0 )) {
        PM_THROW_GUIERROR();
      }
    } else {
      PMWindowSet::remove( m_handle );
    }

    m_default_handler = NULL;
  }
}

/* Determines whether to delete the window object when the presentation
 * window is destroyed.
 *
 * The deletion occurs when the window system dispatches a destroy
 * event to the window.
 */

void PMWindow::auto_delete_object( BOOL state ) {
  m_auto_delete = state;
}

/* If the window object is deleted when a destroy event is dispatched to
 * the window, TRUE is returned.
 */

BOOL PMWindow::is_auto_delete_object() {
  return m_auto_delete;
}

/* Prepares the window to the drop operation.
 */

MRESULT PMWindow::drag_over( PDRAGINFO pdinfo )
{
  USHORT    drag    = DOR_NEVERDROP;
  USHORT    drag_op = DO_UNKNOWN;
  PDRAGITEM pditem;
  int       i;

  if( !DrgAccessDraginfo( pdinfo )) {
    return MRFROM2SHORT( DOR_NEVERDROP, 0 );
  }

  for( i = 0; i < pdinfo->cditem; i++ ) {
    pditem = DrgQueryDragitemPtr( pdinfo, i );

    if( DrgVerifyRMF( pditem, "DRM_OS2FILE", NULL ) && ( m_drop_types & drop_os2file )) {
      drag    = DOR_DROP;
      drag_op = DO_MOVE;
    } else {
      drag    = DOR_NEVERDROP;
      drag_op = DO_UNKNOWN;
      break;
    }
  }

  DrgFreeDraginfo( pdinfo );
  return MPFROM2SHORT( drag, drag_op );
}

/* Receives the dropped objects.
 */

MRESULT PMWindow::drop( PDRAGINFO pdinfo )
{
  PDRAGITEM pditem;

  if( !DrgAccessDraginfo( pdinfo )) {
    return 0;
  }

  pditem = DrgQueryDragitemPtr( pdinfo, 0 );

  if( DrgVerifyRMF( pditem, "DRM_OS2FILE", NULL ) && ( m_drop_types & drop_os2file ))
  {
    char filename[_MAX_PATH];
    char pathname[_MAX_PATH];

    DrgQueryStrName( pditem->hstrContainerName, sizeof( pathname ), pathname );
    DrgQueryStrName( pditem->hstrSourceName, sizeof( filename ), filename );
    strlcat( pathname, filename, sizeof( pathname ));
    text( pathname );
  }

  DrgDeleteDraginfoStrHandles( pdinfo );
  DrgFreeDraginfo( pdinfo );
  return 0;
}

/* Dispatch system native events.
 *
 * GLWindow calls this function when a system native window
 * event occurs.
 */

MRESULT PMWindow::dispatch( ULONG msg, MPARAM mp1, MPARAM mp2 )
{
  switch( msg ) {
    case WM_CONTROLPOINTER:
    {
      // During processing this message the mouse pointer can
      // be set for all of child windows.
      PMWindow* child = win_via_handle( WinWindowFromID( m_handle, SHORT1FROMMP(mp1)));
      if( child && child->m_pointer ) {
        return MRFROMLONG( child->m_pointer );
      }
      break;
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

    // The handler emulates frame window behavior by processing
    // WM_TRANSLATEACCEL messages.
    case WM_TRANSLATEACCEL:
      if( m_acceltable != NULLHANDLE ) {
        if( WinTranslateAccel( PMGUI::hab(), m_handle, m_acceltable, (PQMSG)mp1 )) {
          return MRFROMLONG( TRUE );
        }
      }
      break;

    case DM_DRAGOVER:
      if( m_drop_types ) {
        return drag_over((PDRAGINFO)mp1 );
      }
      break;

    case DM_DROP:
      if( m_drop_types ) {
        return drop((PDRAGINFO)mp1 );
      }
      break;
  }

  return dispatch_everything( msg, mp1, mp2 );
}

/* Dispatch all not catched events.
 *
 * A virtual method that provides default implementation for
 * all events that occur on every window.
 */

MRESULT PMWindow::dispatch_everything( ULONG msg, MPARAM mp1, MPARAM mp2 )
{
  switch( msg ) {
    case WM_DESTROY:
    {
      MRESULT rc = 0;

      if( m_default_handler ) {
        rc = m_default_handler( handle(), msg, mp1, mp2 );
        stop_handling_events();
      }
      if( m_auto_delete ) {
        delete this;
      }
      return rc;
    }

    case WM_PRESPARAMCHANGED:
      invalidate();
      break;

    case WM_SETFOCUS:
      post( PM_SETFOCUS, mp1, mp2 );
      break;
  }

  if( m_default_handler ) {
    return m_default_handler( handle(), msg, mp1, mp2 );
  } else {
    return 0;
  }
}

/* Events processing.
 */

MRESULT _System PMWindow::win_proc_via_ptr( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
  PMWindow* window_ptr =
    (PMWindow*)WinQueryWindowPtr( hwnd, 0 );

  if( window_ptr ) {
    return window_ptr->dispatch( msg, mp1, mp2 );
  } else {
    return 0;
  }
}

/* Events processing.
 */

MRESULT _System PMWindow::win_proc_via_map( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
  PMWindow* window = PMWindowSet::query( hwnd );

  if( window ) {
    return window->dispatch( msg, mp1, mp2 );
  }

  return 0;
}

/* Returns a pointer to the windows object associated
 * with specified window handle.
 */

PMWindow* PMWindow::win_via_handle( HWND hwnd )
{
  PVOID win_proc = WinQueryWindowPtr( hwnd, QWP_PFNWP );

  if( win_proc == win_proc_via_ptr ) {
    return (PMWindow*)WinQueryWindowPtr( hwnd, 0 );
  }

  return PMWindowSet::query( hwnd );
}

/* Default window procedure.
 */

MRESULT _System PMWindow::def_proc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
  switch( msg )
  {
    case WM_PRESPARAMCHANGED:
      WinInvalidateRect( hwnd, NULL, TRUE );
      break;

    case WM_MOUSEMOVE:
    {
      HPOINTER hptr   = WinQuerySysPointer( HWND_DESKTOP, SPTR_ARROW, FALSE );
      USHORT   id     = WinQueryWindowUShort( hwnd, QWS_ID );
      HWND     howner = WinQueryWindow( hwnd, QW_OWNER );

      if( howner ) {
        hptr = (HPOINTER)WinSendMsg( howner, WM_CONTROLPOINTER,
                                     MPFROMSHORT( id ), MPFROMLONG( hptr ));
      }

      WinSetPointer( HWND_DESKTOP, hptr );
      return 0;
    }
  }

  return WinDefWindowProc( hwnd, msg, mp1, mp2 );
}

