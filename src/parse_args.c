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
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "parse_args.h"

extern  int     optind;
extern  char    *optarg;

/*****************************************************************************/
/*
 * Helper prototype
 */

static void parse_error(char *prog_name, char option);
static void insufficient_args(char *prog_name);

/*****************************************************************************/

args_t parse_args(int argc, char *argv[]){
	char input;
	args_t parsed_args = {NULL, UNDEFINED, -1, -1};
	while((input = getopt(argc, argv, "f:a:m:q:")) != EOF){
		switch(input){
			case 'f':
				parsed_args.filename = optarg;
 				break;
			
			case 'a':
				// set the value of size (int value) based on optarg
				if(strcmp(optarg, FIRST_STR) == 0)
					parsed_args.algorithm = FIRST;
				else if(strcmp(optarg, BEST_STR) == 0)
					parsed_args.algorithm = BEST;
				else if(strcmp(optarg, WORST_STR) == 0)
					parsed_args.algorithm = WORST;
				else
					parse_error(argv[0], input);
				break;

			case 'm':
				parsed_args.memsize = atoi(optarg);
				break;

			case 'q':
				parsed_args.quantum = atoi(optarg);
				break;

			default:
				parse_error(argv[0], input);
				break;
		}
	}
	if(parsed_args.filename == NULL ||
		parsed_args.algorithm == UNDEFINED ||
		parsed_args.memsize == -1 ||
		parsed_args.quantum == -1)
		insufficient_args(argv[0]);
	return parsed_args;
}

/*****************************************************************************/
/*
 * Helper functions
 */

static void parse_error(char *prog_name, char option){
	fprintf(stderr, "%s: illegal option -- %c\n", prog_name, option);
	fprintf(stderr, USG1, prog_name);
	fprintf(stderr, USG2);
	exit(EXIT_FAILURE);
}

static void insufficient_args(char *prog_name){
	fprintf(stderr, "%s: insufficient arguments\n", prog_name);
	fprintf(stderr, USG1, prog_name);
	fprintf(stderr, USG2);
	exit(EXIT_FAILURE);
}
