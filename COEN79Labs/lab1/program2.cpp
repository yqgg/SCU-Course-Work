#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

//Precondition: the input must be a string of 10 digits with no spaces
//Postcondition: String printed in the format specified in the instructions for Lab 1 Program 2
int main() {
    string str;
    string rev;
    cout << "Input string of 10 digits (0 to 9) with no space\n";
    getline(cin, str);

    int spaces = 0;
    //loop 5 times to print 5 lines
    for(int i=0; i<5; i++) {
        cout << setw(spaces + str.length()) << str;
        cout << setw(str.length());
        //loop through length of String str, starting from the last index, to print out the string in reverse
        for(int j=str.length()-1; j>=0; j--) {
            cout << str[j];
        }
        cout << "\n";
        spaces += 2;
    }
}