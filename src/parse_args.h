/*****************************************************************************/
/*                                                                           */
/*          This is a submission for assignment 1 of                         */
/*          COMP30023 Computer Systems                                       */
/*                                                                           */
/*          Author     : Shing Sheung Daniel Ip                              */
/*          Student ID : 723508                                              */
/*          Finish Time: 6th April 2017 15:08                                */
/*                                                                           */
/*     Parser for the arguments                                              */
/*                                                                           */
/*****************************************************************************/

#ifndef PARSE_ARGS

#define PARSE_ARGS

#define FIRST_STR "first"
#define BEST_STR "best"
#define WORST_STR "worst"

#define USG1 "usage: %s [-f file] [-a {algorithm}] [-m memsize] [-q quantum]\n"
#define USG2 "algorithm: {best, worst, worst}\n"

/*
 * constants for memory management algorithm type
 * add more if more algorithms is used,
 * also used to determine the controller in main, so update there as well
 */
typedef enum {
	UNDEFINED,
	FIRST,
	BEST,
	WORST,
} algorithm_t;

/*
 * the return value of the parsed arguments
 */
typedef struct {
	char* filename;
	algorithm_t algorithm;
	int memsize;
	int quantum;
} args_t;

/*
 * parsing the arguments and return it as the struct
 */
args_t parse_args(int argc, char *argv[]);

#endif
