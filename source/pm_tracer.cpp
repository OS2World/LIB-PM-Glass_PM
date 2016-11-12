/*
 * Copyright (C) 2010 Dmitry A.Steklenev
 *
 * $Id: pm_tracer.cpp,v 1.3 2011/03/11 12:59:33 glass Exp $
 */

#include "pm_tracer.h"
#include <ptrace.h>

/* Wraps the log messages collector window object around
 * an existing presentation window handle.
 */

PMTracer::PMTracer( HWND handle )
: PMWindow( handle )
{}

/* Wraps the log messages collector window object around
 * an existing child window with the specified identifier.
 */

PMTracer::PMTracer( HWND hparent, SHORT id )
: PMWindow( hparent, id )
{}

/* Constructs the log messages collector window.
 */

PMTracer::PMTracer( SHORT id, HWND hparent,
                    LONG x, LONG y, LONG cx, LONG cy, ULONG style )

: PMWindow( WC_PTRACER, id, "", hparent, hparent,
            x, y, cx, cy, style, NULL )
{}

/* Adds specified message to the log collector.
 */

void PMTracer::trace( const char* message, int options ) {
  send( PTM_TRACE, MPFROMP( message ), MPFROMLONG( options ));
}

/* Deletes all the messages in the log collector..
 */

void PMTracer::clear() {
  send( PTM_CLEAR, 0, 0 );
}

/* Sets the selection state of all messages in a log collector.
 */

void PMTracer::select_all() {
  send( PTM_SELECTALL, 0, 0 );
}

/* Copies all selected messages into the clipboard.
 */

void PMTracer::copy() {
  send( PTM_COPY, 0, 0 );
}
