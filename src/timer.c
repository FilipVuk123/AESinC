
#include "timer.h"

#include <time.h> // clock_gettime

//=========================================================

timer time_now()
{
    struct timespec start_time;

    if (clock_gettime(CLOCK_REALTIME, &start_time) < 0)
    {
    }

    return start_time;
}

//=========================================================


double get_time_diff_usec(timer const start, timer const stop)
{
    return ((stop.tv_sec - start.tv_sec) * (time_t)(1e6)) + NS_TO_US(stop.tv_nsec - start.tv_nsec);
}

double get_time_diff_msec(timer const start, timer const stop)
{
    return ((stop.tv_sec - start.tv_sec) * (time_t)(1e3)) + NS_TO_MS(stop.tv_nsec - start.tv_nsec);
}

double get_time_diff_sec(timer const start, timer const stop)
{
    return (stop.tv_nsec - start.tv_sec) + NS_TO_S(stop.tv_nsec - start.tv_nsec);
}

//=========================================================