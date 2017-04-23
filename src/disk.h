/*****************************************************************************/
/*                                                                           */
/*          This is a submission for assignment 1 of                         */
/*          COMP30023 Computer Systems                                       */
/*                                                                           */
/*          Author     : Shing Sheung Daniel Ip                              */
/*          Student ID : 723508                                              */
/*          Finish Time: 6th April 2017 15:08                                */
/*                                                                           */
/*     This holds the current processes in disk,                             */
/*     basically try to use as much as we could in memory.h                  */
/*                                                                           */
/*****************************************************************************/

#include "memory.h"
#include "queue.h"

#ifndef DISK

#define DISK

typedef memory_t disk_t;

disk_t init_disk();

Process stayedLongestInDisk(disk_t disk);

QueueNode add2Disk(disk_t *disk, Process p);

void diskRemoveLongest(disk_t *disk);

int isDiskEmpty(disk_t disk);

#endif
