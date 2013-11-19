
/*****************************************************

    Zack Garza
    CISP 430 - TTH 5:30 pm
    Programming Project 6 - Hash Tables
    December 12, 2013

*****************************************************/
#include "HashTable.h"
#include <iostream>
using namespace std;
void testOrderedInsert();
void testHashTableInsert();

int main ()
{
    //testOrderedInsert();
    testHashTableInsert();
    return 0;
}

void testHashTableInsert()
{
    HashTable h;
    bool e = h.IsEmpty();
    cout << "Empty: " << e<<endl;
    h.Insert(Record("ABC", "ABC"));
    h.Insert(Record("DEF", "DEF"));
    h.Insert(Record("GHI", "GHI"));
    h.Insert(Record("JKL", "JKL"));
    h.Insert(Record("mno", "mno"));
    h.Insert(Record("pqr", "pqr"));
    h.Insert(Record("stu", "stu"));
    e = h.IsEmpty();
    cout << "Empty: " << e<<endl;

    h.PrintTable();
    cout << "****************************"<<endl;
    cout << "Retrieved: " << h.Retrieve("UVW") << endl;
    h.PrintTable();
    cout << "****************************"<<endl;
    //h.Delete("ABC");
    h.PrintTable();
    cout << "****************************"<<endl;
}

void testOrderedInsert()
{
    cout << "Testing Ordered Insert" << endl;
    DLList d;
    d.OrderedInsert(Record("A", "A"));
    d.OrderedInsert(Record("W", "W"));
    d.OrderedInsert(Record("C", "C"));
    d.OrderedInsert(Record("B", "B"));
    d.OrderedInsert(Record("D", "D"));
    d.OrderedInsert(Record("B", "B"));


    d.Reset();
    cout << endl;
    d.Display();
    d.Advance(); d.Advance(); d.Delete(); cout<<endl; d.Display();
}
