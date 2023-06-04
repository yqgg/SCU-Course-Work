#include <stdio.h>
#include <string.h>
#include "lab4.h"
void main() {
	//flag to determine if user wants to quit program.
        int flag = 0;
        while(flag == 0) {
                printf("\nTHE BOBA SHOP\n1) add\n2) fufill order\n3) list\n4) find an order less than or of equal size\n0) quit\nEnter command: ");
                int user;
                scanf("%d", &user);
                switch(user) {
                        case 1:
                                if(count == 10) {
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
				sizeLessThanOrEqual();
				break;
                        case 0:
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
	printf("Name: ");
	scanf("%s", arr[count].name);
	int i;
	for(i = 0; i<count; i++) {
		if(strcmp(arr[count].name, arr[i].name) == 0) {
			printf("That name has already been taken. Enter another name.\n");
			return;
		}	
	}
	printf("Order size: ");
	scanf("%d", &arr[count].order);
	printf("\nIs this a bobadash order OR an in store order?\n1) Bobadash\n2) In-store\nEnter command: ");
	scanf("%d", &arr[count].classify);
	if(arr[count].classify == 1) {
		printf("Enter phone number: ");
		scanf("%s", arr[count].info.phoneNum);
		printf("The phone number %s is added to the list.\n", arr[count].info.phoneNum);
	} else if (arr[count].classify == 2) {
		printf("Enter order number: ");
		scanf("%d", &arr[count].info.orderNum);
	}
	count++;
}

void fufillOrder() {
	printf("Enter the number of drinks you made: ");
	int numOfDrinks;
	scanf("%d", &numOfDrinks);
	int i = 0;
	//while loop to search through orders
	while(i < count) {
		if(numOfDrinks >= arr[i].order) {
			numOfDrinks -= arr[i].order;
			count--;
			int j;
			//for loop to move orders up if an order is fufilled (the number of drinks made is greater than or equal to the order size
			for(j = i; j<count; j++) {
				arr[j].order = arr[j+1].order;
				strcpy(arr[j].name, arr[j+1].name);
				arr[j].classify = arr[j+1].classify;
				arr[j].info.orderNum = arr[j+1].info.orderNum;
				strcpy(arr[j].info.phoneNum, arr[j+1].info.phoneNum);
			}
		} else {
			//if order is not fufilled (the number of drinks made is less than the order size) increment i to check the next order.
			i++;
		}
	}
}

void listOrders() {
	int i;
	for(i = 0; i<count; i++) {
		printf("%s, %d", arr[i].name, arr[i].order);
		if(arr[i].classify == 1)
			printf("\t(Phone number: %s)\n", arr[i].info.phoneNum);
		else 
			printf("\t(Order number: %d)\n", arr[i].info.orderNum);
	}
}

void sizeLessThanOrEqual() {
	printf("Enter an order size: ");
	int size;
	scanf("%d", &size);
	printf("These orders have an order size less than or equal to the size you entered: \n");
	int i;
	//for loop to loop through customer structure
	for(i = 0; i<count; i++) {
		//if order at index position i is less than or equal to size then print it out
		if(arr[i].order <= size) {
			printf("%s, %d\n", arr[i].name, arr[i].order);
		}		
	}	
}

/* 1) What is the struct definition for a customer? 
	struct customer { 
* 		int order;
 * 		char name[10];
 * 	};
 * 2) Which approach do you prefer and why?
 * 	I prefer using structures because it is much easier to access the elements of each piece of information, like the name and order size. In my head it also makes more sense that each customer has a set of information of different data types rather than having to correspond the index of one array to another to become a customers order.
 *
 *  3) How would you allow employees to input customerss as First Name, space, Last Name?
 *  	Create two elements in the structure which are strings and then write a for loop to loop through the users input to find where the space is. Then, copy characters before the space to the firstName string and then the characters after the space to a lastName string.*/
