/**
 * @file api.c
 * @brief Non-runtime implementation for local testing of SilverLine programs.
 */

#include <sched.h>
#include "MQTTClient.h"

#include "api.h"

/**
 * @brief Open channel.
 * @param path Channel topic to open.
 * @param flags Read/write: `O_RDONLY`, `O_WRONLY` or `O_RDWR`
 * @param mode Unused
 * @return File descriptor of opened channel, or -1 for failure.
 */
int ch_open(const char *path, int flags, int mode) {
    // todo
    return 0;
}

/**
 * @brief Write message to channel.
 * @param fd Channel file descriptor to write to.
 * @param buf Data buffer
 * @param size Number of bytes to write
 * @return Length of message written.
 */
int ch_write_msg(int fd, char *buf, size_t size) {
    // todo
    return 0;
}

/**
 * @brief Read message from channel.
 * @param fd Channel file descriptor to read from
 * @param buf Data buffer to write to
 * @param size Maximum number of bytes to read
 * @return Number of bytes actually read
 */
int ch_read_msg(int fd, char *buf, size_t size) {
    // todo
    return 0;
}

/**
 * @brief Wait for message on channel.
 * @param chs Array of channels to wait on
 * @param nchs Number of channels in `chs`
 * @param timeout Maximum amount of time to wait (in milliseconds)
 * @return Number of channel descriptors in `chs` which received messages.
 */
int ch_poll(int *chs, int nchs, int timeout) {
    // todo
    return 0;
}

/**
 * @brief Get UUID of the current runtime.
 * @param buf Buffer to write UUID for. Should be at least 37 bytes.
 * @return 0 on success.
 */
int runtime_get_uuid(char *buf) {
    strcpy(buf, "native");
}

/**
 * @brief Get UUID of the current module.
 * @param buf Buffer to write UUID for. Should be at least 37 bytes.
 * @return 0 on success.
 */
int module_get_uuid(char *buf) {
    strcpy(buf, "native");
}

// Profiling requires runtime infrastructure support.
void period_start() {}
void period_end() {}
void period_set_flags(int flags) {}

/**
 * @brief End profiling period and yield remaining time.
 */
void period_yield() {
    // Only sched_yield; no profiling here.
    sched_yield();
}
