/*
 * Copyright (C) 2010 Dmitry A.Steklenev
 *
 * $Id: pm_dirtree.cpp,v 1.5 2011/03/11 12:59:31 glass Exp $
 */

#include "pm_dirtree.h"
#include "pm_gui.h"

/* Wraps the directory tree control window object around
 * an existing presentation window handle.
 */

PMDirTree::PMDirTree( HWND handle )
: PMWindow( handle )
{}

/* Constructs the directory tree control window object from
 * an existing child window with the specified identity.
 */

PMDirTree::PMDirTree( HWND hparent, SHORT id )
: PMWindow( hparent, id )
{}

/* Wraps the directory tree control window object around
 * an existing child window with the specified identifier.
 */

PMDirTree::PMDirTree( SHORT id, HWND hparent,
                      LONG x, LONG y, LONG cx, LONG cy, ULONG style )

: PMWindow( WC_DIRTREE, id, "", hparent, hparent,
            x, y, cx, cy, style, NULL )
{}

/* Assigns co-operating file view container.
 */

HWND PMDirTree::attach_fileview( HWND hfileview ) {
  return (HWND)send( DTM_SETFILEVIEW, MPFROMHWND( hfileview ), 0 );
}

/* Returns the name of the selected directory.
 */

char* PMDirTree::curdir( char* result, int size ) const
{
  WinSendMsg( handle(), DTM_QUERYCURDIR, MPFROMLONG( size ), MPFROMP( result ));
  return result;
}

/* Selects the specified directory.
 */

void PMDirTree::chdir( const char* directory )
{
  if( !WinSendMsg( handle(), DTM_CHDIR, MPFROMP( directory ), 0 )) {
    PM_THROW_GUIERROR();
  }
}

/* Refreshes a specified part of the directory tree.
 */

void PMDirTree::refresh( const char* directory )
{
  if( !WinSendMsg( handle(), DTM_REFRESH, MPFROMP( directory ), 0 )) {
    PM_THROW_GUIERROR();
  }
}

/* Returns a pointer to the iterator object.
 *
 * This object can be used to iterate through selected files or
 * directories and must be deleted after usage.
 */

PMDirTree::iterator* PMDirTree::checked()
{
  iterator* i;
  FILELIST  filelist = { sizeof( FILELIST )};

  WinSendMsg( handle(), DTM_QUERYCHECKED, MPFROMP( &filelist ), 0 );
  i = new iterator( &filelist );
  WinSendMsg( handle(), DTM_FREEFILELIST, MPFROMP( &filelist ), 0 );
  return i;
}

/* Constructs the iterator object.
 */

PMDirTree::iterator::iterator( FILELIST* pfilelist )

: m_count( 0    ),
  m_array( NULL ),
  m_next ( 0    )
{
  int i;

  if( pfilelist->ulFQFCount ) {
    m_count = pfilelist->ulFQFCount;
    m_array = (char**)malloc( m_count * sizeof(char*));

    if( !m_array ) {
      PM_THROW_CLIBERROR();
    }

    for( i = 0; i < m_count; i++ ) {
      m_array[i] = strdup( (*pfilelist->papszFQFilename)[i] );

      if( !m_array[i] ) {
        PM_THROW_CLIBERROR();
      }
    }
  }
}

/* Destructs the iterator object.
 */

PMDirTree::iterator::~iterator()
{
  int  i;
  for( i = 0; i < m_count; i++ ) {
    free( m_array[i] );
  }

  free( m_array );
}

/* Returns the next selected file or directory.
 */

BOOL PMDirTree::iterator::next( char* pathname, int size )
{
  if( m_next < m_count ) {
    strlcpy( pathname, m_array[ m_next++ ], size );
    return TRUE;
  }

  return FALSE;
}


