/*
 * Copyright (C) 2001-2009 Dmitry A.Steklenev
 *
 * $Id: pm_button.cpp,v 1.3 2011/03/11 12:59:31 glass Exp $
 */

#include "pm_button.h"

/* Wraps the push button control window object around
 * an existing presentation window handle.
 */

PMButton::PMButton( HWND handle )
: PMWindow( handle )
{}

/* Wraps the push button control window object around
 * an existing child window with the specified identifier.
 */

PMButton::PMButton( HWND hparent, SHORT id )
: PMWindow( hparent, id )
{}

/* Constructs the push button control window.
 */

PMButton::PMButton( SHORT id, const char* text, HWND hparent,
                    LONG x, LONG y, LONG cx, LONG cy, ULONG style )

: PMWindow( WC_BUTTON, id, text, hparent, hparent,
            x, y, cx, cy, style, NULL )
{}
