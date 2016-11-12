/*
 * Copyright (C) 2001-2008 Dmitry A.Steklenev
 *
 * $Id: pm_thread.h,v 1.7 2011/03/11 12:59:33 glass Exp $
 */

#ifndef PM_THREAD_H
#define PM_THREAD_H

#include "pm_os2.h"
#include "pm_notify.h"

/**
 * Thread class.
 *
 * The PMThread class represents threads of execution within
 * the current program. You can use this class to implement
 * multithreaded applications. Objects of this class give you
 * access to all of the tasking APIs of the operating system.
 * In addition, these objects can serve as the anchor for thread-specific
 * information.
 *
 * You can construct and destruct objects of this class.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.7 $
 */

class PMThread : public PMNonCopyable {

  public:

    /**
     * Constructs the thread object.
     *
     * Use this, the default constructor, to create an object of this
     * class without creating an additional thread of execution.
     * You can subsequently start execution of the thread using
     * <i>PMThread::start</i>.
     */

    PMThread();

    /**
     * Dealocates thread-related resources.
     *
     * When objects of this class are destructed, the thread is
     * not terminated. Deleting a running PMThread will probably
     * result in a program crash. You can <i>join</i> on a thread
     * to make sure that it has finished.
     *
     */

    virtual ~PMThread() {}

    /**
     * Obtains the identifier of the thread.
     *
     * @return A return value of -1 indicates that the thread is
     *         not started.
     */

    TID tid() const;

    /** Determines if this thread is currently active. */
    BOOL is_alive() const;
    /** This function causes the thread to start immediately. */
    void start();

    /**
     * Waits the thread.
     *
     * Places the current thread into a wait state until thread,
     * represented of the PMThread object, has ended.
     */

    void join();

    /**
     * Waits the GUI thread.
     *
     * This method then dispatches messages from the queue to
     * the appropriate window or dialog procedure until thread,
     * represented of the PMThread object, has ended.
     *
     * <b>Note:</b> This method must be called from the same thread
     * where the joined thread has been started.
     */

    void join_gui_thread();

    /**
     * Suspends the thread.
     *
     * Suspends the thread's execution, which can be undone later
     * with a call to <i>resume</i>. Note that <i>suspend</i> and <i>resume</i>
     * are not recommended mechanisms for thread control. Resources and
     * conditions provide safer services for managing threads.
     */

    void suspend();

    /**
     * Resumes the thread.
     *
     * Resumes a thread's execution after it has been suspended by a
     * call to <i>suspend</i>. Note that <i>suspend</i> and <i>resume</i>
     * are not recommended mechanisms for thread control. Resources and
     * conditions provide safer services for managing threads.
     */

    void resume();

    /**
     * Stops the thread.
     *
     * This function causes the thread to stop immediately, bypassing
     * some normal termination functions. Use it with extreme caution,
     * preferably when the state of the target thread is known.
     */

    void stop();

    /**
     * Changes the base priority of the thread.
     *
     * @param pclass  Priority class of a process. The values of this field are
     *                shown in the following list:
     * <dl>
     * <dt><i>PRTYC_NOCHANGE        </i><dd>No change, leave as is.
     * <dt><i>PRTYC_IDLETIME        </i><dd>Idle-time.
     * <dt><i>PRTYC_REGULAR         </i><dd>Regular.
     * <dt><i>PRTYC_TIMECRITICAL    </i><dd>Time-critical.
     * <dt><i>PRTYC_FOREGROUNDSERVER</i><dd>Fixed high.
     * </dl>
     *
     * @param pdelta  Change to apply to the current base priority level of the process.
     *                This value must range from -31 (PRTYD_MINIMUM) to +31 (PRTYD_MAXIMUM).
     */

    void priority( ULONG pclass, LONG pdelta );

    /**
     * Returns this thread's stack size.
     *
     * Obtains this thread's stack size in bytes. If it was set when
     * the thread was running, it might not reflect the size of the
     * currently running thread. It only takes affect the next time
     * the thread is started.
     */

    unsigned long stack_size() const;

    /**
     * Sets this thread's stack size.
     *
     * Sets this thread's stack size in bytes. If you have already
     * started the thread, this value takes effect only when the thread
     * is stopped and restarted.
     */

    void stack_size( unsigned long size );

  protected:

    /**
     * Thread function.
     *
     * You must overwrite this method. Note, that the thread function
     * does not take any arguments. Instead, you should define data
     * members and initialise these before you start the thread.
     */

    virtual void operator()() = 0;

  private:

    HMQ      m_hmq;
    TID      m_tid;
    PMNotify m_started;
    HMTX     m_guard;
    unsigned long m_stack_size;
    ULONG    m_pclass;
    LONG     m_pdelta;

    static void launch( PMThread* );
};

/* Returns this thread's stack size
 */

inline unsigned long PMThread::stack_size() const {
  return m_stack_size;
}

/* Sets this thread's stack size
 */

inline void PMThread::stack_size( unsigned long size ) {
  m_stack_size = size;
}

/* Obtains the identifier of the thread
 */

inline TID PMThread::tid() const {
  return m_tid;
}

#endif
