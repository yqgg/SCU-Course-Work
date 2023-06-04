#include <string.h>
#include <stdio.h>
typedef union {
	char bobadash[11];
	int inStore;
} ORDER_INFO;
typedef struct{
	int order;
	char name[10];
	int classify; //if 1 then stores a phone number in bobadash[], if 2 then stores order number in inStore.
	ORDER_INFO confirmation;
} customer;
customer arr[10];
int count;
void enterOrder();
void fufillOrder();
void listOrders();
void sizeLessThanOrEqual();

