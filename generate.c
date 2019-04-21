/**
 *	@file	generate.c
 *	@author	Simon Sedlacek, xsedla1h
 *	@date	18.4.2019
 *	@brief  
 *	@note	IOS 2019 - second assignment - River Crossing Problem
 */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "generate.h"
#include "resources.h"
#include "process.h"

void gen_hacker(params_t parameters) {
    /* Generate hacker processes */
    for (unsigned i = 1; i <= parameters.P; i++) {

        if (parameters.H != 0)
            usleep(1000 * (rand() % (parameters.H + 1)));

        pid_t pid = fork();

        if (pid == 0) {
            hacker_process(parameters, i);

        } else if (pid == -1) {
            fprintf(stderr, "Error: could not fork hacker process\n");

            /* Wait for all the children to end */
            for (unsigned j = 0; j < i; j++)
                wait(NULL);

            exit(1);
        }
    }
    
    /* Wait for all the children to end */
    for (unsigned i = 0; i < parameters.P; i++)
        wait(NULL);
    
    exit(0);
}

void gen_serf(params_t parameters) {
    /* Generate serf processes */
    for (unsigned i = 1; i <= parameters.P; i++) {

        if (parameters.H != 0)
            usleep(1000 * (rand() % (parameters.S + 1)));

        pid_t pid = fork();

        if (pid == 0) {
            serf_process(parameters, i);

        } else if (pid == -1) {
            fprintf(stderr, "Error: could not fork serf process\n");

            /* Wait for all the children to end */
            for (unsigned j = 0; j < i; j++)
                wait(NULL);

            exit(1);
        }
    }

    /* Wait for all the children to end */
    for (unsigned i = 0; i < parameters.P; i++)
        wait(NULL);
    
    exit(0);
}
