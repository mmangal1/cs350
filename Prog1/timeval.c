#include <stdlib.h>
#include <stdio.h>
#include "timeval.h"

void print_time(struct timeval *time){
	fprintf(stderr, "%ld.%06ld seconds\n", time->tv_sec, time->tv_usec); 
}

int get_time(struct timeval *time){

	if(gettimeofday(time, NULL) < 0){
		perror("Get time of day has error : ");
		exit(1);
	}
	return gettimeofday(time, NULL);
}

int diff_time(struct timeval *start, struct timeval *end, struct timeval *result){

	long int diff = (end->tv_usec + 1000000 * end->tv_sec) - (start->tv_usec + 1000000 * start->tv_sec);
	result->tv_sec = diff / 1000000;
	result->tv_usec = diff % 1000000;

	if(diff<0){
		perror("diff_time has error : ");
		exit(1);
	}
	else{
		return 1;
	}
}

