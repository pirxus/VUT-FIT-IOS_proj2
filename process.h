/**
 *	@file	process.h
 *	@author	Simon Sedlacek, xsedla1h
 *	@date	18.4.2019
 *	@brief  
 *	@note	IOS 2019 - second assignment - River Crossing Problem
 */

#ifndef PROCESS_HEADER
#define PROCESS_HEADER

#include "arguments.h"

#define HACKER 0
#define SERF 1

void hacker_process(params_t parameters, unsigned id);

void serf_process(params_t parameters, unsigned id);

void board(int process, unsigned id);

void row();

#endif
