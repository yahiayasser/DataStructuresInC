/*
 * Stack_prg.c
 *
 *  Created on: 3 Jan 2020
 *      Author: Yahia
 */

#include "std_types.h"
#include "common_macros.h"

#include "Stack_interface.h"
#include "Stack_private.h"

#if(Stack_PRINT == Stack_PRINTING)
#include <stdio.h>
#include <stdlib.h>
#endif

static uint8 Stack_Check(Stack* STACK, Stack_node** head){
	Stack_node* Ptr_Elements = (Stack_node*)STACK;
	uint8 count = 0;
	if(*head == NULL){
		while(count != Stack_Max_Elements){
			if(Ptr_Elements[count].Data != 0)
				return 0;
			count++;
		}
		return 1;
	}
	else{
		while(count != Stack_Max_Elements){
			if(*head == (&Ptr_Elements[count])){
				return 1;
			}
			count++;
		}
		return 0;
	}
}

static ErrorType Stack_InsertAtFirst(Stack* STACK, Stack_DataSize data, Stack_node** head){
	Stack_node* Ptr_Elements = (Stack_node*)STACK;
	uint8 count = 0;
	while((count != Stack_Max_Elements) && (Ptr_Elements[count].PtrToNextNode != Stack_MAXADD)){
		count++;
	}

	if(count == Stack_Max_Elements){
		return Stack_Full;
	}
	else{
		Ptr_Elements[count].Data = data;
		Ptr_Elements[count].PtrToNextNode = (*head);
		(*head) = &Ptr_Elements[count];
	}

	return Stack_NoError;
}

static void Stack_FREE(Stack_node* PtrToNode){
	PtrToNode -> Data = 0;
	PtrToNode -> PtrToNextNode = Stack_MAXADD;
}

static ErrorType Stack_DeleteElement(Stack* STACK, Stack_node** head, uint8 index){
	Stack_node* current = (Stack_node*)*head;
	Stack_node* previous = NULL;
	uint8 POS = 0;
	if(current == NULL){
		return Stack_Empty;
	}
	else if(index > Stack_Size(STACK, head)){
		return Stack_ElementNotFound;
	}
	else if(index == 0){
		*head = current -> PtrToNextNode;
		Stack_FREE(current);
		return Stack_NoError;
	}
	else{
		while(POS < index){
			previous = current;
			current = current -> PtrToNextNode;
			POS++;
		}
		previous -> PtrToNextNode = current -> PtrToNextNode;
		Stack_FREE(current);
		return Stack_NoError;
	}
}

static ErrorType Stack_DeleteHead(Stack* STACK, Stack_node** head){
	if((*head) == NULL){
		return Stack_Empty;
	}
	else{
		Stack_DeleteElement(STACK, head, 0);
		return Stack_NoError;
	}
}

static Stack_DataSize Stack_Get(Stack* STACK, Stack_node** head, uint8 index){
	Stack_node* current = (Stack_node*)*head;
	uint8 POS = 0;
	if(current == NULL){
		return -1;
	}
	else if(index > Stack_Size(STACK, head)){
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

static Stack_DataSize Stack_GetHead(Stack* STACK, Stack_node** head){
	if((*head) == NULL){
		return -1;
	}
	else{
		return Stack_Get(STACK, head, 0);
	}
}

ErrorType Stack_Init(Stack* STACK, Stack_node** head){
	Stack_node* Ptr_Elements = (Stack_node*)STACK;
	uint8 count = 0;
	while(count != Stack_Max_Elements){
		Ptr_Elements[count].Data = 0;
		Ptr_Elements[count].PtrToNextNode = Stack_MAXADD;
		count++;
	}
	(*head) = NULL;

	return Stack_NoError;
}

ErrorType Stack_Switch(Stack* STACK, Stack_node** head, uint8 Index1, uint8 Index2){
	if(Stack_Check(STACK, head) == 0)
		return Stack_Notfound;
	Stack_node temp;
	Stack_node* current1 = (Stack_node*)*head;
	Stack_node* current2 = (Stack_node*)*head;
	uint8 POS = 0;
	uint8 count1 = 0;
	uint8 count2 = 0;
	if(current1 == NULL){
		return Stack_Empty;
	}
	else if(Index1 > Stack_Size(STACK, head)){
		return Stack_ElementNotFound;
	}
	else if(Index2 > Stack_Size(STACK, head)){
		return Stack_ElementNotFound;
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
			return Stack_NoError;
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
		return Stack_NoError;
	}
}

ErrorType Stack_UpdateElement(Stack* STACK, Stack_DataSize data, Stack_node** head, uint8 index){
	if(Stack_Check(STACK, head) == 0)
		return Stack_Notfound;
	Stack_node* current = (Stack_node*)*head;
	uint8 POS = 0;
	if(current == NULL){
		return Stack_Empty;
	}
	else if(index > Stack_Size(STACK, head)){
		return Stack_ElementNotFound;
	}
	else if(index == 0){
		current -> Data = data;
		return Stack_NoError;
	}
	else{
		while(POS < index){
			current = current -> PtrToNextNode;
			POS++;
		}
		current -> Data = data;
		return Stack_NoError;
	}
}

uint8 Stack_Size(Stack* STACK, Stack_node** head){
	if(Stack_Check(STACK, head) == 0)
		return Stack_Notfound;
	Stack_node* current = (Stack_node*)*head;
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

ErrorType Stack_Push(Stack* STACK, Stack_DataSize data, Stack_node** head){
	if(Stack_Check(STACK, head) == 0)
		return Stack_Notfound;
	if(Stack_InsertAtFirst(STACK, data, head) == Stack_Full)
		return Stack_Full;
	else
		return Stack_NoError;
}

Stack_DataSize Stack_Pop(Stack* STACK, Stack_node** head){
	if(Stack_Check(STACK, head) == 0)
		return Stack_Notfound;
	uint8 result = -1;
	result = Stack_GetHead(STACK, head);
	if(result == -1)
		return result;
	else{
		Stack_DeleteHead(STACK, head);
		return result;
	}
}

#if(Stack_PRINT == Stack_PRINTING)
ErrorType Stack_Print(Stack* STACK, Stack_node** head){
	Stack_node* current = (Stack_node*)*head;
	if(current == NULL){
		return Stack_Empty;
	}
	printf("\nStack top");
	while(current != NULL){
		printf("\n%d", current -> Data);
		current = current -> PtrToNextNode;
	}
	printf("\nStack bottom\n");
	return Stack_NoError;
}
#endif
