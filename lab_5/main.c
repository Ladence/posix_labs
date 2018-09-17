#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

void divide_by_zero_handler(int);
void segfault_handler(int);
void instruction();

int main(int argc, char** argv)
{
  if (argc < 2)
  {
    instruction();
    return -1;
  }
 
  if (atoi(argv[1]) != 0 && atoi(argv[1]) != 1)
  {
    instruction();
    return -1;
  }
  
  signal(SIGFPE, divide_by_zero_handler);
  signal(SIGSEGV, segfault_handler);
  
  if (strcmp(argv[1], "0") == 0)
  {
    int a = 5/0;
  }
  
  if (strcmp(argv[2], "1") == 0)
  {
    int* causer = NULL;
    *causer = 50;
  }
  return 0;
}

void instruction()
{
 printf("Usage : ./sigs [err]\n");
 printf("err = 0 - Division by zero (SIGFPE)\n");
 printf("err = 1 - Memory protection violation (SIGSEGV)\n");
}

void divide_by_zero_handler(int signum)
{
  printf("Divide by zero!\n");
  exit(-1);
}

void segfault_handler(int signum)
{
  printf("Segmentation fault. Memory protection violation\n");
  exit(-1);
}
