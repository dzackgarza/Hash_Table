/*****************************************************

    Zack Garza
    CISP 430 - TTH 5:30 pm
    Programming Project 3 - Doubly Linked Lists
    October 10, 2013

*****************************************************/

#include <string>
#include <iostream>
#include "DLList.h"
using namespace std;

// Short Functions //
DLList::DLList ( void ) : head(NULL), cursor(NULL) {}

DLList::~DLList ( void )
{
    Reset();
    while(cursor != NULL) Delete();
}

bool DLList::IsEmpty ( void ) const { return (!head && !cursor ); }

bool DLList::EndOfList ( void ) const { return (cursor == NULL); }

void DLList::Reset ( void ) { if (!IsEmpty()) cursor = head; }

void DLList::Advance ( void ) { if (!IsEmpty() && !EndOfList()) cursor = cursor->next; }

void DLList::Retreat ( void ) { if (!IsEmpty() && !EndOfList()) cursor = cursor->previous; }

ItemType DLList::CurrentItem( void ) { if (!IsEmpty() && !EndOfList()) return cursor->data; }


// Long Functions //
void DLList::Delete( void )
{
    if (IsEmpty() || EndOfList()) return;

    node* temp = cursor->next;
    if (cursor == head)
        head = cursor->next;
    if (cursor->next != NULL)
        cursor->next->previous = cursor->previous;
    if (cursor->previous != NULL)
        cursor->previous->next = cursor->next;
    delete cursor;
    cursor = temp;
}

void DLList::InsertBefore ( const ItemType& Inserted )
{
    node* n = new node(Inserted);

    if (IsEmpty()) head = n;
    else if (EndOfList())
    {
        n->next = head;
        head->previous = n;
        head = n;
    }
    else
    {
        n->previous = cursor->previous;
        n->next = cursor;
        if (cursor->previous != NULL) cursor->previous->next = n;
        cursor->previous = n;
        if (cursor == head) head = n;
    }
    cursor = n;
}

void DLList::InsertAfter ( const ItemType& Inserted )
{
    node* n = new node(Inserted);

    if (IsEmpty()) head = n;
    else if (EndOfList())
    {
        Reset();
        while (cursor->next != NULL) Advance();
        n->previous = cursor;
        cursor->next = n;
    }
    else
    {
        n->previous = cursor;
        n->next = cursor->next;
        if (cursor->next != NULL) cursor->next->previous = n;
        cursor->next = n;
    }
    cursor = n;
}

void DLList::Display ( void )
{
    node* temp_cursor = cursor;
    Reset();
    while(cursor != NULL)
    {
        cout << "Data: '" << CurrentItem() << "'.\n";
        Advance();
    }
    cursor = temp_cursor;
}
