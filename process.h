/**
 *	@file	process.h
 *	@author	Simon Sedlacek, xsedla1h
 *	@date	18.4.2019
 *	@brief  
 *	@note	IOS 2019 - second assignment - River Crossing Problem
 */

#ifndef PROCESS_HEADER
#define PROCESS_HEADER

#include <stdbool.h>

#include "arguments.h"

#define HACK "HACK"
#define SERF "SERF"

void hacker_process(params_t parameters, unsigned id);

void serf_process(params_t parameters, unsigned id);

void row(const char *name, params_t parameters, unsigned id);

void board(const char *name, unsigned id);

void print_status(const char *name, const char *message,
        bool pass_count, bool inc, unsigned id);

#endif
