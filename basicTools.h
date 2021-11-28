#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <error.h>

#define PROJ 0x2021
#define PROJ_SEM_1 0x0001
#define PROJ_SEM_2 0x0002
#define REQUEST 0
#define REPLY 1
#define MAXSIZE 128
#define FALSE 0
#define TRUE 1

void die(char *s);
void quitHandler(int theInt);

void die(char *s) {
	perror(s);
	exit(1);
}

void quitHandler(int theInt) { // signal handler used to ignore Ctrl-C
	//fflush(stdin);
	//printf("\n[Enze Shell] Not QUITTING (SIGINT = %d)\n", theInt);
	//printf("\n%s %% ", getMainPath());
	//fflush(stdout);
	exit(1);
	return;
}