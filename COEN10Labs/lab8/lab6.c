#include <stdio.h>
#include <string.h>
#define size 5
//global variables
char names[5][20];
char numbers[5][11];
int groups[5];
int count = 0;
void request();
void cancel();
void list();
void firstLetter();
void getGroup();

int main() {
	int userOp;
	int i,j;
	char name[20];
	char number[11];
	char letter;
	for(i = 0; i<size; i++) {
		names[i][0] = '\0';
	}
	while(1) {
		printf("MENU\n(1)Schedule a lesson\n(2)Cancel a lesson\n(3)List the schedule\n(4)Show names starting with a letter\n(5)Show groups with a specified number of people\n(9)Quit\nOption: ");
		scanf("%d", &userOp);
		switch(userOp) {
			case 1:	//schedule a lesson
				request();
				break;
			case 2:	//cancel lesson
				cancel();
				break;
			case 3:	//print the schedule
				list();
				break;
			case 4: //print names that start with user inputed letter
				firstLetter();
				break;				
			case 5: //print lessons that have the specified number of people in the group
				getGroup();				
				break;
			case 9:
				return 0;
				break;
			default: printf("Not an option\n");
		}
	}
}

void request() {
	int i;
        char name[20];
        char number[11];
	int groupSize;
	if(count == size) {
		printf("No more available times\n");
		return;
        } else {
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter phone number: ");
                scanf("%s", number);
                printf("Enter the number of people attending (maximum of 4): ");
                scanf("%d", &groupSize);
		if(groupSize > 4) {
			printf("Group size is too big.\n");
			return;
		} else if (groupSize < 1) {
			printf("Group size is too small.\n");
			return;
		} else {
			for(i = 0; i<size; i++) {
				if(strcmp(name, names[i]) == 0) {
					printf("A lesson has already been scheduled under that name. Please enter another name.\n");
					return;
				}
			}
		}
	}
	count++;
	strcpy(names[count], name);
	strcpy(numbers[count], number);
	groups[count] = groupSize;
	printf("%s your lesson at %dpm has be scheduled.", name, count);
	printf("(Phone Number: %s, Group Size: %d)\n", number, groupSize);
	printf("\n\n");
}                                

void cancel() {
	int i,j;
        char name[20];
	if(count == 0 ) {
		printf("There are no lessons scheduled.\n\n");
	} else {
		printf("Enter name:  ");
	        scanf("%s", name);
        	for(i = 0; i < size; i++) {
      		if(strcmp(name,names[i]) == 0){
	        	for(j = i+1; j<count; j++){
        	        	strcpy(names[j-1], names[j]);
        	        }
        	        count--;
        	        names[count][0] = '\0';
			numbers[count][0] = '\0';
			break;
        		}
		}
	
        	if(i == size){
			 printf("There is no lesson scheduled under that name.\n\n");
	       	} else {
        	         printf("Your lesson has been canceled.\n\n");
       		}
		printf("\n\n");
	}
}

void list() {
	int i;
	if(count == 0)
        	printf("There are no lessons scheduled.\n\n");
        else {
                for(i = 0; i<size; i++){
                	if(names[i][0] == '\0')
				printf("%dpm: free\n", i+1);
                        else
                                printf("%dpm: %s\n", i+1, names[i]);
                }
        }
        printf("\n\n");
}

void firstLetter() {
	int i;
        char letter;
	if(count == 0) {
        	printf("There are no lessons scheduled.\n\n");
        } else {
                printf("Enter a letter: ");
                getchar();
                scanf("%c", &letter);
                int flag;
		for(i = 0; i<count; i++) {
                if(names[i][0] == letter)
        	        printf("%dpm: %s\n", i+1, names[i]);
			flag = 1;
                }
       }
       printf("\n\n");
}

void getGroup() {
	int i;
	int groupSize;
	if(count == 0) {
		printf("There are no lessons scheduled.\n\n");
	} else {
		printf("Enter a group size: ");
		scanf("%d", &groupSize);
		for(i = 0; i<count; i++) {
			if(groups[i] == groupSize) {
				printf("%dpm: %s", i+1, names[i]);
				printf(" (Group of %d people)\n", groups[i]);
			}	
		} 
	}
	printf("\n\n");
}	
