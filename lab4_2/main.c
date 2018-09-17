#include <stdio.h>
#include <pthread.h>
#include <string.h>

#define MAX_BUF_LEN 200

typedef struct thread_args
{
  char buf[MAX_BUF_LEN];
  FILE* file;
} thread_args_t;

static void fill_thread_args(thread_args_t* args, const char* buf, FILE* file)
{
  (void)strncpy(args->buf, buf, MAX_BUF_LEN);
  args->file = file;
}

void instruction();
void thr_routine(void *);

int main(int argc, char** argv)
{
  if (argc < 4)
  {
    instruction();
    return -1;
  }

  FILE* in       = fopen(argv[1], "r");
  FILE* odd_out  = fopen(argv[2], "w+");
  FILE* even_out = fopen(argv[3], "w+");
  
  if (in == NULL || odd_out == NULL || even_out == NULL)
  {
    printf("Failure openning file\n");
    return -1;
  }

  char  buf[MAX_BUF_LEN];
  int   res;
  int   i = 0;
  
  thread_args_t args;

  while (fgets(buf, MAX_BUF_LEN, in) != NULL)
  {
    pthread_t odd_thr;
    pthread_t even_thr;
    //puts(buf);

    if (i % 2 == 0)
    {
      puts("ODD");
      fill_thread_args(&args, buf, odd_out);
      res = pthread_create(
                         &odd_thr,
                         NULL,
                         &thr_routine,
                         (void*)&args
                          );
       res = pthread_join(odd_thr, NULL);
       //printf("res %d\n", res);
    }
    else
    {
      puts("EVEN");
      fill_thread_args(&args, buf, even_out);

      res = pthread_create(
                         &even_thr,
                         NULL,
                         &thr_routine,
                         (void*)&args
                           );
      res = pthread_join(even_thr, NULL);
    }

    i++;                             
  }

  fclose(in);
  fclose(odd_out);
  fclose(even_out);
  return 0;
}

void instruction()
{
  printf("Usage : ./threads2 [in file_name] [out_odd file_name] [out_even file_name]");
}

void thr_routine(void* buf)
{
  thread_args_t* args = (thread_args_t *)buf;
  fputs(args->buf, args->file);
  pthread_exit(NULL);
  //return;
  /*thread_args_t* arg = (thread_args_t*)args;
  fprintf(arg->file, arg->buf);*/
  //puts(arg->buf);
}
