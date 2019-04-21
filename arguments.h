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
 * @brief This structure stores the loaded program arguments
 *
 * @var P Number of processes in each category which is to be generated
 * @var H The maximum amount of time in ms after which a new hacker is generated
 * @var S The maximum amount of time in ms after which a new serf is generated
 * @var R The maximum amount of time in ms for which the journey can last
 * @var W If the dock is full, the process waits <20, W> ms before returning
 * @var C The capacity of the dock
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
 *
 * @param parameters A structure for storing the loaded information
 * @param argc The number of program arguments
 * @param argv Program arguments
 */
int parse_arguments(struct process_parameters *parameters, int argc, char **argv);

#endif
