/*
 * Copyright (C) 2001-2008 Dmitry A.Steklenev
 *
 * $Id: pm_mutex.h,v 1.2 2011/03/11 12:59:32 glass Exp $
 */

#ifndef PM_MUTEX_H
#define PM_MUTEX_H

#include "pm_os2.h"
#include "pm_noncopyable.h"

/**
 * Serialize access to resources.
 *
 * A mutual exclusion class PMMutex protects resources
 * (such as files, data in memory, and peripheral devices) from
 * simultaneous access by several processes. Class also enable threads
 * to serialize their access to resources.
 *
 * None of the functions in this class throws exceptions because
 * an exception probably has been thrown already or is about
 * to be thrown.
 *
 * You can construct and destruct objects of this class.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.2 $
 */

class PMMutex : public PMNonCopyable
{
  public:
    /** Constructs the mutual exclusion object. */
    PMMutex();
    /** Destructs  the mutual exclusion object. */
   ~PMMutex();

    /**
     * Request access to resource.
     *
     * Requests ownership of a resource.
     * Blocks the calling thread indefinitely.
     *
     * @return TRUE, if ownership established.
     */

    BOOL request();

    /**
     * Request access to resource with wait timeout.
     *
     * Requests ownership of a resource.
     * Blocks the calling thread.
     *
     * @param  mseq   this is the maximum amount of time the
     *                user wants to allow the thread to be blocked.
     *
     * @return TRUE, if ownership established.
     */

    BOOL request( unsigned long msec );

    /**
     * Relinquishes ownership of a resource that was requested by
     * <i>request</i>.
     *
     * Only the thread that owns the resource can issue release().
     *
     * @return TRUE, if ownership relinquished.
     */

    BOOL release();

  private:

    HMTX m_handle;
};

#endif
