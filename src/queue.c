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

#include "queue.h"
#include "list.h"

Queue newQueue(){
	return newList();
}

QueueNode enqueue(Queue queue, void *data){
	return list_append(queue, data);
}

void *dequeue(Queue queue){
	return list_pop(queue);
}

void queue_remove(Queue queue, QueueNode node){
	list_remove(queue, node);
}

void *queue_peek_front(Queue queue){
	return list_peek_head(queue);
}

int queue_is_empty(Queue queue){
	return list_is_empty(queue);
}
