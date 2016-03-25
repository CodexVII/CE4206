/* 
   Program: console.c
   A simple program example where a semaphore is used to lock the console
   upon writing to it.

   Notes:
     compiled with gcc -pthread -o console console.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>

/* Declare a semaphore called mutex_A */
sem_t mutex_A;

main(){
  sem_init(&mutex_A, 0, 1);	/* Initialise the console access */

  /* Use the semaphore to provide mutual exclusion on the console access */
  sem_wait(&mutex_A);		/* do a semaphore wait on mutex_A */
  printf("I have exclusive access to the console!\n");
  sem_post(&mutex_A);		/* do a semaphore post (ie. signal) on mutex_A */
  sem_destroy(&mutex_A); 	/* house cleaning on semaphore before exit */
  exit(0);
}
