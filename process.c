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
#include <string.h>

#include "process.h"
#include "arguments.h"
#include "resources.h"


void hacker_process(params_t parameters, unsigned id) {
    /* The process has been started */
    print_status(HACK, "starts", false, false, id);

    /* Passenger tries to enter the dock */
    sem_wait(mutex);
    while (sem_trywait(dock) == -1) {
        print_status(HACK, "leaves queue", true, false, id);
        sem_post(mutex);

        /* Passenger leaves the queue for some time and then comes back */
        usleep(1000 * ((rand() % (parameters.W - 19) + 20)));
        print_status(HACK, "is back", false, false, id);
        sem_wait(mutex);
    }
    sem_post(mutex);

    /* The process can now wait in the docks... */
    print_status(HACK, "waits", true, true, id);

    /* Check for valid passenger combinations in order to obtain the captain role,
     * otherwise, get in the boarding queue */
    bool captain = false;
    sem_wait(try_to_board);
    sem_wait(counter);
    *hacker_board += 1;

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
        sem_post(try_to_board);
        sem_post(counter);
    }

    sem_wait(hacker_queue);


    if (captain)
        row(HACK, parameters, id);
    else
        board(HACK, id);

    exit(0);
}

void serf_process(params_t parameters, unsigned id) {
    /* The process has been started */
    print_status(SERF, "starts", false, false, id);

    /* Passenger tries to enter the dock */
    sem_wait(mutex);
    while (sem_trywait(dock) == -1) {
        print_status(SERF, "leaves queue", true, false, id);
        sem_post(mutex);

        /* Passenger leaves the queue for some time and then comes back */
        usleep(1000 * ((rand() % (parameters.W - 19) + 20)));
        print_status(SERF, "is back", false, false, id);
        sem_wait(mutex);
    }
    sem_post(mutex);

    /* The process can now wait in the docks... */
    print_status(SERF, "waits", true, true, id);

    /* Check for valid passenger combinations in order to obtain the captain role,
     * otherwise, get in the boarding queue */
    bool captain = false;
    sem_wait(try_to_board);
    sem_wait(counter);
    *serf_board += 1;

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
        sem_post(try_to_board);
        sem_post(counter);
    }

    sem_wait(serf_queue);

    if (captain)
        row(SERF, parameters, id);
    else
        board(SERF, id);

    sem_post(dock);
    exit(0);
}

void row(const char *name, params_t parameters, unsigned id) {

    sem_wait(mutex);

    sem_post(dock);
    sem_post(dock);
    sem_post(dock);
    sem_post(dock);

    print_status(name, "boards", true, false, id);

    sem_post(counter);
    sem_post(mutex);

    usleep(1000 * (rand() % (parameters.R + 1)));

    sem_post(board_limit);
    sem_post(board_limit);
    sem_post(board_limit);

    sem_wait(captain_exit);
    sem_wait(captain_exit);
    sem_wait(captain_exit);

    print_status(name, "captain exits", true, false, id);
    sem_post(try_to_board);
}

void board(const char *name, unsigned id) {
    sem_wait(board_limit);
    print_status(HACK, "member exits", true, false, id);
    sem_post(captain_exit);
}

void print_status(const char *name, const char *message,
        bool pass_count, bool inc, unsigned id) {
    sem_wait(log_write);

    if (pass_count) {
        sem_wait(counter);

        if (inc) {
            if (!strcmp(name, HACK))
                *hacker_count += 1;
            else
                *serf_count += 1;
        }

        fprintf(output_log, "%d      : %s %d      : %s     : %d   : %d\n",
                ++(*message_counter), name, id, message, *hacker_count, *serf_count);
        sem_post(counter);

    } else {
        fprintf(output_log, "%d      : %s %d      : %s \n",
                ++(*message_counter), name, id, message);
    }

    sem_post(log_write);
}
