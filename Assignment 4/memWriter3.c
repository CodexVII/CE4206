/***********************************************************************
Program: memWriter.c

A simple example on shared memory.
Create/open a shared memory object, map to that object and write to it. Unlink object.

Works as normal even if mmcpy() is replaced with write() however
the fd had to be written into with the message before being mapped into
the process

Had to make sure correct page size was allocated else the shared message
object will be corrupted

Donal Heffernan 6/November/2014     Updated 22/October/2015
************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
  struct stat st;
  off_t len;
  char *pt;
  int fd;

  // open file for reading and writing
  fd = open(argv[1], O_RDWR);	
  fstat(fd, &st);  
  
  // map entire file to memory
  pt = mmap(0, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  // modify first character of file
  pt[0] = 'Z';

  // print out size and i-node for file
  printf("File size: %lu\n", st.st_size);
  printf("File i-node: %lu\n", st.st_ino);

  close(fd);
  //  unlink(argv[1]);

  return 0;
}
