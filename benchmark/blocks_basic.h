/**
 * @file blocks_basic.h
 * @brief Basic blocks for testing.
 */

#ifndef BLOCKS_BASIC_H
#define BLOCKS_BASIC_H

#include "block.h"

void block_identity(data_t *data);
void block_not(data_t *data);
void block_concat(data_t *data);
void block_bubble_sort(data_t *data);
void block_quicksort(data_t *data);

#endif
