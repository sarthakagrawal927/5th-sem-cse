#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

/*
Problem parameters:

One set of data is shared among a number of processes
Once a writer is ready, it performs its write. Only one writer may write at a time
If a process is writing, no other process can read it
If at least one reader is reading, no other process can write
Readers may not write and only read

*/


sem_t mutex,wrt;
pthread_t tid;
pthread_t writerthreads[100],readerthreads[100];
int readcount = 0;

void *reader(void* param)
{
    sem_wait(&mutex);
    readcount++;
    if(readcount==1)
        sem_wait(&wrt);
    sem_post(&mutex);
    printf("%d reader in critical sec\n",readcount);
    sleep(1);
    sem_wait(&mutex);
    readcount--;
    if(readcount==0)
    {
        sem_post(&wrt);
    }
    sem_post(&mutex);
    printf("%d reader left\n",readcount);
    return NULL;
}

void *writer(void* param)
{
    printf("writer is trying to enter\n");
    sem_wait(&wrt);
    printf("writer in critical sec\n");
    sleep(1);
    sem_post(&wrt);
    printf("writer left\n");
    return NULL;
}

int main()
{
    int rds,i;
    printf("Enter the number of readers:");
    scanf("%d",&rds);
    printf("\n");
    int n1[rds];
    sem_init(&mutex,0,1);
    sem_init(&wrt,0,1);
    for(i=0;i<rds;i++)
    {
        pthread_create(&writerthreads[i],NULL,reader,NULL);
        pthread_create(&readerthreads[i],NULL,writer,NULL);
    }
    for(i=0;i<rds;i++)
    {
        pthread_join(writerthreads[i],NULL);
        pthread_join(readerthreads[i],NULL);
    }

}