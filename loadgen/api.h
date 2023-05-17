/**
 * @defgroup wasm_api SilverLine WASM API.
 *
 * Channels define the access programs have to external resources. For now, we
 * use channels to define access to a pub/sub structure, but imagine these can
 * be used to define access to other network resources (e.g. client sockets)
 * and even other device resources such as sensors.
 *
 * @note Use `CH_RDONLY, CH_WRONLY, CH_RDWR` instead of `O_*` variants
 * from `fnctl.h` since `fnctl.h` does not guarantee that these flags will be
 * the same on all systems!
 * @{
  */

#ifndef SILVERLINE_API_H
#define SILVERLINE_API_H

#include <stdio.h> // for size_t

/** @brief Read only mode = 0 */
#define CH_RDONLY 0
/** @brief Write only mode = 1 */
#define CH_WRONLY 1
/** @brief Read/write mode = 2 */
#define CH_RDWR 2

/**
 * @brief Open channel.
 * 
 * Returns a channel file descriptor; This is different from a normal file
 * open() in two important ways:
 * 
 *  1. The rw_mode indicates the read/write access (``CH_RDONLY``,
 *     ``CHWRONLY``, ``CH_RDWR``) to the channel (closer to ``open()`` flags);
 *  2. A channel has only one file descriptor; multiple ``ch_open()`` calls
 *     with the same path will return the same file descriptor.
 * @param path Channel topic to open.
 * @param flags Read/write: `O_RDONLY`, `O_WRONLY` or `O_RDWR`
 * @param mode Unused
 * @return File descriptor of opened channel, or -1 for failure.
 */
int ch_open(const char *path, int flags, int mode);

/**
 * @brief Close channel.
 * If this module is the last module with this channel topic open, the topic is
 * unsubscribed by the MQTT client.
 */
int ch_close(int fd);

/**
 * @brief Write message to channel.
 * @param fd Channel file descriptor to write to.
 * @param buf Data buffer.
 * @param size Number of bytes to write.
 * @return Length of message written.
 */
int ch_write_msg(int fd, char *buf, size_t size);

/**
 * @brief Read message from channel.
 * @todo If size is insufficient to read the entire message, the message is
 * held until exhausted by subsequent ch_read_msg calls.
 * @param fd Channel file descriptor to read from.
 * @param buf Data buffer to write to.
 * @param size Maximum number of bytes to read.
 * @return Number of bytes actually read.
 */
int ch_read_msg(int fd, char *buf, size_t size);

/**
 * @brief Wait for message on channel.
 * @param chs Array of channels to wait on.
 * @param nchs Number of channels in `chs`.
 * @param timeout Maximum amount of time to wait (in milliseconds). If
 * ``timeout == 0``, waits indefinitely.
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

/**
 * @brief Start profiling period manually.
 */
void period_start();

/**
 * @brief End profiling period manually.
 */
void period_end();

/**
 * @brief End profiling period and yield remaining time.
 * Only has an effect if periodic scheduling is used (the module has a nonzero
 * period and runtime); calls ``sched_yield``.
 */
void period_yield();

/**
 * @brief Set profiling mode.
 * @param flags 1 for manual, 0 for automatic (ch_poll).
 */
void period_set_flags(int flags);

#endif /* SILVERLINE_API_H */
/** @} */