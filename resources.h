/**
 *	@file	resources.h
 *	@author	Simon Sedlacek, xsedla1h
 *	@date	18.4.2019
 *	@brief  
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

sem_t *mutex;
sem_t *try_to_board;
sem_t *board_limit;
sem_t *hacker_queue;
sem_t *serf_queue;
sem_t *dock;
sem_t *log_write;
sem_t *counter;
sem_t *captain_exit;

FILE *output_log;

int *message_counter;
int message_counter_id;

int *hacker_count;
int hacker_count_id;
int *serf_count;
int serf_count_id;

int *hacker_board;
int hacker_board_id;
int *serf_board;
int serf_board_id;

void init_resources(params_t params);

void destroy_resources();

#endif
