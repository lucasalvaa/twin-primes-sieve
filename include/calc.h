#ifndef CALC_H
#define CALC_H

#include "types.h"

/**
 * @brief Compute the minimum k so that 6·k + LOWER_RESIDUE_CLASS ≥ inf.
 *
 * Solves:   6·k + LOWER_RESIDUE_CLASS ≥ inf  
 * Hence k_start = ⌈(inf - LOWER_RESIDUE_CLASS) / MODULO⌉,  
 * clamped at 0 if inf < LOWER_RESIDUE_CLASS.
 *
 * @param inf Lower bound of the range of numbers given by the user
 * @return The starting k index
 */
u64_t calc_k_start (u64_t inf);


/**
 * @brief Compute the maximum k so that 6·k + UPPER_RESIDUE_CLASS ≤ sup.
 *
 * Solves:   6·k + UPPER_RESIDUE_CLASS ≤ sup  
 * Hence k_end = ⌊(sup - UPPER_RESIDUE_CLASS) / MODULO⌋.
 *
 * @param sup Upper bound of the range of numbers given by the user
 * @return The ending k index
 */
u64_t calc_k_end (u64_t sup);


/**
 * @brief Compute the largest x such that the first rule may still yield ≤ k_end.
 *
 * From rule1: (6x+LOWER_RESIDUE_CLASS)(6x+LOWER_RESIDUE_CLASS) ≥ … leads to  
 * x_exit = ⌈√(k_end·MODULO + UPPER_RESIDUE_CLASS) − LOWER_RESIDUE_CLASS⌉ / MODULO.
 *
 * @param k_end The ending k index
 * @return Maximum x to iterate
 */
u64_t calc_x_exit (u64_t k_end);


/**
 * @brief Compute the initial y for a given x so that the
 *        smallest candidate ≥ k_start.
 *
 * Based on the inequality:
 *   6x+7 + 6y+7 ≥ k_start  
 * solving for y gives:
 *   y = (k_start - 7x - 7) / (6x + 7),
 * or y = 0 if the numerator would be negative.
 *
 * @param x        Current x index.
 * @param k_start  Lower bound index for k.
 * @return         The starting y index.
 */
u64_t calc_y (u64_t x, u64_t k_start);


/**
 * @brief First selection-rule residue.
 *
 * Implements the first selection rule (6x+5)(6y+5)
 *
 * @return k = 6xy + 5x + 5y + 3
 */
u64_t calc_fst_sr (u64_t x, u64_t y);


/**
 * @brief Second selection-rule residue.
 *
 * Implements the second selection rule (6x+7)(6y+7)
 *
 * @return k = 6xy + 7x + 7y + 7
 */
u64_t calc_snd_sr (u64_t x, u64_t y);


/**
 * @brief Third selection-rule residue.
 *
 * Implements the third selection rule (6x+5)(6y+7)
 *
 * @return k = 6xy + 5x + 7y + 5
 */
u64_t calc_trd_sr (u64_t x, u64_t y);


/**
 * @brief Fourth selection-rule residue.
 *
 * Implements the fourth selection rule (6x+7)(6y+5)
 *
 * @return k = 6xy + 7x + 5y + 5
 */
u64_t calc_fth_sr (u64_t x, u64_t y);

#endif