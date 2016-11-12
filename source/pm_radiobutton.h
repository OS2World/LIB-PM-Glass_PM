/*
 * Copyright (C) 2001-2008 Dmitry A.Steklenev
 *
 * $Id: pm_radiobutton.h,v 1.4 2011/03/11 12:59:32 glass Exp $
 */

#ifndef PM_RADIOBUTTON_H
#define PM_RADIOBUTTON_H

#include "pm_os2.h"
#include "pm_window.h"

/**
 * Radio button control window class.
 *
 * The PMRadioButton class creates and manages radio button control
 * windows. A radio button is a circle or a diamond with associated
 * text representing a choice. When a user selects the choice, the radio
 * button is filled to indicate that the choice is selected. The
 * user can clear the radio button by selecting another radio button.
 * Radio buttons are mutually exclusive.
 *
 * You can construct and destruct objects of this class.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.4 $
 */

class PMRadioButton : public PMWindow
{
  public:

    /**
     * Wraps the radio button control window object around
     * an existing presentation window handle.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     */

    PMRadioButton( HWND handle );

    /**
     * Wraps the radio button control window object around
     * an existing child window with the specified identity.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     *
     * @param hparent     Specifies the parent-window handle.
     * @param id          Specifies the identity of the child window.
     */

    PMRadioButton( HWND hparent, SHORT id );

    /**
     * Constructs the radio button control window.
     *
     * @param id          Specifies the window identifier.
     * @param text        Specifies the window text.
     * @param hparent     Specifies the parent-window handle.
     * @param x,y,cx,cy   Specifies the window shape.
     * @param style       Specifies the window style:
     *
     * <dl>
     * <dt><i>BS_AUTORADIOBUTTON</i><dd>Creates an auto-radio button (see also
     *                                  BS_RADIOBUTTON). When the user selects an
     *                                  auto-radio button, the system
     *                                  automatically selects the button and
     *                                  removes the selection from the other
     *                                  auto-radio buttons in the group.
     * <dt><i>BS_AUTOSIZE       </i><dd>Creates a button that is sized
     *                                  automatically to ensure that the contents
     *                                  fit.  Note:  The cx or cy parameter of
     *                                  must be specified as -1 to implement the
     *                                  autosize feature.
     * <dt><i>BS_NOCURSORSELECT </i><dd>Creates an auto-radio button that will
     *                                  not be selected automatically when the
     *                                  user moves the cursor to the button using
     *                                  the cursor-movement keys. This style is
     *                                  valid only in combination with the
     *                                  BS_AUTORADIOBUTTON style or the
     *                                  AUTORADIOBUTTON statement in a
     *                                  resource-definition file.
     * <dt><i>BS_RADIOBUTTON    </i><dd>Creates a radio button-a small circle
     *                                  that has text displayed to its right.
     *                                  Radio buttons usually are used in groups
     *                                  of related, but exclusive, choices. When
     *                                  the user selects a radio button, the
     *                                  button sends a WM_CONTROL message to its
     *                                  owner window. The user should select the
     *                                  button and remove the selection from the
     *                                  other radio buttons in the group.
     * </dl>
     *
     * @see PMWindow::PMWindow 2
     */

    PMRadioButton( SHORT id, const char* text, HWND hparent, LONG x, LONG y, LONG cx, LONG cy, ULONG style );

    /** Selects the radio button. */
    virtual void select();

    /**
     * Selects the radio button.
     *
     * @param index   The 0-based index of the selected radio button in a group.
     *
     * <b>Note:</b> The index includes all windows that are part of
     * the group, not just radio buttons. To ensure that the index only includes
     * radio buttons, be sure that the group does not contain any other windows.
     */

    virtual void select( int index );

    /**
     * Returns the selected button index.
     *
     * @return      The 0-based index of the selected radio button in a group.
     *              If no radio button is selected, -1 is returned.
     *
     * <b>Note:</b> The index returned includes all windows that are part of
     * the group, not just radio buttons. To ensure that the index only includes
     * radio buttons, be sure that the group does not contain any other windows.
     */

     int selected() const;
};

#endif
