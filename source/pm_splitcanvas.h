/* Copyright (C) 2008-2011 Dmitry A.Steklenev
 *
 * $Id: pm_splitcanvas.h,v 1.10 2011/07/01 10:59:25 glass Exp $
 */

#ifndef  PM_SPLITCANVAS_H
#define  PM_SPLITCANVAS_H

#include "pm_os2.h"
#include "pm_window.h"
#include "pm_titlebar.h"

#ifndef  __ccdoc__
#define  SP_VERTICAL    0x0000
#define  SP_HORIZONTAL  0x0001
#define  SP_TITLEBAR    0x0002
#define  SP_2D          0x0004
#define  SP_BORDER1     0x0008
#define  SP_BORDER2     0x0010
#endif

/**
 * Split canvas class.
 *
 * The PMSplitCanvas class provides a way to split a window
 * into two window panes.
 *
 * By dragging the split bar, a user can dynamically change
 * the visible amount of each pane. The split canvas manages
 * the position and size of its child windows, so that
 * together with the split bar, they occupy the entire area
 * of the canvas.
 *
 * You can construct and destruct objects of this class.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.10 $
 */

class PMSplitCanvas : public PMWindow {

  public:

    /**
     * Constructs the split canvas window.
     *
     * @param id            Specifies the window identifier.
     * @param text          Specifies the window text.
     * @param hparent       Specifies the parent-window handle.
     * @param x,y,cx,cy     Specifies the window shape.
     * @param style         Specifies the window style:
     *
     * <dl>
     * <dt><i>SP_VERTICAL  </i><dd>Draws split bars vertically, placing the panes
     *                             left to right. This style is the default.
     * <dt><i>SP_HORIZONTAL</i><dd>Draws split bars horizontally, placing the panes
     *                             top to bottom.
     * <dt><i>SP_TITLEBAR  </i><dd>Title bar.
     * <dt><i>SP_2D        </i><dd>Draw a flat splitter bar.
     * <dt><i>SP_BORDER1   </i><dd>Draws a border inside 1st split canvas pane.
     * <dt><i>SP_BORDER2   </i><dd>Draws a border inside 2nd split canvas pane.
     * </dl>
     *
     * @see PMWindow::PMWindow 2
     */

    PMSplitCanvas( SHORT id, const char* text, HWND hparent, LONG x, LONG y, LONG cx, LONG cy, ULONG style );

    /**
     * Destructs the split canvas window.
     */

    virtual ~PMSplitCanvas();

    /**
     * Sets the window used as the split canvas pane area.
     *
     * @param hwnd  Specifies the window handle.
     * @param id    The zero-based index of the split canvas pane.
     */

    virtual void pane( HWND hwnd, SHORT id );

    /**
     * Returns the window used as the split canvas pane area.
     *
     * @param id    The zero-based index of the split canvas pane.
     */

    virtual HWND pane( SHORT id ) const;

    /** Sets the percentage of the first split canvas pane. */
    virtual void percentage( unsigned int percentage );
    /** Returns the percentage of the first split canvas pane. */
    virtual unsigned int percentage() const;

    /**
     * Sets the orientation of the split bars.
     *
     * @param style Specifies the orientation:
     *
     * <dl>
     * <dt><i>SP_VERTICAL  </i><dd>Draws split bars vertically, placing the panes
     *                             left to right. This style is the default.
     * <dt><i>SP_HORIZONTAL</i><dd>Draws split bars horizontally, placing the panes
     *                             top to bottom.
     * </dl>
     */

    virtual void orientation( int style );

    /** Returns the orientation of the split bars. */
    virtual int  orientation() const;
    /** Makes the canvas title bar visible. */
    virtual void show_title( BOOL state = TRUE );
    /** Makes the canvas title bar invisible. */
    virtual void hide_title();

    /** Sets the the split canvas title text. */
    virtual void text( const char* text );

    /**
     * Returns the split canvas title text.
     *
     * @param result  A buffer in which the text is returned.
     * @param size    This is the size of the buffer specified by the <i>result</i>
     *                parameter. If the call is successful, this is overwritten
     *                with the number of bytes copied into the buffer.
     */

    virtual char* text( char* result, int size ) const;

  protected:

    /**
     * Dispatch system native events.
     *
     * This method is called when a system native window
     * event occurs.
     */

    virtual MRESULT dispatch( ULONG msg, MPARAM mp1, MPARAM mp2 );

  private:

    PMTitleBar  m_titlebar;
    PMWindow*   m_panes[2];
    PMRect      m_rects[2];
    float       m_percentage;
    PMRect      m_splitbar;
    ULONG       m_style;
    BOOL        m_moved;
    float       m_drag_percentage;
    SHORT       m_drag_start;
    SHORT       m_drag_x;
    SHORT       m_drag_y;
    LONG        m_bar_cx;
    LONG        m_bar_cy;

    /** Reformats the split canvas panes. */
    void win_format();
    /** Identify the type of control. */
    LONG win_pdlgcode( SHORT id );
    /** Returns the pane window which user can tab. */
    HWND win_penum( SHORT code, HWND hwnd = NULLHANDLE );

    /** Draws the 3D border. */
    void draw_3d_border( HPS ps, PMRect* rect, LONG thickness );
};

/* Returns the percentage of the first split canvas pane. */
inline unsigned int PMSplitCanvas::percentage() const {
  return m_percentage;
}

#endif
