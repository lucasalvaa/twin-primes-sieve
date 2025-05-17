#include "timer.h"

void start_timer (mytimer_t *timer) {
    clock_gettime(CLOCK_MONOTONIC, &timer->start);
}

void stop_timer (mytimer_t *timer) {
    clock_gettime(CLOCK_MONOTONIC, &timer->end);
}

double get_elapsed_time (const mytimer_t *timer) {
    return (timer->end.tv_sec - timer->start.tv_sec) +
           (timer->end.tv_nsec - timer->start.tv_nsec) / 1e9;
}
