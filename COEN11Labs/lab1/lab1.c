#include <stdio.h>
//initialize function
int divide(int quotient, int userAnswer);
int main (void) {
	srand(time(NULL));
	int i;
	int divisor;
	int quotient;
	int dividend;
	int count = 0;
	printf("\nTest your division skills. Please answer these 10 division problems. \n");
	//for loop to call divide() function 10 times
	for(i = 0; i<10; i++) {
		int userAnswer;
		divisor = (rand() % 12)+1; //generates a random integer from 1-12
		quotient = rand() % 13; //generates a random integer from 0-12
		dividend = divisor * quotient;
		printf("\n%d) %d/%d = ", i+1, dividend, divisor);
		scanf("%d", &userAnswer); //receive user input
		if(divide(quotient, userAnswer) == 1) {
			count++; //counter for number of correct answers
			printf("Correct.\n");
		} else {
			printf("Incorrect. The right answer is %d.\n", quotient);	
		}
		
	}
	printf("\nYou got %d out of 10 questions correct.\n", count);
	if(count == 10)
		printf("Congratulations you passed!\n");
	else
		printf("You did not pass :(\n\n");	
} 

int divide (int quotient, int userAnswer) {
	if(userAnswer == quotient)
		return 1;
	else
		return 0;
}



/*
 * QUESTIONS
 *
 * 1. Comment the line srand(time(NULL)); and run the program multiple times (without recompiling). 
 * Now uncomment the same line and run the program multiple times (without recompiling). How does 
 * the program differ whenyou have the line commented and not commented?
 *
 * 	Without the line srand(time(NULL)); the program only generates random integers every time 
 * 	you compile. If you do not recompile after each run, the program will output the same random 
 * 	integers each time you run the program. With the line srand(time(NULL)); new random integers 
 * 	are generated each time you run the program even without recompiling.
 *
 * 
 * 2. Use a #define preprocessor macro to define the number of repetitions. If you used the following 
 * for loop below, the commpiler will error because of the syntax. Explain why the compiler errors.
 * 	
 * 	There shouldn't be a semicolon after 10. It should be #define REPETITIONS 10
 *
 *
 * 3. How do you prevent the divisor from being 0.
 * 	
 * 	I added 1 to the randomly generated divisor so that if it 0, it will become a 1. And I also 
 * 	decreased the maximum by 1 so the random number does not go above 12.
 *
 *
 * 4. Does your program still work if you remove the #include at the top of the file?
 * 	The program doesn't work if I remove the #include at the top of the file. It gives a compiling
 * 	error.
 *
 * 	a) Compile your program with all of gcc's warnings by using the -Wall flag (command given below)
 * 	b) gcc -Wall main.c
 * 	c) What warnings does the compiler give you?
 * 		It gives warning for "implicit declaration of fuction... " such as, srand(time(NULL)),
 * 		rand(), and scanf().*/
