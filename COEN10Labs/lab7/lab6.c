#include <stdio.h>
#include <string.h>
#define size 5
int main() {
	char arr[5][20];
	int count = 0;
	int userOp;
	int i,j;
	char name[20];
	char letter;
	for(i = 0; i<size; i++) {
		arr[i][0] = '\0';
	}
	while(1) {
		printf("MENU\n(1)Schedule a lesson\n(2)Cancel a lesson\n(3)List the schedule\n(4)Show names starting with a letter\n(9)Quit\nOption: ");
		scanf("%d", &userOp);
		switch(userOp) {
			case 1:	//schedule a lesson
				if(count == size) {
					printf("No more available times\n");
				} else {
					printf("Enter name: ");
					scanf("%s", arr[count]);
					printf("Your lesson is at %dpm.", count+1);
 	                                count++;
				}
				printf("\n\n");
				break;
			case 2:	//cancel lesson
				printf("Enter name:  ");
				scanf("%s", name);
				for(i = 0; i < size; i++) {
					if(strcmp(name,arr[i]) == 0){
						for(j = i+1; j<count; j++){
							strcpy(arr[j-1], arr[j]);
						}
						count--;
						arr[count][0] = '\0';
						
						break;
					} 
				}
				if(i == size){
					printf("You don't have a reservation.");
				} else {
					printf("Your lesson has been canceled\n\n");
				}
				break;
			case 3:	//print the schedule
				if(count == 0)
					printf("There are no lessons scheduled.\n\n");
				else {
					for(i = 0; i<size; i++){
						if(arr[i][0] == '\0')
							printf("%dpm: free\n", i+1);
						else 
							printf("%dpm: %s\n", i+1, arr[i]);		
					}
				}
				printf("\n");
				break;
			case 4:
				
				if(count == 0) {
					printf("There are no lesson scheduled.\n\n");
				} else {
					printf("Enter a letter: ");
					getchar();
					scanf("%c", &letter);
					for(i = 0; i<count; i++) {
						if(arr[i][0] == letter) 
							printf("%dpm: %s", i+1, arr[i]);
					}
				}
				printf("\n\n");
				break;				
			case 9:
				return 0;
				break;
			default: printf("Not an option\n");
		}
	}
}

	
