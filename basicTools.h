#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <error.h>
//#include <pthread.h>

#define PROJ_MSG 0x0001
//#define PROJ_SEM_1 0x0002
//#define PROJ_SEM_2 0x0003
#define REQUEST 0
#define REPLY 1
#define MAXSIZE 1024
#define MAXN 64
#define MAXREQUEST 10
#define FALSE 0
#define TRUE 1
