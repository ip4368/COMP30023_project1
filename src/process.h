/*****************************************************************************/
/*                                                                           */
/*          This is a submission for assignment 1 of                         */
/*          COMP30023 Computer Systems                                       */
/*                                                                           */
/*          Author     : Shing Sheung Daniel Ip                              */
/*          Student ID : 723508                                              */
/*          Finish Time: 6th April 2017 15:08                                */
/*                                                                           */
/*     Processes library, also some printing function for debugging purpose  */
/*                                                                           */
/*****************************************************************************/

#include "queue.h"

#ifndef PROCESS

#define PROCESS

#define PROCESS_TEMPLATE "\t id = %d; lastActiveTime = %d; "\
					"memsize = %d; timeRemaining = %d\n"
#define PROCESS_INIT_LEN 10

typedef struct {
	int lastActiveTime;
	int id;
	int memsize;
	int timeRemaining;
} process_t;

typedef process_t *Process;

typedef struct{
	Process process;
	QueueNode rrqNode;
	int startStayingTime;
	int fromAddress, toAddress;
}*ProcessInStorage;

void printProcesses(Process processes, int size);
void printProcess(process_t process);

#endif
