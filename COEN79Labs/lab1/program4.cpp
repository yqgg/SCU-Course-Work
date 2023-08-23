#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

//Precondition: user presses enter
//Post condition: correct count of number of guess/correct count of how many times the program ran through the while loop.
int main() {
    int userInput;
    char userResponse;
    int count = 0;
    cout << "Think of a number between 1 and 20. Press enter when you are ready.\n";
    cin.get();
    srand(time(NULL));
    //infinite loop until false or 0
    while(1) {
        int guess = rand() % 20 + 1;
        cout << "Is the number " << guess << "? Y or N\n";
        cin >> userResponse;
        count++;
        if(userResponse == 'y') {
            break;
        } else if (userResponse != 'n') {
            cout << "Enter a valid input.\n";
        }
    }
    cout << "I found the number in " << count << " steps.\n";
}
