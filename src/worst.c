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
#include "alloc.h"
#include "memoryAlgorithmController.h"
#include "worst.h"
#include "list.h"
#include "hole.h"
#include "cmp.h"


memController_t worstInitMemController(){
	// assign the interfaces functions
	memController_t memController;
	memController.canFit = &worstCanFit;
	memController.addFreeMem = &worstAddFreeMem;
	memController.reserveSize = &worstReserveSize;
	memController.getAvailTotal = &worstGetAvailTotal;
	memController.getNumHoles = &worstGetNumHoles;

	// data we use in this algorithm
	Worst data = (Worst)safe_malloc(sizeof(*((Worst)(memController.data))));
	data->list = newList();
	data->availableTotal = 0;
	memController.data = data;

	return memController;
}

int worstCanFit(void* storage, int size){
	Worst data = (Worst)storage;

	// if there is one hole can fit, definitely can fit
	ListNode n = data->list->head;
	while(n != NULL){
		Hole hole = (Hole)n->data;
		if(getHoleSize(hole) >= size){
			return 1;
		}
		n = n->next;
	}
	return 0;
}

void worstAddFreeMem(void* storage, int fromAddress, int toAddress){
	Worst data = (Worst)storage;
	data->availableTotal += (toAddress - fromAddress);
	Hole hole = newHole(fromAddress, toAddress);
	ListNode ln = list_insert_sorted(data->list, hole, &holeAddress);

	// check the node before and see if they can be combined
	ListNode previous = ln->previous;
	if(previous != NULL){
		Hole prevHole = previous->data;
		if(prevHole->startAddress == hole->endAddress){
			prevHole->startAddress = hole->startAddress;
			list_remove(data->list, ln);
			ln = previous;
			hole = prevHole;
		}
	}

	// check the node after and see if they can be combined
	ListNode next = ln->next;
	if(next != NULL){
		Hole nextHole = next->data;
		if(nextHole->endAddress == hole->startAddress){
			nextHole->endAddress = hole->endAddress;
			list_remove(data->list, ln);
			ln = next;
			hole = nextHole;
		}
	}
}

void worstReserveSize(
		void* storage, int size, int *fromAddress, int *toAddress){
	Worst data = (Worst)storage;
	data->availableTotal -= size;

	ListNode n = data->list->head;
	ListNode justfit = NULL;
	Hole hole, justfitHole;
	while(n != NULL){
		hole = (Hole)n->data;
		justfitHole = (justfit == NULL) ? NULL : (Hole)justfit->data;
		// trying to get a larger hole always
		if((justfit ==  NULL && getHoleSize(hole) >= size)
				|| (justfit != NULL &&
					getHoleSize(hole) >= size &&
					getHoleSize(hole) >= getHoleSize(justfitHole))){
			if(justfit == NULL)
				justfit = n;
			else if(getHoleSize(hole) > getHoleSize(justfitHole))
				justfit = n;
			else if(hole->startAddress > justfitHole->startAddress)
				justfit = n;
		}
		n = n->next;
	}
	// found hole, update start address
	hole = (Hole)justfit->data;
	(*toAddress) = hole->endAddress;
	hole->endAddress -= size;
	(*fromAddress) = hole->endAddress;

	if(getHoleSize(hole) == 0){
		// the hole is fully used up, remove from the list
		list_remove(data->list, justfit);
	}
	return;
}

int worstGetAvailTotal(void* storage){
	Worst data = (Worst)storage;
	return data->availableTotal;
}

int worstGetNumHoles(void* storage){
	Worst data = (Worst)storage;
	return data->list->size;
}
