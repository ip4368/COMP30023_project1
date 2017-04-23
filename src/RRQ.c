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
#include "RRQ.h"
#include "process.h"
#include "alloc.h"


Process rrqData2Process(RRQData rrqData){
	QueueNode memNode = rrqData->memNode;
	ProcessInStorage data = (ProcessInStorage)memNode->data;
	return data->process;
}

RRQData newRrqData(Process p){
	RRQData rrqData = (RRQData)safe_malloc(sizeof(*rrqData));
	rrqData->p = p;
	rrqData->memNode = NULL;
	return rrqData;
}
