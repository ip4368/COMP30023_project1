/*****************************************************************************/
/*                                                                           */
/*          This is a submission for assignment 1 of                         */
/*          COMP30023 Computer Systems                                       */
/*                                                                           */
/*          Author     : Shing Sheung Daniel Ip                              */
/*          Student ID : 723508                                              */
/*          Finish Time: 6th April 2017 15:08                                */
/*                                                                           */
/*     Implementing memoryAlgorthmController interface with best fit         */
/*                                                                           */
/*****************************************************************************/

#include "list.h"
#include "memoryAlgorithmController.h"
#include "hole.h"

#ifndef BEST_FIT

#define BEST_FIT


typedef struct {
	List list;
	int availableTotal;
}*Best;

memController_t bestInitMemController();
int bestCanFit(void* storage, int size);
void bestAddFreeMem(void* storage, int startAddress, int endAddress);
void bestReserveSize(
	void* storage, int size, int *startAddress, int *endAddress);
int bestGetAvailTotal(void* storage);
int bestGetNumHoles(void* storage);

#endif
