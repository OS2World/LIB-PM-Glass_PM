/*
 * Copyright (C) 2001-2011 Dmitry A.Steklenev
 *
 * $Id: pm_mle.h,v 1.7 2011/04/20 11:55:15 glass Exp $
 */

#ifndef PM_MLE_H
#define PM_MLE_H

#include "pm_os2.h"
#include "pm_window.h"
#include "pm_mutex.h"

/**
 * Multi-line entry field control window class.
 *
 * The PMMLE class creates and manages multi-line entry field
 * control windows. A multi-line entry field control is a
 * rectangular window that displays multiple lines of text
 * that the operator can edit. When it has the focus, the
 * cursor marks the current insertion or replacement point.
 *
 * The text is displayed within a rectangular window. Scroll
 * bars appear if requested.
 *
 * You can construct and destruct objects of this class.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.7 $
 */

class PMMLE : public PMWindow
{
  public:

    /**
     * Wraps the multi-line entry field control window object
     * around an existing presentation window handle.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     */

    PMMLE( HWND handle );

    /**
     * Wraps the multi-line entry field control window object around
     * an existing child window with the specified identity.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     *
     * @param hparent     Specifies the parent-window handle.
     * @param id          Specifies the identity of the child window.
     */

    PMMLE( HWND hparent, SHORT id );

    /**
     * Constructs the multi-line entry field control window.
     *
     * @param id          Specifies the window identifier.
     * @param hparent     Specifies the parent-window handle.
     * @param x,y,cx,cy   Specifies the window shape.
     * @param style       Specifies the window style:
     *
     * <dl>
     * <dt><i>MLS_BORDER      </i><dd>Draws a border around the MLE field.
     * <dt><i>MLS_DISABLEUNDO </i><dd>Directs the MLE control not to allow undo actions.
     * <dt><i>MLS_HSCROLL     </i><dd>Adds a horizontal scroll bar to the MLE field.
     * <dt><i>MLS_IGNORETAB   </i><dd>Directs the MLE control to ignore the Tab key.
     *                                It passes the appropriate WM_CHAR to its owner window.
     * <dt><i>MLS_LIMITVSCROLL</i><dd>Displays the last MLE line at the bottom of
     *                                the screen page. When this style is not used,
     *                                the MLE control shows an empty space between the
     *                                last MLE line and the bottom of the screen page.
     * <dt><i>MLS_READONLY    </i><dd>Prevents the MLE field from accepting text from the user.
     * <dt><i>MLS_VSCROLL     </i><dd>Adds a vertical scroll bar to the MLE field.
     * <dt><i>MLS_WORDWRAP    </i><dd>Automatically breaks lines that are longer than the
     *                                width of the MLE field.
     * </dl>
     *
     * @see PMWindow::PMWindow   2
     */

    PMMLE( SHORT id, HWND hparent, LONG x, LONG y, LONG cx, LONG cy, ULONG style );

    /** Sets a new font to be used by the window. */
    virtual void font( const char* font );

    /**
     * Sets the format to be used for text importing and exporting.
     *
     * @param format    Format to be used for import and export:
     *
     * <dl>
     * <dt><i>MLFIE_CFTEXT </i><dd>Text format. Each line ends with a carriage-return/line-feed
     *                             combination. Tab characters separate fields within a line. A
     *                             NULL character signals the end of the data.
     * <dt><i>MLFIE_NOTRANS</i><dd>Default. Uses LF for line delineation, and guarantees that
     *                             any text imported into the MLE in this format can be recovered
     *                             in exactly the same form on export.
     * <dt><i>MLFIE_WINFMT </i><dd>On import, recognizes CR LF as denoting hard line-breaks, and
     *                             ignores the sequence CR CR LF. On export, uses CR LF to denote
     *                             a hard line-break and CR CR LF to denote a soft line-break
     *                             caused by word-wrapping.
     * </dl>
     */

    virtual void text_format( USHORT format );

    /** Sets the multi-line entry field text. */
    virtual void text( const char* text );

    /**
     * Returns the multi-line entry field text.
     *
     * @param result  A buffer in which the text is returned.
     * @param size    This is the size of the buffer specified by the <i>result</i>
     *                parameter. If the call is successful, this is overwritten
     *                with the number of bytes copied into the buffer.
     */

    virtual char* text( char* result, int size ) const;

    /**
     * Returns the length of the multi-line entry field text.
     *
     * @param  ip_start   Insertion point to start from.
     * @param  chars      Number of characters to convert to bytes. Use 0xFFFFFFFFUL
     *                    to convert until end of line.
     *
     * @return The length of a specified range of characters after the current
     *         formatting has been applied.
     */

    virtual int text_len( IPT ipt_start, ULONG chars ) const;

    /**
     * Returns the length of the multi-line entry field text.
     *
     * @return The length of the multi-line entry field text after the current
     *         formatting has been applied.
     */

    virtual int text_len() const;

    /**
     * Sets a selection.
     *
     * Sets the anchor and cursor points. The screen display is updated appropriately,
     * ensuring that the cursor point is visible (which may involve scrolling). Note
     * that the text cursor and inversion are not displayed if the MLE window does
     * not have the input focus. A negative value for a point leaves that point alone.
     *
     * @param ipt_anchor  Insertion point for new anchor point.
     * @param ipt_cursor  Insertion point for new cursor point.
     *
     */

    virtual void select( IPT ipt_anchor, IPT ipt_cursor );

    /** Selects all multi-line entry field text. */
    virtual void select_all();

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

  private:
    mutable PMMutex m_mutex;
};

#endif
