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
void priority();
int count_letter(char);

int main() {
	int userOp;
	int i;
	int flag;
	char name[20];
	char number[11];
	char letter;
	for(i = 0; i<size; i++) {
		names[i][0] = '\0';
	}
	while(1) {
		printf("MENU\n(1)Schedule a lesson\n(2)Cancel a lesson\n(3)List the schedule\n(4)Show names starting with a letter\n(5)Show groups with a specified number of people\n(6)Priority\n(7)Count letter\n(9)Quit\nOption: ");
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
			case 6:
				if(flag == 1){
					printf("A priority lesson has already been schedule. No more priority lessons can be scheduled.\n\n");
					break;
				} else {
					priority();
					flag = 1;
					break;
				}
			case 7:
				printf("Enter a letter: ");
				scanf(" %c", &letter);
				int numberOfOccurrences = count_letter(letter);
				printf("Found %d occurrences of %c\n\n", numberOfOccurrences, letter); 
				break;
			case 9:
				return 0;
				break;
			default: printf("Not an option\n\n");
		}
	}
}

int count_letter(char letter) {
	int count = 0;
	int i;
	char *p;
	for(i = 0; i<size; i++) {
		p = names[i];
		while(*p != '\0') {
			if(*p == letter) {
				count++;
			}
			p++;
		}
	}
	return count;	
}


void priority() {
	int i;
	char name[20];
	char number[11];
	int groupSize;
	for(i = count; i>0; i--) {
		strcpy(names[i], names[i-1]);
	}
        printf("Enter name: ");
        scanf("%s", name);
        printf("Enter phone number: ");
        scanf("%s", number);
        printf("Enter the number of people attending (maximum of 4): ");
        scanf("%d", &groupSize);
        if(groupSize > 4) {
                 printf("Group size is too big.\n\n");
                 return;
        } else if (groupSize < 1) {
                 printf("Group size is too small.\n\n");
                 return;
        } else {
                 for(i = 0; i<size; i++) {
 	                if(strcmp(name, names[i]) == 0) {
        	                printf("A lesson has already been scheduled under that name. Please enter another name.\n\n");
                                return;
                        }
                }
        }
	strcpy(names[0], name);
	strcpy(numbers[0], number);
	groups[0] = groupSize;	
        printf("%s, your lesson at 1pm has be scheduled.", name);
        printf("(Phone number: %s, Group size: %d)", number, groupSize);
	printf("\n\n");
}

void request() {
	int i;
        char name[20];
        char number[11];
	int groupSize;
	if(count == size) {
		printf("No more available times\n\n");
		return;
        } else {
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter phone number: ");
                scanf("%s", number);
                printf("Enter the number of people attending (maximum of 4): ");
                scanf("%d", &groupSize);
		if(groupSize > 4) {
			printf("Group size is too big.\n\n");
			return;
		} else if (groupSize < 1) {
			printf("Group size is too small.\n\n");
			return;
		} else {
			for(i = 0; i<size; i++) {
				if(strcmp(name, names[i]) == 0) {
					printf("A lesson has already been scheduled under that name. Please enter another name.\n\n");
					return;
				}
			}
		}
	}
 	strcpy(names[count], name);
	strcpy(numbers[count], number);
	groups[count] = groupSize;
	count++;
	printf("%s, your lesson at %dpm has be scheduled.", name, count);
       	printf("(Phone number: %s, Group size: %d)", number, groupSize);
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
