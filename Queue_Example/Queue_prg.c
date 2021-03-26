/*
 * Queue_prg.c
 *
 *  Created on: 3 Jan 2020
 *      Author: Yahia
 */

#include "std_types.h"
#include "common_macros.h"

#include "Queue_interface.h"
#include "Queue_private.h"

#if(Queue_PRINT == Queue_PRINTING)
#include <stdio.h>
#include <stdlib.h>
#endif

static uint8 Queue_Check(Queue* QUEUE, Queue_node** head){
	Queue_node* Ptr_Elements = (Queue_node*)QUEUE;
	uint8 count = 0;
	if(*head == NULL){
		while(count != Queue_Max_Elements){
			if(Ptr_Elements[count].Data != 0)
				return 0;
			count++;
		}
		return 1;
	}
	else{
		while(count != Queue_Max_Elements){
			if(*head == (&Ptr_Elements[count])){
				return 1;
			}
			count++;
		}
		return 0;
	}
}

static ErrorType Queue_InsertAtLast(Queue* QUEUE, Queue_DataSize data, Queue_node** head){
	if(Queue_Check(QUEUE, head) == 0)
		return Queue_Notfound;
	Queue_node* Ptr_Elements = (Queue_node*)QUEUE;
	Queue_node* current = (Queue_node*)*head;
	uint8 count = 0;

	while((count != Queue_Max_Elements) && (Ptr_Elements[count].PtrToNextNode != Queue_MAXADD)){
		count++;
	}

	if(count == Queue_Max_Elements){
		return Queue_Full;
	}
	else{
		Ptr_Elements[count].Data = data;
		Ptr_Elements[count].PtrToNextNode = NULL;
		if(current == NULL){
			(*head) = &Ptr_Elements[count];
			return Queue_NoError;
		}
		else{
			while((current -> PtrToNextNode) != NULL){
				current = current -> PtrToNextNode;
			}
			current -> PtrToNextNode = &Ptr_Elements[count];
			return Queue_NoError;
		}
	}
}

static void Queue_FREE(Queue_node* PtrToNode){
	PtrToNode -> Data = 0;
	PtrToNode -> PtrToNextNode = Queue_MAXADD;
}

static ErrorType Queue_DeleteElement(Queue* QUEUE, Queue_node** head, uint8 index){
	Queue_node* current = (Queue_node*)*head;
	Queue_node* previous = NULL;
	uint8 POS = 0;
	if(current == NULL){
		return Queue_Empty;
	}
	else if(index > Queue_Size(QUEUE, head)){
		return Queue_ElementNotFound;
	}
	else if(index == 0){
		*head = current -> PtrToNextNode;
		Queue_FREE(current);
		return Queue_NoError;
	}
	else{
		while(POS < index){
			previous = current;
			current = current -> PtrToNextNode;
			POS++;
		}
		previous -> PtrToNextNode = current -> PtrToNextNode;
		Queue_FREE(current);
		return Queue_NoError;
	}
}

static ErrorType Queue_DeleteHead(Queue* QUEUE, Queue_node** head){
	if((*head) == NULL){
		return Queue_Empty;
	}
	else{
		Queue_DeleteElement(QUEUE, head, 0);
		return Queue_NoError;
	}
}

static Queue_DataSize Queue_Get(Queue* QUEUE, Queue_node** head, uint8 index){
	Queue_node* current = (Queue_node*)*head;
	uint8 POS = 0;
	if(current == NULL){
		return -1;
	}
	else if(index > Queue_Size(QUEUE, head)){
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

static Queue_DataSize Queue_GetHead(Queue* QUEUE, Queue_node** head){
	if((*head) == NULL){
		return -1;
	}
	else{
		return Queue_Get(QUEUE, head, 0);
	}
}

ErrorType Queue_Init(Queue* QUEUE, Queue_node** head){
	Queue_node* Ptr_Elements = (Queue_node*)QUEUE;
	uint8 count = 0;
	while(count != Queue_Max_Elements){
		Ptr_Elements[count].Data = 0;
		Ptr_Elements[count].PtrToNextNode = Queue_MAXADD;
		count++;
	}
	(*head) = NULL;

	return Queue_NoError;
}

ErrorType Queue_Switch(Queue* QUEUE, Queue_node** head, uint8 Index1, uint8 Index2){
	if(Queue_Check(QUEUE, head) == 0)
		return Queue_Notfound;
	Queue_node temp;
	Queue_node* current1 = (Queue_node*)*head;
	Queue_node* current2 = (Queue_node*)*head;
	uint8 POS = 0;
	uint8 count1 = 0;
	uint8 count2 = 0;
	if(current1 == NULL){
		return Queue_Empty;
	}
	else if(Index1 > Queue_Size(QUEUE, head)){
		return Queue_ElementNotFound;
	}
	else if(Index2 > Queue_Size(QUEUE, head)){
		return Queue_ElementNotFound;
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
			return Queue_NoError;
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
		return Queue_NoError;
	}
}

ErrorType Queue_UpdateElement(Queue* QUEUE, Queue_DataSize data, Queue_node** head, uint8 index){
	if(Queue_Check(QUEUE, head) == 0)
		return Queue_Notfound;
	Queue_node* current = (Queue_node*)*head;
	uint8 POS = 0;
	if(current == NULL){
		return Queue_Empty;
	}
	else if(index > Queue_Size(QUEUE, head)){
		return Queue_ElementNotFound;
	}
	else if(index == 0){
		current -> Data = data;
		return Queue_NoError;
	}
	else{
		while(POS < index){
			current = current -> PtrToNextNode;
			POS++;
		}
		current -> Data = data;
		return Queue_NoError;
	}
}

uint8 Queue_Size(Queue* QUEUE, Queue_node** head){
	if(Queue_Check(QUEUE, head) == 0)
		return Queue_Notfound;
	Queue_node* current = (Queue_node*)*head;
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

ErrorType Queue_Enqueue(Queue* QUEUE, Queue_DataSize data, Queue_node** head){
	if(Queue_Check(QUEUE, head) == 0)
		return Queue_Notfound;
	if(Queue_InsertAtLast(QUEUE, data, head) == Queue_Full)
		return Queue_Full;
	else
		return Queue_NoError;
}

Queue_DataSize Queue_Dequeue(Queue* QUEUE, Queue_node** head){
	if(Queue_Check(QUEUE, head) == 0)
		return Queue_Notfound;
	uint8 result = -1;
	result = Queue_GetHead(QUEUE, head);
	if(result == -1)
		return result;
	else{
		Queue_DeleteHead(QUEUE, head);
		return result;
	}
}

#if(Queue_PRINT == Queue_PRINTING)
ErrorType Queue_Print(Queue* QUEUE, Queue_node** head){
	Queue_node* current = (Queue_node*)*head;
	if(current == NULL){
		return Queue_Empty;
	}
	printf("\nQueue top");
	while(current != NULL){
		printf("\n%d", current -> Data);
		current = current -> PtrToNextNode;
	}
	printf("\nQueue bottom\n");
	return Queue_NoError;
}
#endif
