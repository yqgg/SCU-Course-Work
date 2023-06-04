/*Name: Yi Qian Goh
 * Data: 4/13/2022
 * Section: Wednesday 2:15pm-5:00pm
 * Code Description: The functions in this .c file are programed to manipulate a sorted array of char array pointers. It utlizes binary searching to traverse thea rray and look for specified elements.
 * */

//header files
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "set.h"
#include <stdbool.h>

//define a structure with the number of elements int he array, total length of the array, and the data in the array
typedef struct set {
    int count;
    int length;
    char **data;
} SET;

//allocated memory in the array and defines the variables in the structure
SET *createSet(int maxElts) {
    SET *sp;
    sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->count = 0;
    sp->length = maxElts;
    sp->data = malloc(sizeof(char*)*maxElts);
    assert(sp->data!=NULL);
    return sp;
}

//static funtion implementing binary search of an array
static int binarySearch(SET *sp, char *elt, bool *found) {
    assert(sp != NULL && elt != NULL && found != NULL);
    int lo, hi, mid;
    lo = 0;
    hi = sp->count - 1;
    while(lo <= hi) {
	mid = (lo+hi)/2;
	if( strcmp(sp->data[mid], elt) == 0) {
	    *found = true;
	    return mid;
	} else if (strcmp(sp->data[mid], elt) < 0) {
	    lo = mid +1;
	} else {
	    hi = mid -1;
	}
    }
    *found = false;
    return lo;
}

//function used to delete the entire array, Frees the data from the char array, then the array of char array pointers, then finally the entire structure.
void destroySet(SET *sp) {
    assert(sp != NULL);
    int i;
    for(i = 0; i<sp->count; i++) {
	free(sp->data[i]);
    }
    free(sp->data);
    free(sp);
}

int numElements(SET *sp) {
    return sp->count;
}

//uses binarySearch function to find the corrent index to insert the element. First, the elements greater than the indicated index must be shifted forward by one index. Then, the new element is inserted into the indicated index.
void addElement(SET *sp, char *elt) {
    bool found;
    int i = binarySearch(sp, elt, &found);
    if(!found) {
	assert(sp != NULL && elt != NULL);
	int j;
	for(j = sp->count; j>i; j--) {
	    sp->data[j] = sp->data[j-1];
	}
	elt = strdup(elt);
	assert(elt != NULL);
	sp->data[i] = elt;
	sp->count++;
    }
}

//Seaches for the elemnt given by the parameter and then removing the element from the array. The last element of the array is then inserted into the index of the removed element. Order does not matter in an unsorted array so putting the last element into the index of the removed element works.
void removeElement(SET *sp, char *elt) {
    bool found;
    int i = binarySearch(sp, elt, &found);
    if(found) {
	assert(sp != NULL && elt != NULL);
	int j;
	for(j = i+1; j<sp->count; j++) {
	    sp->data[j-1] = sp->data[j];
	}
	sp->count--;
    }	
}

//Uses the search function to find the element. If found, the element is retuned. If not found, then it returns NULL.
char *findElement(SET *sp, char *elt) {
    assert(sp != NULL && elt != NULL);
    bool found;
    int i = binarySearch(sp, elt, &found);
    if(found) {
	return sp->data[i];
    } else {
	return NULL;
    }
}

//Creates a new char** array. Allocates memory and copies the elements from SET *sp into the new array. Returns the ne array.
char **getElements(SET *sp) {
    assert(sp != NULL);
    char **arr;
    arr = malloc(sizeof(char *) * sp->count);
    assert(arr != NULL);
    return memcpy(arr, sp->data, sizeof(char *) *sp->count);
}
