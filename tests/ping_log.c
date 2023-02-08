#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <getopt.h>
#include "api.h"

#define MS 1000
#define ERR(...) do { fprintf(stderr, __VA_ARGS__); } while(0)

void gettime(struct timespec *ts) {
	clock_gettime(CLOCK_REALTIME, ts);
}

uint64_t ts2us(struct timespec *ts) {
  return (uint64_t)(ts->tv_sec * 1000000) + (uint64_t)(ts->tv_nsec / 1000);
}

static struct option long_options[] = {
	{"topicid", required_argument, NULL, 't'},
	{"interval", optional_argument, NULL, 'm'},
	{"iterations", optional_argument, NULL, 'i'},
	{"size", optional_argument, NULL, 's'},
	{"interf", optional_argument, NULL, 'f'}
};

char* TOPIC_ID = "default";
uint32_t MSG_INTERVAL = 10*MS;
uint32_t MAX_ITER = 20;
uint32_t PAYLOAD_SIZE = 64;
uint32_t INTERF = 0;

void parse_args(int argc, char* argv[]) {
  int opt;
  while ((opt = getopt_long(argc, argv, "t:m:i:s:f:h", long_options, NULL)) != -1) {
    switch(opt) {
      case 'm': MSG_INTERVAL = atoi(optarg);            break;
      case 'i': MAX_ITER = atoi(optarg);                break;
      case 's': PAYLOAD_SIZE = atoi(optarg);            break;
      case 't': TOPIC_ID = optarg + 1;    break;
      case 'f': INTERF = atoi(optarg);    break;
      case 'h':
      default:
        ERR("Usage: %s [--topicid=TOPIC_ID (str)]"
                      "[--interval=INTERVAL (us)] [--iterations=ITERATIONS (int)] "
                      "[--size=SIZE (int)] [--interf=INTERF (int)]\n",
                      argv[0]);
        exit(0);
    }
  }

  printf("----- Configuration -----\n");
  printf("  Topic ID  		: %s\n", TOPIC_ID);
  printf("  Msg Interval  : %d\n", MSG_INTERVAL);
  printf("  Iterations    : %d\n", MAX_ITER);
  printf("  Msg Size      : %d\n", PAYLOAD_SIZE);
  printf("  Interf      	: %d\n", INTERF);
  printf("-------------------------\n");
  return;
}


int main(int argc, char* argv[]) {
  parse_args(argc, argv);

  struct timespec recv_ts;
	char recv_path[60];
	sprintf(recv_path, "test/ping_recv/%s", TOPIC_ID);

	int fd_rd = ch_open(recv_path, CH_RDONLY, 0);

	char recv_packet[65536];
	int ct_val = 1;

	uint64_t* results = malloc(MAX_ITER * sizeof(uint64_t));
  int num_dropped = 0;

	while(1) {
		while (!ch_poll(&fd_rd, 1, 10000)) { };
		int size = ch_read_msg(fd_rd, recv_packet, PAYLOAD_SIZE);
    gettime(&recv_ts);
    uint64_t recv_time = ts2us(&recv_ts);

		int ct_recv_val;
		memcpy(&ct_recv_val, recv_packet, sizeof(int));

		// Check for end packet: val = 0
    if (ct_recv_val == 0) {
			printf("End packet found\n");
			break;
		}
    else if (ct_recv_val != ct_val + 0xDEADBEEF) {
			printf("Invalid offset; packet dropped");
    }

    uint64_t send_time;
    memcpy(&send_time, recv_packet + sizeof(int), sizeof(uint64_t));
    uint64_t rtt_time = recv_time - send_time;
    results[ct_val-1] = rtt_time;
    printf("RTT time: %llu\n", rtt_time);

    ct_val++;
	}

	char outfile[60];

	sprintf(outfile, "nw_results/if%u_i%u_m%u_s%u.results", INTERF, MAX_ITER, MSG_INTERVAL, PAYLOAD_SIZE);
	FILE *fp = fopen(outfile, "w");
	for (int i = 0; i < MAX_ITER; i++) {
		fprintf(fp, "%llu,", results[i]);
	}

	// Signal end of test
	char done_topic[] = "test/finish";
	int fd_done = ch_open(done_topic, CH_WRONLY, 0);
	ch_write_msg(fd_done, &ct_val, 1);
}
