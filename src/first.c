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
#include "first.h"
#include "list.h"
#include "hole.h"
#include "cmp.h"


memController_t firstInitMemController(){
	// assign the interfaces functions
	memController_t memController;
	memController.canFit = &firstCanFit;
	memController.addFreeMem = &firstAddFreeMem;
	memController.reserveSize = &firstReserveSize;
	memController.getAvailTotal = &firstGetAvailTotal;
	memController.getNumHoles = &firstGetNumHoles;

	// data we use in this algorithm
	First data = (First)safe_malloc(sizeof(*((First)(memController.data))));
	data->list = newList();
	data->availableTotal = 0;
	memController.data = data;

	return memController;
}

int firstCanFit(void* storage, int size){
	First data = (First)storage;

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

void firstAddFreeMem(void* storage, int fromAddress, int toAddress){
	First data = (First)storage;
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

void firstReserveSize(
		void* storage, int size, int *fromAddress, int *toAddress){
	First data = (First)storage;
	data->availableTotal -= size;

	ListNode n = data->list->head;
	while(n != NULL){
		Hole hole = (Hole)n->data;
		if(getHoleSize(hole) >= size){
			// found hole, update start address
			(*toAddress) = hole->endAddress;
			hole->endAddress -= size;
			(*fromAddress) = hole->endAddress;

			if(getHoleSize(hole) == 0){
				// the hole is fully used up, remove from the list
				list_remove(data->list, n);
			}
			return;
		}
		n = n->next;
	}
	return;
}

int firstGetAvailTotal(void* storage){
	First data = (First)storage;
	return data->availableTotal;
}

int firstGetNumHoles(void* storage){
	First data = (First)storage;
	return data->list->size;
}
