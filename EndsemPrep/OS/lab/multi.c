#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

int arr[100];

void* func(void *arg){
    printf("In func");
    int *n ;
    n= malloc(sizeof(int));

    n = (int *)arg;
    int * sum;
    sum = malloc(sizeof(int));
    for(int  i = 0; i < *n; i++) *sum+=arr[i];
    return (void *) sum;
}

void* intVal(void *arg){
    printf("In value enter");
    int *d; 
    d = malloc(sizeof(int));
    d = (int *)arg;

    for(int i = 0; i < *d; i++){
        scanf("%d",&arr[i]);
    }
}

int main(int argc, char const *argv[])
{
    pthread_t th1, th2;
    int *s;
    s = malloc(sizeof(int));
    *s  = 10;
    printf("In main");

    pthread_create(&th2,0,&intVal, (void *)s);
    pthread_join(th2,NULL);

    pthread_create(&th1, 0, &func, (void *)s);
    int *result;
    pthread_join(th1, (void *) &result );
    printf("%d",*result);
    return 0;
}
