#include <string.h>
#include <stdio.h>
union orderInfo{
	char phoneNum[11];
	int orderNum;
};
struct customer{
	int order;
	char name[10];
	int classify; //if 1 then stores a phone number in bobadash[], if 2 then stores order number in inStore.
	union orderInfo info;
};
struct customer arr[10];
int count;
void enterOrder();
void fufillOrder();
void listOrders();
void sizeLessThanOrEqual();

