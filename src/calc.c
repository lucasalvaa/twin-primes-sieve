#include "calc.h"
#include <math.h>

/**
 * @brief Generic helper for the four selection-rule formulas.
 *
 * Computes k = MODULO·x·y + cx·x + cy·y + c
 *
 * @param x   Current x index.
 * @param y   Current y index.
 * @param cx  Coefficient of x in the linear term.
 * @param cy  Coefficient of y in the linear term.
 * @param c   Constant term.
 * @return    The computed k residue.
 */
static inline u64_t calc_sr (u64_t x, u64_t y, int cx, int cy, int c) {
  return (MODULO * x * y) + (x * cx) + (y * cy) + c;
}

u64_t calc_k_start (u64_t inf) {
  if (inf < 5) {
    return 0;
  }

  return (inf - LOWER_RESIDUE_CLASS) / MODULO + ((inf - 5) % MODULO == 0 ? 0 : 1);
}

u64_t calc_k_end (u64_t sup) {
  return (sup - UPPER_RESIDUE_CLASS) / MODULO;
}

u64_t calc_x_exit (u64_t k_end) {
  return (ceill(sqrtl(k_end * MODULO + UPPER_RESIDUE_CLASS)) - LOWER_RESIDUE_CLASS) / MODULO;
}

u64_t calc_fst_sr (u64_t x, u64_t y) {
  return calc_sr(x, y, 5, 5, 3);
}

u64_t calc_snd_sr (u64_t x, u64_t y) {
  return calc_sr(x, y, 7, 7, 7);
}

u64_t calc_trd_sr (u64_t x, u64_t y) {
  return calc_sr(x, y, 5, 7, 5);
}

u64_t calc_fth_sr (u64_t x, u64_t y) {
  return calc_sr(x, y, 7, 5, 5);
}

u64_t calc_y (u64_t x, u64_t k_start) {
  if (k_start < (UPPER_RESIDUE_CLASS * x + UPPER_RESIDUE_CLASS)) {
    return 0;
  }

  return (k_start - UPPER_RESIDUE_CLASS * x - UPPER_RESIDUE_CLASS) / (MODULO * x + UPPER_RESIDUE_CLASS);
}
