/*Name: Yi Qian Goh
 * Date: 4/13/2022
 * Section: Wednesday 2:15pm-5:00pm
 * Code Description: The functions in this .c file are programmed to manipulate an unsorted array of char array pointers It utilizes sequential searching to traverse the array and look for specified elements. 
  */
//header files
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "set.h"

//define a structure with the number of elements in the array, total length of the array, and the data in the array.
typedef struct set {
    int count;
    int length;
    char **data;
} SET;

//allocates memory in the array and defines the variables in the structure
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

//a static function the implements sequential searching on an array
static int search(SET *sp, char *elt) {
    assert(sp != NULL && elt != NULL);
    int i;
    for(i = 0; i < sp->count; i++) {
	if(strcmp(elt, sp->data[i]) == 0) {
	    return i;
	}
    }
    return -1;
}

//function used to delete the entire array. Frees the data from the char array, then the array of char array pointers, then finally the entire structure.
void destroySet(SET *sp) {
    assert(sp != NULL);
    int i;
    for(i = 0; i<sp->count; i++) {
	free(sp->data[i]);
    }
    free(sp->data);
    free(sp);
}

//returns and integer indicated the number of elements in the array
int numElements(SET *sp) {
    assert(sp != NULL);
    return sp->count;
}

//add elements at the end of the array. 
void addElement(SET *sp, char* elt) {
    assert(sp != NULL && elt != NULL);
    if(findElement(sp, elt) == NULL) {
	sp->data[sp->count] = strdup(elt);
	assert(sp->data[sp->count] != NULL);
	strcpy(sp->data[sp->count], elt);
	sp->count += 1;
    }
}

//Searches for the element given by the parameter and then removing the element from the array. The last element of the array is then inserted into the index of the removed element. Order does not matter in an unsorted array so putting the last element into the index of the removed element works.
void removeElement(SET *sp, char *elt) {
    int i = search(sp, elt);
    if(i != -1) {
	assert(sp != NULL && elt != NULL);
	free(sp->data[i]);
	sp->data[i] = sp->data[--sp->count];
    }
}

//Uses the search function to find the element. If found, the element is returned. If not found, then it returns NULL.
char *findElement(SET *sp, char *elt) {
    assert(sp != NULL && elt != NULL);
    int i = search(sp, elt);
    if(i != -1) {
	return sp->data[i];
    } else {
	return NULL;
    }
}

//Creates a new char** array. Allocates memory and copies the elements from SET *sp into the new array. Returns the new array.
char **getElements(SET *sp) {
    assert(sp != NULL);
    char **arr;
    arr = malloc(sizeof(char *) * sp->count);
    assert(arr != NULL);
    return memcpy(arr, sp->data, sizeof(char *) *sp->count);
}
