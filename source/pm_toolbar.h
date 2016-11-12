/*
 * Copyright (C) 2008-2012 Dmitry A.Steklenev
 *
 * $Id: pm_toolbar.h,v 1.10 2012/06/13 11:36:11 glass Exp $
 */

#ifndef PM_TOOLBAR_H
#define PM_TOOLBAR_H

#include "pm_os2.h"
#include "pm_window.h"
#include "pm_inittoolbar.h"
#include <etoolbar.h>

/**
 * Toolbar control window class.
 *
 * You can construct and destruct objects of this class.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.10 $
 */

class PMToolBar : public PMWindow
{
  public:

    /**
     * Wraps the toolbar control window object
     * around an existing presentation window handle.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     */

    PMToolBar( HWND handle );

    /**
     * Wraps the toolbar control window object around
     * an existing child window with the specified identity.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     *
     * @param hparent     Specifies the parent-window handle.
     * @param id          Specifies the identity of the child window.
     */

    PMToolBar( HWND hparent, SHORT id );

    /**
     * Constructs the toolbar control window.
     *
     * @param id          Specifies the window identifier.
     * @param hparent     Specifies the parent-window handle.
     * @param x,y,cx,cy   Specifies the window shape.
     * @param style       Specifies the window style.
     *                    @see PMWindow::PMWindow 2
     */

    PMToolBar( SHORT id, HWND hparent, LONG x, LONG y, LONG cx, LONG cy, ULONG style );

    /** Defines the picture size of the toolbar's buttons. */
    virtual void size( USHORT pixels );

    /**
     * Adds button into toolbar.
     *
     * @param id          Specifies the button identifier.
     * @param text        Button text at right side from picture (if present).
     * @param tooltip     Specifies the tooltip text.
     * @param res_id      Bitmap identity within the resource file.
     * @param menu_res_id Menu identity within the resource file, if menu should appear
     *                    on button press.
     * @param hmodule     Module handle referencing a dynamic link library
     *                    containing the resource or NULLHANDLE for the
     *                    application's module.
     */

    virtual void add_button( SHORT id, const char* text,
                                       const char* tooltip, SHORT res_id, SHORT menu_res_id, HMODULE hmodule );
    /**
     * Adds standard button into toolbar.
     *
     * @param id          Specifies the button identifier.
     * @param text        Button text at right side from picture (if present).
     * @param tooltip     Specifies the tooltip text.
     * @param ibmp        System bit-map index value.
     * @param fl          Flags that determine what bitmap is used:
     *                    <dl>
     *                    <dt>DBT_NORMAL
     *                    <dd>Use a bitmap of the normal size. This size is equivalent to the current icon size.
     *                    <dt>DBT_MINI
     *                    <dd>Use a mini-bitmap.
     *                    <dt>DBT_16
     *                    <dd>Use a bitmap at the size of 16x16 pixels.
     *                    <dt>DBT_20
     *                    <dd>Use a bitmap at the size of 20x20 pixels.
     *                    <dt>DBT_32
     *                    <dd>Use a bitmap at the size of 32x32 pixels.
     *                    <dt>DBT_40
     *                    <dd>Use a bitmap at the size of 40x40 pixels.
     *                    </dl>
     *
     * @param menu_res_id Menu identity within the resource file, if menu should appear
     *                    on button press.
     * @param hmodule     Module handle referencing a dynamic link library
     *                    containing the resource or NULLHANDLE for the
     *                    application's module.
     */

    virtual void add_standard_button( SHORT id, const char* text, const char* tooltip, LONG ibmp,
                                      ULONG fl, SHORT menu_res_id = 0, HMODULE hmodule = NULLHANDLE );
    /**
     * Adds separator into toolbar.
     */

    virtual void add_separator();

    /**
     * Adds control into toolbar.
     *
     * @param hwnd        Specifies the control window handle.
     * @param cx          Specifies the control window width.
     * @param cy          Specifies the control window height.
     * @param tooltip     Specifies the tooltip text.
     */

    virtual void add_control( HWND hwnd, SHORT cx, SHORT cy, const char* tooltip );

    /** Makes the buttons text visible. */
    virtual void show_text( BOOL show = TRUE );
    /** Makes the buttons text invisible. */
    virtual void hide_text();

    /**
     * Sets the state of the specified toolbar button to the enable.
     *
     * @param id          Specifies the button identifier.
     * @param state       Enable flag.
     */

    virtual void enable_button( SHORT id, BOOL state = TRUE );

    /**
     * Sets the state of the specified toolbar button to the disable.
     *
     * @param id          Specifies the button identifier.
     */

    virtual void disable_button( SHORT id );

    /**
     * Makes toolbar button checked or unchecked.
     *
     * @param id          Specifies the button identifier.
     * @param state       Check state.
     */

    virtual void check( SHORT id, BOOL state );

  private:
    /** Extracts tooltip text from a menu item text. */
    char* extract_tooltip( char* extracted, const char* text, int size );
};

#endif
