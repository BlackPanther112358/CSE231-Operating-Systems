#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

pthread_t tid1, tid2, tid3;
struct sched_param p1;
struct sched_param p2;
struct sched_param p3;
struct timespec begin[3];
struct timespec end[3];

void* countA(void* arg){
    p1.sched_priority = 0;
    pthread_setschedparam(tid1, (int)SCHED_OTHER, &p1);
    long long int up_limit = (long long int)1<<32, cur_cnt = 0;
    for(long long int i = 0; i < up_limit; i++) cur_cnt++;
    printf("A finished\n");
}

void* countB(void* arg){
    p2.sched_priority = 0;
    pthread_setschedparam(tid2, (int)SCHED_RR, &p2);
    long long int up_limit = (long long int)1<<32, cur_cnt = 0;
    for(long long int i = 0; i < up_limit; i++) cur_cnt++;
    printf("B finished\n");
}

void* countC(void* arg){
    p3.sched_priority = 0;
    pthread_setschedparam(tid3, (int)SCHED_FIFO, &p3);
    long long int up_limit = (long long int)1<<32, cur_cnt = 0;
    for(long long int i = 0; i < up_limit; i++) cur_cnt++;
    printf("C finished\n");
}

int main(){

    clock_gettime(CLOCK_REALTIME, &begin[0]);
    pthread_create(&tid1, NULL, countA, NULL);
    clock_gettime(CLOCK_REALTIME, &begin[1]);
    pthread_create(&tid2, NULL, countB, NULL);
    clock_gettime(CLOCK_REALTIME, &begin[2]);
    pthread_create(&tid3, NULL, countC, NULL);

    pthread_join(tid1, NULL);
    clock_gettime(CLOCK_REALTIME, &end[0]);
    pthread_join(tid2, NULL);
    clock_gettime(CLOCK_REALTIME, &end[1]);
    pthread_join(tid3, NULL);
    clock_gettime(CLOCK_REALTIME, &end[2]);

    printf("%lds %ldms\n", begin[0].tv_sec, begin[0].tv_nsec);
    printf("%lds %ldms\n", begin[1].tv_sec, begin[1].tv_nsec);
    printf("%lds %ldms\n", begin[2].tv_sec, begin[2].tv_nsec);
    printf("%lds %ldms\n", end[0].tv_sec, end[0].tv_nsec);
    printf("%lds %ldms\n", end[1].tv_sec, end[1].tv_nsec);
    printf("%lds %ldms\n", end[2].tv_sec, end[2].tv_nsec);

    return 0;

}