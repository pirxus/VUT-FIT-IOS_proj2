/**
 *	@file	proj2.c
 *	@author	Simon Sedlacek, xsedla1h
 *	@date	5.4.2019
 *	@brief  
 *	@note	IOS 2019 - second assignment - River Crossing Problem
 */

#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <semaphore.h>

#include "resources.h"
#include "generate.h"
#include "arguments.h"

/* Hacker and serf pid variables */
pid_t hacker;
pid_t serf;


int main(int argc, char **argv) {
    /* Get the command line input */
    params_t parameters;
    if (parse_arguments(&parameters, argc, argv) == 1)
        exit(1);

    /* Init all the necessary resources */
    init_resources();


    /* Fork the hacker generator */
    pid_t pid;
    if ((pid = fork()) == -1) {
        fprintf(stderr, "Error: could not fork hacker_gen\n");
        //destroy_resources();
        exit(2);

    } else if (pid == 0) {
        gen_hacker(parameters);

    } else {

        /* Fork the serf generator */
        hacker_gen = pid;
        if ((pid = fork()) == -1) {
            fprintf(stderr, "Error: could not fork serf_gen\n");
            //destroy_resources();
            exit(2);

        } else if (pid == 0) {
            //gen_serf(parameters);

        } else {
            serf_gen = pid;
        }
    }

    waitpid(hacker_gen, NULL, 0);
    waitpid(serf_gen, NULL, 0);
    destroy_resources();

    return 0;
}
