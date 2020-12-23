#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>
#include<sys/ipc.h>
#include<semaphore.h>
#define N 5

time_t end_time;/*end time*/
sem_t mutex,customers,barbers;/*Three semaphors*/
int count=0;/*The number of customers waiting for haircuts*/

void barber(void *arg);
void customer(void *arg);

int main(int argc,char *argv[])
{
	pthread_t id1,id2;
	int status=0;
	end_time=time(NULL)+20;/*Barber Shop Hours is 20s*/
	
	
	sem_init(&mutex,0,1);sem_init(&customers,0,0);
	sem_init(&barbers,0,1);
	
	
	status=pthread_create(&id1,NULL,(void *)barber,NULL);
	if(status!=0)
	perror("barber error!\n");
	
	/*Customer_thread initialization*/
	status=pthread_create(&id2,NULL,(void *)customer,NULL);
	if(status!=0)
	perror("customers error!\n");
	
	/*Customer_thread first blocked*/
	pthread_join(id2,NULL);
	pthread_join(id1,NULL);
	exit(0);
}

void barber(void *arg)
{
	while(time(NULL)<end_time || count>0)
	{
		sem_wait(&customers);
		sem_wait(&mutex);
		count--;
		printf("Barber:cut hair,count is:%d.\n",count);
		sem_post(&mutex);
		sem_post(&barbers);
		sleep(3);
	}
}

void customer(void *arg)
{
	while(time(NULL)<end_time)
	{
		sem_wait(&mutex);
		if(count<N)
		{
			count++;
			printf("Customer:add count,count is:%d\n",count);
			sem_post(&mutex);
			sem_post(&customers);
			sem_wait(&barbers);
		}
		else
			
			/*If the number is full of customers,just put the mutex lock let go*/
			sem_post(&mutex);
		sleep(1);
	}
}
