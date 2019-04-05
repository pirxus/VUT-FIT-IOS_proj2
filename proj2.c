/**
 *	@file	proj2.c
 *	@author	Simon Sedlacek, xsedla1h
 *	@date	5.4.2019
 *	@brief  IOS 2019 - second assignment - River Crossing Problem
 *	@note	
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "arguments.h"

int main(int argc, char **argv) {
    struct process_parameters parameters;
    if (parse_arguments(&parameters, argc, argv) != 0) {
        return 1;
    }

    return 0;
}
