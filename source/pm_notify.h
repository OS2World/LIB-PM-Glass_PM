/*
 * Copyright (C) 2001-2008 Dmitry A.Steklenev
 *
 * $Id: pm_notify.h,v 1.2 2011/03/11 12:59:32 glass Exp $
 */

#ifndef PM_NOTIFY_H
#define PM_NOTIFY_H

#include "pm_os2.h"
#include "pm_noncopyable.h"

/**
 * Notify another thread.
 *
 * An application can use an notify object to trigger execution of
 * other threads. This is useful if, for example, one thread
 * provides data to many other threads. Using an notify object frees
 * the other threads from the trouble of polling to determine when
 * new data is available.
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

class PMNotify : public PMNonCopyable
{
  public:
    /** Constructs the notify object. */
    PMNotify();
    /** Destructs  the notify object. */
   ~PMNotify();

    /**
     * Posts the notify.
     *
     * Causing all of the threads that were blocked on
     * <i>wait</i> requests for that object to execute.
     *
     * @return TRUE, if notify posted.
     */

    BOOL post();

    /**
     * Waits the notify.
     *
     * Enables a thread to wait for an notify to be posted.
     *
     * @return TRUE, if notify received.
     */

    BOOL wait() const;

    /**
     * Waits the notify with timeout.
     *
     * Enables a thread to wait for an notify to be posted.
     *
     * @param  mseq This is the maximum amount of time the
     *              user wants to allow the thread to be blocked.
     * @return TRUE, if notify received.
     */

    BOOL wait( unsigned long msec ) const;

    /**
     * Resets the notify.
     *
     * Resets an object, causing all threads that subsequently call
     * <i>wait</i> to be blocked.
     *
     * @return TRUE, if resets succesfull.
     */

    BOOL reset();

  private:

    HEV m_handle;
};

#endif
