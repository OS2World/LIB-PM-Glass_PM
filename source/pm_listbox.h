/*
 * Copyright (C) 2001-2008 Dmitry A.Steklenev
 *
 * $Id: pm_listbox.h,v 1.8 2011/03/11 12:59:32 glass Exp $
 */

#ifndef PM_LISTBOX_H
#define PM_LISTBOX_H

#include "pm_os2.h"
#include "pm_window.h"

/**
 * List box control window class.
 *
 * The PMListBox class creates and manages list box control windows.
 * List boxes always have vertical scroll bars. Optionally, they
 * can have horizontal scroll bars.
 *
 * You can construct and destruct objects of this class.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.8 $
 */

class PMListBox : public PMWindow
{
  public:

    /**
     * Wraps the list box control window object around
     * an existing presentation window handle.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     */

    PMListBox( HWND handle );

    /**
     * Wraps the list box control window object around
     * an existing child window with the specified identity.
     *
     * The wrapped window object usually have a limited functionality.
     * You can query and set the window attributes, size, position
     * and visibility status.
     *
     * @param hparent     Specifies the parent-window handle.
     * @param id          Specifies the identity of the child window.
     */

    PMListBox( HWND hparent, SHORT id );

    /**
     * Constructs the list box control window.
     *
     * @param id          Specifies the window identifier.
     * @param hparent     Specifies the parent-window handle.
     * @param x,y,cx,cy   Specifies the window shape.
     * @param style       Specifies the window style:
     *
     * <dl>
     * <dt><i>LS_HORZSCROLL </i><dd>The list box control enables the
     *                              operator to scroll the list box horizontally.
     * <dt><i>LS_MULTIPLESEL</i><dd>The list box control enables the operator
     *                              to select more than one item at any one time.
     * <dt><i>LS_EXTENDEDSEL</i><dd>If this style is specified, the extended selection
     *                              user interface is enabled.
     * <dt><i>LS_OWNERDRAW  </i><dd>The list box control has one or more items that
     *                              can be drawn by the owner.
     * <dt><i>LS_NOADJUSTPOS</i><dd>If this style is included, the list box control
     *                              is drawn at the size specified.
     * </dl>
     *
     * @see PMWindow::PMWindow 2
     */

    PMListBox( SHORT id, HWND hparent, LONG x, LONG y, LONG cx, LONG cy, ULONG style );

  protected:

    /**
     * Constructs the presentation window of the specified class.
     *
     * @param classname     Specifies the registered-class name.
     * @param id            Specifies the window identifier.
     * @param text          Specifies the window text.
     * @param hparent       Specifies the parent-window handle.
     * @param howner        Specifies the owner-window handle.
     * @param x,y,cx,cy     Specifies the window shape.
     * @param style         Specifies the window style.
     * @param classdata     Specifies the pointer to control data.
     */

    PMListBox( const char* classname, SHORT id, const char* text, HWND hparent, HWND howner,
               LONG x, LONG y, LONG cx, LONG cy, ULONG style, PVOID classdata = NULL );
  public:

    /**
     * Inserts an item into a list box control.
     *
     * @param string      This points to a string containing the item text.
     * @param handle      The handle of the specified list box item.
     * @param pos         Item index.
     *
     *                    LIT_END - Add the item to the end of the list.
     *                    LIT_SORTASCENDING - Insert the item into the list
     *                    sorted in ascending order.
     *                    LIT_SORTDESCENDING - Insert the item into the list
     *                    sorted in descending order.
     *                    Other - Insert the item into the list at the offset
     *                    specified by this zero-based index.
     * @return            Index of inserted item.
     */

    virtual int insert( const char* string, ULONG handle = 0, int pos = LIT_END );

    /**
     * Removes an item from a list box control.
     *
     * @param pos         The zero-based index of the item to be removed.
     * @return            The number of items in the list after the item is removed.
     */

    virtual int remove( int pos );

    /** Removes all items from the list box control. */
    virtual void clear();

    /**
     * Returns the index of the list box item whose
     * text matches the string.
     *
     * @return  The index of the combination box item or LIT_NONE
     */

    virtual int search( const char* string ) const;

    /** Sets the selection state of an item in a list box. */
    virtual void select( int pos, BOOL state = TRUE );
    /** Sets the selection state of all items in a list box. */
    virtual void select_all( BOOL state = TRUE );

    /**
     * Returns the index of the cursored item.
     * @return  Returns the index of the cursored item or LIT_NONE.
     */

    virtual int cursored() const;

    /**
     * Returns the index of the first selected item.
     * @return  Returns the index of the first selected item or LIT_NONE.
     */

    virtual int selected() const;

    /**
     * Returns the index of the next selected item.
     * @return  Returns the index of the next selected item or LIT_NONE.
     */

    virtual int selected( int pos ) const;

    /**
     * Returns the index of the item currently at the top of the
     * list box.
     *
     * @return  Index of the item currently at the top of the list
     *          box or LIT_NONE.
     */

    virtual int top() const;

    /** Scrolls a particular item to the top of the list box. */
    virtual void top( int pos );

    /** Returns the number of items stored in the list box. */
    virtual int count() const;
    /** Returns the text of the specified list box item. */
    virtual char* item_text( int pos, char* result, short size ) const;
    /** Returns the length of the text of the specified list box item. */
    virtual int item_text_len( int pos ) const;
    /** Sets the text into the specified list box item. */
    virtual void item_text( int pos, const char* text );

    /** Sets the handle of the specified list box item. */
    virtual void  item_handle( int pos, ULONG handle );
    /** Returns the handle of the specified list box item. */
    virtual ULONG item_handle( int pos ) const;
};

#endif
