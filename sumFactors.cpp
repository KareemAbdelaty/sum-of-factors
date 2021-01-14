// ======================================================================
// Kareem Abdelaty
// 		30075331
// ======================================================================

#include "sumFactors.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <atomic>
using namespace std;
pthread_mutex_t myMutex;
std::atomic<int64_t> result;
std::atomic<bool> found;
int64_t jump,num,maximum;
bool noinput,done;
pthread_barrier_t myBarrier2,myBarrier;
pthread_mutex_t mutex;
pthread_cond_t cond;

// calculates smallest divisor of n that is less than n
//
// returns 0 if n is prime or n < 2
//
// examples:
//    n =  1         --> result = 0
//    n =  2         --> result = 0
//    n =  9         --> result = 3
//    n = 35         --> result = 5
//    n = 8589934591 --> result = 7
//
// you may modify this function

//structure that holds the start position for each thread
struct limit{
	int64_t s;	
};

//function that looks for the smallest divisor
void thread_task(void * i)
{
  limit l = *((limit*) i); //cast the void pointer to a pointer of type limit
  int64_t current  = l.s; //get the start postion for this thread
  //while your are lower than max keep looping
  while(current<=maximum) {
	//if another thread found a divisor and you are past that divisor return
	if((found ==true)&&(current>result)){
		break;
	}
	//preform the getsmallestdivisor function
    if ((num % current) == 0){
		//lock the critical section to update result
		pthread_mutex_lock(&myMutex);
        if(found!=true){
			result = current;
			found = true;
		}else if((current)<=result){
			result = current;
		}
        pthread_mutex_unlock(&myMutex);
		//unlock and return
		break;
	}
    if ((num % (current+2)) == 0){
		pthread_mutex_lock(&myMutex);
        if(found!=true){
			result = current +2;
			found = true;
		}
		else if((current+2)<=result){
			result = current +2;
		}
        pthread_mutex_unlock(&myMutex);
		break;
	}
	//increment your current 
    current += jump;
  }
}






void * thread_start(void * tid) {
    while(1) {
		//wait for the input to be ready
		pthread_barrier_wait(&myBarrier);
		//if not input is recieved
		if(noinput==true){
			break;
		}
		//preform get smallest divisor
        thread_task(tid);
		pthread_barrier_wait(&myBarrier); //wait for all thread to finish
	}
    pthread_exit(0);
}





// reads in a positive integers in range (2 .. 2^63-1) from standard input
// for each number on input:
//   if the number is prime, it is ignored
//   determines the smallest factor of the composite number
// prints out the sum of all smallest factors
//
// if no composite numbers are found, it returns 0
//
// please note: the current implementation is single-threades, so
// n_threads argument is ignored
//
// you may modify this function
//
int64_t sum_factors(int n_threads)
{
  pthread_t threadPool[n_threads]; // array to keep track of threads
  limit Limits[n_threads]; // array to keep track of start positions for every thread
  noinput =false;
  pthread_mutex_init(&myMutex, 0);
  pthread_barrier_init(&myBarrier, NULL, (n_threads+1));
  //setup start for each thread
	int64_t start = 5;
	jump =6*n_threads;
  for (int i = 0; i < n_threads; i++)
    {
		Limits[i].s = start;
        pthread_create(&threadPool[i], NULL, thread_start, (void *) &Limits[i]);
		start +=6;
    }	
  int64_t sum = 0;
 
  while(1) {
	found = false;
	done =false;
	result =0;
    if( ! (std::cin >> num) ){
		noinput =true;
		pthread_barrier_wait(&myBarrier);//signal to threads that there is no input
		break;
	}
	else if( num <= 3){
		sum +=0;
	}
	else if( num % 2 == 0){ 
		sum += 2;
	}
	else if( num % 3 == 0){ 
		sum += 3;
	}else{	
		maximum = sqrt(num);
		pthread_barrier_wait(&myBarrier);//signal to threads that input is ready
		pthread_barrier_wait(&myBarrier);//wait for output
		sum += result;

	}
	}
	//clean up
   for (int i = 0; i < n_threads; i++)
    {	
        pthread_join(threadPool[i], NULL);
    }
	pthread_mutex_destroy(&myMutex);
	pthread_barrier_destroy(&myBarrier);
  return sum;
}
