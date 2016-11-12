/*
 * Copyright (C) 2006-2010 Dmitry A.Steklenev
 *
 * $Id: pm_sharedptr.h,v 1.2 2011/03/11 12:59:33 glass Exp $
 */

#ifndef PM_SHAREDPTR_H
#define PM_SHAREDPTR_H

#include "pm_os2.h"
#include "pm_delete.h"
#include "pm_smp.h"

/**
 * Shared pointer class.
 *
 * The PMSharedPtr class template stores a pointer to a dynamically
 * allocated object, typically with a C++ new-expression. The object
 * pointed to is guaranteed to be cleaned when the last PMSharedPtr
 * pointing to it is destroyed.
 *
 * You can construct, destruct, copy, and assign objects of this class.
 *
 * @author  Dmitry A Steklenev
 * @version $Revision: 1.2 $
 */

template <class T> class PMSharedPtr
{
  private:
    /** Base pointer holder class. */
    class base_ptr_holder
    {
      public:
        base_ptr_holder( T* p )
        : m_p         ( p ),
          m_referenced( 1 )
        {}

        virtual ~base_ptr_holder()
        {}

        T* m_p;
        unsigned int m_referenced;
    };

    /** Pointer holder class template. */
    template <class Function>
    class ptr_holder : public base_ptr_holder
    {
      public:
        ptr_holder( T* p, const Function& f )
        : base_ptr_holder( p ),
          m_cleanup      ( f )
        {}

       ~ptr_holder() {
          m_cleanup( m_p );
        }

      private:
        Function m_cleanup;
    };

  public:

    /**
     * Constructs the shared pointer.
     *
     * Use these constructor to create new objects with reference
     * counters set to 1.
     *
     * @param p A pointer.
     * @param f A function object which will be applied to the pointer
     *          when the reference count will reach zero. You can use
     *          {@link PMDelete}, {@link PMDeleteArray} and {@link PMFree}
     *          function object or define your own functor.
     *
     * @exception bad_alloc If the implementation cannot allocate memory storage.
     */

    template <class Function>
    PMSharedPtr( T* p, const Function& f ) {
      m_holder = new ptr_holder<Function>( p, f );
    }

    /** Constructs the "NULL" shared pointer. */
    PMSharedPtr() {
      m_holder = new base_ptr_holder( 0 );
    }

    /**
     * Copy constructor.
     *
     * Use this constructor to create a copy of the given object.
     * The constructor increments the reference count of the object holded
     * to by the given PMSharedPtr object.
     */

    PMSharedPtr( const PMSharedPtr<T>& reference );

    /**
     * Destructs the shared pointer.
     *
     * This destructor destroys the PMSharedPtr object and decrements the
     * reference count of the holded object. When the count is zero, the
     * holded object is cleaned.
     */

   ~PMSharedPtr() {
      dec_reference();
    }

    /**
     * Assignment operator.
     *
     * Use this operator to modify the PMSharedPtr object so that it
     * refers to the same object as another. If the object the pointer
     * previously referred to was a valid object, that object's reference
     * count is decremented. When the count is zero, that object is cleaned.
     */

    PMSharedPtr<T>& operator=( const PMSharedPtr<T>& reference );

    /**
     * Returns a reference to the pointed object.
     * @exception none
     */

    T& operator* () {
      return *(m_holder->m_p);
    }

    /**
     * Returns a reference to the pointed object.
     * @exception none
     */

    const T& operator* () const {
      return *(m_holder->m_p);
    }

    /**
     * Returns a pointer to the pointed object.
     * @exception none
     */

    T* operator->() {
      return m_holder->m_p;
    }

    /**
     * Returns a pointer to the pointed object.
     * @exception none
     */

    const T* operator->() const {
      return m_holder->m_p;
    }

    /**
     * Returns a pointer to the pointed object.
     * @exception none
     */

    operator const T*() const {
      return m_holder->m_p;
    }

    /**
     * Returns a pointer to the pointed object.
     * @exception none
     */

    operator T*() {
      return m_holder->m_p;
    }

    /**
     * Returns whether the stored pointer is NULL.
     * @exception none
     */

    bool is_null() const {
      return !m_holder->m_p;
    }

  private:
    base_ptr_holder* m_holder;

    /** Increments the reference count. */
    void inc_reference() const;
    /** Decrements the reference count. */
    void dec_reference() const;
};

/* Increments the reference count.
 */

template <class T>
inline void PMSharedPtr<T>::inc_reference() const {
  xadd( &m_holder->m_referenced, 1 );
}

/* Decrements the reference count.
 */

template <class T>
inline void PMSharedPtr<T>::dec_reference() const
{
  if( xadd( &m_holder->m_referenced, -1 ) == 1 ) {
    delete m_holder;
  }
}

/* Copy constructor.
 */

template <class T>
PMSharedPtr<T>::PMSharedPtr( const PMSharedPtr<T>& reference )
{
  reference.inc_reference();
  m_holder = reference.m_holder;
}

/* Assignment operator.
 */

template <class T>
PMSharedPtr<T>& PMSharedPtr<T>::operator=( const PMSharedPtr<T>& reference )
{
  if( this != &reference )
  {
    reference.inc_reference();
    dec_reference();
    m_holder = reference.m_holder;
  }

  return *this;
}

#endif
