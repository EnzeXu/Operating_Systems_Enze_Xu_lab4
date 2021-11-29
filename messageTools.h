#include "basicTools.h"

struct msgbuf {
	long mtype;
	int source;
	int snum;
	char mtext[MAXSIZE];
};

void dieMsg(char *s);
int randomInt(int k);
int simpleMessageQueue(int flags, int proj);
int createMessageQueue(int proj);
int attachMessageQueue(int proj);
int removeMessageQueue(int msgid);
int sendMessage(int msgid, int mtype, int source, int snum, char *mtext);
int receiveMessage(int msgid, int receiveType, struct msgbuf *outputBuf);

void dieMsg(char *s) {
	perror(s);
	exit(1);
}

int randomInt(int k) {
	return rand() % k;
}

int simpleMessageQueue(int flags, int proj) {
	key_t key = ftok(".", proj);
	if (key < 0) {
		dieMsg("ftok");
		return -1;
	}
	int msgid = msgget(key, flags);
	if (msgid < 0) {
		dieMsg("msgget");
		return -1;
	}
	return msgid;
}

// IPC_CREAT | IPC_EXCL: create exclusive, fails if resource exists
int createMessageQueue(int proj) {
	return simpleMessageQueue(IPC_CREAT | IPC_EXCL | 0666, proj);
}

// IPC_CREAT: create if it does not exists
int attachMessageQueue(int proj) {
	return simpleMessageQueue(IPC_CREAT, proj);
}

int removeMessageQueue(int msgid) {
	if (msgctl(msgid, IPC_RMID, NULL) < 0) {
		dieMsg("msgctl");
		return -1;
	}
	return 0;
}

int sendMessage(int msgid, int mtype, int source, int snum, char mtext[]) {
	//printf("start sending...\n");
	struct msgbuf sbuf;
	sbuf.mtype = mtype;
	sbuf.source = source;
	sbuf.snum = snum;
	strcpy(sbuf.mtext, mtext);
	// strcpy(sbuf.mtext, msg);
	// size_t buflen = strlen(sbuf.mtext) + 1;
	usleep(randomInt(1000000));
	if (msgsnd(msgid, &sbuf, sizeof(sbuf) - sizeof(long), IPC_NOWAIT) < 0) {
		dieMsg("msgsnd");
		return -1;
	}
	return 0;
}

int receiveMessage(int msgid, int receiveType, struct msgbuf *outputBuf) {
	//printf("start receiving...\n");
	//struct msgbuf sbuf;
	//size_t buflen = strlen(sbuf.mtext) + 1;
	if (msgrcv(msgid, outputBuf, sizeof(struct msgbuf) - sizeof(long), receiveType, 0) < 0) {
		dieMsg("msgrcv");
		return -1;
	}
	//printf("here\n");
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



