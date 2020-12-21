#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/syscall.h>

#ifndef SYS_gettid
#error "SYS_gettid unavailable on this system"
#endif

#define gettid() ((pid_t)syscall(SYS_gettid))

sem_t mutex1,mutex2;

void *get1then2(){

	pid_t pid1 = getpid();
	printf("tid is %d pid is %d \n", gettid(),pid1 );
	int value1,value2; sem_getvalue(&mutex1, &value1); sem_getvalue(&mutex2, &value2); printf("mutex1 %d\t",value1);   printf("mutex2 %d\n",value2);
	sem_wait(&mutex1);
	sleep(1); // acquire resource1
	printf("waiting for resource2 \n");
	sem_wait(&mutex2); 

	// do the job
	printf("doing work in get1then2 \n");

	sem_post(&mutex2);
	sem_post(&mutex1);
}

void *get2then1(){

	pid_t pid2 = getpid();
	printf("tid is %d pid is %d \n", gettid(),pid2 );
	int value1,value2; sem_getvalue(&mutex1, &value1); sem_getvalue(&mutex2, &value2); printf("mutex1 %d\t",value1);   printf("mutex2 %d\n",value2);
	sem_wait(&mutex2); 
	sleep(1); // acquire resource2
	printf("waiting for resource1 \n");
	sem_wait(&mutex1); 

	// do the job
	printf("doing work in get2then1 \n");
	
	sem_post(&mutex1);
	sem_post(&mutex2);
}

int main(){
	pthread_t tid1,tid2;
	sem_init(&mutex1,0,1);
	sem_init(&mutex2,0,1);
	
	pthread_create(&tid1,NULL,get1then2,NULL);
	pthread_create(&tid2,NULL,get2then1,NULL);


	pthread_join(tid1,NULL);
	pthread_join(tid1,NULL);

	printf("this should not be printed if deadlock \n");

	return 0;
}