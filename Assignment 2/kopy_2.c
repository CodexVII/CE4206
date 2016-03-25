/******************************************************************
kopy.c
An example Unix-like shell copy command/utility.
Copies the first file to the second. Options to be defined.
Author: Ian Lodovica
Date: 25th of February 2016

issues
islower(buff[i]) not picking up lower case chars
  wrong iterator
process time giving incorrect results. 
  resolved by using double during calculations
unit conversion
  divide file size by 1024 to get it in kB
*****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>

int main (int argc, char *argv[]) {
  int i, j;                         // i looped through params, j looped through buffer
  int fileArg = 0;                  // Count for files on command line
  int infd, outfd;                  // File descriptor for input and output file
  int num_read, num_write;          // Numbers of characters returned by a file access
  int buff_iter = 0;                // counts the amount of iterations that the buffer is used
  double process_time = 0;          // keeps track of how much time has passed while copying
  double start, end;                // microseconds used while calculating process time
  double copy_rate;                 // stores the copy speed in kB/s
  double file_size;                 // stores size in kB
  char buff [4096];                 // sets buffer size used for copying

  //used to find processing time
  struct timeval startVal;
  struct timeval endVal;

  //flags
  int uppercase_flag = 0;
  int filesize_flag = 0;
  int copyrate_flag = 0;

  // Buffer for use in file access
  char* fileName[2] = {} ; // Point to file names
  // Parse the command line arguments
  for ( i = 1 ; i < argc; i++ ){
    if (argv[i][0] == '-'){
      // Check for a command option
      // Only checks for seperated options
      switch(argv[i][1]){
      case 'u':
	uppercase_flag = 1;
	break;
      case 's':
        filesize_flag = 1;
	break;
      case 'r':
	copyrate_flag = 1;
	break;
      default:
	printf("Unknown modifier. Only -u -s -r modifiers allowed\n");
      }
    }
    else{
      fileName[fileArg++] = argv[i];
    }
  }

  // Open the first file for reading
  infd = open (fileName[0], O_RDONLY);
  if (infd == -1){
    printf ("Failed to open first file %s\n", fileName[0]);
    return 1;
  }

  // Open/create the second file for writing
  outfd = open (fileName[1], O_CREAT | O_WRONLY, 0600 );
  if (outfd == -1){
    printf ("Failed to open second file %s\n", fileName[1]);
    close (infd);
    return 1;
  }
  
  //get time before copying starts
  gettimeofday(&startVal, NULL);
  
  // Now copy the contents of the first file to the second file
  while ( ( num_read = read (infd, buff, sizeof (buff)) ) > 0 ) {
    //capitalize as needed
    if(uppercase_flag){
      for(j = 0; j < sizeof(buff); j++){
	if(islower(buff[j])){
	  buff[j] = toupper(buff[j]);
	}
      }
    }
    
    //count iterations to get size with 1kB resolution
    buff_iter++;

    num_write = write (outfd, buff, num_read);
    // Check for basic failure
    if (num_write != num_read){
      printf ("Problem - mismatch between write size and read size!\n");
    }
  }

  //get time after copying finishes
  gettimeofday(&endVal, NULL);
  
  //calculate processing time in microseconds
  start = startVal.tv_sec*1000000 + startVal.tv_usec;
  end = endVal.tv_sec*1000000 + endVal.tv_usec;
  process_time = (end - start);

  //get rough file size
  //divide size by 1024 to go from bytes to kB
  file_size = ((double) buff_iter*sizeof(buff))/1024;

  //get copy rate
  //divide by 1000000 to go from microseconds to seconds
  copy_rate = (double) file_size/(process_time/1000000);

  if(uppercase_flag){
    printf("Output has been capitalized\n");
  }

  if(filesize_flag){
    printf("File size is %.f kB\n", file_size);
  }

  if(copyrate_flag){
    printf("Process time: %.f us\n", process_time);
    printf("Copy rate is %.2f kB/s\n", copy_rate);
  }

  // Remember to close all open files before exit
  close (outfd);
  close (infd);
  return 0 ;
}
