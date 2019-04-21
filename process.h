/**
 *	@file	process.h
 *	@author	Simon Sedlacek, xsedla1h
 *	@date	18.4.2019
 *	@brief  A header file for process.c
 *	@note	IOS 2019 - second assignment - River Crossing Problem
 */

#ifndef PROCESS_HEADER
#define PROCESS_HEADER

#include <stdbool.h>

#include "arguments.h"

#define HACK "HACK"
#define SERF "SERF"

/**
 * @brief Represents the hacker process
 *
 * @param params A structure holding the command line arguments passed
 * to the program
 * @param id An id of the process, unique within its species
 */
void hacker_process(params_t parameters, unsigned id);

/**
 * @brief Represents the serf process
 *
 * @param params A structure holding the command line arguments passed
 * to the program
 * @param id An id of the process, unique within its species
 */
void serf_process(params_t parameters, unsigned id);

/**
 * @brief Represents the captain taking control of the journey
 *
 * @param name A string literal defining the species of the process - HACK or SERF
 * @param params A structure holding the command line arguments passed
 * to the program
 * @param id An id of the process, unique within its species
 */
void row(const char *name, params_t parameters, unsigned id);

/**
 * @brief Represents the boarding and the journey of the regular crew members
 *
 * @param name A string literal defining the species of the process - HACK or SERF
 * @param id An id of the process, unique within its species
 */
void board(const char *name, unsigned id);

/**
 * @brief Prints an update message for the process
 *
 * @param name A string literal defining the species of the process - HACK or SERF
 * @param message A string literal defining the main part of the message this
 * funcion should print
 * @param pass_count Indicated whether the function should add the current state of the
 * dock to the message
 * @param inc Indicates whether the function should also increment the hacker_count
 * or the serf_count variable according to the parameter 'name'
 * @param id An id of the process, unique within its species
 */
void print_status(const char *name, const char *message,
        bool pass_count, bool inc, unsigned id);

#endif
