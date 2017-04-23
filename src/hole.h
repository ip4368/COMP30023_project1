/*****************************************************************************/
/*                                                                           */
/*          This is a submission for assignment 1 of                         */
/*          COMP30023 Computer Systems                                       */
/*                                                                           */
/*          Author     : Shing Sheung Daniel Ip                              */
/*          Student ID : 723508                                              */
/*          Finish Time: 6th April 2017 15:08                                */
/*                                                                           */
/*     Hole compoent                                                         */
/*                                                                           */
/*****************************************************************************/

#ifndef HOLE

#define HOLE


typedef struct{
	int startAddress, endAddress;
}*Hole;

/*
 * make a new structure representing the hole
 */
Hole newHole(int startAddress, int endAddress);

/*
 * get the size of the hole
 */
int getHoleSize(Hole hole);

#endif
