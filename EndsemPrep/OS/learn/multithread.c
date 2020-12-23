 #include <stdio.h>
 #include <stdint.h>
 #include <pthread.h>

uint32_t counter = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


void * count_to_big(void *arg){
    for(uint32_t i = 0; i < 50000000; i++){
        pthread_mutex_lock(&lock); //without lock answer wont be right due to race around condition
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t th1;
    pthread_create(&th1, NULL, count_to_big,NULL);
    count_to_big(NULL);
    pthread_join(th1,NULL);
    printf("DOne counter=%u\n",counter);
    return 0;
}
