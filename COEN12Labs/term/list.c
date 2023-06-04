/*  Yi Qian Goh
 *  COEN 12 Term Project
 *  4 June 2022
 *  Description: In this project, there is a doubly linked list of nodes, and each of the nodes are circular arrays. The linked list had next and prev pointers, as well had head and tail pointers for more efficient access to the nodes. We implement multiple functions to manipulate the linked list and the circular arrays in each node.
 *
 * */


#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "list.h"

//Global variable for the length of each array in the linked list
#define LENGTH 2

//function declaration. Used only in this file
struct node *createNode(int);

//List structure
typedef struct list {
    int count; //Number of nodes
    struct node *head; //head pointer
    struct node *tail; //tail pointer
} LIST;

//Node structure
typedef struct node {
    void **data; //takes data
    int first; //the first index of the circular array
    int length; //length of the the circular array
    int nCount; //number of items in the circular array
    struct node *next; //next pointers
    struct node *prev; //prev pointers
} NODE;

//Creates nodes of indicated length
//Big-O: O(1)
NODE *createNode(int length) {
    NODE *np = malloc(sizeof(NODE));
    assert(np != NULL);
    np->length = length;
    np->nCount = 0;
    np->first = 0;
    np->next = NULL;
    np->prev = NULL;
    np->data = malloc(sizeof(void*)*length); 
    assert(np != NULL);
    return np;
}

//Creates the list
//Big-O: O(1)
LIST *createList(void) {
    LIST *lp = malloc(sizeof(LIST));
    assert(lp != NULL);
    lp->count = 0;
    lp->head = createNode(LENGTH);
    assert(lp->head != NULL);
    lp->tail = lp->head;
    lp->head->next = lp->head;
    lp->head->prev = lp->head;
    return lp;
}

//Deallocate memory associated with the list pointed to by lp
//Big-O: O(n)
void destroyList(LIST *lp) {
    assert(lp != NULL);
    NODE *np1 = lp->head;
    NODE *np2;
    do {
	np2 = np1->next;
	//free(np1->data);
	free(np1);
	np1 = np2;
    } while(np1 != lp->head);
    free(lp);
}

//Return number of nodes in the linked list
//Big-O: O(1)
int numItems(LIST *lp) {
    assert(lp != NULL);
    return lp->count;
}

//Add an item to the first index of the first node. Since the arrays are circular arrays, first does not necessarily mean index 0. 
//Big-O: O(n)
void addFirst(LIST *lp, void *item) {
    assert(lp != NULL);
    if(lp->head->nCount == LENGTH) { //if the first node of the list is full then create a new node and make the new node the head
	NODE *newNode = createNode(LENGTH);
	lp->head->prev = newNode;
	newNode->next = lp->head;
	newNode->prev = NULL;
	newNode->data[(lp->head->first + LENGTH -1)%LENGTH] = item; //The item is added to the new empty node, however it is not added to the first index of the array. Rather, it is added to the last index of the circular array because next time we want to addFirst, it will add the item to the first index. 
	newNode->nCount++;
	lp->head = newNode;	
    } else {
        lp->head->data[lp->head->first] = item; //First node is not full, so add to the first index.
    }
}

//Add item as the last item in the list pointed to by lp
//Big-O: O(n)
void addLast(LIST *lp, void *item) {
    assert(lp != NULL);
    if(lp->tail->nCount == LENGTH) { //Same as addFirst, if the last node is full, then creat a new empty node at the end of the list.
	NODE *newNode = createNode(LENGTH);
	lp->tail->next = newNode;
	newNode->prev = lp->tail;
	newNode->next = NULL;
	newNode->data[newNode->first] = item; //In addLast it is okay to add the item to the first index
	lp->tail = newNode;
	lp->tail->nCount++;
	lp->count++;
    } else {
	int i = lp->tail->nCount + lp->tail->first;
	if(i >= lp->tail->length) {
	    i -= lp->tail->length;
	}
	lp->tail->data[i] = item; //Last node is not empty, so the node is added to the end of the array
	lp->tail->nCount++;
    }
}

//remove and return the first item of the list pointed to by lp
//Big-O: O(n)
void *removeFirst(LIST *lp) {
    assert(lp != NULL);
    void *temp = lp->head->data[lp->head->first];
    if(lp->head->nCount == 0) { //Deallocate the first node if it is empty
	lp->head = lp->head->next;
	//free(lp->head->prev->data);
	free(lp->head->prev);
	lp->head->prev = NULL;
	lp->count--;
    }
    free(lp->head->data[lp->head->first]); //might be interferring with outer function freeing data. do not need to free.
    lp->head->nCount--;
    return temp;
}

//Remove and return the last item of the list pointed to by lp
//Big-O: O(n)
void *removeLast(LIST *lp) {
    assert(lp != NULL);
    if(lp->tail->nCount == 0) { //Deallocated the last node if it is empty
	lp->tail = lp->tail->prev;
	//free(lp->tail->next->data);
	free(lp->tail->next);
	lp->tail->next = NULL;
	lp->count--;
    }
    lp->tail->nCount--;
    //Since each node is a circular array and not a linear array, we must use this (f+n-1)%m function to find the corrent index. The first index is not necessarily 0, and the last index is not necessarily LENGTH-1 in a circular array.
    void *temp = lp->tail->data[(lp->tail->first + lp->tail->nCount -1)% LENGTH];
    free(lp->tail->data[(lp->tail->first + lp->tail->nCount -1)% LENGTH]);
    return temp;
}

//Get an item from the list from the indicated index
//Big-O: O(n)
void *getItem(LIST *lp, int index) {
    assert(lp != NULL);
    NODE *current = lp->head;
    index += lp->head->first;
    while(current->nCount <= index) { //If the index indicated is greater than the number of items in the array, then it will subtract the number of items from the index given. Then, get the item from the next node with the new index.
	index -= current->nCount;
	current = current->next;
    }
    return current->data[index];
}

//Set an item to the indicated index
//Big-O: O(n)
void setItem(LIST *lp, int index, void *item) {
    assert(lp != NULL && item != NULL);
    //set an item to a particular index 
    NODE *current = lp->head;
    index += lp->head->first;
    while(current->nCount <= index) { //Same as *getItem. The index is mutable
	index -= current->nCount;
	current = current->next;
    }
    current->data[index] = item;
}
