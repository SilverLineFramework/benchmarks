#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

    printf("Starting!\n");

    sleep(1);

    printf("initiating crash...\n");
    while (1) {
        abort();
    }
}
