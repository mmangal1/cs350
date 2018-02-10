#ifndef TIMEVAL_H
#define TIMEVAL_H

#include <sys/time.h>

	//struct timeval timeStart, timeEnd, timeDiff;

	void print_time(struct timeval *time);
	int get_time(struct timeval *time);
	int diff_time(struct timeval *start, struct timeval *end, struct timeval *result);


#endif
