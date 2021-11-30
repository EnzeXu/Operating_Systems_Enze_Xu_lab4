#include "basicTools.h"

void dieShm(char *s);
int createShm(int size, int proj);
int removeShm(int shmid);
int attachShm(int size, int proj);

void dieShm(char *s) {
	perror(s);
	exit(1);
}

int simpleShm(int size, int flags, int proj) {
	key_t key = ftok(".", proj);
	if (key < 0) {
		dieShm("ftok");
		return -1;
	}
	int shmid = shmget(key, size, flags);
	if (shmid < 0) {
		dieShm("shnget");
		return -1;
	}
	return shmid;
}

int createShm(int size, int proj) {
	return simpleShm(size, IPC_CREAT | IPC_EXCL | 0666, proj);
}

int attachShm(int size, int proj) {
	return simpleShm(size, IPC_CREAT, proj);
}

int removeShm(int shmid) {
	if(shmctl(shmid, IPC_RMID, NULL) < 0){
		dieShm("shmctl");
		return -1;
	}
	return 0;
}

