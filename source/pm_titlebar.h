/*
 * Copyright (C) 2009 Dmitry A.Steklenev
 *
 * $Id: pm_titlebar.h,v 1.3 2011/03/11 12:59:33 glass Exp $
 */

#ifndef PM_TITLEBAR_H
#define PM_TITLEBAR_H

#include "pm_os2.h"
#include "pm_window.h"

/**
 * Application title bar window class.
 *
 * Displays the window title or caption and lets
 * the user move the window's owner.
 *
 * You can construct and destruct objects of this class.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.3 $
 */

class PMTitleBar : public PMWindow
{
  public:

    /**
     * Wraps the title bar window object
     * around an existing presentation window handle.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     */

    PMTitleBar( HWND handle );

    /**
     * Wraps the title bar window object around
     * an existing child window with the specified identity.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     *
     * @param hparent     Specifies the parent-window handle.
     * @param id          Specifies the identity of the child window.
     */

    PMTitleBar( HWND hparent, SHORT id );

    /**
     * Constructs the title bar window.
     *
     * @param id          Specifies the window identifier.
     * @param text        Specifies the window text.
     * @param hparent     Specifies the parent-window handle.
     * @param x,y,cx,cy   Specifies the window shape.
     * @param style       Specifies the window style.
     *
     * @see PMWindow::PMWindow 2
     */

    PMTitleBar( SHORT id, const char* text, HWND hparent, LONG x, LONG y, LONG cx, LONG cy, ULONG style );

    /** Highlights or unhighlights a title-bar control. */
    virtual void hilite( BOOL highlight = TRUE );
    /** Returns the highlighting state of a title-bar control. */
    virtual BOOL is_hilited() const;

  protected:

    /**
     * Dispatch system native events.
     *
     * This method is called when a system native window
     * event occurs.
     */

    virtual MRESULT dispatch( ULONG msg, MPARAM mp1, MPARAM mp2 );
};

#endif
