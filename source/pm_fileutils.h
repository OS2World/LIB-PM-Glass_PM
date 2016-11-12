/*
 * Copyright (C) 2004-2012 Dmitry A.Steklenev
 *
 * $Id: pm_fileutils.h,v 1.7 2012/07/02 12:07:45 glass Exp $
 */

#ifndef PM_FILEUTIL_H
#define PM_FILEUTIL_H

#include <string.h>
#include "pm_os2.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @pkg File-Utilities */

/** 
 * File and directory management functions.
 * @pkgdoc File-Utilities
 */

/**
 * Returns the drive letter followed by a colon (:)
 * if a drive is specified in the location.
 *
 * Returns an empty string if specified path does not contain
 * definition of the drive.
 *
 * Note: Because the result string always less or is equal to a location
 * string all functions can safely use the same storage area for a
 * location and result.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.7 $
 */

char* sdrive( char* result, const char* location, size_t size );

/** 
 * Returns the scheme followed by a colon (:) of the specified location. 
 *
 * Returns an empty string if specified location does not contain
 * definition of the url scheme.
 *
 * Note: Because the result string always less or is equal to a location
 * string all functions can safely use the same storage area for a
 * location and result.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.7 $
 */

char* scheme( char* result, const char* location, size_t size );

/**
 * Returns the base file name without any extensions. 
 *
 *
 * Note: Because the result string always less or is equal to a location
 * string all functions can safely use the same storage area for a
 * location and result.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.7 $
 */

char* sfname( char* result, const char* location, size_t size );

/**
 * Returns the file name extension, if any, including the leading period (.). 
 *
 * Note: Because the result string always less or is equal to a location
 * string all functions can safely use the same storage area for a
 * location and result.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.7 $
 */

char* sfext( char* result, const char* location, size_t size );

/**
 * Replaces an extension of the specified file.
 *
 * The specified extension must include the leading period (.).
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.7 $
 */

char* sfextrep( char* filename, const char* ext, int size );

/**
 * Returns the base file name with file extension. 
 *
 * The specified extension must include the leading period (.).
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.7 $
 */

char* sfnameext( char* result, const char* location, size_t size );

/**
 * Returns the drive letter or scheme and the path of subdirectories, if any, including the trailing slash.
 * 
 * Slashes (/), backslashes (\), or both may be present in location. 
 *
 * Returns an empty string if specified location does not contain 
 * any path definition.
 *
 * Note: Because the result string always less or is equal to a location
 * string all functions can safely use the same storage area for a
 * location and result.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.7 $
 */

char* sdrivedir( char* result, const char* location, size_t size );

/**
 * Passed any string value, decode from URL transmission. 
 *
 *
 * Note: Because the result string always less or is equal to a location
 * string all functions can safely use the same storage area for a
 * location and result.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.7 $
 */

char* sdecode( char* result, const char* location, size_t size );

/** Returns TRUE if the specified location is a regular file. */
BOOL is_file( const char* location );
/** Returns TRUE if the specified location is a URL. */
BOOL is_url ( const char* location );
/** Returns TRUE if the specified location is a root directory. */
BOOL is_root( const char* location );
/** Returns TRUE if the specified location is a directory. */
BOOL is_dir ( const char* location );

/** 
 * Creates a single path name, composed of a base path name and file
 * or directory name.
 */

char* smakepath( char* result, const char* pathname, const char* name, int size );

#ifdef __cplusplus
}
#endif

#endif /* PM_FILEUTIL_H */
