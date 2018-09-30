#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

void  instruction();
void  print_attributes(const char* process_name, FILE* file);

int main(int argc, char** argv)
{
 time_t t = time(NULL);
 struct tm tm = *localtime(&t);

 if (argc < 3)
 {
   instruction();
   return -1;
 }

 FILE* file = fopen(argv[1], "a");
 
 //fprintf(file, "\n\n");

 if (file == NULL)
 {
  puts("Error openning file!");
  return -1;
 }

 pid_t child_pid = fork();
 int rv;

 if (child_pid == 0)
 {
   usleep(atoi(argv[2]));
   print_attributes("Potomok1", file);
   fclose(file);
   return 0;
 }
 else if (child_pid < 0)
 {
  printf("Failure fork 1\n");
  return -1;
 }
 
 pid_t sec_child_pid = vfork();
 
 if (sec_child_pid == 0)
 {
  if (execl("./child",
 "./child", argv[1], "Potomok2", argv[3], NULL) == -1)
  {
    printf("Failure child2 execl %d\n", errno);
    return -1;
  }
 }
 else if (sec_child_pid < 0)
 {
  printf("Failure fork 2\n");
  return -1;
 }

 usleep(atoi(argv[4]));
 print_attributes("Roditel", file);
 fclose(file);

 for (int i = 0; i < 2; i++)
 	wait(NULL);

 return 0;
}

void instruction()
{
  printf("Usage : ./fork [filename] [msec delay (int)1] [2] [3]\n");
}


void  print_attributes(const char* process_name, FILE* file)
{
  puts(process_name);
  pid_t cur_pid = getpid();
  fprintf(file, "________________________________\n");
  fprintf(file, "Process name : ");
  fputs(process_name, file);
  fprintf(file, "\nPID : %ld\n", (long)cur_pid);
  fprintf(file, "Session ID : %ld\n", (long)getsid(cur_pid));
  fprintf(file, "Group ID : %ld\n", (long)getpgid(cur_pid));
  fprintf(file, "User ID : %ld\n", (long)getuid());
  fprintf(file, "________________________________\n");
}
