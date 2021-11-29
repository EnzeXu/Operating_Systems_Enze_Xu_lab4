#include "messageTools.h"
#include "semaphoreTools.h"

int main(int argc, char *argv[]) {
	int N = atoi(argv[1]);
	printf("There are %d nodes in the network\n", N);
	int me = 99;
	printf("Print server is node %d\n", me);
	int msgid = createMessageQueue(PROJ_MSG);
	printf("creating msgid = %d successfully\n", msgid);
	////int semid = createSemid(2, PROJ_SEM_1);
	// int semid_2 = createSemid(1, PROJ_SEM_2);
	////printf("creating semid = %d successfully\n", semid);
	//printf("creating semid_2 = %d successfully\n", semid_2);
	printf("waiting for every node ready...\n");
	
	// wait here until every node says he is ready
	pid_t pid_ready = fork();
	if (pid_ready == 0) {
		int ready[MAXN];
		memset(ready, 0, sizeof(ready));
		int flag;
		while(1) {
			struct msgbuf sbuf_ready;
			receiveMessage(msgid, 99, &sbuf_ready);
			printf("From node %d: I am ready!\n", sbuf_ready.source);
			ready[sbuf_ready.source] = 1;
			flag = 1;
			for (int i = 1; i <= N; ++i) {
				if (!ready[i]) {
					flag = 0;
					break;
				}
			}
			if (flag) break;
		}
		exit(0);
	}
	else {
		int status;
		pid_t wait_pid = waitpid(pid_ready, &status, 0);
	}
	printf("All nodes are ready!\n");
	
	// broadcast to each node that they could start
	for (int i = 1; i <= N; ++i) {
		sendMessage(msgid, 100 + i, me, 0);
	}
	printf("finished telling each node they can start\n");
	int times = 0;
	while(times < N * MAXREQUEST) {
		struct msgbuf sbuf;
		receiveMessage(msgid, 99, &sbuf);
		printf("### START OUTPUT FOR NODE %d ###\n", sbuf.source);
		printf("%d is the best number in the world!\n", sbuf.source);
		printf("--- END OUTPUT FOR NODE %d ---\n", sbuf.source);
		times++;
	}
	
	int goodbye[MAXN];
	memset(goodbye, 0, sizeof(goodbye));
	int flag2;
	while(1) {
		struct msgbuf sbuf_goodbye;
		receiveMessage(msgid, 99, &sbuf_goodbye);
		printf("From node %d: Good-bye!\n", sbuf_goodbye.source);
		ready[sbuf_goodbye.source] = 1;
		flag2 = 1;
		for (int i = 1; i <= N; ++i) {
			if (!ready[i]) {
				flag2 = 0;
				break;
			}
		}
		if (flag2) break;
	}
	sleep(5);
	removeMessageQueue(msgid);
	////removeSem(semid);
	//removeSem(semid, 1);
	printf("End\n");
	return 0;
}