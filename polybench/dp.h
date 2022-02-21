/**
 * @file dp.h
 * @brief Dirichlet process implementation
 * 
 * Uses Chinese Restaurant Process representation; draws values from
 * geometric distribution.
 */

#ifndef DP_H


#ifndef MAX_TABLES
#define MAX_TABLES 16
#endif

#ifndef GEOMETRIC_PARAM
#define GEOMETRIC_PARAM 0.001
#endif

#ifndef ALPHA
#define ALPHA 1
#endif

/**
 * @brief Dirichlet process state.
 */
typedef struct {
    /** Number of people at each table */
    int tables[MAX_TABLES];
    /** Value of each table */
    int values[MAX_TABLES];
    /** Number of tables */
    int num_tables;
    /** Total arrivals */
    int total;
} dp_t;


void dp_init(dp_t *dp, unsigned long seed);
int dp_draw(dp_t *dp);


#endif
