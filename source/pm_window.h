/*
 * Copyright (C) 2001-2011 Dmitry A.Steklenev
 *
 * $Id: pm_window.h,v 1.25 2012/06/15 11:25:20 glass Exp $
 */

#ifndef PM_WINDOW_H
#define PM_WINDOW_H

#include "pm_os2.h"
#include "pm_error.h"
#include "pm_noncopyable.h"
#include "pm_rectangle.h"
#include "pm_initwindowset.h"

/**
 * Base window class.
 *
 * The PMWindow class is the base window class and provides
 * behavior common to all windows. Although this class contains
 * behavior requiring the existence of a presentation window,
 * you must construct the presentation window itself using a
 * derived class.
 *
 * You can construct and destruct objects of this class.
 *
 * Note: Although you can construct objects of this class
 * directly, you do not generally do so.
 *
 * @author Dmitry A.Steklenev
 * @version $Revision: 1.25 $
 */

#ifndef __ccdoc__

#define CCI_EDITBACKGROUND CCI_PAGEBACKGROUND
#define CCI_EDITFOREGROUND CCI_PAGEFOREGROUND

#define SPTR_DEFAULT 0

/**
 * This is equal to WS_MULTISELECT that is not used by OS/2
 * anymore and we can use this value.
 */

#define WS_DLGPOINTS 0x00040000
#endif

class PMWindow : public PMNonCopyable
{
  public:

    /**
     * Wraps the window object around an existing
     * presentation window handle.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     */

    PMWindow( HWND handle );

    /**
     * Wraps the window object around an existing
     * child window with the specified identity.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     *
     * @param hparent       Specifies the parent-window handle.
     * @param id            Specifies the identity of the child window.
     */

    PMWindow( HWND hparent, SHORT id );

    /**
     * Constructs the presentation window.
     *
     * @param id            Specifies the window identifier.
     * @param text          Specifies the window text.
     * @param hparent       Specifies the parent-window handle.
     * @param howner        Specifies the owner-window handle.
     * @param x,y,cx,cy     Specifies the window rectangle.
     * @param style         Specifies the window style:
     *
     * <dl>
     * <dt><i>WS_CLIPCHILDREN</i><dd>Prevents a window from painting over its child windows.
     * <dt><i>WS_CLIPSIBLINGS</i><dd>Prevents a window from painting over its sibling windows.
     * <dt><i>WS_DISABLED    </i><dd>Used by an application to disable a window.
     * <dt><i>WS_GROUP       </i><dd>Specifies the first control of a group of controls.
     * <dt><i>WS_MAXIMIZED   </i><dd>Enlarges a window to the maximum size.
     * <dt><i>WS_MINIMIZED   </i><dd>Reduces a window to the size of an icon.
     * <dt><i>WS_PARENTCLIP  </i><dd>Extends a window's visible region to include that
     *                               of its parent window.
     * <dt><i>WS_SAVEBITS    </i><dd>Saves the screen area under a window as a bit map.
     * <dt><i>WS_SYNCPAINT   </i><dd>Causes a window to receive WM_PAINT messages immediately
     *                                after a part of the window becomes invalid.
     * <dt><i>WS_TABSTOP     </i><dd>Specifies one of any number of controls through which
     *                               the user can move by tabbing.
     * <dt><i>WS_VISIBLE     </i><dd>Makes a window visible.
     * <dt><i>WS_DLGPOINTS   </i><dd>The window rectangle is specified in dialog units.
     * </dl>
     */

    PMWindow( SHORT id, const char* text, HWND hparent, HWND howner,
              LONG x, LONG y, LONG cx, LONG cy, ULONG style );
    /**
     * Constructs the presentation window from the dialog template.
     *
     * @param hparent       Specifies the parent-window handle.
     * @param howner        Specifies the owner-window handle.
     * @param res_id        Dialog-template identity within the resource file.
     *                      It is also used as the identity of the created window.
     * @param hmodule       Module handle referencing a dynamic link library
     *                      containing the resource or NULLHANDLE for the
     *                      application's module.
     */

    PMWindow( HWND hparent, HWND howner, SHORT res_id, HMODULE hmodule );

  protected:

    /**
     * Constructs the presentation window of the specified class.
     *
     * @param classname     Specifies the registered-class name.
     * @param id            Specifies the window identifier.
     * @param text          Specifies the window text.
     * @param hparent       Specifies the parent-window handle.
     * @param howner        Specifies the owner-window handle.
     * @param x,y,cx,cy     Specifies the window shape.
     * @param style         Specifies the window style.
     * @param classdata     Specifies the pointer to control data.
     */

    PMWindow( const char* classname, SHORT id, const char* text, HWND hparent, HWND howner,
              LONG x, LONG y, LONG cx, LONG cy, ULONG style, PVOID classdata = NULL );
  public:

    /**
     * Destructs the window object.
     *
     * Cleans up as this window object and destroying the
     * associated presentation window for this object if the object
     * was not created from an existing window handle.
     */

    virtual ~PMWindow();

    /**
     * Destroys the presentation window.
     *
     * Destroying the associated presentation window
     * for this object.
     */

    virtual void destroy();

    /** Returns the presentation window handle. */
    HWND  handle() const { return m_handle; }
    /** Returns the window identifier. */
    SHORT id() const { return m_id; }

    /**
     * Returns the parent window handle.
     *
     * The parent window provides the coordinate system used for
     * positioning a child window. A window whose parent is the desktop window,
     * is called a top-level or overlapped window.
     */

    HWND parent() const;

    /**
     * Returns the owner window handle.
     *
     * Windows that send messages send them to their owner.
     * When an owner window is destroyed, all windows owned by it
     * are also destroyed. The owner window must belong to the
     * current thread.
     */

    HWND owner() const;

    /**
     * Sets the parent window.
     *
     * The parent window provides the coordinate system used for
     * positioning a child window. A window whose parent is the desktop window,
     * is called a top-level or overlapped window.
     *
     * @param hparent New parent window handle.
     *
     *                <ul>
     *                <li>This cannot be a descendant of this window.
     *                <li>If this parameter is a desktop window handle or HWND_DESKTOP,
     *                    window becomes a main window.
     *                <li>If this parameter is not equal to HWND_OBJECT, it must be a descendant
     *                    of the same desktop window as this window.
     *                <li>If this parameter is HWND_OBJECT or a window handle returned by WinQueryObjectWindow,
     *                    window becomes an object window.
     *                </ul>
     *
     * @param redraw  Redraw indicator.
     */

    virtual void parent( HWND hparent, BOOL redraw = TRUE );

    /**
     * Sets the owner window.
     *
     * Windows that send messages send them to their owner.
     * When an owner window is destroyed, all windows owned by it
     * are also destroyed. The owner window must belong to the
     * current thread.
     *
     * @param howner  New owner window handle.
     */

    virtual void owner( HWND howner );

    /**
     * Return the handle of the first frame window associated with this window.
     */

    HWND frame() const;

    /** Sets the window text. */
    virtual void text( const char* text );
    /** Sets the window's position and size. */
    virtual void rectangle( const PMRect& rect );
    /** Centers the window concerning his owner window. */
    virtual void center_at();
    /** Sets a new font to be used by the window. */
    virtual void font( const char* font );

    /**
     * Translates the window text.
     *
     * Translates the window text and all the child texts using
     * for this purpose the current {@link PMLanguage::instance instance}
     * of the messages management object.
     */

    virtual void translate();

    /**
     * Returns the window text.
     *
     * @param result  A buffer in which the window text is returned.
     * @param size    This is the size of the buffer specified by the <i>result</i>
     *                parameter. If the call is successful, this is overwritten
     *                with the number of bytes copied into the buffer.
     */

    virtual char* text( char* result, int size ) const;

    /**
     * Returns the length of the window text.
     *
     * @return The length of the window text, excluding any
     *             null termination character.
     */

    virtual int text_len() const;

    /**
     * Returns the specified color value.
     *
     * @param type    Specify one of window's colors:
     *
     * <dl>
     * <dt><i>CCI_FOREGROUND                </i><dd>Foreground color.
     * <dt><i>CCI_FOREGROUNDREADONLY        </i><dd>Read-only text foreground color.
     * <dt><i>CCI_BACKGROUND                </i><dd>Background color.
     * <dt><i>CCI_BACKGROUNDDIALOG          </i><dd>Background color (in dialog).
     * <dt><i>CCI_DISABLEDFOREGROUND        </i><dd>Disabled foreground color.
     * <dt><i>CCI_DISABLEDFOREGROUNDREADONLY</i><dd>Disabled read-only text foreground color.
     * <dt><i>CCI_DISABLEDBACKGROUND        </i><dd>Disabled background color.
     * <dt><i>CCI_DISABLEDBACKGROUNDDIALOG  </i><dd>Disabled background color (in dialog).
     * <dt><i>CCI_HIGHLIGHTFOREGROUND       </i><dd>Highlight text foreground color.
     * <dt><i>CCI_HIGHLIGHTBACKGROUND       </i><dd>Highlight background color.
     * <dt><i>CCI_HIGHLIGHTBACKGROUNDDIALOG </i><dd>Highlight background color (in dialog).
     * <dt><i>CCI_INACTIVEFOREGROUND        </i><dd>Inactive foreground color.
     * <dt><i>CCI_INACTIVEFOREGROUNDDIALOG  </i><dd>Inactive foreground color (in dialog).
     * <dt><i>CCI_INACTIVEBACKGROUND        </i><dd>Inactive background color.
     * <dt><i>CCI_INACTIVEBACKGROUNDTEXT    </i><dd>Inactive text background color.
     * <dt><i>CCI_ACTIVEFOREGROUND          </i><dd>Active foreground color.
     * <dt><i>CCI_ACTIVEFOREGROUNDDIALOG    </i><dd>Active foreground color (in dialog).
     * <dt><i>CCI_ACTIVEBACKGROUND          </i><dd>Active background color.
     * <dt><i>CCI_ACTIVEBACKGROUNDTEXT      </i><dd>Active text background color.
     * <dt><i>CCI_PAGEBACKGROUND            </i><dd>Page background color.
     * <dt><i>CCI_PAGEFOREGROUND            </i><dd>Page foreground color.
     * <dt><i>CCI_EDITBACKGROUND            </i><dd>Edit area background color.
     * <dt><i>CCI_EDITFOREGROUND            </i><dd>Edit area foreground color.
     * <dt><i>CCI_FIELDBACKGROUND           </i><dd>Edge (or status line) window color.
     * <dt><i>CCI_BORDER                    </i><dd>Thin border color.
     * <dt><i>CCI_BORDERLIGHT               </i><dd>Light border color.
     * <dt><i>CCI_BORDERDARK                </i><dd>Dark border color.
     * <dt><i>CCI_BORDER2                   </i><dd>Disabled border, new notebook border or container
     *                                              record emphasis color.
     * <dt><i>CCI_BORDER2LIGHT              </i><dd>Light border 2 color.
     * <dt><i>CCI_BORDER2DARK               </i><dd>Dark border 2 color.
     * <dt><i>CCI_BORDERDEFAULT             </i><dd>Outer button border color.
     * <dt><i>CCI_BUTTONBACKGROUND          </i><dd>Sub-button background color.
     * <dt><i>CCI_BUTTONBORDERLIGHT         </i><dd>Sub-button light border color.
     * <dt><i>CCI_BUTTONBORDERDARK          </i><dd>Sub-button dark border color.
     * <dt><i>CCI_ARROW                     </i><dd>Arrow color.
     * <dt><i>CCI_DISABLEDARROW             </i><dd>Disabled arrow color.
     * <dt><i>CCI_ARROWBORDERLIGHT          </i><dd>Arrow light border color.
     * <dt><i>CCI_ARROWBORDERDARK           </i><dd>Arrow dark border color.
     * <dt><i>CCI_CHECKLIGHT                </i><dd>Light check mark color.
     * <dt><i>CCI_CHECKMIDDLE               </i><dd>Middle check mark color.
     * <dt><i>CCI_CHECKDARK                 </i><dd>Dark check mark color.
     * <dt><i>CCI_ICONFOREGROUND            </i><dd>Icon text color.
     * <dt><i>CCI_ICONBACKGROUND            </i><dd>Icon text background color.
     * <dt><i>CCI_ICONBACKGROUNDDESKTOP     </i><dd>Icon text background color (in desktop).
     * <dt><i>CCI_ICONHILITEFOREGROUND      </i><dd>Icon text highlight color.
     * <dt><i>CCI_ICONHILITEBACKGROUND      </i><dd>Icon text highlight background color.
     * <dt><i>CCI_MAJORTABFOREGROUND        </i><dd>Major tab text color.
     * <dt><i>CCI_MAJORTABBACKGROUND        </i><dd>Major tab background color.
     * <dt><i>CCI_MINORTABFOREGROUND        </i><dd>Minor tab text color.
     * <dt><i>CCI_MINORTABBACKGROUND        </i><dd>Minor tab background color.
     * </dl>
     *
     * @return The RGB color value. If you have not set the specified color, the default
     *         color value CLR_DEFAULT is returned.
     */

    LONG color( LONG type ) const;

    /**
     * Sets the specified color value.
     *
     * @param type    Specifies one of window's color.
     * @param color   The RGB color value or one of the SYSCLR_* index values:
     *
     * <dl>
     * <dt><i>SYSCLR_SHADOWHILITEBGND     </i><dd>System color for shadow highlighted background.
     * <dt><i>SYSCLR_SHADOWHILITEFGND     </i><dd>System color for shadow highlighted foreground.
     * <dt><i>SYSCLR_SHADOWTEXT           </i><dd>System color for shadow text.
     * <dt><i>SYSCLR_ENTRYFIELD           </i><dd>System color for entry field.
     * <dt><i>SYSCLR_MENUDISABLEDTEXT     </i><dd>System color for disabled menu text.
     * <dt><i>SYSCLR_MENUHILITE           </i><dd>System color for highlighted menu text.
     * <dt><i>SYSCLR_MENUHILITEBGND       </i><dd>System color for highlighted menu background.
     * <dt><i>SYSCLR_PAGEBACKGROUND       </i><dd>System color for page background.
     * <dt><i>SYSCLR_FIELDBACKGROUND      </i><dd>System color for field background.
     * <dt><i>SYSCLR_BUTTONLIGHT          </i><dd>System color for light button.
     * <dt><i>SYSCLR_BUTTONMIDDLE         </i><dd>System color for middle button.
     * <dt><i>SYSCLR_BUTTONDARK           </i><dd>System color for dark button.
     * <dt><i>SYSCLR_BUTTONDEFAULT        </i><dd>System color for default button.
     * <dt><i>SYSCLR_TITLEBOTTOM          </i><dd>System color for title bottom.
     * <dt><i>SYSCLR_SHADOW               </i><dd>System color for shadow.
     * <dt><i>SYSCLR_ICONTEXT             </i><dd>System color for icon text.
     * <dt><i>SYSCLR_DIALOGBACKGROUND     </i><dd>System color for dialog background.
     * <dt><i>SYSCLR_HILITEFOREGROUND     </i><dd>System color for highlighted foreground.
     * <dt><i>SYSCLR_HILITEBACKGROUND     </i><dd>System color for highlighted background.
     * <dt><i>SYSCLR_TITLETEXT            </i><dd>System color for title text.
     * <dt><i>SYSCLR_INACTIVETITLETEXTBGND</i><dd>System color for inactive title text background.
     * <dt><i>SYSCLR_ACTIVETITLETEXTBGND  </i><dd>System color for active title text background.
     * <dt><i>SYSCLR_INACTIVETITLETEXT    </i><dd>System color for inactive title text.
     * <dt><i>SYSCLR_ACTIVETITLETEXT      </i><dd>System color for active title text.
     * <dt><i>SYSCLR_OUTPUTTEXT           </i><dd>System color for output text.
     * <dt><i>SYSCLR_WINDOWSTATICTEXT     </i><dd>System color for static window text.
     * <dt><i>SYSCLR_SCROLLBAR            </i><dd>System color for scroll bar.
     * <dt><i>SYSCLR_BACKGROUND           </i><dd>System color for background.
     * <dt><i>SYSCLR_ACTIVETITLE          </i><dd>System color for active title.
     * <dt><i>SYSCLR_INACTIVETITLE        </i><dd>System color for inactive title.
     * <dt><i>SYSCLR_MENU                 </i><dd>System color for a menu.
     * <dt><i>SYSCLR_MENUTEXT             </i><dd>System color for menu text.
     * <dt><i>SYSCLR_WINDOW               </i><dd>System color for a window.
     * <dt><i>SYSCLR_WINDOWTEXT           </i><dd>System color for window text.
     * <dt><i>SYSCLR_WINDOWFRAME          </i><dd>System color for a window frame.
     * <dt><i>SYSCLR_ACTIVEBORDER         </i><dd>System color for active border.
     * <dt><i>SYSCLR_INACTIVEBORDER       </i><dd>System color for inactive border.
     * <dt><i>SYSCLR_APPWORKSPACE         </i><dd>System color for application work space.
     * <dt><i>SYSCLR_HELPBACKGROUND       </i><dd>System color for help background.
     * <dt><i>SYSCLR_HELPTEXT             </i><dd>System color for help text.
     * <dt><i>SYSCLR_HELPHILITE           </i><dd>System color for help highlighting..
     * </dl>
     *
     * @see PMWindow::color
     */

    void color( LONG type, LONG color );

    /** Returns the window rectangle. */
    virtual PMRect rectangle() const;
    /** Makes the window visible. */
    virtual void show( BOOL state = TRUE );
    /** Makes the window invisible. */
    virtual void hide();

    /**
     * Is the window visible.
     *
     * If the window's style is set to visible, TRUE is returned.
     * Otherwise, FALSE is returned. A window can have the style visible
     * and yet not be showing if it is covered by another window.
     */

    virtual BOOL is_visible();

    /** Enables the window to accept keyboard and mouse input. */
    virtual void enable( BOOL state = TRUE );
    /** Prevents keyboard and mouse input from being sent to the window. */
    virtual void disable();

    /**
     * Use these enumerators to specify various object types that can be
     * dropped to window.
     */

    enum drop_type { drop_none    = 0x0000,
                     drop_os2file = 0x0001 };

    /** Enables the window to accept dropped objects. */
    virtual void enable_drop( LONG type );

    /**
     * Is the window valid.
     *
     * If this object represents a valid window in the
     * window system, TRUE is returned. If the window has yet to be
     * created or has already been destroyed, FALSE is returned.
     */

    virtual BOOL is_valid() const;

    /** Sets the input focus to the window. */
    virtual void set_focus();

    /**
     * Has focus.
     *
     * If the window has the input focus, TRUE is returned.
     * Otherwise, FALSE is returned.
     */

    virtual BOOL has_focus() const;

    /**
     * This method adds a region to a window's update region.
     *
     * The update region is a subregion of a window that is
     * deemed "invalid" or incorrect in visual terms and is
     * in need of redrawing.
     */

    virtual void invalidate( const PMRect& rect );

    /**
     * This method adds the whole window to a window's update region.
     *
     * The update region is a subregion of a window that is
     * deemed "invalid" or incorrect in visual terms and is
     * in need of redrawing.
     */

    virtual void invalidate();

    /**
     * Captures mouse pointer.
     *
     * If capture is true, pointer events are sent only to this window
     * even if the pointer is outside of this window. If capture is false,
     * the window releases the pointer capture. If you attempt to capture
     * the pointer when another window currently is capturing the pointer,
     * an exception is thrown.
     */

    virtual void capture_pointer( BOOL capture = TRUE );

    /**
     * Release mouse pointer.
     *
     * Causes the window to release the pointer capture (pointer capture
     * is set with the function capture_pointer).
     *
     * This function causes mouse events to again be dispatched to the window
     * underneath the mouse pointer.
     */

    virtual void release_pointer();

    /**
     * Has pointer captured.
     *
     * If this window is currently capturing pointer events, true is
     * returned. Otherwise, false is returned.
     */

    virtual BOOL has_pointer_captured() const;

    /**
     * Sets the appearance used by the mouse pointer when it is over the window.
     *
     * @param id        System-pointer identifier.
     *
     * <dl>
     * <dt><i>SPTR_DEFAULT        </i><dd>Default pointer, that is chosen by Presentation Manager.
     * <dt><i>SPTR_ARROW          </i><dd>Arrow pointer
     * <dt><i>SPTR_TEXT           </i><dd>Text I-beam pointer
     * <dt><i>SPTR_WAIT           </i><dd>Hourglass pointer
     * <dt><i>SPTR_SIZE           </i><dd>Size pointer
     * <dt><i>SPTR_MOVE           </i><dd>Move pointer
     * <dt><i>SPTR_SIZENWSE       </i><dd>Downward-sloping, double-headed arrow pointer
     * <dt><i>SPTR_SIZENESW       </i><dd>Upward-sloping, double-headed arrow pointer
     * <dt><i>SPTR_SIZEWE         </i><dd>Horizontal, double-headed arrow pointer
     * <dt><i>SPTR_SIZENS         </i><dd>Vertical, double-headed arrow pointer
     * <dt><i>SPTR_APPICON        </i><dd>Standard application icon pointer
     * <dt><i>SPTR_ICONINFORMATION</i><dd>Information icon pointer
     * <dt><i>SPTR_ICONQUESTION   </i><dd>Question mark icon pointer
     * <dt><i>SPTR_ICONERROR      </i><dd>Exclamation mark icon pointer
     * <dt><i>SPTR_ICONWARNING    </i><dd>Warning icon pointer
     * <dt><i>SPTR_ILLEGAL        </i><dd>Illegal operation icon pointer
     * <dt><i>SPTR_FILE           </i><dd>Single file icon pointer
     * <dt><i>SPTR_MULTFILE       </i><dd>Multiple files icon pointer
     * <dt><i>SPTR_FOLDER         </i><dd>Folder icon pointer
     * <dt><i>SPTR_PROGRAM        </i><dd>Application program icon pointer
     * </dl>
     */

    virtual void pointer( LONG id );

    /** Returns the mouse pointer used when the mouse is over the window. */
    virtual LONG pointer() const;

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
     * Sends a message to window.
     *
     * This method sends a message with identity <i>msg</i> to window,
     * passing <i>mp1</i> and <i>mp2</i> as the parameters to
     * the window.
     */

    MRESULT send( ULONG msg, MPARAM mp1, MPARAM mp2 );

    /**
     * Posts a message to window.
     *
     * This method posts a message to the message queue associated
     * with the window.
     *
     * @return Success indicator.
     */

    BOOL post( ULONG msg, MPARAM mp1, MPARAM mp2 );

    /**
     * This method starts a timer.
     *
     * This method creates a timer identified by <i>id</i>, set to
     * time out every <i>timeout</i> milliseconds. When a timer times out,
     * a WM_TIMER message is posted.
     *
     * A <i>timeout</i> value of zero causes the timer to timeout as fast
     * as possible; generally, this is about 1/18 second.
     *
     * A second call of this method, for a timer that already exists,
     * resets that timer.
     */

     virtual void start_timer( ULONG id, ULONG timeout );

    /**
     * This method stops a timer.
     *
     * When this method is called, no further messages are received
     * from the stopped timer, even if it has timed out.
     */

     virtual void stop_timer( ULONG id );

    /**
     * Determines whether to delete the window object when the presentation
     * window is destroyed.
     *
     * The deletion occurs when the window system dispatches a destroy
     * event to the window.
     */

     virtual void auto_delete_object( BOOL state = TRUE );

    /**
     * If the window object is deleted when a destroy event is dispatched to
     * the window, TRUE is returned.
     */

     virtual BOOL is_auto_delete_object();

  protected:

    /**
     * Handle events.
     *
     * Attaches the handler to the PMWindow object. The windows's
     * dispatch function is called to process all events sent or posted to the
     * window.
     */

    void handle_events();

    /**
     * Stop handling events.
     *
     * Detaches the handler from the PMWindow object. The window's
     * dispatch function is no longer called to process events sent or
     * posted to the window.
     */

    void stop_handling_events();

    /**
     * Dispatch system native events.
     *
     * PMWindow calls this function when a system native window
     * event occurs.
     */

    virtual MRESULT dispatch( ULONG msg, MPARAM mp1, MPARAM mp2 );

    /**
     * Dispatch all not catched events.
     *
     * A virtual method that provides default implementation for
     * all events that occur on every window.
     */

    virtual MRESULT dispatch_everything( ULONG msg, MPARAM mp1, MPARAM mp2 );

  private:
    struct map {
      HWND      handle;
      PMWindow* window;
    };

    PFNWP    m_default_handler;
    HWND     m_handle;
    SHORT    m_id;
    BOOL     m_wrapped;
    HPOINTER m_pointer;
    LONG     m_pointer_id;
    HACCEL   m_acceltable;
    BOOL     m_auto_delete;
    LONG     m_drop_types;

    /** Prepares the window to the drop operation. */
    MRESULT drag_over( PDRAGINFO pdinfo );
    /** Receives the dropped objects. */
    MRESULT drop( PDRAGINFO pdinfo );

    static MRESULT _System win_proc_via_ptr( HWND, ULONG, MPARAM, MPARAM );
    static MRESULT _System win_proc_via_map( HWND, ULONG, MPARAM, MPARAM );
    static MRESULT _System def_proc( HWND, ULONG, MPARAM, MPARAM );

    static PMWindow* win_via_handle( HWND hwnd );
};

/* Sends a message to window. */
inline MRESULT PMWindow::send( ULONG msg, MPARAM mp1, MPARAM mp2 ) {
  return WinSendMsg( m_handle, msg, mp1, mp2 );
}

/* Posts a message to window. */
inline BOOL PMWindow::post( ULONG msg, MPARAM mp1, MPARAM mp2 ) {
  return LONGFROMMR( WinPostMsg( m_handle, msg, mp1, mp2 ));
}

#endif
