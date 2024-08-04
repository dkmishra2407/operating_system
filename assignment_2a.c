#include <stdio.h>
 #include <stdlib.h>
 #include <sys/types.h>
 #include <unistd.h>
 int main(int argc, char *argv[]) {
 printf("exec executed\n");
 printf("The PID of this process is: %d\n", getpid());
 if (argc > 1) {
 printf("Arguments received in reverse order: ");
 for (int i = argc- 1; i > 0;--i) {
 printf("%s ", argv[i]);
 }
 printf("\n");
 } else {
 printf("No arguments received.\n");
 }
 return 0;
 }