#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

struct s_strct{
	int l;
	int u;
	int arr[100];
};


void* thread_code(void *s){
	struct s_strct *s2 = (struct s_strct*)s;
	int l = (int)s2->l;
	int u = (int)s2->u;
	int* arr = (int *)s2->arr;
	printf("in thread_code \n");
	
	int i,j,c=0,k=1;
	for(i=l;i<=u;i++)
	{
	    c=0;
		for(j=1;j<=i;j++)
	    {
	        if(i%j==0)
	        {
	            c++;
	        }
	    }
	    if(c==2)
	    {
	        arr[k++]=i;
	    }
	}
	arr[0]=k;
	
}

int main()
{
	pthread_t tid;
	int n,m;
	struct s_strct * s;
	s = malloc(sizeof(struct s_strct));
	printf("enter lower bound \n");
	scanf("%d",&n);
	printf("enter upper bound \n");
	scanf("%d",&m);

	s->l = n;
	s->u = m;
	
	pthread_create(&tid,0,&thread_code,(void *)s);
	pthread_join(tid,0); // wait for hread to complete
	printf("in main \n");
	printf("prime numbers are -\n");
	for (int i = 1; i < s->arr[0]; ++i)
	{
		printf("%d ",s->arr[i] );
	}
	
}