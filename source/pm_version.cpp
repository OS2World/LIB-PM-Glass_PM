/*
 * Copyright (C) 2008 Dmitry A.Steklenev
 *
 * $Id: pm_version.cpp,v 1.2 2011/03/11 12:59:33 glass Exp $
 */

#include "pm_version.h"

/* Constructs the default version number object.
 */

PMVersion::PMVersion()

: m_major     ( 0 ),
  m_minor     ( 0 ),
  m_patchlevel( 0 ),
  m_buildlevel( 0 )
{}

/* Constructs the version number object.
 */

PMVersion::PMVersion( int major, int minor, int patchlevel, int buildlevel )

: m_major     ( major      ),
  m_minor     ( minor      ),
  m_patchlevel( patchlevel ),
  m_buildlevel( buildlevel )
{}

/* Compares this object to another version object
 */

int PMVersion::compare( const PMVersion& version ) const
{
  if( m_major != version.m_major ) {
    return m_major - version.m_major;
  }
  if( m_minor != version.m_minor ) {
    return m_minor - version.m_minor;
  }
  if( m_patchlevel != version.m_patchlevel ) {
    return m_patchlevel - version.m_patchlevel;
  }
  if( m_buildlevel != version.m_buildlevel ) {
    return m_buildlevel - version.m_buildlevel;
  }

  return 0;
}

/* If all parts of this version object are zero, TRUE is returned.
 */

BOOL PMVersion::empty() const
{
  return !( m_major      ||
            m_minor      ||
            m_patchlevel ||
            m_buildlevel );
}

