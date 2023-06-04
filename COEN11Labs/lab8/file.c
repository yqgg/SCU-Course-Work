#include "lab8.h"
//These two functions are the same as they were in the previous lab
void readfile(char *file) {
    char fileName[20];
    int fileSize;
    FILE *fp;
    fp = fopen(file, "r");
    if(fp == NULL) {
	printf("Cannot open file %s. New file created.\n", file);
	return;
    } else {
	fseek(fp, 33, SEEK_SET); //find the text after the header
	while((fscanf(fp, "%s\n%d\n", fileName, &fileSize)) == 2) {
	    insert(fileName, fileSize);
       }
	fclose(fp);
    }
}

void savefile(char *file) {
    NODE *p;
    p = head;
    FILE *fp;
    fp = fopen(file, "w");
    fprintf(fp, "NAME\tSIZE\n______________________\n");
    while(p != NULL) {
	fprintf(fp, "%s\t%d\n", p->name, p->order_size);
	p = p->next;
    }
    fclose(fp);
}
