/** Credit: David Fox **/

#ifndef MY_RECORD_CLASS_DEF_
#define MY_RECORD_CLASS_DEF_
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

//There must be a header file for class
//STRING in the same folder as Record.h
//It must be named MYSTRING.h
#include "MYSTRING.h"

typedef STRING DataType;
typedef STRING KeyType;

class Record
{
  DataType data;
  KeyType key;


public:
  //Post: an empty Record is created
  Record ( );

  //Post: A Record is created with data == Data && key == Key
  Record ( const DataType& Data, const KeyType& Key );

  //Post: A copy of Record is created
  Record ( const Record& R );

  //Post: A Record is destroyed
  ~Record();

  //Post: *this == R
  Record& operator= ( const Record& R );

  //Post: a copy of data is returned
  DataType Data ( ) const;

  //Post: a copy of key is returned
  KeyType Key ( ) const;

  //Post: a reference to data is returned
  DataType& Data ( );

  //Post: a reference to key is returned
  KeyType& Key ( );

  //Post: this->key is compared to R.key and the results is returned
  bool operator== ( const Record& R ) const;
  bool operator!= ( const Record& R ) const;
  bool operator< ( const Record& R ) const;
  bool operator> ( const Record& R ) const;
  bool operator<= ( const Record& R ) const;
  bool operator>= ( const Record& R ) const;

  //Pre: os must be a valid ostream
  //Post: the key and data of R is put into os
  friend ostream& operator<< ( ostream& os, const Record& R );

  //Pre: os must be a valid ostream opened (ios::out | ios::binary)
  //Post: the key and data is put into os
  //      using the STRING member function write
  void write ( ostream& os ) const;

  //Pre: is must be a valid istream opened (ios::in | ios::binary)
  //     the key and data to be read must have been
  //     written in the format used by Record::write
  //Post: a key and a data is read from is
  //      using the istream member function read
  //      and assigned to *this
  void read ( istream& is );


};

#endif


