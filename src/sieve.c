#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include "sieve.h"

/**
 * @brief Holds parameters for a worker thread in the sieve.
 *
 * Each thread marks the k values that generate composite numbers over
 * a subrange of k values [k_start, k_end], stepping through 
 * x values according to its initial_x and x_increment.
 */
 typedef struct {
    u64_t k_start, k_end; // Lower and upper bound of the 'k' range
    u64_t initial_x; // Thread's starting offset into x
    u64_t x_increment; // Stride in x (≡ number of threads)
    bool *is_twins_gen; // Shared array in which the 'k' generators of twin primes are marked
} thread_data_t;

/**
 * @brief Worker function: mark all composite k‐generators as false in the 'is_twins_gen' array.
 *
 * Uses the four selection rules to identify and mark k values that cannot generate twin primes.
 *
 * @param arg Pointer to a thread_data_t struct (must be freed by caller).
 * @return NULL
 */
static void *mark_composite_generators (void *arg) {
    thread_data_t *d = (thread_data_t *)arg;

    u64_t x = d->initial_x;
    u64_t y;
    u64_t k1, k2, k3, k4;

    // max x to consider: solve 6*x + max(class) <= k_end * 6 + max(class)
    u64_t exit_x = calc_x_exit(d->k_end);

    while (x <= exit_x) {
        y = calc_y(x, d->k_start);

        for(;;) {
            // 1) First selection rule
            k1 = calc_fst_sr(x, y);
            if (k1 > d->k_end) {
                break;
            }
            
            if (k1 >= d->k_start) {
                d->is_twins_gen[k1 - d->k_start] = false;
            }

            // 2) Third selection rule
            k3 = calc_trd_sr(x, y);
            if (d->k_start <= k3 && k3 <= d->k_end) {
                d->is_twins_gen[k3 - d->k_start] = false;
            }

            // 3) Fourth selection rule
            k4 = calc_fth_sr(x, y);
            if (k4 > d->k_end) {
                y++;
                continue;
            }
            if (k4 >= d->k_start) {
                d->is_twins_gen[k4 - d->k_start] = false;
            }
            
            // 4) Second selection rule
            k2 = calc_snd_sr(x, y);
            if (d->k_start <= k2  && k2 <= d->k_end) {
                d->is_twins_gen[k2 - d->k_start] = false;
            }

            y++;
        }

        x += d->x_increment;
    }

    return NULL;
}

/**
 * @brief Spawn threads and wait for them to finish marking composites generators.
 *
 * @param generic_thread_data Thread-data prototype to clone for each thread.
 * @param num_threads Number of worker threads to launch.
 */
static void multithread_parallel_sieve (thread_data_t generic_thread_data, int num_threads) {
    pthread_t threads[num_threads];
    thread_data_t thread_data[num_threads];

    for (int i = 0; i < num_threads; i++) {
        thread_data[i] = generic_thread_data;
        thread_data[i].initial_x = i;
        thread_data[i].x_increment = num_threads;
        pthread_create(&threads[i], NULL, mark_composite_generators, &thread_data[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    } 
}

void start_parallel_sieve (u64_t k_start, u64_t k_end, bool *is_twins_gen) {

    int num_threads = sysconf(_SC_NPROCESSORS_ONLN);

    thread_data_t generic_thread_data = {
        .k_start = k_start,
        .k_end = k_end,
        .initial_x = 0,
        .x_increment = 0,
        .is_twins_gen = is_twins_gen
    };

    multithread_parallel_sieve(generic_thread_data, num_threads);
}