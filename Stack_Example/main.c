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


#include "Stack_interface.h"

Stack yahia;
Stack_Head Head;

int main(void){
	Stack_Init(&yahia, &Head);
	Stack_Push(&yahia,10, &Head);
	Stack_Push(&yahia,20, &Head);
	Stack_Push(&yahia,30, &Head);
	Stack_Push(&yahia,40, &Head);
	Stack_Pop(&yahia, &Head);
	Stack_Pop(&yahia, &Head);
	Stack_Push(&yahia,60, &Head);
	Stack_Print(&yahia, &Head);
	printf("The last popped value is %d", Stack_Pop(&yahia, &Head));
}
