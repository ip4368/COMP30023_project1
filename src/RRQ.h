/*****************************************************************************/
/*                                                                           */
/*          This is a submission for assignment 1 of                         */
/*          COMP30023 Computer Systems                                       */
/*                                                                           */
/*          Author     : Shing Sheung Daniel Ip                              */
/*          Student ID : 723508                                              */
/*          Finish Time: 6th April 2017 15:08                                */
/*                                                                           */
/*     Round Robin Queue Component                                           */
/*                                                                           */
/*****************************************************************************/

#include "queue.h"
#include "process.h"

#ifndef RRQ

#define RRQ

typedef struct{
	Process p;
	QueueNode memNode;
}*RRQData;

/*
 * this is just an easy method to get the process from the RRQ data
 */
Process rrqData2Process(RRQData rrqData);

/*
 * create new Round Robin Data for Round Robin Queue
 */
RRQData newRrqData(Process p);

#endif
