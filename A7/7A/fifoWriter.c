/////////////////////////////   SIMPLE CODE FOR REFERENCE  ///////////////////////////

// #include <fcntl.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <sys/stat.h>

// #define PIPE_NAME "./fifoChannel"
// #define MESSAGE "Hello, World!\n"

// int main() {
//     // Create FIFO
//     mkfifo(PIPE_NAME, 0666);
//     int fd = open(PIPE_NAME, O_WRONLY);
//     if (fd < 0) return -1;

//     // Write message to FIFO
//     write(fd, MESSAGE, sizeof(MESSAGE) - 1); // -1 to exclude null terminator

//     close(fd);
//     unlink(PIPE_NAME);
//     printf("Message sent to the pipe: %s", MESSAGE);

//     return 0;
// }

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

// sys/types.h, sys/stat.h: Definitions for data types and structures used in file handling.
// fcntl.h: File control options.
// unistd.h: Standard symbolic constants and types (e.g., write, close).
// time.h: For time-related functions (e.g., usleep).
// stdlib.h: For general utility functions (e.g., rand).
// stdio.h: For input/output functions (e.g., printf).

#define MaxLoops         12000   /* outer loop */
#define ChunkSize           16   /* how many written at a time */
#define IntsPerChunk         4   /* four 4-byte ints per chunk */
#define MaxZs              250   /* max microseconds to sleep */

int main() {
  const char* pipeName = "./fifoChannel";   // The pipeName variable holds the name of the FIFO file.
  mkfifo(pipeName, 0666);                      
  // creates a named pipe (FIFO) with permissions set to allow read/write for everyone (user, group, and others).
  int fd = open(pipeName, O_CREAT | O_WRONLY); /* open as write-only */
  if (fd < 0) return -1;                       /* can't go on */

  int i;
  for (i = 0; i < MaxLoops; i++) {          /* write MaxWrites times */
    int j;
    for (j = 0; j < ChunkSize; j++) {       /* each time, write ChunkSize bytes */
      int k;
      int chunk[IntsPerChunk];
      for (k = 0; k < IntsPerChunk; k++)
        chunk[k] = rand();
      write(fd, chunk, sizeof(chunk));
    }
    usleep((rand() % MaxZs) + 1);           /* pause a bit for realism */
  }

  close(fd);           /* close pipe: generates an end-of-stream marker */
  unlink(pipeName);    /* unlink from the implementing file */
  printf("%i ints sent to the pipe.\n", MaxLoops * ChunkSize * IntsPerChunk);

  return 0;
}

