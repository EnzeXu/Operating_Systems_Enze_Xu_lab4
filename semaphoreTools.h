#include "basicTools.h"

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *arry;
	struct seminfo *__buf;
};

void dieSem(char *s);
int simpleSemid(int num, int flags, int proj);
int createSemid(int nums, int proj);
int attachSemid(int nums, int proj);
int initSem(int semid, int which, int val);
int setSem(int semid, int which, int op);
int P(int semid, int which, int op);
int V(int semid, int which, int op);
int removeSem(int semid, int which);

void dieSem(char *s) {
	perror(s);
	exit(1);
}

int simpleSemid(int num, int flags, int proj) {
	key_t key = ftok(".", proj);
	if (key > 0) {
		return semget(key, num, flags);
	}
	else {
		dieSem("simpleSemid");
		return -1;
	}
}

int createSemid(int nums, int proj) {
	return simpleSemid(nums, IPC_CREAT | IPC_EXCL | 0666, proj);
}

int attachSemid(int nums, int proj) {
	return simpleSemid(nums, IPC_CREAT, proj);
}

int removeSem(int semid, int which) {
	if (semctl(semid, which, IPC_RMID) > 0) {
		return 0;
	}
	else {
		dieSem("semctl");
		return -1;
	}
}

int initSem(int semid, int which, int val) {
	union semun su;
	su.val = val;
	if (semctl(semid, which, SETVAL, su) < 0) {
		dieSem("semctl");
		return -1;
	}
	return 0;
}

int setSem(int semid, int which, int op) {
	struct sembuf sb;
	sb.sem_num = which;
	sb.sem_op = op;
	sb.sem_flg = 0;
	return semop(semid, &sb, 1);
}

int P(int semid, int which, int op) {
	if (setSem(semid, which, op) < 0) {
		dieSem("P");
		return -1;
	}
	return 0;
}

int V(int semid, int which, int op) {
	if (setSem(semid, which, op) < 0) {
		dieSem("V");
		return -1;
	}
	return 0;
}
