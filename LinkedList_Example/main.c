/*
 * main.c
 *
 *  Created on: 3 Jan 2020
 *      Author: Yahia
 */
#include <stdio.h>
#include <stdlib.h>

#include "std_types.h"
#include "common_macros.h"


#include "LinkedList_interface.h"

linkedlist yahia;
LINKEDLIST_node* Head;

int main(void){
	LINKEDLIST_Init(&yahia, &Head);
	LINKEDLIST_InsertAtFirst(&yahia,10, &Head);
	LINKEDLIST_InsertAtLast(&yahia,20, &Head);
	LINKEDLIST_InsertAtLast(&yahia,30, &Head);
	LINKEDLIST_InsertAtLast(&yahia,50, &Head);
	LINKEDLIST_InsertAtMiddle(&yahia,40, &Head, 3);
	LINKEDLIST_Print(&yahia, &Head);
	printf("\nIndex of 10 = %d", LINKEDLIST_Find(&yahia, &Head, 10));
	printf("\nIndex of 20 = %d", LINKEDLIST_Find(&yahia, &Head, 20));
	printf("\nIndex of 30 = %d", LINKEDLIST_Find(&yahia, &Head, 30));
	printf("\nIndex of 40 = %d", LINKEDLIST_Find(&yahia, &Head, 40));
	printf("\nIndex of 50 = %d", LINKEDLIST_Find(&yahia, &Head, 50));
	printf("\nSize of the list = %d", LINKEDLIST_Size(&yahia, &Head));
	LINKEDLIST_DeleteElement(&yahia, &Head, 2);
	printf("\n");
	LINKEDLIST_Print(&yahia, &Head);
	printf("\nIndex of 50 = %d", LINKEDLIST_Find(&yahia, &Head, 50));
	printf("\nSize of the list = %d", LINKEDLIST_Size(&yahia, &Head));
	LINKEDLIST_UpdateElement(&yahia,30, &Head, 3);
	LINKEDLIST_InsertAtFirst(&yahia,5, &Head);
	printf("\n");
	LINKEDLIST_Print(&yahia, &Head);
	LINKEDLIST_InsertAtLast(&yahia,50, &Head);
	LINKEDLIST_InsertAtLast(&yahia,60, &Head);
	LINKEDLIST_InsertAtLast(&yahia,70, &Head);
	LINKEDLIST_InsertAtLast(&yahia,80, &Head);
	LINKEDLIST_InsertAtLast(&yahia,90, &Head);
	LINKEDLIST_InsertAtLast(&yahia,100, &Head);
	LINKEDLIST_InsertAtLast(&yahia,110, &Head);
	LINKEDLIST_InsertAtLast(&yahia,120, &Head);
	LINKEDLIST_InsertAtLast(&yahia,130, &Head);
	LINKEDLIST_InsertAtLast(&yahia,140, &Head);
	LINKEDLIST_InsertAtLast(&yahia,150, &Head);
	LINKEDLIST_InsertAtLast(&yahia,160, &Head);
	LINKEDLIST_InsertAtLast(&yahia,170, &Head);
	LINKEDLIST_InsertAtLast(&yahia,180, &Head);
	LINKEDLIST_InsertAtLast(&yahia,190, &Head);
	LINKEDLIST_DeleteElement(&yahia, &Head, LINKEDLIST_Find(&yahia, &Head, 5));
	LINKEDLIST_Switch(&yahia, &Head, 2, 1);
	LINKEDLIST_DeleteHead(&yahia, &Head);
	LINKEDLIST_DeleteTail(&yahia, &Head);
	LINKEDLIST_InsertAtLast(&yahia,200, &Head);
	printf("\n");
	LINKEDLIST_Print(&yahia, &Head);
	//printf("\nValue of Index 4 = %d", LINKEDLIST_Get(&yahia, &Head, 4));
	//printf("\nValue of Head = %d", LINKEDLIST_GetHead(&yahia, &Head));
	//printf("\nValue of Tail = %d", LINKEDLIST_GetTail(&yahia, &Head));
}
