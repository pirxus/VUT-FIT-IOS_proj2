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

#define semMutex "/ios-xsedla1h-mutex"
#define semBarrier "/ios-xsedla1h-barrier"
#define semHackerQ "/ios-xsedla1h-hackerQ"
#define semSerfQ "/ios-xsedla1h-serfQ"

sem_t *mutex;
sem_t *barrier;
sem_t *hacker_queue;
sem_t *serf_queue;
sem_t *dock;
sem_t *log_write;

pid_t hacker_gen;
pid_t serf_gen;

FILE *output_log;


int init();

void destroy();

#endif
