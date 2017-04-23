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
#include "memory.h"
#include "time.h"
#include "alloc.h"
#include "queue.h"

memory_t init_memory(){
	memory_t memory;
	memory.processes = newQueue();
	memory.running = NULL;

	return memory;
}

Process stayedLongestInMem(memory_t memory){
	if(memory.processes->head == NULL)
		return NULL;
	ProcessInStorage pis = (ProcessInStorage)memory.processes->head->data;
	return pis->process;
}

Process stayedShortest(memory_t memory){
	if(memory.processes->tail == NULL)
		return NULL;
	ProcessInStorage pis = (ProcessInStorage)memory.processes->tail->data;
	return pis->process;
}

QueueNode add2Memory(memory_t *memory, Process p,
		int fromAddress, int toAddress, QueueNode qn){
	ProcessInStorage pis = (ProcessInStorage)safe_malloc(sizeof(*pis));
	pis->startStayingTime = getTime();
	pis->process = p;
	pis->rrqNode = qn;
	pis->fromAddress = fromAddress;
	pis->toAddress = toAddress;
	return enqueue(memory->processes, pis);
}

void updateRRQNode(QueueNode memNode, QueueNode rrqNode){
	ProcessInStorage pis = (ProcessInStorage)memNode->data;
	pis->rrqNode = rrqNode;
}

void memRemoveLongest(memory_t *memory, Queue q, int *fromAddress,
		int *toAddress, int *justFinishedSwappedOut){
	ProcessInStorage pis = (ProcessInStorage)dequeue(memory->processes);
	/*
	 * there already isn't any process in memory
	 */
	if(pis == NULL)
		return;

	if(fromAddress != NULL)
		(*fromAddress) = pis->fromAddress;
	if(toAddress != NULL)
		(*toAddress) = pis->toAddress;

	/*
	 * Need to remove from round robin queue
	 * don't remove from RRQ if just finished (not in RRQ)
	 */
	if(pis->rrqNode != NULL){
		queue_remove(q, pis->rrqNode);
	}else if(justFinishedSwappedOut != NULL)
		(*justFinishedSwappedOut) = 1;

	free(pis);
}

int isMemoryEmpty(memory_t memory){
	return queue_is_empty(memory.processes);
}
