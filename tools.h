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
#define REQUEST 10
#define REPLY 11
#define MAXSIZE 128

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
struct msgbuf receiveMessage(int msgid, int receiveType);

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

struct msgbuf receiveMessage(int msgid, int receiveType) {
	struct msgbuf sbuf;
	//size_t buflen = strlen(sbuf.mtext) + 1;
	if (msgrcv(msgid, &sbuf, MAXSIZE, receiveType, 0) < 0) {
		die("msgrcv");
		sbuf.mtype = -1;
		return sbuf;
	}
	printf("(type = %ld) ", sbuf.mtype);
	//strcpy(outputBuf, sbuf.mtext);
	return sbuf;
}
