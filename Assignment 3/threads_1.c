/*
  Program: threads_1.c
  A simple threaded program example where each one of three threads carefully writes to
  a defined secion of the console. This example shows corruption on the screen, which
  could be fixed using a semaphore based solution.

  Notes:
    compiled with gcc -pthreads -o threads_1 -threads_1.c
  
  Author: Ian Lodovica (13131567)
  Date: 5th of April 2016
 */

#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>

/* Function declarations */
void *functionA();
void *functionB();
void *functionC();

sem_t sem1;

main(){
  pthread_t thread1, thread2, thread3; /* Declare three thread IDs */
  int rc1, rc2, rc3;

  sem_init(&sem1, 0, 1);

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

  /* Ready semaphore for deletion */
  sem_destroy(&sem1);

  exit(0);
}

void *functionA(){
  while(1){
    sem_wait(&sem1);
    printf("\033[%d;%dH", 4, 0); /* Set cursor position (row 3, column 0 */
    printf("I am a function 1111111111111111111111111111111111111\n");
    sem_post(&sem1);
  }	
  pthread_exit(NULL);		/* thread exits */
}

void *functionB(){
  while(1){
    sem_wait(&sem1);
    printf("\033[%d;%dH", 11, 0); /* Set cursor position (row 3, column 0 */
    printf("I am a function 2222222222222222222222222222222222222\n");
    sem_post(&sem1);
  }
  pthread_exit(NULL);		/* thread exits */
}

void *functionC(){
  while(1){
    sem_wait(&sem1);
    printf("\033[%d;%dH", 19, 0); /* Set cursor position (row 3, column 0 */
    printf("I am a function 3333333333333333333333333333333333333\n");
    sem_post(&sem1);
  }
  pthread_exit(NULL);		/* thread exits */
}

