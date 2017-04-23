/*****************************************************************************/
/*                                                                           */
/*          This is a submission for assignment 1 of                         */
/*          COMP30023 Computer Systems                                       */
/*                                                                           */
/*          Author     : Shing Sheung Daniel Ip                              */
/*          Student ID : 723508                                              */
/*          Finish Time: 6th April 2017 15:08                                */
/*                                                                           */
/*   Description: this is defining an interface                              */
/*   that a memory scheduling algorthms should have,                         */
/*   Any scheduling algorithms implemented according to this interface       */
/*   Shoud work on the whole program without updating a lot of code in main  */
/*                                                                           */
/*****************************************************************************/

#ifndef MEMORY_CONTROLLER

#define MEMORY_CONTROLLER

typedef struct{
	/*
	 * return 1 if there is at least 1 hole fit the size
	 * void *: data that the interface can use
	 * int: size
	 */
	int (*canFit)(void*, int);

	/*
	 * add some memory (hold, should merge with existing if possible)
	 * void *: data that the interface can use
	 */
	void (*addFreeMem)(void*, int, int);

	/*
	 * reserve the a memory with size
	 * void *: data that the interface can use
	 * int: size
	 * int *: start address of allocated memory
	 * int *: end address of allocated memory
	 */
	void (*reserveSize)(void*, int, int*, int*);

	/*
	 * the total size of available memory (sum of all the holes)
	 * void *: data that the interface can use
	 */
	int (*getAvailTotal)(void*);

	/*
	 * the number of holes currently exists
	 * void *: data that the interface can use
	 */
	int (*getNumHoles)(void*);
	void *data;
}memController_t;

#endif
