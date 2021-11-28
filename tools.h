#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define PROJ 0x2021
#define SERVER_TYPE 1
#define CLIENT_TYPE 2
#define MAXSIZE 128

struct msgbuf {
	long mtype;
	char mtext[MAXSIZE];
};

void die(char *s);
int simpleMessageQueue(int flags);
int createMessageQueue();
int attachMessageQueue();
int removeMessageQueue(int msgid);
int sendMessage(int msgid, int who, char *msg);
int receiveMessage(int msgid, int recvType, char out[]);

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

int sendMessage(int msgid, int who, char *msg) {
	struct msgbuf sbuf;
	sbuf.mtype = who;
	strcpy(sbuf.mtext, msg);
	size_t buflen = strlen(sbuf.mtext) + 1;
	if (msgsnd(msgid, &sbuf, buflen, IPC_NOWAIT) < 0) {
		die("msgsnd");
		return -1;
	}
	return 0;
}

int receiveMessage(int msgid, int recvType, char out[]) {
	struct msgbuf sbuf;
	//size_t buflen = strlen(sbuf.mtext) + 1;
	if (msgrcv(msgid, &sbuf, MAXSIZE, recvType, 0) < 0) {
		die("msgrcv");
		return -1;
	}
	strcpy(out, sbuf.mtext);
	return 0;
}
