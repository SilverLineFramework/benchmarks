/**
 * Header for ARENA channels interface.
 */

#include <fcntl.h>
#include <stdio.h>

#ifndef CHANNELS_H
#define CHANNELS_H

int ch_open(const char *path, int flags, mode_t mode);
int ch_write_msg(int fd, char *buf, size_t size);
int ch_read_msg(int fd, char *buf, size_t size);
int ch_poll(int *chs, int nchs, int timeout);

#endif
