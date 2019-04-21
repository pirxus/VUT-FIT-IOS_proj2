/**
 *	@file	resources.c
 *	@author	Simon Sedlacek, xsedla1h
 *	@date	18.4.2019
 *	@brief  This module contains functions that initialize the necessary
 *	resources for the program as well as release them
 *	@note	IOS 2019 - second assignment - River Crossing Problem
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>

#include "resources.h"
#include "arguments.h"

void init_resources(params_t params) {

    srand(time(NULL));

    /* Open the log file */
    output_log = fopen(LOG_FILE, "w");
    if (!output_log) {
        fprintf(stderr, "Error: could not open log file\n");
        exit(1);
    }

    /* Prevent output buffering */
    setbuf(output_log, NULL);

    /* Shared memory initialization */
    if (((message_counter_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666)) == -1) ||
        ((hacker_count_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666)) == -1) ||
        ((serf_count_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666)) == -1) ||
        ((hacker_board_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666)) == -1) ||
        ((serf_board_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666)) == -1)) {

        perror("failed to obtain shared memory");
        destroy_resources();
        exit(1);
    }

    if (((message_counter = shmat(message_counter_id, NULL, 0)) == NULL) || 
        ((hacker_count = shmat(hacker_count_id, NULL, 0)) == NULL) ||
        ((serf_count = shmat(serf_count_id, NULL, 0)) == NULL) || 
        ((hacker_board = shmat(hacker_board_id, NULL, 0)) == NULL) ||
        ((serf_board = shmat(serf_board_id, NULL, 0)) == NULL)) {

        perror("failed to init shared memory");
        destroy_resources();
        exit(1);
    }

    /* Initialize the shared variables */
    *message_counter = 0;
    *hacker_count = 0;
    *serf_count = 0;
    *hacker_board = 0;
    *serf_board = 0;


    /* Semaphore initialization */
    if (((mutex = sem_open(semMUTEX, O_CREAT | O_EXCL, 0666, 1)) == SEM_FAILED) ||
        ((try_to_board = sem_open(semTRY_TO_BOARD, O_CREAT | O_EXCL, 0666, 1)) == SEM_FAILED) ||
        ((board_limit = sem_open(semBOARD_LIMIT, O_CREAT | O_EXCL, 0666, 0)) == SEM_FAILED) ||
        ((hacker_queue = sem_open(semHACKER, O_CREAT | O_EXCL, 0666, 0)) == SEM_FAILED) ||
        ((serf_queue = sem_open(semSERF, O_CREAT | O_EXCL, 0666, 0)) == SEM_FAILED) ||
        ((dock = sem_open(semDOCK, O_CREAT | O_EXCL, 0666, params.C)) == SEM_FAILED) ||
        ((log_write = sem_open(semLOG_WRITE, O_CREAT | O_EXCL, 0666, 1)) == SEM_FAILED) ||
        ((counter = sem_open(semCOUNTER, O_CREAT | O_EXCL, 0666, 1)) == SEM_FAILED) ||
        ((captain_exit = sem_open(semCAPTAIN, O_CREAT | O_EXCL, 0666, 0)) == SEM_FAILED)) {

        perror("failed to open semaphore");
        destroy_resources();
        exit(1);
    }
}

void destroy_resources() {
    sem_close(mutex);
    sem_close(try_to_board);
    sem_close(board_limit);
    sem_close(hacker_queue);
    sem_close(serf_queue);
    sem_close(dock);
    sem_close(log_write);
    sem_close(counter);
    sem_close(captain_exit);

    sem_unlink(semMUTEX);
    sem_unlink(semTRY_TO_BOARD);
    sem_unlink(semBOARD_LIMIT);
    sem_unlink(semHACKER);
    sem_unlink(semSERF);
    sem_unlink(semDOCK);
    sem_unlink(semLOG_WRITE);
    sem_unlink(semCOUNTER);
    sem_unlink(semCAPTAIN);

    shmctl(message_counter_id, IPC_RMID, NULL);
    shmctl(hacker_count_id, IPC_RMID, NULL);
    shmctl(serf_count_id, IPC_RMID, NULL);
    shmctl(hacker_board_id, IPC_RMID, NULL);
    shmctl(serf_board_id, IPC_RMID, NULL);

    fclose(output_log);
}
