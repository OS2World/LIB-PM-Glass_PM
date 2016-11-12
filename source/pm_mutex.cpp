/*
 * Copyright (C) 2001-2008 Dmitry A.Steklenev
 *
 * $Id: pm_mutex.cpp,v 1.3 2011/03/11 12:59:32 glass Exp $
 */

#include "pm_mutex.h"

/* Constructs the mutual exclusion object.
 */

PMMutex::PMMutex() {
  DosCreateMutexSem( NULL, &m_handle, 0, 0 );
}

/* Destructs the mutual exclusion object.
 */

PMMutex::~PMMutex() {
  DosCloseMutexSem( m_handle );
}

/* Request access to resource.
 *
 * Requests ownership of a resource.
 * Blocks the calling thread indefinitely.
 */

BOOL PMMutex::request() {
  return !WinRequestMutexSem( m_handle, SEM_INDEFINITE_WAIT );
}

/* Request access to resource with wait timeout.
 *
 * Requests ownership of a resource.
 * Blocks the calling thread.
 */

BOOL PMMutex::request( unsigned long mseq ) {
  return !WinRequestMutexSem( m_handle, mseq );
}

/**
 * Relinquishes ownership of a resource.
 *
 * Only the thread that owns the resource can issue release().
 */

BOOL PMMutex::release() {
  return !DosReleaseMutexSem( m_handle );
}
