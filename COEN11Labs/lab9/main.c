#include "lab9.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//initializing variables that were declared in lab8.h
NODE *head = NULL;
NODE *tail = NULL;
int count = 0;
pthread_mutex_t lock;

int main(int argc, char *argv[]) {
	pthread_mutex_init(&lock, NULL);	
	if(argc == 1) {
		printf("Missing file name.\n");
		return 0;
	}
	readfile(argv[1]);
	while(1) {
		printf("\nTHE BOBA SHOP\n1) add\n2) fufill order\n3) list\n4) find an order less than or of equal size\n5) show the list backwards\n6) show the length of the list\n7) show the file content\n0) quit\nEnter command: ");
		int user;
		scanf("%d", &user);
		int listLength;
		pthread_t tid1;
		pthread_create(&tid1, NULL, autoSave, NULL);
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
					} else {
					    printf("That name has already been taken. Enter another name.\n");
					    break;
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
			case 5:
				backwards(head);
				break;
			case 6:
				showLength(head, listLength);
				printf("The length of the list is %d\n", showLength(head, 0));
				break;
			case 7:
				showFile();
				break;
			case 0:
				pthread_mutex_lock(&lock);
				pthread_cancel(tid1);
				pthread_mutex_unlock(&lock);
				savefile(argv[1]);
				delete_all(head);
				return 0;
			default:
				printf("invalid input");
				break;
		}
	}
}

/* PRELAB
 * A lock is needed in every almost function that traverses or changes some element of the globally shared list. Except the lock and unlock is not needed in the delete_all() function in list.c because the thread is terminated before delete_all() is called. So, almost every function in "file.c" and every function in "list.c". None needed in the header file "lab9.h". Lock and unlock is used in the case 0 of the switch in main.c.*/
