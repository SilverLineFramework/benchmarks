#include <stdlib.h>
#include <stdio.h>

#define NUM_REQUESTS 100

int main() {
  srand(time(NULL));
  if (init_database() == -1) {
    printf("Database initialization error!\n");
  }

  for (int i = 0; i < NUM_REQUESTS, i++) {
    action_t act = rand() % NUM_ACTIONS;
    switch (act) {
      case READ: client_read(); break;
      case WRITE: {
                    qelem elem = { .id = rand() % 100, .val = rand() }
                    break;
                  }
      case WAIT_UNTIL: {
                         //qelem elem = client_wait_until(((uint64_t)rand()) % 100);
                         break;
                       }
      case GET_QSIZE: {
                        uint32_t qsize = client_get_queue_size();
                        break;
                      }
      default: {
              printf("Invalid action! Exiting..\n");
              exit(1);
               }
    }
  }
}
