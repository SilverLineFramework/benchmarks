/**
 * @file api.h
 * @brief Header for ARENA API.
 * 
 * @note Use `CH_RDONLY, CH_WRONLY, CH_RDWR` instead of `O_*` variants
 * from `fnctl.h` since `fnctl.h` does not guarantee that these flags will be
 * the same on all systems!
 */

#include <stdio.h>

#ifndef CHANNELS_H
#define CHANNELS_H

/** @brief Read only mode */
#define CH_RDONLY 0
/** @brief Write only mode */
#define CH_WRONLY 1
/** @brief Read/write mode */
#define CH_RDWR 2

/**
 * @brief Open channel.
 * @param path Channel topic to open.
 * @param flags Read/write: `O_RDONLY`, `O_WRONLY` or `O_RDWR`
 * @param mode Unused
 * @return File descriptor of opened channel, or -1 for failure.
 */
int ch_open(const char *path, int flags, int mode);

/**
 * @brief Write message to channel.
 * @param fd Channel file descriptor to write to.
 * @param buf Data buffer
 * @param size Number of bytes to write
 * @return Length of message written.
 */
int ch_write_msg(int fd, char *buf, size_t size);

/**
 * @brief Read message from channel.
 * @param fd Channel file descriptor to read from
 * @param buf Data buffer to write to
 * @param size Maximum number of bytes to read
 * @return Number of bytes actually read
 */
int ch_read_msg(int fd, char *buf, size_t size);

/**
 * @brief Wait for message on channel.
 * @param chs Array of channels to wait on
 * @param nchs Number of channels in `chs`
 * @param timeout Maximum amount of time to wait (in milliseconds)
 * @return Number of channel descriptors in `chs` which received messages.
 */
int ch_poll(int *chs, int nchs, int timeout);

/**
 * @brief Get UUID of the current runtime.
 * @param buf Buffer to write UUID for. Should be at least 37 bytes.
 * @return 0 on success.
 */
int runtime_get_uuid(char *buf);

/**
 * @brief Get UUID of the current module.
 * @param buf Buffer to write UUID for. Should be at least 37 bytes.
 * @return 0 on success.
 */
int module_get_uuid(char *buf);

#endif /* CHANNELS_H */
