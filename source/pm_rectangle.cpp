/*
 * Copyright (C) 2001-2008 Dmitry A.Steklenev
 *
 * $Id: pm_rectangle.cpp,v 1.4 2011/03/11 12:59:32 glass Exp $
 */

#include "pm_rectangle.h"

/* Constructs the empty rectangle object.
 */

PMRect::PMRect()

: x ( 0 ),
  y ( 0 ),
  cx( 0 ),
  cy( 0 )
{}

/* Constructs the rectangle object from coordinates.
 */

PMRect::PMRect( long x, long y, long cx, long cy )

: x ( x  ),
  y ( y  ),
  cx( cx ),
  cy( cy )
{}

/* Constructs the rectangle from inclusive-inclusive
 * system rectangle.
 */

PMRect::PMRect( const sys_rectangle& rect, const inclusive_type& )

: x ( rect.xLeft   ),
  y ( rect.yBottom ),
  cx( rect.xRight - rect.xLeft   + 1 ),
  cy( rect.yTop   - rect.yBottom + 1 )
{}

/* Constructs the rectangle from inclusive-exclusive
 * system rectangle.
 */

PMRect::PMRect( const sys_rectangle& rect, const exclusive_type& )

: x ( rect.xLeft   ),
  y ( rect.yBottom ),
  cx( rect.xRight - rect.xLeft   ),
  cy( rect.yTop   - rect.yBottom )
{}

/* If the width or height of this rectangle is zero,
 * TRUE is returned.
 */

BOOL PMRect::empty() const {
  return cx == 0 || cy == 0;
}

/* If the rectangle and specified rectangle overlap,
 * TRUE is returned.
 */

BOOL PMRect::intersects( const PMRect& rect ) const
{
  return ( x < rect.x + rect.cx || y < rect.y + rect.cy ) &&
         ( rect.x < x + cx      || rect.y < y + cy      );
}

/* If the rectangle contains the specified point,
 * TRUE is returned.
 */

BOOL PMRect::contains( long px, long py ) const
{
  return ( px >= x && px <= x + cx - 1 &&
           py >= y && py <= y + cy - 1 );
}

/* Shrinks the rectangle.
 *
 * Moves the corners of the rectangle inward toward the center by
 * the specified amount
 */

void PMRect::shrink_by( long amount )
{
  x  += amount;
  y  += amount;
  cx -= amount*2;
  cy -= amount*2;
}

/* Expands the rectangle.
 *
 * Moves the corners of the rectangle outward from the center
 * by the specified amount
 */

void PMRect::expand_by( long amount )
{
  x  -= amount;
  y  -= amount;
  cx += amount*2;
  cy += amount*2;
}

/* Maps a rectangle.
 *
 * Maps a rectangle from one window's coordinate space to another's,
 * such as mapping from screen coordinates to window coordinates.
 */

void PMRect::map( HWND hfrom, HWND hto )
{
  POINTL pos = { x, y };

  WinMapWindowPoints( hfrom, hto, &pos, 1 );
  x = pos.x;
  y = pos.y;
}

/* Compares this object to another rectangle
 * object for equality.
 */

BOOL PMRect::operator==( const PMRect& rect ) const
{
  return x  == rect.x  &&
         y  == rect.y  &&
         cx == rect.cx &&
         cy == rect.cy ;
}

/* Compares this object to another rectangle object
 * for inequality.
 */
BOOL PMRect::operator!=( const PMRect& rect ) const
{
  return x  != rect.x  ||
         y  != rect.y  ||
         cx != rect.cx ||
         cy != rect.cy ;
}

/* Converts the rectangle to system rectangle.
 */

PMRect::sys_rectangle PMRect::as_sys_value( const inclusive_type& ) const
{
  sys_rectangle rect;

  rect.xLeft   = x;
  rect.yBottom = y;
  rect.xRight  = x + cx - 1;
  rect.yTop    = y + cy - 1;

  return rect;
}

/* Converts the rectangle to system rectangle.
 */

PMRect::sys_rectangle PMRect::as_sys_value( const exclusive_type& ) const
{
  sys_rectangle rect;

  rect.xLeft   = x;
  rect.yBottom = y;
  rect.xRight  = x + cx;
  rect.yTop    = y + cy;

  return rect;
}

