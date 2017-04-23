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
#include "process.h"
#include "queue.h"

void printProcesses(Process processes, int size){
	printf("Processes recorded:\n");
	int i;
	for(i=0; i<size; i++){
		printProcess(processes[i]);
	}
}

void printProcess(process_t process){
	printf(PROCESS_TEMPLATE,
		process.id,
		process.lastActiveTime,
		process.memsize,
		process.timeRemaining);
}
