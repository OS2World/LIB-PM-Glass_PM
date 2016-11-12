/*
 * Copyright (C) 2011 Dmitry A.Steklenev
 * Copyright (C) 2011 eCo Software
 */

#ifndef PM_GROUPBOX_H
#define PM_GROUPBOX_H

#include "pm_os2.h"
#include "pm_window.h"

/**
 * Group box control window class.
 *
 * The PMGroupBox class creates and manages group box control windows.
 * For example, you can group a set of related radio buttons
 * within a group box in order to confine their mutually exclusive behavior.
 * This allows the user to select a radio button outside the group box
 * without deselecting one that is inside it.
 *
 * You can construct and destruct objects of this class.
 *
 * @author  Dmitry A.Steklenev
 */

class PMGroupBox : public PMWindow
{
  public:

    /**
     * Wraps the group box control window object around
     * an existing presentation window handle.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     */

    PMGroupBox( HWND handle );

    /**
     * Wraps the group box control window object around
     * an existing child window with the specified identity.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     *
     * @param hparent     Specifies the parent-window handle.
     * @param id          Specifies the identity of the child window.
     */

    PMGroupBox( HWND hparent, SHORT id );

    /**
     * Constructs the group box control window.
     *
     * @param id          Specifies the window identifier.
     * @param text        Specifies the window text.
     * @param hparent     Specifies the parent-window handle.
     * @param x,y,cx,cy   Specifies the window shape.
     * @param style       Specifies the window style.
     *
     * @see PMWindow::PMWindow   2
     */

    PMGroupBox( SHORT id, const char* text, HWND hparent, LONG x, LONG y, LONG cx, LONG cy, ULONG style );
};

#endif
