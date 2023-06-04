#include <stdio.h>
#include <string.h>
#define MAX_LIST_SIZE 10
#define MAX_NAME_LENGTH 10
char names[MAX_LIST_SIZE][MAX_NAME_LENGTH];
int orders[MAX_LIST_SIZE];
int count;
void enterOrder();
void fufillOrder();
void listOrders();
void main() {
	//use flag to determine if user wants to quit the program.
	int flag = 0;
	while(flag == 0){
		printf("\nTHE BOBA SHOP\n1) add\n2) fufill order\n3) list\n4) quit\nEnter command: ");
		int user;
		scanf("%d", &user);
		switch(user) {
			case 1:
				if(count == MAX_LIST_SIZE) {
					printf("There is no more space left for orders.\n");
				} else {
					enterOrder();		
				}
				break;
			case 2:
				fufillOrder();
				break;
			case 3:
				listOrders();
				break;
			case 4:
				flag = 1;
				return;
			default :
				printf("invalid input");
				break;
		}
		//printf("\nTHE BOBA SHOP\na) add\nb) fufill order\nc) list\nd) quit\nEnter command: ");
	}	
}

void enterOrder() {
	if(count != MAX_LIST_SIZE) {
		printf("Name: ");
		char name[MAX_NAME_LENGTH];
		scanf("%s", name);
		//first check if the name entered is too long. If not then ask for order size.
		if(strlen(name) > MAX_NAME_LENGTH) {
			printf("Name is too long. Enter another name.\n");			
		} else {
			printf("Group Size: ");
			int size;
			scanf("%d", &size);
			orders[count] = size;
			int i = 0;
			for(i = 0; i<strlen(name); i++) 
				names[count][i] = name[i];
			count++;
		}
	}	
}


void fufillOrder() {
	printf("Enter the number of drinks you made: ");
	int numOfDrinks;
	scanf("%d", &numOfDrinks);
	//while loop to check entire list of orders to check for order sizes less than or equal to the number of drinks made.
	int i = 0;
	while(i < count) {
		if(numOfDrinks >= orders[i]) {
			numOfDrinks -= orders[i];
			count--;
			int j;
			//moving all orders up if an order is fufilled
			for(j = i; j<count; j++) {
				orders[j] = orders[j+1];
				strcpy(names[j], names[j+1]);
			}
		} else {
			//if no orders are less than or equal to the number of drinks made, then increment i to check the next order.
			i++;
		}
	}
}

void listOrders() {
	int i;
	for(i = 0; i<count; i++) {
		printf("%s, %d\n", names[i], orders[i]);
	}
}

/* 1) What happnes if a customers name is longer than 10 characters? Try setting MAX_NAME_LENGTH to 8 and see how the program changes when u list the orders using the Example input below.
 * 	a) There is an error.
 * 	b) The array length is shorter than the string entered. There are too many characters in the string to fit into the array with a specified and initialized length.
 * 	c) Write an if statement that asks the user to enter a new name if the length of the string is greater than the MAX_NAME_LENGTH.
 *
 *2) How can your program handle any input that isn't listed without exiting?
	Write a default switch in the switch which returns to the beginning of the loop.

3) How can you use true and false instead of 0 and 1 to check conditions?
	I can use boolean true and false data type instead of integers data type. */
