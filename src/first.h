/*****************************************************************************/
/*                                                                           */
/*          This is a submission for assignment 1 of                         */
/*          COMP30023 Computer Systems                                       */
/*                                                                           */
/*          Author     : Shing Sheung Daniel Ip                              */
/*          Student ID : 723508                                              */
/*          Finish Time: 6th April 2017 15:08                                */
/*                                                                           */
/*     Implementing memoryAlgorthmController interface with first fit        */
/*                                                                           */
/*****************************************************************************/

#include "list.h"
#include "memoryAlgorithmController.h"

#ifndef FIRST_FIT

#define FIRST_FIT


typedef struct {
	List list;
	int availableTotal;
}*First;

memController_t firstInitMemController();
int firstCanFit(void* storage, int size);
void firstAddFreeMem(void* storage, int fromAddress, int toAddress);
void firstReserveSize(
	void* storage, int size, int *fromAddress, int *toAddress);
int firstGetAvailTotal(void* storage);
int firstGetNumHoles(void* storage);

#endif
