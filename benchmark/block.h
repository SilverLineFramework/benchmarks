/**
 * @file block.h
 * @brief Common definitions for processing blocks
 */

#ifndef BLOCK_H
#define BLOCK_H

#include <stdint.h>

/**
 * @brief Data buffer and length
 */
typedef struct {
    /** Data buffer */
    union {
        char *buf;
        int32_t *i32;
        uint32_t *u32;
        float *f32;
    };
    /** Length in bytes */
    int len;
} data_t;

#endif
