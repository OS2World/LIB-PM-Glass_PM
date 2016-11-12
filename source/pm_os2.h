/*
 * Copyright (C) 2011 Dmitry A.Steklenev
 *
 * $Id: pm_os2.h,v 1.4 2011/07/01 10:59:25 glass Exp $
 */

#ifndef PM_OS2_H
#define PM_OS2_H

#define INCL_BASE
#define INCL_DOSDEVIOCTL
#define INCL_PM
#define INCL_LONGLONG
#include <os2.h>

#define PM_BASE           (0xFF00   )
#define PM_SETFOCUS       (PM_BASE+0) /* Replacement of the WM_SETFOCUS for safe     */
                                      /* focus change during the message processing. */
#define PM_TEXTEDIT       (PM_BASE+1) /* Begin direct name edit.                     */
#define PM_FORMATFRAME    (PM_BASE+2) /* OS/2 requires formatting the frame window   */
                                      /* after processing WM_FORMATFRAME.            */
#define PM_THREAD_END     (PM_BASE+3) /* Notify parent thread about termination of   */
                                      /* the specified thread.                       */
#define PM_SETEXTENSION   (PM_BASE+4) /* Attaches a window as a window extension.    */
#define PM_SETACCELTABLE  (PM_BASE+5) /* Establishes the window accelerator table.   */
#define PM_GETEXTENSION   (PM_BASE+6) /* Queries a window extension.                 */

/* Additional dialog codes: returned by WM_QUERYDLGCODE message */

#define DLGC_SPCANVAS     0x0800      /* Split canvas. */

/* PM_SETEXTENSION message parameter flags */

#define PMA_SE_ATTACH     0
#define PMA_SE_DETACH     1
#define PMA_SE_DETACH_ALL 2

/* PM_GETEXTENSION message parameter flags */

#define PMA_GE_FIRST     -1
#define PMA_GE_LAST      -2
#define PMA_GE_NEXT      -3
#define PMA_GE_PREV      -4

#endif
