#include<stdio.h>


#define NO_OF_READER 1
#define NO_OF_WRITER 1

sem_t wsem;
int x = 0;
int readc = 0;
pthread_mutex_t mutex;
void* reader(void *arg){
    int id = *((int*)arg); // get the argument passed to this

    pthread_mutex_lock(&wsem);
    readc++;
    if(readc == 0){
        sem_wait(&wsem);
    }
    pthread_mutex_unlock(&wsem);
    // read section 
    printf("Reader %d reads %d",id,x);
    pthread_mutex_lock(&wsem);
    readc--;
    if(readc == 1){
        sem_post(&wsem);
    }
    pthread_mutex_unlock(&wsem);
}

void* writer(void *arg){
    int id = *((int*)arg); // get the argument passed to this
    sem_wait(&wsem);
    x++;
    sem_post(&wsem);
    
}