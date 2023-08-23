#include <string>
#include <iostream>
using namespace std;

//Precondition: The input can be any alphabet, number, and punctuation.
//Postcondition: Correct count of alphanumerical characters and count of non alphanumerical characters.
 int main() {
   string str;
   int alphaCount = 0;
   int notAlpha = 0;
   cout << "Please input something\n"; //print out instruction for user
   getline(cin, str); //store user input as a String
   
   //Get the length of the user input string and create a for loop to search through the String str
   for(int i=0; i<str.length(); i++) {
      //check if index i of the string is a space
      if(str[i] != ' ') {
        //isalnum() takes a character and returns true if index i of the string is an alphanumeric character
        if(isalnum(str[i])) {
          alphaCount++; //increment alphaCount if true
        } else {
          notAlpha++; //else increment notAlpha if false
        }
      }
   }

   //print the int values
   cout << "Number of alphanumeric characters: " << alphaCount << "\n"; 
   cout << "Number of non-alphanumeric characters: " << notAlpha << "\n";
 }