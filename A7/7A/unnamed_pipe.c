#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int pipeFDs[2];
    // pipeFDs[2] creates an array to hold two file descriptors: 
    // pipeFDs[0] for reading from the pipe 
    // pipeFDs[1] for writing to the pipe.
    char buf;   // BUFFER 
    char* msg = "Message\n";   // MESSAGE TO PRINT
    if(pipe(pipeFDs) < 0) {perror("pipeFDs"); exit(-1);}  // CHECK THE PIPES ARE CREATED CORRECTLY OR NOT 

    pid_t cpid = fork();   // CREATE THE PROCESS
    if(cpid < 0) {perror("Fork"); exit(-1);}
    if(cpid == 0)
    {
        // child
        close(pipeFDs[1]);    // CLOSE THE WRITING FILE
        while(read(pipeFDs[0], &buf, 1) > 0)  // FOR READING THE FILE IT WILL WRITE IN THE BUFFER
        {
            write(STDOUT_FILENO, &buf, sizeof(buf));
        }
        close(pipeFDs[0]);
        _exit(0);
    }
    else
    {
        // parent
        close(pipeFDs[0]);   // CLOSE THE READING FILE 
        write(pipeFDs[1], msg ,strlen(msg));
        close(pipeFDs[1]);
        wait(NULL);   // WAIT FOR THE TERMINATION OF THE CHILD PROCESS
        exit(0);
    }
    return 0;
}