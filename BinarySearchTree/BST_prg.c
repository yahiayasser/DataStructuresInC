/*
 * BST_prg.c
 *
 *  Created on: 4 Jan 2020
 *      Author: Yahia
 */

#include "std_types.h"
#include "common_macros.h"

#include "BST_interface.h"
#include "BST_private.h"

#if(BST_PRINT == BST_PRINTING)
#include <stdio.h>
#include <stdlib.h>
#endif

BST yahia;

void BST_Init(BST* BST_ptr){
	BST_node* Ptr_Elemnets = (BST_node*)&(BST_ptr -> Tree);
	uint8 count = 0;
	while(count != BST_Max_Elements){
		Ptr_Elemnets[count].Data = 0;
		Ptr_Elemnets[count].PtrToLeftNode = NULL;
		Ptr_Elemnets[count].PtrToRightNode = NULL;
		Ptr_Elemnets[count].State = BST_NODE_EMPTY;
		count++;
	}
	BST_ptr -> Root = NULL;
}

BST_ErrorType BST_Insert(BST* BST_ptr, BST_DataSize data){
	BST_node* Ptr_Elemnets = (BST_node*)&(BST_ptr -> Tree);
	BST_node* current = BST_ptr -> Root;
	uint8 count = 0;
	uint8 index = 0;
	while((count < BST_Max_Elements) && ((Ptr_Elemnets[count].State) == BST_NODE_OCCUPIED)){
		count++;
	}
	if(count == BST_Max_Elements){
		return BST_Full;
	}
	else{
		Ptr_Elemnets[count].State = BST_NODE_OCCUPIED;
		Ptr_Elemnets[count].Data = data;
		Ptr_Elemnets[count].leaf_state = BST_NODE_LEAF;
		if(current == NULL){
			Ptr_Elemnets[count].Index = index;
			BST_ptr -> Root = &Ptr_Elemnets[count];
			return BST_NoError;
		}
		else{
			while(!((((current -> PtrToLeftNode) == NULL) && (data <= (current -> Data))) || ((((current -> PtrToRightNode) == NULL) && (data > (current -> Data)))))){
				if(data <= (current -> Data)){
					current = current -> PtrToLeftNode;
					index = (index << 2) + 1;
				}
				else{
					current = current -> PtrToRightNode;
					index = (index << 2) + 2;
				}
			}
			if(data <= (current -> Data)){
				current -> PtrToLeftNode = &Ptr_Elemnets[count];
				current -> leaf_state += BST_NODE_LEFT_CHILD;
				current -> Index = (index << 2) + 1;
				return BST_NoError;
			}
			else{
				current -> PtrToRightNode = &Ptr_Elemnets[count];
				current -> leaf_state += BST_NODE_RIGHT_CHILD;
				current -> Index = (index << 2) + 2;
				return BST_NoError;
			}
		}
	}
}

/*BST_ErrorType BST_Find(BST* BST_ptr, BST_DataSize data){
	BST_node* current = BST_ptr -> Root;
	if(current == NULL){
		return BST_Empty;
	}
	while(!((((current -> PtrToLeftNode) == NULL) && (data <= (current -> Data))) || ((((current -> PtrToRightNode) == NULL) && (data > (current -> Data)))))){
		if(data <= (current -> Data)){
			if(((current -> leaf_state) == BST_NODE_LEAF) || ((current -> leaf_state) == BST_NODE_RIGHT_CHILD)){
				return BST_Full;
			}
			else{
				current = current -> PtrToLeftNode;
			}
		}
		else{
			if(((current -> leaf_state) == BST_NODE_LEAF) || ((current -> leaf_state) == BST_NODE_LEFT_CHILD)){
				return BST_Full;
			}
			else{
				current = current -> PtrToRightNode;
			}
		}
	}
}*/

int main (void){
	BST_Init(&yahia);
	BST_Insert(&yahia, 10);
	BST_Insert(&yahia, 12);
	BST_Insert(&yahia, 7);
	BST_Insert(&yahia, 8);
	BST_Insert(&yahia, 10);
}
