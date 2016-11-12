/*
 * Copyright (C) 2001-2008 Dmitry A.Steklenev
 *
 * $Id: pm_noncopyable.h,v 1.2 2011/03/11 12:59:32 glass Exp $
 */

#ifndef PM_NONCOPYABLE_H
#define PM_NONCOPYABLE_H

#include "pm_os2.h"

/**
 * Prohibit copy construction and copy assignment.
 *
 * Class noncopyable is a base class. Derive your own class from
 * noncopyable when you want to prohibit copy construction and
 * copy assignment.
 * 
 * Some objects, particularly those which hold complex resources like
 * files or network connections, have no sensible copy semantics.
 * Sometimes there are possible copy semantics, but these would be
 * of very limited usefulness and be very difficult to implement
 * correctly.  Sometimes you're implementing a class that doesn't
 * need to be copied just yet and you don't want to take the time
 * to write the appropriate functions. Deriving from noncopyable
 * will prevent the otherwise implicitly-generated functions
 * (which don't have the proper semantics) from becoming a
 * trap for other programmers.
 * 
 * The traditional way to deal with these is to declare a private
 * copy constructor and copy assignment, and then document why this
 * is done. But deriving from noncopyable is simpler and
 * clearer, and doesn't require additional documentation.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.2 $
 */

class PMNonCopyable
{
  public:
    /** Constructs the noncopyable object. */
    PMNonCopyable() {}

  private:
    PMNonCopyable( const PMNonCopyable& );
    PMNonCopyable& operator=( const PMNonCopyable& );
};

#endif
