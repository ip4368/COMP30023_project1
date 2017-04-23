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
#include <stdlib.h>
#include "alloc.h"


/*****************************************************************************/
/*
 * Helper prototype
 */

static void Exception();

/*****************************************************************************/

void* safe_malloc(size_t size){
	void *ptr = malloc(size);
	if(ptr == NULL)
		Exception();
	return ptr;
}

void* safe_realloc(void *ptr, size_t size){
	ptr = realloc(ptr, size);
	if(ptr == NULL)
		Exception();
	return ptr;
}

/*****************************************************************************/
/*
 * Helper functions
 */

static void Exception(){
	fprintf(stderr, MEMORY_FAILURE_MSG);
	exit(EXIT_FAILURE);
}
