#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

struct s_strct{
	int num;
	int sumeven;
	int sumodd;
	int arr[100];
};


void* thread_code1(void *s){
	struct s_strct *s2 = (struct s_strct*)s;
	int a = (int)s2->num;
	int* arr = (int *)s2->arr;
	printf("in thread_code1 \n");
	
	s2->sumeven = 0;
	for(int i=0;i<a;++i){
		if(arr[i]%2==0){
			s2->sumeven += arr[i];
		}
	}
}

void* thread_code2(void *s){
	struct s_strct *s2 = (struct s_strct*)s;
	int a = (int)s2->num;
	int* arr = (int *)s2->arr;
	printf("in thread_code2 \n");
	
	s2->sumodd = 0;
	for(int i=0;i<a;++i){
		if(arr[i]%2==1){
			s2->sumodd += arr[i];
		}
	}
}

int main()
{
	pthread_t tid1,tid2;
	int n;
	struct s_strct * s;
	s = malloc(sizeof(struct s_strct));
	printf("enter tot num \n");
	scanf("%d",&n);
	s->num = n;
	printf("enter nums \n");
	for (int i = 0; i < n; ++i)
	{
		scanf("%d",&(s->arr[i]));
	}

	pthread_create(&tid1,0,&thread_code1,(void *)s);
	pthread_create(&tid2,0,&thread_code2,(void *)s);

	pthread_join(tid1,0); // wait for thread to complete
	pthread_join(tid2,0); 

	printf("in main \n");
	printf("sum odd is = %d\n",s->sumodd );
	printf("sum even is = %d\n",s->sumeven );
	
}