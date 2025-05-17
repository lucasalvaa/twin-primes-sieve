#include <stdlib.h>
#include <stdio.h>
#include "pairs.h"
#include "utils.h"

#define INITIAL_CAPACITY 256
#define LIST_GROWTH_FACTOR 3

/**
 * @brief Represents a pair of twin primes (a, b), where b = a + 2.
 */
 typedef struct {
    u64_t a;
    u64_t b;
} twin_primes_t;


/**
 * @brief A dynamic array to store multiple twin prime pairs.
 */
struct twin_primes_list {
    twin_primes_t *pairs;   /**< Pointer to the array of twin prime pairs. */
    size_t max_capacity;    /**< Allocated capacity of the array. */
    size_t count;           /**< Number of twin pairs currently stored. */
};

twin_primes_list_t create_twin_primes_list () {
    twin_primes_list_t list = secure_malloc(sizeof(struct twin_primes_list));
    list->max_capacity = INITIAL_CAPACITY;
    list->count = 0;
    list->pairs = secure_malloc(list->max_capacity * sizeof(*list->pairs));
    return list;
}

void insert_pair (twin_primes_list_t list, const u64_t a, const u64_t b) {
    // if the list
    if (list->count == list->max_capacity) {
        list->max_capacity *= LIST_GROWTH_FACTOR;
        list->pairs = secure_realloc(list->pairs, list->max_capacity * sizeof(*list->pairs));
    }
    
    list->pairs[list->count].a = a;
    list->pairs[list->count].b = b;
    list->count++;
}

int get_pairs_count (twin_primes_list_t list) {
    return list->count;
}

void write_pairs_to_file (const char *filename, const twin_primes_list_t list) {
    FILE *fp = secure_fopen(filename, "w");
    for (size_t i=0; i < list->count; i++) {
        fprintf(fp, "%lu, %lu\n", list->pairs[i].a, list->pairs[i].b);
    }
    fclose(fp);
}

void free_twin_primes_list (twin_primes_list_t list) {
    free(list->pairs);
    free(list);
}