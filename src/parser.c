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
#include "parser.h"
#include "alloc.h"

Process readProcessesFromFile(char *filename, int *size){
	FILE *file = fopen(filename, READ_ONLY);
	int currMax = PROCESS_INIT_LEN;
	int currSize = 0;
	Process processes = safe_malloc(sizeof(*processes) * currMax);
	while(readLine(file, processes + currSize) != EOF){
		currSize++;
		if(currSize == currMax){
			currMax *= 2;
			processes = safe_realloc(processes, sizeof(*processes) * currMax);
		}
	}
	(*size) = currSize;
	return processes;
}

int readLine(FILE* file, Process process){
	static int line = 0;
	line++;
	switch(fscanf(file, "%d %d %d %d",
		&(process->lastActiveTime),
		&(process->id),
		&(process->memsize),
		&(process->timeRemaining))){
		case EOF:
			return EOF;
			break;
		case 4:
			return 4;
			break;
		default:
			readException(line);
			break;
	}
	return 0;
}

void readException(int line){
	fprintf(stderr, FILE_FAILURE_MSG, line);
	exit(EXIT_FAILURE);
}
