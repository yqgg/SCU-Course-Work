#include "lab9.h"
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void readfile(char *file) {
    char fileName[20];
    int fileSize;
    FILE *fp;
    pthread_mutex_lock(&lock);
    fp = fopen(file, "r");
    if(fp == NULL) {
	printf("Cannot open file %s. New file created.\n", file);
	return;
    } else {
	fseek(fp, 33, SEEK_SET); //find the text after the header
	while((fscanf(fp, "%s\n%d\n", fileName, &fileSize)) == 2) {
	    pthread_mutex_unlock(&lock);
	    insert(fileName, fileSize);
	    pthread_mutex_lock(&lock);
        }
	fclose(fp);
    }
    pthread_mutex_unlock(&lock);
}

void savefile(char *file) {
    NODE *p;
    p = head;
    FILE *fp;
    pthread_mutex_lock(&lock);
    fp = fopen(file, "w");
    fprintf(fp, "NAME\tSIZE\n______________________\n");
    while(p != NULL) {
	fprintf(fp, "%s\t%d\n", p->name, p->order_size);
	p = p->next;
    }
    fclose(fp);
    pthread_mutex_unlock(&lock);
}

void *autoSave(void *arg) {
    FILE *fp;
    while(1) {
	NODE *p = head;
	sleep(15);
	pthread_mutex_lock(&lock);
	fp = fopen("data.txt", "w");
	fprintf(fp, "NAME\tSIZE\n______________________\n");
	while(p != NULL) {
	    fprintf(fp, "%s\t%d", p->name, p->order_size);
	    p = p->next;
	}
	fclose(fp);
	pthread_mutex_unlock(&lock);
    }
}

void showFile() {
    FILE *fp;
    char fileName[20];
    int fileSize;
    pthread_mutex_lock(&lock);
    fp = fopen("data.txt", "r");
    printf("NAME\tSIZE\n______________________\n");
    fseek(fp, 33, SEEK_SET);
    while(fscanf(fp, "%s\n%d\n", fileName, &fileSize)==2) {
	printf("%s\t%d\n", fileName, fileSize);
    }
    fclose(fp);
    pthread_mutex_unlock(&lock);
}

