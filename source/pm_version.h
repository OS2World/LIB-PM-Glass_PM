/*
 * Copyright (C) 2008 Dmitry A.Steklenev
 *
 * $Id: pm_version.h,v 1.2 2011/03/11 12:59:33 glass Exp $
 */

#ifndef PM_VERSION_H
#define PM_VERSION_H

#include "pm_os2.h"

#undef  major
#undef  minor

/**
 *
 * Version number.
 *
 * Represents a specific version number. It provides mechanisms
 * for version comparison.<br>
 * An PMVersion is composed of:
 *
 * <ul>
 * <li>A major number.
 * <li>A minor number.
 * <li>A patchlevel.
 * <li>A buildlevel.
 * </ul>
 *
 * You can construct, destruct, copy, and assign objects of this class.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.2 $
 */

class PMVersion
{
  public:
    /** Constructs the default version number object. */
    PMVersion();
    /** Constructs the version number object. */
    PMVersion( int major, int minor, int patchlevel, int buildlevel );

    /** Returns the major version number. */
    int major() const;
    /** Returns the minor version number. */
    int minor() const;
    /** Returns the patchlevel. */
    int patchlevel() const;
    /** Returns the buildlevel. */
    int buildlevel() const;

    /** Sets the major version number. */
    void major( int major );
    /** Sets the minor version number. */
    void minor( int minor );
    /** Sets the patchlevel. */
    void patchlevel( int patchlevel );
    /** Sets the buildlevel. */
    void buildlevel( int buildlevel );

    /** Compares this object to another version object for equality. */
    int  operator==( const PMVersion& version ) const { return compare( version ) == 0; }
    /** Compares this object to another version object for inequality. */
    int  operator!=( const PMVersion& version ) const { return compare( version ) != 0; }
    /** Compares this object to another version object for relative magnitude. */
    int  operator< ( const PMVersion& version ) const { return compare( version ) <  0; }
    /** Compares this object to another version object for relative magnitude. */
    int  operator<=( const PMVersion& version ) const { return compare( version ) <= 0; }
    /** Compares this object to another version object for relative magnitude. */
    int  operator> ( const PMVersion& version ) const { return compare( version ) >  0; }
    /** Compares this object to another version object for relative magnitude. */
    int  operator>=( const PMVersion& version ) const { return compare( version ) >= 0; }

    /** If all parts of this version object are zero, TRUE is returned. */
    BOOL empty() const;

  private:
    int compare( const PMVersion& ) const;

    int m_major;
    int m_minor;
    int m_patchlevel;
    int m_buildlevel;
};

/* Returns the major version number. */
inline int PMVersion::major() const {
  return m_major;
}

/* Returns the minor version number. */
inline int PMVersion::minor() const {
  return m_minor;
}

/* Returns the patchlevel. */
inline int PMVersion::patchlevel() const {
  return m_patchlevel;
}

/* Returns the buildlevel. */
inline int PMVersion::buildlevel() const {
  return m_buildlevel;
}

/* Sets the major version number. */
inline void PMVersion::major( int major ) {
  m_major = major;
}

/* Sets the minor version number. */
inline void PMVersion::minor( int minor ) {
  m_minor = minor;
}

/* Sets the patchlevel. */
inline void PMVersion::patchlevel( int patchlevel ) {
  m_patchlevel = patchlevel;
}

/* Sets the buildlevel. */
inline void PMVersion::buildlevel( int buildlevel ) {
  m_buildlevel = buildlevel;
}

#endif
