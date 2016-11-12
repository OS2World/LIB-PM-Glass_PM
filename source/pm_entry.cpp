/*
 * Copyright (C) 2008-2011 Dmitry A.Steklenev
 *
 * $Id: pm_entry.cpp,v 1.8 2011/03/11 12:59:31 glass Exp $
 */

#include "pm_entry.h"

/* Wraps the entry field control window object around
 * an existing presentation window handle.
 */

PMEntry::PMEntry( HWND handle )
: PMWindow( handle )
{}

/* Wraps the entry field control window object around
 * an existing child window with the specified identifier.
 */

PMEntry::PMEntry( HWND hparent, SHORT id )
: PMWindow  ( hparent, id )
{}

/* Constructs the entry field control window.
 */

PMEntry::PMEntry( SHORT id, const char* text, HWND hparent,
                  LONG x, LONG y, LONG cx, LONG cy, ULONG style )

: PMWindow  ( WC_ENTRYFIELD, id, text, hparent, hparent,
              x, y, cx, cy, style, NULL )
{
  if( style & ES_READONLY ) {
    color( CCI_BACKGROUND, SYSCLR_DIALOGBACKGROUND );
  }
}

/* Returns the the maximum number of bytes the entry
 * field can contain.
 */

USHORT PMEntry::limit() const
{
  WNDPARAMS  prm;
  ENTRYFDATA efd;

  prm.fsStatus  = WPM_CTLDATA;
  prm.pCtlData  = &efd;
  prm.cbCtlData = sizeof( ENTRYFDATA );

  WinSendMsg( handle(), WM_QUERYWINDOWPARAMS, MPFROMP( &prm ), 0 );
  return efd.cchEditLimit;
}

/* Sets the maximum number of bytes the entry field
 * can contain.
 */

void PMEntry::limit( USHORT len ) {
  send( EM_SETTEXTLIMIT, MPFROMSHORT( len ), 0 );
}

/* Deletes the text that forms the current selection.
 */

void PMEntry::clear() {
  send( EM_CLEAR, 0, 0 );
}

/* Copies the current selection to the clipboard.
 */

void PMEntry::copy() {
  send( EM_COPY, 0, 0 );
}

/* Copies the text that forms the current selection to
 * the clipboard, and then deletes it.
 */

void PMEntry::cut() {
  send( EM_CUT, 0, 0 );
}

/* Replaces the text that forms the current selection with
 * text from the clipboard.
 */

void PMEntry::paste() {
  send( EM_PASTE, 0, 0 );
}

/* Enables or disables the read-only mode on
 * an entry field control.
 */

void PMEntry::enable_data_update( BOOL state )
{
  send( EM_SETREADONLY, MPFROMSHORT( !state ), 0 );
  // Always use predefined color because otherwise there are problems
  // at storing and loading of presentation parameters.
  color( CCI_BACKGROUND, state ? SYSCLR_ENTRYFIELD : SYSCLR_DIALOGBACKGROUND );
}

/* Prevents inserting or changing characters
 * in the entry field's text.
 */

void PMEntry::disable_data_update() {
  enable_data_update( FALSE );
}

/* If the contents of the entry field can be modified,
 * TRUE is returned.
 */

BOOL PMEntry::is_writeable() const {
  return !WinSendMsg( handle(), EM_QUERYREADONLY, 0, 0 );
}

