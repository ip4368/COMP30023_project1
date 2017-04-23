/*****************************************************************************/
/*                                                                           */
/*          This is a submission for assignment 1 of                         */
/*          COMP30023 Computer Systems                                       */
/*                                                                           */
/*          Author     : Shing Sheung Daniel Ip                              */
/*          Student ID : 723508                                              */
/*          Finish Time: 6th April 2017 15:08                                */
/*                                                                           */
/*****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "alloc.h"

List newList(){
	List list = (List)safe_malloc(sizeof(*list));
	list->head = list->tail = NULL;
	list->size = 0;
	return list;
}

ListNode list_append(List list, void *data){
	ListNode node = (ListNode)safe_malloc(sizeof(*node));

	/*
	 * list originally empty
	 */
	if(list->head == NULL && list->tail == NULL){
		node->next = node->previous = NULL;
		node->data = data;
		list->head = list->tail = node;
		list->size++;
		return node;
	}
	/*
	 * initialise the node attributes
	 */
	// newly appended should be the end, no next node
	node->next = NULL;
	node->previous = list->tail;
	node->previous->next = node;
	node->data = data;

	/*
	 * set the next of the tail to new node
	 * need to update the tail of the list as well
	 */
	list->tail = node;
	list->size++;
	return node;
}

ListNode list_insert_sorted(List list, void *data, int(*cmp)(void *, void*)){
	/*
	 * Just nothing in list, just insert any way
	 */
	if(list->head == NULL && list->tail == NULL){
		return list_append(list, data);
	}

	ListNode node = (ListNode)safe_malloc(sizeof(*node));
	node->data = data;
	ListNode currNode = list->head;
	/*
	 * loop which curr is larger
	 */
	while(currNode != NULL && (*cmp)(currNode->data, data) > 0){
		currNode = currNode->next;
	}

	/*
	 * so it stopped, the data need to be inserted before the currNode;
	 */
	if(currNode == NULL){
		// this means the data should be inserted at the end of the queue
		node->previous = list->tail;
		node->next = NULL;
		list->tail->next = node;
		list->tail = node;
	}else if(currNode->previous == NULL){
		// or insert at the front
		node->previous = NULL;
		node->next = currNode;
		list->head->previous = node;
		list->head = node;
	}else{
		// insert somewhere middle
		node->previous = currNode->previous;
		node->next = currNode;
		node->previous->next = node->next->previous = node;
	}
	list->size++;
	return node;
}

void *list_pop(List list){
	/*
	 * only one node in the list
	 */
	if(list->head == list->tail){
		ListNode node = list->head;
		list->head = list->tail = NULL;
		void *data = node->data;
		free(node);
		list->size--;
		return data;
	}

	/*
	 * remove and update the head, return the data stored
	 */
	ListNode head = list->head;
	list->head = head->next;
	// the new head should not have any previous node
	list->head->previous = NULL;
	void *data = head->data;
	free(head);
	list->size--;
	return data;
}

void list_remove(List list, ListNode node){
	/*
	 * ONLY 1 node in the list or removing the head, just pop it
	 */
	if(node->previous == NULL){
		list_pop(list);
		return;
	}

	/*
	 * If the node is tail
	 */
	if(list->tail == node){
		list->tail = node->previous;
		list->tail->next = NULL;
		free(node);
		list->size--;
		return;
	}

	node->previous->next = node->next;
	node->next->previous = node->previous;
	free(node);
	list->size--;
}

void *list_peek_head(List list){
	return list->head->data;
}

int list_is_empty(List list){
	return !list->size;
}
