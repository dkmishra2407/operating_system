#include<stdio.h>

int main(int argv,char argc[]){
    for(int i=5;i>=0;i--){
        int item = atoi(argc[i]);
        printf("%d",item);
    }
    return 0;
}