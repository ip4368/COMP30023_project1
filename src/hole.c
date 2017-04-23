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

#include "hole.h"
#include "alloc.h"

Hole newHole(int startAddress, int endAddress){
	Hole hole = (Hole)safe_malloc(sizeof(*hole));
	hole->startAddress = startAddress;
	hole->endAddress = endAddress;
	return hole;
}

int getHoleSize(Hole hole){
	return hole->endAddress - hole->startAddress;
}
