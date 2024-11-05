#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024  // Size of shared memory segment

int main() {
    int shmid;
    key_t key = ftok("shmfile", 65); // Generate a unique key
    char *str;

    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    str = (char*) shmat(shmid, NULL, 0);
    if (str == (char*)(-1)) {
        perror("shmat failed");
        exit(1);
    }

    // Write a message to the shared memory
    sprintf(str, "Hello from Server!");
    printf("Server: Message written to shared memory: %s\n", str);

    // Detach from the shared memory segment
    shmdt(str);
    return 0;
}
