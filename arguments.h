/**
 *	@file	arguments.h
 *	@author	Simon Sedlacek, xsedla1h
 *	@date	5.4.2019
 *	@brief  A header file for a module that takes care of parsing
 *	the arguments of the program.
 *	@note	
 */

#ifndef ARGUMENTS_HEADER
#define ARGUMENTS_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief
 */
struct process_parameters {
    int process_count;
    int hacker_time;
    int serf_time;
    int run_time;
    int w;
    int capacity;
};

/**
 * @brief
 */
int parse_arguments(struct process_parameters *parameters, int argc, char **argv);

#endif
