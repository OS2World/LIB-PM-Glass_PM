/*
 * Copyright (C) 2008-2011 Dmitry A.Steklenev
 *
 * $Id: pm_container.h,v 1.17 2012/06/15 11:24:40 glass Exp $
 */

#ifndef PM_CONTAINER_H
#define PM_CONTAINER_H

#include "pm_os2.h"
#include "pm_window.h"

/**
 * Container control window class.
 *
 * The PMContainer class creates and manages container control windows.
 * A container can display objects in various formats and views.
 * Generally speaking, each view displays different information about
 * each object. If a container's data is too large for the window's
 * work area, scrolling mechanisms are enabled.
 *
 * You can construct and destruct objects of this class.
 *
 * @author  Dmitry A.Steklenev
 * @version $Revision: 1.17 $
 */

template <class TRecord>
class PMContainer : public PMWindow
{
  public:

    /**
     * Constructs the container control window object
     * from an existing presentation window handle.
     */

    PMContainer( HWND handle );

    /**
     * Constructs the container control window object from
     * an existing child window with the specified identity.
     *
     * @param hparent     Specifies the parent-window handle.
     * @param id          Specifies the identity of the child window.
     */

    PMContainer( HWND hparent, SHORT id );

    /**
     * Constructs the container control window.
     *
     * @param id          Specifies the window identifier.
     * @param hparent     Specifies the parent-window handle.
     * @param x,y,cx,cy   Specifies the window shape.
     * @param style       Specifies the window style:
     *
     * <dl>
     * <dt><i>CCS_AUTOPOSITION  </i><dd>Automatic positioning, which causes
     *                                  container items displayed in the icon view
     *                                  to be arranged.
     * <dt><i>CCS_READONLY      </i><dd>A read-only style bit for an entire container,
     *                                  which prevents a user from editing any of the
     *                                  text in a container window.
     * <dt><i>CCS_VERIFYPOINTERS</i><dd>A pointer verification style bit, which
     *                                  verifies that the application pointers are
     *                                  members of the container's linked list before
     *                                  they are used. If it is not set, the container
     *                                  does not verify the pointers.
     * <dt><i>CCS_SINGLESEL     </i><dd>Single selection, which allows a user to
     *                                  select only one container item at a time. Each
     *                                  time a user selects a container item, the
     *                                  selection of any other container item is
     *                                  cancelled.
     * <dt><i>CCS_EXTENDSEL     </i><dd>Extended selection, which allows a user to
     *                                  select one or more container items. A user can
     *                                  select one item, a range of items, or multiple
     *                                  ranges of items.
     * <dt><i>CCS_MULTIPLESEL   </i><dd>Multiple selection, which allows a user to
     *                                  select zero or more container items.
     * </dl>
     *
     * @see PMWindow::PMWindow 2
     */

    PMContainer( SHORT id, HWND hparent, LONG x, LONG y, LONG cx, LONG cy, ULONG style );

    /**
     * Destructs the container control window.
     */

    virtual ~PMContainer();

    /**
     * Sets the attributes of a container control.
     *
     * @param options Consists of container window attributes:
     *
     * <dl>
     * <dt><i>CV_ICON</i>
     *     <dd>In the icon view, the container items are represented as
     *         icon/text or bit-map/text pairs, with text beneath the
     *         icons or bit maps.
     * <dt><i>CV_NAME</i>
     *     <dd>In the name view, the container items are represented as
     *         icon/text or bit-map/text pairs, with text to the right
     *         of the icons or bit maps.
     * <dt><i>CV_TREE</i>
     *     <dd>In the tree view, the container items are represented in
     *         a hierarchical manner.
     * <dt><i>CV_DETAIL</i>
     *     <dd>In the details view, the container items are presented
     *         in columns. Each column can contain icons or bit maps,
     *         text, numbers, dates, or times.
     * <dt><i>CV_MINI</i>
     *     <dd>Produces a mini-icons.
     * <dt><i>CV_FLOW</i>
     *      <dd>Dynamically arranges container items in columns in the
     *          name and text views.
     * <dt><i>CA_DRAWICON</i>
     *     <dd>Icons are used for the icon, name, tree, or details views.
     * <dt><i>CA_DRAWBITMAP</i>
     *     <dd>Bit maps are used for the icon, name, tree, or details views.
     * <dt><i>CA_ORDEREDTARGETEMPH</i>
     *     <dd>Shows where a container record can be dropped during direct
     *         manipulation by drawing a line beneath the record. Ordered
     *         target emphasis does not apply to the icon and tree views.
     * <dt><i>CA_MIXEDTARGETEMPH</i>
     *     <dd>Shows where a container record can be dropped during direct
     *         manipulation either by drawing a line between two items or by
     *         drawing lines around the container record. Mixed target
     *         emphasis does not apply to the icon and tree views.
     * <dt><i>CA_TREELINE</i>
     *     <dd>Shows the relationship between all items in the tree view.
     * <dt><i>CA_OWNERDRAW</i>
     *     <dd>Ownerdraw for the container, which allows the application to
     *         draw container records.
     * <dt><i>CA_OWNERPAINTBACKGROUND</i>
     *     <dd>Allows the application to subclass the container and paint
     *         the background. If specified, and the container is subclassed,
     *         the application receives the CM_PAINTBACKGROUND message in the
     *         subclass procedure.
     * <dt><i>CA_CONTAINERTITLE</i>
     *     <dd>Allows you to include a container title.
     * <dt><i>CA_TITLEREADONLY</i>
     *     <dd>Prevents the container title from being edited directly.
     * <dt><i>CA_TITLESEPARATOR</i>
     *     <dd>Puts a separator line between the container title and the
     *         records beneath it
     * <dt><i>CA_TITLECENTER</i>
     *     <dd>Centers the container title.
     * <dt><i>CA_TITLELEFT</i>
     *     <dd>Left-justifies the container title.
     * <dt><i>CA_TITLERIGHT</i>
     *     <dd>Right-justifies the container title.
     * <dt><i>CA_DETAILSVIEWTITLES</i>
     *     <dd>Allows you to include column headings in the details view.
     * </dl>
     */

    void attributes( ULONG options );

    /** Returns the attributes of a container control. */
    ULONG attributes() const;
    /** Sets the icon or bitmap size for all objects.  */
    void icon_size( long cx, long cy );

    /**
     * Sets the amount of horizontal space between levels in the tree view.
     *
     * @param cx              The amount of horizontal space (in pels) between
     *                        levels in the tree view. If you specify a value
     *                        that is less than 0, a default value is used.
     */

    void tree_indent( long cx );

    /** Sets the container title. */
    void title( const char* text );

    /**
     * Adds column to the details view of the container control.
     *
     * @param title           Column heading data, which can be a text string or
     *                        an icon or bit map. The default is a text string.
     *                        If the <i>title_options</i> field is set to the
     *                        CFA_BITMAPORICON attribute, this must be an icon or
     *                        bit map.
     *
     * @param title_options   Column heading attributes:
     * <dl>
     * <dt><i>CFA_BITMAPORICON</i>
     *     <dd>The column heading contains icon or bit-map data.
     * <dt><i>CFA_FITITLEREADONLY</i>
     *     <dd>Prevents a column heading from being edited directly.
     * <dt><i>CFA_TOP</i>
     *     <dd>Top-justifies column headings.
     * <dt><i>CFA_BOTTOM</i>
     *     <dd>Bottom-justifies column headings.
     * <dt><i>CFA_VCENTER</i>
     *     <dd>Vertically centers column headings. This is the default.
     * <dt><i>CFA_CENTER</i>
     *     <dd>Horizontally centers column headings.
     * <dt><i>CFA_LEFT</i>
     *     <dd>Left-justifies column headings. This is the default.
     * <dt><i>CFA_RIGHT</i>
     *     <dd>Left-Right-justifies column headings.
     * </dl>
     *
     * @param data_offset     Offset from the beginning of a RECORDCORE structure
     *                        to the data that is displayed in this column.
     * @param data_options    Attributes of the data in a column:
     * <dl>
     * <dt><i>CFA_BITMAPORICON</i>
     *     <dd>The column contains bit-map or icon data.
     * <dt><i>CFA_DATE</i>
     *     <dd>The data in the column is displayed in date format.
     *         National Language Support (NLS) is enabled for date format.
     *         Use the data structure described in <i>CDATE</i>.
     * <dt><i>CFA_STRING</i>
     *     <dd>Character or text data is displayed in this column.
     * <dt><i>CFA_TIME</i>
     *     <dd>The data in the column is displayed in time format.
     *         National Language Support (NLS) is enabled for time format.
     *         Use the data structure described in <i>CTIME</i>.
     * <dt><i>CFA_ULONG</i>
     *     <dd>Unsigned number data is displayed in this column.
     *         National Language Support (NLS) is enabled for number format.
     * <dt><i>CFA_FIREADONLY</i>
     *     <dd>Prevents text from being edited directly. This attribute
     *         applies only to columns for which the CFA_STRING attribute has
     *         been specified.
     * <dt><i>CFA_HORZSEPARATOR</i>
     *     <dd>A horizontal separator is provided beneath column headings.
     * <dt><i>CFA_INVISIBLE</i>
     *     <dd>Invisible container column. The default is visible.
     * <dt><i>CFA_OWNER</i>
     *     <dd>Ownerdraw is enabled for this container column.
     * <dt><i>CFA_SEPARATOR</i>
     *     <dd>A vertical separator is drawn after this column.
     * <dt><i>CFA_BOTTOM</i>
     *     <dd>Bottom-justifies field data.
     * <dt><i>CFA_TOP</i>
     *     <dd>Top-justifies field data.
     * <dt><i>CFA_VCENTER</i>
     *     <dd>Vertically centers field data. This is the default.
     * <dt><i>CFA_CENTER</i>
     *     <dd>Horizontally centers field data.
     * <dt><i>CFA_LEFT</i>
     *     <dd>Left-justifies field data. This is the default.
     * <dt><i>CFA_RIGHT</i>
     *     <dd>Right-justifies field data.
     * </dl>
     *
     * @param pos             Column order:
     * <dl>
     * <dt><i>CMA_FIRST</i>
     *     <dd>Places a column at the front of the list of columns.
     * <dt><i>CMA_END</i>
     *     <dd>Places a column at the end of the list of columns.
     * </dl>
     *
     * @param width           Used to specify the width of a column. The default is
     *                        an automatically sized column that is always the width
     *                        of its widest element. If this field is set and the data
     *                        is too wide, the data is truncated.
     */

    void add_column( PVOID title, ULONG title_options,
                     ULONG data_offset, ULONG data_options, ULONG pos = CMA_END, ULONG width = 0 );
    /**
     * Sets the position of the vertical split bar.
     *
     * @param x   The position of the split bar relative to the
     *            container, used in the details view. If this value is
     *            less than 0, the split bar is not used.
     * @param pos Number of the last column in the left window of the
     *            split details view, or 0. The default is 0, which causes
     *            all columns to be positioned in the left window.
     */

    void splitbar( LONG x, LONG pos = 0 );

    /**
     * Returns the position of the vertical split bar.
     *
     * Returns the position of the split bar relative to the
     * container, used in the details view. If this value is
     * less than 0, the split bar is not used.
     */

    LONG splitbar() const;

    /** Returns the number of records in the container. */
    ULONG count() const;
    /** Returns the number of child records of <i>rec</i>. */
    ULONG count( TRecord* rec ) const;

    /**
     * Allocates memory for one record.
     *
     * The container control requires that the application use this
     * method to allocate memory for container records.
     */

    TRecord* allocate();

    /**
     * Frees the memory associated with one record.
     *
     * It is the application's responsibility to free all
     * application-allocated memory associated with the container
     * records, such as text strings. You can use class destructor
     * for this purpose.
     */

    void free( TRecord* rec );

    /**
     * Inserts one record into the container control.
     *
     * @param rec     Pointer to the record to insert.
     * @param order   Orders the record relative to other record in
     *                the container. The values can be:
     * <dl>
     * <dt><i>CMA_FIRST</i>
     *     <dd>Places a record at the beginning of the list of records.
     * <dt><i>CMA_END</i>
     *     <dd>Places a record at the end of the list of records.
     * <dt><i>Other</i>
     *     <dd>Pointer to a record after which this record is to be inserted.
     * </dl>
     *
     * @param parent  Pointer to a record that is the parent of the records
     *                to be inserted. This field is used only with the
     *                <i>CMA_FIRST</i> or <i>CMA_END</i> attributes of the <i>order</i>.
     * @param refresh The display is automatically updated after a record is inserted.
     */

    void insert( TRecord* rec, TRecord* order  = (TRecord*)CMA_END,
                               TRecord* parent = NULL, BOOL refresh = TRUE );
    /**
     * Removes one record from the container control.
     *
     * When parent item records are removed, all associated child item
     * records are removed, as well.
     *
     * @param rec     Pointer to the record that is to be removed.
     * @param option  Flags that show whether memory must be freed
     *                and container records invalidated:
     * <dl>
     * <dt><i>CMA_FREE</i>
     *     <dd>If specified, record is removed and memory associated with
     *         record is freed. If not specified, record are removed and no memory
     *         is freed.
     * <dt><i>CMA_INVALIDATE</i>
     *     <dd>If specified, after record is removed the container is invalidated
     *         and any necessary repositioning of the container records
     *         is performed.
     * </dl>
     */

    void remove( TRecord* rec, USHORT options = CMA_FREE | CMA_INVALIDATE );

    /**
     * Removes records from the container control.
     *
     * When parent item records are removed, all associated child item
     * records are removed, as well.
     *
     * @param recs    Pointer to an array of pointers to records that are to be removed.
     * @param count   Number of records.
     * @param option  Flags that show whether memory must be freed
     *                and container records invalidated:
     * <dl>
     * <dt><i>CMA_FREE</i>
     *     <dd>If specified, record is removed and memory associated with
     *         record is freed. If not specified, record are removed and no memory
     *         is freed.
     * <dt><i>CMA_INVALIDATE</i>
     *     <dd>If specified, after record is removed the container is invalidated
     *         and any necessary repositioning of the container records
     *         is performed.
     * </dl>
     */

    void remove( TRecord** recs, ULONG count, USHORT options = CMA_FREE | CMA_INVALIDATE );

    /**
     * Moves a record to a new parent in the container control.
     *
     * @param rec         Record to be moved.
     * @param target_rec  New parent for moved record.
     * @param order       Record order for siblings. The values can be:
     *
     * <dl>
     * <dt><i>CMA_FIRST</i>
     *     <dd>Record moves to the FIRST child position of parent. If <i>target_rec</i>
     *         is NULL, record becomes the first root level record of the container.
     * <dt><i>CMA_END</i>
     *     <dd>Record moves to the LAST child position of parent. If <i>target_rec</i>
     *         is NULL, record becomes the last root level record of the container.
     * <dt><i>Other</i>
     *     <dd>Record moves after this record in the list of children of parent.
     *         If <i>target_rec</i> is NULL, record moves after the record specified
     *         by <i>order</i> only if that record is also a root level record.<br>
     *         <b>Note: </b>This record must currently exist in the list of
     *         children of <i>target_rec</i>.
     * </dl>
     */

    BOOL move_tree( TRecord* rec, TRecord* target_rec, TRecord* order = (TRecord*)CMA_END );

    /**
     * Removes all records from the container control.
     *
     * @param option  Flags that show whether memory must be freed
     *                and container records invalidated:
     * <dl>
     * <dt><i>CMA_FREE</i>
     *     <dd>If specified, records are removed and memory associated with
     *         records is freed. If not specified, records are removed and no memory
     *         is freed.
     * <dt><i>CMA_INVALIDATE</i>
     *     <dd>If specified, after records are removed the container is invalidated
     *         and any necessary repositioning of the container records
     *         is performed.
     * </dl>
     */

    void clear( USHORT options = CMA_FREE | CMA_INVALIDATE );

    /**
     * Notifies the container control that the record is not
     * valid and must be refreshed.
     *
     * @param rec     Pointer to a record that are to be refreshed.
     * @param options Flags used to optimize container record invalidation.
     *                The <i>CMA_REPOSITION</i>, <i>CMA_NOREPOSITION</i>, and
     *                <i>CMA_TEXTCHANGED</i> attributes are mutually exclusive.
     *                However, any of them can be combined with the <i>CMA_ERASE</i>
     *                attribute:
     * <p>
     * <dl>
     * <dt><i>CMA_ERASE</i>
     *     <dd>Flag used when the icon view is displayed to minimize painting
     *         of a container record's background when it has changed. If specified,
     *         the background is erased when the display is refreshed. The default
     *         is to not erase the background when the display is refreshed.
     * <dt><i>CMA_REPOSITION</i>
     *     <dd>Flag used to reposition all container records. This flag must be used
     *         if container records are inserted or removed, or if many changes have
     *         occurred. If a container record is inserted, the <i>rec</i> parameter
     *         points to the inserted record. If a container record is removed, the
     *         <i>rec</i> parameter points to the record that precedes the removed
     *         one.
     * <dt><i>CMA_NOREPOSITION</i>
     *     <dd>Flag used to indicate that container records do not need to be
     *         repositioned. The container draws the record pointed
     *         to in the <i>rec</i> parameter. The container does not do any validation;
     *         therefore it is the application's responsibility to make sure
     *         repositioning is not needed or changing the longest text line is
     *         not necessary.
     * <dt><i>CMA_TEXTCHANGED</i>
     *     <dd>Flag used if text has changed and you do not know whether repositioning
     *         is needed. The container determines whether the longest line or the
     *         height of the record has changed. If so, the container repositions
     *         and redraws the necessary visible container records.
     * </dl>
     */

    void refresh( TRecord* rec, USHORT options );

    /**
     * Notifies the container control that all records is not
     * valid and must be refreshed.
     *
     * @param options Flags used to optimize container record invalidation.
     *                The <i>CMA_REPOSITION</i>, <i>CMA_NOREPOSITION</i>, and
     *                <i>CMA_TEXTCHANGED</i> attributes are mutually exclusive.
     *                However, any of them can be combined with the <i>CMA_ERASE</i>
     *                attribute:
     * <p>
     * <dl>
     * <dt><i>CMA_ERASE</i>
     *     <dd>Flag used when the icon view is displayed to minimize painting
     *         of a container record's background when it has changed. If specified,
     *         the background is erased when the display is refreshed. The default
     *         is to not erase the background when the display is refreshed.
     * <dt><i>CMA_REPOSITION</i>
     *     <dd>Flag used to reposition all container records. This flag must be used
     *         if container records are inserted or removed, or if many changes have
     *         occurred. If a container record is inserted, the <i>rec</i> parameter
     *         points to the inserted record. If a container record is removed, the
     *         <i>rec</i> parameter points to the record that precedes the removed
     *         one.
     * <dt><i>CMA_NOREPOSITION</i>
     *     <dd>Flag used to indicate that container records do not need to be
     *         repositioned. The container draws the record pointed
     *         to in the <i>rec</i> parameter. The container does not do any validation;
     *         therefore it is the application's responsibility to make sure
     *         repositioning is not needed or changing the longest text line is
     *         not necessary.
     * <dt><i>CMA_TEXTCHANGED</i>
     *     <dd>Flag used if text has changed and you do not know whether repositioning
     *         is needed. The container determines whether the longest line or the
     *         height of the record has changed. If so, the container repositions
     *         and redraws the necessary visible container records.
     * </dl>
     */

    void refresh( USHORT options = CMA_REPOSITION );

    /**
     * Sorts current and inserted container records in the container control.
     *
     * @param pcompare    Pointer to a comparison function. If NULL, no sorting is performed.
     *                    This function is called one or more times during the sorting
     *                    process and is passed pointers to two <i>TRecord</i> structures on
     *                    each call. The routine must compare this structures, and then
     *                    return one of the following values:<p>
     *                    >0 if <i>p1</i> is less than <i>p2</i>.<br>
     *                    =0 if <i>p1</i> is equal to <i>p2</i>.<br>
     *                    <0 if <i>p1</i> is greater than <i>p2</i>.
     */

    void sort( SHORT (EXPENTRY * pcompare)( TRecord* p1, TRecord* p2, PMContainer* container ));

    /**
     * Filters the contents of a container so that a subset of the container items is viewable.
     *
     * @param  pfilter    Points to an application-provided function that determines
     *                    whether a record is to be included in the viewable subset.
     * @return TRUE       A subset was successfully created.
     */

    BOOL filter( BOOL (EXPENTRY * pfilter)( TRecord* p, PMContainer* container ));

    /**
     * Filters the contents of a container so that a subset of the container items is viewable.
     *
     * @param  pfilter    Points to an application-provided function that determines
     *                    whether a record is to be included in the viewable subset.
     * @param  storage    Available for application use.
     *
     * @return TRUE       A subset was successfully created.
     */

    BOOL filter( BOOL (EXPENTRY * pfilter)( TRecord* p, PVOID storage ), PVOID storage );

    /**
     * Causes one parent item in the tree view to
     * be expanded.
     */

    void expand( TRecord* rec, BOOL expandtree = TRUE );

    /**
     * Causes one parent item in the tree view to
     * be collapsed.
     */

    void collapse( TRecord* rec ) {
      expand( rec, FALSE );
    }

    /**
     * Specifies that a record will be drawn with
     * selected-state emphasis.
     */

    void select( TRecord* rec, BOOL set = TRUE );

    /**
     * Specifies that a record will be drawn with
     * in-use emphasis.
     */

    void in_use( TRecord* rec, BOOL set = TRUE );

    /**
     * Specifies that a record will be drawn with
     * source emphasis.
     */

    void source( TRecord* rec, BOOL set = TRUE );

    /**
     * Scrolls the container window so that the
     * specified record became visible.
     */

    void scroll_to( TRecord* rec );

    /**
     * Returns the TRUE if the specified parent item in the
     * tree is expanded.
     */

    BOOL is_expanded( TRecord* rec  ) const {
      if( WinSendMsg( handle(), CM_QUERYRECORDINFO, MPFROMP( &rec ), MPFROMLONG( 1 ))) {
        return rec->flRecordAttr & CRA_EXPANDED;
      }
      return FALSE;
    }

    /**
     * Returns the TRUE if the specified parent item in the
     * tree is collapsed.
     */

    BOOL is_collapsed( TRecord* rec ) const {
      return !is_expanded( rec );
    }

    /** Returns the TRUE if the specified item is cursored. */
    BOOL is_cursored( TRecord* rec ) const {
      if( WinSendMsg( handle(), CM_QUERYRECORDINFO, MPFROMP( &rec ), MPFROMLONG( 1 ))) {
        return rec->flRecordAttr & CRA_CURSORED;
      }
      return FALSE;
    }

    /** Returns the TRUE if the specified item is selected. */
    BOOL is_selected( TRecord* rec ) const {
      if( WinSendMsg( handle(), CM_QUERYRECORDINFO, MPFROMP( &rec ), MPFROMLONG( 1 ))) {
        return rec->flRecordAttr & CRA_SELECTED;
      }
      return FALSE;
    }

    /** Returns the TRUE if the specified item is drawn with in-use emphasis. */
    BOOL is_in_use( TRecord* rec ) const {
      if( WinSendMsg( handle(), CM_QUERYRECORDINFO, MPFROMP( &rec ), MPFROMLONG( 1 ))) {
        return rec->flRecordAttr & CRA_INUSE;
      }
      return FALSE;
    }

    /** Returns the TRUE if the specified item is drawn with source emphasis. */
    BOOL is_source( TRecord* rec ) const {
      if( WinSendMsg( handle(), CM_QUERYRECORDINFO, MPFROMP( &rec ), MPFROMLONG( 1 ))) {
        return rec->flRecordAttr & CRA_SOURCE;
      }
      return FALSE;
    }

    /** If the specified record is in the container, TRUE is returned. */
    BOOL contains( TRecord* rec ) const;

    /** Returns a pointer to the first record in the container. */
    TRecord* first() const {
      return record( NULL, CMA_FIRST );
    }

    /** Returns a pointer to the first child record of <i>rec</i>. */
    TRecord* firstchild( TRecord* rec ) const {
      return record( rec, CMA_FIRSTCHILD );
    }

    /** Returns a pointer to the last record in the container. */
    TRecord* last() const {
      return record( NULL, CMA_LAST );
    }

    /** Returns a pointer to the last child record of <i>rec</i>. */
    TRecord* lastchild ( TRecord* rec ) const {
      return record( rec, CMA_LASTCHILD );
    }

    /** Returns a pointer to the next record of <i>rec</i>. */
    TRecord* next( TRecord* rec ) const {
      return record( rec, CMA_NEXT );
    }

    /** Returns a pointer to the previous record of <i>rec</i>. */
    TRecord* prev( TRecord* rec ) const {
      return record( rec, CMA_PREV );
    }

    /** Returns a pointer to the parent record of <i>rec</i>. */
    TRecord* parentrecord( TRecord* rec ) const {
      return record( rec, CMA_PARENT );
    }

    /** Returns a pointer to the current cursored record. */
    TRecord* cursored() const {
      return emphasis_record((TRecord*)CMA_FIRST, CRA_CURSORED );
    }

    /** Returns a pointer to the current selected record. */
    TRecord* selected() const {
      return emphasis_record((TRecord*)CMA_FIRST, CRA_SELECTED );
    }

    /** Returns a pointer to the next selected record. */
    TRecord* selected( TRecord* rec ) const {
      return emphasis_record( rec,  CRA_SELECTED );
    }

  protected:

    /**
     * Dispatch system native events.
     *
     * PMContainer calls this function when a system native window
     * event occurs.
     */

    virtual MRESULT dispatch( ULONG msg, MPARAM mp1, MPARAM mp2 );

  private:
    /** Returns a pointer to the requested record structure. */
    TRecord* record( TRecord* rec, USHORT cmd ) const;
    /** Returns a pointer to the record structure with the specified emphasis attributes. */
    TRecord* emphasis_record( TRecord* rec, USHORT mask ) const;
    /** Returns a pointer to the column structure. */
    PFIELDINFO column( LONG pos );

    BOOL m_is_tree;
};

/* Constructs the container control window object
 * from an existing presentation window handle.
 */

template <class TRecord>
inline PMContainer<TRecord>::PMContainer( HWND handle )

: PMWindow ( handle ),
  m_is_tree( FALSE  )
{
  handle_events();
}

/* Constructs the container control window object from
 * an existing child window with the specified identity.
 */

template <class TRecord>
inline PMContainer<TRecord>::PMContainer( HWND hparent, SHORT id )

: PMWindow ( hparent, id ),
  m_is_tree( FALSE       )
{
  handle_events();
}

/* Constructs the container control window.
 */

template <class TRecord>
inline PMContainer<TRecord>::PMContainer( SHORT id, HWND hparent,
                                          LONG x, LONG y, LONG cx, LONG cy, ULONG style )

: PMWindow ( WC_CONTAINER, id, "", hparent, hparent,
             x, y, cx, cy, style, NULL ),
  m_is_tree( FALSE       )
{}

/* Destructs the container control window.
 */

template <class TRecord>
inline PMContainer<TRecord>::~PMContainer() {
  title( NULL );
}

/* Sets the attributes of a container control.
 */

template <class TRecord>
inline void PMContainer<TRecord>::attributes( ULONG options )
{
  CNRINFO cnrinfo = {0};

  cnrinfo.cb = sizeof(cnrinfo);
  cnrinfo.flWindowAttr = options;

  if( !send( CM_SETCNRINFO, MPFROMP( &cnrinfo ), MPFROMLONG( CMA_FLWINDOWATTR ))) {
    PM_THROW_GUIERROR();
  }
}

/* Sets the icon or bitmap size for all objects.
 */

template <class TRecord>
inline void PMContainer<TRecord>::icon_size( long cx, long cy )
{
  CNRINFO cnrinfo   = {0};
  LONG    cyicon    = WinQuerySysValue( HWND_DESKTOP, SV_CYICON ) / 2;
  LONG    cxicon    = WinQuerySysValue( HWND_DESKTOP, SV_CXICON ) / 2;
  ULONG   cnrinfofl = CMA_SLBITMAPORICON;

  cnrinfo.cb = sizeof(cnrinfo);
  cnrinfo.slBitmapOrIcon.cx = cx;
  cnrinfo.slBitmapOrIcon.cy = cy;

  if( cy <= cyicon ) {
    cnrinfo.slTreeBitmapOrIcon.cx = cxicon == 16 ? 14 : 17;
    cnrinfo.slTreeBitmapOrIcon.cy = cyicon == 16 ? 14 : 17;
    cnrinfo.cxTreeIndent          = cxicon;

    cnrinfofl |= CMA_SLTREEBITMAPORICON | CMA_CXTREEINDENT;
  }

  if( !send( CM_SETCNRINFO, MPFROMP( &cnrinfo ), MPFROMLONG( cnrinfofl ))) {
    PM_THROW_GUIERROR();
  }
}

/* Sets the amount of horizontal space between levels in the tree view.
 */

template <class TRecord>
inline void PMContainer<TRecord>::tree_indent( long cx )
{
  CNRINFO cnrinfo = {0};

  cnrinfo.cb = sizeof(cnrinfo);
  cnrinfo.cxTreeIndent = cx;

  if( !send( CM_SETCNRINFO, MPFROMP( &cnrinfo ), MPFROMLONG( CMA_CXTREEINDENT ))) {
    PM_THROW_GUIERROR();
  }
}

/* Returns the attributes of a container control.
 */

template <class TRecord>
inline ULONG PMContainer<TRecord>::attributes() const
{
  CNRINFO cnrinfo = {0};

  if( WinSendMsg( handle(), CM_QUERYCNRINFO, MPFROMP( &cnrinfo ),
                                             MPFROMLONG( sizeof( cnrinfo ))) == 0 )
  {
    PM_THROW_GUIERROR();
  }

  return cnrinfo.flWindowAttr;
}

/* Sets the position of the vertical split bar.
 */

template <class TRecord>
inline void PMContainer<TRecord>::splitbar( LONG x, LONG pos )
{
  CNRINFO cnrinfo = {0};

  cnrinfo.cb             = sizeof(cnrinfo);
  cnrinfo.xVertSplitbar  = x;
  cnrinfo.pFieldInfoLast = column( pos );

  if( !send( CM_SETCNRINFO, MPFROMP( &cnrinfo ),
             MPFROMLONG( CMA_XVERTSPLITBAR | CMA_PFIELDINFOLAST )))
  {
    PM_THROW_GUIERROR();
  }
}

/* Returns the position of the vertical split bar.
 */

template <class TRecord>
inline LONG PMContainer<TRecord>::splitbar() const
{
  CNRINFO cnrinfo = {0};

  if( WinSendMsg( handle(), CM_QUERYCNRINFO, MPFROMP( &cnrinfo ),
                            MPFROMLONG( sizeof( cnrinfo ))) == 0 )
  {
    PM_THROW_GUIERROR();
  }

  return cnrinfo.xVertSplitbar;
}

/* Returns the number of child records of <i>rec</i>.
 */

template <class TRecord>
inline ULONG PMContainer<TRecord>::count( TRecord* rec ) const
{
  TRecord* child;
  ULONG    records = 0;

  for( child = firstchild( rec ); child; child = next( child )) {
    records += count( child ) + 1;
  }

  return records;
}

/* Returns the number of records in the container.
 */

template <class TRecord>
inline ULONG PMContainer<TRecord>::count() const
{
  if( m_is_tree )
  {
    ULONG    records = 0;
    TRecord* rec;

    for( rec = first(); rec; rec = next( rec )) {
      records += count( rec ) + 1;
    }

    return records;
  }
  else
  {
    CNRINFO cnrinfo = {0};

    if( WinSendMsg( handle(), CM_QUERYCNRINFO, MPFROMP( &cnrinfo ),
                              MPFROMLONG( sizeof( cnrinfo ))) == 0 )
    {
      PM_THROW_GUIERROR();
    }

    return cnrinfo.cRecords;
  }
}

/* Sets the container title.
 */

template <class TRecord>
inline void PMContainer<TRecord>::title( const char* text )
{
  CNRINFO cnrinfo = {0};
  char*   old;

  if( send( CM_QUERYCNRINFO, MPFROMP( &cnrinfo ), MPFROMLONG( sizeof( cnrinfo ))) == 0 ) {
    PM_THROW_GUIERROR();
  }

  old = cnrinfo.pszCnrTitle;
  cnrinfo.pszCnrTitle = text ? strdup( text ) : NULL;

  if( !send( CM_SETCNRINFO, MPFROMP( &cnrinfo ), MPFROMLONG( CMA_CNRTITLE ))) {
    PM_THROW_GUIERROR();
  }

  ::free( old );
}

/* Adds column to the details view of the container control.
 */

template <class TRecord>
inline void PMContainer<TRecord>::add_column( PVOID title, ULONG title_options,
                                              ULONG data_offset, ULONG data_options,
                                              ULONG pos, ULONG width )
{
  FIELDINFO* field;
  FIELDINFOINSERT insert;

  field = (FIELDINFO*)send( CM_ALLOCDETAILFIELDINFO, MPFROMSHORT(1), 0 );

  if( field == 0 ) {
    PM_THROW_GUIERROR();
  }

  field->cb         = sizeof( *field );
  field->flData     = data_options;
  field->flTitle    = title_options;
  field->pTitleData = title;
  field->offStruct  = data_offset;
  field->cxWidth    = width;

  insert.cb = sizeof(FIELDINFOINSERT);
  insert.pFieldInfoOrder = (PFIELDINFO)pos;
  insert.fInvalidateFieldInfo = TRUE;
  insert.cFieldInfoInsert = 1;

  if( send( CM_INSERTDETAILFIELDINFO, MPFROMP( field ), MPFROMP( &insert )) == 0 ) {
    PM_THROW_GUIERROR();
  }
}

/* Allocates memory for one record.
 */

template <class TRecord>
inline TRecord* PMContainer<TRecord>::allocate()
{
  TRecord* rec =
    (TRecord*)send( CM_ALLOCRECORD,
                    MPFROMLONG( sizeof( TRecord ) - sizeof( RECORDCORE )),
                    MPFROMLONG( 1 ));

  if( rec == NULL ) {
    PM_THROW_GUIERROR();
  }
  return new(rec) TRecord;
}

/* Frees the memory associated with one record.
 */

template <class TRecord>
inline void PMContainer<TRecord>::free( TRecord* rec )
{
  rec->~TRecord();
  send( CM_FREERECORD, MPFROMP( &rec ), MPFROMSHORT( 1 ));
}

/* Inserts one record into the container control.
 */

template <class TRecord>
inline void PMContainer<TRecord>::insert( TRecord* rec, TRecord* order,
                                                        TRecord* parent, BOOL refresh )
{
  RECORDINSERT ins;

  ins.cb                = sizeof(RECORDINSERT);
  ins.pRecordOrder      = order;
  ins.pRecordParent     = parent;
  ins.fInvalidateRecord = refresh;
  ins.zOrder            = CMA_TOP;
  ins.cRecordsInsert    = 1;

  if( send( CM_INSERTRECORD, MPFROMP( rec ), MPFROMP( &ins )) == 0 ) {
    PM_THROW_GUIERROR();
  }

  if( parent ) {
    m_is_tree = TRUE;
  }
}

/* Removes one record from the container control.
 */

template <class TRecord>
inline void PMContainer<TRecord>::remove( TRecord* rec, USHORT options )
{
  TRecord* child;

  if( m_is_tree ) {
    while(( child = firstchild( rec )) != NULL ) {
      remove( child, options );
    }
  }

  if( send( CM_REMOVERECORD, MPFROMP( &rec ),
            MPFROM2SHORT( 1, options & ~CMA_FREE )) == MRFROMLONG( -1 ))
  {
    PM_THROW_GUIERROR();
  }
  if( options & CMA_FREE ) {
    free( rec );
  }
}

/* Removes records from the container control.
 */

template <class TRecord>
inline void PMContainer<TRecord>::remove( TRecord** recs, ULONG count, USHORT options )
{
  ULONG i;

  if( m_is_tree ) {
    for( i = 0; i < count; i++ ) {
      remove( recs[i], (USHORT)( options & ~CMA_INVALIDATE ));
    }
  } else {
    USHORT short_count = (USHORT)(( count > 65535 ) ? 65535 : count );
    ULONG  done = 0;

    while( count ) {
      if( send( CM_REMOVERECORD, MPFROMP( recs + done ),
                MPFROM2SHORT( short_count, 0 )) == MRFROMLONG( -1 ))
      {
        PM_THROW_GUIERROR();
      }
      if( options & CMA_FREE ) {
        for( i = 0; i < short_count; i++ ) {
          recs[done+i]->~TRecord();
        }
        if( send( CM_FREERECORD, MPFROMP( recs + done ),
                                 MPFROMSHORT( short_count )) == MRFROMLONG( -1 ))
        {
          PM_THROW_GUIERROR();
        }
      }
      done  += short_count;
      count -= short_count;
      short_count = (USHORT)(( count > 65535 ) ? 65535 : count );
    }
  }
  if( options & CMA_INVALIDATE ) {
    refresh( CMA_REPOSITION );
  }
}

/* Moves a record to a new parent in the container control.
 */

template <class TRecord>
inline BOOL PMContainer<TRecord>::move_tree( TRecord* rec, TRecord* target_rec, TRecord* order )
{
  TREEMOVE treemove;

  treemove.preccMove      = rec;
  treemove.preccNewParent = target_rec;
  treemove.pRecordOrder   = order;
  treemove.flMoveSiblings = FALSE;

  return LONGFROMMR( send( CM_MOVETREE, MPFROMP( &treemove ), 0 ));
}

/* Removes all records from the container control.
 */

template <class TRecord>
inline void PMContainer<TRecord>::clear( USHORT options )
{
  TRecord* rec;

  if( m_is_tree ) {
    while(( rec = last()) != NULL ) {
      remove( rec, (USHORT)( options & ~CMA_INVALIDATE ));
    }
    if( options & CMA_INVALIDATE ) {
      refresh( CMA_REPOSITION );
    }
  } else {
    unsigned int recs_count = 0;
    unsigned int recs_size  = 0;
    TRecord**    recs       = NULL;
    TRecord*     rec;

    for( rec = last(); rec; rec = prev( rec )) {
      if( recs_count == recs_size ) {
        recs_size += 1000;
        recs = (TRecord**)realloc( recs, recs_size * sizeof( TRecord* ));
        if( !recs ) {
          PM_THROW_CLIBERROR();
        }
      }
      recs[recs_count++] = rec;
    }
    if( recs_count )
    {
      ULONG  i;

      if( send( CM_REMOVERECORD, MPFROMP( NULL ),
                MPFROM2SHORT( 0, options & ~CMA_FREE )) == MRFROMLONG( -1 ))
      {
        PM_THROW_GUIERROR();
      }
      if( options & CMA_FREE ) {
        for( i = 0; i < recs_count; i++ ) {
          free( recs[i] );
        }
      }
      ::free( recs );
    }
  }
}

/* Notifies the container control that the record is not
 * valid and must be refreshed.
 */

template <class TRecord>
inline void PMContainer<TRecord>::refresh( TRecord* rec, USHORT options ) {
  send( CM_INVALIDATERECORD, MPFROMP( &rec ), MPFROM2SHORT( 1, options ));
}

/* Sorts current and inserted container records in the container control.
 */

template <class TRecord>
inline void PMContainer<TRecord>::sort( SHORT (EXPENTRY * pcompare)( TRecord* p1,
                                                                     TRecord* p2, PMContainer* container ))
{
  CNRINFO cnrinfo = {0};

  if( send( CM_QUERYCNRINFO, MPFROMP( &cnrinfo ),
                             MPFROMLONG( sizeof( cnrinfo ))) == 0 )
  {
    PM_THROW_GUIERROR();
  }

  if( cnrinfo.pSortRecord == pcompare ) {
    if( pcompare ) {
      send( CM_SORTRECORD, MPFROMP( pcompare ), MPFROMP( this ));
    }
  } else {
    cnrinfo.cb = sizeof(cnrinfo);
    cnrinfo.pSortRecord = pcompare;

    if( !send( CM_SETCNRINFO, MPFROMP( &cnrinfo ), MPFROMLONG( CMA_PSORTRECORD ))) {
      PM_THROW_GUIERROR();
    }
  }
}

/* Filters the contents of a container so that a subset of the container
 * items is viewable.
 */

template <class TRecord>
inline BOOL PMContainer<TRecord>::filter( BOOL (EXPENTRY * pfilter)( TRecord* p, PMContainer* container ))
{
  return LONGFROMMR( send( CM_FILTER, MPFROMP( pfilter ), MPFROMP( this )));
}

/* Filters the contents of a container so that a subset of the container
 * items is viewable.
 */

template <class TRecord>
inline BOOL PMContainer<TRecord>::filter( BOOL (EXPENTRY * pfilter)( TRecord* p, PVOID storage ), PVOID storage )
{
  return LONGFROMMR( send( CM_FILTER, MPFROMP( pfilter ), MPFROMP( storage )));
}

/* Notifies the container control that all records is not
 * valid and must be refreshed.
 */

template <class TRecord>
inline void PMContainer<TRecord>::refresh( USHORT options ) {
  send( CM_INVALIDATERECORD, NULL, MPFROM2SHORT( 0, options ));
}

/* Causes one parent item in the tree view to
 * be expanded or collapsed.
 */

template <class TRecord>
inline void PMContainer<TRecord>::expand( TRecord* rec, BOOL expandtree ) {
  send( expandtree ? CM_EXPANDTREE : CM_COLLAPSETREE, MPFROMP( rec ), 0 );
}

/* Returns a pointer to the requested record structure. */
template <class TRecord>
inline TRecord* PMContainer<TRecord>::record( TRecord* rec, USHORT cmd ) const
{
  TRecord* rc = (TRecord*)WinSendMsg( handle(), CM_QUERYRECORD, MPFROMP( rec ),
                                      MPFROM2SHORT( cmd, CMA_ITEMORDER ));
  if( rc != (TRecord*)-1 ) {
    return rc;
  } else {
    return NULL;
  }
}

/* Returns a pointer to the record structure with the specified
 * emphasis attributes.
 */

template <class TRecord>
inline TRecord* PMContainer<TRecord>::emphasis_record( TRecord* rec, USHORT mask ) const
{
  TRecord* rc = (TRecord*)WinSendMsg( handle(), CM_QUERYRECORDEMPHASIS, MPFROMP( rec ),
                                      MPFROMSHORT( mask ));
  if( rc != (TRecord*)-1 ) {
    return rc;
  } else {
    return NULL;
  }
}

/* Returns a pointer to the column structure. */
template <class TRecord>
inline PFIELDINFO PMContainer<TRecord>::column( LONG pos )
{
  if( pos <= 0 ) {
    return NULL;
  } else {
    PFIELDINFO pfi =
      (PFIELDINFO)send( CM_QUERYDETAILFIELDINFO, 0, MPFROMLONG( CMA_FIRST ));

    while( --pos && pfi && pfi != (PFIELDINFO)-1 ) {
      pfi = (PFIELDINFO)send( CM_QUERYDETAILFIELDINFO, pfi, MPFROMLONG( CMA_NEXT ));
    }

    if( pfi == (PFIELDINFO)-1 ) {
      PM_THROW_GUIERROR();
    }

    return pfi;
  }
}

/* Specifies that a record will be drawn with
 * selected-state emphasis.
 */

template <class TRecord>
inline void PMContainer<TRecord>::select( TRecord* rec, BOOL set )
{
  if( set ) {
    send( CM_SETRECORDEMPHASIS, MPFROMP( rec ), MPFROM2SHORT( set, CRA_SELECTED | CRA_CURSORED ));
  } else {
    send( CM_SETRECORDEMPHASIS, MPFROMP( rec ), MPFROM2SHORT( set, CRA_SELECTED ));
  }
}

/* Specifies that a record will be drawn with
 * in-use emphasis.
 */

template <class TRecord>
inline void PMContainer<TRecord>::in_use( TRecord* rec, BOOL set ) {
  send( CM_SETRECORDEMPHASIS, MPFROMP( rec ), MPFROM2SHORT( set, CRA_INUSE ));
}

/* Specifies that a record will be drawn with
 * source emphasis.
 */

template <class TRecord>
inline void PMContainer<TRecord>::source( TRecord* rec, BOOL set ) {
  send( CM_SETRECORDEMPHASIS, MPFROMP( rec ), MPFROM2SHORT( set, CRA_SOURCE ));
}

/* If the specified record is in the container, TRUE is returned.
 */

template <class TRecord>
inline BOOL PMContainer<TRecord>::contains( TRecord* rec ) const {
  return (BOOL)WinSendMsg( handle(), CM_QUERYRECORDINFO, MPFROMP( &rec ), MPFROMSHORT(1));
}

/* Scrolls the container window so that the
 * specified record became visible.
 */

template <class TRecord>
inline void PMContainer<TRecord>::scroll_to( TRecord* rec )
{
  QUERYRECORDRECT prc_item;
  RECTL           rcl_record;
  RECTL           rcl_container;

  prc_item.cb                = sizeof( prc_item );
  prc_item.pRecord           = (PRECORDCORE)rec;
  prc_item.fRightSplitWindow = FALSE;
  prc_item.fsExtent          = CMA_ICON | CMA_TEXT;

  if( attributes() & CV_TREE ) {
    prc_item.fsExtent |= CMA_TREEICON;
  }

  if( send( CM_QUERYRECORDRECT, &rcl_record, &prc_item )) {
    if( send( CM_QUERYVIEWPORTRECT, &rcl_container, MPFROM2SHORT( CMA_WINDOW, FALSE ))) {
      if( rcl_record.yBottom < rcl_container.yBottom )
      {
        send( CM_SCROLLWINDOW, (MPARAM)CMA_VERTICAL,
                               (MPARAM)(rcl_container.yBottom - rcl_record.yBottom ));
      }
      else if( rcl_record.yTop > rcl_container.yTop )
      {
        send( CM_SCROLLWINDOW, (MPARAM)CMA_VERTICAL,
                               (MPARAM)(rcl_container.yTop - rcl_record.yTop ));
      }
    }
  }
}

/* Dispatch system native events.
 *
 * PMContainer calls this function when a system native window
 * event occurs.
 */

template <class TRecord>
inline MRESULT PMContainer<TRecord>::dispatch( ULONG msg, MPARAM mp1, MPARAM mp2 )
{
  switch( msg ) {
    case WM_TRANSLATEACCEL:
    {
      // Check for SV_CONTEXTMENUKB translation
      // Low word is the virtual key code (VK_*)
      // High word is the keyboard control code (KC_*)

      PQMSG pqmsg = (PQMSG)mp1;
      ULONG svKey = WinQuerySysValue( HWND_DESKTOP, SV_CONTEXTMENUKB );

      // Because the keyboard does not really send the exact same
      // keyboard control codes, we need to do the checking in
      // several stages:
      //
      //  - bits 0 thru 2 must have the desired bits turned on, but
      //    may also have others (KC_CHAR, KC_VIRTUALKEY, KC_SCANCODE)
      //  - bits 3 thru 7 must match (KC_SHIFT, KC_CTRL, KC_ALT,
      //    KC_KEYUP, KC_KEYDOWN)
      //  - bits 8 thru 15 can be ignored
      //  - the virtual key (VK_*) values must match

      if(( SHORT1FROMMP( pqmsg->mp1 ) & SHORT2FROMMP( svKey ) & 0x07 ) &&
        (( SHORT1FROMMP( pqmsg->mp1 ) & 0xF8 ) == ( SHORT2FROMMP( svKey ) & 0xF8 )) &&
         ( SHORT2FROMMP( pqmsg->mp2 ) == SHORT1FROMMP( svKey )))
      {
        // This is a popup menu request from the keyboard
        pqmsg->hwnd = handle();
        pqmsg->msg  = WM_CONTEXTMENU;
        pqmsg->mp1  = 0;
        pqmsg->mp2  = MPFROMLONG( 0x10000 );
        return MRFROMLONG( TRUE );
      }

      // Check for SV_TEXTEDITKB translation
      // Low word is the virtual key code (VK_*)
      // High word is the keyboard control code (KC_*)

      svKey = WinQuerySysValue( HWND_DESKTOP, SV_TEXTEDITKB );

      if(( SHORT1FROMMP( pqmsg->mp1 ) & SHORT2FROMMP( svKey ) & 0x07 ) &&
        (( SHORT1FROMMP( pqmsg->mp1 ) & 0xF8 ) == ( SHORT2FROMMP( svKey ) & 0xF8 )) &&
         ( SHORT2FROMMP( pqmsg->mp2 ) == SHORT1FROMMP( svKey )))
      {
        // This is a begin direct name edit request from the keyboard
        pqmsg->hwnd = handle();
        pqmsg->msg  = PM_TEXTEDIT;
        pqmsg->mp1  = 0;
        pqmsg->mp2  = 0;
        return MRFROMLONG( TRUE );
      }
      break;
    }

    case PM_TEXTEDIT:
    {
      ULONG       attrs = attributes();
      CNREDITDATA edata = { 0 };
      TRecord*    rec;

      if( attrs & CV_TREE ) {
        if(( rec = selected()) != NULL ) {
          edata.cb      = sizeof( edata );
          edata.hwndCnr = handle();
          edata.pRecord = rec;
          edata.id      = id();

          scroll_to( rec );
          post( CM_OPENEDIT, MPFROMP( &edata ), 0 );
        }
      } else if( attrs & CV_DETAIL ) {
        if(( rec = cursored()) != NULL )
        {
          ULONG id = CID_LEFTDVWND;
          CNRINFO cnrinfo  = { 0 };
          FIELDINFO* flast = NULL;
          FIELDINFO* finfo =
              (FIELDINFO*)send( CM_QUERYDETAILFIELDINFO, NULL, MPFROMSHORT( CMA_FIRST ));

          if( send( CM_QUERYCNRINFO, MPFROMP( &cnrinfo ), MPFROMLONG( sizeof( cnrinfo ))) > 0 ) {
            flast = cnrinfo.pFieldInfoLast;
          }

          while( finfo != NULL && finfo != (FIELDINFO*)-1 ) {
            if(( finfo->flData & CFA_STRING ) && !( finfo->flData & CFA_FIREADONLY )) {
              break;
            }
            if( finfo == flast ) {
              id = CID_RIGHTDVWND;
            }
            finfo = (FIELDINFO*)send( CM_QUERYDETAILFIELDINFO,
                                      MPFROMP( finfo ), MPFROMSHORT( CMA_NEXT ));
          }

          if( finfo != NULL && finfo != (FIELDINFO*)-1 ) {
            edata.cb         = sizeof( edata );
            edata.hwndCnr    = handle();
            edata.pRecord    = rec;
            edata.pFieldInfo = finfo;
            edata.id         = id;
          }

          scroll_to( rec );
          post( CM_OPENEDIT, MPFROMP( &edata ), 0 );
        }
      } else {
        if(( rec = cursored()) != NULL ) {
          edata.cb      = sizeof( edata );
          edata.hwndCnr = handle();
          edata.pRecord = rec;
          edata.id      = id();

          scroll_to( rec );
          post( CM_OPENEDIT, MPFROMP( &edata ), 0 );
        }
      }
      return 0;
    }
  }

  return PMWindow::dispatch( msg, mp1, mp2 );
}

#endif
