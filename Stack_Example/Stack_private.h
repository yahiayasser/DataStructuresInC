/*
 * Stack_private.h
 *
 *  Created on: 3 Jan 2020
 *      Author: Yahia
 */

#ifndef STACK_PRIVATE_H_
#define STACK_PRIVATE_H_

#ifndef NULL
#define NULL	(void *)0
#endif

#define Stack_MAXADD	(void *)0xFFFFFFFF

static uint8 Stack_Check(Stack* STACK, Stack_node** head);
static ErrorType Stack_InsertAtFirst(Stack* STACK, Stack_DataSize data, Stack_node** head);
static void Stack_FREE(Stack_node* PtrToNode);
static ErrorType Stack_DeleteHead(Stack* STACK, Stack_node** head);
static ErrorType Stack_DeleteElement(Stack* STACK, Stack_node** head, uint8 index);
static Stack_DataSize Stack_Get(Stack* STACK, Stack_node** head, uint8 index);
static Stack_DataSize Stack_GetHead(Stack* STACK, Stack_node** head);

#endif /* STACK_PRIVATE_H_ */
