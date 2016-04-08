/***********************************************************************
Program: memWriter3.c

Loading a file into the process' memory for quicker write access.

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

int main(int argc, char *argv[]) {
  struct stat st;
  char *pt;
  int fd;

  // basic parameter check
  if(argc != 2){
    printf("Invalid parameters passed\n");
    return 1;
  }

  // open file for reading and writing
  fd = open(argv[1], O_RDWR);	
  fstat(fd, &st);  
  
  // map entire file to memory
  pt = mmap(0, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  // modify first character of file
  pt[0] = 'Z';

  // print out size and i-node for file
  printf("File size: %lu bytes\n", st.st_size);
  printf("File i-node: %lu\n", st.st_ino);

  // house keeping
  munmap(pt, st.st_size);
  close(fd);
  
  return 0;
}
