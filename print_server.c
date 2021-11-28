#include "messageTools.h"
#include "semaphoreTools.h"

int main(int argc, char *argv[]) {
	int N = atoi(argv[1]);
	printf("There are %d nodes in the network\n", N);
	int me = 99;
	printf("Print server is node %d\n", me);
	int msgid = createMessageQueue(PROJ_MSG);
	printf("creating msgid = %d successfully\n", msgid);
	int semid = createSemid(2, PROJ_SEM_1);
	// int semid_2 = createSemid(1, PROJ_SEM_2);
	printf("creating semid = %d successfully\n", semid);
	//printf("creating semid_2 = %d successfully\n", semid_2);
	printf("waiting for every node ready...\n");
	
	pid_t pid_ready = fork();
	if (pid_ready == 0) {
		int ready[MAXN];
		memset(ready, 0, sizeof(ready));
		int flag;
		while(1) {
			struct msgbuf sbuf;
			receiveMessage(msgid, 0, &sbuf);
			printf("From node %d: I am ready!\n", sbuf.source);
			ready[sbuf.source] = 1;
			flag = 1;
			for (int i = 1; i <= N; ++i) {
				if (!ready[i]) {
					flag = 0;
					break;
				}
			}
			if (flag) break;
		}
	else {
		int status;
		pid_t wait_pid = waitpid(pid_ready, &status, 0);
	}
	printf("All nodes are ready!\n");
	
	removeMessageQueue(msgid);
	removeSem(semid);
	//removeSem(semid, 1);
	printf("End\n");
	return 0;
}