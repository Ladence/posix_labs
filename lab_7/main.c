#include <stdio.h>

void instruction();

int main(int argc, char** argv)
{
  if (argc < 3)
  {
    instruction();
    return -1;
  }
  return 0;
}

void instruction()
{
  printf("Usage ./per [period] [count]"\n);
}

