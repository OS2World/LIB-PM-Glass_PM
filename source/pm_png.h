/*
 * Copyright (C) 2009-2010 Dmitry A.Steklenev
 *
 * $Id: pm_png.h,v 1.5 2011/03/11 13:23:22 glass Exp $
 */

#ifndef PM_PNG_H
#define PM_PNG_H

#include "pm_os2.h"
#include "pm_window.h"
#include <ecomedia.h>

#pragma library( "ecomedia.lib" )

/**
 * Static PNG image.
 *
 * The PMPNG class creates and manages a window to display
 * a PNG image.
 *
 * You can construct and destruct objects of this class.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.5 $
 */

class PMPNG : public PMWindow
{
  public:

    /**
     * Wraps the static image control window object around
     * an existing presentation window handle.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     */

    PMPNG( HWND handle );

    /**
     * Wraps the static image control window object around
     * an existing child window with the specified identity.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     *
     * @param hparent     Specifies the parent-window handle.
     * @param id          Specifies the identity of the child window.
     */

    PMPNG( HWND hparent, SHORT id );

    /**
     * Constructs the static image control window.
     *
     * @param id          Specifies the window identifier.
     * @param hparent     Specifies the parent-window handle.
     * @param x,y,cx,cy   Specifies the window shape.
     * @param res_id      Image identity within the resource file.
     * @param hmodule     Module handle referencing a dynamic link library containing
     *                    the resource or NULLHANDLE for the application's module.
     * @param style       Specifies the window style:
     *
     * <dl>
     * <dt><i>DT_LEFT     </i><dd>Left-justified image.
     * <dt><i>DT_CENTER   </i><dd>Centered image.
     * <dt><i>DT_RIGHT    </i><dd>Right-justified image.
     * <dt><i>DT_TOP      </i><dd>Image is aligned to top of window.
     * <dt><i>DT_VCENTER  </i><dd>Image is aligned vertically in center of window.
     * <dt><i>DT_BOTTOM   </i><dd>Image is aligned to bottom of window.
     * <dt><i>SS_AUTOSIZE </i><dd>The image control will be sized to make sure the
     *                            contents fit.
     * </dl>
     *
     * @see PMWindow::PMWindow   2
     */

    PMPNG( SHORT id, HWND hparent, LONG x, LONG y, LONG cx, LONG cy,
                                   SHORT res_id, HMODULE hmodule, ULONG style );
    /**
     * Destructs the static image control window.
     */

    virtual ~PMPNG();

    /**
     * Sets the image.
     *
     * @param res_id      Image identity within the resource file.
     * @param hmodule     Module handle referencing a dynamic link library containing
     *                    the resource or NULLHANDLE for the application's module.
     */

    virtual void image( SHORT res_id, HMODULE hmodule );

    /**
     * Sets an animation sequence.
     *
     * @param res_id      Identity of a first image within the resource file.
     * @param hmodule     Module handle referencing a dynamic link library containing
     *                    the resource or NULLHANDLE for the application's module.
     * @param count       Count of images which must be animated.
     * @param ms          Milliseconds to pause after each displayed image.
     */

    virtual void animate( SHORT res_id, HMODULE hmodule, SHORT count, ULONG ms );

  protected:

    /**
     * Dispatch system native events.
     *
     * This method is called when a system native window
     * event occurs.
     */

    virtual MRESULT dispatch( ULONG msg, MPARAM mp1, MPARAM mp2 );

  private:

    BOOL      m_phbm2_owner;
    HBITMAP2* m_phbm2;
    ULONG     m_count;
    ULONG     m_phase;
};

#endif
