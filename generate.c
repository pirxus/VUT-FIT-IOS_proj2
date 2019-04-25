/**
 *	@file	generate.c
 *	@author	Simon Sedlacek, xsedla1h
 *	@date	18.4.2019
 *	@brief  Functions in this module generate the hacker and serf processes
 *	@note	IOS 2019 - second assignment - River Crossing Problem
 */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#include "generate.h"
#include "resources.h"
#include "process.h"


void gen_hacker(params_t parameters) {
    srand(time(NULL));
    pid_t pid;

    /* Generate hacker processes */
    for (unsigned i = 1; i <= parameters.P; i++) {

        if (parameters.H != 0)
            usleep(1000 * (rand() % (parameters.H + 1)));

        pid = fork();

        if (pid == 0) {
            hacker_process(parameters, i);

        } else if (pid == -1) {
            perror("fork_hacker");

            /* Wait for all the children to end */
            for (unsigned j = 0; j < i; j++)
                wait(NULL);

            exit(2);
        }
    }
    
    /* Wait for all the children to end */
    for (unsigned i = 0; i < parameters.P; i++)
        wait(NULL);
    
    exit(0);
}

void gen_serf(params_t parameters) {
    srand(time(NULL));
    pid_t pid;

    /* Generate serf processes */
    for (unsigned i = 1; i <= parameters.P; i++) {

        if (parameters.H != 0)
            usleep(1000 * (rand() % (parameters.S + 1)));

        pid = fork();

        if (pid == 0) {
            serf_process(parameters, i);

        } else if (pid == -1) {
            perror("fork_serf");

            /* Wait for all the children to end */
            for (unsigned j = 0; j < i; j++)
                wait(NULL);
            exit(2);
        }
    }

    /* Wait for all the children to end */
    for (unsigned i = 0; i < parameters.P; i++)
        wait(NULL);
    
    exit(0);
}
