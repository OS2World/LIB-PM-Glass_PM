/*
 * Copyright (C) 2006-2010 Dmitry A.Steklenev
 *
 * $Id: pm_delete.h,v 1.2 2011/03/11 12:59:31 glass Exp $
 */

#ifndef PM_DELETE_H
#define PM_DELETE_H

#include "pm_os2.h"

/**
 * Deletes a C++ object.
 *
 * The PMDelete&lt;T&gt; is a function object. Specifically, it is an Adaptable
 * Binary Function. If f is an object of class GLDelete&lt;T&gt; and p are pointer
 * to object of class T, then f(p) caused delete p.
 *
 * @author  Dmitry A Steklenev
 * @version $Revision: 1.2 $
 */

template <class T> class PMDelete
{
  public:

    /** Deletes a C++ object. */
    void operator()( T* p ) const {
      delete p;
    }
};

/**
 * Deletes a C++ array of objects.
 *
 * The PMDeleteArray&lt;T&gt; is a function object. Specifically, it is an Adaptable
 * Binary Function. If f is an object of class PMDeleteArray&lt;T&gt; and p are pointer
 * to array of objects of class T, then f(p) caused delete[] p.
 *
 * @author  Dmitry A Steklenev
 * @version $Revision: 1.2 $
 */

template <class T> class PMDeleteArray
{
  public:

    /** Deletes a C++ array of objects. */
    void operator()( T* p ) const {
      delete[] p;
    }
};

/**
 * Frees a memory block of storage.
 *
 * The PMFree&lt;T&gt; is a function object. Specifically, it is an Adaptable
 * Binary Function. If f is an object of class PMFree&lt;T&gt; and p are pointer
 * to a memory block previously reserved with a call to one of the memory
 * allocation functions, then f(p) caused free(p).
 *
 * @author  Dmitry A Steklenev
 * @version $Revision: 1.2 $
 */

template <class T> class PMFree
{
  public:

    /** Frees a memory block of storage. */
    void operator()( T* p ) const {
      free( p );
    }
};

#endif
