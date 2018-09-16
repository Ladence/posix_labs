#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <sched.h>

#define MAX_BUFF_SIZE 200

void instruction();
void process_routine(FILE* file);

int main(int argc, char** argv)
{
   if (argc < 2)
   {
     instruction();
     return -1;
   }
   
   FILE* file = fopen(argv[1], "r");
   
   if (file == NULL)
   {
     printf("Error file openning\n");
     return -1;
   }
   pthread_attr_t attr;
   int ret = pthread_attr_init(&attr);
   pthread_t printer_thread;
   int errcode = pthread_create(&printer_thread,
                                &attr,
  				process_routine,
				file
			       );
   ret = pthread_join(printer_thread, NULL);
   return 0;
}

void instruction()
{
   printf("Usage : ./threads [file_name]\n");
}

void process_routine(FILE* file)
{
  char buffer[MAX_BUFF_SIZE];
  while (fgets(buffer, MAX_BUFF_SIZE, file) != NULL)
  {
    puts(buffer);
  }
  if (feof(file))
  {
    printf("File has been successfully read\n");
  }
  else
  {
    printf("Some error\n");
    exit(-1);
  }
  
  int policy = SCHED_FIFO;
  struct sched_param sched;
  sched.sched_priority = 50;
  int ret = pthread_setschedparam(pthread_self(), policy, &sched);
  int s = pthread_getschedparam(pthread_self(), &policy, &sched);
  printf("sched_prior : %d\n", sched.sched_priority);
  printf("Policy : %d\n", policy);
  printf("Max priority : %d , Min priority : %d\n", sched_get_priority_max(policy), sched_get_priority_min(policy));
  fclose(file); 
}
