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

int main(){

    int val = syscall(kernel_read_task, 1, 2);
    if(val < 0){
        printf("ERROR ENCOUNTERED\n");
        exit(1);
    }

    return 0;

}