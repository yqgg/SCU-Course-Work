#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
	int num1;
	int num2;
	int user;
	int totalCorrect;
	int i;
	srand(time(NULL));
	//for loop to print out two random numbers, receive user input, and checks if the user input equals the product of the two random numbers
	for(i = 0; i<10; i++) {
		num1 = rand()%13;
		num2 = rand()%13;
		printf("%d * %d\n", num1, num2);
		scanf("%d", &user);
		//checks if user input is correct
		if(user == num1*num2) {
			totalCorrect++;
			printf("Yay, you got it right!\n");
		} else {
			printf("That's incorrect. The correct answer is %d.\n", num1*num2);
		}
			
	}
	printf("You got %d percent correct\n", totalCorrect*10);
}
