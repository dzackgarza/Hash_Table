/*****************************************************

    Zack Garza
    CISP 430 - TTH 5:30 pm
    Programming Project 2 - Classes
    September 12, 2013

*****************************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "MYSTRING.h"

using namespace std;

// Helper functions
bool alphaCompare(const STRING& inA, const STRING& inB);
char upcase(const char &c);
char downcase(const char &c);
//

//          Constructors / Destructor               //
/****************************************************/

// This constructor will initialize an empty STRING.
STRING::STRING()
{
    this->len = 0;
    contents = new char[0];
}

// This constructor will take a char* and use it to initialize the
// STRING.
STRING::STRING(const char* cstr)
{
    unsigned cstrLength = 0;

    if (cstr != NULL) // Count the characters in cstr to find the minimum amount of memory necessary.
        for (unsigned i = 0; cstr[i] != '\0'; i++, cstrLength++);

    this->len = cstrLength;
    this->contents = new char[cstrLength];
       // Letter by letter assignment, shorts if cstrLength is still zero
    for (unsigned i = 0; i < cstrLength; i++)
        this->contents[i] = cstr[i];
}


// This constructor will take a char and use it to initialize the
// STRING.
STRING::STRING(const char c)
{
    this->len = 1;
    contents = new char[this->len];
    this->contents[0] = c;
}


// This constructor will take a STRING and use it to initialize
// a new STRING. This is called the copy constructor.
STRING::STRING(const STRING& s)
{
    this->len = s.len;
    this->contents = new char[s.len];
    for (unsigned i = 0; i < s.len; i++)
        this->contents[i] = s.contents[i];
}


// The destructor.
STRING::~STRING() { delete[] contents; }



//                  Member Functions                //
/****************************************************/

// This will return the number of characters in the STRING.
unsigned STRING::length() const { return this->len; }


// Assignment ( = ) operator
// This operator assigns one STRING to another.
    // if (this == &right_argument)
    //  return *this{}
    // 1.  Deallocate any memory that STRING is using internally
    // 2.  Allocate some memory to hold the contents of the new STRING
    // 3.  Copy the values from into this instance
    // 4.  Return *this
STRING& STRING::operator = (const STRING &right_argument)
{
    if (this == &right_argument) return *this;

    delete[] this->contents;
    this->contents = new char [right_argument.len];

    for (unsigned i = 0; i < right_argument.len; i++)
        this->contents[i] = right_argument.contents[i];
    this->len = right_argument.len;
    return *this;
}

STRING& STRING::operator = (const char* &right_argument)
{
    *this = STRING(right_argument);
    return *this;
}

STRING& STRING::operator = (const char &right_argument)
{
    *this = STRING(right_argument);
    return *this;
}


// This will return the position of the first occurrence of char in
// the STRING as an int. Throws error (1) if the char is not in the STRING.
int STRING::position(const char c) const
{
    for (unsigned i = 0; i <= this->len; i++)
        if (contents[i] == c) return i;
    // Character not found.
    throw int(1);
}


// Immediate concatenation ( += ) operator{}
// This operator will be overloaded to
// work with a right hand value of either type STRING, type char* or type char.
STRING STRING::operator += (const STRING &right_argument)
{
    unsigned newLength = this->len + right_argument.length();
    int new_length = this->len;
    char* temp = new char[new_length];

    // Copy the left hand argument into a temporary char array
    // so we can delete its contents and reallocate more memory
    for(unsigned i = 0; i < this->len; i++)
        temp[i] = this->contents[i];
    delete[] this->contents;
    this->contents = new char[newLength];

    unsigned i = 0;

    // Copy the first string's contents back in.
    // Must be a while loop for proper scoping of i.
    while (i < this->len)
    {
        this->contents[i] = temp[i];
        i++;
    }
    // Copy the second string's contents in.
    for (unsigned j = 0; j < right_argument.length(); j++)
        this->contents[i + j] = right_argument.contents[j];

    this->len = newLength;
    return *this;
}

STRING STRING::operator += (const char* &right_argument)
{
    *this += STRING(right_argument);
    return *this;
}

STRING STRING::operator += (const char &right_argument)
{
    *this += STRING(right_argument);
    return *this;
}


// Index ( [ ] ) operator
// This operator returns one character through indexing. An
// error is thrown if the index is out of range.
//
// Bounds checks are done to make sure the index is in range.
// The index must be greater than zero and less than the length of the STRING.
char& STRING::operator [] (const int index)
{
    if (index >= (int)this->len || index < 0) throw int(1);
    else return this->contents[index];
}

char& STRING::operator [] (const int index) const
{
    if (index >= (int)this->len || index < 0) throw int(1);
    else return this->contents[index];
}


// This function will change all alphabetic characters to upper case.
// Works on the character at index first through, but not including, the character at index
// last.
//
// Bounds checks are done to make sure they are in range - the bounds must be less than the lengths
// of both strings and greater than zero.
void STRING::upcase(const unsigned first, const unsigned last)
{
    for (unsigned i = first; (i < last && i <= this->len) && i >= 0; i++)
    {
        if (this->contents[i] >= 'a' && this->contents[i] <= 'z')
            this->contents[i] &= ('A' - 'a' - 1);
    }
}

void STRING::upcase() { this->upcase(0, this->len); }

char upcase(const char &c)
{
    char temp = c;
    if (c >= 'a' && c <= 'z')
        temp &= ('A' - 'a' - 1);
    return temp;
}


// This function will change all alphabetic characters to lower case.
void STRING::downcase(const unsigned first, const unsigned last)
{
    for (unsigned i = first; i < last && i <= this->len && i >= 0; i++)
    {
        if (this->contents[i] >= 'A' && this->contents[i] <= 'Z')
            this->contents[i] |= 'a'-'A';
    }
}

// No arguments - downcases the entire STRING.
void STRING::downcase() { this->downcase(0, this->len); }

// Downcase a single character. Just in "case"
char downcase(const char &c)
{
    char temp = c;
    if (c >= 'A' && c <= 'Z') // Is it an uppercase letter?
            temp |= 'a'-'A'; // Send it to lowercase
    return temp;
}


// This function will change the case of all alphabetic characters.
// Bounds checks are done to ensure the range given is
// between zero and the lengths of both STRINGS
void STRING::togglecase(unsigned first, unsigned last)
{
    for (unsigned i = first; (i < last && i <= this->len) && i >= 0; i++)
    {
        if (this->contents[i] >= 'A' && this->contents[i] <= 'Z')   // Is it an uppercase letter?
            this->contents[i] |= 'a'-'A';           // Send it to lowercase
        else                                                        // Must be a lowercase letter.
            this->contents[i] &= ('A' - 'a' - 1);   // Send it to uppercase
    }
}

// If no arguments are given, toggles the entire STRING.
void STRING::togglecase() { this->togglecase(0, this->len); }


//               Comparison / Friend Functions      //
/****************************************************/

// Output stream ( << ) operator{}
// This operator will return an ostream.
std::ostream& operator << (ostream &out, const STRING &right_argument)
{
    for (unsigned i = 0; i < right_argument.len; i++)
        out << right_argument.contents[i];
    return out;
}


// Input stream ( >> ) operator{}
// This operator will return an istream.
std::istream& operator >> (istream &in, STRING &right_argument)
{
    char c;
    while(in.get(c))
    {
        if (c == '\n') break;
        else right_argument += c;   // Automatically handles memory reallocation. Could be slow.
    }
    return in;
}


// Comparison ( == ) operator{}
// (see note below for all comparison operators)
bool operator == (const STRING &left_argument, const STRING &right_argument)
{
    if  (left_argument.len != right_argument.len) return false;
    for (unsigned i = 0; i < left_argument.len; i++)
        if (left_argument.contents[i] != right_argument.contents[i]) return false;
    return true;
}

bool operator == (const char* &left_argument, const STRING &right_argument)
{
    return (STRING(left_argument) == right_argument);
}
bool operator == (const char &left_argument, const STRING &right_argument)
{
    return (STRING(left_argument) == right_argument);
}

bool operator == (const STRING &left_argument, const char* &right_argument)
{
    return (left_argument == STRING(right_argument));
}
bool operator == (const STRING &left_argument, const char &right_argument)
{
    return (left_argument == STRING(right_argument));
}




// Comparison ( != ) operator{}
bool operator != (const STRING &left_argument, const STRING &right_argument)
{
    return !(left_argument == right_argument);
}

bool operator != (const char* &left_argument, const STRING &right_argument)
{
    return !(STRING(left_argument) == right_argument);
}
bool operator != (const char &left_argument, const STRING &right_argument)
{
    return !(STRING(left_argument) == right_argument);
}

bool operator != (const STRING &left_argument, const char* &right_argument)
{
    return !(left_argument == STRING(right_argument));
}
bool operator != (const STRING &left_argument, const char &right_argument)
{
    return !(left_argument == STRING(right_argument));
}





// Comparison ( > ) operator{}
bool operator < (const STRING &left_argument, const STRING &right_argument)
{
    return (alphaCompare(left_argument, right_argument));
}

bool operator < (const char* &left_argument, const STRING &right_argument)
{
    return (alphaCompare(STRING(left_argument), right_argument));
}
bool operator < (const char &left_argument, const STRING &right_argument)
{
    return (alphaCompare(STRING(left_argument), right_argument));
}

bool operator < (const STRING &left_argument, const char* &right_argument)
{
    return (alphaCompare(left_argument, STRING(right_argument)));
}
bool operator < (const STRING &left_argument, const char &right_argument)
{
    return (alphaCompare(left_argument, STRING(right_argument)));
}




// Comparison ( < ) operator{}
bool operator > (const STRING &left_argument, const STRING &right_argument)
{
    return (right_argument < left_argument);
}

bool operator > (const char* &left_argument, const STRING &right_argument)
{
    return (right_argument < STRING(left_argument));
}
bool operator > (const char &left_argument, const STRING &right_argument)
{
    return (right_argument < STRING(left_argument));
}

bool operator > (const STRING &left_argument, const char* &right_argument)
{
    return (STRING(right_argument) < left_argument);
}
bool operator > (const STRING &left_argument, const char &right_argument)
{
    return (STRING(right_argument) < left_argument);
}






// Comparison ( <= ) operator{}
bool operator <= (const STRING &left_argument, const STRING &right_argument)
{
    return (left_argument == right_argument || left_argument < right_argument);
}

bool operator <= (const char* &left_argument, const STRING &right_argument)
{
    STRING l_arg(left_argument);
    return (l_arg == right_argument || l_arg < right_argument);
}
bool operator <= (const char &left_argument, const STRING &right_argument)
{
    STRING l_arg(left_argument);
    return (l_arg == right_argument || l_arg < right_argument);
}

bool operator <= (const STRING &left_argument, const char* &right_argument)
{
    STRING r_arg(right_argument);
    return (left_argument == r_arg || left_argument < r_arg);
}
bool operator <= (const STRING &left_argument, const char &right_argument)
{
    STRING r_arg(right_argument);
    return (left_argument == r_arg || left_argument < r_arg);
}






// Comparison ( >= ) operator{}
bool operator >= (const STRING &left_argument, const STRING &right_argument)
{
    return (left_argument == right_argument || left_argument > right_argument);
}

bool operator >= (const char* &left_argument, const STRING &right_argument)
{
    STRING l_arg(left_argument);
    return (l_arg== right_argument || l_arg > right_argument);
}
bool operator >= (const char &left_argument, const STRING &right_argument)
{
    STRING l_arg(left_argument);
    return (l_arg== right_argument || l_arg > right_argument);
}

bool operator >= (const STRING &left_argument, const char* &right_argument)
{
    STRING r_arg(right_argument);
    return (left_argument == r_arg || left_argument > r_arg);
}
bool operator >= (const STRING &left_argument, const char &right_argument)
{
    STRING r_arg(right_argument);
    return (left_argument == r_arg || left_argument > r_arg);
}



// Concatenation ( + ) operator{}
STRING STRING::operator + (const STRING &right_argument)
{
    unsigned right_arg_length = right_argument.length();
    unsigned left_arg_length = this->length();
    unsigned newSTRlen = left_arg_length + right_arg_length;

    STRING temp;
    temp.contents = new char[newSTRlen];
    temp.len = newSTRlen;

    for (unsigned i = 0; i < left_arg_length; i++)
        temp.contents[i] = this->contents[i];

    for (unsigned i = 0; i < right_arg_length; i++)
        temp.contents[i + left_arg_length] = right_argument.contents[i];

    return temp;
}

STRING STRING::operator + (const char* &right_argument)
{
    STRING s1(right_argument);
    return (*this + s1);
}

STRING STRING::operator + (const char &right_argument)
{
    STRING s1(right_argument);
    return (*this + s1);
}

//               Extra Credit Functions             //
/****************************************************/
// STRING& STRING::operator char*(const STRING &left_argument, const STRING &right_argument){}
// This will cast our STRING to a char*.

// STRING& STRING::operator int(const STRING &left_argument, const STRING &right_argument){}
// This will cast our STRING to an int if possible. It will return 0
// if unsuccessful.

// STRING& STRING::operator float(const STRING &left_argument, const STRING &right_argument){}
// This will cast our STRING to a float if possible. It will
// return 0 if unsuccessful.





// Helper Functions //

// "a" < "b"    97 < 98
// "A" < "B"    65 < 66
// "A"< "a"     65 < 97
// "a" < "B"    97 < 65
// "ab" < "abc"
// Notice that the numerical (ASCII) value of a
// character decides its position when comparing upper to lower case of the same letter,
// e.g., "A" < "a", but it does not when comparing differing letters
// Returns the answer to "Does inA come before inB alphabetically?"
bool alphaCompare(const STRING& inA, const STRING& inB)
{
    STRING A(inA);
    STRING B(inB);

    for (unsigned i = 0; i < A.length() && i < B.length() ; i++)
    {
        if (A[i] != B[i])
        {
            // Are both characters alphabetic?
            if (
                ((A[i] >= 'A' && A[i]<= 'Z') ||
                (A[i] >= 'a' && A[i] <= 'z')) &&
                ((B[i] >= 'A' && B[i]<= 'Z') ||
                (B[i] >= 'a' && B[i] <= 'z'))
                )
            {
                // Same character, different case
                if (downcase(A[i]) == downcase(B[i])) return A[i] < B[i];

                // Different character, same case
                else if (
                ((A[i] >= 'A' && A[i] <= 'Z') &&
                (B[i] >= 'A' && B[i] <= 'Z')) ||
                ((A[i] >= 'a' && A[i] <= 'z') &&
                (B[i] >= 'a' && B[i] <= 'z'))
                )
                {
                    return (A[i] < B[i]);
                }
                // Different character, different case
                else return (downcase(A[i]) < downcase(B[i]));
            }
            else
            {
                return A[i] < B[i]; // Not an alphabetic character. Compare ASCII values.
            }
        }
    }
    // All characters match. Shorter strings come first - is A shorter than B?
    return (A.length() < B.length());
}

void STRdisplay(const STRING& s)
{
    for (unsigned i = 0; i < s.len; i++)
        cout << s.contents[i];
}

bool STRING::isEmpty() { return (this->len == 0); }

STRING::operator char*()
{
    char* c = new char[this->len+1];
    unsigned i = 0;
    while (i < this->len)
    {
        c[i] = this->contents[i];
        i++;
    }
    c[i] = '\0';
    return c;
}

void STRING::write( std::ostream& os ) const
{
    os.write(reinterpret_cast<const char*>(&len), sizeof(unsigned));
    os.write(contents, len);
}

void STRING::read ( std::istream& is )
{
    is.read(reinterpret_cast<char*>(&len), sizeof(unsigned));
    this->contents = new char[len];
    is.read(contents, len);
}
