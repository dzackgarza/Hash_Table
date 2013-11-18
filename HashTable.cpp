/*****************************************************

    Zack Garza
    CISP 430 - TTH 5:30 pm
    Programming Project 6 - Hash Tables
    December 12, 2013

*****************************************************/

#include "HashTable.h"
#include <cstdlib>
#include <iostream>

using namespace std;

// Post: An empty HashTable is created and initialized
HashTable::HashTable( ) { }

// Post: The HashTable is destroyed and all memory is released
HashTable::~HashTable( )
{
    for (unsigned i = 0; i < MAX_HASH_SIZE; i++)
        contents[i].Delete();
}

// Pre:  There is room in the HashTable
// Post: The ItemType is inserted into the HashTable
// according to its key
void HashTable::Insert ( const ItemType& )
{
    // Hash Item
    // Insert into Hash Table
    // Relegate to DLList to insert
}

// Pre:  The HashTable is not empty
// Post: The ItemType with this key is returned.
// If the table does not contain an ItemType with this key it
// returns ItemType (“KEY NOT FOUND”,”KEY NOT FOUND”)
ItemType HashTable::Retrieve ( const KeyType& key )
{
    if (!IsEmpty())
    {
        // Search the table for the key and return a reference to it.
        // If found, return item
        // else return Record("KNF", "KEY NOT FOUND");
    }
}

// Pre: The HashTable is not empty
// Post: The ItemType with this key is removed from the
// HashTable
// If the key is not found, it does nothing
void HashTable::Delete ( const KeyType& key )
{
    if (!IsEmpty())
    {
        // Search the table for the key and delete it.
    }
}

// Post: Returns true if there is nothing in the HashTable
bool HashTable::IsEmpty ( ) const
{
    bool has_item = false;
    for (int i = 0; i < MAX_HASH_SIZE; i++)
    {
        if (this->contents[i].IsEmpty() == false) has_item = true;
    }
    return has_item;
}

/************************** Helper Functions **********************/

// Given an item, generates a hash for it that is as unique as possible.
unsigned Hash_Function( const ItemType& R)
{
    unsigned index;

    // Go through each character in the STRING
    for (unsigned i = 0; i < R.Key().length(); i++)
    {
        // Sum the values of each character, weighted by its position in the STRING.
        index += R.Key()[i] * (i+1);
    }
    // Modulo, so it will fit into the Hash Table
    return (index % MAX_HASH_SIZE);
}
