/*
 * Copyright (C) 2001-2008 Dmitry A.Steklenev
 *
 * $Id: pm_notify.cpp,v 1.3 2011/03/11 12:59:32 glass Exp $
 */

#include "pm_notify.h"

/* Constructs the notify object.
 */

PMNotify::PMNotify() {
  DosCreateEventSem( NULL, &m_handle, 0, 0 );
}

/* Destructs the notify object.
 */

PMNotify::~PMNotify() {
  DosCloseEventSem( m_handle );
}

/* Posts the notify.
 *
 * Causing all of the threads that were blocked on
 * wait requests for that object to execute.
 */

BOOL PMNotify::post()
{
  APIRET rc = DosPostEventSem( m_handle );

  return ( rc == NO_ERROR             ||
           rc == ERROR_ALREADY_POSTED ||
           rc == ERROR_TOO_MANY_POSTS  );
}

/* Waits the notify.
 *
 * Enables a thread to wait for an notify to be posted.
 */

BOOL PMNotify::wait() const {
  return !WinWaitEventSem( m_handle, SEM_INDEFINITE_WAIT );
}

/* Waits the notify with timeout.
 *
 * Enables a thread to wait for an notify to be posted.
 */

BOOL PMNotify::wait( unsigned long msec ) const {
  return !WinWaitEventSem( m_handle, msec );
}

/* Resets the notify.
 *
 * Resets an object, causing all threads that subsequently call
 * wait to be blocked.
 */

BOOL PMNotify::reset()
{
  ULONG  post_count;
  APIRET rc = DosResetEventSem( m_handle, &post_count );

  return ( rc == NO_ERROR ||
           rc == ERROR_ALREADY_RESET );
}


