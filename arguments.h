/**
 *	@file	arguments.h
 *	@author	Simon Sedlacek, xsedla1h
 *	@date	5.4.2019
 *	@brief  A header file for a module that takes care of parsing
 *	the arguments of the program.
 *	@note	IOS 2019 - second assignment - River Crossing Problem
 */

#ifndef ARGUMENTS_HEADER
#define ARGUMENTS_HEADER

/**
 * @brief This structure represents the program parameters
 *
 * @var P
 * @var H
 * @var S
 * @var R
 * @var W
 * @var C
 */
typedef struct process_parameters {
    int P;
    int H;
    int S;
    int R;
    int W;
    int C;
} params_t;

/**
 * @brief Parses program arguments and stores their values
 */
int parse_arguments(struct process_parameters *parameters, int argc, char **argv);

#endif
