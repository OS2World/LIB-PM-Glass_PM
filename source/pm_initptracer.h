/*
 * Copyright (C) 2010 Dmitry A.Steklenev
 *
 * $Id: pm_initptracer.h,v 1.3 2011/03/11 13:23:22 glass Exp $
 */

#ifndef PM_INITPTRACER_H
#define PM_INITPTRACER_H

#include "pm_os2.h"
#include "pm_noncopyable.h"

#pragma library( "ptrace.lib" )

/**
 * Register and unregister the log messages collector window class.
 *
 * This is an internal class type, used by other library classes.
 * You should not attempt to use it directly.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.3 $
 */

class PMPTracerInit : public PMNonCopyable
{
  public:
    PMPTracerInit();
   ~PMPTracerInit();

  private:
    static ULONG   m_initialized;
    static HMODULE m_hmodule;
};

static PMPTracerInit pm_ptracer_init_;
#endif
