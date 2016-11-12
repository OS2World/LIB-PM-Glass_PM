/*
 * Copyright (C) 2000-2011 Dmitry A.Steklenev
 *
 * $Id: pm_2drawable.h,v 1.1 2011/06/08 13:17:20 glass Exp $
 */

#ifndef PM_2DRAWABLE_H
#define PM_2DRAWABLE_H

#include "pm_rectangle.h"

/**
 * 2D Base drawable class.
 *
 * PM2Drawable is an abstract base class which allows a graphic object
 * to draw itself.
 *
 * @author Dmitry A Steklenev
 * @version $Revision: 1.1 $
 */

class PM2Drawable
{
  public:

    /** Constructs the drawable object. */
    PM2Drawable() {}
    /** Destructs  the drawable object. */
    virtual ~PM2Drawable() {}

  protected:

    /** Constructs the drawable object from another object. */
    PM2Drawable( const PM2Drawable& ) {}
    /** Assigns the value of one drawable object to another. */
    PM2Drawable& operator=( const PM2Drawable& );

  public:

    /**
     * Draws the graphic to the specified presentation space.
     *
     * This is a pure virtual function.
     */

    virtual void draw( HPS hps ) = 0;

    /**
     * Return the bounding rectangle for this graphic.
     *
     * This is a pure virtual function.
     */

    virtual PMRect bound() const = 0;
};

/* Assigns the value of one object to another
 */

inline PM2Drawable& PM2Drawable::operator=( const PM2Drawable& ) {
  return *this;
}

#endif
