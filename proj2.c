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
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <semaphore.h>
#include "arguments.h"

int main(int argc, char **argv) {
    struct process_parameters parameters;
    if (parse_arguments(&parameters, argc, argv) != 0)
        return 1;

    pid_t pid_hacker = fork();
    if (pid_hacker == 0) {
        //hacker code
        exit(0);

    } else if (pid_hacker == -1) {
        perror(strerror(errno));
        exit(1);

    } else {
        pid_t pid_serf = fork();
        if (pid_serf == 0) {
            //serf code
            exit(0);

        } else if (pid_serf == -1) {
            perror(strerror(errno));
            exit(1);

        } else {
            wait();
        }
    }

    return 0;
}
