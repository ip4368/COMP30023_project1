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
#include "disk.h"
#include "list.h"
#include "queue.h"
#include "cmp.h"


disk_t init_disk(){
	return init_memory();
}

Process stayedLongestInDisk(disk_t disk){
	List candidate = newList();

	QueueNode pisNode = disk.processes->head;
	ProcessInStorage pis = (ProcessInStorage)pisNode->data;
	list_insert_sorted(candidate, pisNode, &processIdInPisInQueue);
	/*
	 * there already isn't any process in disk
	 */
	if(pisNode == NULL)
		return NULL;

	QueueNode nextNode = pisNode->next;
	ProcessInStorage nextPis =
		(nextNode == NULL) ? NULL : (ProcessInStorage)nextNode->data;

	// make sure find all the process with same staying time, insert as sorted
	while(nextNode != NULL &&
			pis->startStayingTime == nextPis->startStayingTime){
		list_insert_sorted(candidate, nextNode, &processIdInPisInQueue);
		nextNode = nextNode->next;
		nextPis = (nextNode == NULL) ? NULL : (ProcessInStorage)nextNode->data;
	}

	// as sorted, the head must be lowest id with same staying time
	QueueNode longest = (QueueNode)list_pop(candidate);
	pis = (ProcessInStorage)longest->data;
	Process p = pis->process;

	free(candidate);
	return p;
}

QueueNode add2Disk(disk_t *disk, Process p){
	return add2Memory(disk, p, -1, -1, NULL);
}

void diskRemoveLongest(disk_t *disk){
	List candidate = newList();

	QueueNode pisNode = disk->processes->head;
	ProcessInStorage pis = (ProcessInStorage)pisNode->data;
	list_insert_sorted(candidate, pisNode, &processIdInPisInQueue);

	if(pisNode == NULL)
		return;

	QueueNode nextNode = pisNode->next;
	ProcessInStorage nextPis =
		(nextNode == NULL) ? NULL : (ProcessInStorage)nextNode->data;

	// make sure find all the process with same staying time, insert as sorted
	while(nextNode != NULL &&
			pis->startStayingTime == nextPis->startStayingTime){
		list_insert_sorted(candidate, nextNode, &processIdInPisInQueue);
		nextNode = nextNode->next;
		nextPis = (nextNode == NULL) ? NULL : (ProcessInStorage)nextNode->data;
	}

	// as sorted, the head must be lowest id with same staying time
	QueueNode removing = (QueueNode)list_pop(candidate);
	queue_remove(disk->processes, removing);
	pis = (ProcessInStorage)removing->data;
	free(candidate);
	free(pis);
}

int isDiskEmpty(disk_t disk){
	return isMemoryEmpty(disk);
}
