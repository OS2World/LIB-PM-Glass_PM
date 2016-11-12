/* Copyright (C) 2001-2010 Dmitry A.Steklenev
 *
 * $Id: pm_frame.h,v 1.14 2011/12/19 06:36:48 glass Exp $
 */

#ifndef PM_FRAME_H
#define PM_FRAME_H

#include "pm_os2.h"
#include "pm_window.h"

/**
 * Frame window class.
 *
 * A composite window class that can contain child windows
 * of many of the other window classes.
 *
 * The frame's client window is the control corresponding to the
 * rectangular portion of the frame window not occupied by frame
 * extensions and accessory windows that can be added through frame
 * styles (such as the title bar, system menu, and borders). You
 * do not give the client area an initial size because the client
 * area is automatically sized to fill the frame window.
 *
 * You can construct and destruct objects of this class.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.14 $
 */

class PMFrame : public PMWindow {

  public:

    /**
     * Wraps the frame window object around an existing
     * presentation window handle.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     */

    PMFrame( HWND handle );

    /**
     * Constructs the frame window.
     *
     * @param id            Specifies the window identifier.
     * @param text          Specifies the window text.
     * @param howner        Specifies the owner-window handle.
     * @param x,y,cx,cy     Specifies the window shape.
     * @param frame_style   Specifies the frame window style:
     *
     * <dl>
     * <dt><i>FCF_TITLEBAR       </i><dd>Title bar.
     * <dt><i>FCF_SYSMENU        </i><dd>System menu.
     * <dt><i>FCF_MENU           </i><dd>Application menu.
     * <dt><i>FCF_MINMAX         </i><dd>Minimize and Maximize buttons.
     * <dt><i>FCF_MINBUTTON      </i><dd>Minimize button.
     * <dt><i>FCF_MAXBUTTON      </i><dd>Maximize button.
     * <dt><i>FCF_VERTSCROLL     </i><dd>Vertical scroll bar.
     * <dt><i>FCF_HORZSCROLL     </i><dd>Horizontal scroll bar.
     * <dt><i>FCF_SIZEBORDER     </i><dd>Sizing border.
     * <dt><i>FCF_BORDER         </i><dd>Window is drawn with a thin border.
     * <dt><i>FCF_DLGBORDER      </i><dd>Window is drawn with a standard dialog border.
     * <dt><i>FCF_ACCELTABLE     </i><dd>Causes an accelerator table to be loaded.
     * <dt><i>FCF_ICON           </i><dd>Window is created with an icon associated with it.
     * <dt><i>FCF_SHELLPOSITION  </i><dd>The window is created with a size and position
     *                                 determined by the shell.
     * <dt><i>FCF_SYSMODAL       </i><dd>The frame window is System Modal.
     * <dt><i>FCF_NOBYTEALIGN    </i><dd>When this flag is not set, the frame window is
     *                                 adjusted so that window operations, such as moving,
     *                                 can be performed in an optimized manner.
     * <dt><i>FCF_TASKLIST       </i><dd>When this flag is set, the program title is added
     *                                   to the front of the frame window text, the resulting
     *                                   string is used as the window title and is also entered
     *                                   on the task list.
     * <dt><i>FCF_NOMOVEWITHOWNER</i><dd>The window should not be moved when its owner is moved.
     * <dt><i>FCF_STANDARD       </i><dd>Same as (FCF_TITLEBAR | FCF_SYSMENU | FCF_MINBUTTON |
     *                                   FCF_MAXBUTTON | FCF_SIZEBORDER | FCF_ICON |
     *                                   FCF_MENU | FCF_ACCELTABLE | FCF_SHELLPOSITION | FCF_TASKLIST).
     * <dt><i>FCF_SCREENALIGN    </i><dd>See FS_SCREENALIGN.
     * <dt><i>FCF_MOUSEALIGN     </i><dd>See FS_MOUSEALIGN.
     * <dt><i>FCF_AUTOICON       </i><dd>Performance optimization. When repainting iconized
     *                               frames, the system will redraw the icon and will not
     *                               send a WM_PAINT message to the application.
     * <dt><i>FCF_HIDEBUTTON     </i><dd>Hide button.
     * <dt><i>FCF_HIDEMAX        </i><dd>Hide and maximize buttons.
     * <dt><i>FCF_CLOSEBUTTON    </i><dd>Close button.
     * </dl>
     *
     * @param style       Specifies the window style.
     *
     * @see PMWindow::PMWindow 2
     */

    PMFrame( SHORT id, const char* text, HWND howner,
             LONG x, LONG y, LONG cx, LONG cy, ULONG frame_style, ULONG style = 0 );

    /**
     * Constructs the frame window from the dialog template.
     *
     * @param howner        Specifies the owner-window handle.
     * @param res_id        Dialog-template identity within the resource file.
     *                      It is also used as the identity of the created dialog window.
     * @param hmodule       Module handle referencing a dynamic link library
     *                      containing the resource or NULLHANDLE for the
     *                      application's module.
     */

    PMFrame( HWND howner, SHORT res_id, HMODULE hmodule );

    /**
     * Destructs the frame window object.
     *
     * Cleans up as this window object and destroying the
     * associated presentation window for this object if the object
     * was not wrapped around an existing window handle.
     */

    virtual ~PMFrame();

    /** Sets the window used as the frame window's client area. */
    virtual void client( HWND client );
    /** Sets the menu used as the frame window's menu bar. */
    virtual void menu( HWND hmenu );

    /** Returns the handle of the window used as the frame window's client area. */
    virtual HWND client();
    /** Returns the handle of the menu used as the frame window's menu bar. */
    virtual HWND menu();

    /**
     * Calculates a client rectangle.
     *
     * This method calculates a client rectangle from a
     * frame rectangle.
     */

    virtual PMRect client_rectangle() const;

    /**
     * Displays the frame window.
     *
     * The frame window is made the topmost window also.
     */

    virtual void show( BOOL state = TRUE );

    /**
     * Displays the frame window modally.
     *
     * While the frame window is being shown modally, its parent or owner or
     * both windows are disabled. Other top level windows belonging to the
     * application are not disabled.
     *
     * @return Value established by the <i>dismiss</i> method.
     */

    virtual ULONG show_modally();

    /**
     * Dismiss the frame window.
     *
     * This method hides the modeless frame window, and causes
     * <i>show_modally</i> to return.
     *
     * @param rc    Reply value. Returned to the caller of
     *              <i>show_modally</i>.
     */

    virtual void dismiss( ULONG rc );

    /**
     * Replaces the accelerator keys used by the window.
     *
     * @param res_id    Accelerator-table identifier, within the resource file.
     * @param hmodule   Module handle referencing a dynamic link library
     *                  containing the resource or NULLHANDLE for the
     *                  application's module.
     */

    virtual void attach_accelerators( SHORT res_id, HMODULE hmodule );

    /**
     * Detaches the accelerator keys used by the window.
     */

    virtual void detach_accelerators();

    /**
     * Use these enumerators to specify the possible locations for a
     * frame extension.
     *
     * <dl>
     * <dt><i>left  </i><dd>Specifies the left-hand side of the client area.
     * <dt><i>right </i><dd>Specifies the right-hand side of the client area.
     * <dt><i>above </i><dd>Specifies the top of the client area.
     * <dt><i>below </i><dd>Specifies the bottom of the client area.
     * </dl>
     */

    enum location_type { left  = 0,
                         right = 1,
                         above = 2,
                         below = 3  };

    /** Attaches a window to frame as a frame extension. */
    virtual void attach_extension( HWND hwnd, location_type location );
    /** Detaches a frame extension from frame. */
    virtual void detach_extension( HWND hwnd );

    /** Sets the window as topmost window. */
    virtual void set_as_topmost( BOOL topmost = TRUE );
    /** Returns TRUE if the window is a topmost window. */
    virtual BOOL is_topmost() const;

  protected:

    /**
     * Dispatch system native events.
     *
     * PMFrame calls this function when a system native window
     * event occurs.
     */

    virtual MRESULT dispatch( ULONG msg, MPARAM mp1, MPARAM mp2 );

  private:
    struct WNDEXTS {
      HWND          hwnd;
      location_type location;
      WNDEXTS*      next;
    };

    FRAMECDATA m_fcdata;
    HWND       m_client;
    HWND       m_menu;
    WNDEXTS*   m_extensions;
    HPOINTER   m_icon;
    HACCEL     m_acceltable;

    void win_format();
    void win_attach_extension( HWND hwnd, location_type location );
    void win_detach_extension( HWND hwnd );
    void win_detach_all_extensions();
};

#endif
