#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

/**
 * @brief Allocate memory and check for allocation failure.
 *
 * Behaves like malloc(), but terminates the program with an error
 * message if allocation fails.
 *
 * @param bytes Number of bytes to allocate.
 * @return Pointer to the allocated memory.
 */
void *secure_malloc (size_t bytes);


/**
 * @brief Reallocate memory and check for allocation failure.
 *
 * Behaves like realloc(), but terminates the program with an error
 * message if allocation fails.
 *
 * @param p Pointer to the memory previously allocated.
 * @param bytes New size in bytes for the memory block.
 * @return Pointer to the reallocated memory.
 */
void *secure_realloc (void *p, size_t bytes);


/**
 * @brief Open a file securely and check for failure.
 *
 * Behaves like fopen(), but terminates the program with an error
 * message if the file cannot be opened.
 *
 * @param filename Path of the file to open.
 * @param mode File access mode (e.g., "r", "w", "a").
 * @return FILE pointer to the opened file.
 */
FILE *secure_fopen (const char *filename, char *mode);

#endif