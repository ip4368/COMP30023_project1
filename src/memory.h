/*****************************************************************************/
/*                                                                           */
/*          This is a submission for assignment 1 of                         */
/*          COMP30023 Computer Systems                                       */
/*                                                                           */
/*          Author     : Shing Sheung Daniel Ip                              */
/*          Student ID : 723508                                              */
/*          Finish Time: 6th April 2017 15:08                                */
/*                                                                           */
/*     This holds the current processes in memory                            */
/*                                                                           */
/*****************************************************************************/

#include "process.h"
#include "queue.h"
#include "RRQ.h"


#ifndef MEMORY

#define MEMORY


typedef struct{
	Queue processes;
	RRQData running;
}memory_t;

memory_t init_memory();

/*
 * find the longest and shortest, longest potentially is the one be swapped out
 */
Process stayedLongestInMem(memory_t memory);
Process stayedShortest(memory_t memory);

/*
 * add a new process to memory, with the address associated to that process
 * this also holds information of the node in RRQ,
 * as potential deletion in RRQ if being swapped out
 */
QueueNode add2Memory(memory_t *memory, Process p,
		int fromAddress, int toAddress, QueueNode qn);
void updateRRQNode(QueueNode memNode, QueueNode rrqNode);

/*
 * actually remove the longest process in memory, according the the priority
 */
void memRemoveLongest(memory_t *memory, Queue q, int *fromAddress,
		int *toAddress, int *justFinishedSwappedOut);

/*
 * check if the memory is holding nothing
 */
int isMemoryEmpty(memory_t memory);

#endif
