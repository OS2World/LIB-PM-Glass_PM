/*
 * Copyright (C) 2010 Dmitry A.Steklenev
 *
 * $Id: pm_selectdir.h,v 1.5 2011/03/11 13:23:22 glass Exp $
 */

#ifndef PM_SELECTDIR_FOC_H
#define PM_SELECTDIR_FOC_H

#include "pm_os2.h"
#include "pm_noncopyable.h"
#include <foc.h>

#pragma library( "foc.lib" )

/**
 * Directory selection dialog class.
 *
 * The directory selection dialog class creates a directory selection
 * dialog object for the user to choose a directory. Once the user has
 * chosen a directory, you can use member functions of this class to
 * retrieve information about the chosen directory.
 *
 * You can construct and destruct objects of this class.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.5 $
 */

class PMSelectDir : public PMNonCopyable
{
  public:

    /**
     * Constructs the directory selection dialog object.
     *
     * This constructor create directory selection dialog object.
     * You must use <i>show_modally</i> to activate it.
     *
     * @param caption  The dialog window title
     * @param howner   Specifies the owner-window handle.
     * @param pathname The directory name to use as the default.
     * @param style    Specifies the dialog style:
     *
     * <dl>
     * <dt><i>FDS_CENTER  </i><dd>The dialog is positioned in the center of
     *                            its owner window.
     * </dl>
     */

    PMSelectDir( const char* caption, HWND howner, const char* pathname, ULONG style );

    /**
     * Destructs the directory selection dialog object.
     *
     * Cleans up as this dialog object and destroying the
     * associated presentation window for this object.
     */

    virtual ~PMSelectDir();

    /**
     * Displays the directory selection dialog.
     *
     * While the dialog window is being shown modally, its parent or owner or
     * both windows are disabled. Other top level windows belonging to the
     * application are not disabled.
     *
     * @return Result code from dialog dismissal. This field contains the
     *         ID of the push button pressed to dismiss the dialog, DID_OK
     *         or DID_CANCEL. If an error occurs on dialog invocation,
     *         this value is set to zero.
     */

    virtual ULONG show_modally();

    /**
     * Returns the chosen directory.
     *
     * @param   filename  A buffer in which the chosen directory name is returned.
     * @param   size      This is the size of the buffer specified by
     *                    the <i>filename</i> parameter.
     *
     * @return  Success indicator.
     */

    virtual BOOL selected( char* pathname, int size );

    /** Returns the presentation window handle. */
    HWND handle() const { return m_handle; }

  private:

    FOCSELDIR m_seldir;

    HWND  m_owner;
    HWND  m_handle;
};

#endif
