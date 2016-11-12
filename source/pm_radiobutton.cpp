/*
 * Copyright (C) 2001-2011 Dmitry A.Steklenev
 *
 * $Id: pm_radiobutton.cpp,v 1.5 2011/03/11 12:59:32 glass Exp $
 */

#include "pm_radiobutton.h"

/* Wraps the radio button control window object around
 * an existing presentation window handle.
 */

PMRadioButton::PMRadioButton( HWND handle )
: PMWindow( handle )
{}

/* Wraps the radio button control window object around
 * an existing child window with the specified identity.
 */

PMRadioButton::PMRadioButton( HWND hparent, SHORT id )
: PMWindow( hparent, id )
{}

/* Constructs the radio button control window.
 */

PMRadioButton::PMRadioButton( SHORT id, const char* text, HWND hparent,
                              LONG x, LONG y, LONG cx, LONG cy, ULONG style )

: PMWindow( WC_BUTTON, id, text, hparent, hparent,
            x, y, cx, cy, style, NULL )
{}

/* Selects the radio button.
 */

void PMRadioButton::select()
{
  WinSendMsg( handle(), BM_SETCHECK, MPFROM2SHORT( 1, 0 ), 0 );
  WinSendMsg( owner(),  WM_CONTROL,  MPFROM2SHORT( id(), BN_CLICKED ), MPFROMHWND( handle()));
}

/* Selects the radio button.
 */

void PMRadioButton::select( int index )
{
  HWND howner = owner();
  HWND hwnd   = WinEnumDlgItem( howner, handle(), EDI_FIRSTGROUPITEM );

  while( index-- ) {
    hwnd = WinEnumDlgItem( howner, hwnd, EDI_NEXTGROUPITEM );
  }

  if( hwnd ) {
    PMRadioButton( hwnd ).select();
  }
}

/* Returns the selected button index.
 *
 * Returns the 0-based index of the selected radio button in a group.
 * If no radio button is selected, -1 is returned.
 */

int PMRadioButton::selected() const {
  return LONGFROMMR( WinSendMsg( handle(), BM_QUERYCHECKINDEX, 0, 0 ));
}

