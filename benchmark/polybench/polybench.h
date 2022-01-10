/**
 * @file polybench/polybench.h
 * @brief Blocks adapted from polybench
 */

#ifndef POLYBENCH_H
#define POLYBENCH_H

#include "../block.h"

void block_correlation(data_t *data);

void block_2mm(data_t *data);
void block_3mm(data_t *data);

void block_cholesky(data_t *data);

#endif
