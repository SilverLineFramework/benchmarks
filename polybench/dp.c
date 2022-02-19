/**
 * @file dp.c
 * @brief Dirichlet process implementation
 * 
 * Uses Chinese Restaurant Process representation; draws values from
 * geometric distribution.
 */

#include <math.h>
#include <stdlib.h>

#include "dp.h"

/** Draw from geometric */
static int sample_geometric() {
    double x = (double) rand() / (double) RAND_MAX;

    return ceil(log(x) / log(0.999));
}


/** Initialize dirichlet process. */
void dp_init(dp_t *dp) {
    for (int i = 0; i < MAX_TABLES; i++) {
        dp->tables[i] = 0;
    }
    dp->total = ALPHA;
    dp->num_tables = 0;
}

/** Draw from dirichlet process */
int dp_draw(dp_t *dp) {
    double x = (double) rand() / (double) RAND_MAX;

    double acc = 1 / (double) dp->total;
    int i;

    // Draw new
    if (x < acc) {
        dp->values[dp->num_tables] = sample_geometric();
        dp->num_tables += 1;
        i = dp->num_tables - 1;
    // Sample from existing table
    } else {
        for (i = 0; i < MAX_TABLES; i++) {
            acc += (double) dp->tables[i] / (double) dp->total;
            if (acc > x) { break; }
        }
    }

    dp->tables[i] += 1;
    dp->total += 1;
    return dp->values[i];
}
