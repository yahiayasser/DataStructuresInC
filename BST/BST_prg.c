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
//static uint8 Level_Flag = 0;
//static uint8 Left_Level = 0;
//static uint8 Right_Level = 0;

void BST_Init(BST* BST_ptr){
	BST_node* Ptr_Elemnets = (BST_node*)&(BST_ptr -> Tree);
	uint8 count = 0;
	while(count != BST_Max_Elements){
		Ptr_Elemnets[count].Data = 0;
		Ptr_Elemnets[count].PtrToLeftNode = NULL;
		Ptr_Elemnets[count].PtrToRightNode = NULL;
		Ptr_Elemnets[count].State = BST_NODE_EMPTY;
		Ptr_Elemnets[count].Index = MAX_Index;
		Ptr_Elemnets[count].leaf_state = BST_NODE_NULL;
		count++;
	}
	BST_ptr -> Root = NULL;
}

BST_node* BST_Insert(BST* BST_ptr, BST_DataSize data){

	BST_node* Ptr_Elemnets = (BST_node*)&(BST_ptr -> Tree);
	BST_node* current = BST_ptr -> Root;
	uint8 count = 0;
	uint8 index = 0;
	while((count < BST_Max_Elements) && ((Ptr_Elemnets[count].State) == BST_NODE_OCCUPIED)){
		count++;
	}
	if(count == BST_Max_Elements){
		return NULL;
	}
	else{
		Ptr_Elemnets[count].State = BST_NODE_OCCUPIED;
		Ptr_Elemnets[count].Data = data;
		Ptr_Elemnets[count].leaf_state = BST_NODE_LEAF;
		if(current == NULL){
			Ptr_Elemnets[count].Index = index;
			BST_ptr -> Root = &Ptr_Elemnets[count];
			return (BST_ptr -> Root);
		}
		else{
			while(!((((current -> PtrToLeftNode) == NULL) && (data <= (current -> Data))) || ((((current -> PtrToRightNode) == NULL) && (data > (current -> Data)))))){
				if(data <= (current -> Data)){
					current = current -> PtrToLeftNode;
					index = (index << 1) + 1;
				}
				else{
					current = current -> PtrToRightNode;
					index = (index << 1) + 2;
				}
			}
			if(data <= (current -> Data)){
				current -> PtrToLeftNode = &Ptr_Elemnets[count];
				current -> leaf_state += BST_NODE_LEFT_CHILD;
				Ptr_Elemnets[count].Index = (index << 1) + 1;
				return current -> PtrToLeftNode;
			}
			else{
				current -> PtrToRightNode = &Ptr_Elemnets[count];
				current -> leaf_state += BST_NODE_RIGHT_CHILD;
				Ptr_Elemnets[count].Index = (index << 1) + 2;
				return current -> PtrToRightNode;
			}
		}
	}
}

uint32 BST_FindIndex(BST* BST_ptr, BST_DataSize data){
	BST_node* current = BST_ptr -> Root;
	uint8 index = 0;
	if(current == NULL){
		return -1;
	}
	while(!((((current -> PtrToLeftNode) == NULL) && (data < (current -> Data))) || ((((current -> PtrToRightNode) == NULL) && (data > (current -> Data)))))){
		if(data == (current -> Data)){
			index = current -> Index;
			return index;
		}
		if(data < (current -> Data)){
			if(((current -> leaf_state) == BST_NODE_LEAF) || ((current -> leaf_state) == BST_NODE_RIGHT_CHILD)){
				return -1;
			}
			else{
				current = current -> PtrToLeftNode;
			}
		}
		else{
			if(((current -> leaf_state) == BST_NODE_LEAF) || ((current -> leaf_state) == BST_NODE_LEFT_CHILD)){
				return -1;
			}
			else{
				current = current -> PtrToRightNode;
			}
		}
	}
	return -1;
}

BST_DataSize* BST_FindElement(BST* BST_ptr, BST_DataSize data){
	BST_node* current = BST_ptr -> Root;
	BST_DataSize* data_ptr = NULL;
	if(current == NULL){
		return data_ptr;
	}
	while(!((((current -> PtrToLeftNode) == NULL) && (data < (current -> Data))) || ((((current -> PtrToRightNode) == NULL) && (data > (current -> Data)))))){
		if(data == (current -> Data)){
			data_ptr = &(current -> Data);
			return data_ptr;
		}
		if(data < (current -> Data)){
			if(((current -> leaf_state) == BST_NODE_LEAF) || ((current -> leaf_state) == BST_NODE_RIGHT_CHILD)){
				return data_ptr;
			}
			else{
				current = current -> PtrToLeftNode;
			}
		}
		else{
			if(((current -> leaf_state) == BST_NODE_LEAF) || ((current -> leaf_state) == BST_NODE_LEFT_CHILD)){
				return data_ptr;
			}
			else{
				current = current -> PtrToRightNode;
			}
		}
	}
	return data_ptr;
}

static void BST_Free(BST_node* PtrToNode){
	PtrToNode -> Data = 0;
	PtrToNode -> PtrToLeftNode = NULL;
	PtrToNode -> PtrToRightNode = NULL;
	PtrToNode -> State = BST_NODE_EMPTY;
	PtrToNode -> Index = MAX_Index;
	PtrToNode -> leaf_state = BST_NODE_NULL;
}

static void BST_UpdateIndex(BST_node* current, BST_node* prev, uint8 direction){
	if(current == NULL){
		return;
	}
	if(prev == NULL){
		current -> Index = 0;
	}

	else{
		if(direction == BST_LEFT)
			current -> Index = ((prev -> Index) << 1) + 1;
		else
			current -> Index = ((prev -> Index) << 1) + 2;
	}
	if(((current -> PtrToLeftNode) == NULL) && ((current -> PtrToRightNode) == NULL)){
		return;
	}
	BST_UpdateIndex(current -> PtrToLeftNode, current, BST_LEFT);
	BST_UpdateIndex(current -> PtrToRightNode, current, BST_RIGHT);
}

static BST_node* BST_Find_Parent(BST_node* root, uint8 index){
	index += 1;
	index = index >> 1;
	uint8 temp = index;
	uint8 count = 0;
	uint8 sum = 0;
	while(temp != 1){
		sum = (temp % 2) + (sum << count);
		count++;
		temp = temp >> 1;
	}
	while(count != 0){
		if(sum & 1){
			root = root -> PtrToRightNode;
		}
		else{
			root = root -> PtrToLeftNode;
		}
		sum = sum >> 1;
		count--;
	}
	return root;
}

BST_ErrorType BST_Delete(BST* BST_ptr, BST_DataSize data){
	BST_node* current = BST_ptr -> Root;
	BST_node* prev = BST_ptr -> Root;
	uint8 index = 0;
	uint8 direction_flag = 0;
	BST_node* temp_add = prev;
	BST_NODE_LeafOrNot temp_child;
	BST_DataSize temp;
	if(current == NULL){
		return BST_Empty;
	}
	while(!((((current -> PtrToLeftNode) == NULL) && (data < (current -> Data))) || ((((current -> PtrToRightNode) == NULL) && (data > (current -> Data)))))){
		if(data == (current -> Data)){
			if(((current -> PtrToLeftNode) == NULL) && ((current -> PtrToRightNode) == NULL)){
				if(current == prev){
					BST_ptr -> Root = NULL;
					BST_Free(current);
					return BST_NoError;
				}
				if((current -> Data) <= (prev -> Data)){
					prev -> PtrToLeftNode = NULL;
					prev -> leaf_state -= BST_NODE_LEFT_CHILD;
				}
				else{
					prev -> PtrToRightNode = NULL;
					prev -> leaf_state -= BST_NODE_RIGHT_CHILD;
				}
				BST_Free(current);
				return BST_NoError;
			}
			else if(((current -> PtrToLeftNode) == NULL)){
				if(current == prev){
					BST_ptr -> Root = current -> PtrToRightNode;
					BST_Free(current);
					return BST_NoError;
				}
				if((current -> Data) <= (prev -> Data)){
					prev -> PtrToLeftNode = current -> PtrToRightNode;
				}
				else{
					prev -> PtrToRightNode = current -> PtrToRightNode;
				}
				BST_Free(current);
				BST_UpdateIndex(BST_ptr -> Root, NULL, BST_LEFT);
				return BST_NoError;
			}
			else if(((current -> PtrToRightNode) == NULL)){
				if(current == prev){
					BST_ptr -> Root = current -> PtrToLeftNode;
					BST_Free(current);
					return BST_NoError;
				}
				if((current -> Data) <= (prev -> Data)){
					prev -> PtrToLeftNode = current -> PtrToLeftNode;
				}
				else{
					prev -> PtrToRightNode = current -> PtrToLeftNode;
				}
				BST_Free(current);
				BST_UpdateIndex(BST_ptr -> Root, NULL, BST_LEFT);
				return BST_NoError;
			}
			else{
				prev = current;
				current = current -> PtrToRightNode;
				while((current -> PtrToLeftNode) != NULL){
					current = current -> PtrToLeftNode;
					direction_flag = 1;
				}
				temp_add = current -> PtrToRightNode;
				temp = current -> Data;
				current -> Data = prev -> Data;
				prev -> Data = temp;
				//prev -> leaf_state = current -> leaf_state;
				temp_child = current -> leaf_state;
				index = current -> Index;
				BST_Free(current);
				current = BST_Find_Parent(BST_ptr -> Root, index);
				if(direction_flag){
					current -> PtrToLeftNode = temp_add;
					current -> leaf_state = (current -> leaf_state) - BST_NODE_LEFT_CHILD + temp_child;
				}
				else{
					current -> PtrToRightNode = temp_add;
					current -> leaf_state = (current -> leaf_state) - BST_NODE_RIGHT_CHILD + temp_child;
				}
				BST_UpdateIndex(BST_ptr -> Root, NULL, BST_LEFT);
				return BST_NoError;

			}
		}
		if(data < (current -> Data)){
			if(((current -> leaf_state) == BST_NODE_LEAF) || ((current -> leaf_state) == BST_NODE_RIGHT_CHILD)){
				return BST_ElementNotFound;
			}
			else{
				prev = current;
				current = current -> PtrToLeftNode;
			}
		}
		else{
			if(((current -> leaf_state) == BST_NODE_LEAF) || ((current -> leaf_state) == BST_NODE_LEFT_CHILD)){
				return BST_ElementNotFound;
			}
			else{
				prev = current;
				current = current -> PtrToRightNode;
			}
		}
	}
	return BST_ElementNotFound;
}

BST_DataSize* BST_UpdateElement(BST* BST_ptr, BST_DataSize old_data, BST_DataSize new_data){
	BST_node* current = BST_ptr -> Root;
	BST_DataSize* New_data_ptr = NULL;
	if(current == NULL){
		return New_data_ptr;
	}
	while(!((((current -> PtrToLeftNode) == NULL) && (old_data < (current -> Data))) || ((((current -> PtrToRightNode) == NULL) && (old_data > (current -> Data)))))){
		if(old_data == (current -> Data)){
			if(BST_Delete(BST_ptr, old_data) != BST_NoError){
				return New_data_ptr;
			}
			else{
				BST_Insert(BST_ptr, new_data);
				return BST_FindElement(BST_ptr, new_data);
			}
		}
		else{
			if(old_data < (current -> Data)){
				if(((current -> leaf_state) == BST_NODE_LEAF) || ((current -> leaf_state) == BST_NODE_RIGHT_CHILD)){
					return New_data_ptr;
				}
				else{
					current = current -> PtrToLeftNode;
				}
			}
			else{
				if(((current -> leaf_state) == BST_NODE_LEAF) || ((current -> leaf_state) == BST_NODE_LEFT_CHILD)){
					return New_data_ptr;
				}
				else{
					current = current -> PtrToRightNode;
				}
			}
		}
	}
	return New_data_ptr;
}

BST_ElementIsExist BST_ElementIsFound(BST* BST_ptr, BST_DataSize data){
	BST_node* current = BST_ptr -> Root;
	if(current == NULL){
		return BST_Element_Not_Found;
	}
	while(!((((current -> PtrToLeftNode) == NULL) && (data < (current -> Data))) || ((((current -> PtrToRightNode) == NULL) && (data > (current -> Data)))))){
		if(data == (current -> Data)){
			return BST_Element_Found;
		}
		if(data < (current -> Data)){
			if(((current -> leaf_state) == BST_NODE_LEAF) || ((current -> leaf_state) == BST_NODE_RIGHT_CHILD)){
				return BST_Element_Not_Found;
			}
			else{
				current = current -> PtrToLeftNode;
			}
		}
		else{
			if(((current -> leaf_state) == BST_NODE_LEAF) || ((current -> leaf_state) == BST_NODE_LEFT_CHILD)){
				return BST_Element_Not_Found;
			}
			else{
				current = current -> PtrToRightNode;
			}
		}
	}
	return BST_Element_Not_Found;
}

/*
static void BST_LeftLevel(BST_node* current, uint8 Level, uint8 direction){
	uint8 level = Level;
	if(Level_Flag){
		return;
	}
	if(current == NULL){
		return;
	}
	if(((current -> PtrToLeftNode) == NULL) && ((current -> PtrToRightNode) == NULL)){
		return;
	}
	else{
		if(direction == BST_LEFT){
			current= current -> PtrToLeftNode;
		}
		else{
			current= current -> PtrToRightNode;
		}
	}
	if(level > Left_Level){
		Left_Level = level;
	}
	BST_LeftLevel(current, Level, BST_LEFT);
	BST_LeftLevel(current, Level, BST_RIGHT);
	Level_Flag = 1;
}

void BST_Balance(BST* BST_ptr)
{
	BST_DataSize arr[BST_Max_Elements];
	uint8 index = 0;
	uint8 middle = 0, sum = 0, tomb, front = 0, back = 0, Counter = 0;
	BST new;
	if((BST_ptr -> Root) == NULL){
		return;
	}
	BST_Init(&new);
	BST_ConvertIntoArray(BST_ptr -> Root, arr, &index);

	for(uint8 count = 1; sum < index; count = count << 1)
	{
		sum = sum + count;
		Counter++;
	}

	for(uint8 count = 0; count <= index; count++)
	{
		if(count != arr[count])
		{
			tomb = count;
			break;
		}
		else if(count == index)
		{
			tomb = count;
			break;
		}
	}

	front = (sum - index)/2;
	back = sum - (index + front);

	for(uint8 count = 0; count < sum; count++)
	{
		if(count < back)
		{
			arr[sum - count - 1] = tomb;
		}
		else if(count >= (index + front))
		{
			arr[sum - count - 1] = tomb;
		}
		else
		{
			arr[sum - count - 1] = arr[sum - count - front - 1];
		}
	}

	index = sum;
	sum = 0;
	middle = ((float)(index)/2) + 0.5;

	for(uint8 count = 0; count < Counter; count++)
	{
		for(uint8 count2 = middle; count2 <= index; count2 += middle)
		{
			if((count2 % (middle * 2)) != 0){
				BST_Insert(&new, arr[count2 - 1]);
			}
		}
		middle = middle/2;
	}
	(*BST_ptr) = new;
}

static void BST_ConvertIntoArray(BST_node* root, BST_DataSize* arr_ptr, uint8* index)
{
	BST_node* current = root;

	if(current == NULL)
		return;

	if(direction == BST_LEFT){
		if((current -> PtrToLeftNode) == NULL)
			return;
		current = current -> PtrToLeftNode;
	}
	else{
		if((current -> PtrToRightNode) == NULL)
					return;
		current = current -> PtrToRightNode;
	}
	BST_ConvertIntoArray(current -> PtrToLeftNode, arr_ptr, index);
	arr_ptr[*index] = current -> Data;
	(*index)++;
	BST_ConvertIntoArray(current -> PtrToRightNode, arr_ptr, index);
}
*/

#if(BST_PRINT ==  BST_PRINTING)
BST_ErrorType BST_Print(BST* BST_ptr){
	BST_node* Ptr_Elemnets = (BST_node*)&(BST_ptr -> Tree);
	BST_node* current = BST_ptr -> Root;
	const uint8 arr_size = 200;
	BST_DataSize arr[arr_size];
	uint8 max_index = 0;
	uint8 count1 = 0;
	uint8 count2 = 0;
	uint8 count3 = 0;
	uint8 count4 = 0;
	//setbuf(stdout, NULL);
	if(current == NULL){
		return BST_Empty;
	}
	while(count1 != arr_size){
		arr[count1] = MAX_Index;
		count1++;
	}
	count1 = 0;
	while(count1 != BST_Max_Elements){
		if((Ptr_Elemnets[count1].Index) == MAX_Index){

		}
		else{
			arr[Ptr_Elemnets[count1].Index] = Ptr_Elemnets[count1].Data;
			if((Ptr_Elemnets[count1].Index) > max_index)
				max_index = Ptr_Elemnets[count1].Index;
		}
		count1++;
	}
	for(count1 = 0; count1 < 10; count1++){
		while(count3 != (10 - count1)){
			printf("   ");
			count3 += 1;
		}
		count3 = 0;
		for(count2 = 0; count2 < (1 << count1); count2++){
			if(arr[count4] == MAX_Index){
				printf(" _ ");
			}
			else{
				printf(" %lu ", arr[count4]);
			}
			if(count4 == max_index){
				printf("\n");
				return BST_NoError;
			}
			count4++;
		}
		printf("\n");
	}
	printf("\n");
	return BST_NoError;
}
#endif

/*uint32 BST_FindElement(BST* BST_ptr, uint8 Index){

}*/

int main (void){
	BST_Init(&yahia);
	BST_Insert(&yahia, 11);
	BST_Insert(&yahia, 15);
	BST_Insert(&yahia, 6);
	BST_Insert(&yahia, 3);
	BST_Insert(&yahia, 8);
	BST_Insert(&yahia, 13);
	BST_Insert(&yahia, 17);
	BST_Insert(&yahia, 1);
	BST_Insert(&yahia, 5);
	BST_Insert(&yahia, 12);
	BST_Insert(&yahia, 14);
	BST_Insert(&yahia, 11);
	//BST_Print(&yahia);
	BST_UpdateElement(&yahia, 12, 20);
	BST_UpdateElement(&yahia, 12, 21);
	BST_UpdateElement(&yahia, 11, 2);
	/*Level_Flag = 0;
	BST_FindLevel(yahia.Root, NULL, BST_LEFT);
	Level_Flag = 0;
	BST_FindLevel(yahia.Root, NULL, BST_RIGHT);
	printf("\nLeft level = %d", left_level);
	printf("\nRight level = %d", right_level);*/
	BST_ElementIsFound(&yahia, 15);
	BST_ElementIsFound(&yahia, 19);
	BST_ElementIsFound(&yahia, 17);
	BST_ElementIsFound(&yahia, 1);
	BST_ElementIsFound(&yahia, 8);
	BST_ElementIsFound(&yahia, 3);
	BST_ElementIsFound(&yahia, 10);
	BST_ElementIsFound(&yahia, 20);
	BST_ElementIsFound(&yahia, 9);
	BST_ElementIsFound(&yahia, 0);
	/*BST_FindIndex(&yahia, 10);
	BST_FindIndex(&yahia, 12);
	BST_FindIndex(&yahia, 7);
	BST_FindIndex(&yahia, 8);
	BST_FindIndex(&yahia, 10);
	BST_FindIndex(&yahia, 11);
	BST_FindIndex(&yahia, 5);*/
	BST_Delete(&yahia, 6);
	BST_Delete(&yahia, 15);
	BST_Delete(&yahia, 11);
	BST_ElementIsFound(&yahia, 11);
	BST_ElementIsFound(&yahia, 15);
	BST_ElementIsFound(&yahia, 6);
	BST_Print(&yahia);
	//BST_Delete(&yahia, 12);
	//BST_Delete(&yahia, 10);
}
