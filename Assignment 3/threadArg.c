/* 
   Program: threadArg.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

void *my_function(void*);	/* Thread function */

struct rusage ru;
int main(){
  pthread_t my_thread;
  int rc1;
  int x=100000;


  /* Create thread */
  rc1 = pthread_create(&my_thread, NULL, &my_function, (void*)&x);

  /* Wait for the thread to exit */
  pthread_join(my_thread, NULL); 

  getrusage(RUSAGE_SELF, &ru);

  /* Print out resource used */
  printf ("Usage results for this program are:\n\n");
  printf("User space CPU time used:\t%6lu  %6lu\n",  ru.ru_utime.tv_sec, ru.ru_utime.tv_usec   );
  printf("Kernel CPU time used:\t\t%6lu  %6lu\n",  ru.ru_stime.tv_sec, ru.ru_stime.tv_usec   );

  exit(0);
}

void *my_function(void *arg){
  int i = *(int*)arg;
  
  while(i > 0){
    printf("Integer i has the value %d\n", i);
    i--;
  }

  pthread_exit(NULL);
}
