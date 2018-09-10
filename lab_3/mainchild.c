#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void  instruction();
void  print_attributes(const char* process_name, FILE* file);

int main(int argc, char** argv)
{
 
 if (argc < 3)
 {
   instruction();
   return -1;
 }
 
 FILE* file = fopen(argv[1], "r+");
 //printf("Size of file %ld bytes\n", ftell(file));
 fseek(file, 0, SEEK_END);

 if (file == NULL)
 {
   printf("Failure fopen");
 }

 print_attributes(argv[2], file);
 fclose(file);
 return 0;
}

void instruction()
{
  printf("Usage : ./fork [filename] [process_name]\n");
}


void  print_attributes(const char* process_name, FILE* file)
{
  fprintf(file, "Process name : ");
  fputs(process_name, file);
  fprintf(file, "\nPID : %ld\n", (long)getpid());
}
