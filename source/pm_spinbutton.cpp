/*
 * Copyright (C) 2001-2008 Dmitry A.Steklenev
 *
 * $Id: pm_spinbutton.cpp,v 1.4 2011/03/11 12:59:33 glass Exp $
 */

#include "pm_spinbutton.h"

/* Wraps the spin button control window object around
 * an existing presentation window handle.
 */

PMSpinButton::PMSpinButton( HWND handle )
: PMWindow( handle )
{}

/* Wraps the spin button control window object around
 * an existing child window with the specified identity.
 */

PMSpinButton::PMSpinButton( HWND hparent, SHORT id )
: PMWindow( hparent, id )
{}

/* Constructs the spin button control window.
 */

PMSpinButton::PMSpinButton( SHORT id, HWND hparent,
                            LONG x, LONG y, LONG cx, LONG cy, ULONG style )

: PMWindow( WC_SPINBUTTON, id, "", hparent, hparent,
            x, y, cx, cy, style, NULL )
{}

/* Returns the current value of the spin field.
 */

ULONG PMSpinButton::value() const
{
  ULONG x = 0;

  // This method can't throw exception because SPBM_QUERYVALUE return FALSE
  // in case the value entered by user is invalid.
  WinSendMsg( handle(), SPBM_QUERYVALUE,
              MPFROMP( &x ), MPFROM2SHORT( 0, SPBQ_ALWAYSUPDATE ));
  return x;
}

/* Sets the current value of the spin field.
 */

void PMSpinButton::value( ULONG x )
{
  if( !WinSendMsg( handle(), SPBM_SETCURRENTVALUE, MPFROMLONG( x ), 0 )) {
    PM_THROW_GUIERROR();
  }
}

