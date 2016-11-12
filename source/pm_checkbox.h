/*
 * Copyright (C) 2001-2008 Dmitry A.Steklenev
 *
 * $Id: pm_checkbox.h,v 1.5 2011/03/11 12:59:31 glass Exp $
 */

#ifndef PM_CHECKBOX_H
#define PM_CHECKBOX_H

#include "pm_os2.h"
#include "pm_window.h"

/**
 * Radio button control window class.
 *
 * The PMCheckBox class creates and manages check box control windows.
 * A check box is a square box with associated text that represents a
 * choice. When a user selects the choice, the check box is filled to
 * indicate that the choice is selected. If the user selects the check
 * box again, the choice is deselected.
 *
 * You can construct and destruct objects of this class.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.5 $
 */

class PMCheckBox : public PMWindow
{
  public:

    /**
     * Wraps the check box control window object around
     * an existing presentation window handle.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     */

    PMCheckBox( HWND handle );

    /**
     * Wraps the check box control window object around
     * an existing child window with the specified identifier.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     *
     * @param hparent     Specifies the parent-window handle.
     * @param id          Specifies the identity of the child window.
     */

    PMCheckBox( HWND hparent, SHORT id );

    /**
     * Constructs the check box control window.
     *
     * @param id          Specifies the window identifier.
     * @param text        Specifies the window text.
     * @param hparent     Specifies the parent-window handle.
     * @param x,y,cx,cy   Specifies the window shape.
     * @param style       Specifies the window style:
     *
     * <dl>
     * <dt><i>BS_3STATE      </i><dd>Creates a three-state check box (see also
     *                               BS_CHECKBOX). When the user selects the
     *                               check box, it sends a WM_CONTROL message
     *                               to the owner window.  The owner should
     *                               set the check box to the appropriate
     *                               state: selected, unselected, or halftone.
     * <dt><i>BS_AUTO3STATE  </i><dd>Creates an auto-three-state check box
     *                               (see also BS_CHECKBOX).  When the user
     *                               selects the check box, the system
     *                               automatically sets the check box to the
     *                               appropriate state: selected, unselected,
     *                               or halftone.
     * <dt><i>BS_AUTOCHECKBOX</i><dd>Creates an auto-check box (see also
     *                               BS_CHECKBOX).  The system automatically
     *                               toggles the check box between the
     *                               selected and unselected states each time
     *                               the user selects the box.
     * <dt><i>BS_AUTOSIZE    </i><dd>Creates a button that is sized
     *                               automatically to ensure that the contents
     *                               fit.  Note:  The cx or cy parameter of
     *                               must be specified as -1 to implement the
     *                               autosize feature.
     * <dt><i>BS_CHECKBOX    </i><dd>Creates a check box-a small square that
     *                               has text displayed to its right.  When
     *                               the user selects a check box, the check
     *                               box sends a WM_CONTROL message to the
     *                               owner window.  The owner window should
     *                               toggle the check box between selected and
     *                               unselected states.
     * </dl>
     *
     * @see PMWindow::PMWindow 2
     */

    PMCheckBox( SHORT id, const char* text, HWND hparent, LONG x, LONG y, LONG cx, LONG cy, ULONG style );

    /**
     * Sets the checked state of a check box control.
     *
     * @param state 0 Display the check box control in the unchecked state.<br>
     *              1 Display the check box control in the checked state.<br>
     *              2 Display a 3-state check box control in the indeterminate state.
     */

    virtual void check( USHORT state );

    /**
     * Returns the checked state of a check box control.
     *
     * @return  0 The check box control is in unchecked state.<br>
     *          1 The check box control is in checked state.<br>
     *          2 The check box control is in indeterminate state.<br>
     */

    virtual USHORT check() const;
};

#endif
