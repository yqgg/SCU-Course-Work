/* Yi Qian Goh
 * 11 May 2022
 * COEN 12 - Lab 4 
 * Description: Write functions that help a robot find its way out of a maze by implementing a stack. We will use a circular doubly linked list.*/

#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct list {
    int count;
    int (*compare)();
    struct node *head;
} LIST;

typedef struct node {
    void *data;
    struct node *next;
    struct node *prev;
} NODE;

LIST *createList(int (*compare)()) {
    LIST *lp = malloc(sizeof(LIST));
    assert(lp != NULL);
    lp->count = 0;
    lp->compare = compare;
    lp->head = malloc(sizeof(NODE));
    assert(lp->head != NULL);
    lp->head->next = lp->head;
    lp->head->prev = lp->head;
    return lp;
}

void destroyList(LIST *lp) {
    assert(lp != NULL);
    NODE *pDel = lp->head->next;
    NODE *pNext;
    while(pDel != lp->head) {
	pNext = pDel->next;
	free(pDel);
	pDel = pNext;
	lp->count--;
    }
    free(lp);
}

//return the number of nodes in the list
//Big-O: O(1)
int numItems(LIST *lp){
    assert(lp != NULL);
    return(lp->count);
}

//Add an element to the front of the list
//Big-O: O(1)
void addFirst(LIST *lp, void *item) {
    assert(lp != NULL && item != NULL);
    NODE *temp = malloc(sizeof(NODE));
    assert( temp != NULL);
    temp->data = item;
    temp->next = lp->head->next;
    temp->prev = lp->head;
    temp->next->prev = temp;
    lp->head->next = temp;
    lp->count++;
}

//Add an element to the end of the list
//Big-O: O(1)
void addLast(LIST *lp, void *item) {
    assert(lp != NULL && item != NULL);
    NODE *temp = malloc(sizeof(NODE));
    temp->data = item;
    temp->next = lp->head;
    temp->prev = lp->head->prev;
    temp->prev->next = temp;
    lp->head->prev = temp;
    lp->count++;
}

//Reassigns pointers to point away from the last node. Return the data of the first node and then free the node from memory.
//Big-O: O(1)
void *removeFirst(LIST *lp) {
    assert(lp != NULL);
    NODE *pDel = malloc(sizeof(NODE));
    assert(pDel != NULL);
    pDel = lp->head->next;
    lp->head->next = pDel->next;
    pDel->next->prev = lp->head;
    void *first = pDel->data;
    free(pDel);
    lp->count--;
    return first;
}

//Reassigns pointers to point away from the last node. Return the data of the last node and then free the node from memory.
//Big-O: O(1)
void *removeLast(LIST *lp) {
    assert(lp != NULL);
    NODE *pDel = malloc(sizeof(NODE));
    assert(pDel != NULL);
    pDel = lp->head->prev;
    pDel->prev->next = lp->head;
    lp->head->prev = pDel->prev;
    void *last = pDel->data;
    free(pDel);
    lp->count--;
    return last;
}

//Return but do not delete the first item in the listed pointed by lp
//Big-O: O(1)
void *getFirst(LIST *lp) {
    assert(lp != NULL);
    return(lp->head->next->data);
}

//Remove but do not delete the last item in the list poitned to lp.
//Big-O: O(1)
void *getLast(LIST *lp) {
    assert(lp != NULL);
    return(lp->head->prev->data);
}

void removeItem(LIST *lp, void *item) {
    assert(lp != NULL && item != NULL);
    NODE *np = lp->head->next;
    int i;
    for(i = 0; i<lp->count; i++) {
	if(lp->compare(item, np->data) == 0) {
	    np->next->prev = np->prev;
	    np->prev->next = np->next;
	    free(np);
	    lp->count--;
	}
	np = np->next;
    }
}

//finds the item in the list lp. If not found it returns NULL
//Big-O: O(n)
void *findItem(LIST *lp, void *item){
    assert(lp != NULL && item != NULL);
    NODE *p = lp->head->next;
    int i;
    for(i = 0; i < lp->count; i++) {
	if(lp->compare(item, p->data) == 0) {
	    return(p->data);
	}
	p = p->next;
    }
    return NULL;
}

//Makes a copy of the items in the list and returns the copy
//Big-O: O(n)
void *getItems(LIST *lp) {
    void **listCopy = malloc(sizeof(void*)*lp->count);
    NODE *p = lp->head->next;
    int i;
    for(i = 0; i<lp->count; i++) {
	listCopy[i] = p->data;
	p = p->next;
    }
    return listCopy;
}
