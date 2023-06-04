/* Yi Qian Goh
 * 18 May 2022
 * COEN 12 - Lab 5
 * Description: Implementations of a priority queue
 * */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "pqueue.h"

//instatiation of static functions determining the parent, left and right children of a node
static int p(int i); //parent node
static int l(int i); //left child node
static int r(int i); //right child node


typedef struct pqueue {
    int count;
    int length;
    void **data;
    int (*compare)();
} PQ;

//creates the priority queue
//Big-O: O(1)
PQ *createQueue(int (*compare)()) {
    assert(compare != NULL);
    PQ *pq;
    pq = malloc(sizeof(PQ));
    assert(pq != NULL);
    pq->count = 0;
    pq->length = 10;
    pq->data = malloc(sizeof(void*)*10);
    pq->compare = compare;
    assert(pq->data != NULL);
    return pq;
}

//frees all memory from the queue
//Big-O: O(1)
void destroyQueue(PQ *pq) {
    assert(pq != NULL);
    int i;
    for(i = 0; i<pq->count; i++) {
	free(pq->data[i]);
    }
    free(pq->data);
    free(pq);
}

//Return the number of nodes in the queue
//Big-O: O(1)
int numEntries(PQ *pq) {
    assert(pq != NULL);
    return pq->count;
}

//Adds a new node to the priority queue and reallocates 2 times of the full memory if the priority queue is full
//Big-O: O(logn)
void addEntry(PQ *pq, void *entry) {
    assert(pq != NULL && entry != NULL);
    if(pq->length == pq->count) {
	pq->data = realloc(pq->data, sizeof(void *)*pq->length*2);
	pq->length *= 2;
    }
    pq->data[pq->count] = entry;
    int i = pq->count;
    while(pq->compare(pq->data[i], pq->data[p(i)]) < 0) {
	void *temp = pq->data[p(i)];
	pq->data[p(i)] = pq->data[i];
	pq->data[i] = temp;
	i = p(i);
    }
    pq->count++;
}

//Returns the removed item and shifts the queue as necessary once the item is removed
//Big-O: O(logn)
void *removeEntry(PQ *pq) {
    assert(pq != NULL);
    void *root = pq->data[0];
    int i = 0;
    pq->data[i] = pq->data[pq->count -1];
    while(l(i) < pq->count) {
	int smallerChild = l(i);
	if(r(i) < pq->count) {
	    if(pq->compare(pq->data[l(i)], pq->data[r(i)]) < 0) {
		smallerChild = l(i);
	    } else {
		smallerChild = r(i);
	    }
	}
	if(pq->compare(pq->data[smallerChild], pq->data[i]) < 0) {
	    void* temp = pq->data[smallerChild];
	    pq->data[smallerChild] = pq->data[i];
	    pq->data[i] = temp;
	    i = smallerChild;
	} else {
	    break;
	}
    }
    pq->count--;
    return root;
}

static int p(int i) {
    return (i-1)/2;
}

static int l(int i) {
    return (i*2)+1;
}

static int r(int i) {
    return (i*2)+2;
}
