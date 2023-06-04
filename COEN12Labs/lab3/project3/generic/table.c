/*
 * Yi Qian Goh
 * COEN 12 Project 3
 * 29 April 2022
 * Description: Implementation of a set abstract data type for generic pointer types 
 * */

//header files
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "set.h"
#include <stdbool.h>

//function declarations
//unsigned strhash(char *s);
//static int search(SET *sp, char *elt, bool *found);

//define a structure. Compare to lab2, this structure is similar except tor an additional array of flags to keep track of which indexes are filled, empty, or were deleted.
typedef struct set {
    int count;
    int length;
    void **data;
    char *flags;
    int (*compare)();
    unsigned (*hash)();
} SET;

//This funciton allocates memory
//Big-O: O(n)
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) {
    SET *sp;
    sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->count = 0;
    sp->length = maxElts;
    sp->data = malloc(sizeof(void*)*maxElts);
    assert(sp->data != NULL);
    sp->flags = malloc(sizeof(char)*maxElts);
    assert(sp->flags != NULL);
    int i;
    for(i = 0; i<sp->length; i++) {
    sp->flags[i] = 'E';
    }
    sp->compare = compare;
    sp->hash = hash;
    return sp;
}

//sequential search function that returns the index of specified elt if it is found.
////Big-O: O(n)
static int search(SET *sp, void *elt, bool *found) {
    assert(sp != NULL && elt != NULL && found!=NULL);
    int i;
    for(i = 0; i < sp->length; i++) {
        int locn = ((sp->hash)(elt)+i)%sp->length; //makes sure all indexes in the array is serched. When the locn starts off in the middle of the array, it will loop back to the beginnign of the array because of this equation
	if(sp->flags[locn] == 'F') { //if the flag is 'F' the index being searched is filled. Next we must check if the string is the same as the specified element. If not then search the next index.
	    if((*sp->compare)(elt, sp->data[locn]) == 0){ //check if the filled spot in the array contains the element we specified in the parameter
	        *found = true;
	        return locn;
	    }
	}
	if(sp->flags[locn] == 'D'){ //if the flag is 'D' the element in the array had been deleted. new element should still be inserted.
            *found = false;
	    return locn;
	} else if (sp->flags[locn] == 'E') { //if the flag is 'E' the index is empty and the new element should be inserted.
           *found = false;
            return locn;
        }
     }
     *found = false;
     return -1;
}

//frees allocated memory
//Big-O: O(n)
void destroySet(SET *sp) { 
    assert(sp != NULL);
    free(sp->data);
    free(sp->flags);
    free(sp);
    return;
}

//returns number of elements in the sp->data array
int numElements(SET *sp) {
    assert(sp != NULL);
    return sp->count;
}                         

//Checks is the element is already in the array, if not then insert it.
////Big-O: O(n)
void addElement(SET *sp, void *elt) {
    assert(sp != NULL && elt != NULL);
    bool found;
    int locn = search(sp, elt, &found);
    if(!found) {
        sp->data[locn] = elt;
        sp->flags[locn] = 'F';
        sp->count += 1;
    }
    return;
}

//removes the element from the array and changes the flag to 'D' indicating that the element was deleted. Then the memory is freed.
////Big-O: O(n)
void removeElement(SET *sp, void *elt) {
    assert(sp != NULL && elt != NULL);
    bool found;
    int i = search(sp, elt, &found);
    if(found) {
	sp->flags[i] = 'D';
	//free(sp->data[i]);
	sp->count -= 1;
    }
}

//Uses the search function to find the element. If found, the element is returned. If not found, then it returns NULL.
////Big-O: O(n)
void *findElement(SET *sp, void *elt) {
    assert(sp!=NULL && elt!=NULL);
    bool found;
    int i = search(sp, elt, &found);
    if(found) {
	return sp->data[i];
     } else {
        return NULL;
    }
}

//creates a new array and inserts all the elements in sp->data into the new array. Returns the new array
////Big-O: O(n)
void *getElements(SET *sp) {
    assert(sp != NULL);
    void **elts = malloc(sizeof(void*)*sp->count);
    assert(elts != NULL);
    int i, j=0;
    for(i = 0; i < sp->length; i++) {
        if(sp->flags[i] == 'F') {
	    elts[j] = sp->data[i];
	    j++;
	}
    }
    return elts;
}
