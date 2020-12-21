#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

struct s_strct{
	int num;
	int arr[100];
};


void* thread_code(void *s){
	struct s_strct *s2 = (struct s_strct*)s;
	int a = (int)s2->num;
	int* arr = (int *)s2->arr;
	printf("in thread_code \n");
	
	arr[0]=0;arr[1]=1;
	for(int i=2;i<a;++i){
		arr[i] = arr[i-1]+arr[i-2];
	}
}

int main()
{
	pthread_t tid;
	int n;
	struct s_strct * s;
	s = malloc(sizeof(struct s_strct));
	printf("enter num\n");
	scanf("%d",&n);
	s->num = n;
	pthread_create(&tid,0,&thread_code,(void *)s);
	pthread_join(tid,0); // wait for hread to complete
	printf("in main \n");
	printf("fibbonaci series is\n");
	for (int i = 0; i < n; ++i)
	{
		printf("%d ",s->arr[i] );
	}
	
}