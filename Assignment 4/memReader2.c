/***********************************************************************
Program: memReader.c

Open a shared a shared memory object, map to that object and read it.

Donal Heffernan 6/November/2014   Updated 22/October/2015
************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define SHARED_OBJ_PATH   "don1337"   // pathname to shared object  
#define MESSAGE_SIZE      10000  // maximum length the message 

char message[MESSAGE_SIZE];

int main() {
  int mfd;  //file descriptor for the shared object
  int seg_size = getMessagePageSize(MESSAGE_SIZE);   //shared object sized to store message 
  char *shared_msg;
  int i;   //message iterator
  // open the shared memory object for reading  only  
  mfd = shm_open(SHARED_OBJ_PATH, O_RDONLY, S_IRWXU | S_IRWXG);
  if (mfd < 0) {
    perror("error shm_open(): forgot to run memWriter?");
    exit(1) ;
  }
      
  printf("Opened the shared memory object (read only): %s\n", SHARED_OBJ_PATH);
    
  // map the shared memory object to this process    
  shared_msg = mmap(NULL, seg_size, PROT_READ, MAP_SHARED, mfd, 0);
  if (shared_msg == NULL) {
    perror("error in  mmap()") ;
    exit(1);
  }

  // print first 5 A's
  for(i=0; i<5;i++){
    putchar(shared_msg[i]);
  }

  // print last 3 A's
  for(i=MESSAGE_SIZE-1; i>MESSAGE_SIZE-4; i--){
    putchar(shared_msg[i]);
  }
  
  printf("\nShared memory size allocated is %d bytes\n", seg_size);
    
  return 0;
}

int getMessagePageSize(int msg_size){
  int page_size = sysconf(_SC_PAGESIZE) ;
  int pages_required = msg_size/page_size;
  
  //left over (wasted) memory
  if(msg_size%page_size != 0 ){
    pages_required++;
  }

  printf("Pages required: %d\n", pages_required);
  return pages_required*page_size;
}
