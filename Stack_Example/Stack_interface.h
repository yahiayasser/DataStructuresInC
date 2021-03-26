/*
 * Stack_interface.h
 *
 *  Created on: 3 Jan 2020
 *      Author: Yahia
 */

#ifndef STACK_INTERFACE_H_
#define STACK_INTERFACE_H_

#include "Stack_config.h"

struct StackNode{
	struct StackNode* PtrToNextNode;
	Stack_DataSize Data;
};

typedef struct StackNode Stack_node;
typedef Stack_node Stack[Stack_Max_Elements];

typedef Stack_node*		Stack_Head;

typedef enum{
	Stack_Notfound,
	Stack_Full,
	Stack_Empty,
	Stack_ElementNotFound,
	Stack_NoError
}ErrorType;

#ifndef Stack_PRINTING
#define Stack_PRINTING		1
#endif

#ifndef Stack_NOT_PRINTING
#define Stack_NOT_PRINTING	0
#endif

ErrorType Stack_Init(Stack* STACK, Stack_node** head);
uint8 Stack_Size(Stack* STACK, Stack_node** head);
ErrorType Stack_UpdateElement(Stack* STACK, Stack_DataSize data, Stack_node** head, uint8 index);
ErrorType Stack_Switch(Stack* STACK, Stack_node** head, uint8 Index1, uint8 Index2);
ErrorType Stack_Push(Stack* STACK, Stack_DataSize data, Stack_node** head);
Stack_DataSize Stack_Pop(Stack* STACK, Stack_node** head);
#if(Stack_PRINT ==  Stack_PRINTING)
ErrorType Stack_Print(Stack* STACK, Stack_node** head);
#endif

#endif /* STACK_INTERFACE_H_ */
