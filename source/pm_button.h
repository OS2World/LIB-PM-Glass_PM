/*
 * Copyright (C) 2001-2009 Dmitry A.Steklenev
 *
 * $Id: pm_button.h,v 1.3 2011/03/11 12:59:31 glass Exp $
 */

#ifndef PM_BUTTON_H
#define PM_BUTTON_H

#include "pm_os2.h"
#include "pm_window.h"

/**
 * Push button control window class.
 *
 * The PMButton class creates and manages push button control
 * windows.
 *
 * You can construct and destruct objects of this class.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.3 $
 */

class PMButton : public PMWindow
{
  public:

    /**
     * Wraps the push button control window object around
     * an existing presentation window handle.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     */

    PMButton( HWND handle );

    /**
     * Wraps the push button control window object around
     * an existing child window with the specified identifier.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     *
     * @param hparent     Specifies the parent-window handle.
     * @param id          Specifies the identity of the child window.
     */

    PMButton( HWND hparent, SHORT id );

    /**
     * Constructs the push button control window.
     *
     * @param id          Specifies the window identifier.
     * @param text        Specifies the window text.
     * @param hparent     Specifies the parent-window handle.
     * @param x,y,cx,cy   Specifies the window shape.
     * @param style       Specifies the window style:
     *
     * <dl>
     * <dt><i>BS_PUSHBUTTON    </i><dd>A pushbutton is a box that contains a string. When a button
     *                                 is pushed, by clicking the pointing device on it or pressing
     *                                 the spacebar when it is active, the parent window is notified.
     * <dt><i>BS_NOTEBOOKBUTTON</i><dd>A notebook button is identical to a pushbutton except that
     *                                 when it is created as a child of a notebook page it becomes a
     *                                 button in the common button area of the notebook page. If
     *                                 the button is not in a notebook page it will be indistinguishable
     *                                 from a pushbutton.
     * <dt><i>BS_AUTOSIZE      </i><dd>Creates a button that is sized
     *                                 automatically to ensure that the contents
     *                                 fit.  Note:  The cx or cy parameter of
     *                                 must be specified as -1 to implement the
     *                                 autosize feature.
     * <dt><i>BS_BITMAP        </i><dd>Places a bit map instead of text on the push
     *                                 button control.
     * <dt><i>BS_DEFAULT       </i><dd>A BS_DEFAULT pushbutton is one with a thick border box.
     *                                 It has the same properties as a pushbutton. In addition,
     *                                 the user may press a BS_DEFAULT pushbutton by pressing
     *                                 the RETURN or ENTER key.
     * <dt><i>BS_HELP          </i><dd>The button posts a WM_HELP message rather than a WM_COMMAND
     *                                 message. If both BS_HELP and BS_SYSCOMMAND are set, BS_HELP
     *                                 takes precedence.
     * <dt><i>BS_ICON          </i><dd>Places an icon instead of text on the push
     *                                 button control.
     * <dt><i>BS_MINIICON      </i><dd>This enables miniicons (half the size of normal icons) to
     *                                 be placed on the push button control.
     * <dt><i>BS_NOBORDER      </i><dd>The pushbutton is displayed without a border drawn around
     *                                 it. There is no other change in the pushbutton's operation.
     * <dt><i>BS_NOPOINTERFOCUS</i><dd>Buttons with this style do not set the focus to themselves
     *                                 when clicked with the pointing device. This enables the
     *                                 cursor to stay on a control for which information is required,
     *                                 rather than moving to the button. This style has no effect on
     *                                 keyboard interaction. The tab key can still be used as usual
     *                                 to move the focus to the button.
     * <dt><i>BS_SYSCOMMAND    </i><dd>The button posts a WM_SYSCOMMAND message rather than a
     *                                 WM_COMMAND message.
     * </dl>
     *
     * @see PMWindow::PMWindow 2
     */

    PMButton( SHORT id, const char* text, HWND hparent, LONG x, LONG y, LONG cx, LONG cy, ULONG style );
};

#endif
