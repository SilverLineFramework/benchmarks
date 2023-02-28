#include <stdio.h>
#include <fcntl.h>

int main(void) {
    printf("hello world\n");

    /*int fd;
    char buf[256] = { 0 };

    fd = open("/home/jeremy/playground/io_test.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    size_t num_read = read(fd, buf, 10);
    printf("%s\n", buf);
    close(fd);*/
    return 0;
}
