#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define SZ 10
#define loop 20
int buf[SZ],f,r;

sem_t full,mutex,empty;

void *produce(void *arg){
	int i;
	for (int i = 0; i < loop; ++i)
	{
		sem_wait(&empty);
		sem_wait(&mutex);
		printf("produced item is %d \n", i);
		buf[(++r)%SZ]=i;
		sleep(1);
		sem_post(&mutex);
		sem_post(&full);


		int value;
    	sem_getvalue(&full, &value);
    	printf("full %d\n",value);
    	// int value2;
    	// sem_getvalue(&mutex, &value2);
    	// printf("mutex %d\n",value2);
		// printf("full %ld\n", full);
	}
	
}

void *consume(void *arg){
	int i,item;
	
	for (int i = 0; i < loop; ++i)
	{
		sem_wait(&full);
		sem_wait(&mutex);

		int value;
    	sem_getvalue(&full, &value);
    	printf("full %d\n",value);
		// printf("full %ld\n", full);
		
		
		item=buf[(++f)%SZ];
		printf("consumed item is %d \n", item);
		sleep(1);
		sem_post(&mutex);
		sem_post(&empty);
		
	}
}

int main(){
	pthread_t tid1,tid2;
	sem_init(&mutex,0,1);
	sem_init(&full,0,1);
	sem_init(&empty,0,SZ);
	pthread_create(&tid1,NULL,produce,NULL);
	pthread_create(&tid2,NULL,consume,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid1,NULL);
}