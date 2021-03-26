/*
 * Queue_private.h
 *
 *  Created on: 3 Jan 2020
 *      Author: Yahia
 */

#ifndef QUEUE_PRIVATE_H_
#define QUEUE_PRIVATE_H_

#ifndef NULL
#define NULL	(void *)0
#endif

#define Queue_MAXADD	(void *)0xFFFFFFFF

static uint8 Queue_Check(Queue* QUEUE, Queue_node** head);
static ErrorType Queue_InsertAtLast(Queue* QUEUE, Queue_DataSize data, Queue_node** head);
static void Queue_FREE(Queue_node* PtrToNode);
static ErrorType Queue_DeleteHead(Queue* QUEUE, Queue_node** head);
static ErrorType Queue_DeleteElement(Queue* QUEUE, Queue_node** head, uint8 index);
static Queue_DataSize Queue_Get(Queue* QUEUE, Queue_node** head, uint8 index);
static Queue_DataSize Queue_GetHead(Queue* QUEUE, Queue_node** head);

#endif /* QUEUE_PRIVATE_H_ */
