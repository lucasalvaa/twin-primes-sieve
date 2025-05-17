#ifndef TIMER_H
#define TIMER_H

#include <time.h>

typedef struct {
    struct timespec start;
    struct timespec end;
} mytimer_t;

void start_timer (mytimer_t *timer);
void stop_timer (mytimer_t *timer);
double get_elapsed_time (const mytimer_t *timer);

#endif
