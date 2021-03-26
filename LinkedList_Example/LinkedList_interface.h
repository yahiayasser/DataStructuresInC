/*
 * LinkedList_interface.h
 *
 *  Created on: 1 Jan 2020
 *      Author: Yahia
 */

#ifndef LINKEDLIST_INTERFACE_H_
#define LINKEDLIST_INTERFACE_H_

#include "LinkedList_config.h"

struct LinkedlistNode{
	struct LinkedlistNode* PtrToNextNode;
	LINKEDLIST_DataSize Data;
};

typedef struct LinkedlistNode LINKEDLIST_node;
typedef LINKEDLIST_node linkedlist[LINKEDLIST_Max_Elements];

typedef enum{
	LINKEDLIST_Notfound,
	LINKEDLIST_Full,
	LINKEDLIST_Empty,
	LINKEDLIST_ElementNotFound,
	LINKEDLIST_NoError
}ErrorType;

#ifndef LINKEDLIST_PRINTING
#define LINKEDLIST_PRINTING		1
#endif

#ifndef LINKEDLIST_NOT_PRINTING
#define LINKEDLIST_NOT_PRINTING	0
#endif

ErrorType LINKEDLIST_Init(linkedlist* LINKEDLIST, LINKEDLIST_node** head);
ErrorType LINKEDLIST_InsertAtFirst(linkedlist* LINKEDLIST, LINKEDLIST_DataSize data, LINKEDLIST_node** head);
ErrorType LINKEDLIST_InsertAtLast(linkedlist* LINKEDLIST, LINKEDLIST_DataSize data, LINKEDLIST_node** head);
uint8 LINKEDLIST_Size(linkedlist* LINKEDLIST, LINKEDLIST_node** head);
ErrorType LINKEDLIST_InsertAtMiddle(linkedlist* LINKEDLIST, LINKEDLIST_DataSize data, LINKEDLIST_node** head, uint8 index);
uint8 LINKEDLIST_Find(linkedlist* LINKEDLIST, LINKEDLIST_node** head, LINKEDLIST_DataSize data);
void LINKEDLIST_FREE(LINKEDLIST_node* PtrToNode);
ErrorType LINKEDLIST_DeleteHead(linkedlist* LINKEDLIST, LINKEDLIST_node** head);
ErrorType LINKEDLIST_DeleteTail(linkedlist* LINKEDLIST, LINKEDLIST_node** head);
ErrorType LINKEDLIST_DeleteElement(linkedlist* LINKEDLIST, LINKEDLIST_node** head, uint8 index);
ErrorType LINKEDLIST_UpdateElement(linkedlist* LINKEDLIST, LINKEDLIST_DataSize data, LINKEDLIST_node** head, uint8 index);
ErrorType LINKEDLIST_Switch(linkedlist* LINKEDLIST, LINKEDLIST_node** head, uint8 Index1, uint8 Index2);
LINKEDLIST_DataSize LINKEDLIST_Get(linkedlist* LINKEDLIST, LINKEDLIST_node** head, uint8 index);
LINKEDLIST_DataSize LINKEDLIST_GetHead(linkedlist* LINKEDLIST, LINKEDLIST_node** head);
LINKEDLIST_DataSize LINKEDLIST_GetTail(linkedlist* LINKEDLIST, LINKEDLIST_node** head);
#if(LINKEDLIST_PRINT ==  LINKEDLIST_PRINTING)
ErrorType LINKEDLIST_Print(linkedlist* LINKEDLIST, LINKEDLIST_node** head);
#endif

#endif /* LINKEDLIST_INTERFACE_H_ */
