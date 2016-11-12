/* Copyright (C) 2001-2008 Dmitry A.Steklenev
 *
 * $Id: pm_notebook.h,v 1.6 2011/07/04 13:41:42 glass Exp $
 */

#ifndef PM_NOTEBOOK_H
#define PM_NOTEBOOK_H

#include "pm_os2.h"
#include "pm_window.h"

/**
 * Notebook control window class.
 *
 * A notebook control is a visual component that organizes
 * information on individual pages so that a user can find
 * and display that information quickly and easily.
 *
 * You can construct and destruct objects of this class.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.6 $
 */

class PMNoteBook : public PMWindow {

  public:

    /**
     * Wraps the notebook control window object around
     * an existing presentation window handle.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     */

    PMNoteBook( HWND handle );

    /**
     * Wraps the notebook control window object around
     * an existing child window with the specified identity.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     *
     * @param hparent     Specifies the parent-window handle.
     * @param id          Specifies the identity of the child window.
     */

    PMNoteBook( HWND hparent, SHORT id );

    /**
     * Constructs the notebook control window.
     *
     * @param id          Specifies the window identifier.
     * @param hparent     Specifies the parent-window handle.
     * @param x,y,cx,cy   Specifies the window shape.
     * @param style       Specifies the window style:
     *
     * <dl>
     * <dt><i>BKS_SOLIDBIND       </i><dd>Paints a solid binding on the notebook.
     *                                    This is the default.
     * <dt><i>BKS_SPIRALBIND      </i><dd>Paints a spiral binding on the notebook.
     * <dt><i>BKS_BACKPAGESBR     </i><dd>Paints back pages on the notebook's
     *                                    bottom and right sides. This is the default.
     * <dt><i>BKS_BACKPAGESBL     </i><dd>Paints back pages on the notebook's bottom and left sides.
     * <dt><i>BKS_BACKPAGESTR     </i><dd>Paints back pages on the notebook's top and right sides.
     * <dt><i>BKS_BACKPAGESTL     </i><dd>Paints back pages on the notebook's top and left sides.
     * <dt><i>BKS_MAJORTABRIGHT   </i><dd>Places major tabs on the notebook's right edge.
     * <dt><i>BKS_MAJORTABLEFT    </i><dd>Places major tabs on the notebook's left edge.
     * <dt><i>BKS_MAJORTABTOP     </i><dd>Places major tabs on the notebook's top edge.
     * <dt><i>BKS_MAJORTABBOTTOM  </i><dd>Places major tabs on the notebook's bottom edge.
     * <dt><i>BKS_SQUARETABS      </i><dd>Draws tabs with square edges. This is the default.
     * <dt><i>BKS_ROUNDEDTABS     </i><dd>Draws tabs with rounded edges.
     * <dt><i>BKS_POLYGONTABS     </i><dd>Draws tabs with polygon edges.
     * <dt><i>BKS_STATUSTEXTLEFT  </i><dd>Left-justifies status line text. This is the default.
     * <dt><i>BKS_STATUSTEXTRIGHT </i><dd>Right-justifies status line text.
     * <dt><i>BKS_STATUSTEXTCENTER</i><dd>Centers status line text.
     * <dt><i>BKS_TABTEXTCENTER   </i><dd>Centers tab text. This is the default.
     * <dt><i>BKS_TABTEXTLEFT     </i><dd>Left-justifies tab text.
     * <dt><i>BKS_TABTEXTRIGHT    </i><dd>Right-justifies tab text.
     * <dt><i>BKS_TABBEDDIALOG    </i><dd>Indicates a new style notebook.
     * <dt><i>BKS_BUTTONAREA      </i><dd>Creates a common button area in a new style notebook.
     * </dl>
     *
     * @see PMWindow::PMWindow 2
     */

    PMNoteBook( SHORT id, HWND hparent, LONG x, LONG y, LONG cx, LONG cy, ULONG style );

    /**
     * Inserts the specified page into the notebook data list.
     *
     * @param hpage       The handle of the application page window that is
     *                    to be associated with the notebook page.
     * @param caption     Pointer to a text string that ends with a null character.
     * @param order       BKA_FIRST - insert page at the front of the notebook.
     *                    BKA_LAST  - insert page at the end of the notebook.
     */

    virtual void insert( HWND hpage, const char* caption, SHORT order = BKA_LAST );

    /**
     * Brings the specified page to the top of the notebook.
     *
     * @param pos         The page identifier that is to become the top page.
     */

    virtual void turn_to( int pos );

    /**
     * Translates the notebook window text and all the pages text
     * using for this purpose the current instance of the messages
     * management object.
     */

    virtual void translate();

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
