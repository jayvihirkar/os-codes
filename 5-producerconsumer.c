/* Producer-Consumer Problem using Counting Semaphores and Mutex Lock */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// Counting semaphores
sem_t empty;   // Number of empty slots
sem_t full;    // Number of filled slots

// Mutex lock for critical section
pthread_mutex_t mutex;

// Producer thread function
void *producer(void *arg)
{
    int item, i;

    for (i = 1; i <= 10; i++)
    {
        item = rand() % 100;   // Generate random item

        sem_wait(&empty);          // Decrement empty count
        pthread_mutex_lock(&mutex); // Enter critical section

        buffer[in] = item;
        printf("Producer produced %d at position %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&full);              // Increment full count

        sleep(1);
    }

    pthread_exit(NULL);
}

// Consumer thread function
void *consumer(void *arg)
{
    int item, i;

    for (i = 1; i <= 10; i++)
    {
        sem_wait(&full);            // Decrement full count
        pthread_mutex_lock(&mutex); // Enter critical section

        item = buffer[out];
        printf("Consumer consumed %d from position %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&empty);             // Increment empty count

        sleep(2);
    }

    pthread_exit(NULL);
}

// Main function
int main()
{
    pthread_t prod, cons;

    // Initialize counting semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // All buffer slots are initially empty
    sem_init(&full, 0, 0);            // No items initially

    // Initialize mutex lock
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}