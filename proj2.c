/**
 *	@file	proj2.c
 *	@author	Simon Sedlacek, xsedla1h
 *	@date	5.4.2019
 *	@brief  The main source file for this project
 *	@note	IOS 2019 - second assignment - River Crossing Problem
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#include "resources.h"
#include "generate.h"
#include "arguments.h"


int main(int argc, char **argv) {

    /* Get the command line input */
    params_t parameters;
    if (parse_arguments(&parameters, argc, argv) == 1)
        exit(1);

    /* Init all the necessary resources */
    init_resources(parameters);

    /* Fork the hacker generator */
    pid_t hacker, serf;
    if ((hacker = fork()) == -1) {
        perror("gen_hacker fork");
        destroy_resources();
        exit(2);

    } else if (hacker == 0) {
        gen_hacker(parameters);

    } else {

        /* Fork the serf generator */
        if ((serf = fork()) == -1) {
            perror("gen_serf fork");
            destroy_resources();
            exit(2);

        } else if (serf == 0) {
            gen_serf(parameters);
        }
    }

    waitpid(hacker, NULL, 0);
    waitpid(serf, NULL, 0);
    destroy_resources();

    return 0;
}
