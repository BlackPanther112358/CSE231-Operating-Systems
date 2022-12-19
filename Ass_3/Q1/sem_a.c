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
#define WAITING 0           // State of philosopher while waiting for forks
#define EATING 1            // State of philosopher while eating
#define THINKING 2          // State of philosopher while thinking

typedef struct FORK{
    int id;
    sem_t *fork;
}FORK;

typedef struct PHILOSOPHER{
    int id;
    pthread_t pid;
    int hunger;
    int curr_state;
    sem_t *left_fork;
    sem_t *right_fork;
    struct PHILOSOPHER *left_philosopher;
    struct PHILOSOPHER *right_philosopher;
}PHILOSOPHER;

sem_t *can_pick_up_forks;

FORK forks[PHILOSOPHER_CNT];
PHILOSOPHER philosophers[PHILOSOPHER_CNT];

int get_random_integer(){
    return 10 + rand() % 10;
}

void generate_forks(){
    for(int i = 0; i < PHILOSOPHER_CNT; i++){
        forks[i].id = i;
        forks[i].fork = (sem_t *)malloc(sizeof(sem_t));
        sem_init(forks[i].fork, 0, 1);
    }
}

void generate_philosophers(){
    for(int i = 0; i < PHILOSOPHER_CNT; i++){
        philosophers[i].id = i;
        philosophers[i].pid = (pthread_t)i;
        philosophers[i].hunger = HUNGER;
        philosophers[i].curr_state = WAITING;
        philosophers[i].left_fork = forks[i].fork;
        philosophers[i].right_fork = forks[(i + 1) % PHILOSOPHER_CNT].fork;
    }
    for(int i = 0; i < 5; i++){
        philosophers[i].left_philosopher = (PHILOSOPHER *)malloc(sizeof(PHILOSOPHER));
        philosophers[i].left_philosopher = &philosophers[(i + 4) % PHILOSOPHER_CNT];
        philosophers[i].right_philosopher = (PHILOSOPHER *)malloc(sizeof(PHILOSOPHER));
        philosophers[i].right_philosopher = &philosophers[(i + 1) % PHILOSOPHER_CNT];
    }
}

bool pick_up_forks(PHILOSOPHER *philosopher){
    int val = -1;
    if((val = sem_trywait(can_pick_up_forks)) != 0){
        return false;
    }
    if(((philosopher->left_philosopher)->curr_state == EATING) || ((philosopher->right_philosopher)->curr_state == EATING)){
        sem_post(can_pick_up_forks);
        return false;
    }
    sem_wait(philosopher->left_fork);
    sem_wait(philosopher->right_fork);
    philosopher->curr_state = EATING;

    sem_post(can_pick_up_forks);
    return true;
}

void* philosopher_simulate(void *arg){
    PHILOSOPHER *philosopher = (PHILOSOPHER *)arg;
    while(philosopher->hunger--){
        philosopher->curr_state = WAITING;
        if(pick_up_forks(philosopher)){
            printf("Philosopher %d is eating\n", philosopher->id);
            sleep(get_random_integer());
        }else{
            sleep(1);
            philosopher->hunger++;
            continue;
        }
        sem_post(philosopher->left_fork);
        sem_post(philosopher->right_fork);
        philosopher->curr_state = THINKING;
        printf("Philosopher %d is thinking\n", philosopher->id);
        sleep(get_random_integer());
    }
    printf("Philosopher %d leaves the table\n", philosopher->id);
    return NULL;
}

int main(){

    srand(time(NULL));
    can_pick_up_forks = (sem_t *)malloc(sizeof(sem_t));
    sem_init(can_pick_up_forks, 0, 1);

    generate_forks();
    generate_philosophers();

    for(int i = 0; i < PHILOSOPHER_CNT; i++)
        pthread_create(&philosophers[i].pid, NULL, philosopher_simulate, &philosophers[i]);

    for(int i = 0; i < PHILOSOPHER_CNT; i++)
        pthread_join(philosophers[i].pid, NULL);

    return 0;

}