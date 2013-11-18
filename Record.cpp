/** Credit: David Fox **/

#include "Record.h"

Record::Record ( ){}

Record::Record ( const DataType& d, const KeyType& k )
:data(d), key(k){}

Record::Record ( const Record& r )
:data(r.data), key(r.key){}
Record::~Record(){}
  
Record& Record::operator= ( const Record& r )
{
  data = r.data;
  key = r.key;
  return *this;
}

DataType Record::Data ( ) const { return data; }
KeyType Record::Key ( ) const { return key; }

DataType& Record::Data ( ) { return data; }
KeyType& Record::Key ( ) { return key; }
  
bool Record::operator== ( const Record& r ) const
{
  return ( key == r.key );
}
bool Record::operator!= ( const Record& r ) const
{
  return !(*this == r );
}

bool Record::operator< ( const Record& r ) const
{
  return ( key < r.key );
}
bool Record::operator> ( const Record& r ) const 
{
  return ( key > r.key );
}

bool Record::operator<= ( const Record& r ) const
{
  return ! ( *this > r );
}
bool Record::operator>= ( const Record& r ) const
{
  return !( *this < r );
}

ostream& operator<< ( ostream& os, const Record& r )
{
  os << "Data: " << r.data<< "  Key: " << r.key;
  return os;
}

void Record::write ( ostream& out ) const
{
  data.write( out );
  key.write( out );
}
  
void Record::read ( istream& in )
{
  data.read( in );
  key.read( in );
}
