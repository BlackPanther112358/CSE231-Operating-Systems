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
#define SEM_NAME "sem_shm3"

key_t SHM_KEY;
sem_t *sem;
char string_array[array_size][string_length + 1];

int main(){

    sleep(5);

    SHM_KEY = ftok(SHM_NAME, 'A');
    if(SHM_KEY == -1) {perror("ftok error"); exit(1);}
    int shmid = shmget(SHM_KEY, SHM_SIZE, 0666);    
    if(shmid == -1) {perror("shmget error"); exit(1);}

    char *shm = shmat(shmid, NULL, 0);
    if(shm == (char *)-1) {perror("shmat error"); exit(1);}

    sem = sem_open(SEM_NAME, 0);
    if(sem == SEM_FAILED) {perror("sem_open error"); exit(1);}

    int index = 0;

    while(index < array_size){
        sem_wait(sem);

        char data[5*(string_length + 1)] = {0};
        memcpy(data, shm, 5*(string_length + 1));
        // printf("Recieved %s\n", data);
        int itr = 0;
        for(int i = 0; i < block_size; i++){
            char idx[2];
            idx[0] = data[itr++];
            idx[1] = data[itr++];
            idx[2] = '\0';
            itr++;
            index = atoi(idx);
            if(index > array_size){
                printf("Recieved all the strings\n");
                break;
            }else printf("Recieved ID: %d\n", index);
            for(int j = 0; j < string_length; j++){
                string_array[index - 1][j] = data[itr];
                itr++;
            }
        }

        sprintf(shm, "%d", index);
        printf("Acknowledge ID: %d\n", index);

        sem_post(sem);

        sleep(5);
    }

    sem_unlink(SEM_NAME);

    return 0;

}