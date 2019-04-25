/**
 *	@file	process.c
 *	@author	Simon Sedlacek, xsedla1h
 *	@date	18.4.2019
 *	@brief  This module contains all the funcions representing the hackers
 *	and serfs themselfs
 *	@note	IOS 2019 - second assignment - River Crossing Problem
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "process.h"
#include "arguments.h"
#include "resources.h"


void hacker_process(params_t parameters, unsigned id) {
    srand(time(NULL));
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

    /* The process can now wait in the docks... */
    print_status(HACK, "waits", true, true, id);
    sem_post(mutex);

    /* Check for valid passenger combinations in order to obtain the captain role,
     * otherwise, get in the boarding queue */
    bool captain = false;
    sem_wait(try_to_board);
    sem_wait(mutex);

    *hacker_board += 1;
    if (*hacker_board == 4) {

        /* Found four hackers! */
        sem_post(hacker_queue);
        sem_post(hacker_queue);
        sem_post(hacker_queue);
        sem_post(hacker_queue);

        *hacker_board = 0;
        *hacker_count -= 4;
        captain = true;

    } else if (*hacker_board == 2 && *serf_board >= 2) {

        /* Found two serfs and two hackers! */
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

        /* Non captain releases the resources */
        sem_post(try_to_board);
        sem_post(mutex);
    }

    /* Passenger waits to be boarded... */
    sem_wait(hacker_queue);

    if (captain)
        row(HACK, parameters, id);
    else
        board(HACK, id);

    exit(0);
}

void serf_process(params_t parameters, unsigned id) {
    srand(time(NULL));
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

    /* The process can now wait in the docks... */
    print_status(SERF, "waits", true, true, id);
    sem_post(mutex);

    /* Check for valid passenger combinations in order to obtain the captain role,
     * otherwise, get in the boarding queue */
    bool captain = false;
    sem_wait(try_to_board);
    sem_wait(mutex);

    *serf_board += 1;
    if (*serf_board == 4) {

        /* Found four hackers! */
        sem_post(serf_queue);
        sem_post(serf_queue);
        sem_post(serf_queue);
        sem_post(serf_queue);

        *serf_board = 0;
        *serf_count -= 4;
        captain = true;

    } else if (*serf_board == 2 && *hacker_board >= 2) {

        /* Found two serfs and two hackers! */
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

        /* Non captain releases the resources */
        sem_post(mutex);
        sem_post(try_to_board);
    }

    /* Passenger waits to be boarded... */
    sem_wait(serf_queue);

    if (captain)
        row(SERF, parameters, id);
    else
        board(SERF, id);

    exit(0);
}

void row(const char *name, params_t parameters, unsigned id) {
    /* The captain frees four spaces in the docks and starts his journey */
    sem_post(dock);
    sem_post(dock);
    sem_post(dock);
    sem_post(dock);

    print_status(name, "boards", true, false, id);
    sem_post(mutex);

    /* Gendry is still rowing his boat... */
    usleep(1000 * (rand() % (parameters.R + 1)));

    /* Waits for the crew to exit the boat */
    sem_post(board_limit);
    sem_post(board_limit);
    sem_post(board_limit);

    /* Now exits the boat himself */
    sem_wait(captain_exit);
    sem_wait(captain_exit);
    sem_wait(captain_exit);

    print_status(name, "captain exits", true, false, id);
    sem_post(try_to_board);
}

void board(const char *name, unsigned id) {
    /* The passenger gets on board, where he waits for
     * the captain to finish rowing... */
    sem_wait(board_limit);
    print_status(name, "member exits", true, false, id);

    /* Lets captain know he's exiting the boat */
    sem_post(captain_exit);
}

void print_status(const char *name, const char *message,
        bool pass_count, bool inc, unsigned id) {

    sem_wait(log_write);

    /* Checks if the message should contain information about current
     * numbers of passengers waiting in the docks */
    if (pass_count) {

        /* Increments either the hacker count or the serf count */
        if (inc) {
            if (!strcmp(name, HACK))
                *hacker_count += 1;
            else
                *serf_count += 1;
        }

        fprintf(output_log, "%-8d: %s %-8d: %-20s: %-8d: %d\n",
                ++(*message_counter), name, id, message, *hacker_count, *serf_count);

    } else {
        fprintf(output_log, "%-8d: %s %-8d: %s\n",
                ++(*message_counter), name, id, message);
    }

    sem_post(log_write);
}
