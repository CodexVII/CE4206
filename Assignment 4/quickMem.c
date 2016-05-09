#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char* argv[]){
  int p_size = sysconf(_SC_PAGESIZE);
  printf("Page size:%d\n", p_size);
  
  char *mem_block = (char*)malloc(p_size);
  int mfd = shm_open("mem_object", O_CREAT|O_RDWR, S_IRWXU|S_IRWXG);
  
  ftruncate(mfd, p_size);

  memset(&mfd, 'A', p_size);
  memcpy(mem_block, &mfd, 100);

  // print first 5 A's
  int i;
  for(i=0; i<p_size;i++){
    putchar(mem_block[i]);
  }
  
  shm_unlink("mem_object");
  free(mem_block);


  return 0;
}
