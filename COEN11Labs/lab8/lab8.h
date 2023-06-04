#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NODE struct node
struct node{
    char name[20];
    int order_size;
    NODE *next;
};
extern NODE *head;
extern NODE *tail;
extern int count;
void insert(char *, int);
void delete();
void show();
void search_size();
int check_duplicate(char *);
void readfile(char *);
void savefile(char *);
void backwards(NODE *);
int showLength(NODE *, int);
void delete_all(NODE *);
