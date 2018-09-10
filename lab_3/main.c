#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

void  instruction();
void  print_attributes(const char* process_name, FILE* file);

int main(int argc, char** argv)
{
 
 if (argc < 2)
 {
   instruction();
   return -1;
 }

 FILE* file = fopen(argv[1], "w");
 
 if (file == NULL)
 {
  puts("Error openning file!");
  return -1;
 }

 print_attributes("Roditel", file);
 fclose(file);

 pid_t child_pid = fork();
 if (child_pid == 0)
 {
  if (execl("/home/karlin/Desktop/lab_3/child",
 "/home/karlin/Desktop/lab_3/child", argv[1], "Potomok1", NULL) == -1)
  {
    printf("Failure child1 execl %d\n", errno);
    return -1;
  }
 }
 else if (child_pid == -1)
 {
  printf("Failure fork 1\n");
 }

 pid_t sec_child_pid = vfork();
 
 if (sec_child_pid == 0)
 {
  if (execl("/home/karlin/Desktop/lab_3/child",
 "/home/karlin/Desktop/lab_3/child", argv[1], "Potomok2", NULL) == -1)
  {
    printf("Failure child2 execl %d\n", errno);
    return -1;
  }
 }
 else if (sec_child_pid == -1)
 {
  printf("Failure fork 2\n");
 }

 //fclose(file);
 return 0;
}

void instruction()
{
  printf("Usage : ./fork [filename]\n");
}


void  print_attributes(const char* process_name, FILE* file)
{
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
