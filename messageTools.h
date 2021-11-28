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

#define PROJ 0x2021
#define REQUEST 0
#define REPLY 1
#define MAXSIZE 128
#define FALSE 0
#define TRUE 1

struct msgbuf {
	long mtype;
	int source;
	int snum;
};

void die(char *s);
int simpleMessageQueue(int flags);
int createMessageQueue();
int attachMessageQueue();
int removeMessageQueue(int msgid);
int sendMessage(int msgid, int mtype, int source, int snum);
int receiveMessage(int msgid, int receiveType, struct msgbuf *outputBuf);

void die(char *s) {
	perror(s);
	exit(1);
}

int simpleMessageQueue(int flags) {
	key_t key = ftok(".", PROJ);
	if (key < 0) {
		perror("ftok");
		return -1;
	}
	int msgid = msgget(key, flags);
	if (msgid < 0) {
		die("msgget");
	}
	return msgid;
}

// IPC_CREAT | IPC_EXCL: create exclusive, fails if resource exists
int createMessageQueue() {
	return simpleMessageQueue(IPC_CREAT | IPC_EXCL | 0666);
}

// IPC_CREAT: create if it does not exists
int attachMessageQueue() {
	return simpleMessageQueue(IPC_CREAT);
}

int removeMessageQueue(int msgid) {
	if (msgctl(msgid, IPC_RMID, NULL) < 0) {
		die("msgctl");
		return -1;
	}
	return 0;
}

int sendMessage(int msgid, int mtype, int source, int snum) {
	printf("start sending...\n");
	struct msgbuf sbuf;
	sbuf.mtype = mtype;
	sbuf.source = source;
	sbuf.snum = snum;
	// strcpy(sbuf.mtext, msg);
	// size_t buflen = strlen(sbuf.mtext) + 1;
	if (msgsnd(msgid, &sbuf, sizeof(sbuf), IPC_NOWAIT) < 0) {
		die("msgsnd");
		return -1;
	}
	return 0;
}

int receiveMessage(int msgid, int receiveType, struct msgbuf *outputBuf) {
	printf("start receiving...\n");
	//struct msgbuf sbuf;
	//size_t buflen = strlen(sbuf.mtext) + 1;
	if (msgrcv(msgid, outputBuf, sizeof(struct msgbuf), receiveType, 0) < 0) {
		die("msgrcv");
		return -1;
	}
	printf("here\n");
	//*outputBuf = sbuf;
	//outputBuf->mtype = sbuf.mtype;
	//outputBuf->source = sbuf.source;
	//outputBuf->snum = sbuf.snum;
	//strcpy(outputBuf, sbuf.mtext);
	return 0;
}
/*
int semop(int semid,  struct sembuf *sops,  unsigned int nsops);

struct sembuf {
	unsigned short sem_num;
	short int sem_op;
	short int sem_flag;
};
*/



