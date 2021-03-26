/*
 * LinkedList_prg.c
 *
 *  Created on: 1 Jan 2020
 *      Author: Yahia
 */

#include "std_types.h"
#include "common_macros.h"

#include "LinkedList_interface.h"
#include "LinkedList_private.h"

#if(LINKEDLIST_PRINT == LINKEDLIST_PRINTING)
#include <stdio.h>
#include <stdlib.h>
#endif

static uint8 LINKEDLIST_Check(linkedlist* LINKEDLIST, LINKEDLIST_node** head){
	LINKEDLIST_node* Ptr_Elements = (LINKEDLIST_node*)LINKEDLIST;
	uint8 count = 0;
	if(*head == NULL){
		while(count != LINKEDLIST_Max_Elements){
			if(Ptr_Elements[count].Data != 0)
				return 0;
			count++;
		}
		return 1;
	}
	else{
		while(count != LINKEDLIST_Max_Elements){
			if(*head == (&Ptr_Elements[count])){
				return 1;
			}
			count++;
		}
		return 0;
	}
}

LINKEDLIST_ErrorType LINKEDLIST_Init(linkedlist* LINKEDLIST, LINKEDLIST_node** head){
	LINKEDLIST_node* Ptr_Elements = (LINKEDLIST_node*)LINKEDLIST;
	uint8 count = 0;
	while(count != LINKEDLIST_Max_Elements){
		Ptr_Elements[count].Data = 0;
		Ptr_Elements[count].PtrToNextNode = LINKEDLIST_MAXADD;
		count++;
	}
	(*head) = NULL;

	return LINKEDLIST_NoError;
}

LINKEDLIST_ErrorType LINKEDLIST_InsertAtFirst(linkedlist* LINKEDLIST, LINKEDLIST_DataSize data, LINKEDLIST_node** head){
	if(LINKEDLIST_Check(LINKEDLIST, head) == 0)
		return LINKEDLIST_Notfound;
	LINKEDLIST_node* Ptr_Elements = (LINKEDLIST_node*)LINKEDLIST;
	uint8 count = 0;
	while((count != LINKEDLIST_Max_Elements) && (Ptr_Elements[count].PtrToNextNode != LINKEDLIST_MAXADD)){
		count++;
	}

	if(count == LINKEDLIST_Max_Elements){
		return LINKEDLIST_Full;
	}
	else{
		Ptr_Elements[count].Data = data;
		Ptr_Elements[count].PtrToNextNode = (*head);
		(*head) = &Ptr_Elements[count];
	}

	return LINKEDLIST_NoError;
}

LINKEDLIST_ErrorType LINKEDLIST_InsertAtLast(linkedlist* LINKEDLIST, LINKEDLIST_DataSize data, LINKEDLIST_node** head){
	if(LINKEDLIST_Check(LINKEDLIST, head) == 0)
		return LINKEDLIST_Notfound;
	LINKEDLIST_node* Ptr_Elements = (LINKEDLIST_node*)LINKEDLIST;
	LINKEDLIST_node* current = (LINKEDLIST_node*)*head;
	uint8 count = 0;

	while((count != LINKEDLIST_Max_Elements) && (Ptr_Elements[count].PtrToNextNode != LINKEDLIST_MAXADD)){
		count++;
	}

	if(count == LINKEDLIST_Max_Elements){
		return LINKEDLIST_Full;
	}
	else{
		Ptr_Elements[count].Data = data;
		Ptr_Elements[count].PtrToNextNode = NULL;
		if(current == NULL){
			(*head) = &Ptr_Elements[count];
			return LINKEDLIST_NoError;
		}
		else{
			while((current -> PtrToNextNode) != NULL){
				current = current -> PtrToNextNode;
			}
			current -> PtrToNextNode = &Ptr_Elements[count];
			return LINKEDLIST_NoError;
		}
	}
}

uint8 LINKEDLIST_Size(linkedlist* LINKEDLIST, LINKEDLIST_node** head){
	if(LINKEDLIST_Check(LINKEDLIST, head) == 0)
		return LINKEDLIST_Notfound;
	LINKEDLIST_node* current = (LINKEDLIST_node*)*head;
	uint8 size = 0;
	if(current == NULL){
		return size;
	}
	else{
		while(current != NULL){
			current = current -> PtrToNextNode;
			size++;
		}
		return size;
	}
}

LINKEDLIST_ErrorType LINKEDLIST_InsertAtMiddle(linkedlist* LINKEDLIST, LINKEDLIST_DataSize data, LINKEDLIST_node** head, uint8 index){
	if(LINKEDLIST_Check(LINKEDLIST, head) == 0)
		return LINKEDLIST_Notfound;
	LINKEDLIST_node* Ptr_Elements = (LINKEDLIST_node*)LINKEDLIST;
	LINKEDLIST_node* current = (LINKEDLIST_node*)*head;
	LINKEDLIST_node* previous = NULL;
	uint8 count = 0;
	uint8 POS = 0;

	while((count != LINKEDLIST_Max_Elements) && (Ptr_Elements[count].PtrToNextNode != LINKEDLIST_MAXADD)){
		count++;
	}

	if(count == LINKEDLIST_Max_Elements){
		return LINKEDLIST_Full;
	}
	else{
		Ptr_Elements[count].Data = data;
		if(index == 0){
			Ptr_Elements[count].PtrToNextNode = current;
			*head = &Ptr_Elements[count];
			return LINKEDLIST_NoError;
		}
		else{
			while(POS < index){
				previous = current;
				current = current -> PtrToNextNode;
				POS++;
			}
			Ptr_Elements[count].PtrToNextNode = current;
			previous -> PtrToNextNode = &Ptr_Elements[count];
			return LINKEDLIST_NoError;
		}
	}
}

uint8 LINKEDLIST_Find(linkedlist* LINKEDLIST, LINKEDLIST_node** head, LINKEDLIST_DataSize data){
	if(LINKEDLIST_Check(LINKEDLIST, head) == 0)
		return LINKEDLIST_Notfound;
	LINKEDLIST_node* current = (LINKEDLIST_node*)*head;
	uint8 index = 0;
	if(current == NULL){
		return -1;
	}
	while(((current -> Data) != data) && (current != NULL)){
		current = current -> PtrToNextNode;
		index++;
	}
	if(current == NULL){
		return -1;
	}
	else{
		return index;
	}
}

void LINKEDLIST_FREE(LINKEDLIST_node* PtrToNode){
	PtrToNode -> Data = 0;
	PtrToNode -> PtrToNextNode = LINKEDLIST_MAXADD;
}

LINKEDLIST_ErrorType LINKEDLIST_DeleteElement(linkedlist* LINKEDLIST, LINKEDLIST_node** head, uint8 index){
	if(LINKEDLIST_Check(LINKEDLIST, head) == 0)
		return LINKEDLIST_Notfound;
	LINKEDLIST_node* current = (LINKEDLIST_node*)*head;
	LINKEDLIST_node* previous = NULL;
	uint8 POS = 0;
	if(current == NULL){
		return LINKEDLIST_Empty;
	}
	else if(index > LINKEDLIST_Size(LINKEDLIST, head)){
		return LINKEDLIST_ElementNotFound;
	}
	else if(index == 0){
		*head = current -> PtrToNextNode;
		LINKEDLIST_FREE(current);
		return LINKEDLIST_NoError;
	}
	else{
		while(POS < index){
			previous = current;
			current = current -> PtrToNextNode;
			POS++;
		}
		previous -> PtrToNextNode = current -> PtrToNextNode;
		LINKEDLIST_FREE(current);
		return LINKEDLIST_NoError;
	}
}

LINKEDLIST_ErrorType LINKEDLIST_DeleteHead(linkedlist* LINKEDLIST, LINKEDLIST_node** head){
	if(LINKEDLIST_Check(LINKEDLIST, head) == 0)
		return LINKEDLIST_Notfound;
	if((*head) == NULL){
		return LINKEDLIST_Empty;
	}
	else{
		LINKEDLIST_DeleteElement(LINKEDLIST, head, 0);
		return LINKEDLIST_NoError;
	}
}

LINKEDLIST_ErrorType LINKEDLIST_DeleteTail(linkedlist* LINKEDLIST, LINKEDLIST_node** head){
	if(LINKEDLIST_Check(LINKEDLIST, head) == 0)
		return LINKEDLIST_Notfound;
	LINKEDLIST_node* current = (LINKEDLIST_node*)*head;
	uint8 Index = 0;
	if((*head) == NULL){
		return LINKEDLIST_Empty;
	}
	else{
		while((current-> PtrToNextNode) != NULL){
			current = current -> PtrToNextNode;
			Index++;
		}
		LINKEDLIST_DeleteElement(LINKEDLIST, head, Index);
		return LINKEDLIST_NoError;
	}
}

LINKEDLIST_ErrorType LINKEDLIST_UpdateElement(linkedlist* LINKEDLIST, LINKEDLIST_DataSize data, LINKEDLIST_node** head, uint8 index){
	if(LINKEDLIST_Check(LINKEDLIST, head) == 0)
		return LINKEDLIST_Notfound;
	LINKEDLIST_node* current = (LINKEDLIST_node*)*head;
	uint8 POS = 0;
	if(current == NULL){
		return LINKEDLIST_Empty;
	}
	else if(index > LINKEDLIST_Size(LINKEDLIST, head)){
		return LINKEDLIST_ElementNotFound;
	}
	else if(index == 0){
		current -> Data = data;
		return LINKEDLIST_NoError;
	}
	else{
		while(POS < index){
			current = current -> PtrToNextNode;
			POS++;
		}
		current -> Data = data;
		return LINKEDLIST_NoError;
	}
}

LINKEDLIST_ErrorType LINKEDLIST_Switch(linkedlist* LINKEDLIST, LINKEDLIST_node** head, uint8 Index1, uint8 Index2){
	if(LINKEDLIST_Check(LINKEDLIST, head) == 0)
		return LINKEDLIST_Notfound;
	LINKEDLIST_node temp;
	LINKEDLIST_node* current1 = (LINKEDLIST_node*)*head;
	LINKEDLIST_node* current2 = (LINKEDLIST_node*)*head;
	uint8 POS = 0;
	uint8 count1 = 0;
	uint8 count2 = 0;
	if(current1 == NULL){
		return LINKEDLIST_Empty;
	}
	else if(Index1 > LINKEDLIST_Size(LINKEDLIST, head)){
		return LINKEDLIST_ElementNotFound;
	}
	else if(Index2 > LINKEDLIST_Size(LINKEDLIST, head)){
		return LINKEDLIST_ElementNotFound;
	}
	else{
		if(Index1 > Index2)
		{
			count1 = Index2;
			count2 = Index1;
		}
		else if(Index1 < Index2)
		{
			count1 = Index1;
			count2 = Index2;
		}
		else
		{
			return LINKEDLIST_NoError;
		}
		while(POS < count1){
			current1 = current1 -> PtrToNextNode;
			current2 = current2 -> PtrToNextNode;
			POS++;
		}
		while(POS < count2){
			current2 = current2 -> PtrToNextNode;
			POS++;
		}
		temp.Data = current1 -> Data;
		current1 -> Data = current2 -> Data;
		current2 -> Data = temp.Data;
		return LINKEDLIST_NoError;
	}
}

LINKEDLIST_DataSize LINKEDLIST_Get(linkedlist* LINKEDLIST, LINKEDLIST_node** head, uint8 index){
	if(LINKEDLIST_Check(LINKEDLIST, head) == 0)
		return LINKEDLIST_Notfound;
	LINKEDLIST_node* current = (LINKEDLIST_node*)*head;
	uint8 POS = 0;
	if(current == NULL){
		return -1;
	}
	else if(index > LINKEDLIST_Size(LINKEDLIST, head)){
		return -1;
	}
	else{
		while(POS < index){
			current = current -> PtrToNextNode;
			POS++;
		}
		return current -> Data;
	}
}

LINKEDLIST_DataSize LINKEDLIST_GetHead(linkedlist* LINKEDLIST, LINKEDLIST_node** head){
	if(LINKEDLIST_Check(LINKEDLIST, head) == 0)
		return LINKEDLIST_Notfound;
	if((*head) == NULL){
		return -1;
	}
	else{
		return LINKEDLIST_Get(LINKEDLIST, head, 0);
	}
}

LINKEDLIST_DataSize LINKEDLIST_GetTail(linkedlist* LINKEDLIST, LINKEDLIST_node** head){
	if(LINKEDLIST_Check(LINKEDLIST, head) == 0)
		return LINKEDLIST_Notfound;
	LINKEDLIST_node* current = (LINKEDLIST_node*)*head;
	uint8 Index = 0;
	if((*head) == NULL){
		return -1;
	}
	else{
		while((current-> PtrToNextNode) != NULL){
			current = current -> PtrToNextNode;
			Index++;
		}
		return LINKEDLIST_Get(LINKEDLIST, head, Index);
	}
}

#if(LINKEDLIST_PRINT == LINKEDLIST_PRINTING)
LINKEDLIST_ErrorType LINKEDLIST_Print(linkedlist* LINKEDLIST, LINKEDLIST_node** head){
	if(LINKEDLIST_Check(LINKEDLIST, head) == 0)
		return LINKEDLIST_Notfound;
	LINKEDLIST_node* current = (LINKEDLIST_node*)*head;
	if(current == NULL){
		return LINKEDLIST_Empty;
	}
	printf("head => ");
	while(current != NULL){
		printf("%d => ", current -> Data);
		current = current -> PtrToNextNode;
	}
	printf("NULL");
	return LINKEDLIST_NoError;
}
#endif



