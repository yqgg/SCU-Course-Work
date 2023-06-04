#include "lab9.h"
//pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void backwards(NODE *p) {   //recursive function
    if(p == NULL)
	return;
    else
	pthread_mutex_lock(&lock);
	backwards(p->next); //calling itself
    printf("%s, %d\n", p->name, p->order_size);
    pthread_mutex_unlock(&lock);
}

int showLength(NODE *p, int count) { //recursive function
    if(p == NULL) 
	return count;
    else
	pthread_mutex_lock(&lock);
	return showLength(p->next, count+1); //calls itself
    pthread_mutex_unlock(&lock);
}

void delete_all(NODE *p) { //recursive function
    if(p == NULL){ 
	return;
    } else {
	delete_all(p->next); //calls itself
    }
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
    pthread_mutex_lock(&lock);
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
    pthread_mutex_unlock(&lock);
    return;
}

void delete() {
    printf("Enter the number of drinks you made: ");
    int num;
    scanf("%d", &num);
    NODE *p, *q;
    pthread_mutex_lock(&lock);
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
    pthread_mutex_unlock(&lock);
    return;
}

void show() {
    pthread_mutex_lock(&lock);
    NODE *p = head;
    while(p != NULL) {
	printf("%s, %d\n", p->name, p->order_size);
	p = p->next;
    }
    pthread_mutex_unlock(&lock);
}

void search_size() {
    printf("Enter and order size: ");
    int size;
    scanf("%d", &size);
    printf("These orders have an order size less than or equal to the size you entered: \n");
    pthread_mutex_lock(&lock);
    NODE *p = head;
    while(p != NULL) {
	if(p->order_size <= size) {
	    printf("%s, %d\n", p->name, p->order_size);   
	}
	p = p->next;
    }
    pthread_mutex_unlock(&lock);
}

int check_duplicate(char *n) {
    pthread_mutex_lock(&lock);
    NODE *p = head;
    int flag = 0;
    while(p != NULL) {
	if(strcmp(n, p->name) == 0) {
	    flag = 1;
	}
	p = p->next;
    }
    pthread_mutex_unlock(&lock);
    return flag;
}


























