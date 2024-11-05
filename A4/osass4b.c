    #include<stdio.h>
    #include<stdlib.h>
    #include<seamphore.h>
    #include<pthread.h>

    #define no_of_reader 3 
    #define no_of_writer 3

    pthread_mutex_t mutex;
    sem_t wsem;

    int x = 0;
    int read_count = 0;
    void *reader(void *arg){
        int id = *((int *)arg);
        pthread_mutex_lock(&mutex);
        read_count++;
        if(read_count == 1){
            sem_wait(&wsem);  // First reader blocks writers
        }
        pthread_mutex_unlock(&mutex);
        pthread_mutex_lock(&mutex);
        read_count--;
        if(read_count == 0){
            sem_post(&wsem);  // Last reader allows writers
        }
        pthread_mutex_unlock(&mutex);
        return NULL;
    }

    void *writer(void *arg){
        int id = *((int *)arg);

        sem_wait(&wsem);
        x++;
        sem_post(&wsem);

        return NULL;
        
    }
    int main(){
        pthread_t readers[NO_OF_READERS], writers[NO_OF_WRITERS];
        int reader_id[NO_OF_READERS], writer_id[NO_OF_WRITERS];

        // Initialize semaphore and mutex
        sem_init(&wsem, 0, 1);  // Binary semaphore for writer control
        pthread_mutex_init(&mutex, NULL);

        // Create reader threads
        for (int i = 0; i < NO_OF_READERS; i++) {
            reader_id[i] = i + 1;
            pthread_create(&readers[i], NULL, reader, &reader_id[i]);
        }

        // Create writer threads
        for (int i = 0; i < NO_OF_WRITERS; i++) {
            writer_id[i] = i + 1;
            pthread_create(&writers[i], NULL, writer, &writer_id[i]);
        }

        // Wait for all threads to complete
        for (int i = 0; i < NO_OF_READERS; i++) {
            pthread_join(readers[i], NULL);
        }

        for (int i = 0; i < NO_OF_WRITERS; i++) {
            pthread_join(writers[i], NULL);
        }

        // Destroy semaphore and mutex
        sem_destroy(&wsem);
        pthread_mutex_destroy(&mutex);

        return  0;
    }