/*****************************************************************************/
/*                                                                           */
/*          This is a submission for assignment 1 of                         */
/*          COMP30023 Computer Systems                                       */
/*                                                                           */
/*          Author     : Shing Sheung Daniel Ip                              */
/*          Student ID : 723508                                              */
/*          Finish Time: 6th April 2017 15:08                                */
/*                                                                           */
/*     FIFO queue, but allow to remove a node in middle if that node is known*/
/*                                                                           */
/*****************************************************************************/

/*
 * Using the linked-list data structure in list.h and list.c
 * to archieve a FIFO queue
 * Author: Shing Sheung Daniel Ip (Github: ip4368)
 * StudentID in unimelb: 723508
 */

#include "list.h"

#ifndef QUEUE

#define QUEUE

typedef List Queue;
typedef ListNode QueueNode;

Queue newQueue();

QueueNode enqueue(Queue queue, void *data);

void *dequeue(Queue queue);

void queue_remove(Queue queue, QueueNode node);

int queue_is_empty(Queue queue);

#endif
