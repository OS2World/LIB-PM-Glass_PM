/*
 * Copyright (C) 2000-2011 Dmitry A.Steklenev
 *
 * $Id: pm_2dimage.cpp,v 1.1 2011/06/08 13:18:26 glass Exp $
 */

#include "pm_2dimage.h"
#include "pm_error.h"

/* Constructs the bitmap image object.
 *
 * Load a bitmap image from the specified resource library
 * with its specified bitmap identifier. If you have not
 * already loaded the bitmap and you want load it from the
 * default resource library, use this constructor.
 */

PM2DImage::PM2DImage( LONG x, LONG y, SHORT res_id, HMODULE hmodule )
: m_handle( new sys_handle( res_id, hmodule ), PMDelete<sys_handle>())
{
  m_pos.x = x;
  m_pos.y = y;
}

/* Constructs the bitmap image object from another object.
 */

PM2DImage::PM2DImage( const PM2DImage& image )
: m_pos( image.m_pos ), m_handle( image.m_handle )
{}

/* Assigns the value of one image object to another.
 */

PM2DImage& PM2DImage::operator=( const PM2DImage& image )
{
  if( &image != this ) {
    m_handle = image.m_handle;
    m_pos = image.m_pos;
  }
  return *this;
}

/* Returns the bitmap rectangle.
 */

PMRect PM2DImage::rectangle() const
{
  BITMAP2HEADER bmp2h;
  Gpi2QueryBitmapInfo( handle(), &bmp2h );
  return PMRect( m_pos.x, m_pos.y, bmp2h.usCx, bmp2h.usCy );
}

/* Return the bounding rectangle for this image.
 */

PMRect PM2DImage::bound() const {
  return rectangle();
}

/* Moves image to another position.
 */

void PM2DImage::move( LONG x, LONG y )
{
  m_pos.x = x;
  m_pos.y = y;
}

/* Draws the bitmap to the specific presentation space.
 */

void PM2DImage::draw( HPS hps )
{
  if( handle()) {
    Gpi2DrawBitmap( hps, handle(), 1, &m_pos );
  }
}

/* Loads a image from the specified resource library.
 */

PM2DImage::sys_handle::sys_handle( SHORT res_id, HMODULE hmodule )
{
  PVOID  data;
  APIRET rc;

  if(( rc = DosGetResource( hmodule, RT_PNG, res_id, &data )) != NO_ERROR ) {
    PM_THROW_DOSERROR( rc );
  }

  m_hbm2 = Gpi2ReadPng((PBYTE)data, 0, 0 );

  if(( rc = DosFreeResource( data )) != NO_ERROR ) {
    PM_THROW_DOSERROR( rc );
  }
}

/* Deletes a image.
 */

PM2DImage::sys_handle::~sys_handle()
{
  if( m_hbm2 ) {
    Gpi2DeleteBitmap( m_hbm2 );
  }
}


