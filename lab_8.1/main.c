#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <signal.h>
#include <sys/time.h>

#define MSG_KEY 128
#define MSG_TYPE 1

typedef struct
{
  long mtype;
  int32_t timeout;
} msgbuf;

key_t g_msqid;

void signal_h(int sig)
{
  msgctl(g_msqid, IPC_RMID, NULL);
  printf("Timeout reached\n");
  exit(1);
}

int main(int argc, char** argv)
{
  if (argc < 2)
  {
    printf("wrong param\n");
    return -1;
  }

  int timeout = atoi(argv[1]);

  g_msqid = msgget(MSG_KEY, IPC_CREAT | 0666);

  if (g_msqid == -1)
  {
    perror("error at msgget()");
    return -1;
  }

  printf("MSQID = %d\n", g_msqid);


  signal(SIGALRM, signal_h);

  do {
    struct itimerval timer;

    timer.it_value.tv_sec = timeout;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL, &timer, NULL);

    msgbuf received;

    if (msgrcv(g_msqid, (void*)&received, sizeof(received),
              MSG_TYPE, 0) == -1)
    {
        perror("msgrcv");
        return -1;
    }
    else
    {
      timeout = received.timeout;
      printf("Timeout gain : %d\n", timeout);
    }
  } while(1);

  return 0;
}
