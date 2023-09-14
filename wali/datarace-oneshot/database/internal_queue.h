#include "database.h"
#include <pthread.h>

#define QSIZE 500

typedef struct {
  qelem buf[QSIZE];
  int head;
  int tail;
} internal_queue_t;

void init_internal_queue ();

bool internal_queue_enqueue(qelem elem);
bool internal_queue_dequeue(qelem *elem);
