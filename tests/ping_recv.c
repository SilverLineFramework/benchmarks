#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "api.h"

char* TOPIC_ID = "default";

int main(int argc, char* argv[]) {
	if (argc > 1) {
		TOPIC_ID = argv[1];
	}
	char send_path[60];
	char recv_path[60];
	sprintf(send_path, "test/ping_send_%s", TOPIC_ID);
	sprintf(recv_path, "test/ping_recv_%s", TOPIC_ID);

	int fd_rd = ch_open(recv_path, CH_WRONLY, 0);
	int fd_sd = ch_open(send_path, CH_RDONLY, 0);

	char recv_packet[65536];
	int ct = 0;
	while(1) {
		while (!ch_poll(&fd_sd, 1, 10000)) { };
		int size = ch_read_msg(fd_sd, recv_packet, sizeof(int));
		int ct_recv_val;
		memcpy(&ct_recv_val, recv_packet, sizeof(int));

		// Check for end packet: val = 0
		if (ct_recv_val == 0) {
			printf("End packet found\n");
			break;
		}

		// Increment and send response packet
		ct_recv_val += 0xDEADBEEF;
		memcpy(recv_packet, &ct_recv_val, sizeof(int));
		ch_write_msg(fd_rd, recv_packet, size);
		printf("Send resp: %d\n", ct);
		ct++;
	}
}
