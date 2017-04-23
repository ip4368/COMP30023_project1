/*****************************************************************************/
/*                                                                           */
/*          This is a submission for assignment 1 of                         */
/*          COMP30023 Computer Systems                                       */
/*                                                                           */
/*          Author     : Shing Sheung Daniel Ip                              */
/*          Student ID : 723508                                              */
/*          Finish Time: 6th April 2017 15:08                                */
/*                                                                           */
/* there are a lot of components used in this driver program,                */
/*     parse_args.h: parser for arguments (be updated if add algorithm)      */
/*     time.h: provide a standard interface for all components in this       */
/*             program to count and get the time                             */
/*     parser.h: parse the input file according to parse the -f argument     */
/*     events.h: it calculate what is the time the next event should happen  */
/*               VERY IMPORTANT                                              */
/*               the main loop in the main is basically built on top of this */
/*     memory.h: this holds the current processes in memory,                 */
/*               but not holding the holes,                                  */
/*               the holes should be held by the memory algorithms           */
/*     disk.h: this holds the current processes in disk,                     */
/*             basically build on top of memory.h                            */
/*     memoryAlgorithmController.h:                                          */
/*                       standard interface for all memory algorthms         */
/*     first.h: the implementation of the interface for first fit            */
/*     best.h: the implementation of the interface for best fit              */
/*             tried to use 2 self balancing search tree to do this          */
/*             but turned out my tree is buggy, so using linked list now     */
/*     worst.h: the implementation of the interface for worst fit            */
/*     list.h: provide doubly-linked-list                                    */
/*     queue.h: a first in first out queue,                                  */
/*              but actually provide a bit more functionality than that      */
/*     RRQ.h: round robin queue, implemented on top of queue.h               */
/*     cmp.h: this provides all the comparator functions used                */
/*                                                                           */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "parse_args.h"
#include "time.h"
#include "events.h"
#include "process.h"
#include "parser.h"
#include "memory.h"
#include "disk.h"
#include "memoryAlgorithmController.h"
#include "first.h"
#include "best.h"
#include "worst.h"
#include "list.h"
#include "queue.h"
#include "RRQ.h"
#include "cmp.h"


/*****************************************************************************/
/*
 * functions prototype
 */

void loadProcess2Disk(
	Process processes, int *n, int numProcesses, disk_t *disk);
RRQData clearRunning(memory_t *mem, int quantum);
void startRunning(memory_t *mem, Queue rrq);
void swap(memory_t *mem, disk_t *disk, Queue rrq,
	memController_t *memController, int *justStoppedSwappedOut, int memSize);
void QuantumException();
void EmptyMemorySwappingException();
void printMemoryPercent(int total, int availTotal);

/*****************************************************************************/

int main(int argc, char *argv[]){
	args_t args = parse_args(argc, argv);

	int numProcesses;
	Process processes = readProcessesFromFile(args.filename, &numProcesses);

	memory_t memory = init_memory();
	disk_t disk = init_disk();
	Queue roundRobinQueue = newQueue();
	/*
	 * initialise this with switch for controller
	 * anyone code a adapter according to controller interface
	 * should be able to run with this driver program
	 * Update only this part if more algorithms interfaces being implemented
	 */
	memController_t memController;
	switch(args.algorithm){
		case FIRST:
			memController = firstInitMemController();
			break;
		case BEST:
			memController = bestInitMemController();
			break;
		case WORST:
			memController = worstInitMemController();
			break;
		default:
			break;
	}
	(*memController.addFreeMem)(memController.data, 0, args.memsize);

	int i=0;
	int finished, justStoppedSwappedOut;
	/*
	 * main loop, fully based on time counting to do next event (by events.h)
	 */
	while((i<numProcesses || memory.running != NULL) ||
			memory.processes->size != 0){
		int t;
		if(i == numProcesses)
			t = time2NextEvent(memory, NULL, args.quantum);
		else
			t = time2NextEvent(memory, processes + i, args.quantum);
		// increase the time here
		time(t - getTime());

		// try to load process to disk
		// if there is any that can be loaded at this time
		loadProcess2Disk(processes, &i, numProcesses, &disk);

		// check if the process is finished, or used up the quantum
		// if yes, swap it out, may not add back to RRQ, see `finished` later
		RRQData justStopped = clearRunning(&memory, args.quantum);
		finished = 0;
		justStoppedSwappedOut = 0;

		// check if actually finished, if finished, remove from memory as well
		if(justStopped != NULL &&
				rrqData2Process(justStopped)->timeRemaining == 0){
			// finished, remove from memory and add hole, free the mem as well
			ProcessInStorage pis = justStopped->memNode->data;

			// add hole, using interface
			(*memController.addFreeMem)
				(memController.data, pis->fromAddress, pis->toAddress);

			// removing process from memory here
			queue_remove(memory.processes, justStopped->memNode);
			finished = 1;
		}

		/*
		 * if nothing running,
		 * try to swap
		 * and run the process at the front of the round robin queue
		 */
		if(memory.running == NULL){
			swap(&memory, &disk, roundRobinQueue, &memController,
				&justStoppedSwappedOut, args.memsize);
			startRunning(&memory, roundRobinQueue);
		}

		/*
		 * add the stopped process at the end of the cycle
		 * only add if something actually stopped and
		 * the stopped process is not yet finished
		 */
		if(justStopped != NULL && !justStoppedSwappedOut && !finished){
			// not finished, requeue again
			QueueNode newRrqNode = enqueue(roundRobinQueue, justStopped);
			updateRRQNode(justStopped->memNode, newRrqNode);
		}
	}

	printf("time %d, simulation finished.\n", getTime());
	return 0;
}

/*
 * this load all process coming in onto disk at current time
 */
void loadProcess2Disk(
		Process processes, int *n, int numProcesses, disk_t *disk){
	/*
	 * keep doing if the head of the processes
	 * if the processes should be on disk at current time
	 */
	while((*n) < numProcesses && processes[*n].lastActiveTime <= getTime()){
		add2Disk(disk, processes + (*n));
		(*n)++;
	}
}

/*
 * stop the process that probably finished or used up the quantum time
 * not a must tho, at this time it could only be getting process from incoming
 */
RRQData clearRunning(memory_t *mem, int quantum){
	// nothing running, nothing to clear
	if(mem->running == NULL)
		return NULL;

	// process running has finished at this time stamp
	Process runningP = rrqData2Process(mem->running);
	if(getTime() - runningP->lastActiveTime == runningP->timeRemaining){
		RRQData processRemoved = mem->running;
		runningP->lastActiveTime = getTime();
		runningP->timeRemaining = 0;
		mem->running = NULL;
		return processRemoved;
	}

	// process use up the whole quantum
	if(getTime() - runningP->lastActiveTime == quantum){
		RRQData processRemoved = mem->running;
		runningP->lastActiveTime = getTime();
		runningP->timeRemaining -= quantum;
		mem->running = NULL;
		return processRemoved;
	}

	/*
	 * if the time is greater than the quantum, something must be wrong,
	 * the event.c is not giving back the correct time
	 */
	if(getTime() - runningP->lastActiveTime > quantum){
		QuantumException();
	}

	// not yet done, should not clear the running
	return NULL;
}

/*
 * start the process at the front of the round robin queue
 */
void startRunning(memory_t *mem, Queue rrq){
	// something is running, we only have 1 CPU to run user processes
	if(mem->running != NULL){
		return;
	}

	// nothing can be swapped in
	if(queue_is_empty(rrq)){
		return;
	}
	RRQData startRun = (RRQData)dequeue(rrq);

	// this node is no longer in RRQ
	updateRRQNode(startRun->memNode, NULL);
	Process p = rrqData2Process(startRun);
	p->lastActiveTime = getTime();
	mem->running = startRun;
}

/*
 * swap in the process staying in disk for the longest,
 * swap out process in memory if needed
 */
void swap(memory_t *mem, disk_t *disk, Queue rrq,
		memController_t *memController, int *justStoppedSwappedOut,
		int memSize){
	// the disk is empty, nothing to swap
	if(isDiskEmpty(*disk))
		return;

	Process p = stayedLongestInDisk(*disk);
	// only if there is a process originally on disk
	if(p != NULL){
		diskRemoveLongest(disk);

		/*
		 * if cannot fit, keep removing from processes loaded
		 * NOTED THIS: this will NEVER swap out the process that is running
		 */
		int fromAddress, toAddress;
		while(!((*memController->canFit)(memController->data, p->memsize))){
			Process p2disk = stayedLongestInMem(*mem);

			// if swap out all processes, still cannot fit, it not gonna fit
			// therefore, exception
			if(p2disk == NULL)
				EmptyMemorySwappingException();
			
			// add swapped out process to disk
			add2Disk(disk, p2disk);

			// remove the longest process from memory after adding to disk
			memRemoveLongest(
				mem, rrq, &fromAddress, &toAddress, justStoppedSwappedOut);

			// add the freed section of memory back to holes pool
			(*memController->addFreeMem)
				(memController->data, fromAddress, toAddress);
		}

		// put the swapping in process in to Round Robin Queue
		RRQData rrqData = newRrqData(p);
		QueueNode rrqNode = enqueue(rrq, rrqData);

		// reserve memory for swapping in process
		(*memController->reserveSize)
			(memController->data, p->memsize, &fromAddress, &toAddress);

		// actually add to memory
		QueueNode memNode = add2Memory(mem, p, fromAddress, toAddress, rrqNode);
		rrqData->memNode = memNode;

		// print out swap in message
		printf("time %d, %d loaded, numprocesses=%d, numholes=%d, memusage=",
			getTime(),
			p->id,
			mem->processes->size,
			(*memController->getNumHoles)(memController->data));
		printMemoryPercent(
			memSize, (*memController->getAvailTotal)(memController->data));
		printf("\n");		
	}
}

/*
 * Exception for quantum exceeded and not yet stopping the process
 * should not happen or major error in events.h
 */
void QuantumException(){
	printf("QUANTUM EXCEEDED, TERRIBLE ERROR\n");
	exit(EXIT_FAILURE);
}

/*
 * This should not happen as well,
 * only if the process cannot even fit into the whole piece of memory
 */
void EmptyMemorySwappingException(){
	printf("PROCESS DO NOT FIT INTO MEMORY, ALL SWAPPED OUT\n");
	exit(EXIT_FAILURE);
}

/*
 * print the percent
 */
void printMemoryPercent(int total, int availTotal){
	int memRemain = total - availTotal;
	int percentNominator = memRemain * 100;
	int percent = percentNominator / total;
	// if thers is remainder, round up
	if(percentNominator % total){
		percent++;
	}
	printf("%d%%", percent);
}
