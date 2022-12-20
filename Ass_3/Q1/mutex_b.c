#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define PHILOSOPHER_CNT 5   // Set number of Philosophers
#define HUNGER 2            // Set number of times each philosopher eats
#define BOWL_CNT 2          // Set number of bowls

typedef struct FORK{
    int id;
    pthread_mutex_t *fork;
}FORK;

typedef struct BOWL{
    int id;
    sem_t *bowl;
}BOWL;

typedef struct PHILOSOPHER{
    int id;
    pthread_t pid;
    int parity;
    int hunger;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    sem_t *bowl;
}PHILOSOPHER;

FORK forks[PHILOSOPHER_CNT];
BOWL bowls[BOWL_CNT];
PHILOSOPHER philosophers[PHILOSOPHER_CNT];

int get_random_integer(){
    return 10 + rand() % 10;
}

void generate_forks(){
    for(int i = 0; i < PHILOSOPHER_CNT; i++){
        forks[i].id = i;
        forks[i].fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
        pthread_mutex_init(forks[i].fork, NULL);
    }
}

void generate_bowls(){
    for(int i = 0; i < BOWL_CNT; i++){
        bowls[i].id = i;
        bowls[i].bowl = (sem_t *)malloc(sizeof(sem_t));
        sem_init(bowls[i].bowl, 0, 1);
    }
}

void generate_philosophers(){
    for(int i = 0; i < PHILOSOPHER_CNT; i++){
        philosophers[i].id = i;
        philosophers[i].parity = (i == 4) ? 1 : 0;
        philosophers[i].pid = (pthread_t)i;
        philosophers[i].hunger = HUNGER;
        philosophers[i].left_fork = forks[i].fork;
        philosophers[i].right_fork = forks[(i + 1) % PHILOSOPHER_CNT].fork;
        philosophers[i].bowl = NULL;
    }
}

void* philosopher_simulate(void *arg){
    PHILOSOPHER *philosopher = (PHILOSOPHER *)arg;
    while(philosopher->hunger--){
        if(philosopher->parity == 0){
            pthread_mutex_lock(philosopher->left_fork);
            pthread_mutex_lock(philosopher->right_fork);
        }else{
            pthread_mutex_lock(philosopher->left_fork);
            pthread_mutex_lock(philosopher->right_fork);
        }
        int val = -1;
        sem_getvalue(bowls[0].bowl, &val);
        if(val) {sem_wait(bowls[0].bowl); philosopher->bowl = bowls[0].bowl;}
        else {sem_wait(bowls[1].bowl); philosopher->bowl = bowls[1].bowl;}
        printf("Philosopher %d is eating\n", philosopher->id);
        sleep(get_random_integer());
        pthread_mutex_unlock(philosopher->left_fork);
        pthread_mutex_unlock(philosopher->right_fork);
        sem_post(philosopher->bowl);
        printf("Philosopher %d is thinking\n", philosopher->id);
        sleep(get_random_integer());
    }
    printf("Philosopher %d leaves the table\n", philosopher->id);
    return NULL;
}

int main(){

    srand(time(NULL));

    generate_forks();
    generate_bowls();
    generate_philosophers();

    for(int i = 0; i < PHILOSOPHER_CNT; i++)
        pthread_create(&philosophers[i].pid, NULL, philosopher_simulate, &philosophers[i]);

    for(int i = 0; i < PHILOSOPHER_CNT; i++)
        pthread_join(philosophers[i].pid, NULL);

    return 0;

}