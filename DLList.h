/*****************************************************

    Zack Garza
    CISP 430 - TTH 5:30 pm
    Programming Project 3 - Doubly Linked Lists
    October 10, 2013

*****************************************************/

#ifndef DLL_CLASS_H
#define DLL_CLASS_H
#include <string>
#include "Record.h"
typedef Record ItemType;

/**
Class Invariants:

    If a DLList exists, HEAD points to the first element in the list,
    while CURSOR points to the current position in the list at all times.
    A DLList always has HEAD and CURSOR pointers, even if they are empty.

    A NODE only exists if it is created explicitly. Each NODE contains
    pointers to the previous and next NODEs, if they exist, and always
    contain the data explicitly set at their creation.
**/

class DLList {

    struct node
    {
        node* previous;
        node* next;
        ItemType data;

        // Explicit node constructor - manually set pointers
        node(ItemType init, node* prev, node* nex) : data(init), previous(prev), next(nex) {}
        // Implicit node constructor - just pass in a value to create a node
        node(ItemType init) : data(init), previous(NULL), next(NULL) {}

    };
    node* head;
    node* cursor;
    public:

// Main Functions //

// Pre:  None.
// Post: An empty DLList is created.
DLList ( void );

// Pre:  A DLList exists.
// Post: A DLList is destroyed. All memory allocated to nodes is freed.
~DLList ( void );

// Pre:  None
// Post: RETVAL = TRUE if the list is empty, FALSE if there are
//       one or more elements.
bool IsEmpty ( void ) const;

// Pre:  None
// Post: RETVAL = TRUE if the cursor is after last item or
//       before the first item in the list, FALSE if the
//       cursor is somewhere wihin the list.
bool EndOfList ( void ) const;

// Pre: !IsEmpty()
// Post: The cursor is moved to the first item in the list.
void Reset ( void );

// Pre: !IsEmpty() && !EndOfList()
//      In other words, list element i+1 must exist.
// Post: The cursor is moved to the next item in the list.
void Advance ( void );

// Pre: !IsEmpty() && !EndOfList()
//       Cursor can not be beyond the last item, and element i-1 must exist.
// Post: The cursor is moved to the previous item.
void Retreat ( void );

// Pre: !IsEmpty() && !EndOfList()
// Post: RETVAL == Value of the data contained in the node at cursor.
ItemType CurrentItem( void );

// Pre: !IsEmpty()&& !EndOfList()
// Post: Item at the cursor is deleted && the cursor points to the
//       successor of deleted item.
//       EndOfList() == TRUE if cursor points to the last (nth) element in the list.
//       IsEmpty() == TRUE if the item
//       deleted was the only remaining item in the list.
void Delete( void );

// Pre:  None
// Post: If the list was empty, then Inserted is the only item in
//       the list.
//       If EndOfList() was true, then Inserted is the new first
//       item in the list.
//       Otherwise, Inserted is the predecessor of
//       the item that was current when the function was called.
//       Inserted is the new current item.
void InsertBefore ( /*in*/ const ItemType& Inserted );

// Pre:  None
// Post: If the list was empty, then Inserted is the only item in
//       the list.
//       If EndOfList was true, then Inserted is the new last
//       item in the list.
//       Otherwise, Inserted is the successor of the
//       item that was current when the function was called.
//       Inserted is the new current item.
void InsertAfter ( /*in*/ const ItemType& Inserted );

// Pre:  None
// Post: List is displayed to standard out. Only for debugging.
void Display ( void );

// #TODO
//Post: If the list was empty then ITEM is the only item in the
//list. Otherwise, ITEM is inserted into the list so that the
//list is ordered from first key to last key.
void OrderedInsert ( /*in*/ const ItemType& ITEM );

};
#endif
