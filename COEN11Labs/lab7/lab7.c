/* 
 * Yi Qian Goh 1613654
 * COEN 11L 39405
 * Lab 7 The Boba Shop
 * */

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

//initialize functions
void insert(char *, int);
void delete();
void show();
void search_size();
int check_duplicate(char *);
void readfile(char *);
void savefile(char *);


int main(int argc, char *argv[]) {
	if(argc == 1) { //check if file name was put into command prompt
		printf("Missing file name.\n");
		return 0;
	}
	readfile(argv[1]);
        while(1) {
                printf("\nTHE BOBA SHOP\n1) add\n2) fufill order\n3) list\n4) find an order less than or of equal size\n0) quit\nEnter command: ");
                int user;
                scanf("%d", &user);
                switch(user) {
                        case 1:
				if(count == 10) {
					printf("There is no more space for orders\n");
					break;
				} else {
					printf("Name: ");
					char n[20];
					scanf("%s", n);
					if(check_duplicate(n) == 0) {
						printf("Order size: ");
						int orderSize;
						scanf("%d", &orderSize);
						insert(n, orderSize);
					}
					
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
				savefile(argv[1]);
                                return 0;
                        default :
                                printf("invalid input");
                                break;
                }
	}
}

void readfile(char *file) {
	char fileName[20];
	int fileSize;
	fp = fopen(file, "r");//read file
	if(fp == NULL) {
		printf("Cannot open file %s.\n", file);
		return;
	} else {
		fseek(fp, 33, SEEK_SET); //find the text after the header
		while((fscanf(fp, "%s\t%d\n", fileName, &fileSize)) == 2) {
			insert(fileName, fileSize);
		}
		fclose(fp);
	}
}

void savefile(char *file) {
	NODE *p;
	p = head;
	FILE *fp; 
	fp = fopen(file, "w");//open file to write in new orders
	fprintf(fp, "NAME\tSIZE\n______________________\n"); //header of text file
	while(p != NULL) {
		fprintf(fp, "%s\t%d\n", p->name, p->order_size);
		p = p->next;
	}
	fclose(fp);
}


void insert(char *n, int orderSize) {
	NODE *temp;
	temp = (NODE *)malloc(sizeof(NODE));
	if(temp == NULL) {
		printf("Error malloc\n");
		return;
	}
	strcpy(temp->name, n);
	temp->order_size = orderSize;
	count++;
	if(head == NULL) {
		temp->next = NULL;
		head = temp;
		tail = temp;
	} else {
		temp->next = NULL;
		tail->next = temp;
		tail = temp;
	}
	return;
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

int check_duplicate(char *n) {	
	NODE *p = head;
	int flag = 0;
	while(p != NULL) {
		if(strcmp(n, p->name) == 0) {
			flag = 1;
		}
		p = p->next;
	}
	return flag;
}
/* PRELAB QUESTIONS
 * 1. 
 * 	a. fseek(fp, 0, SEEK_SET);
 * 	b. fseek(fp, 0, SEEK_END);
 * 	c. SEEK_CUR
 *
 * 2. 
 * 	a. "r" for read.
 * 	b. "w" will create a new file that we do not need.*/
