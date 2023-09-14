#include <stdbool.h>
#include <stdint.h>

#define MAX_CLIENTS 5

typedef enum {
  READ,
  WRITE,
  WAIT_UNTIL,
  GET_QSIZE,
  NUM_ACTIONS
} action_t;

typedef struct {
  action_t action;
  void *args;
} message_t;


typedef qelem {
  uint64_t id;
  /* Element value */
  int val;
};


int init_database();

int init_client();

qelem client_read(void);
bool client_write(qelem elem);
qelem client_wait_until(uint64_t id);
uint32_t client_get_queue_size(void);

void destroy_client(int cid);

