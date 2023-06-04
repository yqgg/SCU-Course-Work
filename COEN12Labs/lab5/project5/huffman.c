/* Yi Qian Goh
 * 18 May 2022
 * COEN 12 - Lab 5
 * Description: Implement huffman coding for data compression. In this case, the code will compile the frequency of characters in a .txt file and determine the bits of the frequencies.
 * */

#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "pqueue.h"
#include "pack.h"

typedef struct node NODE;

static void readFile(char* fileName);
static NODE* mkNode(int data, NODE* left, NODE* right);
static int depth(NODE* np);
static int nodeCmp(NODE* np1, NODE* np2);

int counts[257];//each index number is an ascii value, and the value in each index is the frequency of the character
NODE *nodes[257];//priority queue

//Big-O: O(1)
int main(int argc, char* argv[]){
    if(argc == 2){
	printf("Missing file name");
	return 0;
    } else {
	readFile(argv[1]);
    }
    PQ *pq = createQueue(nodeCmp);//create the priority queue 
    int i;
    for(i = 0; i < 256; i++) { //make each non-zero frequency character into a leaf and add it to the priority queue
	if(counts[i] > 0){
	    nodes[i] = mkNode(counts[i], NULL, NULL);
	    addEntry(pq, nodes[i]);
	}
    }
    nodes[256] = mkNode(0, NULL, NULL);//last spot is 0 as the EOF to ensure that the priority queue is never truly empty
    addEntry(pq, nodes[256]);
    int j;  
    while(numEntries(pq) > 1){//repeatedly combine the least frequent nodes until you are left with one node in the priority queue (the huffman tree)
	NODE* left = removeEntry(pq);//smallest nodes as root of the main heap
	NODE* right = removeEntry(pq);
	NODE* parent = mkNode(left->count + right->count, left, right);
	addEntry(pq, parent);
    }
    for(j = 0; j < 256; j++){ //print out the bits used for each character in text file
        if(nodes[j] != NULL){
	printf(isprint(j) ? "%c" : "%03o", j);
	printf(": %d x %d bits = %d bits\n", counts[j], depth(nodes[j]), counts[j]*depth(nodes[j]));
	}
    }
    pack(argv[1], argv[2], nodes);
    destroyQueue(pq);
    return 0;
}

static void readFile(char* fileName) {
    FILE* fp = fopen(fileName, "r");
    if(fp == NULL) {//if file cannot be opened
	printf("readFile error occurred");
	return;
    }
    int x = getc(fp);//will continously retrieve the character at spot in file in terms of ASCII (0 - 255)
    while(x != EOF) {
        counts[x]++;
	x = getc(fp);
    }
    fclose(fp);
    return;
}

//Big-O: O(1)
static NODE* mkNode(int data, NODE* left, NODE* right) {
    NODE* root = malloc(sizeof(NODE));
    assert(root != NULL);
    root->count = data;
    root->parent = NULL;
    if(left != NULL) {//if left and right are not NULL, they should be the new node's children
	left->parent = root;
    }
    if(right != NULL) {
	right->parent = root;
    }
    return root;
}

//Big-O: O(1)
static int depth(NODE *np) { //return the depth of a given node
    assert(np != NULL);
    if(np->parent == NULL) {
	return 0;
    }
    return depth(np->parent) + 1;
}

//Big-O: O(1)
static int nodeCmp(NODE *np1, NODE *np2) {//return the largest of two nodes
    assert(np1 != NULL && np2 != NULL);
    return (np1->count < np2->count) ? -1 : (np1->count > np2->count);
}
