/*
 * Copyright (C) 2001-2008 Dmitry A.Steklenev
 *
 * $Id: pm_rectangle.h,v 1.4 2011/03/11 12:59:33 glass Exp $
 */

#ifndef PM_RECTANGLE_H
#define PM_RECTANGLE_H

#include "pm_os2.h"

/**
 * Object rectangle.
 *
 * The PMRect class represents a rectangular area defined by
 * start point and rectangle size. It provides mechanisms for sizes
 * comparison.
 *
 * You can construct, destruct, copy, and assign objects of this class.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.4 $
 */

class PMRect
{
  public:
    /** System dependent type defines a rectangle coordinates. */
    typedef struct _RECTL sys_rectangle;

    /**
     * Defines inclusive-inclusive type of a system rectangle.
     *
     * Locations of window rectangles are described by <i>sys_rectangle</i> structures,
     * which contain the coordinates of two points that define the opposite corners
     * of the rectangle.
     *
     * There are two types of sytem rectangles: inclusive-inclusive and
     * inclusive-exclusive. In inclusive-exclusive rectangles, the first corner
     * of the rectangle is included within the rectangle area, while
     * the second corner is excluded from the rectangle area. In an
     * inclusive-inclusive rectangle, both the corners are included in the
     * rectangle.
     */

    enum inclusive_type { inclusive };

    /**
     * Defines inclusive-exclusive type of a system rectangle.
     *
     * Locations of window rectangles are described by <i>sys_rectangle</i> structures,
     * which contain the coordinates of two points that define the opposite corners
     * of the rectangle.
     *
     * There are two types of sytem rectangles: inclusive-inclusive and
     * inclusive-exclusive. In inclusive-exclusive rectangles, the first corner
     * of the rectangle is included within the rectangle area, while
     * the second corner is excluded from the rectangle area. In an
     * inclusive-inclusive rectangle, both the corners are included in the
     * rectangle.
     */

    enum exclusive_type { exclusive };

    /** Constructs the empty rectangle object. */
    PMRect();
    /** Constructs the rectangle object from coordinates. */
    PMRect( long x, long y, long cx, long cy );
    /** Constructs the rectangle from inclusive-inclusive system rectangle. */
    PMRect( const sys_rectangle&, const inclusive_type& );
    /** Constructs the rectangle from inclusive-exclusive system rectangle. */
    PMRect( const sys_rectangle&, const exclusive_type& );

    long x;   //@- The rectangle's x-coordinate.
    long y;   //@- The rectangle's y-coordinate.
    long cx;  //@- The rectangle's width.
    long cy;  //@- The rectangle's height.

    /** If the width or height of this rectangle is zero, TRUE is returned. */
    BOOL empty() const;

    /** If the rectangle and specified rectangle overlap, TRUE is returned. */
    BOOL intersects( const PMRect& ) const;
    /** If the rectangle contains the specified point, TRUE is returned. */
    BOOL contains( long x, long y  ) const;

    /**
     * Shrinks the rectangle.
     *
     * Moves the corners of the rectangle inward toward the center by
     * the specified amount
     */

    void shrink_by( long amount );

    /**
     * Expands the rectangle.
     *
     * Moves the corners of the rectangle outward from the center
     * by the specified amount
     */

    void expand_by( long amount );

    /**
     * Maps a rectangle.
     *
     * Maps a rectangle from one window's coordinate space to another's,
     * such as mapping from screen coordinates to window coordinates.
     */

    void map( HWND hfrom, HWND hto );

    /** Compares this object to another rectangle object for equality.  */
    BOOL operator==( const PMRect& ) const;
    /** Compares this object to another rectangle object for inequality. */
    BOOL operator!=( const PMRect& ) const;

    /** Converts the rectangle value to inclusive-inclusive system rectangle. */
    sys_rectangle as_sys_value( const inclusive_type& ) const;
    /** Converts the rectangle value to inclusive-exclusive system rectangle. */
    sys_rectangle as_sys_value( const exclusive_type& ) const;
};

#endif
