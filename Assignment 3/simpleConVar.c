/* 
   Program: simpleConVar.c
   Shows the use of a POSIX Condition Variable as an introductory
   example. Only Thread 1 can display the condition where the counter's
   value is divisible by 3.

   Note: Counter increments had to be carefully placed. A counter should
         only be implemented if the value was displayed. If only sending
	 a signal there is no need to increment it
	 Checks were added to initial IF statement if the number was
	 divisible by 3

   Author: Ian Lodovica (13131567)
   Date: 5th of April 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Function declarations */
void *functionA();
void *functionB();
void *functionC();

/* Initialise a mutex called mutex1 */
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

/* Initialise a condition variable called con_var*/
pthread_cond_t con_var1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t con_var2 = PTHREAD_COND_INITIALIZER;

/* Global definitions and a variable */
#define TOP_LIMIT 17
int counter = 1;

/* MAIN */
int main(){
  pthread_t thread1, thread2, thread3; /* declare 3 threads */

  /* Create three threads - no error checking fro simplcity */
  pthread_create(&thread1, NULL, &functionA, NULL);
  pthread_create(&thread2, NULL, &functionB, NULL);
  pthread_create(&thread3, NULL, &functionC, NULL);

  /* Remeber to use the thread joins */
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  pthread_join(thread3, NULL);
  
  /* Destroy the mutex and the condition variable */
  pthread_cond_destroy(&con_var1);
  pthread_mutex_destroy(&mutex1);

  printf("\nNow finished\n");
  
  /* main exits */
  exit(0);
}


/* Thread 1 */
void *functionA(){
  while(counter <= 15){
    pthread_mutex_lock(&mutex1); /* Lock mutex1 */
    
    /* Check the value of counter and if it is not divisible by 3
       wait on con_var1 for signal to release mutex1
       blocks until signalled, mutex1 is unlocked if signalled
     */
    if(!(counter%3) && counter != 3){
      printf("I am Thread 1 the current value is: %d\n", counter);
      counter++;
    }else if(counter < 6){
      pthread_cond_signal(&con_var2);
    }else{
      pthread_cond_wait(&con_var1, &mutex1);
      printf("I am Thread 1 the current value is: %d\n", counter);
      counter++;
    }


    pthread_mutex_unlock(&mutex1);
    sleep(1);			/* Allow some time so threads can alternate */
  }
  pthread_exit(NULL);
}

/* Thread 2 */
void *functionB(){
  while(counter<TOP_LIMIT){
    pthread_mutex_lock(&mutex1);
    
    /* If counter is divisible by 3, then 'if' condition is met so send signal */
    if(!(counter%3) && counter != 3){
      pthread_cond_signal(&con_var1);
    }else if(counter < 6){
      pthread_cond_signal(&con_var2); 	
    }else{
      printf("I am Thread 2 the current value is: %d\n", counter);
      counter++;		
    }


    pthread_mutex_unlock(&mutex1);
    sleep(1);			/* allow some time so threads can alternate */
  }
  pthread_exit(NULL);
}

/* Thread 3 */
void *functionC(){
  while(counter<TOP_LIMIT){
    pthread_mutex_lock(&mutex1);
    
    if(!(counter%3) && counter != 3){
      pthread_cond_signal(&con_var1);
    }else if(counter < 6){
      pthread_cond_wait(&con_var2, &mutex1);
      printf("I am Thread 3 the current value is: %d\n", counter);
      counter++;	
    }else{
      printf("I am Thread 3 the current value is: %d\n", counter);
      counter++;	
    }
	
    pthread_mutex_unlock(&mutex1);
    sleep(1);			/* allow some time so threads can alternate */
  }
  pthread_exit(NULL);
}
