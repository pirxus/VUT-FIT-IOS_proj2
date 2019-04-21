/**
 *	@file	generate.h
 *	@author	Simon Sedlacek, xsedla1h
 *	@date	18.4.2019
 *	@brief  A header file for generate.c
 *	@note	IOS 2019 - second assignment - River Crossing Problem
 */

#ifndef GENERATE_HEADER
#define GENERATE_HEADER

#include "arguments.h"

/**
 * @brief Generates hacker processes
 *
 * @param parameters A structure that holds the program arguments
 */
void gen_hacker(params_t parameters);

/**
 * @brief Generates serf processes
 *
 * @param parameters A structure that holds the program arguments
 */
void gen_serf(params_t parameters);

#endif
