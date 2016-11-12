/*
 * Copyright (C) 2010 Dmitry A.Steklenev
 *
 * $Id: pm_inittoolbar.h,v 1.3 2011/03/11 13:23:22 glass Exp $
 */

#ifndef PM_INITTOOLBAR_H
#define PM_INITTOOLBAR_H

#include "pm_os2.h"
#include "pm_noncopyable.h"

#pragma library( "etoolbar.lib" )
#pragma library( "eicons.lib"   )
#pragma library( "ecomedia.lib" )

/**
 * Register and unregister the toolbar control window class.
 *
 * This is an internal class type, used by other library classes.
 * You should not attempt to use it directly.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.3 $
 */

class PMToolBarInit : public PMNonCopyable
{
  public:
    PMToolBarInit();
   ~PMToolBarInit();

  private:
    static ULONG   m_initialized;
    static HMODULE m_hmodule;
};

static PMToolBarInit pm_toolbar_init_;
#endif
