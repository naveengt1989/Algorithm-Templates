#include <iostream>
#include<stdio.h>
#include <pthread.h>
using namespace std;
// Initiliazer variables ///
const int MAX_NUM=14;
const int THREADS=3;
//////////////////////////
int gCount=0;
pthread_mutex_t mutex;
pthread_cond_t cond;
void *print(void* ptr)
{
	int id = *((int*)(ptr));
	while(1)
	{
		if(gCount+abs(id - gCount%THREADS) > MAX_NUM)
			break;
		pthread_mutex_lock (&mutex);
		if(gCount%THREADS == id)
		{
			cout<<"thread "<<id<<" - "<<gCount<<endl;
			gCount++;
		}
		pthread_mutex_unlock (&mutex);
	}
	pthread_exit(NULL); 
}


int main()
{
	pthread_t T[THREADS];
	int i[THREADS];
	for(int j=0; j<THREADS; j++) 
	{
		i[j]=j;
		pthread_create(&T[j],NULL,print,&i[j]);
	}
	for(int j=0; j<THREADS; j++) 
		pthread_join(T[j],NULL);
	pthread_exit(NULL);
	return 0;
}
