#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "jsmn.h"

int ch_open(const char *path, int flags, mode_t mode);
int ch_write_msg(int fd, char *buf, size_t size);
int ch_read_msg(int fd, char *buf, size_t size);
int ch_poll(int *chs, int nchs, int timeout);

#define BUFLEN 8192

/* const char *scene_ch = "realm/s/public/arts-meeting2/myClient/43d2c2f0-9155-47a3-92d8-59ec8d4ccfe5"; */
char *create_msg = "{\"object_id\": \"16906644-b34f-4a69-bc23-d5fabd4de9aa\", \"type\": \"object\", \"persist\": false, \"data\": {\"object_type\": \"box\", \"position\": {\"x\": \"5\", \"y\": \"5\", \"z\": \"5\"}, \"click-listener\": \"true\"}, \"action\": \"create\"}"; //, \"timestamp\": \"2021-02-16T22:34:14.386Z\"}"
char *blue_msg = "{\"object_id\": \"16906644-b34f-4a69-bc23-d5fabd4de9aa\", \"type\": \"object\", \"persist\": false, \"data\": {\"object_type\": \"box\", \"position\": {\"x\": \"5\", \"y\": \"5\", \"z\": \"5\"}, \"color\": \"blue\", \"click-listener\": \"true\"}, \"action\": \"update\"}";
char *red_msg = "{\"object_id\": \"16906644-b34f-4a69-bc23-d5fabd4de9aa\", \"type\": \"object\", \"persist\": false, \"data\": {\"object_type\": \"box\", \"position\": {\"x\": \"5\", \"y\": \"5\", \"z\": \"5\"}, \"color\": \"red\", \"click-listener\": \"true\"}, \"action\": \"update\"}";

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
  if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
      strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
    return 0;
  }
  return -1;
}

int main(void) {
  jsmn_parser prsr;
  jsmntok_t toks[256];
  char buf[BUFLEN];
  int blue = 1;
  char *update_msg = blue_msg;

  jsmn_init(&prsr);

  int cd_write = ch_open("/ch/box", 0, 0);
  int cd_read = ch_open("/ch/events", 0, 0);

  ch_write_msg(cd_write, create_msg, strlen(create_msg));

  while(1) {
    int i;
    ch_read_msg(cd_read, buf, BUFLEN);
    sleep(2);
    printf("here %s\n", buf);
    int r = jsmn_parse(&prsr, buf, strlen(buf), toks, 256);
    if (r < 0) {
      printf("failed to parse\n");
    }

    for (i = 0; i < r; i++) {
      printf("looping\n");
      if (jsoneq(buf, &toks[i], "type") == 0 &&
          jsoneq(buf, &toks[i+1], "mousedown") == 0) {
        printf("here?\n");
        ch_write_msg(cd_write, update_msg, strlen(update_msg));
        break;
      }
    }


    update_msg = blue ? blue_msg : red_msg;
    if (blue) {
      update_msg = blue_msg;
    } else {
      update_msg = red_msg;
    }


    blue = !blue;
    sleep(3);
  }



  // Create a box
  // Create color changing buttons
  // poll for click events
  return 0;
}
