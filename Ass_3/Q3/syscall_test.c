#define _GNU_SOURCE
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <errno.h>

#define kernel_read_task 451

int main(int argc, char *argv[]){

    if(argc != 2){
        printf("ERROR: Invalid number of arguments\n");
        exit(1);
    }else printf("PID: %d\n", atoi(argv[1]));
    int val = syscall(kernel_read_task, atoi(argv[1]), 5);
    if(val < 0){
        printf("ERROR ENCOUNTERED\n");
        exit(1);
    }

    return 0;

}