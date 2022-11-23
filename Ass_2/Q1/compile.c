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

const char* COMPILE_A = "./runA.sh";
const char* COMPILE_B = "./runB.sh";
const char* COMPILE_C = "./runC.sh";

void setPid(int idx, pid_t pid){
    pids[idx] = pid;
}

void setBegin(int idx, struct timespec start_time){
    begin[idx] = start_time;
}

void setEnd(pid_t pid, struct timespec end_time){
    for(int i = 0; i < 3; i++) if(pids[i] == pid) end[i] = end_time;
}

int main(){

    pid_t child_pid, wpid;
    int status = 0;

    for(int i = 0; i < 3; i++){
        struct timespec curr_time; 
        clock_gettime(CLOCK_REALTIME, &curr_time); 
        setBegin(i, curr_time);
        if((child_pid = fork()) == 0){
            if(i == 0) execvp(COMPILE_A, NULL);
            else if(i == 1) execvp(COMPILE_B, NULL);
            else if(i == 2) execvp(COMPILE_C, NULL);
            exit(0);
        }else setPid(i, child_pid);
    }

    while((wpid = wait(&status)) > 0) {struct timespec curr_time; clock_gettime(CLOCK_REALTIME, &curr_time); setEnd(wpid, curr_time);}

    time_val[0] = (end[0].tv_sec - begin[0].tv_sec) + ((float)end[0].tv_nsec - begin[0].tv_nsec)/1000000000;
    time_val[1] = (end[1].tv_sec - begin[1].tv_sec) + ((float)end[1].tv_nsec - begin[1].tv_nsec)/1000000000;
    time_val[2] = (end[2].tv_sec - begin[2].tv_sec) + ((float)end[2].tv_nsec - begin[2].tv_nsec)/1000000000;

    // printf("%lds %ldms\n", begin[0].tv_sec, begin[0].tv_nsec);
    // printf("%lds %ldms\n", begin[1].tv_sec, begin[1].tv_nsec);
    // printf("%lds %ldms\n", begin[2].tv_sec, begin[2].tv_nsec);
    // printf("%lds %ldms\n", end[0].tv_sec, end[0].tv_nsec);
    // printf("%lds %ldms\n", end[1].tv_sec, end[1].tv_nsec);
    // printf("%lds %ldms\n", end[2].tv_sec, end[2].tv_nsec);
    // printf("%f s\n", time_val[0]);
    // printf("%f s\n", time_val[1]);
    // printf("%f s\n", time_val[2]);

    FILE* fout = fopen("compile_time.txt", "a+");
    fprintf(fout, "%f %f %f\n", time_val[0], time_val[1], time_val[2]);
    fclose(fout);

    return 0;

}