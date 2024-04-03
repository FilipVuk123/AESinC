#ifndef CLOCK_H
#define CLOCK_H

#include <time.h>

#define NS_TO_US(nsec) ((double)((nsec) / (double)(1e3)))
#define NS_TO_MS(nsec) ((double)((nsec) / (double)(1e6)))
#define NS_TO_S(nsec)  ((double)((nsec) / (double)(1e9)))

#define US_TO_NS(usec) ((double)((usec) * (double)(1e3)))
#define US_TO_MS(usec) ((double)((usec) / (double)(1e3)))
#define US_TO_S(usec)  ((double)((usec) / (double)(1e6)))

#define MS_TO_NS(msec) ((double)((msec) * (double)(1e6)))
#define MS_TO_US(msec) ((double)((msec) * (double)(1e3)))
#define MS_TO_S(msec)  ((double)((msec) / (double)(1e3)))

#define S_TO_NS(sec)   ((double)((sec)  * (double)(1e9)))
#define S_TO_US(sec)   ((double)((sec)  * (double)(1e6)))
#define S_TO_MS(sec)   ((double)((sec)  * (double)(1e3)))

typedef struct timespec timer;

timer time_now();

double get_time_diff_usec(timer const start, timer const stop);

double get_time_diff_msec(timer const start, timer const stop);

double get_time_diff_sec(timer const start, timer const stop);

#endif // CLOCK_H