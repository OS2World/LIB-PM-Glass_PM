/*
 * Copyright (C) 2011 Dmitry A.Steklenev
 *
 * $Id: pm_font.h,v 1.2 2011/04/22 11:44:48 glass Exp $
 */

#ifndef PM_FONT_H
#define PM_FONT_H

#include "pm_os2.h"

/**
 * Font class.
 *
 * The PMFont class manages the use of fonts.
 * You can construct, destruct, copy, and assign objects of this class.
 *
 * @author Dmitry A Steklenev
 */

class PMFont
{
  public:
    /** Constructs the font object from characters string. */
    PMFont( const char* fontname );

    /**
     * Returns the face name of the font.
     *
     * @param result  A buffer in which the face name is returned.
     * @param size    This is the size of the buffer specified by the <i>result</i>
     *                parameter. If the call is successful, this is overwritten
     *                with the number of bytes copied into the buffer.
     */

    char* name( char* result, int size ) const;

    /** Returns the point size of the font. */
    LONG size() const;
    /** Returns the font attributes. */
    const FATTRS* attrs() const;

  private:

    FATTRS m_attrs;
    LONG   m_points;
    SIZEF  m_sizef;
};

/* Returns the point size of the font.
 */

inline LONG PMFont::size() const {
  return m_points;
}

/* Returns the font attributes.
 */

inline const FATTRS* PMFont::attrs() const {
  return &m_attrs;
}

#endif
