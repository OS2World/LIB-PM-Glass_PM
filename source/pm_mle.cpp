/*
 * Copyright (C) 2001-2011 Dmitry A.Steklenev
 *
 * $Id: pm_mle.cpp,v 1.9 2011/11/25 13:05:04 glass Exp $
 */

#include "pm_mle.h"
#include "pm_font.h"
#include "pm_gui.h"

/* Wraps the multi-line entry field control window object
 * around an existing presentation window handle.
 */

PMMLE::PMMLE( HWND handle )
: PMWindow( handle )
{}

/* Wraps the multi-line entry field control window object around
 * an existing child window with the specified identity.
 */

PMMLE::PMMLE( HWND hparent, SHORT id )
: PMWindow( hparent, id )
{}

/* Constructs the multi-line entry field control window.
 */

PMMLE::PMMLE( SHORT id, HWND hparent,
              LONG x, LONG y, LONG cx, LONG cy, ULONG style )

: PMWindow( WC_MLE, id, "", hparent, hparent,
            x, y, cx, cy, style, NULL )
{
  text_format( MLFIE_NOTRANS );
}

/* Sets a new font to be used by the window.
 */

void PMMLE::font( const char* fontname )
{
  PMFont font( fontname );

  if( !send( MLM_SETFONT, MPFROMP( font.attrs()), 0 )) {
    PM_THROW_GUIERROR();
  }
}

/* Sets the format to be used for text importing and exporting.
 */

void PMMLE::text_format( USHORT format ) {
  WinSendMsg( handle(), MLM_FORMAT, MPFROMLONG( format ), 0 );
}

/* Sets the multi-line entry field text.
 */

void PMMLE::text( const char* text )
{
  int     size  = strlen( text );
  IPT     begin = 0;
  MRESULT rc;

  m_mutex.request();

  WinSendMsg( handle(), MLM_DELETE, 0,
              WinSendMsg( handle(), MLM_QUERYTEXTLENGTH, 0, 0 ));

  if(( rc = WinSendMsg( handle(), MLM_SETIMPORTEXPORT, MPFROMP( text ), MPFROMLONG( size ))) != FALSE ) {
    WinSendMsg( handle(), MLM_IMPORT, MPFROMP( &begin ), MPFROMLONG( size ));
  }

  m_mutex.release();

  if( !rc ) {
    PM_THROW_GUIERROR();
  }
}

/* Returns the multi-line entry field text.
 */

char* PMMLE::text( char* result, int size ) const
{
  IPT     begin = 0;
  ULONG   success;
  MRESULT rc;

  m_mutex.request();

  if(( rc = WinSendMsg( handle(), MLM_SETIMPORTEXPORT, MPFROMP( result ), MPFROMLONG( size ))) != FALSE ) {
    success = LONGFROMMR( WinSendMsg( handle(), MLM_EXPORT,
                                      MPFROMP( &begin ), MPFROMP( &size )));
    result[success] = 0;
  }

  m_mutex.release();

  if( !rc ) {
    PM_THROW_GUIERROR();
  }

  return result;
}

/* Returns the length of the multi-line entry field text.
 */

int PMMLE::text_len( IPT ipt_start, ULONG chars ) const
{
  return (int)WinSendMsg( handle(), MLM_QUERYFORMATTEXTLENGTH,
                                    MPFROMLONG( ipt_start ), MPFROMLONG( chars ));
}

/* Returns the length of the multi-line entry field text.
 */

int PMMLE::text_len() const {
  return text_len( 0, 0xFFFFFFFFUL );
}

/* Sets a selection.
 *
 * Sets the anchor and cursor points. The screen display is updated appropriately,
 * ensuring that the cursor point is visible (which may involve scrolling). Note
 * that the text cursor and inversion are not displayed if the MLE window does
 * not have the input focus. A negative value for a point leaves that point alone.
 */

void PMMLE::select( IPT ipt_anchor, IPT ipt_cursor )
{
  if( !send( MLM_SETSEL, MPFROMLONG( ipt_anchor ), MPFROMLONG( ipt_cursor ))) {
    PM_THROW_GUIERROR();
  }
}

/* Selects all multi-line entry field text.
 */

void PMMLE::select_all() {
  select( 0, text_len());
}

/* Deletes the text that forms the current selection.
 */

void PMMLE::clear() {
  send( MLM_CLEAR, 0, 0 );
}

/* Copies the current selection to the clipboard.
 */

void PMMLE::copy()
{
  int    size = text_len();
  APIRET rc;
  char*  data;

  if( !WinOpenClipbrd( PMGUI::hab())) {
    PM_THROW_GUIERROR();
  }

  rc = DosAllocSharedMem((void**)&data, NULL, size + 1,
                         PAG_WRITE | OBJ_GIVEABLE | PAG_COMMIT );
  if( rc != NO_ERROR ) {
    PM_THROW_DOSERROR( rc );
  }

  text( data, size + 1 );

  if( !WinEmptyClipbrd( PMGUI::hab())) {
    PM_THROW_GUIERROR();
  }
  if( !WinSetClipbrdData( PMGUI::hab(), (ULONG)data, CF_TEXT, CFI_POINTER )) {
    PM_THROW_GUIERROR();
  }
  if( !WinCloseClipbrd( PMGUI::hab())) {
    PM_THROW_GUIERROR();
  }
}

/* Copies the text that forms the current selection to the
 * clipboard, and then deletes it.
 */

void PMMLE::cut() {
  send( MLM_CUT, 0, 0 );
}

/* Replaces the text that forms the current selection with
 * text from the clipboard.
 */

void PMMLE::paste() {
  send( MLM_PASTE, 0, 0 );
}

