/*
 * Copyright (C) 2001-2011 Dmitry A.Steklenev
 *
 * $Id: pm_thread.cpp,v 1.9 2011/06/29 13:39:25 glass Exp $
 */

#include <stdlib.h>
#include <process.h>

#include "pm_thread.h"
#include "pm_gui.h"
#include "pm_error.h"

/* Constructs the thread object.
 *
 * Use this, the default constructor, to create an object of this
 * class without creating an additional thread of execution.
 * You can subsequently start execution of the thread using
 * PMThread::start.
 */

PMThread::PMThread()
: m_tid       ( -1             ),
  m_stack_size( 256 * 1024     ),
  m_hmq       ( PMGUI::hmq()   ),
  m_guard     ( NULLHANDLE     ),
  m_pclass    ( PRTYC_NOCHANGE ),
  m_pdelta    ( 0              )
{}

/* Thread launching routine.
 */

void PMThread::launch( PMThread* runit )
{
  PMGUI initialize;

  DosCreateMutexSem( NULL, &runit->m_guard, 0, TRUE );
  runit->m_started.post();

  (*runit)();

  DosCloseMutexSem( runit->m_guard );
  runit->m_guard = NULLHANDLE;
  runit->m_tid   = -1;

  WinPostQueueMsg( runit->m_hmq, PM_THREAD_END, MPFROMP( runit ), 0 );
}

/* Determines if this thread is currently active.
 */

BOOL PMThread::is_alive() const
{
  PID   owner_pid;
  TID   owner_tid;
  ULONG count;

  // If thread is killed, the DosQueryMutexSem must return ERROR_SEM_OWNER_DIED or
  // ownership must be transfered to the thread one.

  return ( m_guard != NULLHANDLE &&
           DosQueryMutexSem( m_guard, &owner_pid, &owner_tid, &count ) == NO_ERROR &&
           owner_tid == m_tid );
}

/* This function causes the thread to start immediately.
 */

void PMThread::start()
{
  if( !is_alive()) {
    m_started.reset();
    m_tid = _beginthread(( void (*)(void*))launch, NULL, m_stack_size, this );

    if( m_tid == -1 ) {
      PM_THROW_CLIBERROR();
    }

    if( m_pclass != PRTYC_NOCHANGE ) {
      DosSetPriority( PRTYS_THREAD, m_pclass, m_pdelta, m_tid );
    }

    m_started.wait();
  }
}

/* Stops the thread.
 *
 * This function causes the thread to stop immediately, bypassing
 * some normal termination functions. Use it with extreme caution,
 * preferably when the state of the target thread is known.
 */

void PMThread::stop()
{
  if( is_alive())
  {
    APIRET rc = DosKillThread( tid());

    if( rc != NO_ERROR && rc != ERROR_INVALID_THREADID ) {
      PM_THROW_DOSERROR( rc );
    }

    m_tid = -1;
  }
}

/* Waits the thread.
 *
 * Places the current thread into a wait state until thread,
 * represented of the PMThread object, has ended.
 */

void PMThread::join()
{
  if( is_alive()) {
    DosWaitThread( &m_tid, DCWW_WAIT );
  }
}

/* Waits the GUI thread.
 *
 * This method then dispatches messages from the queue to
 * the appropriate window or dialog procedure until thread,
 * represented of the PMThread object, has ended.
 *
 * Note: This method must be called from the same thread
 * where the joined thread has been started.
 */

void PMThread::join_gui_thread()
{
  if( is_alive())
  {
    QMSG qms;
    HAB  hab = PMGUI::hab();

    while( WinGetMsg( hab, &qms, 0, 0, 0 )) {
      if(( qms.msg == PM_THREAD_END && LONGFROMMP( qms.mp1 ) == (LONG)this ) || !is_alive()) {
        break;
      }
      WinDispatchMsg( hab, &qms );
    }
  }
}

/* Suspends the thread.
 *
 * Suspends the thread's execution, which can be undone later
 * with a call to resume. Note that suspend and resume
 * are not recommended mechanisms for thread control. Resources and
 * conditions provide safer services for managing threads.
 */

void PMThread::suspend()
{
  if( is_alive())
  {
    APIRET rc = DosSuspendThread( m_tid );

    if( rc != NO_ERROR ) {
      PM_THROW_DOSERROR( rc );
    }
  }
}

/* Resumes the thread.
 *
 * Resumes a thread's execution after it has been suspended by a
 * call to suspend. Note that suspend and resume are not
 * recommended mechanisms for thread control. Resources and
 * conditions provide safer services for managing threads.
 */

void PMThread::resume()
{
  if( is_alive())
  {
    APIRET rc = DosResumeThread( m_tid );

    if( rc != NO_ERROR && rc != ERROR_NOT_FROZEN ) {
      PM_THROW_DOSERROR( rc );
    }
  }
}

/* Changes the base priority of the thread.
 */

void PMThread::priority( ULONG pclass, LONG pdelta )
{
  m_pclass = pclass;
  m_pdelta = pdelta;

  if( is_alive()) {
    if( m_pclass != PRTYC_NOCHANGE ) {
      DosSetPriority( PRTYS_THREAD, m_pclass, m_pdelta, m_tid );
    }
  }
}

