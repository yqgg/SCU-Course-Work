#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NODE struct node
struct node{
	char name[20];
	int order_size;
	NODE *next;
};
NODE *head = NULL;
NODE *tail = NULL;
int count;
void insert();
void delete();
void show();
void search_size();
int check_duplicate();
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
                                        insert();
                                }
                                break;
                        case 2:
                                delete();
                                break;
                        case 3:
                                show();
                                break;
			case 4:
				search_size();
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

void insert() {
	NODE *p, *q, *temp;
	temp = malloc(sizeof(NODE));
	printf("Name: ");
	scanf("%s", temp->name);
	printf("Order size: ");
	scanf("%d", &temp->order_size);
	if(check_duplicate(temp) == 0) {
		if(temp == NULL) {
			printf("Error malloc\n");
			return;
		}
		if(head == NULL) {
			temp->next = NULL;
			head = temp;
			tail = temp;
		} else {
			temp->next = NULL;
			tail->next = temp;
			tail = temp;
		}
	} else {
		printf("That name has already been taken. Please enter another one.\n");
		return;
	}	
}

void delete() {
	printf("Enter the number of drinks you made: ");
	int num;
	scanf("%d", &num);
	NODE *p, *q;
	p = q = head;
	while(p != NULL) {
		if(p->order_size <= num) {
			num -= p->order_size;
			count--;
			if(p == head){ //p is pointing to head
				head = p->next;
			} else if(p->next == NULL){ //p is pointing to the last node
				NODE *temp = head;
				while(temp->next->next != NULL)  //locate the second to last node 
					temp = temp->next;
				temp->next = NULL;
				tail = temp;
			} else {  //p is somewhere in the middle
				q->next = p->next;
			}
			free(p);
		}
		p = p->next;
	}
	return;
}

void show() {
	NODE *p = head;
	while(p != NULL) {
		printf("%s, %d\n", p->name, p->order_size);
		p = p->next;
	}
}

void search_size() {
	printf("Enter an order size: ");
	int size;
	scanf("%d", &size);
	printf("These orders have an order size less than or equal to the size you entered: \n");
	NODE *p = head;
	while(p != NULL) {
		if(p->order_size <= size) {
			printf("%s, %d\n", p->name, p->order_size);
		}
		p = p->next;
	}	
}

int check_duplicate(NODE *param) {
	NODE *p = head;
	int flag = 0;
	while(p != NULL) {
		if(strcmp(param->name, p->name) == 0) {
			flag = 1;
		}
		p = p->next;
	}
	if(flag == 1)
		return 1;
	else
		return 0;
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
