/*
 * Copyright (C) 2001-2010 Dmitry A.Steklenev
 *
 * $Id: pm_filedialog.cpp,v 1.11 2011/03/11 12:59:31 glass Exp $
 */

#include <memory.h>
#include "pm_filedialog.h"
#include "pm_gui.h"
#include "pm_error.h"
#include "pm_fileutils.h"
#include "pm_frame.h"
#include "pm_debuglog.h"

/* Constructs the file dialog object.
 *
 * This constructor create file dialog object. You must use show_modally
 * to activate it.
 */

PMFileDialog::PMFileDialog( const char* caption,  HWND howner,
                            const char* filename, ULONG style )

: m_owner      (  howner     ),
  m_types      (  NULL       ),
  m_types_count(  0          ),
  m_handle     (  NULLHANDLE ),
  m_next       (  0          ),
  m_initial    (  0          )
{
  memset( &m_filedlg, 0, sizeof( FOCFILEDLG ));

  m_filedlg.cbSize   = sizeof( FOCFILEDLG );
  m_filedlg.fl       = style;
  m_filedlg.pszTitle = strdup( caption );
  m_filedlg.ulUser   = (ULONG)this;

  strlcpy( m_filedlg.szFullFile, filename, sizeof( m_filedlg.szFullFile ));

  if( m_filedlg.pszTitle == NULL ) {
    PM_THROW_CLIBERROR();
  }
}

/* Destructs the file dialog object.
 *
 * Cleans up as this dialog object and destroying the
 * associated presentation window for this object.
 */

PMFileDialog::~PMFileDialog()
{
  int  i;
  for( i = 0; i < m_types_count; i++ ) {
    free( m_types[i][0] );
  }

  free( m_types );
  free( m_filedlg.pszTitle );

  if( m_filedlg.papszFQFilename ) {
    FOCFreeFileDlgList( m_filedlg.papszFQFilename );
  }
}

/**
 * Displays the file dialog.
 *
 * While the dialog window is being shown modally, its parent or owner or
 * both windows are disabled. Other top level windows belonging to the
 * application are not disabled.
 */

ULONG PMFileDialog::show_modally()
{
  char type[254];
  m_handle = NULLHANDLE;

  if( m_types != NULL )
  {
    // WinFileDlg returns error if a length of the pszIType string is above
    // 255 characters. Therefore the small part from the full filter is used
    // as initial extended-attribute type filter. This part has enough to
    // find the full filter in the papszITypeList.
    strlcpy( type, m_types[m_initial][0], sizeof( type ));

    m_filedlg.papszITypeList = m_types;
    m_filedlg.pszIType = type;
  }

  if( m_filedlg.papszFQFilename ) {
    FOCFreeFileDlgList( m_filedlg.papszFQFilename );
    m_filedlg.papszFQFilename = NULL;
    m_filedlg.ulFQFCount = 0;
  }

  if( FOCFileDlg( HWND_DESKTOP, m_owner, &m_filedlg ) == NULLHANDLE ) {
    PM_THROW_GUIERROR();
  }

  return m_filedlg.lReturn;
}

/* Adds the specified type to the drop-down list box.
 */

void PMFileDialog::add_filetype( const char* filetype, const char* filter, BOOL initial )
{
  char* combined =
    (char*)malloc( strlen( filetype ) + strlen( filter ) * 2 + 5 );

  if( combined == NULL ) {
    PM_THROW_CLIBERROR();
  }

  sprintf( combined, "%s (%s)\t%s", filetype, filter, filter );
  m_types = (APSZ*)realloc( m_types, sizeof( APSZ ) * ( m_types_count + 2 ));

  if( m_types == NULL ) {
    PM_THROW_CLIBERROR();
  }
  if( initial ) {
    m_initial = m_types_count;
  }

  m_types[m_types_count    ][0] = combined;
  m_types[m_types_count + 1][0] = NULL;
  m_types_count++;
}

/* Returns a selected file type to assign to the file name returned.
 */

int PMFileDialog::filetype() const {
  return m_filedlg.sEAType;
}

/* Returns a pointer to the iterator object.
 *
 * This object can be used to iterate through chosen files
 * and must be deleted after usage.
 */

PMFileDialog::iterator* PMFileDialog::selected() {
  return new iterator( &m_filedlg );
}

/* Constructs the iterator object.
 */

PMFileDialog::iterator::iterator( PFOCFILEDLG pfiledlg )

: m_count( 0    ),
  m_array( NULL ),
  m_next ( 0    )
{
  int i;

  if( pfiledlg->ulFQFCount ) {
    m_count = pfiledlg->ulFQFCount;
    m_array = (char**)malloc( m_count * sizeof(char*));

    if( !m_array ) {
      PM_THROW_CLIBERROR();
    }

    if( m_count > 1 ) {
      for( i = 0; i < m_count; i++ ) {
        m_array[i] = strdup( (*pfiledlg->papszFQFilename)[i] );

        if( !m_array[i] ) {
          PM_THROW_CLIBERROR();
        }
      }
    } else {
      m_array[0] = strdup( pfiledlg->szFullFile );
    }
  }
}

/* Destructs the iterator object.
 */

PMFileDialog::iterator::~iterator()
{
  int i;

  for( i = 0; i < m_count; i++ ) {
    free( m_array[i] );
  }

  free( m_array );
}

/* Returns the next selected file or directory.
 */

BOOL PMFileDialog::iterator::next( char* pathname, int size )
{
  if( m_next < m_count ) {
    strlcpy( pathname, m_array[m_next], size );
    ++m_next;
    return TRUE;
  }

  return FALSE;
}


