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

#define semMUTEX "/ios-xsedla1h-mutex"
#define semBARRIER "/ios-xsedla1h-barrier"
#define semHACKER "/ios-xsedla1h-hacker"
#define semSERF "/ios-xsedla1h-serf"
#define semLOG_WRITE "/ios-xsedla1h-log_write"
#define semCOUNTER "/ios-xsedla1h-counter"

#define LOG_FILE "proj2.out"

sem_t *mutex;
sem_t *barrier;
sem_t *hacker_queue;
sem_t *serf_queue;
sem_t *dock;
sem_t *log_write;
sem_t *counter;


pid_t hacker_gen;
pid_t serf_gen;

FILE *output_log;
int *shared_counter;
int shared_counter_id;

void init_resources();

void destroy_resources();

#endif
