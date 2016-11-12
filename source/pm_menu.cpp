/*
 * Copyright (C) 2001-2011 Dmitry A.Steklenev
 *
 * $Id: pm_menu.cpp,v 1.9 2011/03/11 12:59:32 glass Exp $
 */

#include "pm_menu.h"
#include "pm_language.h"
#include "pm_gui.h"
#include "pm_error.h"
#include "pm_window.h"

/* Constructs the menu window from the dialog template.
 */

PMMenu::PMMenu( HWND hparent, SHORT res_id, HMODULE hmodule )

: m_id     ( res_id  ),
  m_parent ( hparent ),
  m_wrapped( FALSE   )
{
  m_handle = WinLoadMenu( hparent, hmodule, res_id );

  if( m_handle == NULLHANDLE ) {
    PM_THROW_GUIERROR();
  }

  if( !WinSetWindowUShort( m_handle, QWS_ID, (USHORT)res_id )) {
    PM_THROW_GUIERROR();
  }
}

/* Wraps the menu window object around an existing
 * presentation window handle.
 */

PMMenu::PMMenu( HWND handle )

: m_handle ( handle ),
  m_wrapped( TRUE   ),
  m_parent ( WinQueryWindow( m_handle, QW_PARENT  )),
  m_id     ( WinQueryWindowUShort( handle, QWS_ID ))
{}

/* Destructs the menu window object.
 */

PMMenu::~PMMenu()
{
  if( !m_wrapped ) {
    if( WinIsWindow( PMGUI::hab(), m_handle )) {
      if( !WinDestroyWindow( m_handle )) {
        PM_THROW_GUIERROR();
      }
    }
  }
}

/* Returns the number of items in the menu.
 */

SHORT PMMenu::count() const {
  return (SHORT)WinSendMsg( m_handle, MM_QUERYITEMCOUNT, 0, 0 );
}

/* Returns the text of the specified menu item.
 */

char* PMMenu::item_text( SHORT item_id, char* result, short size ) const
{
  if( !WinSendMsg( m_handle, MM_QUERYITEMTEXT,
                   MPFROM2SHORT( item_id, size ), MPFROMP( result )))
  {
    PM_THROW_GUIERROR();
  }

  return result;
}

/* Returns the length of the text of the specified menu item.
 */

int PMMenu::item_text_len( SHORT item_id ) const {
  return (int)WinSendMsg( m_handle, MM_QUERYITEMTEXTLENGTH, MPFROMSHORT( item_id ), 0 );
}

/* Sets the text into the specified menu item.
 */

void PMMenu::item_text( SHORT item_id, const char* text )
{
  if( !WinSendMsg( m_handle, MM_SETITEMTEXT, MPFROMSHORT( item_id ), MPFROMP( text ))) {
    PM_THROW_GUIERROR();
  }
}

/* Sets a new font to be used by the window.
 */

void PMMenu::font( const char* font ) {
  PMWindow( m_handle ).font( font );
}

/* Sets the check state of the specified menu item.
 */

void PMMenu::check( SHORT item_id, BOOL state ) {
  WinCheckMenuItem( m_handle, item_id, state );
}

/* Sets the state of the specified menu item to the enable.
 */

void PMMenu::enable( SHORT item_id, BOOL state ) {
  WinEnableMenuItem( m_handle, item_id, state );
}

/* Sets the state of the specified menu item to the disable.
 */

void PMMenu::disable( SHORT item_id ) {
  enable( item_id, FALSE );
}

/* Displays the pop-up menu.
 */

void PMMenu::show( SHORT item_id )
{
  POINTL   pos;
  SWP      swp;

  WinQueryPointerPos( HWND_DESKTOP, &pos );
  WinMapWindowPoints( HWND_DESKTOP, m_parent, &pos, 1 );

  if( WinWindowFromPoint( m_parent, &pos, TRUE ) == NULLHANDLE )
  {
    // The pop-up menu is probably activated from the keyboard.
    WinQueryWindowPos( m_parent, &swp );
    pos.x = swp.cx/2;
    pos.y = swp.cy/2;
  }

  if( !WinPopupMenu( m_parent, m_parent, m_handle, pos.x, pos.y, item_id,
                     PU_POSITIONONITEM | PU_HCONSTRAIN   | PU_VCONSTRAIN |
                     PU_MOUSEBUTTON1   | PU_MOUSEBUTTON2 | PU_KEYBOARD   ))
  {
    PM_THROW_GUIERROR();
  }
}

/* Translates the whole menu.
 *
 * Translates the menu text and all the submenu texts using
 * for this purpose the current PMLanguage::instance
 * of the messages management object.
 */

void PMMenu::translate()
{
  if( PMLanguage::instance ) {
    translate_submenu( m_handle );
  }
}

/* Translates the whole submenu.
 */

void PMMenu::translate_submenu( HWND hwnd )
{
  SHORT    item_id;
  SHORT    i;
  SHORT    count = (SHORT)WinSendMsg( hwnd, MM_QUERYITEMCOUNT, 0, 0 );
  MENUITEM item;

  char current[256] = "";
  char message[256];

  for( i = 0; i < count; i++ ) {
    item_id = (SHORT)WinSendMsg( hwnd, MM_ITEMIDFROMPOSITION, MPFROMSHORT(i), 0 );
    if( item_id != MIT_ERROR ) {
      if( WinSendMsg( hwnd, MM_QUERYITEMTEXT,
                      MPFROM2SHORT( item_id, sizeof( current )),
                      MPFROMP( current )) > 0 )
      {
        PMLanguage::instance->message( message, sizeof( message ), current );

        if( strcmp( message, current ) == 0 )
        {
          char  key[256];
          char* p;

          if(( p = strchr( current, '\t' )) == NULL ) {
            p = current + strlen( current );
          }
          while( p > current ) {
            if( p[-1] == '.' ) {
              --p;
            } else {
              break;
            }
          }
          if( p > current && *p ) {
            strlcpy( key, current, p - current + 1 );
            PMLanguage::instance->message( message, sizeof( message ), key );
            strlcat( message, p, sizeof( message ));
          }
        }

        WinSendMsg( hwnd, MM_SETITEMTEXT,
                    MPFROMSHORT( item_id ), MPFROMP( message ));
      }

      if( WinSendMsg( hwnd, MM_QUERYITEM,
                      MPFROM2SHORT( item_id, FALSE ), MPFROMP( &item )))
      {
        if( item.afStyle | MIS_SUBMENU ) {
          translate_submenu( item.hwndSubMenu );
        }
      }
    }
  }
}


