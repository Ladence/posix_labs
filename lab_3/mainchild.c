#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void  instruction();
void  print_attributes(const char* process_name, FILE* file);

int main(int argc, char** argv)
{
 
 if (argc < 4)
 {
   instruction();
   return -1;
 }
 
 FILE* file = fopen(argv[1], "a");

 if (file == NULL)
 {
   printf("Failure fopen");
   return -1;
 }

 usleep(atoi(argv[3]));
 print_attributes(argv[2], file);
 fclose(file);
 return 0;
}

void instruction()
{
  printf("Usage : ./fork [filename] [process_name] [msec delay]\n");
}


void  print_attributes(const char* process_name, FILE* file)
{
  puts(process_name);
  pid_t cur_pid = getpid();
  fprintf(file, "Process name : ");
  fputs(process_name, file);
  fprintf(file, "\nPID : %ld\n", (long)getpid());
  fprintf(file, "Session ID : %ld\n", (long)getsid(cur_pid));
  fprintf(file, "Group ID : %ld\n", (long)getpgid(cur_pid));
  fprintf(file, "User ID : %ld\n", (long)getuid());
  fprintf(file, "________________________________\n");
}
