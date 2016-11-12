/*
 * Copyright (C) 2001-2008 Dmitry A.Steklenev
 *
 * $Id: pm_listbox.cpp,v 1.9 2011/03/11 12:59:32 glass Exp $
 */

#include "pm_listbox.h"

/* Wraps the list box control window object around
 * an existing presentation window handle.
 */

PMListBox::PMListBox( HWND handle )
: PMWindow( handle )
{}

/* Wraps the list box control window object around
 * an existing child window with the specified identity.
 */

PMListBox::PMListBox( HWND hparent, SHORT id )
: PMWindow( hparent, id )
{}

/* Constructs the list box control window.
 */

PMListBox::PMListBox( SHORT id, HWND hparent,
                      LONG x, LONG y, LONG cx, LONG cy, ULONG style )

: PMWindow( WC_LISTBOX, id, "", hparent, hparent,
            x, y, cx, cy, style, NULL )
{}

/* Constructs the presentation window of the specified class.
 */

PMListBox::PMListBox( const char* classname, SHORT id,
                      const char* text, HWND hparent, HWND howner,
                      LONG x, LONG y, LONG cx, LONG cy, ULONG style, PVOID classdata )

: PMWindow( classname, id, text, hparent, howner,
                        x, y, cx, cy, style, classdata )
{}

/* Inserts an item into a list box control.
 */

int PMListBox::insert( const char* string, ULONG hitem, int before )
{
  int pos = (int)WinSendMsg( handle(), LM_INSERTITEM,
                             MPFROMSHORT(before),
                             MPFROMP(string));

  if( pos == LIT_ERROR || pos == LIT_MEMERROR ) {
    PM_THROW_GUIERROR();
  }

  if( hitem ) {
    if( !WinSendMsg( handle(), LM_SETITEMHANDLE, MPFROMSHORT(pos), MPFROMLONG(hitem))) {
      PM_THROW_GUIERROR();
    }
  }

  return pos;
}

/* Removes an item from a list box control.
 */

int PMListBox::remove( int pos ) {
  return LONGFROMMR( WinSendMsg( handle(), LM_DELETEITEM, MPFROMSHORT( pos ), 0 ));
}

/* Returns the index of the list box item whose
 * text matches the string.
 */

int PMListBox::search( const char* string ) const
{
  int pos = (int)WinSendMsg( handle(),
                             LM_SEARCHSTRING,
                             MPFROM2SHORT( 0, LIT_FIRST ),
                             MPFROMP(string));
  if( pos == LIT_ERROR ) {
    PM_THROW_GUIERROR();
  }

  return pos;
}

/* Removes all items from the list box control.
 */

void PMListBox::clear()
{
  if( !WinSendMsg( handle(), LM_DELETEALL, 0, 0 )) {
    PM_THROW_GUIERROR();
  }
}

/* Sets the selection state of an item in a list box.
 */

void PMListBox::select( int pos, BOOL state )
{
  if( pos != LIT_NONE ) {
    if( !WinSendMsg( handle(), LM_SELECTITEM, MPFROMSHORT(pos), MPFROMLONG(state))) {
      PM_THROW_GUIERROR();
    }
  }
}

/* Sets the selection state of all items in a list box.
 */

void PMListBox::select_all( BOOL state )
{
  if( WinQueryWindowULong( handle(), QWL_STYLE ) & ( LS_EXTENDEDSEL | LS_MULTIPLESEL ))
  {
    int i;

    if( state ) {
      for( i = 0; i < count(); i++ ) {
        select( i, TRUE );
      }
    } else {
      while(( i = selected()) != LIT_NONE ) {
        select( i, FALSE );
      }
    }
  }
}

/* Returns the index of the cursored item.
 */

int PMListBox::cursored() const {
  return (int)WinSendMsg( handle(), LM_QUERYSELECTION, MPFROMSHORT( LIT_CURSOR ), 0 );
}

/* Returns the index of the first selected item.
 */

int PMListBox::selected() const {
  return (int)WinSendMsg( handle(), LM_QUERYSELECTION, MPFROMSHORT( LIT_FIRST ), 0 );
}

/* Returns the index of the next selected item.
 */

int PMListBox::selected( int pos ) const {
  return (int)WinSendMsg( handle(), LM_QUERYSELECTION, MPFROMSHORT( pos ), 0 );
}

/* Returns the index of the item currently at the top of the
 * list box.
 */

int PMListBox::top() const {
  return (int)WinSendMsg( handle(), LM_QUERYTOPINDEX, 0, 0 );
}

/* Scrolls a particular item to the top of the list box.
 */

void PMListBox::top( int pos ) {
  WinSendMsg( handle(), LM_SETTOPINDEX, MPFROMSHORT( pos ), 0 );
}

/* Returns the number of items stored in the list box.
 */

int PMListBox::count() const {
  return (int)WinSendMsg( handle(), LM_QUERYITEMCOUNT, 0, 0 );
}

/* Returns the text of the specified list box item.
 */

char* PMListBox::item_text( int pos, char* result, short size ) const
{
  WinSendMsg( handle(), LM_QUERYITEMTEXT,
              MPFROM2SHORT( pos, size ), MPFROMP( result ));

  return result;
}

/* Returns the length of the text of the specified list box item.
 */

int PMListBox::item_text_len( int pos ) const {
  return (int)WinSendMsg( handle(), LM_QUERYITEMTEXTLENGTH, MPFROMSHORT( pos ),  0 );
}

/* Sets the text into the specified list box item.
 */

void PMListBox::item_text( int pos, const char* text )
{
  if( !WinSendMsg( handle(), LM_SETITEMTEXT,
                   MPFROMSHORT( pos ), MPFROMP( text )))
  {
    PM_THROW_GUIERROR();
  }
}

/* Sets the handle of the specified list box item.
 */

void PMListBox::item_handle( int pos, ULONG hitem )
{
  if( !WinSendMsg( handle(), LM_SETITEMHANDLE, MPFROMSHORT( pos ), MPFROMLONG( hitem ))) {
    PM_THROW_GUIERROR();
  }
}

/* Returns the handle of the specified list box item.
 */

ULONG PMListBox::item_handle( int pos ) const {
  return (ULONG)WinSendMsg( handle(), LM_QUERYITEMHANDLE, MPFROMSHORT( pos ), 0 );
}

