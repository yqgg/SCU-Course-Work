#include <cstring>
#include <iostream>
#include <cassert>
#include "mystring.h"
using namespace std;

/*    private:
        char *characters; //pointer to first char in string
        size_t allocated; //# of chars allocated for string
        size_t current_length; //# of chars currently in string at any given time*/

namespace coen79_lab5 {
    // CONSTRUCTOR, COPY CONSTRUCTOR, and DESTRUCTOR
    //     Precondition: str is an ordinary null-terminated string.
    //     Postcondition: The string contains the sequence of chars from str.
    string::string(const char str[ ]) {
        current_length = strlen(str);
        allocated = current_length +1;
        characters = new char[allocated];
        strncpy(characters, str, current_length);
        characters[current_length] = '\0';
    }

    //     Postcondition: The string contains c and then the null character.
    string::string(char c) {
        current_length = 1;
        allocated = 2;
        characters = new char[allocated];
        characters[0] = c;
        characters[1] = '\0';
    }

    //     Postcondition: The string becomes a copy of the source string.
    string::string(const string& source) {
        current_length = source.current_length;
        allocated = source.allocated;
        characters = new char[allocated];
        strncpy(characters, source.characters, source.current_length);
    }

    //  destructor function
    string::~string( ) {
        delete[] characters;
        allocated = 0;
        current_length = 0;
    }

    // MODIFICATION MEMBER FUNCTIONS
    //     Postcondition: addend has been catenated to the end of the string.
    void string::operator +=(const string& addend) {
        reserve(current_length + addend.current_length);
        strncat(characters, addend.characters, addend.current_length);
        current_length += addend.current_length;
    }

    //     Precondition: addend is an ordinary null-terminated string.
    //     Postcondition: addend has been catenated to the end of the string.
    void string::operator +=(const char addend[ ]) {
        reserve(current_length + strlen(addend));
        strncat(characters, addend, strlen(addend));
        current_length += strlen(addend);
    }

    //     Postcondition: The single character addend has been catenated to the
    //     end of the string.
    void string::operator +=(char addend) {
        reserve(current_length);
        characters[current_length] = addend;
        characters[current_length + 1] = '\0';
        current_length += 1;
    }

    //void reserve(size_t n)
    //      Postcondition: All functions will now work efficiently (without
    //      allocating new memory) until n characters are in the string.
    void string::reserve(size_t n) {
        char* arr = new char[n + allocated]; 
        strncpy(arr, characters, allocated); 
        delete[] characters; 
        characters = arr; 
        allocated += n; 
    }


    string& string::operator =(const string& source) {
        this->dlt(0, current_length);
        if (current_length != source.current_length){
            allocated = source.allocated;
            reserve(allocated);
        }
        strncpy(characters, source.characters, source.current_length);
        current_length = source.current_length;
        return *this;
    }

    //     Precondtion: position <= length()
    //     Postcondition: The source string is inserted into this string before
    //     the character at the given index.
    void string::insert(const string& source, unsigned int position) {
        assert(position <= length());
        string temp = source; 
        for(size_t i = position; i < current_length; i++) {
            temp += characters[i];
        }
        current_length += source.length();
        for(size_t j = 0; j < temp.length(); position++, j++) {
            characters[position] = temp[j];
        }
    }

    //     Precondition: (position + num) <= length( ).
    //     Postcondition: num characters are deleted from the sequence, starting
    //     at index position.
    void string::dlt(unsigned int position, unsigned int num) {
        assert((position + num) <= length());
        for(size_t i = position; i<=current_length-num; i++) {
            characters[i] = characters[i + num];
        }
        characters[current_length] = '\0';
        current_length -= num;
    }

    //     Precondition: position < length()
    //     Postcondtion: the character at the given position in the string is
    //     replaced with c. 
    void string::replace(char c, unsigned int position) {
        assert(position < length());
        characters[position] = c;
    }

    //     Precondition: (position + source.length()) <= length()
    //     Postcondtion: the characters in this string starting at position are
    //     replaced with those in the source srting.
    void string::replace(const string& source, unsigned int position){
        assert((position + source.length()) <= length());
        size_t j = 0;
        for(size_t i = position; i<(position + source.length()); i++) {
            characters[i] = source[j];
            j++;
        }
    }
        
    // CONSTANT MEMBER FUNCTIONS

    //     Precondition: position < length( ).
    //     Postcondition: The value returned is the character at the specified
    //     position of the string. A string's positions start from 0 at the start
    //     of the sequence and go up to length( )-1 at the right end.
    char string::operator [ ](size_t position) const {
        assert(position < length());
        return characters[position];
    }

    //     Postcondition: The location of the first occurence of the character c
    //     within this string is returned. If the string does not contain c, -1 is
    //     is returned.
    int string::search(char c) const {
        for(size_t i = 0; i<current_length; i++) {
            if(characters[i] == c) {
                return i;
            }
        }
        return -1;
    }

    //     Postcondition: Returns the index of the start of the first instance of
    //     the given substring inside of this string. If the substring is not found,
    //     this function returns -1.
    int string::search(const string& substring) const{ 
        char *p = strstr(characters, substring.characters);
        if(p != NULL) {
            return (*p - *characters);
        } else {
            return -1;
        }
    }

    //     Postcondition: The count of the occurence of the character c within this
    //     string is returned. 
    unsigned int string::count(char c) const {
        unsigned int count = 0;
        for(size_t i = 0; i<length(); i++) {
            if(characters[i] == c) {
                count++;
            }
        }
        return count;
    }
        
    // FRIEND FUNCTIONS
    //     Postcondition: The sequence of characters in source has been written
    //     to outs. The return value is the ostream outs.
    std::ostream& operator <<(std::ostream& outs, const string& source) {
        outs << source.characters;
        return outs;
    }
    bool operator ==(const string& s1, const string& s2) {
        return(strcmp(s1.characters, s2.characters)== 0);
    }
    bool operator !=(const string& s1, const string& s2) {
        return(strcmp(s1.characters, s2.characters)!= 0);
    }
    bool operator > (const string& s1, const string& s2) {
        return(strcmp(s1.characters, s2.characters)> 0);
    }
    bool operator < (const string& s1, const string& s2) {
        return(strcmp(s1.characters, s2.characters)< 0);
    }
    bool operator >=(const string& s1, const string& s2) {
        return(strcmp(s1.characters, s2.characters)>= 0);
    }
    bool operator <=(const string& s1, const string& s2) {
        return(strcmp(s1.characters, s2.characters)<= 0);
    }
    // NON-MEMBER FUNCTIONS for the string class
    string operator +(const string& s1, const string& s2) {
        string s;
        s.reserve(s1.length() + s2.length()+1);
        s += s1;
        s += s2;
        return s;
    }
    string operator +(const string& s1, const char addend[ ]) {
        string s;
        s.reserve(s1.length() + strlen(addend) +1);
        s += s1;
        s += addend;
        return s;
    }

    //     Postcondition: A string has been read from the istream ins, and the
    //     istream ins is then returned by the function. The reading operation
    //     skips white space (i.e., blanks, newlines, tabs) at the start of ins.
    //     Then the string is read up to the next white space or the end of the
    //     file. The white space character that terminates the string has not
    //     been read.
    std::istream& operator >> (std::istream& ins, string& target) {
        while(ins && isspace(ins.peek())) {
            ins.ignore();
        }
        char *in = new char[500];
        ins >> in;
        target = string(in);
        return ins;
    }
}