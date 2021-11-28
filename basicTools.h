#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <error.h>

#define PROJ 0x2021
#define REQUEST 0
#define REPLY 1
#define MAXSIZE 128
#define FALSE 0
#define TRUE 1

void die(char *s);

void die(char *s) {
	perror(s);
	exit(1);
}