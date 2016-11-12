/*
 * Copyright (C) 2011 Dmitry A.Steklenev
 * Copyright (C) 2011 eCo Software
 */

#include "pm_groupbox.h"

/* Wraps the group box control window object around
 * an existing presentation window handle.
 */

PMGroupBox::PMGroupBox( HWND handle )
: PMWindow( handle )
{}

/* Wraps the group box control window object around
 * an existing child window with the specified identity.
 */

PMGroupBox::PMGroupBox( HWND hparent, SHORT id )
: PMWindow( hparent, id )
{}

/* Constructs the group box control window.
 */

PMGroupBox::PMGroupBox( SHORT id, const char* text, HWND hparent,
                        LONG x, LONG y, LONG cx, LONG cy, ULONG style )

: PMWindow( WC_STATIC, id, text, hparent, hparent,
            x, y, cx, cy, SS_GROUPBOX | style, NULL )
{}

