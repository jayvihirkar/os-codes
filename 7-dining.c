/* Dining Philosopher Problem using Semaphores and Mutex
   Compile: gcc dining_philosopher.c -lpthread
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5   // Number of philosophers

sem_t chopstick[N];      // Semaphore for each chopstick
pthread_t phil[N];       // Philosopher threads
int phil_num[N];         // Philosopher numbers

// Function for philosopher actions
void *philosopher(void *num)
{
    int id = *(int *)num;

    while (1)
    {
        // Thinking
        printf("Philosopher %d is Thinking\n", id);
        sleep(1);

        // Hungry
        printf("Philosopher %d is Hungry\n", id);

        // Pick up left chopstick
        sem_wait(&chopstick[id]);
        printf("Philosopher %d picked up Left Chopstick %d\n", id, id);

        // Pick up right chopstick
        sem_wait(&chopstick[(id + 1) % N]);
        printf("Philosopher %d picked up Right Chopstick %d\n",
               id, (id + 1) % N);

        // Eating
        printf("Philosopher %d is Eating\n", id);
        sleep(2);

        // Put down right chopstick
        sem_post(&chopstick[(id + 1) % N]);

        // Put down left chopstick
        sem_post(&chopstick[id]);

        printf("Philosopher %d finished Eating and released Chopsticks\n", id);

        sleep(1);
    }
}

int main()
{
    int i;

    // Initialize semaphores for chopsticks
    for (i = 0; i < N; i++)
    {
        sem_init(&chopstick[i], 0, 1);
        phil_num[i] = i;
    }

    // Create philosopher threads
    for (i = 0; i < N; i++)
    {
        pthread_create(&phil[i], NULL, philosopher, &phil_num[i]);
    }

    // Wait for threads (program runs indefinitely)
    for (i = 0; i < N; i++)
    {
        pthread_join(phil[i], NULL);
    }

    // Destroy semaphores
    for (i = 0; i < N; i++)
    {
        sem_destroy(&chopstick[i]);
    }

    return 0;
}