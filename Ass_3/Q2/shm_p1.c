#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define array_size 50
#define string_length 10
#define block_size 5
#define SHM_SIZE 1024
#define SHM_NAME "/tmp"
#define SEM_NAME "sem_shm2"

key_t SHM_KEY;
sem_t *sem;
char string_array[array_size][string_length + 1];
struct timespec begin, end;

void generate_string_array(){
    for(int i = 0; i < array_size; i++){
        for(int j = 0; j < string_length; j++){
            string_array[i][j] = (rand() % 26) + 97;
        }
        string_array[i][string_length] = '\0';
    }
}

void print_string_array(){
    for(int i = 0; i < array_size; i++){
        printf("%s\n", string_array[i]);
    }
}

int main(){

    srand(time(NULL));

    generate_string_array();
    // print_string_array();

    SHM_KEY = ftok(SHM_NAME, 'A');
    if(SHM_KEY == -1) {perror("ftok error"); exit(1);}
    int shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);    
    if(shmid == -1) {perror("shmget error"); exit(1);}

    char *shm = shmat(shmid, NULL, 0);
    if(shm == (char *)-1) {perror("shmat error"); exit(1);}

    sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);
    if(sem == SEM_FAILED) {perror("sem_open error"); exit(1);}

    sem_wait(sem);

    clock_gettime(CLOCK_REALTIME, &begin);

    char data[5*(string_length + 4)] = {0};
    for(int i = 0; i < block_size; i++){
        char num[1];
        sprintf(num, "%d", i + 1);
        strcat(data, "0");
        strcat(data, num);
        strcat(data, " ");
        strcat(data, string_array[i]);
    }
    sprintf(shm, "%s", data);
    printf("Sent: %s\n", data);

    sem_post(sem);
    sleep(10);

    int index = 0;

    while(index < array_size){
        sem_wait(sem);

        index = atoi(shm);
        printf("Recieved: %d\n", index);

        if(index >= array_size){
            printf("All strings sent\n");
            sem_post(sem);
            break;
        }

        char data[5*(string_length + 4)] = {0};
        for(int i = 0; i < block_size; i++){
            if((index + i)< 9){
                char num[1];
                sprintf(num, "%d", index + i + 1);
                strcat(data, "0");
                strcat(data, num);
                strcat(data, " ");
                strcat(data, string_array[index + i]);
            }else{
                char num[2];
                sprintf(num, "%d", index + i + 1);
                strcat(data, num);
                strcat(data, " ");
                strcat(data, string_array[index + i]);
            }
        }
        sprintf(shm, "%s", data);
        printf("Sent: %s\n", data);

        sem_post(sem);

        sleep(5);
    }

    clock_gettime(CLOCK_REALTIME, &end);
    float runtime = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1000000000.0;

    sem_unlink(SEM_NAME);

    printf("Runtime: %f\n", runtime);

    return 0;

}
