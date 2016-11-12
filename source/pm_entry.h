/*
 * Copyright (C) 2008 Dmitry A.Steklenev
 *
 * $Id: pm_entry.h,v 1.7 2011/03/11 12:59:31 glass Exp $
 */

#ifndef PM_ENTRY_H
#define PM_ENTRY_H

#include "pm_os2.h"
#include "pm_window.h"

/**
 * Entry field control window class.
 *
 * The PMEntry class creates and manages entry field controls.
 * An entry field control is a control window which allows a user
 * to type and edit a single line of text
 *
 * You can construct and destruct objects of this class.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.7 $
 */

class PMEntry : public PMWindow
{
  public:

    /**
     * Wraps the entry field control window object around
     * an existing presentation window handle.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     */

    PMEntry( HWND handle );

    /**
     * Wraps the entry field control window object around
     * an existing child window with the specified identifier.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     *
     * @param hparent     Specifies the parent-window handle.
     * @param id          Specifies the identity of the child window.
     */

    PMEntry( HWND hparent, SHORT id );

    /**
     * Constructs the entry field control window.
     *
     * @param id          Specifies the window identifier.
     * @param text        Specifies the window text.
     * @param hparent     Specifies the parent-window handle.
     * @param x,y,cx,cy   Specifies the window shape.
     * @param style       Specifies the window style:
     *
     * <dl>
     * <dt><i>ES_LEFT      </i><dd>The text in the control is left-justified.
     * <dt><i>ES_RIGHT     </i><dd>The text in the control is right-justified.
     * <dt><i>ES_CENTER    </i><dd>The text in the control is centered.
     * <dt><i>ES_AUTOSIZE  </i><dd>The text will be sized to make sure the contents fit.
     * <dt><i>ES_AUTOSCROLL</i><dd>If the user tries to move off the end of a line,
     *                             the control automatically scrolls one-third the width
     *                             of the window in the appropriate direction.
     * <dt><i>ES_MARGIN    </i><dd>This style can be used to cause a border to be drawn
     *                             around the control, with a margin around the editable text.
     *                             The margin is half a character-width wide and half a
     *                             character-height high.
     * <dt><i>ES_READONLY  </i><dd>This style causes a single line entry field to be created
     *                             in read only state.
     * <dt><i>ES_UNREADABLE</i><dd>This style causes the text to be displayed as an asterisk
     *                             for each character. It can be used for passwords.
     * <dt><i>ES_COMMAND   </i><dd>This style identifies the entry field as a command entry
     *                             field. This information is used by the Help Manager to
     *                             provide command help if the end user requests help for this
     *                             field.
     * <dt><i>ES_AUTOTAB   </i><dd>This style indicates that when the field is filled by
     *                             adding a character to the end of the entry field text, the
     *                             effect of a tab key will be generated. Inserting or
     *                             replacing a character in the middle of the text, however,
     *                             does not result in an autotab.
     * </dl>
     *
     * @see PMWindow::PMWindow   2
     */

    PMEntry( SHORT id, const char* text, HWND hparent, LONG x, LONG y, LONG cx, LONG cy, ULONG style );

    /** Returns the the maximum number of bytes the entry field can contain. */
    virtual USHORT limit() const;
    /** Sets the maximum number of bytes the entry field can contain. */
    virtual void limit( USHORT len );

    /** Deletes the text that forms the current selection. */
    virtual void clear();
    /** Copies the current selection to the clipboard. */
    virtual void copy();

    /**
     * Copies the text that forms the current selection to the
     * clipboard, and then deletes it.
     */

    virtual void cut();

    /**
     * Replaces the text that forms the current selection with
     * text from the clipboard.
     */

    virtual void paste();

    /**
     * Enables or disables the read-only mode on
     * an entry field control.
     */

    virtual void enable_data_update( BOOL state = TRUE );

    /**
     * Prevents inserting or changing characters
     * in the entry field's text.
     */

    virtual void disable_data_update();

    /**
     * If the contents of the entry field can be modified,
     * TRUE is returned.
     */

    virtual BOOL is_writeable() const;
};

#endif
