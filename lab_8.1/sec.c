#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>

#define MSG_KEY 128
#define MSG_TYPE 1

typedef struct
{
  long mtype;
  int32_t timeout;
} msgbuf;


int main(int argc, char** argv)
{
  if (argc < 2)
  {
    printf("wrong param\n");
    return -1;
  }


  int msqid = msgget(MSG_KEY, IPC_CREAT | IPC_EXCL);

  if (msqid != -1)
  {
    printf("Receiver is not running!\n");
    msgctl(msqid, IPC_RMID, NULL);
    return -1;
  }

  msqid = msgget(MSG_KEY, 0);

  printf("MSQID = %d\n", msqid);

  int32_t timeout = atoi(argv[1]);

  msgbuf buf;
  buf.mtype = MSG_TYPE;
  buf.timeout = timeout;

  if (msgsnd(msqid, (void*)&buf,
                  sizeof(buf.timeout), 0) == -1)
  {
    perror("msgsnd error");
    return 0;
  }

  return 0;
}
