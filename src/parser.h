/*****************************************************************************/
/*                                                                           */
/*          This is a submission for assignment 1 of                         */
/*          COMP30023 Computer Systems                                       */
/*                                                                           */
/*          Author     : Shing Sheung Daniel Ip                              */
/*          Student ID : 723508                                              */
/*          Finish Time: 6th April 2017 15:08                                */
/*                                                                           */
/*     Just parser for the input file                                        */
/*                                                                           */
/*****************************************************************************/

#include "process.h"

#ifndef PROCESS_PARSER

#define PROCESS_PARSER

#define READ_ONLY "r"
#define FILE_FAILURE_MSG "file reading failure on line %d\n"

Process readProcessesFromFile(char *filename, int *size);
int readLine(FILE* file, Process process);
void readException(int);

#endif
