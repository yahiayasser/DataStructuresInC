/*
 * Queue_interface.h
 *
 *  Created on: 3 Jan 2020
 *      Author: Yahia
 */

#ifndef QUEUE_INTERFACE_H_
#define QUEUE_INTERFACE_H_

#include "Queue_config.h"

struct QueueNode{
	struct QueueNode* PtrToNextNode;
	Queue_DataSize Data;
};

typedef struct QueueNode Queue_node;
typedef Queue_node Queue[Queue_Max_Elements];

typedef Queue_node*		Queue_Head;

typedef enum{
	Queue_Notfound,
	Queue_Full,
	Queue_Empty,
	Queue_ElementNotFound,
	Queue_NoError
}Queue_ErrorType;

#ifndef Queue_PRINTING
#define Queue_PRINTING		1
#endif

#ifndef Queue_NOT_PRINTING
#define Queue_NOT_PRINTING	0
#endif

Queue_ErrorType Queue_Init(Queue* QUEUE, Queue_node** head);
uint8 Queue_Size(Queue* QUEUE, Queue_node** head);
Queue_ErrorType Queue_UpdateElement(Queue* QUEUE, Queue_DataSize data, Queue_node** head, uint8 index);
Queue_ErrorType Queue_Switch(Queue* QUEUE, Queue_node** head, uint8 Index1, uint8 Index2);
Queue_ErrorType Queue_Enqueue(Queue* QUEUE, Queue_DataSize data, Queue_node** head);
Queue_DataSize Queue_Dequeue(Queue* QUEUE, Queue_node** head);
#if(Queue_PRINT ==  Queue_PRINTING)
Queue_ErrorType Queue_Print(Queue* QUEUE, Queue_node** head);
#endif

#endif /* QUEUE_INTERFACE_H_ */
