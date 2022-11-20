#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

pid_t pids[3];
struct timespec begin[3];
struct timespec end[3];
float time_val[3];

const char* SCRIPT_A = "bash runA.sh";
const char* SCRIPT_B = "bash runB.sh";
const char* SCRIPT_C = "bash runC.sh";

void setPid(int idx, pid_t pid){
    pids[idx] = pid;
}

void setBegin(int idx, timespec start_time){
    begin[idx] = start_time;
}

void setEnd(pid_t pid, timespec end_time){
    for(int i = 0; i < 3; i++) if(pids[i] == pid) end[i] = end_time;
}

int main(){

    pid_t child_pid, wpid;
    int status = 0;

    for(int i = 0; i < 3; i++){
        if((child_pid = fork()) == 0){
            if(i == 0) {execl(SCRIPT_A, (char *)NULL); printf("Called A\n");}
            else if(i == 1) execl(SCRIPT_B, (char *)NULL);
            else if(i == 2) execl(SCRIPT_C, (char *)NULL);
            exit(0);
        }else printf("%d\n", child_pid);
    }

    while((wpid = wait(&status)) > 0) printf("%d\n", wpid);

    time_val[0] = (end[0].tv_sec - begin[0].tv_sec) + ((float)end[0].tv_nsec - begin[0].tv_nsec)/1000000000;
    time_val[1] = (end[1].tv_sec - begin[1].tv_sec) + ((float)end[1].tv_nsec - begin[1].tv_nsec)/1000000000;
    time_val[2] = (end[2].tv_sec - begin[2].tv_sec) + ((float)end[2].tv_nsec - begin[2].tv_nsec)/1000000000;

    printf("%f s\n", time_val[0]);
    printf("%f s\n", time_val[1]);
    printf("%f s\n", time_val[2]);

    return 0;

}