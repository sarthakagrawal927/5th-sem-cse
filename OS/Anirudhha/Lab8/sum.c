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
	
	int sum = 0;
	for(int i=0;i<a;++i){
		sum += arr[i];
	}
	return (void *)sum;
}

int main()
{
	pthread_t tid;
	int n,result;
	struct s_strct * s;
	s = malloc(sizeof(struct s_strct));
	printf("enter tot num \n");
	scanf("%d",&n);
	s->num = n;
	for (int i = 0; i < n; ++i)
	{
		scanf("%d",&(s->arr[i]));
	}
	pthread_create(&tid,0,&thread_code,(void *)s);
	pthread_join(tid,(void**)&result ); // wait for hread to complete
	printf("in main \n");
	printf("sum is = %d\n",result );
	
	
}