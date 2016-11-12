/*
 * Copyright (C) 2000-2011 Dmitry A.Steklenev
 *
 * $Id: pm_2dimage.h,v 1.1 2011/06/08 13:18:26 glass Exp $
 */

#ifndef PM_2DIMAGE_H
#define PM_2DIMAGE_H

#include "pm_2drawable.h"
#include "pm_sharedptr.h"
#include <ecomedia.h>

#pragma library( "ecomedia.lib" )

/**
 * 2D PNG Image class.
 *
 * The PM2DImage class accesses and manages PNG bitmap
 * resources through reference-counting. Reference-counting
 * allows the system to use one bitmap in multiple places.
 * The library maintains the lifetime of this bitmap until
 * all users are finished with it.
 * <p>
 * You can construct, destruct, copy, and assign objects of this class.
 *
 * @author Dmitry A Steklenev
 * @version $Revision: 1.1 $
 */

class PM2DImage : public PM2Drawable
{
  public:

    /**
     * Constructs the bitmap image object.
     *
     * Load a bitmap image from the specified resource library
     * with its specified bitmap identifier. If you have not
     * already loaded the bitmap and you want load it from the
     * default resource library, use this constructor.
     *
     * @param x        Horizontal position of the bitmap.
     * @param y        Vertical position of the bitmap.
     * @param res_id   The identifier of the bitmap.
     * @param hmodule  Module handle referencing a dynamic link library containing the
     *                 resource or NULLHANDLE for the application's module.
     */

    PM2DImage( LONG x, LONG y, SHORT res_id, HMODULE hmodule );

    /** Constructs the bitmap image object from another object. */
    PM2DImage( const PM2DImage& );
    /** Assigns the value of one bitmap object to another. */
    PM2DImage& operator=( const PM2DImage& );

    /** Returns the bitmap handle. */
    HBITMAP2 handle() const;

    /** Returns the bitmap rectangle. */
    virtual PMRect rectangle() const;
    /** Return the bounding rectangle for this image. */
    virtual PMRect bound() const;
    /** Moves image to another position. */
    virtual void move( LONG x, LONG y );

    /** Draws the bitmap to the specific presentation space. */
    virtual void draw( HPS hps );

  private:

    POINTL m_pos;

    class sys_handle {

      public:
        HBITMAP2 m_hbm2;

        sys_handle( SHORT res_id, HMODULE hmodule );
        sys_handle();
       ~sys_handle();
    };

    PMSharedPtr<sys_handle> m_handle;
};

/* Returns the bitmap handle
 */

inline HBITMAP2 PM2DImage::handle() const {
  return m_handle->m_hbm2;
}

/* Create default handle
 */

inline PM2DImage::sys_handle::sys_handle() {
  m_hbm2 = 0;
}

#endif
