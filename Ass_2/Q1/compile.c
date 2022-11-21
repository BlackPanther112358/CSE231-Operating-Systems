#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

pid_t pids[3];
struct timespec begin[3];
struct timespec end[3];
float time_val[3];

const char* SCRIPT_A = "./runA.sh";
const char* SCRIPT_B = "./runB.sh";
const char* SCRIPT_C = "./runC.sh";

void setPid(int idx, pid_t pid){
    pids[idx] = pid;
}

void setBegin(int idx, struct timespec start_time){
    printf("Setting %d at %lds %ld ns\n", idx, start_time.tv_sec, start_time.tv_nsec);
    begin[idx] = start_time;
}

void setEnd(pid_t pid, struct timespec end_time){
    printf("Setting %d at %lds %ld ns\n", pid, end_time.tv_sec, end_time.tv_nsec);
    for(int i = 0; i < 3; i++) if(pids[i] == pid) end[i] = end_time;
}

int main(){

    pid_t child_pid, wpid;
    int status = 0;

    for(int i = 0; i < 3; i++){
        if((child_pid = fork()) == 0){
            if(i == 0) {struct timespec curr_time; clock_gettime(CLOCK_REALTIME, &curr_time); setBegin(i, curr_time); execvp(SCRIPT_A, NULL);}
            else if(i == 1) {struct timespec curr_time; clock_gettime(CLOCK_REALTIME, &curr_time); setBegin(i, curr_time); execvp(SCRIPT_B, NULL);}
            else if(i == 2) {struct timespec curr_time; clock_gettime(CLOCK_REALTIME, &curr_time); setBegin(i, curr_time); execvp(SCRIPT_C, NULL);}
            exit(0);
        }else {setPid(i, child_pid); printf("%d\n", child_pid);}
    }

    // Set endtimes here
    while((wpid = wait(&status)) > 0) {struct timespec curr_time; clock_gettime(CLOCK_REALTIME, &curr_time); setEnd(wpid, curr_time); printf("ENDING: %lds %ldms\n", curr_time.tv_sec, curr_time.tv_nsec);}

    time_val[0] = (end[0].tv_sec - begin[0].tv_sec) + ((float)end[0].tv_nsec - begin[0].tv_nsec)/1000000000;
    time_val[1] = (end[1].tv_sec - begin[1].tv_sec) + ((float)end[1].tv_nsec - begin[1].tv_nsec)/1000000000;
    time_val[2] = (end[2].tv_sec - begin[2].tv_sec) + ((float)end[2].tv_nsec - begin[2].tv_nsec)/1000000000;

    printf("%lds %ldms\n", begin[0].tv_sec, begin[0].tv_nsec);
    printf("%lds %ldms\n", begin[1].tv_sec, begin[1].tv_nsec);
    printf("%lds %ldms\n", begin[2].tv_sec, begin[2].tv_nsec);
    printf("%lds %ldms\n", end[0].tv_sec, end[0].tv_nsec);
    printf("%lds %ldms\n", end[1].tv_sec, end[1].tv_nsec);
    printf("%lds %ldms\n", end[2].tv_sec, end[2].tv_nsec);
    printf("%ld s\n", time_val[0]);
    printf("%ld s\n", time_val[1]);
    printf("%ld s\n", time_val[2]);

    return 0;

}