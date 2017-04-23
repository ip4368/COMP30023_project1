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

#include <stdio.h>
#include "cmp.h"
#include "memory.h"
#include "process.h"
#include "hole.h"
#include "first.h"
#include "best.h"
#include "first.h"


int holeAddress(void *data1, void *data2){
	Hole hole1 = (Hole)data1;
	Hole hole2 = (Hole)data2;

	if(hole1->startAddress < hole2->startAddress){
		return -1;
	}
	if(hole1->startAddress == hole2->startAddress){
		return 0;
	}
	return 1;
}

int processId(void *data1, void *data2){
	Process p1 = (Process)data1;
	Process p2 = (Process)data2;

	if(p1->id < p2->id)
		return 1;
	if(p1->id == p2->id)
		return 0;
	return -1;
}

int processIdInPisInQueue(void *data1, void *data2){
	QueueNode q1 = (QueueNode)data1;
	QueueNode q2 = (QueueNode)data2;

	ProcessInStorage pis1 = (ProcessInStorage)q1->data;
	ProcessInStorage pis2 = (ProcessInStorage)q2->data;

	return processId(pis1->process, pis2->process);
}
