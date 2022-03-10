/**
 * @file kernelhc
 * @brief Main kernel for parameterized benchmark proposal.
 */

#ifndef KERNEL_H
#define KERNEL_H

#ifndef NUM_COLUMNS
#define NUM_COLUMNS 4096
#endif

#ifndef COLUMN_STRIDE
#define COLUMN_STRIDE 1
#endif

#ifndef ROW_STRIDE
#define ROW_STRIDE 4096
#endif

#ifndef ARRAY_SIZE
// This number is prime, and approximately 2^26
// ARRAY_SIZE must be less than 2^32 to support all possible strides.
#define ARRAY_SIZE 67108879
#endif

#define NUM_ROWS (ARRAY_SIZE / NUM_COLUMNS)


#define MAGIC1 3141592653589793238
#define MAGIC2 4626433832795028
#define MAGIC3 11235813213455

#endif
