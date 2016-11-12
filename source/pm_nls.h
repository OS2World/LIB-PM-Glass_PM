/*
 * Copyright (C) 2010-2011 Dmitry A.Steklenev
 *
 * $Id: pm_nls.h,v 1.4 2012/04/24 11:22:41 glass Exp $
 */

#ifndef PM_NLS_H
#define PM_NLS_H

#include "pm_os2.h"
#include "pm_noncopyable.h"
#include "pm_initnls.h"
#include <uconv.h>

#ifdef  __WATCOMC__
#pragma library( "libconv.lib" )
#pragma library( "libuls.lib" )
#endif

/**
 * National language support class.
 *
 * Provides national language support via
 * various conversion and comparision member functions.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.4 $
 */

class PMNLS : public PMNonCopyable
{
  friend class PMInitNLS;

  public:

    /**
     * Converts the long long integer to the
     * decimal ASCII string separated by thousands.
     *
     * @param result  A buffer in which the converted text is returned.
     * @param size    This is the size of the buffer specified by the <i>result</i>.
     *                parameter.
     *
     * @return A pointer to <i>result</i>. There is no error return value.
     */

    static char* lltoa( char* result, int size, long long number );

    /**
     * Converts time to formatted character string containing
     * separated hours, minutes and seconds.
     *
     * @param result  A buffer in which the converted text is returned.
     * @param size    This is the size of the buffer specified by the <i>result</i>.
     *                parameter.
     *
     * @return A pointer to <i>result</i>. There is no error return value.
     */

    static char* timetohms( char* result, int size, unsigned long seconds );

    /**
     * Converts time to formatted character string containing
     * separated minutes and seconds.
     *
     * @param result  A buffer in which the converted text is returned.
     * @param size    This is the size of the buffer specified by the <i>result</i>.
     *                parameter.
     *
     * @return A pointer to <i>result</i>. There is no error return value.
     */

    static char* timetoms( char* result, int size, unsigned long seconds );

    /** Compare strings without case sensitivity. */
    static int stricmp( const char* string1, const char* string2 );
    /** Compare strings without case sensitivity. */
    static int strnicmp( const char* string1, const char* string2, int n );

    /**
     * Converts any lowercase letters in string to uppercase.
     * Other characters are not affected.
     */

    static char* strupr( char* string );

    /**
     * Converts the lowercase letter to the corresponding
     * uppercase letter.
     */

    static int toupper( int c );

    /**
     * Converts the string from current codepage to the unicode string.
     *
     * @param string  A pointer to the input null terminated string.
     * @param result  A buffer in which the converted string is returned.
     * @param size    This is the size in unicode characters of the buffer
     *                 specified by the <i>result</i> parameter.
     *
     * @return If successfully converts the source string, it returns the number
     *         of converted characters. If encounters an error, it returns -1.
     */

    static int strtoucs( const char* string, UniChar* result, int size );

    /**
     * Converts the unicode string to current codepage string.
     *
     * @param string  A pointer to the input null terminated string.
     * @param result  A buffer in which the converted string is returned.
     * @param size    This is the size in bytes of the buffer
     *                 specified by the <i>result</i> parameter.
     *
     * @return If successfully converts the source string, it returns the number
     *         of converted characters. If encounters an error, it returns -1.
     */

    static int ucstostr( const UniChar* string, char* result, int size );

  private:
    static COUNTRYINFO m_country_info;
    static CHAR        m_mapcase[256];
    static UconvObject m_uco_curcp;
};

/* Converts the lowercase letter to the corresponding
 * uppercase letter.
 */

inline int PMNLS::toupper( int c ) {
  return m_mapcase[(unsigned char)c];
}

#endif
