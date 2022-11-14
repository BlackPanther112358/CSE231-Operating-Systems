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
#include <sys/time.h>

pthread_t tid1, tid2, tid3;
struct sched_param p1;
struct sched_param p2;
struct sched_param p3;

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

    pthread_create(&tid1, NULL, countA, NULL);
    pthread_create(&tid2, NULL, countB, NULL);
    pthread_create(&tid3, NULL, countC, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    return 0;

}