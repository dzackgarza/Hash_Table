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

HashTable::HashTable( ) { }

HashTable::~HashTable( )
{
    //for (unsigned i = 0; i < MAX_HASH_SIZE; i++)
        //contents[i].Delete();
}

void HashTable::Insert ( const ItemType& item)
{
    unsigned key = Hash_Function( item.Key() );
    contents[key].OrderedInsert(item);
}

ItemType HashTable::Retrieve ( const KeyType& k )
{
    // No use searching an empty Hash Table
    if ( !(this->IsEmpty()) )
    {
        unsigned key = Hash_Function(k);
        contents[key].Reset();
        // Stop searching when we reach an item bigger than the key.
        while ( !(contents[key].EndOfList()) && contents[key].CurrentItem().Key() <= k )
        {
            if ( contents[key].CurrentItem().Key() == k)
                return contents[key].CurrentItem();
            else
                contents[key].Advance();
        }
    }
    return ItemType("KNF","KEY NOT FOUND");
}

void HashTable::Delete ( const KeyType& k )
{
    // Return immediately if list at key's position is empty.
    if (!IsEmpty())
    {
        unsigned key = Hash_Function(k);

        // Search through list from beginning for a Record with a matching key.
        // Deletes all occurences that are found.
        contents[key].Reset();
        while ( !(contents[key].EndOfList()) )
        {
            if ( contents[key].CurrentItem().Key() == k)
                contents[key].Delete();
            else
                contents[key].Advance();
        }
    }
}

bool HashTable::IsEmpty ( ) const
{
    bool hasItem = false;
    for (int i = 0; i < MAX_HASH_SIZE; i++)
    {
        if (this->contents[i].IsEmpty() == false)
            hasItem = true;
    }
    return !hasItem;
}

/************************** Helper Functions **********************/

// Given an item, generates a hash for it that is as unique as possible.
unsigned HashTable::Hash_Function( const KeyType& R) const
{
    unsigned index = 0;
    // Go through each character in the STRING
    for (unsigned i = 0; i < R.length(); i++)
    {
        // Sum the values of each character, weighted by its position in the STRING.
        index += R[i]*i;

    }

    // Modulo, so it will fit into the Hash Table
    return (index% MAX_HASH_SIZE);
}

/*
void HashTable::PrintTable()
{
    for(unsigned i = 0; i < MAX_HASH_SIZE; i++)
    {
        cout << "Index: " << i << " || Contents: " <<endl;
        contents[i].Display();
        cout << "-----------------------------------"<<endl;
    }
}

unsigned HashTable::getCollisions(unsigned i)
{
    unsigned collided_nodes = 0;
    unsigned collisions = 0;
    if (!contents[i].IsEmpty())
    {
        contents[i].Reset();
        contents[i].Advance();
        while(!contents[i].EndOfList())
        {
            collisions++;
            contents[i].Advance();
        }
        contents[i].Reset();
    }
    return (collisions);
}

DLList& HashTable::getList(unsigned position)
{
    contents[position].Reset();
    return contents[position];
}
*/
