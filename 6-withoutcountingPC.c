/* Producer-Consumer Problem using Binary Semaphores and Mutex */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

/* Binary semaphores (values only 0 or 1) */
sem_t empty = 1;   // Indicates whether buffer has at least one empty slot
sem_t full = 0;    // Indicates whether buffer has at least one filled slot

/* Mutex lock */
pthread_mutex_t mutex;

/* Producer Function */
void *producer(void *arg)
{
    int item, i;

    for (i = 1; i <= 10; i++)
    {
        item = rand() % 100;

        sem_wait(&empty);              // Wait if buffer is considered full
        pthread_mutex_lock(&mutex);    // Enter critical section

        buffer[in] = item;
        printf("Producer produced: %d at position %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);  // Exit critical section
        sem_post(&full);               // Signal that data is available

        sleep(1);
    }

    pthread_exit(NULL);
}

/* Consumer Function */
void *consumer(void *arg)
{
    int item, i;

    for (i = 1; i <= 10; i++)
    {
        sem_wait(&full);               // Wait until an item is available
        pthread_mutex_lock(&mutex);    // Enter critical section

        item = buffer[out];
        printf("Consumer consumed: %d from position %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);  // Exit critical section
        sem_post(&empty);              // Signal that buffer is empty again

        sleep(2);
    }

    pthread_exit(NULL);
}

/* Main Function */
int main()
{
    pthread_t prod, cons;

    /* Initialize binary semaphores */
    sem_init(&empty, 0, 1);   // Binary semaphore
    sem_init(&full, 0, 0);    // Binary semaphore

    /* Initialize mutex */
    pthread_mutex_init(&mutex, NULL);

    /* Create threads */
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    /* Wait for threads to finish */
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    /* Destroy semaphores and mutex */
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}