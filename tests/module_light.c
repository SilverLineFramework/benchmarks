#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>    

#define MAT_SIZE 50

void mat_multiply () {
    double mat_a[MAT_SIZE] [MAT_SIZE];
    double mat_b[MAT_SIZE] [MAT_SIZE];
    double mat_c[MAT_SIZE] [MAT_SIZE];
    int i, j, k;
    
    srand(0);
    for(i = 0; i < MAT_SIZE; i++){
        for (j = 0 ; j < MAT_SIZE; j++) {
            mat_a[i][j] = rand() % 500 + 1;
            mat_b[i][j] = rand() % 500 + 1;
            mat_c[i][j] = 0.0;
        }
    }

    for(i = 0; i < MAT_SIZE; i++) {
        for(j = 0; j < MAT_SIZE; j++) {
            for(k = 0; k < MAT_SIZE; k++) {
                mat_c[i][j] += mat_a[i][k] * mat_b[k][j];
            }
            
        }
    }
}

/* msleep(): Sleep for the requested number of milliseconds. */
int msleep(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}


int main(void) {
    while (1) {
        mat_multiply();
        msleep(100);
    }    
}


