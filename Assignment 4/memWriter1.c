/***********************************************************************
Program: memWriter1.c

A simple example on shared memory.
Create/open a shared memory object, map to that object and write to it. Unlink object.

Works as normal even if mmcpy() is replaced with write() however
the fd had to be written into with the message before being mapped into
the process

Author: Ian Lodovica (13131567)
Date: 8th of April 2016
************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define SHARED_OBJ_PATH  "Acting" // pathname to shared object       
#define MESSAGE_SIZE      100     // maximum length the message 

char message[MESSAGE_SIZE] = "Hello World";

int main() {

  int mfd; //file descriptor for the shared object
  int seg_size = (sizeof(message));   //shared object sized to store message
  char *shared_msg;

  // create the shared memory object with shm_open()  
  mfd = shm_open(SHARED_OBJ_PATH, O_CREAT | O_RDWR, S_IRWXU | S_IRWXG);
  if (mfd < 0) {
    perror("error in shm_open()");
    exit(1);
  }

  // write to the file descriptor
  write(mfd, message, MESSAGE_SIZE);
  
  printf("I have created a lucky shared memory object:  %s\n", SHARED_OBJ_PATH);
    
  ftruncate(mfd, seg_size) ; // define size of shared memory object

  // map the shared memory object to this process    
  shared_msg = mmap(NULL, seg_size, PROT_READ | PROT_WRITE, MAP_SHARED, mfd, 0);
  if (shared_msg == NULL) {
    perror("error in mmap()");
    exit(1);
  }
    
  printf("Shared memory is now allocated %d bytes\n", seg_size);
  
  printf("Message content is: %s\n\n Hit any key to finish!\n", shared_msg) ;
  getchar() ; // wait for user to hit any key
   
  // house keeping
  munmap(shared_msg, seg_size);
  close(mfd);
  shm_unlink(SHARED_OBJ_PATH);

  return 0 ;
} 
