/**
 * @file kernel.c
 * @brief Main kernel for parameterized benchmark proposal.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "../common/runtime.h"

#include "kernel.h"


static inline uint32_t transform(uint32_t val, uint32_t prev) {
    return (val * prev + MAGIC1) / MAGIC2 - MAGIC3;
}


uint64_t kernel(
        uint32_t *data, uint64_t rows, uint64_t columns,
        uint64_t row_stride, uint64_t column_stride) {
    uint64_t acc = 0;
    uint32_t prev = 0;
    for (uint64_t i = 0; i < rows; i++) {
        // Second accumulator; prevents the loop order from being swapped by a
        // smart compiler (i.e. if we had just one accumulator)
        uint64_t acc_inner = 0;
        for (uint64_t j = 0; j < columns; j++) {
            uint64_t idx = (i * row_stride + j * column_stride) % ARRAY_SIZE;
            acc_inner += (uint64_t) transform(data[idx], prev);
            prev = data[idx];
        }
        acc ^= acc_inner;
    }
    return acc;
}


int benchmark_main(int argc, char **argv) {
    uint32_t *data_array = malloc(sizeof(uint32_t) * ARRAY_SIZE);

    for (uint32_t i = 0; i < ARRAY_SIZE; i++) { data_array[i] = i; }

    uint64_t res = kernel(
        data_array, NUM_ROWS, NUM_COLUMNS, ROW_STRIDE, COLUMN_STRIDE);

    free(data_array);
    return 0;
}


int main(int argc, char **argv) {
    return loop(argc, argv, benchmark_main);
}
