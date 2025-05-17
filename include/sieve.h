#ifndef SIEVE_H
#define SIEVE_H

#include <stdbool.h>
#include "types.h"
#include "calc.h"

/**
 * @brief Launch a multithreaded parallel sieve to mark the k 
 * that generate composite numbers in the 'is_twins_gen' array.
 *
 * We know every prime p>3 is of the form 6k-1 or 6k+1.  
 * Equivalently, and for ease of implementation, based on the
 * concept of residue classes, we can say that prime numbers
 * are of the form p=6k+5 and p=6k+7. By discarding those k
 * for which any of the four "selection rules" yields a composite
 * in [6k+5, 6k+7], the remaining k generate twin primes.
 *
 * @param k_start       Lower bound of the k-range.
 * @param k_end         Upper bound of the k-range.
 * @param is_twins_gen  Pre-allocated boolean array of length
 *                      (k_end - k_start + 1), all initialized true;
 *                      entries set to false mark k that fail any of the four rules.
 */
void start_parallel_sieve (u64_t k_start, u64_t k_end, bool *is_twins_gen);

#endif
