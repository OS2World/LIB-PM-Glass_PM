/*
 * Copyright (C) 2006-2008 Dmitry A.Steklenev
 *
 * $Id: pm_queue.cpp,v 1.4 2011/03/11 12:59:32 glass Exp $
 */

#include "pm_queue.h"
#include "pm_error.h"

/* Creates a queue object.
 */

PMQueue::PMQueue()

: m_frst_node( NULL ),
  m_last_node( NULL )
{}

/* Destroys the queue object.
 */

PMQueue::~PMQueue() {
  clear();
}

/* Purges a queue of all its elements.
 */

void PMQueue::clear()
{
  QNode* node;
  QNode* next;

  m_data_mutex.request();

  for( node = m_frst_node; node; node = next ) {
    next = node->m_next_node;
    free( node );
  }

  m_frst_node = NULL;
  m_last_node = NULL;

  m_data_ready.reset();
  m_data_mutex.release();
}

/* Is a queue empty.
 */

BOOL PMQueue::empty() const {
  return !m_frst_node;
}

/* Reads an element from a queue.
 */

BOOL PMQueue::read( ULONG* request, void** data, ULONG* priority )
{
  for(;;) {
    m_data_ready.wait();
    m_data_mutex.request();

    if( m_frst_node )
    {
      QNode* node = m_frst_node;

      if( request  ) { *request  = node->m_request;  }
      if( data     ) { *data     = node->m_data;     }
      if( priority ) { *priority = node->m_priority; }

      m_frst_node = node->m_next_node;
      free( node );

      if( m_frst_node ) {
        m_frst_node->m_prev_node = NULL;
      } else {
        m_data_ready.reset();
        m_last_node = NULL;
      }
      m_data_mutex.release();
      break;
    } else {
      m_data_ready.reset();
      m_data_mutex.release();
    }
  }

  return TRUE;
}

/* Examines a queue element without removing
 * it from the queue.
 */

BOOL PMQueue::peek( ULONG* request, void** data, ULONG* priority )
{
  m_data_mutex.request();

  if( m_frst_node )
  {
    if( request  ) { *request  = m_frst_node->m_request;  }
    if( data     ) { *data     = m_frst_node->m_data;     }
    if( priority ) { *priority = m_frst_node->m_priority; }

    m_data_mutex.release();
    return TRUE;
  } else {
    m_data_mutex.release();
    return FALSE;
  }
}

/* Examines a queue element without removing
 * it from the queue.
 */

BOOL PMQueue::peek( ULONG first, ULONG last )
{
  BOOL rc;

  m_data_mutex.request();

  if( m_frst_node ) {
    rc = ( m_frst_node->m_request >= first &&
           m_frst_node->m_request <= last  );
  } else {
    rc = FALSE;
  }

  m_data_mutex.release();
  return rc;
}

/* Adds an element to a queue.
 */

void PMQueue::write( ULONG request, void* data, ULONG priority )
{
  QNode* node = (QNode*)calloc( sizeof( QNode ), 1 );
  QNode* last;

  if( node )
  {
    node->m_request  = request;
    node->m_data     = data;
    node->m_priority = priority;

    m_data_mutex.request();

    if( m_last_node ) {
      for( last = m_last_node; last; last = last->m_prev_node ) {
        if( last->m_priority >= priority ) {
          node->m_prev_node = last;
          node->m_next_node = last->m_next_node;
          last->m_next_node = node;

          if( node->m_next_node ) {
            node->m_next_node->m_prev_node = node;
          } else {
            m_last_node = node;
          }
          break;
        }
      }
      if( !last ) {
        node->m_next_node = m_frst_node;
        m_frst_node->m_prev_node = node;
        m_frst_node = node;
      }
    } else {
      m_frst_node = node;
      m_last_node = node;
    }

    m_data_ready.post();
    m_data_mutex.release();
  } else {
    PM_THROW_CLIBERROR();
  }
}

