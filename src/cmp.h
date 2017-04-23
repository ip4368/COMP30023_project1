/*****************************************************************************/
/*                                                                           */
/*          This is a submission for assignment 1 of                         */
/*          COMP30023 Computer Systems                                       */
/*                                                                           */
/*          Author     : Shing Sheung Daniel Ip                              */
/*          Student ID : 723508                                              */
/*          Finish Time: 6th April 2017 15:08                                */
/*                                                                           */
/*     Comparing functions library                                           */
/*                                                                           */
/*****************************************************************************/

#ifndef CMP

#define CMP

/*
 * this could be used to sort by the hole address, smaller address is smaller
 */
int holeAddress(void *data1, void *data2);

/*
 * this could be used to sort by the process id,
 * smaller id is greater (proritised)
 * in pis in queue, is just a queue node holding a pointer to processInStorage
 */
int processId(void *data1, void *data2);
int processIdInPisInQueue(void *data1, void *data2);

#endif