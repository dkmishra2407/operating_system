#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024  // Size of shared memory segment

int main() {
    int shmid;
    key_t key = ftok("shmfile", 65); // Generate the same key as server
    char *str;

    // Get shared memory segment
    shmid = shmget(key, SHM_SIZE, 0666);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    // Attach to the shared memory segment
    str = (char*) shmat(shmid, NULL, 0);
    if (str == (char*)(-1)) {
        perror("shmat failed");
        exit(1);
    }

    // Read the message from shared memory
    printf("Client: Read from shared memory: %s\n", str);

    // Detach from the shared memory segment
    shmdt(str);

    // Optionally, you can remove the shared memory segment
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
