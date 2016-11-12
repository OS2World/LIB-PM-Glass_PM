/*
 * Copyright (C) 2001-2010 Dmitry A.Steklenev
 *
 * $Id: pm_filedialog.h,v 1.12 2012/04/24 11:21:38 glass Exp $
 */

#ifndef PM_FILEDIALOG_H
#define PM_FILEDIALOG_H

#include "pm_os2.h"
#include "pm_noncopyable.h"
#include <foc.h>

#pragma library( "foc.lib" )

/**
 * File dialog class.
 *
 * The file dialog class creates a file dialog object for the user
 * to choose a file. Once the user has chosen a file, you can use
 * member functions of this class to retrieve information about
 * the chosen file.
 *
 * You can construct and destruct objects of this class.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.12 $
 */

class PMFileDialog : public PMNonCopyable
{
  public:

    /**
     * Constructs the file dialog object.
     *
     * This constructor create file dialog object. You must use <i>show_modally</i>
     * to activate it.
     *
     * @param caption  The dialog window title
     * @param howner   Specifies the owner-window handle.
     * @param filename The file name to use as the default. If you
     *                 want to specify global (or wildcard) characters
     *                 or path information for the dialog defaults,
     *                 include this information in this parameter's string.
     *                 If you do not specify the path with the file name,
     *                 the current directory is used.
     * @param style    Specifies the dialog style:
     *
     * <dl>
     * <dt><i>FDS_CENTER         </i><dd>The dialog is positioned in the center of
     *                                   its owner window.
     * <dt><i>FDS_ENABLEFILELB   </i><dd>When this flag is set, the Files list box
     *                                   on a Save As dialog is enabled.
     * <dt><i>FDS_MULTIPLESEL    </i><dd>When this flag is set, the Files list box
     *                                   for the dialog is a multiple selection list
     *                                   box. When this flag is not set, the default
     *                                   is a single-selection list box.
     * <dt><i>FDS_OPEN_DIALOG    </i><dd>The dialog is an "Open" dialog when this flag is set.
     * <dt><i>FDS_SAVEAS_DIALOG  </i><dd>The dialog is a "Save As" dialog when this flag is set.
     * <dt><i>FDS_TRANSLATE      </i><dd>Translates the dialog texts using for this purpose
     *                                   the current {@link PMLanguage::instance instance} of the
     *                                   messages management object.
     * </dl>
     */

    PMFileDialog( const char* caption, HWND howner, const char* filename, ULONG style );

    /**
     * Destructs the file dialog object.
     *
     * Cleans up as this dialog object and destroying the
     * associated presentation window for this object.
     */

    virtual ~PMFileDialog();

    /**
     * Displays the file dialog.
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
     * Adds the specified type to the drop-down list box.
     *
     * @param filetype The file type description.
     * @param filter   The file filter for the type description. If multiple wildcards are
     *                 specified, then they must be separated by a semicolon.
     * @param initial  The file filter is applied to the initial dialog screen.
     */

    virtual void add_filetype( const char* filetype, const char* filter, BOOL initial = FALSE );

    /**
     * Returns a selected file type to assign to the file name returned.
     *
     * @return A zero-based index of selected type. A -1 value is returned when
     *         &lt;All Files&gt; filter is used.
     */

    virtual int filetype() const;

    /** Returns the presentation window handle. */
    HWND  handle() const { return m_handle; }

    /**
     * Iterator class used to iterate through chosen files.
     *
     * @author  Dmitry A.Steklenev
     * @version $Revision: 1.12 $
     */

    class iterator : public PMNonCopyable
    {
      friend class PMFileDialog;

      public:

        /** Destructs the iterator object. */
       ~iterator();

        /**
         * Returns the next chosen file.
         *
         * @param pathname  A buffer in which the selected name is returned.
         * @param size      This is the size of the buffer specified by the pathname parameter.
         *
         * @return  Success indicator.
         */

        BOOL next( char* pathname, int size );

        /** Repositions the iterator to the first chosen file. */
        void rewind() { m_next = 0; }

      private:
        /** Constructs the iterator object. */
        iterator( PFOCFILEDLG pfiledlg );

        int    m_count;
        int    m_next;
        char** m_array;
    };

    /**
     * Returns a pointer to the iterator object.
     *
     * This object can be used to iterate through chosen files
     * and must be deleted after usage.
     */

    virtual iterator* selected();

  private:

    FOCFILEDLG m_filedlg;

    APSZ* m_types;
    int   m_types_count;
    HWND  m_owner;
    HWND  m_handle;
    int   m_next;
    int   m_initial;
};

#endif
