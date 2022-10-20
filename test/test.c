#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

int check(){
    int a = 5;
    int rc = fork();
    if(rc > 0){
        a += 1;
        wait(NULL);
    }else if(rc == 0) a += 2;
    return a;
}

int swap(int a, int b){
    int c;
    c = b;
    printf("%d %d %d\n", a, b, c);
    b = a;
    printf("%d %d %d\n", a, b, c);
    a = c;
    printf("%d %d %d\n", a, b, c);
}

int main(){
    int x = 3, y = 4;
    swap(x, y);
    printf("%d %d", x, y);
    return 0;
}