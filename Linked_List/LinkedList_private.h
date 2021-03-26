/*
 * LinkedList_private.h
 *
 *  Created on: 1 Jan 2020
 *      Author: Yahia
 */

#ifndef LINKEDLIST_PRIVATE_H_
#define LINKEDLIST_PRIVATE_H_

#ifndef NULL
#define NULL	(void *)0
#endif

#define LINKEDLIST_MAXADD	(void *)0xFFFFFFFF

static uint8 LINKEDLIST_Check(linkedlist* LINKEDLIST, LINKEDLIST_node** head);

#endif /* LINKEDLIST_PRIVATE_H_ */
