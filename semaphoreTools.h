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
int initSem(int semid, int semnum, int val);
int setSem(int semid, int semnum, int op);
int P(int semid, int semnum, int op);
int V(int semid, int semnum, int op);
int removeSem(int semid);

void dieSem(char *s) {
	perror(s);
	exit(1);
}

int simpleSemid(int num, int flags, int proj) {
	key_t key = ftok(".", proj);
	if (key < 0) {
		dieSem("ftok");
		return -1;
	}
	int semid = semget(key, num, flags);
	if (semid < 0) {
		dieSem("semget");
		return -1;
	}
	return semid;
}

int createSemid(int nums, int proj) {
	return simpleSemid(nums, IPC_CREAT | IPC_EXCL | 0666, proj);
}

int attachSemid(int nums, int proj) {
	return simpleSemid(nums, IPC_CREAT, proj);
}

int removeSem(int semid) {
	pid_t pid = fork();
	if (pid == 0) {
		int retCode = semctl(semid, 0, IPC_RMID);
		if (retCode >= 0) {
			printf("removed semid = %d successfully, return code = %d\n", semid, retCode);
		}
		else {
			dieSem("semctl");
		}
		exit(0);
	}
	int status;
	pid_t wait_pid = waitpid(pid, &status, 0);
	return 0;
}

int initSem(int semid, int semnum, int val) {
	union semun su;
	su.val = val;
	if (semctl(semid, semnum, SETVAL, su) < 0) {
		dieSem("semctl");
		return -1;
	}
	return 0;
}

int setSem(int semid, int semnum, int op) {
	struct sembuf sb;
	sb.sem_num = semnum;
	sb.sem_op = op;
	sb.sem_flg = 0;
	return semop(semid, &sb, 1);
}

int P(int semid, int semnum, int op) {
	if (setSem(semid, semnum, op) < 0) {
		dieSem("P");
		return -1;
	}
	return 0;
}

int V(int semid, int semnum, int op) {
	if (setSem(semid, semnum, op) < 0) {
		dieSem("V");
		return -1;
	}
	return 0;
}
