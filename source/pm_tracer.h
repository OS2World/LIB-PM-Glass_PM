/*
 * Copyright (C) 2010 Dmitry A.Steklenev
 *
 * $Id: pm_tracer.h,v 1.4 2011/03/11 12:59:33 glass Exp $
 */

#ifndef PM_TRACER_H
#define PM_TRACER_H

#include "pm_os2.h"
#include "pm_window.h"
#include "pm_initptracer.h"

/**
 * Log messages collector window class.
 *
 * Primary purpose of the PMTracer control is to collecting and displaying
 * various log messages. The log collector control can be easy used during
 * PTOpen, PTGetString and PTClose sequence.
 *
 * The maximum number of messages permitted in a log collector is 32767. If
 * more messages are added then oldest messages are removed from control.
 *
 * You can construct and destruct objects of this class.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.4 $
 */

class PMTracer : public PMWindow
{
  public:

    /**
     * Wraps the log messages collector window object around
     * an existing presentation window handle.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     */

    PMTracer( HWND handle );

    /**
     * Wraps the Log messages collector window object around
     * an existing child window with the specified identifier.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     *
     * @param hparent     Specifies the parent-window handle.
     * @param id          Specifies the identity of the child window.
     */

    PMTracer( HWND hparent, SHORT id );

    /**
     * Constructs the Log messages collector window.
     *
     * @param id          Specifies the window identifier.
     * @param hparent     Specifies the parent-window handle.
     * @param x,y,cx,cy   Specifies the window shape.
     * @param style       Specifies the window style.
     *
     * @see PMWindow::PMWindow 2
     */

    PMTracer( SHORT id, HWND hparent, LONG x, LONG y, LONG cx, LONG cy, ULONG style );

    /**
     * Adds specified message to the log collector.
     *
     * @param message   Address of the message string.
     * @param options   Flags used to specify a method of message addition:
     * <dl>
     * <dt><i>PTA_REPLACE_LAST</i><dd>Replace the previously added message.
     * </dl>
     */

    virtual void trace( const char* message, int options );

    /** Deletes all the messages in the log collector. */
    virtual void clear();
    /** Sets the selection state of all messages in a log collector. */
    virtual void select_all();
    /** Copies all selected messages into the clipboard. */
    virtual void copy();
};

#endif
