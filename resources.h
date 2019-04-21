/**
 *	@file	resources.h
 *	@author	Simon Sedlacek, xsedla1h
 *	@date	22.4.2019
 *	@brief  This module contains all the resources for the program, for example
 *	shared variables, semaphores, etc.
 *	@note	IOS 2019 - second assignment - River Crossing Problem
 */

#ifndef RESOURCES_HEADER
#define RESOURCES_HEADER

#include <semaphore.h>
#include <stdio.h>

#include "arguments.h"

#define semMUTEX "/ios-xsedla1h-mutex"
#define semTRY_TO_BOARD "/ios-xsedla1h-try_to_board"
#define semBOARD_LIMIT "/ios-xsedla1h-board_limit"
#define semHACKER "/ios-xsedla1h-hacker"
#define semSERF "/ios-xsedla1h-serf"
#define semDOCK "/ios-xsedla1h-dock"
#define semLOG_WRITE "/ios-xsedla1h-log_write"
#define semCOUNTER "/ios-xsedla1h-counter"
#define semCAPTAIN "/ios-xsedla1h-captain"

#define LOG_FILE "proj2.out"

/* Semaphores */
sem_t *mutex;
sem_t *try_to_board; //mutex
sem_t *board_limit;
sem_t *hacker_queue;
sem_t *serf_queue;
sem_t *dock;
sem_t *log_write; //mutex
sem_t *counter; //mutex
sem_t *captain_exit; //barrier

/**
 * @brief Output log file for process updates
 */
FILE *output_log;

/**
 * @brief Process update message number
 */
int *message_counter;

/**
 * @brief Current number of hackers in the dock
 */
int *hacker_count;

/**
 * @brief Current number of serf in the dock
 */
int *serf_count;

/**
 * @brief Current number of hackers waiting to be boarded
 */
int *hacker_board;

/**
 * @brief Current number of serfs waiting to be boarded
 */
int *serf_board;

/* Variables used for the initialization of the corresponding shared variables */
int message_counter_id;
int hacker_count_id;
int serf_count_id;
int hacker_board_id;
int serf_board_id;

/**
 * @brief Allocates all the necessary resources for the program
 *
 * @param params A structure holding the command line arguments passed
 * to the program
 */
void init_resources(params_t params);

/**
 * @brief Releases all the allocated resources
 */
void destroy_resources();

#endif
