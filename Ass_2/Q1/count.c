#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

pthread_t tid1, tid2, tid3;
int OTHER_PRIORITY, RR_PRIORITY, FIFO_PRIORITY;
struct sched_param p1;
struct sched_param p2;
struct sched_param p3;
struct timespec begin[3];
struct timespec end[3];
float time_val[3];

void* countA(void* arg){
    clock_gettime(CLOCK_REALTIME, &begin[0]);
    p1.sched_priority = OTHER_PRIORITY;
    pthread_setschedparam(tid1, (int)SCHED_OTHER, &p1);
    long long int up_limit = (long long int)1<<32, cur_cnt = 0;
    for(long long int i = 0; i < up_limit; i++) cur_cnt++;
    clock_gettime(CLOCK_REALTIME, &end[0]);
}

void* countB(void* arg){
    clock_gettime(CLOCK_REALTIME, &begin[1]);
    p2.sched_priority = RR_PRIORITY;
    pthread_setschedparam(tid2, (int)SCHED_RR, &p2);
    long long int up_limit = (long long int)1<<32, cur_cnt = 0;
    for(long long int i = 0; i < up_limit; i++) cur_cnt++;
    clock_gettime(CLOCK_REALTIME, &end[1]);
}

void* countC(void* arg){
    clock_gettime(CLOCK_REALTIME, &begin[2]);
    p3.sched_priority = FIFO_PRIORITY;
    pthread_setschedparam(tid3, (int)SCHED_FIFO, &p3);
    long long int up_limit = (long long int)1<<32, cur_cnt = 0;
    for(long long int i = 0; i < up_limit; i++) cur_cnt++;
    clock_gettime(CLOCK_REALTIME, &end[2]);
}

int main(int argc, char* argv[]){

    OTHER_PRIORITY = atoi(argv[1]);
    RR_PRIORITY = atoi(argv[2]);
    FIFO_PRIORITY = atoi(argv[3]);

    pthread_create(&tid1, NULL, countA, NULL);
    pthread_create(&tid2, NULL, countB, NULL);
    pthread_create(&tid3, NULL, countC, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    time_val[0] = (end[0].tv_sec - begin[0].tv_sec) + ((float)end[0].tv_nsec - begin[0].tv_nsec)/1000000000;
    time_val[1] = (end[1].tv_sec - begin[1].tv_sec) + ((float)end[1].tv_nsec - begin[1].tv_nsec)/1000000000;
    time_val[2] = (end[2].tv_sec - begin[2].tv_sec) + ((float)end[2].tv_nsec - begin[2].tv_nsec)/1000000000;

    // printf("%lds %ldms\n", begin[0].tv_sec, begin[0].tv_nsec);
    // printf("%lds %ldms\n", begin[1].tv_sec, begin[1].tv_nsec);
    // printf("%lds %ldms\n", begin[2].tv_sec, begin[2].tv_nsec);
    // printf("%lds %ldms\n", end[0].tv_sec, end[0].tv_nsec);
    // printf("%lds %ldms\n", end[1].tv_sec, end[1].tv_nsec);
    // printf("%lds %ldms\n", end[2].tv_sec, end[2].tv_nsec);
    printf("%f s\n", time_val[0]);
    printf("%f s\n", time_val[1]);
    printf("%f s\n", time_val[2]);

    return 0;

}