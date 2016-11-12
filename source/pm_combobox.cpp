/*
 * Copyright (C) 2001-2008 Dmitry A.Steklenev
 *
 * $Id: pm_combobox.cpp,v 1.3 2011/03/11 12:59:31 glass Exp $
 */

#include "pm_combobox.h"

/* Wraps the combination box control window object around
 * an existing presentation window handle.
 */

PMComboBox::PMComboBox( HWND handle )
: PMListBox( handle )
{}

/* Wraps the combination box control window object around
 * an existing child window with the specified identifier.
 */

PMComboBox::PMComboBox( HWND hparent, SHORT id )
: PMListBox( hparent, id )
{}

/* Constructs the combination box control window.
 */

PMComboBox::PMComboBox( SHORT id, HWND hparent,
                        LONG x, LONG y, LONG cx, LONG cy, ULONG style )

: PMListBox( WC_COMBOBOX, id, "", hparent, hparent,
             x, y, cx, cy, style, NULL )
{}

