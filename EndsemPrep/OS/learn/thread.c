#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>

void *myturn(void *arg){
    int *ptr =  (int *)arg;
    for(int i = 0 ; i <6; i++){
        sleep(1);
        printf("MY %d\n",*ptr);
          (  *ptr )++;
    }
    return NULL;
}


void*  yourturn(void * arg){
    int *ptr = (int *) malloc(sizeof(int));
    *ptr = 5;
    for(int i = 0 ; i <5; i++){
        sleep(1);
        printf("YT\n");
        (*ptr)++;
    }
    return ptr;
}

int main(int argc, char const *argv[])
{
    pthread_t newthread, newthread2;
    int v = 4;
    pthread_create(&newthread, NULL, myturn, &v);
    pthread_create(&newthread2, NULL, myturn, NULL);

    int *result;
    pthread_join(newthread2 ,(void *) &result);
    pthread_join(newthread , NULL);

    printf("From thread %d\n",*result);
    
    return 0;
}
