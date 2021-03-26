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


#include "Queue_interface.h"

Queue yahia;
Queue_Head Head;

int main(void){
	Queue_Init(&yahia, &Head);
	Queue_Enqueue(&yahia,10, &Head);
	Queue_Enqueue(&yahia,20, &Head);
	Queue_Enqueue(&yahia,30, &Head);
	Queue_Enqueue(&yahia,40, &Head);
	Queue_Dequeue(&yahia, &Head);
	Queue_Dequeue(&yahia, &Head);
	Queue_Enqueue(&yahia,60, &Head);
	Queue_Print(&yahia, &Head);
	printf("The last popped value is %d", Queue_Dequeue(&yahia, &Head));
}
