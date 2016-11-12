/*
 * Copyright (C) 2010 Dmitry A.Steklenev
 *
 * $Id: pm_windowset.h,v 1.2 2011/03/11 12:59:33 glass Exp $
 */

#ifndef PM_WINDOWSET_H
#define PM_WINDOWSET_H

#include "pm_os2.h"
#include "pm_initwindowset.h"

#ifndef PM_MAX_WINDOWS

/**
 * Sets the maximum number of the wrapped windows (that is
 * not created inside this library) supported by the
 * library.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.2 $
 */

#define PM_MAX_WINDOWS 150
#endif

/**
 * Windows set class.
 *
 * This is an internal class type, used by other library classes.
 * You should not attempt to use it directly.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.2 $
 */

class PMWindowSet : public PMNonCopyable
{
  friend class PMInitWindowSet;

  public:

    /** Inserts a new window object to the windows set. */
    static void insert( HWND hwnd, class PMWindow* window );
    /** Removes a window object from the windows set. */
    static void remove( HWND hwnd );
    /** Queries a window object. */
    static class PMWindow* query( HWND hwnd );

  private:

    struct map {
      HWND            handle;
      class PMWindow* window;
    };

    static HMTX m_mutex;
    static map  m_map[PM_MAX_WINDOWS];
};

#endif
