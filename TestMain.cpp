
/*****************************************************

    Zack Garza
    CISP 430 - TTH 5:30 pm
    Programming Project 6 - Hash Tables
    December 12, 2013

*****************************************************/
#include "HashTable.h"
#include <iostream>
#include <time.h>
#include <sys/timeb.h>
#include "MyFuncs.h"
#include <cmath>
#include "BSTree.h"
using namespace std;
#define _TRIALS 20
#define _ELEMS 10
#define _STRLENGTH 10


void testOrderedInsert();
void testHashTableInsert();
void testTimes();
void testVS();
// Array to hold all records read in from file.
Record r[500000], random_records[500000], result[500000], result2[500000];

int main ()
{
    srand (time(NULL));
    //testOrderedInsert();
    //testHashTableInsert();
    //testTimes();\
    cout << "Program started." << endl;
    testVS();
    return 0;
}

void testVS()
{
    unsigned i = 0, maxsize = 0;
    unsigned elements = _ELEMS;
    double BSTimeInit = 0, BSTimeFinal = 0, HTimeInit = 0, HTimeFinal = 0;


    ifstream infile("CISP430records.dat", ios::in | ios::binary);
    puts("File opened, reading Records into Array...");
    for (i = 0; infile; i++)
    {
        r[i].read(infile);
        if (i % 20000 == 0) cout << i << endl;
        maxsize = i;    // How many Record were read in
    }
    infile.close();
    puts("File imported.");

    ofstream outfile;
    outfile.open("testdata.txt");
    outfile << "Elements,";
    outfile << "Import Time Ratio,";
    outfile << "Random Read Time Ratio,";
    outfile << "Random Deletion Time Ratio" << endl;

    for (unsigned j = 0; j < _TRIALS; j++)
    {
        double ratio = 0;
        elements = 2 * elements;
        outfile << elements << ",";
        if (elements > maxsize) elements = maxsize;

        puts("Reading records into BSTree...");
        BSTree t;
        BSTimeInit = TIME();
        for (i = 0; i < elements; i++)
        {
            t.Insert(r[i]);
            if (i % 20000 == 0) cout << i << endl;
        }
        BSTimeFinal = TIME();
        double BSTimeTotal = (BSTimeFinal - BSTimeInit) / 1000;

        puts("Records imported into BSTree");

        puts("Reading Records into HashTable...");
        HashTable h;
        HTimeInit = TIME();
        for (i = 0; i < elements; i++)
        {
            h.Insert(r[i]);
            if (i % 20000 == 0) cout << i << endl;
        }
        HTimeFinal = TIME();
        double HTimeTotal = (HTimeFinal - HTimeInit) / 1000;
        ratio = HTimeTotal / BSTimeTotal;
        cout << "Records imported into HashTable.\n" << endl;

        cout << "BSTree time: " << BSTimeTotal << " seconds." << endl;
        cout << "HashTable time: " << HTimeTotal << "seconds" << endl;
        cout << "HashTable is " << ratio << " times as slow as BSTree. (BS/H)" << endl;
        cout << "Write test completed.\n\n" << endl;
        outfile << ratio << ",";

        cout << "Begin random access test - locate " << elements << " random records." << endl;


        for (i = 0; i < elements; i++)
        {
            unsigned w = (int) 0 + (rand() % (int)(maxsize - 0 + 1));
            random_records[i] = r[w];
        }

        BSTimeInit = TIME();
        for (i = 0; i < elements; i++)
        {
            result[i] = t.Find(random_records[i].Key());
        }
        BSTimeFinal = TIME();
        BSTimeTotal = (BSTimeFinal - BSTimeInit);

        HTimeInit = TIME();
        for (i = 0; i < elements; i++)
        {
            result2[i] = h.Retrieve(random_records[i].Key());
        }
        HTimeFinal = TIME();
        HTimeTotal = (HTimeFinal - HTimeInit);
        ratio = HTimeTotal / BSTimeTotal;

        cout << "BSTree time: " << BSTimeTotal << " ms." << endl;
        cout << "Hashtable time:" << HTimeTotal << " ms." << endl;
        cout << "Hashtable is " << ratio << " times as fast as BStree." << endl;
        puts("End random access test\n\n");
        outfile << ratio << ",";

        cout << "Start deletion test: delete "<< elements << " items.\n" << endl;

        for (i = 0; i < elements; i++)
        {
            unsigned w = (int) (0 + (rand() % (int)(elements - 0 + 1)));
            random_records[i] = r[w];
        }

        BSTimeInit = TIME();
        for (i=0; i < elements; i++)
        {
            t.Delete(random_records[i].Key());
        }
        BSTimeFinal = TIME();
        BSTimeTotal = BSTimeFinal - BSTimeInit;
        puts("BSTree Success.");

        HTimeInit = TIME();
        for (i=0; i < elements; i++)
        {
            h.Delete(random_records[i].Key());
        }
        HTimeFinal = TIME();
        HTimeTotal = HTimeFinal - HTimeInit;
        puts("HashTable success.");
        ratio = HTimeTotal / BSTimeTotal;

        cout << "BSTree time: " << BSTimeTotal << " ms." << endl;
        cout << "Hashtable time:" << HTimeTotal << " ms." << endl;
        cout << "Hashtable is " << ratio << " times as fast as BStree." << endl;
        puts("End deletion test\n\n");
        outfile << ratio << "," << endl;
    }
    outfile.close();
}

void testTimes()
{
    ofstream outfile;
    outfile.open("data.txt");

    double TotalAvg;
    double LengthAvg[MAX_HASH_SIZE], Collisions[MAX_HASH_SIZE];
    for (int i = 0; i < MAX_HASH_SIZE; i++)
    {
        LengthAvg[i] = 0;
        Collisions[i] = 0;
    }
    // Run i trials
    for (unsigned i = 0; i < _TRIALS; i++)
    {
        cout << "Test " << i << "." << endl << endl;
        STRING s[_ELEMS];
        HashTable h;
        double TimeInit = 0, TimeFinal = 0;
        // Populate array with c-standard strings
        for (unsigned i = 0; i < _ELEMS; i++)
        {
            char* s_i = random_string(_STRLENGTH);
            s[i] = s_i;
        }

        TimeInit = TIME();
        // Insert j elements
        for (unsigned j = 0; j < _ELEMS; j++)
        {
            Record r_j(s[j], s[j]);
            h.Insert(r_j);
            //cout << "Record Inserted: " << r_j << endl;
        }
        TimeFinal = TIME();

        //Test collision spread
        for (unsigned i = 0; i < MAX_HASH_SIZE; i++)
        {
            LengthAvg[i] += (double) (h.getList(i).getLength());
            Collisions[i] = h.getCollisions(i);
        }
        TotalAvg += (TimeFinal - TimeInit);
    }
    // Total Time taken to insert _ELEMS items
    TotalAvg = (double) TotalAvg / (double) (_TRIALS * 1000);
    // Ideal collisions per bucket.
    double ideal_length = (double) _ELEMS / (double) MAX_HASH_SIZE;
    for (int i =0; i < MAX_HASH_SIZE; i++)
    {
        LengthAvg[i] = LengthAvg[i] / _TRIALS;
    }
    cout << "Test completed. Trials: " << _TRIALS << endl;
    cout << "Average time to insert " << _ELEMS << " items: " << TotalAvg << " seconds." << endl << endl;

    cout << "Ideal list length: " << ideal_length << endl;
    cout << "Avg Length \t Deviation From Ideal" << endl;
    for (unsigned i = 0; i < MAX_HASH_SIZE; i++)
    {

        cout << "Bucket " << i << ": " << LengthAvg[i] << "             \t ";
        cout << (double) (LengthAvg[i] - ideal_length) << endl;
        outfile << i << ", " << LengthAvg[i] << endl;
    }
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
