/*****************************************************************************/
/*                                                                           */
/*          This is a submission for assignment 1 of                         */
/*          COMP30023 Computer Systems                                       */
/*                                                                           */
/*          Author     : Shing Sheung Daniel Ip                              */
/*          Student ID : 723508                                              */
/*          Finish Time: 6th April 2017 15:08                                */
/*                                                                           */
/*     List, doubly-linked-list, nothing else to say lol                     */
/*                                                                           */
/*****************************************************************************/

/*
 * linked-list data structure, support append(end) and pop(front) only
 * Author: Shing Sheung Daniel Ip (Github: ip4368)
 * StudentID in unimelb: 723508
 */

#ifndef LIST

#define LIST

typedef struct list_node_t *ListNode;

struct list_node_t{
	ListNode previous, next;
	void *data;
};

typedef struct {
	ListNode head;
	ListNode tail;
	int size;
} *List;

List newList();

// add void ptr data to the end of the list
ListNode list_append(List list, void *data);
ListNode list_insert_sorted(List list, void *data, int(*cmp)(void *, void*));

// remove the head and return the data void ptr holding by the head
void *list_pop(List list);

void list_remove(List list, ListNode node);

void *list_peek_head(List list);

int list_is_empty(List list);

#endif
