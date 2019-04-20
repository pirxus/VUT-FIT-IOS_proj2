/**
 *	@file	resources.c
 *	@author	Simon Sedlacek, xsedla1h
 *	@date	18.4.2019
 *	@brief  
 *	@note	IOS 2019 - second assignment - River Crossing Problem
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>

#include "resources.h"

void init_resources() {
    output_log = fopen(LOG_FILE, "w");
    if (!output_log) {
        fprintf(stderr, "Error: could not open log file\n");
        exit(1);
    }

    setbuf(output_log, NULL);

    if ((shared_counter_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666)) == -1) {
        // handle error
    }

    if ((shared_counter = shmat(shared_counter_id, NULL, 0)) == NULL) {
        // handle error
    }

    if ((mutex = sem_open(semMUTEX, O_CREAT | O_EXCL, 0666, 1)) == SEM_FAILED) {
        // handle error
    }

    if ((counter = sem_open(semCOUNTER, O_CREAT | O_EXCL, 0666, 1)) == SEM_FAILED) {
        // handle error
    }

    if ((log_write = sem_open(semLOG_WRITE, O_CREAT | O_EXCL, 0666, 1)) == SEM_FAILED) {
        // handle error
    }


}

void destroy_resources() {
    sem_close(mutex);
    sem_unlink(semMUTEX);

    sem_close(barrier);
    sem_unlink(semBARRIER);

    sem_close(hacker_queue);
    sem_unlink(semHACKER);

    sem_close(serf_queue);
    sem_unlink(semSERF);

    sem_close(log_write);
    sem_unlink(semLOG_WRITE);

    sem_close(counter);
    sem_unlink(semCOUNTER);

    shmctl(shared_counter_id, IPC_RMID, NULL);

    fclose(output_log);

}
