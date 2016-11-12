/*
 * Copyright (C) 2001-2008 Dmitry A.Steklenev
 *
 * $Id: pm_language.h,v 1.12 2011/03/11 13:23:22 glass Exp $
 */

#ifndef PM_LANGUAGE_H
#define PM_LANGUAGE_H

#include "pm_os2.h"
#include "pm_noncopyable.h"
#include <ecolange.h>

#pragma library( "ecolange.lib" )

/**
 * Messages catalog management class.
 *
 * None of the functions in this class throws exceptions because
 * an exception probably has been thrown already or is about to be
 * thrown.
 *
 * You can construct and destruct objects of this class.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.12 $
 */

class PMLanguage : public PMNonCopyable
{
  /** Easy way to retrieve a message from the messages catalog. */
  #define MSGCPY( var, key ) PMLanguage::instance->message( var, sizeof( var ), key )
  /** Easy way to retrieve a message pointer from the messages catalog. */
  #define MSGPTR( key ) PMLanguage::instance->message_ptr( key )

  public:

    /**
     * Constructs the messages management object.
     *
     * Opens the specified by <i>filename</i> messages catalog file
     * and loads all messages of the current language into the
     * program memory.
     */

    PMLanguage( const char* filename );

    /**
     * Constructs the messages management object of a current module.
     *
     * Opens the specified as <i>modulename.nls</i> messages catalog file
     * and loads all messages of the current language into the
     * program memory.
     */

    PMLanguage();

    /**
     * Destructs the messages management object.
     */

   ~PMLanguage();

    /**
     * Retrieves a message from the messages catalog.
     *
     * @param result  A buffer in which the message corresponding to
     *                the keyword is returned.
     * @param size    This is the size of the buffer specified by the <i>result</i>
     *                parameter. If the call is successful, this is overwritten
     *                with the number of bytes copied into the buffer.
     * @param key     Specifies the message keyword.
     */

    char* message( char* result, int size, const char* key );

    /**
     * Retrieves a pointer to message from the messages catalog.
     *
     * <b>Note: </b>This method don't understand of the escaped
     * characters.
     *
     * @param  key Specifies the message keyword.
     * @return A pointer to the message corresponding to the keyword.
     *         The <i>char*</i> type is used instead of <i>const char*</i>
     *         because of the most functions of the ECS runtime which
     *         receives <i>char*</i> as argument.
     */

    char* message_ptr( const char* key ) const;

    /** Returns the handle of the opened message catalog. */
    LANGE  handle() const;

    /**
     * This is a global instance of the messages management object.
     *
     * This static member variable must be initialized during a initialization of
     * the application, because this variable is used in some cases by library
     * functions.
     */

    static PMLanguage* instance;

  private:
    LANGE m_handle;
};

/* Returns the handle of the opened message catalog. */
inline LANGE PMLanguage::handle() const {
  return m_handle;
}

#endif
