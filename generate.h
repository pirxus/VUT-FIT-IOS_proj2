/**
 *	@file	generate.h
 *	@author	Simon Sedlacek, xsedla1h
 *	@date	18.4.2019
 *	@brief  
 *	@note	IOS 2019 - second assignment - River Crossing Problem
 */

#ifndef GENERATE_HEADER
#define GENERATE_HEADER

#include "arguments.h"
#include <time.h>

/**
 * @brief Generates hacker processes
 */
void gen_hacker(params_t parameters);

/**
 * @brief Generates serf processes
 */
void gen_serf(params_t parameters);

#endif
