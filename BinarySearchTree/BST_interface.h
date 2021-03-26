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
	BST_NODE_TWO_CHILD
}BST_NODE_LeafOrNot;

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
BST_ErrorType BST_Insert(BST* BST_ptr, BST_DataSize data);
BST_ErrorType BST_Find(BST* BST_ptr, BST_DataSize data);


#endif /* BST_INTERFACE_H_ */
