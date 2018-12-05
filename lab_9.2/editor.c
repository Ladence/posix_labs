#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <sys/ipc.h>
#include <sys/shm.h>

#define ARR_SIZE 5

void reduce_elements(int*, size_t);

int main(int argc, char const *argv[])
{
  int array[ARR_SIZE];

  key_t key = 5678;
  key_t sec_key = 5679;

  int shmid = shmget(key, ARR_SIZE, 0666);

  if (shmid < 0)
  {
    perror("shmget");
    return -1;
  }

  void* dataptr = shmat(shmid, NULL, 0);

  if (dataptr == (void*)-1)
  {
    perror("shmat");
    return -1;
  }

  printf("From first process : ");

  for (int i = 0; i < ARR_SIZE; i++)
  {
    array[i] = *(int*)dataptr + i;
    printf("%d ", array[i]);
  }
  printf("\n");

  reduce_elements(array, ARR_SIZE);

  // open second shared memory
  int secshmid = shmget(sec_key, ARR_SIZE, IPC_CREAT | 0666);

  if (secshmid < 0)
  {
    perror("second shmget");
    return -1;
  }

  void* reduced_data = shmat(secshmid, NULL, 0);

  if (reduced_data == (void*)-1)
  {
    perror("shmat reduced");
    return -1;
  }

  memcpy(reduced_data + 1, array, ARR_SIZE * sizeof(int));
  // set sync as 1 so main proc can read
  *(uint8_t*)(reduced_data) = 1;

  //detach
  if (shmdt(reduced_data) < 0)
  {
    perror("shmdt reduced");
    return -1;
  }

  if (shmdt(dataptr) < 0)
  {
    perror("shmdt");
    return -1;
  }

  return 0;
}

void reduce_elements(int* array, size_t sz)
{
  for (int i = 0; i < sz; i++)
  {
    array[i] -= 1;
  }
}
