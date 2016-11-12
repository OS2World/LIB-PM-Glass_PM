/*
 * Copyright (C) 2001-2008 Dmitry A.Steklenev
 *
 * $Id: pm_combobox.h,v 1.3 2011/03/11 12:59:31 glass Exp $
 */

#ifndef PM_COMBOBOX_H
#define PM_COMBOBOX_H

#include "pm_os2.h"
#include "pm_listbox.h"

/**
 * Combination box control window class.
 *
 * The PMComboBox class creates and manages combination box control
 * windows. The PMComboBox class combines an entry field and a
 * list box to form one control containing the features of both.
 *
 * You can construct and destruct objects of this class.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.3 $
 */

class PMComboBox : public PMListBox
{
  public:

    /**
     * Wraps the combination box control window object around
     * an existing presentation window handle.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     */

    PMComboBox( HWND handle );

    /**
     * Wraps the combination box control window object around
     * an existing child window with the specified identifier.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     *
     * @param hparent     Specifies the parent-window handle.
     * @param id          Specifies the identity of the child window.
     */

    PMComboBox( HWND hparent, SHORT id );

    /**
     * Constructs the combination box control window.
     *
     * @param id          Specifies the window identifier.
     * @param hparent     Specifies the parent-window handle.
     * @param x,y,cx,cy   Specifies the window shape.
     * @param style       Specifies the window style:
     *
     * <dl>
     * <dt><i>CBS_SIMPLE      </i><dd>Both the entry field control and the
     *                                list box control are visible.
     * <dt><i>CBS_DROPDOWN    </i><dd>Inherits all the properties of a
     *                                combination-box control with a style
     *                                of CBS_SIMPLE and, in addition, the
     *                                list box control is hidden until
     *                                the user requests that it should
     *                                be displayed.
     * <dt><i>CBS_DROPDOWNLIST</i><dd>In which the entry field control is
     *                                replaced by a static control, that
     *                                displays the current selection from
     *                                the list box control. The user must
     *                                explicitly cause the display of the
     *                                list box control in order to make
     *                                alternative selections in the list
     *                                box.
     * </dl>
     *
     * @see PMListBox::PMListBox 2
     * @see PMWindow::PMWindow   2
     */

    PMComboBox( SHORT id, HWND hparent, LONG x, LONG y, LONG cx, LONG cy, ULONG style );
};

#endif
