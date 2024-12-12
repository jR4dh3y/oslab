#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void wait(){
  printf("Press Enter to continue...");
  while(getchar() != '\n');
}


int main(int argc, char **argv) {
  int megabytes = 0;
  megabytes = atoi(argv[1]);
  
  printf("Memory Allocation\n");

  size_t bytes = megabytes * 1024 * 1024;
  printf("Allocating %zu bytes\n", bytes);
  wait();

  char *ptr = (char *)malloc(bytes);
  printf("Memory allocated\n");
  memset(ptr, 1, bytes);

  wait();
  free(ptr);

  return 0;
}
