/* Yi Qian Goh
 * 12 May 2022
 * COEN 12 - Lab 4
 * Description: Implement a set using a hash table with hashing and chaining. There is no need for probing because each spot is a linked list giving an infinite amount of spots.*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "set.h"
#include "list.h"
#define ALPHA 20

//List structure. List of doubly linked nodes
typedef struct list {
    int count;
    int (*compare)();
    struct node *head;
} LIST;

//Node structure
typedef struct node {
    void *data;
    struct node *next;
    struct node *prev;
} NODE;

//SET structure containing lists
typedef struct set {
    int length;
    int count;
    int (*compare)();
    unsigned (*hash)();
    LIST **lists;
} SET;

//Creates and allocated memory to the set, lists, and nodes
//Big-O: O(n)
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) {
    assert(compare != NULL && hash != NULL);
    SET *sp;
    sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->length = maxElts/ALPHA;
    sp->count = 0;
    sp->compare = compare;    
    sp->hash = hash;
    sp->lists = malloc(sizeof(LIST*)*sp->length);
    assert(sp->lists != NULL);
    int i;
    for(i = 0; i < sp->length; i++){
        sp->lists[i] = createList(compare);
    }   
    return sp;
}

//destroys the entire set by freeing allocated memory
//Big-O: O(1)
void destroySet(SET *sp) {
    assert(sp != NULL);
    free(sp->lists);
    free(sp);
}

//returns the number of elements in the set
//Big-O: O(1)
int numElements(SET *sp) {
    assert(sp != NULL);
    return sp->count;
}

//Add elements the a list
//Big-O: O(n)
void addElement(SET *sp, void *elt) {
    assert(sp != NULL && elt != NULL);
    int i = (*sp->hash)(elt) % sp->length;
    if(findItem(sp->lists[i],elt) == NULL)  {
        addFirst(sp->lists[i] , elt);
	sp->count++;
    }
}

//Removes an appointed element from a list if it is found
//Big-O: O(n)
void removeElement(SET *sp, void *elt)	{
    assert(sp != NULL && elt != NULL);
    int index = (*sp->hash)(elt)%sp->length;
    if(findItem(sp->lists[index],elt) != NULL)	{
	removeItem(sp->lists[index], elt);
	sp->count--;
    }
}

//Find out if the elements exist and return pointer
//Big-O: O(n)
void *findElement(SET *sp, void *elt)	{
    assert(sp != NULL && elt != NULL);
    int index = (*sp->hash)(elt) % sp->length;
    return findItem(sp->lists[index], elt); 
}

//Create a copy of the elements in set and return the copy
//Big-O: O(n)
void *getElements(SET *sp)  {
    assert(sp != NULL);
    NODE *np;
    void **copy = malloc(sizeof(void*)*sp->count);
    int i, j;
    j = 0; 
    for(i = 0; i < sp->length; i++) {
	int num = numItems(sp->lists[i]);
	if(num != 0)	{
	    np = sp->lists[i]->head->next;
	    while(np != sp->lists[i]->head) {
		copy[j] = np->data;
		num++;
		j++;
		np = np->next;
	    }
	}
    }
    return copy; 
}
