/*
 * Copyright (C) 2001-2008 Dmitry A.Steklenev
 *
 * $Id: pm_checkbox.cpp,v 1.5 2011/03/11 12:59:31 glass Exp $
 */

#include "pm_checkbox.h"

/* Wraps the check box control window object around
 * an existing presentation window handle.
 */

PMCheckBox::PMCheckBox( HWND handle )
: PMWindow( handle )
{}

/* Wraps the check box control window object around
 * an existing child window with the specified identifier.
 */

PMCheckBox::PMCheckBox( HWND hparent, SHORT id )
: PMWindow( hparent, id )
{}

/* Constructs the check box control window.
 */

PMCheckBox::PMCheckBox( SHORT id, const char* text, HWND hparent,
                        LONG x, LONG y, LONG cx, LONG cy, ULONG style )

: PMWindow( WC_BUTTON, id, text, hparent, hparent,
            x, y, cx, cy, style, NULL )
{}

/* Sets the checked state of a check box control.
 */

void PMCheckBox::check( USHORT state ) {
  WinSendMsg( handle(), BM_SETCHECK, MPFROM2SHORT( state, 0 ), 0 );
}

/* Returns the checked state of a check box control.
 */

USHORT PMCheckBox::check() const {
  return (USHORT)WinSendMsg( handle(), BM_QUERYCHECK, 0, 0 );
}

