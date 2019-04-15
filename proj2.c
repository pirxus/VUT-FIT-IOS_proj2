/**
 *	@file	proj2.c
 *	@author	Simon Sedlacek, xsedla1h
 *	@date	5.4.2019
 *	@brief  IOS 2019 - second assignment - River Crossing Problem
 *	@note	
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <semaphore.h>
#include "arguments.h"

pid_t hacker_gen;
pid_t serf_gen;

pid_t hacker;
pid_t serf;

FILE *output_log;

void gen_hacker(params_t parameters);
void gen_serf(params_t parameters);

void hacker_process(params_t parameters, unsigned id);
void serf_process(params_t parameters, unsigned id);

int board();
int row();

int init();
int destroy();

int main(int argc, char **argv) {
    params_t parameters;
    if (parse_arguments(&parameters, argc, argv) == 1)
        return 1;

    pid_t pid = fork();
    if (pid == 0) {
        gen_hacker(parameters);
        exit(0);

    } else if (pid == -1) {
        perror(strerror(errno));
        //destroy();
        exit(2);

    } else {

        hacker_gen = pid;
        pid = fork();
        if (pid == 0) {
            //gen_serf(parameters);
            exit(0);

        } else if (pid == -1) {
            perror(strerror(errno));
            //destroy();
            exit(2);

        } else {
            serf_gen = pid;
        }
    }

    waitpid(hacker_gen, NULL, 0);
    waitpid(serf_gen, NULL, 0);

    return 0;
}


void gen_hacker(params_t parameters) {
    /* Generate hacker processes */
    for (unsigned i = 1; i <= parameters.P; i++) {

        if (parameters.H != 0)
            usleep(rand() % (1000 * parameters.H));

        pid_t pid = fork();

        if (pid == 0) {
            hacker_process(parameters, i);

        } else if (pid == -1) {
            //destroy();
            exit(1);
        }
    }
    
    for (unsigned i = 1; i <= parameters.P; i++) {
        wait(NULL);
    }
}

void hacker_process(params_t parameters, unsigned id) {
    printf("hacker no.: %u\n", id);
    exit(0);
}
