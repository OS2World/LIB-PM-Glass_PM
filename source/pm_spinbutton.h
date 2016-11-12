/*
 * Copyright (C) 2001-2008 Dmitry A.Steklenev
 *
 * $Id: pm_spinbutton.h,v 1.4 2011/03/11 12:59:33 glass Exp $
 */

#ifndef PM_SPINBUTTON_H
#define PM_SPINBUTTON_H

#include "pm_os2.h"
#include "pm_window.h"

/**
 * Spin button control window class.
 *
 * The PMSpinButton class creates and manages spin button control windows.
 * A spin button consists of at least one spin field that is a single-line
 * entry (SLE) field, and up and down arrows that are stacked on top
 * of one another. These arrows are positioned to the right of the SLE
 * field.
 *
 * You can construct and destruct objects of this class.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.4 $
 */

class PMSpinButton : public PMWindow
{
  public:

    /**
     * Wraps the spin button control window object around
     * an existing presentation window handle.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     */

    PMSpinButton( HWND handle );

    /**
     * Wraps the spin button control window object around
     * an existing child window with the specified identity.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     *
     * @param hparent     Specifies the parent-window handle.
     * @param id          Specifies the identity of the child window.
     */

    PMSpinButton( HWND hparent, SHORT id );

    /**
     * Constructs the spin button control window.
     *
     * @param id          Specifies the window identifier.
     * @param hparent     Specifies the parent-window handle.
     * @param x,y,cx,cy   Specifies the window shape.
     * @param style       Specifies the window style:
     *
     * <dl>
     * <dt><i>SPBS_MASTER       </i><dd>The spin button component consists of at
     *                                  least one single line entry field (SLE),
     *                                  or spin field, and two arrows, the Up Arrow
     *                                  and the Down Arrow. When a spin button contains
     *                                  more than one spin field, the master
     *                                  component contains the spin arrows. If the
     *                                  component contains only one spin field, it
     *                                  should be a master.
     * <dt><i>SPBS_SERVANT      </i><dd>You can create a multifield spin button by
     *                                  spinning servants from the master.
     * <dt><i>SPBS_ALLCHARACTERS</i><dd>Any character can be typed in the spin field.
     *                                  This is the default.
     * <dt><i>SPBS_NUMERICONLY  </i><dd>Only the digits 0-9 and the minus sign (-) can
     *                                  be typed in the spin field.
     * <dt><i>SPBS_READONLY     </i><dd>Nothing can be typed in the spin field.
     * <dt><i>SPBS_JUSTLEFT     </i><dd>Left-justify the text. This is the default.
     * <dt><i>SPBS_JUSTRIGHT    </i><dd>Right-justify the text.
     * <dt><i>SPBS_JUSTCENTER   </i><dd>Center the text.
     * <dt><i>SPBS_NOBORDER     </i><dd>Suppresses drawing a border.
     * <dt><i>SPBS_FASTSPIN     </i><dd>Enables the spin button to increase the spin
     *                                  speed with time. The speed doubles every two
     *                                  seconds.
     * <dt><i>SPBS_PADWITHZEROS </i><dd>The output number is padded at the front between
     *                                  the first non-zero digit and the field width, or
     *                                  11 characters, whichever is the lesser. The
     *                                  negative sign, if there is one, is retained. The
     *                                  maximum number of characters required to display
     *                                  a LONG number is 11.
     * </dl>
     *
     * @see PMWindow::PMWindow 2
     */

    PMSpinButton( SHORT id, HWND hparent, LONG x, LONG y, LONG cx, LONG cy, ULONG style );

    /** Returns the current value of the spin field. */
    virtual ULONG value() const;
    /** Sets the current value of the spin field. */
    virtual void value( ULONG x );
};

#endif
