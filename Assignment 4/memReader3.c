/***********************************************************************
Program: memReader3.c

Load a file into the process' memory for reading.

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


int main(int argc, char *argv[]) {
  struct stat st;
  int i;
  char *pt;
  int fd;

  // basic parameter check
  if(argc != 2){
    printf("Invalid parameters passed\n");
    return 1;
  }

  // open file for reading
  fd = open(argv[1], O_RDONLY);
  fstat(fd, &st);

  // map entire file to memory.
  pt = mmap(0, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

  //print out first few characters
  for( i=0; i<3; i++){
    putchar(pt[i]);
  }

  printf("\n");

  // house keeping
  munmap(pt, st.st_size);
  close(fd);
  
  return 0;
}
