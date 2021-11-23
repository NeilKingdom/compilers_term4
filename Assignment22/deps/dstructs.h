/* Setup */

#include <stddef.h>

#ifndef DSTRUCTS_H
#define DSTRUCTS_H

/* Linked List Declarations */

typedef struct linkedList {

	void* data;
	struct linkedList* next;
} LL_Node, LL_Head;

int init_LL(LL_Head**, void*, size_t);
int addNode_LL(LL_Head**, void*, size_t);
int deleteNode_LL(LL_Head**, int);
int findData_LL(LL_Head**, void*, size_t);
int modData_LL(LL_Head**, void*, int, size_t);
int deleteList_LL(LL_Head**);
void print_LL(LL_Head**, size_t);
int convertToString(char**, void*, size_t);

/* Double Linked List Declarations */

typedef struct doublyLinkedList {

	void* data;
	struct doublyLinkedlist* next;
	struct doublyLinkedList* prev;
} DLL_Node, DLL_Head, DLL_Tail;

/* Hash Map Declarations */

void* hashVal_HM();
int init_HM();
int resize_HM();
int addEntry_HM();
int delEntry_HM();
int findEntry_HM();

/* Binary Tree Declarations */

typedef struct node {
	struct node* child;
	char* data;
} Node, Root;

/* Binary Search Declarations */

/* Some sort of sorting algorithm (Numeric and String) */
int binSearchNumeric(void* a[], void* key); /* Cast numeric types to double*/
int binSearchString();

#endif
