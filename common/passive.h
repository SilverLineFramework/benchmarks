/**
 * @file active.h
 * @brief Main loop for passive profiling.
 */

#ifndef PASSIVE_H
#define PASSIVE_H

int loop(int argc, char **argv, int (*func)(int, char **));

#if !defined REPEAT
#define REPEAT 1
#endif

#endif
