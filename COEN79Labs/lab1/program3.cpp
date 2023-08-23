#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Precondition: there must exist a file names "program3.txt"
//Postcondition: file is closed and words of length greater than 10 printed out.
int main() {
    fstream file;
    file.open("program3.txt");
    string str;
    string word;
    //Go through file word by word using while loop
    while(file >> word) {
        //iterate through each character of the word to check if it is an alphabet. Erase if it is not, convert to upper case if it is an alphabet.
        for(int i = 0; i<word.length(); i++) {
            if(isalpha(word[i])) {
                word[i] = toupper(word[i]);
            } else {
                word.erase(i--,1);
            }
        }
        //print out words that are 10 or more characters long
        if(word.length() >= 10) {
            cout << word << "\n";
        }
    }
    file.close();
}
