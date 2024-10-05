#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	printf("\n");
	printf("Inside Reverse Program \n");
	printf("Printing Sorted Array In Reverse Order \n");
	for(int i=5;i>=1;i--)
	{
		int x = atoi(argv[i]);
		printf("%d ",x);
	}
	printf("\n\n");
}
