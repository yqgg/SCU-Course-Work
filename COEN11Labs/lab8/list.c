#include "lab8.h"
void backwards(NODE *p) {   //recursive function
    if(p == NULL)
	return;
    else
	backwards(p->next); //calling itself
    printf("%s, %d\n", p->name, p->order_size);
}

int showLength(NODE *p, int count) { //recursive function
    if(p == NULL) 
	return count;
    else
	return showLength(p->next, count+1); //calls itself
}

void delete_all(NODE *p) { //recursive function
    if(p == NULL) 
	return;
    else
	delete_all(p->next); //calls itself
    free(p);
    return;
}

//functions below are the same as in the previous lab
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
	head = temp;
    	head->next = NULL;
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
	    if(p == head) {
		head = p->next;
	    } else if(p->next == NULL) {
		NODE *temp = head;
		while(temp->next->next != NULL)
		    temp = temp->next;
		temp->next = NULL;
		tail = temp;
	    } else {
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
    printf("Enter and order size: ");
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


























