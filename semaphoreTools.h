#include "basicTools.h"

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *arry;
	struct seminfo *__buf;
};

static int simpleSemid(int num, int flags);
int createSemid(int nums);
int attachSemid(int nums);
int initSem(int semid, int which, int val);
static int setSem(int semid, int which, int op);
int P(int semid, int which, int op);
int V(int semid, int which, int op);
int removeSem(int semid);


static int simpleSemid(int num, int flags) {
	key_t key = ftok(".", PROJ);
	if (key > 0) {
		return semget(key, num, flags);
	}
	else {
		die("simpleSemid");
		return -1;
	}
}

int createSemid(int nums) {
	return simpleSemid(nums, IPC_CREAT | IPC_EXCL | 0666);
}

int attachSemid(int nums) {
	return simpleSemid(nums, IPC_CREAT);
}

int removeSem(int semid) {
	if (semctl(semid, 0, IPC_RMID) > 0) {
		return 0;
	}
	else {
		die("semctl");
		return -1;
	}
}

int initSem(int semid, int which, int val) {
	union semun su;
	su.val = val;
	if (semctl(semid, which, SETVAL, su) < 0) {
		die("semctl");
		return -1;
	}
	return 0;
}

static int setSem(int semid, int which, int op) {
	struct sembuf sb;
	sb.sem_num = which;
	sb.sem_op = op;
	sb.sem_flg = 0;
	return semop(semid, &sb, 1);
}

int P(int semid, int which, int op) {
	if (setSem(semid, which, op) < 0) {
		die("P");
		return -1;
	}
	return 0;
}

int V(int semid, int which, int op) {
	if (setSem(semid, which, op) < 0) {
		die("V");
		return -1;
	}
	return 0;
}
