/*
 * Copyright (C) 2009 Dmitry A.Steklenev
 *
 * $Id: pm_helpwindow.h,v 1.5 2011/03/11 12:59:32 glass Exp $
 */

#ifndef PM_HELPWINDOW_H
#define PM_HELPWINDOW_H

#include "pm_os2.h"
#include "pm_noncopyable.h"

/**
 * Help window class.
 *
 * The PMHelpWindow class provides help for application windows. Typically,
 * you create a PMHelpWindow object and associate it with the primary windows
 * of your application. Multiple help windows can also exist within an
 * application.
 *
 * You can construct and destruct objects of this class.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.5 $
 */

class PMHelpWindow : public PMNonCopyable
{
  public:

    /**
     * Constructs the help window object.
     *
     * @param res_id  Resource identifier for a help table resource.
     * @param title   Window title for the main help window of this help instance.
     * @param library A help library to use by IPF. IPF searches these help library
     *                for the help panels that it displays.
     */

    PMHelpWindow( SHORT res_id, const char* title, const char* library = NULL );

    /**
     * Wraps the help window object around an existing
     * associated application window.
     */

    PMHelpWindow( HWND hwnd );

    /**
     * Destructs the help window object.
     */

    virtual ~PMHelpWindow();

    /** Associates the help window with the specified application window. */
    virtual void attach( HWND hwnd );
    /** Disassociates the help window from a window. */
    virtual void detach();

    /** Identifies a help window library name. */
    virtual void library( const char* filename );
    /** Tells the help manager to display a specific help window. */
    virtual void show( SHORT res_id );

  private:
    HWND m_handle;
    HWND m_owner;
    BOOL m_wrapped;
};

#endif
