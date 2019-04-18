/**
 *	@file	generate.c
 *	@author	Simon Sedlacek, xsedla1h
 *	@date	18.4.2019
 *	@brief  
 *	@note	IOS 2019 - second assignment - River Crossing Problem
 */

#include <time.h>
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

void gen_serf(params_t parameters) {

}
