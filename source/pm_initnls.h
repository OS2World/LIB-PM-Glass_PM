/*
 * Copyright (C) 2010 Dmitry A.Steklenev
 *
 * $Id: pm_initnls.h,v 1.2 2011/03/11 12:59:32 glass Exp $
 */

#ifndef PM_INITNLS_H
#define PM_INITNLS_H

#include "pm_os2.h"
#include "pm_noncopyable.h"

/**
 * Initializes and terminates the national language support class.
 *
 * This is an internal class type, used by other library classes.
 * You should not attempt to use it directly.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.2 $
 */

class PMInitNLS : public PMNonCopyable
{
  public:
    PMInitNLS();
   ~PMInitNLS();

  private:
    static ULONG m_initialized;
};

static PMInitNLS pm_nls_init_;
#endif
