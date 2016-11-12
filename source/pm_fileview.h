/*
 * Copyright (C) 2010 Dmitry A.Steklenev
 *
 * $Id: pm_fileview.h,v 1.5 2011/03/11 12:59:31 glass Exp $
 */

#ifndef PM_FILEVIEW_H
#define PM_FILEVIEW_H

#include "pm_os2.h"
#include "pm_window.h"
#include "pm_initfoc.h"

/**
 * File view control window class.
 *
 * A File View control is a visual component that holds an
 * information about drives, files and directories. It provides
 * a powerful and flexible component for easily developing products
 * that conform to the Common User Access (CUA) user interface
 * guidelines.
 *
 * You can construct and destruct objects of this class.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.5 $
 */

class PMFileView : public PMWindow
{
  public:

    /**
     * Wraps the file view control window object around
     * an existing presentation window handle.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     */

    PMFileView( HWND handle );

    /**
     * Wraps the file view control window object around
     * an existing child window with the specified identifier.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     *
     * @param hparent     Specifies the parent-window handle.
     * @param id          Specifies the identity of the child window.
     */

    PMFileView( HWND hparent, SHORT id );

    /**
     * Constructs the file view control window.
     *
     * @param id          Specifies the window identifier.
     * @param hparent     Specifies the parent-window handle.
     * @param x,y,cx,cy   Specifies the window shape.
     * @param style       Specifies the window style:
     *
     * <dl>
     * <dt><i>FVS_BORDER     </i><dd>Draws a border around the file view container.
     * <dt><i>FVS_READONLY   </i><dd>A read-only style bit for an entire file view container,
     *                               which prevents a user from renaming, deleting or creating
     *                               any of the directory or file in a container window.
     * <dt><i>FVS_SHOWALL    </i><dd>Shows all files, including hidden and system.
     * <dt><i>FVS_SHOWDIRS   </i><dd>Shows list of directories on top of file view.
     * <dt><i>FVS_SHOWDOTS   </i><dd>Places to each file view a link to a parent directory
     *                               (".."). This style is ignored if FVS_SHOWDIRS is not
     *                               specified.
     * <dt><i>FVS_TITLE      </i><dd>Allows you to include a file view container title.
     * <dt><i>FVS_SINGLESEL  </i><dd>Single selection, which allows a user to select only one
     *                               container item at a time. Each time a user selects a
     *                               container item, the selection of any other container item is
     *                               cancelled.
     * <dt><i>FVS_EXTENDSEL  </i><dd>Extended selection, which allows a user to select one or
     *                               more container items. A user can select one item, a range of
     *                               items, or multiple ranges of items.
     * <dt><i>FVS_MULTIPLESEL</i><dd>Multiple selection, which allows a user to select zero or
     *                               more container items.
     * <dt><i>FVS_ICON       </i><dd>In the icon view, the file view items are represented as
     *                               icon/text pairs, with text beneath the icons.
     * <dt><i>FVS_DETAIL     </i><dd>In the details view, the file view items are presented in
     *                               columns. Each column can contain icons, file names, sizes,
     *                               dates and times. This is the default view.
     * <dt><i>FVS_CHECKED    </i><dd>The checked view is similar to a details view, but has an
     *                               additional column with check boxes that can be turned on or
     *                               off.
     * </dl>
     *
     * @see PMWindow::PMWindow 2
     */

    PMFileView( SHORT id, HWND hparent, LONG x, LONG y, LONG cx, LONG cy, ULONG style );

    /**
     * Assigns co-operating directory tree container.
     *
     * @param hdirtree  Handle of the directory tree container control. All changes made with
     *                  a file view will be reflected in this directory tree container.
     *
     * @return          The directory tree container handle which has been attached before.
     */

    virtual HWND attach_dirtree( HWND hdirtree );

    /**
     * Returns the name of the current selected directory.
     *
     * @param result  Buffer into which the directory name is to be copied.
     * @param size    Copy the directory name as a null-terminated string, but
     *                limit the number of characters copied, including the null
     *                termination character, to this value.
     */

    virtual char* curdir( char* result, int size ) const;

    /**
     * Selects the specified directory.
     *
     * @param directory   Address of the fully qualified path name of the subdirectory
     *                    to be selected. You can use an empty string ("") to select a
     *                    root of the directory tree.
     */

    virtual void chdir( const char* directory );

    /**
     * Returns position of the split bar relative to the container
     * used in the details view.
     */

    virtual LONG splitbar() const;

    /**
     * Sets the position of the split bar relative to the container
     * used in the details view.
     */

    virtual void splitbar( LONG x );

    /**
     * Sorts the file view items.
     *
     * @param order   Sorting order.
     *
     * <dl>
     * <dt><i>FVA_NONE</i><dd>Unsorted.
     * <dt><i>FVA_NAME</i><dd>The file view items are sorted by file name.
     * <dt><i>FVA_SIZE</i><dd>The file view items are sorted by file size.
     * <dt><i>FVA_TIME</i><dd>The file view items are sorted by the last write date and time.
     * </dl>
     */

    virtual void sort( ULONG order );

    /** Refreshes a current selected directory. */
    virtual void refresh();

    /**
     * Iterator class used to iterate through selected files or
     * directories.
     *
     * @author  Dmitry A.Steklenev
     * @version $Revision: 1.5 $
     */

    class iterator : public PMNonCopyable
    {
      friend class PMFileView;

      public:

        /** Destructs the iterator object. */
       ~iterator();

        /**
         * Returns the next selected file or directory.
         *
         * @param pathname  A buffer in which the selected name is returned.
         * @param size      This is the size of the buffer specified by the pathname parameter.
         *
         * @return  Success indicator.
         */

        BOOL next( char* pathname, int size );

        /** Repositions the iterator to the first selected file. */
        void rewind() { m_next = 0; }

      private:
        /** Constructs the iterator object. */
        iterator( FILELIST* pfilelist );

        int    m_count;
        int    m_next;
        char** m_array;
    };

    /**
     * Returns a pointer to the iterator object.
     *
     * This object can be used to iterate through selected files or
     * directories and must be deleted after usage.
     */

    virtual iterator* selected();

    /**
     * Returns a pointer to the iterator object.
     *
     * This object can be used to iterate through checked files or
     * directories and must be deleted after usage.
     *
     * <b>Note:</b> The first character of each item is a check mark
     * status where '+' means "checked".
     */

    virtual iterator* checked();
};

#endif
