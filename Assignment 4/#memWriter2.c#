/***********************************************************************
Program: memWriter2.c

Had to make sure correct page size was allocated else the shared message
object will be corrupted

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

#define SHARED_OBJ_PATH  "Acting"   // pathname to shared object       
#define MESSAGE_SIZE      10000     // maximum length the message 

char message[MESSAGE_SIZE];
int getMessagePageSize(int msg_size);

int main() {
  int mfd; //file descriptor for the shared object
  int seg_size = getMessagePageSize(MESSAGE_SIZE);   //shared object sized to store message
  char *shared_msg;
  
  // populate message array with 'A's
  memset(&message, 'A', MESSAGE_SIZE);
  
  // create the shared memory object with shm_open()  
  mfd = shm_open(SHARED_OBJ_PATH, O_CREAT | O_RDWR, S_IRWXU | S_IRWXG);
  if (mfd < 0) {
    perror("error in shm_open()");
    exit(1);
  }
  
  printf("I have created a lucky shared memory object:  %s\n", SHARED_OBJ_PATH);
    
  //set SHARED_OBJ_PATH to have a memory size of 1 page.
  ftruncate(mfd, seg_size); 

  // map the shared memory object to this process    
  shared_msg = mmap(NULL, seg_size, PROT_READ | PROT_WRITE, MAP_SHARED, mfd, 0);
  if (shared_msg == NULL) {
    perror("error in mmap()");
    exit(1);
  }
    
  printf("Shared memory is now allocated %d bytes\n", seg_size );

  // put the 10000 'A's into memory
  memcpy(shared_msg, message, MESSAGE_SIZE); 
  
  printf("Message content is: %s\n\n Hit any key to finish!\n", shared_msg) ;
  getchar() ; // wait for user to hit any key
   
  // house keeping
  munmap(shared_msg, seg_size);
  close(mfd);
  shm_unlink(SHARED_OBJ_PATH);

  return 0 ;
} 

int getMessagePageSize(int msg_size){
  int page_size = sysconf(_SC_PAGESIZE);
  int pages_required = msg_size/page_size;
  
  //left over (wasted) memory
  if(msg_size%page_size != 0 ){
    pages_required++;
  }

  printf("Pages required: %d\n", pages_required);
  return pages_required*page_size;
}
