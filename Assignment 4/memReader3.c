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

#define MESSAGE_SIZE      10000  // maximum length the message 

char message[MESSAGE_SIZE];

int main(int argc, char *argv[]) {
  struct stat st;
  int i;
  char *pt;
  int fd;

  // open file for reading
  fd = open(argv[1], O_RDONLY);

  fstat(fd, &st);
  pt = mmap(0, st.st_size, PROT_READ, MAP_SHARED, fd, 0);

  //print out first few characters
  for( i=0; i<3; i++){
    putchar(pt[i]);
  }

  printf("\n");
  close(fd);
  
  return 0;
}
