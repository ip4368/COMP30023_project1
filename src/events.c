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
#include "events.h"
#include "time.h"
#include "process.h"
#include "memory.h"


int time2NextEvent(memory_t memory, Process nextProcessComing, int quantum){
	RRQData running = memory.running;

	// if there is no process in memory
	if(memory.processes->size == 0 && nextProcessComing != NULL){
		return nextProcessComing->lastActiveTime;
	}

	int nextProcessArrivingTime =
		(nextProcessComing == NULL) ? 0 : nextProcessComing->lastActiveTime;
	int processStop;

	/*
	 * if there is something in memory,
	 * something should be running or going to end
	 */
	Process runningp = (running == NULL) ? NULL : rrqData2Process(running);
	if(running != NULL){
		if(runningp->timeRemaining > quantum){
			processStop = runningp->lastActiveTime + quantum;
		}else{
			processStop = runningp->lastActiveTime + runningp->timeRemaining;
		}
	}else{
		processStop = 0;
	}

	if(nextProcessComing == NULL && runningp == NULL){
		return getTime();
	}

	if(nextProcessComing != NULL && nextProcessArrivingTime < processStop){
		return nextProcessArrivingTime;
	}else{
		return processStop;
	}
}
