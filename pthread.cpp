#include<stdio.h>
#include<pthread.h>
#include<assert.h>
#include<stdlib.h>
#include<unistd.h>

pthread_mutex_t *lock;
pthread_cond_t *cond;
int done = 1;

void* printOdd(void *max){
	int range = *(int *) max;
	for(int i=1; i<range; i+=2){
		while(done != 0) {
			pthread_cond_wait(cond, lock);
		}
		//pthread_mutex_lock(lock);
		printf("printOdd Lock Acquired\n");

		printf("%d \n",i);
		done = 1;
		pthread_cond_signal(cond);
		printf("printOdd Lock Yielded\n");
		//pthread_mutex_unlock(lock);
	}
	return NULL;
}

void* printEven(void *max){
	int range = *(int *) max;
	for(int i=0; i<range; i+=2){
		while(done != 1){
			pthread_cond_wait(cond, lock);
		}
		//pthread_mutex_lock(lock);
		printf("printEven Lock Acquired\n");

		printf("%d \n",i);
		done = 0;
		pthread_cond_signal(cond);
		printf("printEven Lock Yielded\n");
		//pthread_mutex_unlock(lock);
	}
	while(done!=1);
	return NULL;
}

int main(int argc, char *argv[]){
	if(argc != 2){
		//printf(“Provide the max range of nos to print\n”);
		return -1;
	}
	pthread_t t1,t2;
	lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	cond = (pthread_cond_t *)malloc(sizeof(*cond));
	int rc = pthread_mutex_init(lock,NULL);
	//assert(rc == 0);
	rc = pthread_cond_init(cond,NULL);
	//assert(rc == 0);
	int max = atoi(argv[1]);
	pthread_create(&t2,NULL,printEven,(void *)&max);
	pthread_create(&t1,NULL,printOdd,(void *)&max);
	pthread_join(t2, NULL);
	pthread_join(t1, NULL);
	return 0;

}
