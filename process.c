/**
 *	@file	process.c
 *	@author	Simon Sedlacek, xsedla1h
 *	@date	18.4.2019
 *	@brief  
 *	@note	IOS 2019 - second assignment - River Crossing Problem
 */

#include <stdlib.h>
#include "process.h"
#include "arguments.h"
#include "resources.h"

void hacker_process(params_t parameters, unsigned id) {
    fprintf(output_log, "hacker no.: %u\n", id);
    exit(0);
}

void serf_process(params_t parameters, unsigned id) {
}

void board(int process, unsigned id) {
    if (process == HACKER) {
        fprintf(output_log, "HACK\n");
    } else {
        fprintf(output_log, "SERF\n");
    }
}

void row() {
}
