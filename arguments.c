/**
 *	@file	arguments.c
 *	@author	Simon Sedlacek, xsedla1h
 *	@date	5.4.2019
 *	@brief  A module containing all the needed functions for parsing
 *	the command line arguments.
 *	@note   IOS 2019 - second assignment - River Crossing Problem
 */

#include "arguments.h"

int parse_arguments(struct process_parameters *parameters, int argc, char **argv) {
    if (argc != 7) {
        fprintf(stderr, "Error: invalid program argument count\n");
        return 1;
    }

    char *endptr = NULL;

    /* Check if every argument is an integer */
    parameters->P = strtoul(argv[1], &endptr, 10);
    if (strcmp(endptr, "") || argv[1][0] == '-' || argv[1][0] == '+') {
        fprintf(stderr, "Error: invalid 'P' program argument format\n");
        return 1;
    }

    parameters->H = strtoul(argv[2], &endptr, 10);
    if (strcmp(endptr, "") || argv[2][0] == '-' || argv[2][0] == '+') {
        fprintf(stderr, "Error: invalid 'H' program argument format\n");
        return 1;
    }
    
    parameters->S = strtoul(argv[3], &endptr, 10);
    if (strcmp(endptr, "") || argv[3][0] == '-' || argv[3][0] == '+') {
        fprintf(stderr, "Error: invalid 'S' program argument format\n");
        return 1;
    }

    parameters->R = strtoul(argv[4], &endptr, 10);
    if (strcmp(endptr, "") || argv[4][0] == '-' || argv[4][0] == '+') {
        fprintf(stderr, "Error: invalid 'R' program argument format\n");
        return 1;
    }

    parameters->W = strtoul(argv[5], &endptr, 10);
    if (strcmp(endptr, "") || argv[5][0] == '-' || argv[5][0] == '+') {
        fprintf(stderr, "Error: invalid 'W' program argument format\n");
        return 1;
    }

    parameters->C = strtoul(argv[6], &endptr, 10);
    if (strcmp(endptr, "") || argv[6][0] == '-' || argv[6][0] == '+') {
        fprintf(stderr, "Error: invalid 'C' program argument format\n");
        return 1;
    }

    /* Check if every loaded parameter falls within correct limits. */
    if (parameters->P < 2 || parameters->P % 2 != 0) {
        fprintf(stderr, "Error: 'P' has to be even and bigger or equal to 2\n");
        return 1;
    }
    if (parameters->H > 2000) {
        fprintf(stderr, "Error: 'H' has to be bigger or equal to 2000\n");
        return 1;
    }
    if (parameters->S > 2000) {
        fprintf(stderr, "Error: 'S' has to be bigger or equal to 2000\n");
        return 1;
    }
    if (parameters->R > 2000) {
        fprintf(stderr, "Error: 'R' has to be bigger or equal to 2000\n");
        return 1;
    }
    if (parameters->W < 20 || parameters->W > 2000) {
        fprintf(stderr, "Error: 'W' has to be in range <20, 2000>\n");
        return 1;
    }
    if (parameters->C < 5) {
        fprintf(stderr, "Error: 'C' has to be bigger or equal to 5\n");
        return 1;
    }

    return 0;
}
