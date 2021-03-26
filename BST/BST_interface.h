/*
 * BST_interface.h
 *
 *  Created on: 4 Jan 2020
 *      Author: Yahia
 */

#ifndef BST_INTERFACE_H_
#define BST_INTERFACE_H_

#include "BST_config.h"

typedef enum{
	BST_NODE_EMPTY,
	BST_NODE_OCCUPIED
}BST_NODE_STATE;

typedef enum{
	BST_NODE_LEAF,
	BST_NODE_LEFT_CHILD,
	BST_NODE_RIGHT_CHILD,
	BST_NODE_TWO_CHILD,
	BST_NODE_NULL
}BST_NODE_LeafOrNot;

typedef enum{
	BST_Element_Not_Found,
	BST_Element_Found
}BST_ElementIsExist;

typedef enum{
	BST_Notfound,
	BST_Full,
	BST_Empty,
	BST_ElementNotFound,
	BST_NoError
}BST_ErrorType;

struct BSTNode{
	struct BSTNode* PtrToLeftNode;
	struct BSTNode* PtrToRightNode;
	BST_DataSize Data;
	uint8 Index;
	BST_NODE_STATE State;
	BST_NODE_LeafOrNot leaf_state;
};

typedef struct BSTNode BST_node;
typedef struct{
	BST_node Tree[BST_Max_Elements];
	BST_node* Root;
}BST;

#ifndef BST_PRINTING
#define BST_PRINTING		1
#endif

#ifndef BST_NOT_PRINTING
#define BST_NOT_PRINTING	0
#endif

void BST_Init(BST* BST_ptr);
BST_node* BST_Insert(BST* BST_ptr, BST_DataSize data);
uint32 BST_FindIndex(BST* BST_ptr, BST_DataSize data);
BST_DataSize* BST_FindElement(BST* BST_ptr, BST_DataSize data);
//uint32 BST_FindElement(BST* BST_ptr, uint8 Index);
BST_ErrorType BST_Delete(BST* BST_ptr, BST_DataSize data);
static void BST_Free(BST_node* PtrToNode);
static void BST_UpdateIndex(BST_node* current, BST_node* prev, uint8 direction);
static BST_node* BST_Find_Parent(BST_node* root, uint8 index);
BST_ElementIsExist BST_ElementIsFound(BST* BST_ptr, BST_DataSize data);
BST_DataSize* BST_UpdateElement(BST* BST_ptr, BST_DataSize old_data, BST_DataSize new_data);
void BST_Balance(BST* BST_ptr);
//static void BST_ConvertIntoArray(BST_node* root, BST_DataSize* arr_ptr, uint8* index);
#if(BST_PRINT ==  BST_PRINTING)
BST_ErrorType BST_Print(BST* BST_ptr);
//static void BST_LeftLevel(BST_node* current, uint8 Level, uint8 direction);
//static void BST_RightLevel(BST* BST_ptr, BST_DataSize Start, uint8* Level, uint8 direction);
#endif


#endif /* BST_INTERFACE_H_ */
