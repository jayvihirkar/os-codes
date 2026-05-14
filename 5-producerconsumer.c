#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int count = 0;

sem_t mutex; // Declares a semaphore

void *producer(void *arg) {

    for(int i=0;i<100000;i++) {

        sem_wait(&mutex); // accquires lock, if already locked, thread waits

        count++;

        sem_post(&mutex); // releases lock
    }

    return NULL;
}

void *consumer(void *arg) {

    for(int i=0;i<100000;i++) {

        sem_wait(&mutex); // ~

        count--;

        sem_post(&mutex); // ~
    }

    return NULL;
}

int main() {

    pthread_t t1, t2;
		
		// (&semaphore, shared, initial_value)
    sem_init(&mutex, 0, 1); /* Initilizes semaphore with initial value 1, making it 
															 a binary semaphore */

    pthread_create(&t1, NULL, producer, NULL);
    pthread_create(&t2, NULL, consumer, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final count = %d\n", count);

    sem_destroy(&mutex); // Deleted semaphore

    return 0;
}
+