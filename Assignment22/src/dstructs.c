/* Setup */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#ifndef DSTRUCTS_H
#include "../deps/dstructs.h"
#endif

extern int errno;

/* Linked List Definitions */

/**************************************************
Function: init_LL
Author: Neil Kingdom
Date: Sep 17, 2021
Params: head - The head/root node of the LL
		  t_data - The head node's data
		  db_size - The size of data in bytes

Purpose: Initialize a given root/head node of a
singly linked list
**************************************************/
int init_LL(LL_Head** head, void* t_data, size_t db_size) {

	/* Check if head is already initialized */
	if(*head != NULL) {
		printf("Head is already initialized\n");
		return 1;
	}

	*head = malloc(sizeof(struct linkedList) + db_size);
	
	if(*head == NULL) {
		int error = errno;
		fprintf(stderr, "Error %d\n%s, Line: %d\nFailed to initialize head node in linked list\n", error, __FILE__, __LINE__);
		return error;
	}
	
	(*head)->data = t_data;	
	(*head)->next = NULL;
	return 0;
}

/**************************************************
Function: addNode_LL
Author: Neil Kingdom
Date: Sep 17, 2021
Params: head - The head/root node of the LL
		  t_data - The head node's data
		  db_size - The size of data in bytes

Purpose: Add a new node to an existing linked list.
If init_LL has not been called, this function will
fail
**************************************************/
int addNode_LL(LL_Head** head, void* t_data, size_t db_size) {

	/* Check if head has not been initialized */
	if(*head == NULL) {
		printf("You must initialize head before adding a new node to linked list\n");
		return 1;
	}

	LL_Node* nNode = malloc(sizeof(struct linkedList) + db_size);

	if(nNode == NULL) {
		int error = errno;
		fprintf(stderr, "Error %d\n%s, Line: %d\nFailed to initialize new node in linked list\n", error, __FILE__, __LINE__);
		return error;
	}

	nNode->data = t_data;
	/* The following operation sets nNode's next attribute to head, and then the external head is set the nNode */
	nNode->next = *head;
	*head = nNode;
	
	return 0;
}

/**************************************************
Function: deleteNode_LL
Author: Neil Kingdom
Date: Sep 18, 2021
Params: head - The head/root node of the LL
		  index - The index of the node to be deleted

Purpose: Delete a node from linked list. Deletion
should be done via index rather than data since LL 
can contain duplicate data. If the link list only 
contains head, the index is not checked, and the
list simply gets deleted
**************************************************/
int deleteNode_LL(LL_Head** head, int index) {

	int i;
	LL_Node* delete = *head;
	LL_Node* tmpNode = NULL;

	/* Check if head has not been initialized */	
	if(*head == NULL) {
		printf("Cannot perform deletion on an empty linked list");
		return 1;
	}

	/* If head is the only node, delete the entire list */
	if(delete->next == NULL) {
		deleteList_LL(head);
		return 0;
	}

	if(index == 0) {
		*head = (*head)->next;
		free(delete);
		return 0;
	}

	for(i = 0; i < index; i++) {
		tmpNode = delete;
		delete = delete->next;
	}

	tmpNode->next = delete->next;

	free(delete);
	
	return 0;
}

/**************************************************
Function: convertToString
Author: Neil Kingdom
Date: Sep 26, 2021
Params: str - The output string 
		  t_data - The data to be queried
		  db_size - The size of data in bytes

Purpose: This function is a sketchy but useful
way of "converting" data of any datatype to string
for comparison purposes. It takes the size of the
data in bytes, and will return the corresponding 
number of characters. Each byte of t_data is 
treated as a raw sequence of bits, and therefore,
the accuracy of this function improves for data
that occupies more bytes. Issues are prone to 
arise if the user compares data of two different
data types so this ought to be avoided. Note: this
does not convert the value to it's actual string
representation. It will output garbage, but that
garbage is consistent, and can be compared to other
garbage.
**************************************************/
int convertToString(char** str, void* t_data, size_t db_size) {

	int i;
	char buf[50];

	if(db_size > 50) {
		printf("Cannot convert data greater than 50 bytes in length");
		return 1;
	}

	for(i = 0; i < db_size; i++) {
		/* Voodo magic to cast each byte of t_data to char */
		buf[i] = (char)((*(((char*)t_data) + i)) + '0');
		strcpy(*str, buf);
	}
	return 0;
}

/**************************************************
Function: findData_LL
Author: Neil Kingdom
Date: Sep 27, 2021
Params: head - The head/root node of the LL
		  t_data - The data to be queried
		  db_size - The size of data in bytes

Purpose: Query data of any data type. The function
returns the index of the first node containing
matching data, otherwise returns -1
**************************************************/
int findData_LL(LL_Head** head, void* t_data, size_t db_size) {

	int i = 0;
	char* query = malloc(db_size);
	char* nodeData = malloc(db_size);
	LL_Node* tmpNode = *head;

	/* Check if head has not been initialized */	
	if(*head == NULL) {
		printf("Cannot data search query on an empty linked list");
		free(query);
		free(nodeData);
		return -1;
	}

	while(tmpNode != NULL) {
		convertToString(&query, t_data, db_size);
		convertToString(&nodeData, tmpNode->data, db_size);
		
		/* Check string equality */
		if(strcmp(query, nodeData) == 0) {
			free(query);
			free(nodeData);
			return i;
		}

		tmpNode = tmpNode->next;
		i++;
	}

	free(query);
	free(nodeData);
	
	return -1;
}

/**************************************************
Function: modData_LL
Author: Neil Kingdom
Date: Sep 27, 2021
Params: head - The head/root node of the LL
		  t_data - The head node's data
		  index - The index of the node to modify
		  db_size - The size of data in bytes

Purpose: Change the data currently located in the
node at given index with t_data
**************************************************/
int modData_LL(LL_Head** head, void* t_data, int index, size_t db_size) {

	int i;
	LL_Node* tmpNode = *head;

	/* Check if head has not been initialized */	
	if(*head == NULL) {
		printf("Cannot modify values in an empty linked list");
		free(tmpNode);
		return -1;
	}

	for(i = 0; i < index; i++) 
		tmpNode = tmpNode->next;

	tmpNode->data = t_data;

	return 0;
}

/**************************************************
Function: print_LL
Author: Neil Kingdom
Date: Sep 27, 2021
Params: head - The head/root node of the LL
		  db_size - The size of data in bytes

Purpose: This function calls convertToString 
function to print the entire linked list. It is not
supposed to be accurate, it is only for testing/
comparison purposes
**************************************************/
void print_LL(LL_Head** head, size_t db_size) {

	int i = 0;
	char* str = malloc(db_size);
	LL_Node* tmpNode = *head;
	
	while(tmpNode != NULL) {
		convertToString(&str, tmpNode->data, db_size);	
		printf("Data at index %d: %s\n", i, str);
		tmpNode = tmpNode->next;
		i++;
	}

	free(tmpNode);
	return;
}

/**************************************************
Function: deleteList_LL
Author: Neil Kingdom
Date: Sep 27, 2021
Params: head - The head/root node of the LL

Purpose: Delete the entire linked list
**************************************************/
int deleteList_LL(LL_Head** head) {

	LL_Node* tmpNode = *head;
	LL_Node* prev = NULL;

	while(tmpNode != NULL) {
		prev = tmpNode;
		tmpNode = tmpNode->next;
		free(prev);
	}

	free(tmpNode);
	*head = NULL;
	return 0;
}
