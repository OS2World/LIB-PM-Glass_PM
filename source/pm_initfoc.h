/*
 * Copyright (C) 2010 Dmitry A.Steklenev
 *
 * $Id: pm_initfoc.h,v 1.3 2011/03/11 13:23:22 glass Exp $
 */

#ifndef PM_INITFOC_H
#define PM_INITFOC_H

#include "pm_os2.h"
#include "pm_noncopyable.h"
#include <foc.h>

#pragma library( "foc.lib" )

/**
 * Register and unregister the FOC control window classes.
 *
 * This is an internal class type, used by other library classes.
 * You should not attempt to use it directly.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.3 $
 */

class PMFOCInit : public PMNonCopyable
{
  public:
    PMFOCInit();
   ~PMFOCInit();

  private:
    static ULONG   m_initialized;
    static HMODULE m_hmodule;
};

static PMFOCInit pm_foc_init_;
#endif
