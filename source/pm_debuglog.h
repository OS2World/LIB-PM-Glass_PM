/*
 * Copyright (C) 2008-2011 Dmitry A.Steklenev
 *
 * $Id: pm_debuglog.h,v 1.5 2011/09/19 08:41:17 glass Exp $
 */

#ifndef  PM_DEBUGLOG_H
#define  PM_DEBUGLOG_H

#include "pm_os2.h"

#if defined( DEBUG )
  void debuglog( const char* fmt, ... );
  void debugmsg( const char* prefix, HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 );

  #define DEBUGLOG(x) debuglog x
  #define DEBUGMSG(x) debugmsg x
#else
  #define DEBUGLOG(x)
  #define DEBUGMSG(x)
#endif

#if defined( DEBUG ) && DEBUG >= 2
  #define DEBUGLOG2(x) debuglog x
  #define DEBUGMSG2(x) debugmsg x
#else
  #define DEBUGLOG2(x)
  #define DEBUGMSG2(x)
#endif

#define DEBUG_TRACE_POINT() \
  DEBUGLOG(( "%s %s (%d)\n",  __FILE__, __FUNCTION__, __LINE__ ))

#endif
