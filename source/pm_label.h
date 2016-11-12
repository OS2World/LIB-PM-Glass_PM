/*
 * Copyright (C) 2008 Dmitry A.Steklenev
 *
 * $Id: pm_label.h,v 1.3 2011/03/11 12:59:32 glass Exp $
 */

#ifndef PM_LABEL_H
#define PM_LABEL_H

#include "pm_os2.h"
#include "pm_window.h"

/**
 * Static text control window class.
 *
 * The PMLabel class creates and manages static text control windows.
 * Static text controls are simple text fields that do not accept
 * user input. You can use PMLabel to create text prompts and labels.
 *
 * You can construct and destruct objects of this class.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.3 $
 */

class PMLabel : public PMWindow
{
  public:

    /**
     * Wraps the static text control window object around
     * an existing presentation window handle.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     */

    PMLabel( HWND handle );

    /**
     * Wraps the static text control window object around
     * an existing child window with the specified identity.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     *
     * @param hparent     Specifies the parent-window handle.
     * @param id          Specifies the identity of the child window.
     */

    PMLabel( HWND hparent, SHORT id );

    /**
     * Constructs the static text control window.
     *
     * @param id          Specifies the window identifier.
     * @param text        Specifies the window text.
     * @param hparent     Specifies the parent-window handle.
     * @param x,y,cx,cy   Specifies the window shape.
     * @param style       Specifies the window style:
     *
     * <dl>
     * <dt><i>DT_LEFT     </i><dd>Left-justified text.
     * <dt><i>DT_CENTER   </i><dd>Centered text.
     * <dt><i>DT_RIGHT    </i><dd>Right-justified text.
     * <dt><i>DT_TOP      </i><dd>Text is aligned to top of window.
     * <dt><i>DT_VCENTER  </i><dd>Text is aligned vertically in center of window.
     * <dt><i>DT_BOTTOM   </i><dd>Text is aligned to bottom of window.
     * <dt><i>DT_WORDBREAK</i><dd>Text is multi-line with word-wrapping at ends of lines.
     *                            This text drawing style can also be ORed, but only if
     *                            DT_TOP and DT_LEFT are also specified.
     * <dt><i>DT_MNEMONIC </i><dd>If a mnemonic prefix character is encountered, the next
     *                            character is drawn with mnemonic emphasis. .
     * </dl>
     *
     * @see PMWindow::PMWindow   2
     */

    PMLabel( SHORT id, const char* text, HWND hparent, LONG x, LONG y, LONG cx, LONG cy, ULONG style );
};

#endif
