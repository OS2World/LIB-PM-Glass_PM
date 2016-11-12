/*
 * Copyright (C) 2001-2008 Dmitry A.Steklenev
 *
 * $Id: pm_gui.h,v 1.6 2011/05/25 10:53:54 glass Exp $
 */

#ifndef PM_GUI_H
#define PM_GUI_H

#include <stdlib.h>

#include "pm_os2.h"
#include "pm_noncopyable.h"

#ifndef PM_MAX_THREADS

/**
 * Sets the maximum number of threads supported by the library.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.6 $
 */

#define PM_MAX_THREADS 50
#endif

/**
 * GUI initialization and information class.
 *
 * Initialize GUI in current thread. Automatically called
 * from <i>PMThread</i>.
 *
 * You can construct and destruct objects of this class.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.6 $
 */

class PMGUI : public PMNonCopyable
{
  public:

    /**
     * Constructs the GUI object and initializes the
     * GUI facilities for use by an application.
     */

    PMGUI();

    /**
     * Constructs the GUI object from an existing
     * GUI environment.
     */

    PMGUI( HAB hab );

    /**
     * Destroys the GUI object.
     *
     * Releases all of associated GUI resources if the object
     * was not created from an existing environment.
     */

   ~PMGUI();

    /** Returns the current thread identifier. */
    static TID tid();
    /** Returns the current process identifier. */
    static PID pid();
    /** Returns the anchor block handle of the current thread. */
    static HAB hab();
    /** Returns the message queue handle of the current thread. */
    static HMQ hmq();


    /**
     * Returns a system metric.
     *
     * Allows the application to ask for details about
     * the user interface element sizes.
     *
     * @param id  Metric-value identity:
     *
     * <dl>
     * <dt><i>SV_BEGINDRAG</i>
     *        <dd>Mouse begin drag (low word=mouse message id (WM_*),
     *            high word=keyboard control code (KC_*)).
     * <dt><i>SV_BEGINDRAGKB</i>
     *        <dd>Keyboard begin drag (low word=virtual key code (VK_*),
     *            high word=keyboard control code (KC_*)).
     * <dt><i>SV_BEGINSELECT</i>
     *        <dd>Mouse begin swipe select (low word=mouse message id (WM_*),
     *            high word=keyboard control code (KC_*)).
     * <dt><i>SV_BEGINSELECTKB</i>
     *        <dd>Keyboard begin swipe select (low word=virtual key code (VK_*),
     *            high word=keyboard control code (KC_*)).
     * <dt><i>SV_CICONTEXTLINES</i>
     *        <dd>Maximum number of lines that the icon text may occupy for a
     *            minimized window.
     * <dt><i>SV_CONTEXTHELP</i>
     *        <dd>Mouse control for pop-up menu (low word=mouse message id (WM_*),
     *            high word=keyboard control code (KC_*)).
     * <dt><i>SV_CONTEXTHELPKB</i>
     *        <dd>Keyboard control for pop-up menu (low word=virtual key code (VK_*),
     *            high word=keyboard control code (KC_*)).
     * <dt><i>SV_CONTEXTMENU</i>
     *        <dd>Mouse request pop-up menu (low word=mouse message id (WM_*),
     *            high word=keyboard control code (KC_*)).
     * <dt><i>SV_CONTEXTMENUKB</i>
     *        <dd>Keyboard request pop-up menu (low word=virtual key code (VK_*),
     *            high word=keyboard control code (KC_*)).
     * <dt><i>SV_CMOUSEBUTTONS</i>
     *        <dd>The number of buttons on the pointing device (zero if no pointing
     *            device is installed).
     * <dt><i>SV_CTIMERS</i>
     *        <dd>Count of available timers.
     * <dt><i>SV_CURSORLEVEL</i>
     *        <dd>The cursor hide level.
     * <dt><i>SV_CURSORRATE</i>
     *        <dd>Cursor blink rate, in milliseconds.
     * <dt><i>SV_CXBORDER</i>
     *        <dd>Width of the nominal-width border.
     * <dt><i>SV_CXBYTEALIGN</i>
     *        <dd>Horizontal count of pels for alignment.
     * <dt><i>SV_CXDBLCLK</i>
     *        <dd>Width of the pointing device double-click sensitive area.
     *            The default is the system-font character width.
     * <dt><i>SV_CXDLGFRAME</i>
     *        <dd>Width of the dialog-frame border.
     * <dt><i>SV_CXFULLSCREEN</i>
     *        <dd>Width of the client area when the window is full screen.
     * <dt><i>SV_CXHSCROLLARROW</i>
     *        <dd>Width of the horizontal scroll-bar arrow bit maps.
     * <dt><i>SV_CXHSLIDER</i>
     *        <dd>Width of the horizontal scroll-bar thumb.
     * <dt><i>SV_CXICON</i>
     *        <dd>Icon width.
     * <dt><i>SV_CXICONTEXTWIDTH</i>
     *        <dd>Maximum number of characters per line allowed in the icon text for
     *            a minimized window.
     * <dt><i>SV_CXMINMAXBUTTON</i>
     *        <dd>Width of the minimize/maximize buttons.
     * <dt><i>SV_CXMOTIONSTART</i>
     *        <dd>The number of pels that a pointing device must be moved in the
     *            horizontal direction, while the button is depressed, before a
     *            WM_BUTTONxMOTIONSTR message is sent.
     * <dt><i>SV_CXPOINTER</i>
     *        <dd>Pointer width.
     * <dt><i>SV_CXSCREEN</i>
     *        <dd>Width of the screen.
     * <dt><i>SV_CXSIZEBORDER</i>
     *        <dd>Width of the sizing border.
     * <dt><i>SV_CXVSCROLL</i>
     *        <dd>Width of the vertical scroll-bar.
     * <dt><i>SV_CYBORDER</i>
     *        <dd>Height of the nominal-width border.
     * <dt><i>SV_CYBYTEALIGN</i>
     *        <dd>Vertical count of pels for alignment.
     * <dt><i>SV_CYDBLCLK</i>
     *        <dd>Height of the pointing device double-click sensitive area.
     *            The default is half the height of the system font character height.
     * <dt><i>SV_CYDLGFRAME</i>
     *        <dd>Height of the dialog-frame border.
     * <dt><i>SV_CYFULLSCREEN</i>
     *        <dd>Height of the client area when the window is full screen (excluding
     *            menu height).
     * <dt><i>SV_CYHSCROLL</i>
     *        <dd>Height of the horizontal scroll-bar.
     * <dt><i>SV_CYICON</i>
     *        <dd>Icon height.
     * <dt><i>SV_CYMENU</i>
     *        <dd>Height of the single-line menu height.
     * <dt><i>SV_CYMINMAXBUTTON</i>
     *        <dd>Height of the minimize/maximize buttons.
     * <dt><i>SV_CYMOTIONSTART</i>
     *        <dd>The number of pels that a pointing device must be moved in the
     *            vertical direction, while the button is depressed, before a
     *            WM_BUTTONxMOTIONSTR message is sent.
     * <dt><i>SV_CYPOINTER</i>
     *        <dd>Pointer height.
     * <dt><i>SV_CYSCREEN</i>
     *        <dd>Height of the screen.
     * <dt><i>SV_CYSIZEBORDER</i>
     *        <dd>Height of the sizing border.
     * <dt><i>SV_CYTITLEBAR</i>
     *        <dd>Height of the caption.
     * <dt><i>SV_CYVSCROLLARROW</i>
     *        <dd>Height of the vertical scroll-bar arrow bit maps.
     * <dt><i>SV_CYVSLIDER</i>
     *        <dd>Height of the vertical scroll-bar thumb.
     * <dt><i>SV_DBLCLKTIME</i>
     *        <dd>Pointing device double-click time, in milliseconds.
     * <dt><i>SV_DEBUG</i>
     *        <dd>FALSE indicates this is not a debug system.
     * <dt><i>SV_ENDDRAG</i>
     *        <dd>Mouse end drag (low word=mouse message id (WM_*),
     *            high word=keyboard control code (KC_*)).
     * <dt><i>SV_ENDDRAGKB</i>
     *        <dd>Keyboard end drag (low word=virtual key code (VK_*),
     *            high word=keyboard control code (KC_*)).
     * <dt><i>SV_ENDSELECT</i>
     *        <dd>Mouse select or end swipe select (low word=mouse message id (WM_*),
     *            high word=keyboard control code (KC_*)).
     * <dt><i>SV_ENDSELECTKB</i>
     *        <dd>Keybaord select or end swipe select (low word=virtual key code (VK_*),
     *            high word=keyboard control code (KC_*)).
     * <dt><i>SV_ERRORDURATION</i>
     *        <dd>Duration for error alarms generated by WinAlarm.
     * <dt><i>SV_ERRORFREQ</i>
     *        <dd>Frequency for error alarms generated by WinAlarm.
     * <dt><i>SV_EXTRAKEYBEEP</i>
     *        <dd>When TRUE, the press of a key that does not exist on the Enhanced
     *            keyboard causes the system to generate a beep.
     * <dt><i>SV_FIRSTSCROLLRATE</i>
     *        <dd>The delay (in milliseconds) before autoscrolling starts, when using
     *            a scroll bar.
     * <dt><i>SV_INSERTMODE</i>
     *        <dd>TRUE if the system is in insert mode (for edit and multi-line edit
     *            controls); FALSE if in overtype mode.
     * <dt><i>SV_KBDALTERED</i>
     *        <dd>Hardware ID of the newly attached keyboard.
     * <dt><i>SV_LOCKSTARTINPUT</i>
     *        <dd>TRUE when the type ahead function is enabled; FALSE when the type ahead
     *            function is disabled.
     * <dt><i>SV_MENUROLLDOWNDELAY</i>
     *        <dd>The delay in milliseconds before displaying a pull down referred to from
     *            a submenu item, when the button is already down as the pointer moves
     *            onto the submenu item.
     * <dt><i>SV_MENUROLLUPDELAY</i>
     *        <dd>The delay in milliseconds before hiding a pull down referred to
     *            from a submenu item, when the button is already down as the pointer
     *            moves off the submenu item.
     * <dt><i>SV_MONOICONS</i>
     *        <dd>When TRUE preference is given to black and white icons when
     *            selecting which icon resource definition to use on the screen.
     *            Black and white icons may have more clarity than color icons on LCD
     *            and Plasma display screens.
     * <dt><i>SV_MOUSEPRESENT</i>
     *        <dd>When TRUE a mouse pointing device is attached to the system.
     * <dt><i>SV_NOTEDURATION</i>
     *        <dd>Duration for note alarms generated by WinAlarm.
     * <dt><i>SV_NOTEFREQ</i>
     *        <dd>Frequency for note alarms generated by WinAlarm.
     * <dt><i>SV_OPEN</i>
     *        <dd>Mouse open (low word=mouse message id (WM_*), high
     *            word=keyboard control code (KC_*)).
     * <dt><i>SV_OPENKB</i>
     *        <dd>Keyboard open (low word=virtual key code (VK_*),
     *            high word=keyboard control code (KC_*)).
     * <dt><i>SV_POINTERLEVEL</i>
     *        <dd>Pointer hide level. If the pointer level is zero, the
     *            pointer is visible. If it is greater than zero, the pointer
     *            is not visible. The WinShowPointer call is invoked to increment
     *            and decrement the SV_POINTERLEVEL, but its value cannot become
     *            negative.
     * <dt><i>SV_PRINTSCREEN</i>
     *        <dd>TRUE when the Print Screen function is enabled; FALSE when the
     *            Print Screen function is disabled.
     * <dt><i>SV_SCROLLRATE</i>
     *        <dd>The delay (in milliseconds) between scroll operations, when
     *            using a scroll bar.
     * <dt><i>SV_SETLIGHTS</i>
     *        <dd>When TRUE, the appropriate light is set when the keyboard state
     *            table is set.
     * <dt><i>SV_SINGLESELECT</i>
     *        <dd>Mouse select (low word=mouse message id (WM_*), high word=keyboard
     *            control code (KC_*)).
     * <dt><i>SV_TASKLISTMOUSEACCESS</i>
     *        <dd>Determines whether the task list is displayed when mouse buttons 1
     *            and 2 are pressed simultaneously, or when mouse button 2 is pressed
     *            by itself, or for no mouse gesture.
     * <dt><i>SV_TEXTEDIT</i>
     *        <dd>Mouse begin direct name edit (low word=mouse message id (WM_*),
     *            high word=keyboard control code (KC_*)).
     * <dt><i>SV_TEXTEDITKB</i>
     *        <dd>Keyboard begin direct name edit (low word=virtual key code (VK_*),
     *            high word=keyboard control code (KC_*)).
     * <dt><i>SV_TRACKRECTLEVEL</i>
     *        <dd>The hide level of the tracking rectangle (zero if visible, greater
     *            than zero if not).
     * <dt><i>SV_SWAPBUTTON</i>
     *        <dd>TRUE if pointing device buttons are swapped. Normally, the pointing
     *            device buttons are set for right-handed use. Setting this value changes
     *            them for left-handed use.
     * <dt><i>SV_WARNINGDURATION</i>
     *        <dd>Duration for warning alarms generated by WinAlarm.
     * <dt><i>SV_WARNINGFREQ</i>
     *        <dd>Frequency for warning alarms generated by WinAlarm.
     * </dl>
     */

    static LONG metric( LONG id );

    /** Returns a current screen resolution. */
    static LONG dpi();

    /** Returns the current module handle. */
    static HMODULE module_handle();

    /**
     * Returns the current module name.
     *
     * @return The fully-qualified drive, path, file name, and extension
     *         of the current module.
     */

    static char* module_name( char* result, int size );

    /**
     * Returns the current program name.
     *
     * @return The fully-qualified drive, path, file name, and extension
     *         of the current executed application.
     */

    static char* program_name( char* result, int size );

    /**
     * Returns the current program startup path.
     *
     * @return The fully-qualified drive and path (including the
     *         trailing slash) of the directory out of which the
     *         current executed application is started.
     */

    static char* program_path( char* result, int size );

    /** Dispatches messages. */
    static void run();

  private:
    BOOL   m_wrapped;
    static HAB m_hab[PM_MAX_THREADS];
    static HMQ m_hmq[PM_MAX_THREADS];
};

#endif
