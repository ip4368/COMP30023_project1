/*****************************************************************************/
/*                                                                           */
/*          This is a submission for assignment 1 of                         */
/*          COMP30023 Computer Systems                                       */
/*                                                                           */
/*          Author     : Shing Sheung Daniel Ip                              */
/*          Student ID : 723508                                              */
/*          Finish Time: 6th April 2017 15:08                                */
/*                                                                           */
/*     Implementing memoryAlgorthmController interface with worst fit        */
/*                                                                           */
/*****************************************************************************/

#include "list.h"
#include "memoryAlgorithmController.h"
#include "hole.h"

#ifndef WORST_FIT

#define WORST_FIT


typedef struct {
	List list;
	int availableTotal;
}*Worst;

memController_t worstInitMemController();
int worstCanFit(void* storage, int size);
void worstAddFreeMem(void* storage, int fromAddress, int toAddress);
void worstReserveSize(
	void* storage, int size, int *fromAddress, int *toAddress);
int worstGetAvailTotal(void* storage);
int worstGetNumHoles(void* storage);

#endif
