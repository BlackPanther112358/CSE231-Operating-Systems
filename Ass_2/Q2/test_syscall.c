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

#define kernel_2D_memcpy 451

int main(){

    float matrix[5][5] = {{1.1, 1.2, 1.3, 1.4, 1.5}, {2.1, 2.2, 2.3, 2.4, 2.5}, {3.1, 3.2, 3.3, 3.4, 3.5}, {4.1, 4.2, 4.3, 4.4, 4.5}, {5.1, 5.2, 5.3, 5.4, 5.5}};
    float res[5][5];

    int val = syscall(kernel_2D_memcpy, matrix, res, 5, 5);
    if(val < 0){
        printf("ERROR ENCOUNTERED\n");
        exit(1);
    }

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(matrix[i][j] != res[i][j]){
                printf("LHS != RHS\n");
                return 0;
            }
        }
    }

    printf("LHS = RHS\n");

    return 0;

}