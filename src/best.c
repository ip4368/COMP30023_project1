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
#include "best.h"
#include "list.h"
#include "hole.h"
#include "cmp.h"


memController_t bestInitMemController(){
	// assign the interfaces functions
	memController_t memController;
	memController.canFit = &bestCanFit;
	memController.addFreeMem = &bestAddFreeMem;
	memController.reserveSize = &bestReserveSize;
	memController.getAvailTotal = &bestGetAvailTotal;
	memController.getNumHoles = &bestGetNumHoles;

	// data we use in this algorithm
	Best data = (Best)safe_malloc(sizeof(*((Best)(memController.data))));
	data->list = newList();
	data->availableTotal = 0;
	memController.data = data;

	return memController;
}

int bestCanFit(void* storage, int size){
	Best data = (Best)storage;

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

void bestAddFreeMem(void* storage, int fromAddress, int toAddress){
	Best data = (Best)storage;
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

void bestReserveSize(
		void* storage, int size, int *fromAddress, int *toAddress){
	Best data = (Best)storage;
	data->availableTotal -= size;

	ListNode n = data->list->head;
	ListNode justfit = NULL;
	Hole hole, justfitHole;
	while(n != NULL){
		hole = (Hole)n->data;
		justfitHole = (justfit == NULL) ? NULL : (Hole)justfit->data;
		// trying to get a smaller hole that still fit
		if((justfit ==  NULL && getHoleSize(hole) >= size)
				|| (justfit != NULL &&
					getHoleSize(hole) >= size &&
					getHoleSize(hole) <= getHoleSize(justfitHole))){
			if(justfit == NULL)
				justfit = n;
			else if(getHoleSize(hole) < getHoleSize(justfitHole))
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

int bestGetAvailTotal(void* storage){
	Best data = (Best)storage;
	return data->availableTotal;
}

int bestGetNumHoles(void* storage){
	Best data = (Best)storage;
	return data->list->size;
}
