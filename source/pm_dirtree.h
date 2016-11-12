/*
 * Copyright (C) 2010 Dmitry A.Steklenev
 *
 * $Id: pm_dirtree.h,v 1.5 2011/03/11 12:59:31 glass Exp $
 */

#ifndef PM_DIRTREE_H
#define PM_DIRTREE_H

#include "pm_os2.h"
#include "pm_window.h"
#include "pm_initfoc.h"

/**
 * Directory tree control window class.
 *
 * A Directory Tree container control is a visual component
 * that holds a tree of drives and directories. It provides a
 * powerful and flexible component for easily developing products
 * that conform to the Common User Access (CUA) user interface
 * guidelines.
 *
 * You can construct and destruct objects of this class.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.5 $
 */

class PMDirTree : public PMWindow
{
  public:

    /**
     * Wraps the directory tree control window object around
     * an existing presentation window handle.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     */

    PMDirTree( HWND handle );

    /**
     * Wraps the directory tree control window object around
     * an existing child window with the specified identifier.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     *
     * @param hparent     Specifies the parent-window handle.
     * @param id          Specifies the identity of the child window.
     */

    PMDirTree( HWND hparent, SHORT id );

    /**
     * Constructs the directory tree control window.
     *
     * @param id          Specifies the window identifier.
     * @param hparent     Specifies the parent-window handle.
     * @param x,y,cx,cy   Specifies the window shape.
     * @param style       Specifies the window style:
     *
     * <dl>
     * <dt><i>DTS_BORDER    </i><dd>Draws a border around the directory tree container.
     * <dt><i>DTS_READONLY  </i><dd>A read-only style bit for an entire directory tree
     *                              container, which prevents a user from renaming, deleting
     *                              or creating any of the directory in a container window.
     * <dt><i>DTS_SHOWALL   </i><dd>Shows all directories, including hidden and system.
     * <dt><i>DTS_TITLE     </i><dd>Allows you to include a directory tree container title.
     * <dt><i>DTS_TREE      </i><dd>The tree view displays items arranged hierarchically. This is
     *                              the default view.
     * <dt><i>DTS_CHECKED   </i><dd>The checked view is similar to a tree view, but at each item
     *                              is a check box that can be turned on or off.
     * </dl>
     *
     * @see PMWindow::PMWindow 2
     */

    PMDirTree( SHORT id, HWND hparent, LONG x, LONG y, LONG cx, LONG cy, ULONG style );

    /**
     * Assigns co-operating file view container.
     *
     * @param hfileview   Handle of the file view container control. All changes made with
     *                    a directory tree will be reflected in this files view container.
     *
     * @return            The files view container handle which has been attached before.
     */

    virtual HWND attach_fileview( HWND hfileview );

    /**
     * Returns the name of the selected directory.
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
     * Refreshes a specified part of the directory tree.
     *
     * @param directory   Address of the fully qualified path name of the subdirectory
     *                    to be refreshed. You can use an empty string ("") to refresh
     *                    whole directory tree.
     */

    virtual void refresh( const char* directory );

    /**
     * Iterator class used to iterate through checked files or
     * directories.
     *
     * @author  Dmitry A.Steklenev
     * @version $Revision: 1.5 $
     */

    class iterator : public PMNonCopyable
    {
      friend class PMDirTree;

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

        /** Repositions the iterator to the first checked file. */
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
     * This object can be used to iterate through checked files or
     * directories and must be deleted after usage.
     *
     * <b>Note:</b> The first character of each item is a check mark
     * status where '+' means "checked".
     */

    virtual iterator* checked();
};

#endif
