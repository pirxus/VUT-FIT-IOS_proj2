/**
 *	@file	process.c
 *	@author	Simon Sedlacek, xsedla1h
 *	@date	18.4.2019
 *	@brief  
 *	@note	IOS 2019 - second assignment - River Crossing Problem
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "process.h"
#include "arguments.h"
#include "resources.h"

void hacker_process(params_t parameters, unsigned id) {
    sem_wait(log_write);
    fprintf(output_log, "%d      : HACK %d      : starts\n",
            ++(*counter), id);
    sem_post(log_write);


    /* Passenger tries to enter the dock */
    while (sem_trywait(dock) == -1) {
        sem_wait(log_write);
        sem_wait(counter_sem);
        fprintf(output_log, "%d      : HACK %d      : leaves queue   : %d  : %d\n",
                ++(*counter), id, *hacker_count, *serf_count);
        sem_post(counter_sem);
        sem_post(log_write);

        /* Passenger leaves the queue for some time and then comes back */
        usleep(rand() % ((1000 * parameters.W) + 1));

        sem_wait(log_write);
        fprintf(output_log, "%d      : HACK %d      : is back\n",
                ++(*counter), id);
        sem_post(log_write);
    }

    sem_wait(log_write);
    sem_wait(counter_sem);
    fprintf(output_log, "%d      : HACK %d      : waits   : %d  : %d\n",
            ++(*counter), id, ++(*hacker_count), *serf_count);
    sem_post(counter_sem);
    sem_post(log_write);

    bool captain = false;

    /* Check for valid passenger combinations, otherwise, get in the queue */
    sem_wait(mutex);
    *hacker_board += 1;

    sem_wait(counter_sem);
    if (*hacker_board == 4) {

        sem_post(hacker_queue);
        sem_post(hacker_queue);
        sem_post(hacker_queue);
        sem_post(hacker_queue);

        *hacker_board = 0;
        *hacker_count -= 4;
        captain = true;

    } else if (*hacker_board == 2 && *serf_board >= 2) {

        sem_post(hacker_queue);
        sem_post(hacker_queue);
        sem_post(serf_queue);
        sem_post(serf_queue);

        *hacker_board = 0;
        *serf_board -= 2;
        *hacker_count -= 2;
        *serf_count -= 2;
        captain = true;

    } else {
        sem_post(mutex);
    }

    sem_post(counter_sem);

    sem_wait(hacker_queue);


    if (!captain) {
        sem_wait(barrier);

        sem_wait(log_write);
        sem_wait(counter_sem);
        fprintf(output_log, "%d      : HACK %d      : member exits   : %d  : %d\n",
                ++(*counter), id, *hacker_count, *serf_count);
        sem_post(counter_sem);
        sem_post(log_write);

        sem_post(captain_exit);

    } else {
        sem_wait(log_write);
        sem_wait(counter_sem);
        fprintf(output_log, "%d      : HACK %d      : boards   : %d  : %d\n",
                ++(*counter), id, *hacker_count, *serf_count);
        sem_post(counter_sem);
        sem_post(log_write);

        row();

        /* Captain exits */
        sem_wait(log_write);
        sem_wait(counter_sem);
        fprintf(output_log, "%d      : HACK %d      : captain exits   : %d  : %d\n",
                ++(*counter), id, *hacker_count, *serf_count);
        sem_post(counter_sem);
        sem_post(log_write);

        sem_post(mutex);
    }

    sem_post(dock);
    exit(0);
}

void serf_process(params_t parameters, unsigned id) {
    sem_wait(log_write);
    fprintf(output_log, "%d      : SERF %d      : starts\n",
            ++(*counter), id);
    sem_post(log_write);


    /* Passenger tries to enter the dock */
    while (sem_trywait(dock) == -1) {
        sem_wait(log_write);
        sem_wait(counter_sem);
        fprintf(output_log, "%d      : SERF %d      : leaves queue   : %d  : %d\n",
                ++(*counter), id, *hacker_count, *serf_count);
        sem_post(counter_sem);
        sem_post(log_write);

        /* Passenger leaves the queue for some time and then comes back */
        usleep(rand() % ((1000 * parameters.W) + 1));

        sem_wait(log_write);
        fprintf(output_log, "%d      : SERF %d      : is back\n",
                ++(*counter), id);
        sem_post(log_write);
    }

    sem_wait(log_write);
    sem_wait(counter_sem);
    fprintf(output_log, "%d      : SERF %d      : waits   : %d  : %d\n",
            ++(*counter), id, *hacker_count, ++(*serf_count));
    sem_post(counter_sem);
    sem_post(log_write);

    bool captain = false;

    /* Check for valid passenger combinations, otherwise, get in the queue */
    sem_wait(mutex);
    *serf_board += 1;

    sem_wait(counter_sem);
    if (*serf_board == 4) {

        sem_post(serf_queue);
        sem_post(serf_queue);
        sem_post(serf_queue);
        sem_post(serf_queue);

        *serf_board = 0;
        *serf_count -= 4;
        captain = true;

    } else if (*serf_board == 2 && *hacker_board >= 2) {

        sem_post(serf_queue);
        sem_post(serf_queue);
        sem_post(hacker_queue);
        sem_post(hacker_queue);

        *serf_board = 0;
        *hacker_board -= 2;
        *serf_count -= 2;
        *hacker_count -= 2;
        captain = true;

    } else {
        sem_post(mutex);
    }

    sem_post(counter_sem);

    sem_wait(serf_queue);


    if (!captain) {
        sem_wait(barrier);

        sem_wait(log_write);
        sem_wait(counter_sem);
        fprintf(output_log, "%d      : SERF %d      : member exits   : %d  : %d\n",
                ++(*counter), id, *hacker_count, *serf_count);
        sem_post(counter_sem);
        sem_post(log_write);

        sem_post(captain_exit);

    } else {
        sem_wait(log_write);
        sem_wait(counter_sem);
        fprintf(output_log, "%d      : SERF %d      : boards   : %d  : %d\n",
                ++(*counter), id, *hacker_count, *serf_count);
        sem_post(counter_sem);
        sem_post(log_write);

        row();

        /* Captain exits */
        sem_wait(log_write);
        sem_wait(counter_sem);
        fprintf(output_log, "%d      : SERF %d      : captain exits   : %d  : %d\n",
                ++(*counter), id, *hacker_count, *serf_count);
        sem_post(counter_sem);
        sem_post(log_write);

        sem_post(mutex);
    }

    sem_post(dock);
    exit(0);
}

void row(params_t parameters) {
    usleep(rand() % ((1000 * parameters.R) + 1));
    sem_post(barrier);
    sem_post(barrier);
    sem_post(barrier);

    sem_wait(captain_exit);
    sem_wait(captain_exit);
    sem_wait(captain_exit);
}
