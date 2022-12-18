#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#define PHILOSOPHER_CNT 5   // Set number of Philosophers
#define HUNGER 2            // Set number of times each philosopher eats

typedef struct FORK{
    int id;
    pthread_mutex_t *fork;
}FORK;

typedef struct PHILOSOPHER{
    int id;
    pthread_t pid;
    int parity;
    int hunger;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
}PHILOSOPHER;

FORK forks[PHILOSOPHER_CNT];
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

void generate_philosophers(){
    for(int i = 0; i < PHILOSOPHER_CNT; i++){
        philosophers[i].id = i;
        philosophers[i].parity = (i == 4) ? 1 : 0;
        philosophers[i].pid = (pthread_t)i;
        philosophers[i].hunger = HUNGER;
        philosophers[i].left_fork = forks[i].fork;
        philosophers[i].right_fork = forks[(i + 1) % PHILOSOPHER_CNT].fork;
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
        printf("Philosopher %d is eating\n", philosopher->id);
        sleep(get_random_integer());
        pthread_mutex_unlock(philosopher->left_fork);
        pthread_mutex_unlock(philosopher->right_fork);
        printf("Philosopher %d is thinking\n", philosopher->id);
        sleep(get_random_integer());
    }
    printf("Philosopher %d leaves the table\n", philosopher->id);
    return NULL;
}

int main(){

    srand(time(NULL));

    generate_forks();
    generate_philosophers();

    for(int i = 0; i < PHILOSOPHER_CNT; i++)
        pthread_create(&philosophers[i].pid, NULL, philosopher_simulate, &philosophers[i]);

    for(int i = 0; i < PHILOSOPHER_CNT; i++)
        pthread_join(philosophers[i].pid, NULL);

    return 0;

}