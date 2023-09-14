#include <stdint.h>
#include "database.h"
#include "internal_queue.h"

internal_queue_t internal_queue;

void init_internal_queue () {
  internal_queue.head = 0;
  internal_queue.tail = 0;
}

static bool isempty() {
  return internal_queue.head == internal_queue.tail;
}

static bool isfull() {
  return (internal_queue->head == internal_queue->tail + 1) || 
          ((internal_queue->head == 0) && (internal_queue->tail == (QSIZE-1)));
}

bool internal_queue_enqueue(qelem elem) {
  if (isfull()) {
    return false;
  }
  internal_queue.buf[internal_queue->tail++] = elem;
  if (internal_queue.tail == QSIZE) {
    internal_queue.tail = 0;
  }
  return true;
}

bool internal_queue_dequeue(qelem *elem) {
  if (isempty()) {
    return false;
  }
  *elem = internal_queue->buf[internal_queue->head];
  if (internal_queue->head == QSIZE) {
    internal_queue->head = 0;
  }
  return true;
}


