// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <semaphore.h>

// #define BUFFER_SIZE 5
// #define NUM_PRODUCERS 2
// #define NUM_CONSUMERS 2

// int buffer[BUFFER_SIZE];
// int in = 0, out = 0;

// sem_t empty, full;
// pthread_mutex_t mutex;

// void *producer(void *arg) {
//     int id = *((int *)arg);
//     for (int i = 0; i < 1000; i++) {
//         sem_wait(&empty);
//         pthread_mutex_lock(&mutex);
//         buffer[in] = i;
//         printf("Producer %d produced %d\n", id, i);
//         in = (in + 1) % BUFFER_SIZE;
//         pthread_mutex_unlock(&mutex);
//         sem_post(&full);
//     }
//     return NULL;
// }

// void *consumer(void *arg) {
//     int id = *((int *)arg);
//     for (int i = 0; i < 1000; i++) {
//         sem_wait(&full);
//         pthread_mutex_lock(&mutex);
//         int item = buffer[out];
//         printf("Consumer %d consumed %d\n", id, item);
//         out = (out + 1) % BUFFER_SIZE;
//         pthread_mutex_unlock(&mutex);
//         sem_post(&empty);
//     }
//     return NULL;
// }

// int main() {
//     pthread_t producers[NUM_PRODUCERS], consumers[NUM_CONSUMERS];
//     int producer_ids[NUM_PRODUCERS], consumer_ids[NUM_CONSUMERS];

//     sem_init(&empty, 0, BUFFER_SIZE);
//     sem_init(&full, 0, 0);
//     pthread_mutex_init(&mutex, NULL);

//     for (int i = 0; i < NUM_PRODUCERS; i++) {
//         producer_ids[i] = i + 1;
//         pthread_create(&producers[i], NULL, producer, &producer_ids[i]);
//     }

//     for (int i = 0; i < NUM_CONSUMERS; i++) {
//         consumer_ids[i] = i + 1;
//         pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]);
//     }

//     for (int i = 0; i < NUM_PRODUCERS; i++) {
//         pthread_join(producers[i], NULL);
//     }

//     for (int i = 0; i < NUM_CONSUMERS; i++) {
//         pthread_join(consumers[i], NULL);
//     }

//     sem_destroy(&empty);
//     sem_destroy(&full);
//     pthread_mutex_destroy(&mutex);

//     return 0;
// }




#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define BUFFER_SIZE 5 // Buffer size

int buffer[BUFFER_SIZE]; // Shared buffer
int in = 0; // Producer index
int out = 0; // Consumer index

// Semaphores and mutex
sem_t empty; // Counting semaphore for empty slots
sem_t full;  // Counting semaphore for full slots
pthread_mutex_t mutex; // Mutex for buffer access

// Producer function
void* producer(void* arg) {
    int item;
    while (1) {
        item = rand() % 100; // Produce an item

        // Wait for an empty slot
        sem_wait(&empty);
        // Lock mutex to access buffer
        pthread_mutex_lock(&mutex);

        // Produce item in buffer
        buffer[in] = item;
        printf("Producer produced: %d at position %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;

        // Unlock mutex
        pthread_mutex_unlock(&mutex);
        // Signal full slot
        sem_post(&full);

        // Random sleep time between 1 and 3 seconds
        sleep(rand() % 3 + 1);
    }
}

// Consumer function
void* consumer(void* arg) {
    int item;
    while (1) {
        // Wait for full slot
        sem_wait(&full);
        // Lock mutex to access buffer
        pthread_mutex_lock(&mutex);

        // Consume item from buffer
        item = buffer[out];
        printf("Consumer consumed: %d from position %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        // Unlock mutex
        pthread_mutex_unlock(&mutex);
        // Signal empty slot
        sem_post(&empty);

        // Random sleep time between 1 and 3 seconds
        sleep(rand() % 3 + 1);
    }
}

int main() {
    pthread_t prod, cons;

    // Seed the random number generator
    srand(time(NULL));

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Join threads
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}