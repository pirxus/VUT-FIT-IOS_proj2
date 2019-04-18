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
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <semaphore.h>

#include "resources.h"
#include "generate.h"
#include "arguments.h"

pid_t hacker;
pid_t serf;


int main(int argc, char **argv) {
    /* Get the command line input */
    params_t parameters;
    if (parse_arguments(&parameters, argc, argv) == 1)
        return 1;

    /* Open the log file */
    output_log = fopen("proj2.out", "w");
    if (!output_log) {
        fprintf(stderr, "Error: could not open log file\n");
        return 1;
    }

    pid_t pid;
    if ((pid = fork()) == -1) {
        perror(strerror(errno));
        //destroy();
        fclose(output_log);
        exit(2);

    } else if (pid == 0) {
        gen_hacker(parameters);
        exit(0);

    } else {

        hacker_gen = pid;
        if ((pid = fork()) == -1) {
            perror(strerror(errno));
            //destroy();
            fclose(output_log);
            exit(2);

        } else if (pid == 0) {
            //gen_serf(parameters);
            exit(0);

        } else {
            serf_gen = pid;
        }
    }

    waitpid(hacker_gen, NULL, 0);
    waitpid(serf_gen, NULL, 0);
    fclose(output_log);

    return 0;
}
