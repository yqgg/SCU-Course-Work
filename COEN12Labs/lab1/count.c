#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX_WORD_LENGTH 30

void readfile(char *); //initialize function

//the main function
void  main(int argc, char *argv[]) {
    if(argc ==1) {
	printf("Missing file name.\n");
	return;
    }
    readfile(argv[1]);
}

//reads the file given. If the name of the file does not exist then it will print an error and then create a new file. Else, it counts the number of words in the file.  
void readfile(char *file) {
    char fileName[20];
    int fileSize;
    FILE *fp;
    fp = fopen(file, "r");
    if(fp == NULL) {
	printf("Cannot open file %s. New file created.\n", file);
	return;
    } else {
	int count = 0;
	char *word[MAX_WORD_LENGTH];
	//while loop until it reaches EOF (end of file).
	while ((fscanf(fp, "%s", word)) != EOF) {
		count++;
	}
	fclose(fp);
	printf("%d total words\n", count);
    }
}
