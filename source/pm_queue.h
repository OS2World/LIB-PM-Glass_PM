/*
 * Copyright (C) 2006-2008 Dmitry A.Steklenev
 *
 * $Id: pm_queue.h,v 1.4 2011/03/11 12:59:32 glass Exp $
 */

#ifndef PM_QUEUE_H
#define PM_QUEUE_H

#include <stdlib.h>

#include "pm_os2.h"
#include "pm_noncopyable.h"
#include "pm_mutex.h"
#include "pm_notify.h"

/**
 * Queue class.
 *
 * A queue is ordered list of elements that is used to
 * pass information between related or unrelated processes.
 *
 * You can construct and destruct objects of this class.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.4 $
 */

class PMQueue : public PMNonCopyable
{
  public:

    /** Creates a queue object. */
    PMQueue();
    /** Destroys the queue object. */
   ~PMQueue();

    /** Purges a queue of all its elements. */
    void clear();
    /** Is a queue empty. */
    BOOL empty() const;

    /**
     * Reads an element from a queue.
     *
     * @param request   An event code that is specified by the application.
     * @param data      A pointer to the data that is being removed.
     * @param priority  The address of the element's priority.
     */

    BOOL read( ULONG* request, void** data = NULL, ULONG* priority = NULL );

    /**
     * Examines a queue element without removing it from the queue.
     *
     * @param request   An event code that is specified by the application.
     * @param data      A pointer to the examined data.
     * @param priority  The address of the element's priority.
     */

    BOOL peek( ULONG* request, void** data = NULL, ULONG* priority = NULL );

    /**
     * Examines a queue element without removing it from the queue.
     *
     * @param first     First event code.
     * @param last      Last event code.
     *
     * @return TRUE if a next queue element has a event code in range specified
     *              by the <i>first</i> and <i>last</i> inclusive.
     */

    BOOL peek( ULONG first, ULONG last );

    /**
     * Adds an element to a queue.
     *
     * @param request   An event code that is specified by the application.
     * @param data      A data to be placed into the queue.
     * @param priority  The priority value of the element that is being added to the queue.
     */

    void write( ULONG request, void* data = NULL, ULONG priority = 0 );

  private:

    struct QNode {
      ULONG  m_request;
      void*  m_data;
      QNode* m_prev_node;
      QNode* m_next_node;
      ULONG  m_priority;
    };

    QNode*    m_frst_node;
    QNode*    m_last_node;
    PMMutex   m_data_mutex;
    PMNotify  m_data_ready;
};

#endif
