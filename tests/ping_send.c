#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <getopt.h>
#include "api.h"

#define MS 1000
#define ERR(...) do { fprintf(stderr, __VA_ARGS__); } while(0)

void gettime(struct timespec *ts) {
	clock_gettime(CLOCK_REALTIME, ts);
}

long get_rtt_time(struct timespec send_ts, struct timespec recv_ts) {
	long send_usec = (long)(send_ts.tv_sec) * 1000000 + (long)(send_ts.tv_nsec) / 1000;
	long recv_usec = (long)(recv_ts.tv_sec) * 1000000 + (long)(recv_ts.tv_nsec) / 1000;
	return recv_usec - send_usec;
}


static struct option long_options[] = {
	{"topicid", required_argument, NULL, 't'},
	{"interval", optional_argument, NULL, 'm'},
	{"iterations", optional_argument, NULL, 'i'},
	{"size", optional_argument, NULL, 's'}
};

char* TOPIC_ID = "default";
uint32_t MSG_INTERVAL = 10*MS;
uint32_t MAX_ITER = 20;
uint32_t PAYLOAD_SIZE = 64;

void parse_args(int argc, char* argv[]) {
  int opt;
  while ((opt = getopt_long(argc, argv, "t:m:i:s:h", long_options, NULL)) != -1) {
    switch(opt) {
      case 'm': MSG_INTERVAL = atoi(optarg);            break;
      case 'i': MAX_ITER = atoi(optarg);                break;
      case 's': PAYLOAD_SIZE = atoi(optarg);            break;
      case 't': TOPIC_ID = optarg;    break;
      case 'h':
      default:
        ERR("Usage: %s [--topicid=TOPIC_ID (str)]"
                      "[--interval=INTERVAL (us)] [--iterations=ITERATIONS (int)] "
                      "[--size=SIZE (int)]\n",
                      argv[0]);
        exit(0);
    }
  }

  printf("----- Configuration -----\n");
  printf("  Topic ID  		: %s\n", TOPIC_ID);
  printf("  Msg Interval  : %d\n", MSG_INTERVAL);
  printf("  Iterations    : %d\n", MAX_ITER);
  printf("  Msg Size      : %d\n", PAYLOAD_SIZE);
  printf("-------------------------\n");
  return;
}

int main(int argc, char* argv[]) {
	parse_args(argc, argv);
	char send_path[60];
	char recv_path[60];
	sprintf(send_path, "test/ping_send_%s", TOPIC_ID);
	sprintf(recv_path, "test/ping_recv_%s", TOPIC_ID);

	int fd_rd = ch_open(recv_path, CH_RDONLY, 0);
	int fd_sd = ch_open(send_path, CH_WRONLY, 0);

	struct timespec send_ts;
	struct timespec recv_ts;

	int ct_val = 1;
	char* packet = malloc(PAYLOAD_SIZE);
	packet[sizeof(int)] = 0;
	long* results = malloc(MAX_ITER * sizeof(long));
		
	for (int i = 0; i < MAX_ITER; i++) {
		// Get send time
		gettime(&send_ts);
		memcpy(packet, &ct_val, sizeof(int));
		ch_write_msg(fd_sd, packet, PAYLOAD_SIZE);
		while (!ch_poll(&fd_rd, 1, 10000)) { };

		int recv_val;
		ch_read_msg(fd_rd, packet, PAYLOAD_SIZE);
		memcpy(&recv_val, packet, sizeof(int));
		// Get recv time
		gettime(&recv_ts);
		if (recv_val != ct_val + 0xDEADBEEF) {
			printf("Invalid\n");
		}
		else {
			results[i] = get_rtt_time(send_ts, recv_ts);
			printf("RTT time: %lu\n", results[i]);
		}
		ct_val++;
		// Wait
		long sleep_time = MSG_INTERVAL - results[i];
		sleep_time = ((sleep_time < 0) ? 0 : sleep_time);
		usleep(sleep_time);
	}

	// Send end packet: ct = 0
	int zero_val = 0;
	memcpy(packet, &zero_val, sizeof(int));
	ch_write_msg(fd_sd, packet, PAYLOAD_SIZE);

	char outfile[60];
	sprintf(outfile, "%s.results", TOPIC_ID);
	FILE *fp = fopen(outfile, "w");
	for (int i = 0; i < MAX_ITER; i++) {
		fprintf(fp, "%lu,", results[i]);
	}
}
