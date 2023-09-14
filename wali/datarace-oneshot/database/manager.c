#include "database.h"
#include "internal_queue.h"
#include <pthread.h>

/* Request queue implementation */
typedef struct {
  message_t msg;
  int client_id;
} request_t;

typedef struct {
  request_t buf[MAX_CLIENTS];
  int head;
  int tail;
  pthread_mutex_t lock;
} req_queue_t;

req_queue_t request_queue;

static bool qempty(req_queue_t *rq) {
  return rq->head == rq->tail; 
}

static bool qfull(req_queue_t *rq) {
  return (rq->head == rq->tail + 1) || 
          ((rq->head == 0) && (rq->tail == (REQUEST_QSIZE-1)));
}

bool qenqueue (req_queue_t *rq, request_t req) {
  bool retval = false;
  pthread_mutex_lock (&rq->lock);
  if (!qfull(rq)) {
    rq->buf[rq->tail++] = req;
    if (rq->tail == REQUEST_SIZE) {
      rq->tail = 0;
    }
    retval = true;
  }
  pthread_mutex_unlock (&req_queue->lock);
  return retval;
}

bool qdequeue (req_queue_t *rq, request_t *request) {
  bool retval = false;
  pthread_mutex_lock (&rq->lock);
  if (!qempty(rq)) {
    *request = rq->buf[rq->head++];
    if (rq->head == REQUEST_SIZE) {
      rq->head = 0;
    }
  }
  pthread_mutex_unlock (&rq->lock);
}

/* */

/* Response list */



void init_request_queue() {
  request_queue.head = 0;
  request_queue.tail = 0;
  pthread_mutex_init(&request_queue.lock);
  pthread_t req_tid;
  if (pthread_create(&req_tid, NULL, req_queue_message_handler, NULL)) {
    printf("Failed to spawn request queue message handler..\n");
    exit(1);
  }
}

int init_database() {
  init_request_queue ();
  /* init data structures */
  init_internal_queue();
}

int destroy_database() {
}

bool handler_done = false;
void req_queue_message_handler() {
  while (!handler_done) {
    if(!qempty(&request_queue)) {
      request_t request;
      qdequeue(&request_queue, &request);
      switch (action) {
        case READ: {
          qelem elem = internal_queue_dequeue(5
        }
      }
    }
  }
}



bool client_read(int cid, qelem *elem) {
  request_t req = { .client_id = cid, .action = READ };
}

bool client_write(int cid, qelem elem) {
  request_t req = { .client_id = cid, .action = WRITE, .args = &elem };
}

void client_wait_until(int cid, qelem *elem, uint64_t id) {
}

uint32_t client_get_queue_size(int cid) {
  request_t req = { .client_id = cid, .action = GET_QSIZE };
}
