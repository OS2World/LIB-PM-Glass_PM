/*
 * Copyright (C) 2008 Dmitry A.Steklenev
 *
 * $Id: pm_toolbar.cpp,v 1.12 2012/06/13 11:36:11 glass Exp $
 */

#include "pm_toolbar.h"
#include "pm_gui.h"
#include "pm_png.h"
#include <etoolbar.h>
#include <eicons.h>

/* Wraps the toolbar control window object
 * around an existing presentation window handle.
 */

PMToolBar::PMToolBar( HWND handle )
: PMWindow( handle )
{}

/* Wraps the toolbar control window object around
 * an existing child window with the specified identity.
 */

PMToolBar::PMToolBar( HWND hparent, SHORT id )
: PMWindow( hparent, id )
{}

/* Constructs the toolbar control window.
 */

PMToolBar::PMToolBar( SHORT id, HWND hparent,
                      LONG x, LONG y, LONG cx, LONG cy, ULONG style )

: PMWindow( WC_ER_TOOLBAR, id, "", hparent, hparent,
            x, y, cx, cy, style, NULL )
{}

/** Defines the picture size of the toolbar's buttons. */
void PMToolBar::size( USHORT pixels )
{
  PMRect rect = rectangle();
  rect.cy = pixels - 1 + TOOLBAR_HEIGHT_ADD;

  send( TBM_SETPICTSIZE, MPFROMSHORT( pixels ), 0 );
  rectangle( rect );
}

/* Extracts tooltip text from a menu item text.
 */

char* PMToolBar::extract_tooltip( char* result, const char* string, int size )
{
  char  ch;
  const char* s = string;
  char* p = result;
  char* pend = p + size - 1;

  if( string ) {
    while( *s && p < pend ) {
      ch = *s++;
      if( ch == '\t' ) {
        break;
      } else if( ch == '~' ) {
        if( *s == '~' ) {
          ++s;
        } else {
          continue;
        }
      }
      *p++ = ch;
    }

    *p = 0;
    return result;
  }

  return NULL;
}

/* Adds button into toolbar.
 */

void PMToolBar::add_button( SHORT id, const char* text,
                                      const char* tooltip, SHORT res_id, SHORT menu_res_id, HMODULE hmodule )
{
  AddBtnStruct add = { 0 };
  char  extracted[128];
  ULONG size;

  add.cmd         = id;
  add.buttonText  = (PSZ)text;
  add.tooltipText = extract_tooltip( extracted, tooltip, sizeof( extracted ));
  add.picType     = PICTURE_TYPE_BITMAP;
  add.pictRes     = res_id;
  add.pictHmod    = hmodule;
  add.enabled     = TRUE;
  add.menuRes     = menu_res_id;
  add.menuHmod    = hmodule;

  if( res_id ) {
    if( DosQueryResourceSize( hmodule, RT_PNG, res_id, &size ) == NO_ERROR ) {
      add.picType = PICTURE_TYPE_PNG;
      add.resType = RT_PNG;
    }
  }

  send( TBM_ADDBUTTON, MPFROMP( &add ), 0 );
}

/* Adds button into toolbar.
 */

void PMToolBar::add_standard_button( SHORT id, const char* text, const char* tooltip,
                                     LONG ibmp, ULONG fl, SHORT menu_res_id, HMODULE hmodule )
{
  char extracted[128];
  AddBtnStruct add = { 0 };

  add.cmd         = id;
  add.buttonText  = (PSZ)text;
  add.tooltipText = extract_tooltip( extracted, tooltip, sizeof( extracted ));
  add.picType     = PICTURE_TYPE_BITMAP_HANDLE2;
  add.hBitmap     = eQueryToolbarBitmap( HWND_DESKTOP, ibmp, fl & ~DBT_COPY );
  add.pictHmod    = hmodule;
  add.enabled     = TRUE;
  add.menuRes     = menu_res_id;
  add.menuHmod    = hmodule;

  send( TBM_ADDBUTTON, MPFROMP( &add ), 0 );
}

/* Adds separator into toolbar.
 */

void PMToolBar::add_separator() {
  send( TBM_ADDSEPARATOR, 0, 0 );
}

/* Adds control into toolbar.
 */

void PMToolBar::add_control( HWND hwnd, SHORT cx, SHORT cy, const char* tooltip )
{
  char extracted[128];
  AddCtrlStruct add = { 0 };

  add.ctrlHandle  = hwnd;
  add.cx          = cx;
  add.cy          = cy;
  add.tooltipText = extract_tooltip( extracted, tooltip, sizeof( extracted ));

  send( TBM_ADDCONTROL, MPFROMP( &add ), 0 );
}

/* Makes the buttons text visible.
 */

void PMToolBar::show_text( BOOL show ) {
  send( TBM_SHOWTEXT, MPFROMLONG( show ), 0 );
}

/* Makes the buttons text invisible.
 */

void PMToolBar::hide_text() {
  show_text( FALSE );
}

/* Sets the state of the specified toolbar button to the enable.
 */

void PMToolBar::enable_button( SHORT id, BOOL state ) {
  send( TBM_ENABLEITEM, MPFROMSHORT( id ), MPFROMLONG( state ));
}

/* Sets the state of the specified toolbar button to the disable.
 */

void PMToolBar::disable_button( SHORT id ) {
  send( TBM_ENABLEITEM, MPFROMSHORT( id ), MPFROMLONG( FALSE ));
}

/* Makes toolbar button checked or unchecked.
 */

void PMToolBar::check( SHORT id, BOOL state ) {
  send( TBM_SETCHECK, MPFROMSHORT( id ), MPFROMLONG( state ));
}

