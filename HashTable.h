/*****************************************************

    Zack Garza
    CISP 430 - TTH 5:30 pm
    Programming Project 6 - Hash Tables
    December 12, 2013

*****************************************************/

#ifndef HASH_TABLE_DEF
#define HASH_TABLE_DEF

#include "DLList.h"
#include "Record.h"
#define MAX_HASH_SIZE 10

class HashTable
{
    DLList contents[MAX_HASH_SIZE];

public:
// Post: An empty HashTable is created and initialized
HashTable( );

// Post: The HashTable is destroyed and all memory is released
~HashTable( );

// Pre:  There is room in the HashTable
// Post: The ItemType is inserted into the HashTable
// according to its key
void Insert ( const ItemType& );

// Pre:  The HashTable is not empty
// Post: The ItemType with this key is returned.
// If the table does not contain an ItemType with this key it
// returns ItemType (“KEY NOT FOUND”,”KEY NOT FOUND”)
ItemType Retrieve ( const KeyType& key );

// Pre: The HashTable is not empty
// Post: The ItemType with this key is removed from the
// HashTable
// If the key is not found, it does nothing
void Delete ( const KeyType& key );

// Post: Returns true if there is nothing in the HashTable
bool IsEmpty ( ) const;

void PrintTable();

private:

unsigned Hash_Function( const KeyType&) const;


};
#endif
