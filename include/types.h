#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

/**
 * We know every prime p>3 is of the form 6k-1 or 6k+1.  
 * Equivalently, and for ease of implementation, based on the
 * concept of residue classes, we can say that prime numbers
 * are of the form p=6k+5 and p=6k+7.
 */
#define MODULO 6
#define LOWER_RESIDUE_CLASS 5
#define UPPER_RESIDUE_CLASS 7


/**
 * @brief Alias for a high-performance 64-bit unsigned integer.
 *
 * This type is suitable for numerical operations that benefit from faster
 * access on modern architectures, compared to standard uint64_t.
 * This type is defined in the stdint.h library.
 */
typedef uint_fast64_t u64_t;

#endif