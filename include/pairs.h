#ifndef PAIRS_H
#define PAIRS_H

#include "types.h"
#include "utils.h"

/**
 * @brief A dynamic array to store multiple twin prime pairs.
 */
typedef struct twin_primes_list* twin_primes_list_t;


/**
 * @brief Initializes an empty twin prime list.
 */
twin_primes_list_t create_twin_primes_list ();


/**
 * @brief Inserts a new twin prime pair into the list.
 *        Automatically expands the list if needed.
 *
 * @param list The twin prime list.
 * @param a The smaller number of the twin prime pair.
 * @param b The larger number of the twin prime pair.
 */
void insert_pair (twin_primes_list_t list, const u64_t a, const u64_t b);


/**
 * @brief Returns the count of twin prime pairs in the list.
 *
 * @param list The twin prime list.
 *
 * @return The count of twin prime pairs in the list. 
 */
int get_pairs_count (twin_primes_list_t list);


/**
 * @brief Writes the list of twin prime pairs to a file.
 *
 * Each pair is written in the format "a b\n", one per line.
 *
 * @param filename Path to the output file.
 * @param list The twin prime list.
 */
void write_pairs_to_file (const char *filename, const twin_primes_list_t list);


/**
 * @brief Frees the memory allocated for the twin prime list.
 *
 * @param list The twin prime list to deallocate.
 */
void free_twin_primes_list (twin_primes_list_t list);

#endif