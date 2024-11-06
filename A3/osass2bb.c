#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    int arr[5];
    for(int i=0;i<5;i++){
        scanf("%d",&arr[i]);
    }
    pid_t pid = fork();

    if(pid < 0){
        printf("fork failed\n");
        return 1;
    }
    if(pid == 0){
        printf("Child process start");
        mergesort(arr,0,4);
        printf("Sorted...");
        for(int i=0;i<5;i++){
        printf("%d",arr[i]);
        }
        char** sarr = (char**)malloc(7*sizeof(char*));
        sarr[0] = "/reverse";
        sarr[6] = NULL;
        int j =0;
        for(int i=1;i<6;i++){
               sarr[i] = (char*)malloc(12*sizeof(char)); //Allocating memory for a string
				sprintf(sarr[i], "%d", arr[j++]); //Converting integer to string
        }
        execv("/reverse",sarr);
    }
    else{
        //parent
        printf("Inside parent");
        printf("Waiting For the child process");
        wait(NULL);
        printf("Child Died");
        printf("parent die");
    }
    return 0;
}