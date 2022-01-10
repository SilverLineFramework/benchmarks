/**
 * @file blocks_basic.c
 * @brief Basic blocks for testing.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "block.h"


/** @brief Identity block. */
void block_identity(data_t *data) {
    printf("[Block] Identity -> %02X...\n", data->buf[0] & 0xff);
}

/** @brief Simple bitwise not block for testing (u8) */
void block_not(data_t *data) {
    for (int i = 0; i < data->len / sizeof(uint32_t); i++) {
        data->u32[i] = ~data->u32[i];
    }
    printf("[Block] Bitwise Not -> %02X...\n", data->buf[0] & 0xff);
}

/** @brief Concatenate an array to itself to double its size. */
void block_concat(data_t *data) {
    char *buf_new = malloc(sizeof(char) * data->len * 2);
    memcpy(buf_new, data->buf, data->len);
    memcpy(buf_new + data->len, data->buf, data->len);
    free(data->buf);
    data->buf = buf_new;
    printf("[Block] Double size -> %d\n", data->len);
}

/** @brief Bubble sort (i32) */
void block_bubble_sort(data_t *data) {
    bool swap = false;
    int iters = 0;
    while (!swap) {
        swap = false;
        for(int i = 0; i < (data->len / sizeof(int32_t) - 1); i++) {
            if(data->i32[i] > data->i32[i + 1]) {
                int32_t swap = data->i32[i + 1];
                data->i32[i + 1] = data->i32[i];
                data->i32[i] = swap;
            }
        }
        iters += 1;
    }
    printf("[Block] Bubble sort (iters=%d\n)\n", iters);
}


/** @brief Sort comparison */
static int cmp (const void *a, const void *b) {
    return *(int *) a - *(int *)b;
}

/** @brief Quicksort (i32) */
void block_quicksort(data_t *data) {
    qsort(data->i32, data->len / sizeof(int32_t), sizeof(int32_t), &cmp);
    printf("[Block] Quick sort (len=%d)\n", data->len);
}
