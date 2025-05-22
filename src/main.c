#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "types.h"
#include "calc.h"
#include "timer.h"
#include "utils.h"
#include "sieve.h"
#include "pairs.h"

#define EXPECTED_ARGS 3 // program name, lower bound and upper bound expected


void parse_arguments (int argc, char **argv, u64_t *inf, u64_t *sup);
void write_resume_to_file (const u64_t inf, const u64_t sup, const u64_t pairs_found, mytimer_t *timer);


int main (int argc, char **argv) {
  // Default output file name
  char *output_file = "output.txt";

  // Parse command-line arguments to get the lower and upper bounds
  u64_t inf, sup;
  parse_arguments(argc, argv, &inf, &sup);

  // Compute the range of k values that could generate twin primes
  const u64_t k_start = calc_k_start(inf);
  const u64_t k_end = calc_k_end(sup);
  const u64_t necessary_space = k_end - k_start;

  // Start performance timer
  mytimer_t timer;
  start_timer(&timer);

  // Initialize the boolean array that tracks valid twin prime generators
  bool *is_twins_gen = (bool*) secure_malloc((necessary_space + 1) * sizeof(bool));
  memset(is_twins_gen, 1, (necessary_space + 1) * sizeof(*is_twins_gen));
  
  // Launch the multithreaded sieve to mark k values generating composites
  // We don't need those k values
  start_parallel_sieve(k_start, k_end, is_twins_gen);
  
  // Initialize the dynamic list that will store the resulting twin prime pairs
  twin_primes_list_t list = create_twin_primes_list();

  // Manually add the special twin prime pair (3, 5) if it falls within the input rang
  if (inf <= 3) {
    insert_pair(list, 3, 5);
  }
  
  // Generate and collect twin primes based on the filtered k value
  for (u64_t i=0, p=0; i <= necessary_space; i++) {
    if (!is_twins_gen[i]) {
      continue; // Non-twin-prime generators are skipped
    }
    // Convert k back to actual twin primes using the canonical formulas
    p = (k_start + i) * MODULO + LOWER_RESIDUE_CLASS;
    insert_pair(list, p, p+2);
  }

  // Stop the performance timer
  stop_timer(&timer);

  // Output statistics and results
  write_resume_to_file(inf, sup, get_pairs_count(list), &timer);
  write_pairs_to_file(output_file, list);
  
  // Clean up resources
  free_twin_primes_list(list);
  free(is_twins_gen);
  return 0;
}

void write_resume_to_file (const u64_t inf, const u64_t sup, const u64_t pairs_found, mytimer_t *timer) {
  printf("Elapsed time: %f, Range: %lu to %lu, Pairs found: %lu\n",
    get_elapsed_time(timer), inf, sup, pairs_found);

  char *filename = "resumes.txt";
  FILE *resume = secure_fopen(filename, "a");

  fprintf(resume, "Elapsed time: %f, Range: %lu to %lu, Pairs found: %lu\n",
    get_elapsed_time(timer), inf, sup, pairs_found);
  
  fclose(resume);

  printf("Resume successfully updated to file %s\n", filename);
}

void parse_arguments (int argc, char **argv, u64_t *inf, u64_t *sup) {
  if (argc != EXPECTED_ARGS) {
    fprintf(stderr, "Usage: %s <inf> <sup>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  char *end;
  *inf = strtoull(argv[1], &end, 10);
  if (*end != '\0') {
    fprintf(stderr, "Invalid inferior limit: %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  *sup = strtoull(argv[2], &end, 10);
  if (*end != '\0') {
    fprintf(stderr, "Invalid superior limit: %s\n", argv[2]);
    exit(EXIT_FAILURE);
  }

  if (*sup < *inf) {
    fprintf(stderr, "Superior limit must be >= inferior limit.\n");
    exit(EXIT_FAILURE);
  }
}

