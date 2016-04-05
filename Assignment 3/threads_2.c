/*
  Program: threads.c
  A simple threaded program example where each one of three threads carefully writes to
  a defined secion of the console. This example shows corruption on the screen, which
  could be fixed using a semaphore based solution.

  Can be fixed by doing the following:
  Escape characters are used to clear the screen and to set cursor positions.

  Notes:
    compiled with gcc -pthreads -o threads -threads.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Function declarations */
void *functionA();
void *functionB();
void *functionC();

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

main(){
  pthread_t thread1, thread2, thread3; /* Declare three thread IDs */
  int rc1, rc2, rc3;

  /* Split up the console into three sections */
  printf("\033[2J");		/* Clear the screen */
  
  printf("\033[%d;%dH", 0 ,0);	/* Set cursor position (row 0, column 0) */  
  printf("THREAD ONE\n");
  printf("===========================================================\n");

  printf("\033[%d;%dH", 8, 0);
  printf("THREAD TWO\n");
  printf("===========================================================\n");

  printf("\033[%d;%dH", 16, 0);
  printf("THREAD THREE\n");
  printf("===========================================================\n");

  /* Create first thread .. thread 1 */
  if( rc1=pthread_create(&thread1, NULL, &functionA, NULL)){
    printf("Error in creating thread %d\n", rc1 );
  }

  /* Create second thread .. thread 2 */
  if( rc2=pthread_create(&thread2, NULL, &functionB, NULL)){
    printf("Error in creating thread %d\n", rc2 );
  }

  /* Crate third thread .. thread 3 */
  if( rc3=pthread_create(&thread3, NULL, &functionC, NULL)){
    printf("Error in creating thread %d\n", rc3 );
  }

  /* Wait for threads to exit */
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  pthread_join(thread3, NULL);

  /* Ready mutex for deletion */
  pthread_mutex_destroy(&mutex1);

  exit(0);
}

void *functionA(){
  while(1){
    pthread_mutex_lock(&mutex1);
    printf("\033[%d;%dH", 4, 0); /* Set cursor position (row 3, column 0 */
    printf("I am a function 1111111111111111111111111111111111111\n");
    pthread_mutex_unlock(&mutex1);
  }	
  pthread_exit(NULL);		/* thread exits */
}

void *functionB(){
  while(1){
    pthread_mutex_lock(&mutex1);
    printf("\033[%d;%dH", 11, 0); /* Set cursor position (row 3, column 0 */
    printf("I am a function 2222222222222222222222222222222222222\n");
    pthread_mutex_unlock(&mutex1);
  }
  pthread_exit(NULL);		/* thread exits */
}

void *functionC(){
  while(1){
    pthread_mutex_lock(&mutex1);
    printf("\033[%d;%dH", 19, 0); /* Set cursor position (row 3, column 0 */
    printf("I am a function 3333333333333333333333333333333333333\n");
    pthread_mutex_unlock(&mutex1);
  }
  pthread_exit(NULL);		/* thread exits */
}

