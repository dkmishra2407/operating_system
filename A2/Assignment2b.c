#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void merge(int arr[], int l, int mid, int h) //Function to merge divided array
{
	int temp[h-l+1];
	int i = l;
	int j = mid+1;
	int k = 0;
	
	while(i<=mid && j<=h)
	{
		if(arr[i]<=arr[j])
		{
			temp[k] = arr[i];
			i++;
		}
		else
		{
			temp[k] = arr[j];
			j++;
		}
		k++;
	}
	
	while(i<=mid)
	{
		temp[k] = arr[i];
		i++;
		k++;
	}
	
	while(j<=h)
	{
		temp[k] = arr[j];
		j++;
		k++;
	}
	
	for(int x=l;x<=h;x++)
	{
		arr[x] = temp[x-l];
	}
}
	
void mergeSort(int arr[], int l, int h) //Merge sort function
{
	if(l>=h)
		return;
	
	int mid = (l+h)/2;
	mergeSort(arr, l, mid);
	mergeSort(arr, mid+1, h);
	merge(arr, l, mid, h);
}

int main()
{
	int arr[5], x;
	
	printf("\n");
	printf("Enter Five Integers To Be Sorted \n");
	for(int i=0;i<5;i++) //Take five integers as input
	{
		printf("Enter Integer %d : ",i+1);
		scanf("%d", &x);
		arr[i] = x;
	}
	
	pid_t pid;
	pid = fork(); //Call fork() function and store returned value in a variable
	
	switch(pid)
	{
		case -1: //If pid==-1, then error occured while forking the process
			printf("Error In Forking The Process! \n"); //Error occured while forking the process
			break;
			
		case 0: //If pid==0, then we are in child process
			printf("\n");
			printf("Inside Child Process \n"); //We are in the child process
			mergeSort(arr, 0, 4); //Sort the given array
			printf("Array Sorted By Child Process \n");
			for(int i=0;i<5;i++) //Display sorted array
			{
				printf("%d ",arr[i]);
			}
			printf("\n");
			char** sarr = (char**)malloc(7*sizeof(char*)); //Declaring array of strings
			sarr[0] = "./reverse";
			sarr[6] = NULL;
			int j=0;
			for(int i=1;i<6;i++)
			{
				sarr[i] = (char*)malloc(12*sizeof(char)); //Allocating memory for a string
				sprintf(sarr[i], "%d", arr[j++]); //Converting integer to string
			}
			execv("./reverse", sarr); //Calling exec function to replace current process by reverse program
			break;
			
					
		default: //Else if pid>0, then we are in parent process
			printf("\n");
			printf("Inside Parent Process \n"); //We are inside parent process
			printf("Waiting For Child Process To Terminate..... \n");
			wait(NULL);
			printf("Execution Of Child Process Has Been Completed \n");
			printf("Ending Parent Process Now \n\n");
			break;
	}
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
