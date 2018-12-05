#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <sys/ipc.h>
#include <sys/shm.h>

#define ARR_SIZE 5

int main(int argc, char** argv)
{
  int array[ARR_SIZE] = {0,1,2,3,4};

  int red_array[ARR_SIZE] = {0};

  key_t key = 5678;

  // open first shared memory
  int idshm = shmget(key, ARR_SIZE, IPC_CREAT | 0666);

  if (idshm < 0)
  {
    perror("shmget");
    return -1;
  }

  key_t sec_key = 5679;

  // open second shared memory
  int secshmid = shmget(sec_key, ARR_SIZE, IPC_CREAT | 0666);

  if (secshmid < 0)
  {
    perror("second shmget");
    return -1;
  }

  void* reduced_data = shmat(secshmid, NULL, 0);

  void* dataptr = shmat(idshm, NULL, 0);

  if (dataptr == (void*)-1)
  {
    perror("shmat");
    return -1;
  }

  if (reduced_data == (void*)-1)
  {
    perror("shmat second");
    return -1;
  }

  memcpy(dataptr, array, ARR_SIZE * sizeof(int));

  uint8_t sync = 0;

  *(uint8_t*)(reduced_data) = sync;

  memcpy(reduced_data + 1, red_array, ARR_SIZE * sizeof(int));

  // busy loop while sync == 0
  while (*(uint8_t*)(reduced_data) == 0);

  printf("After reducing (Second to first)\n");
  int* reduced = (int*)(reduced_data + 1);

  for (int i = 0; i < ARR_SIZE; i++)
  {
    printf("%d ", *(reduced + i));
  }

  printf("\n");

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

  if (shmctl(idshm, IPC_RMID, NULL) < 0)
  {
    perror("shmctl");
    return -1;
  }

  if (shmctl(secshmid, IPC_RMID, NULL) < 0)
  {
    perror("shmctl second");
    return -1;
  }

  return 0;
}
