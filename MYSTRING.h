/*****************************************************

    Zack Garza
    CISP 430 - TTH 5:30 pm
    Programming Project 2 - Classes
    September 12, 2013

*****************************************************/
#ifndef MY_STRING_CLASS_H
#define MY_STRING_CLASS_H

#include <iostream>
#include <fstream>
#include <cstdlib>
// Class Invariants: //
// The allocated memory of a STRINGS contents will always be len bytes.
//*******************//

// Global Conditions //
// To use any member functions of a STRING object, it must be initialized by one of the constructors.
// All member functions assume the parent STRING object has validly allocated memory, and that there
// is enough memory available to hold the string's contents.
//
// All char* arguments must be valid, null-terminated character arrays.
// Additionally, the null terminator must be within strlen(char*) bytes of the
// beginning of all char*s - that is, they must occur within valid memory.
//
// Trailing null-terminators from c-style strings are never copied into STRINGs.
//
// Most member functions have an implicit STRING //in parameter.
// Several have an implicit STRING //inout parameter, however. The exceptions are:
//  +, +=,

class STRING {
    unsigned len;
    char* contents;
    public:
//          Constructors / Destructor               //
/****************************************************/



/****************************************************/
// Pre: None
// Post: A STRING is created with len == 0 and contents == "".
// This constructor will initialize an empty STRING.

// out
STRING();
/**********************************************/


/**********************************************/
// Pre: cstr must be a null-terminated character array.
// Post: A STRING is created with len == strlen(cstr) whose contents are
//   are equal to the contents of cstr, without the trailing null terminator.
// This constructor will take a char* and use it to initialize the
// STRING.

//out                //in
STRING(const char* cstr);
/**********************************************/


/**********************************************/
// Pre: None
// Post: A STRING is created with len == 1 and contents == c
// This constructor will take a char and use it to initialize the
// STRING.

//out        //in
STRING(const char c);
/**********************************************/


/**********************************************/
// Pre: The STRING s has been properly intialized by another constructor.
// Post: A new STRING is created with len == s.len and contents == s.contents
// This constructor will take a STRING and use it to initialize
// the STRING. This is called the copy constructor.

//out         //in
STRING(const STRING& s);
/**********************************************/


/**********************************************/
// Pre: The STRING has been created with one of the above constructors.
// Post: The memory allocated to the string's contents is freed.
// The destructor.

//inout
~STRING();
/**********************************************/









//                  Member Functions                //
/****************************************************/

/**********************************************/
// Pre: None
// Post: Return s.len to non-member functions.
// This will return the number of characters in the STRING.

//out
unsigned length() const;
/**********************************************/

/**********************************************/
// Pre: Right_argument must be an initialized STRING, a null terminated c-string, or a character.
// Post: The STRING object on the left hand side of the assignment operation will be initialized
//      All characters except for trailing null terminators will be copied into the STRINGs contents.

//inout                  //in
STRING& operator = (const STRING &right_argument);
//inout                  //in
STRING& operator = (const char* &right_argument);
//inout                  //in
STRING& operator = (const char &right_argument);
/**********************************************/


/**********************************************/
// Pre: None
// Post: Returns the position of the first occurrence of char in
//      the STRING as an int. Throws a positive number if char is not in the STRING.

//out        //in
int position(const char) const;
/**********************************************/


/**********************************************/
// Pre: A STRING object has been initialized with a constructor.
// Post: Returns a new STRING whose contents are the right_argument's contents
//      appended to the implicit STRING object's contents.
//      Immediate concatenation ( += ) operator;

//inout             //in
STRING operator += (const STRING &right_argument);
//inout             //in
STRING operator += (const char* &right_argument);
//inout             //in
STRING operator += (const char &right_argument);
/**********************************************/


/**********************************************/
// Pre: Index must be <= the STRING's length for valid results
// Post: Returns a reference to the character contained at index.
// Index ( [ ] ) operator:
// If the index is out of range, throws a positive integer error.

//inout             //in
char& operator [] (const int index);
//inout             //in
char& operator [] (const int index) const;
/**********************************************/


/**********************************************/
// Pre: first >= 0 && < len; last >= 0 && < len for valid results
// Post: Converts all alphabetic characters between the indexes
// of first and last to uppercase letters.

//STRING:inout              //in                 //in
void upcase(const unsigned first, const unsigned last);
//STRING:inout
void upcase(); // Upcases the whole string.
/**********************************************/


/**********************************************/
// Pre: first >= 0 && < len; last >= 0 && < len for valid results
// Post: Converts all alphabetic characters between the indexes
//      of first and last to lowercase letters.

//STRING;inout              //in                //in
void downcase(const unsigned first, const unsigned last);
//STRING:inout
void downcase(); // Downcases the entire string.
/**********************************************/


/**********************************************/
// Pre: first >= 0 && < len; last >= 0 && < len for valid results
// Post: Changes all uppercase alphabetic characters to lowercase and
//      changes all lowercase alphabetic characters to uppercase within indexes
//      first to last.

//STRING:inout                  //in                //in
void togglecase(const unsigned first, const unsigned last);
//STRING:inout
void togglecase(); // Toggles entire string.
/**********************************************/




//           Comparison / Friend Functions          //
/****************************************************/

/**********************************************/
// Pre: None
// Post: Extracts individual characters from the STRING's contents
//          and appends them to any ostream
// Output stream ( << ) operator;
// This operator will return an ostream.

//                                  //inout             //in
friend std::ostream& operator << (std::ostream &out, const STRING &right_argument);
/**********************************************/


/**********************************************/
// Pre: None
// Post: Extracts individual characters from the STRING's contents
//          and appends them to any istream
// Input stream ( >> ) operator;
// This operator will return an istream.
//                                  //inout         //in
friend std::istream& operator >> (std::istream &in, STRING &right_argument);
/**********************************************/


/**********************************************/
// Pre: None
// Post: Tests for equality between STRINGS and other STRINGs, char*s, or chars.
//      Case sensitive. STRING == right_argument iff for all i < STRING.length and
//      right_argument.length, STRING[i] == right_argument[i].
// Comparison ( == ) operator;

// Applies to all:          //in                        //in
friend bool operator == (const STRING &left_argument, const STRING &right_argument);
friend bool operator == (const char* &left_argument, const STRING &right_argument);
friend bool operator == (const STRING &left_argument, const char* &right_argument);
friend bool operator == (const char &left_argument, const STRING &right_argument);
friend bool operator == (const STRING &left_argument, const char &right_argument);
/**********************************************/


/**********************************************/
// Pre: None
// Post: Tests for inequality between STRINGS and chars, char*s, or other STRINGs.
//      left_argument != right_argument if there exists any i for which
//      (right_argument[i] == leftargument[i]) is false or if their lengths are not equal.
// Comparison ( != ) operator;

// Applies to all:          //in                        //in
friend bool operator != (const STRING &left_argument, const STRING &right_argument);
friend bool operator != (const char* &left_argument, const STRING &right_argument);
friend bool operator != (const STRING &left_argument, const char* &right_argument);
friend bool operator != (const char &left_argument, const STRING &right_argument);
friend bool operator != (const STRING &left_argument, const char &right_argument);
/**********************************************/


/**********************************************/
// Pre: None
// Post: Compares STRINGs, chars, and char*s interoperably.
//      Returns true if left argument comes after right
//      argument alphabetically.
// Comparison ( > ) operator;

//Applies to all:       //in                            //in
friend bool operator > (const STRING &left_argument, const STRING &right_argument);
friend bool operator > (const char* &left_argument, const STRING &right_argument);
friend bool operator > (const STRING &left_argument, const char* &right_argument);
friend bool operator > (const char &left_argument, const STRING &right_argument);
friend bool operator > (const STRING &left_argument, const char &right_argument);
/**********************************************/


/**********************************************/
// Pre: None
// Post: Compares STRINGs, char*s, and chars interoperable.
//      Returns true if left argument comes before
//      right argument alphabetically.
// Comparison ( < ) operator;

//Applies to all:           //in                        //in
friend bool operator < (const STRING &left_argument, const STRING &right_argument);
friend bool operator < (const char* &left_argument, const STRING &right_argument);
friend bool operator < (const STRING &left_argument, const char* &right_argument);
friend bool operator < (const char &left_argument, const STRING &right_argument);
friend bool operator < (const STRING &left_argument, const char &right_argument);
/**********************************************/


/**********************************************/
// Pre: None
// Post: Returns true if left argument < right argument or
//      left_argument == right argument
// Comparison ( <= ) operator;

//Applies to all:               //in                        //in
friend bool operator <= (const STRING &left_argument, const STRING &right_argument);
friend bool operator <= (const char* &left_argument, const STRING &right_argument);
friend bool operator <= (const STRING &left_argument, const char* &right_argument);
friend bool operator <= (const char &left_argument, const STRING &right_argument);
friend bool operator <= (const STRING &left_argument, const char &right_argument);
/**********************************************/


/**********************************************/
// Pre: None
// Post: Returns true if left argument > right argument or
//      left_argument == right argument
// Comparison ( >= ) operator;

//Applies to all:           //in                        //in
friend bool operator >= (const STRING &left_argument, const STRING &right_argument);
friend bool operator >= (const char* &left_argument, const STRING &right_argument);
friend bool operator >= (const STRING &left_argument, const char* &right_argument);
friend bool operator >= (const char &left_argument, const STRING &right_argument);
friend bool operator >= (const STRING &left_argument, const char &right_argument);
/**********************************************/


/**********************************************/
// Pre: None
// Post: Appends the contents of right_argument (minus trailing null-terminators)
//      to the contents of the implicit STRING object.
// Concatenation ( + ) operator;

//Applies to all:
//STRING:inout      //in
STRING operator + (const STRING &right_argument);
STRING operator + (const char* &right_argument);
STRING operator + (const char &right_argument);
/**********************************************/




//               Extra Credit Functions             //
/****************************************************/
// Pre:
// Post:
//
operator char*();
// operator char*();
// This will cast our STRING to a char*.
/**********************************************/


/**********************************************/
// Pre:
// Post:
//
// STRING& operator int(const STRING &right_argument);
// operator int();
// This will cast our STRING to an int if possible. It will return 0
// if unsuccessful.
/**********************************************/

/**********************************************/
// Pre:
// Post:
//
// STRING& operator float(const STRING &right_argument);
// operator float();
// This will cast our STRING to a float if possible. It will
// return 0 if unsuccessful.
/**********************************************/




// Helper Functions //
/**********************************************/
// Pre: None
// Post: Displays the contents of s to stdout.

                        //in
friend void STRdisplay(const STRING& s);

/**********************************************/
// Pre: None
// Post: Return true if STRING.len == 0. If true, memory for contents
//      has been deallocated and contains garbage.
bool isEmpty();

// Pre: "os" must be a valid, opened ostream (ios::out | ios::binary)
//Post: *this is sent to os using the ostream member function "write".
void write( std::ostream& os ) const;

//Pre: "is" must be a valid and opened istream (ios::in | ios::binary)
// The STRING to be read must have been writen in the format used by STRING::write
//Post: A STRING is read from "IS" using the istream member function "read" and assigned to *this.
void read( std::istream& );
};
#endif
