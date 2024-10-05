#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int pipeFDs[2];
    char buf;
    char* msg = "Message\n";
    if(pipe(pipeFDs) < 0) {perror("pipeFDs"); exit(-1);}
    pid_t cpid = fork();
    if(cpid < 0) {perror("Fork"); exit(-1);}
    if(cpid == 0)
    {
        // child
        close(pipeFDs[1]);
        while(read(pipeFDs[0], &buf, 1) > 0)
        {
            write(STDOUT_FILENO, &buf, sizeof(buf));
        }
        close(pipeFDs[0]);
        _exit(0);
    }
    else
    {
        // parent
        close(pipeFDs[0]);
        write(pipeFDs[1], msg ,strlen(msg));
        close(pipeFDs[1]);
        wait(NULL);
        exit(0);
    }
    return 0;
}