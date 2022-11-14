#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

void* countA(){
    int up_limit = 1<<32, cur_cnt = 0;
    for(int i = 0; i < up_limit; i++) cur_cnt++;
    return;
}

void* countB(){
    int up_limit = 1<<32, cur_cnt = 0;
    for(int i = 0; i < up_limit; i++) cur_cnt++;
    return;
}

void* countC(){
    int up_limit = 1<<32, cur_cnt = 0;
    for(int i = 0; i < up_limit; i++) cur_cnt++;
    return;
}

int main(){



    return 0;

}