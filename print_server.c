#include "messageTools.h"
#include "semaphoreTools.h"

int main(int argc, char *argv[]) {
	char empty[MAXSIZE] = "";
	int N = atoi(argv[1]);
	printf("[Print server] there are %d nodes in the network\n", N);
	int me = 99;
	printf("[Print server] print server is node %d\n", me);
	int msgid = createMessageQueue(PROJ_MSG);
	printf("[Print server] created msgid = %d successfully\n", msgid);
	////int semid = createSemid(2, PROJ_SEM_1);
	// int semid_2 = createSemid(1, PROJ_SEM_2);
	////printf("creating semid = %d successfully\n", semid);
	//printf("creating semid_2 = %d successfully\n", semid_2);
	printf("[Print server] waiting for every node ready...\n");
	
	// wait here until every node says he is ready
	int ready[MAXN];
	memset(ready, 0, sizeof(ready));
	int flag1;
	while(1) {
		struct msgbuf sbuf_ready;
		receiveMessage(msgid, 99, &sbuf_ready);
		printf("[Print server] received a message from node %d: I am ready!\n", sbuf_ready.source);
		ready[sbuf_ready.source] = 1;
		flag1 = 1;
		for (int i = 1; i <= N; ++i) {
			if (!ready[i]) {
				flag1 = 0;
				break;
			}
		}
		if (flag1) break;
	}
	printf("[Print server] All nodes are ready!\n");
	
	// broadcast to each node that they could start
	for (int i = 1; i <= N; ++i) {
		sendMessage(msgid, 100 + (N + 1 - i), me, 0, empty);
	}
	printf("[Print server] finished telling each node they can start\n");
	int times = 0;
	int current_node = -1;
	while(times < N * MAXREQUEST * N) {
		struct msgbuf sbuf;
		receiveMessage(msgid, 99, &sbuf);
		if (sbuf.source != current_node) {
			if (current_node != -1) printf("--- END OUTPUT FOR NODE %d ---\n\n", current_node);
			printf("### START OUTPUT FOR NODE %d ###\n", sbuf.source);
			current_node = sbuf.source;
		}
		printf("%d: This is line %d!\n", current_node, sbuf.snum);
		times++;
	}
	printf("--- END OUTPUT FOR NODE %d ---\n\n", current_node);
	
	int goodbye[MAXN];
	memset(goodbye, 0, sizeof(goodbye));
	int flag2;
	while(1) {
		struct msgbuf sbuf_goodbye;
		receiveMessage(msgid, 100 + 99, &sbuf_goodbye);
		printf("[Print server] received a message from node %d: Good-bye!\n", sbuf_goodbye.source);
		goodbye[sbuf_goodbye.source] = 1;
		flag2 = 1;
		for (int i = 1; i <= N; ++i) {
			if (!goodbye[i]) {
				flag2 = 0;
				break;
			}
		}
		if (flag2) break;
	}
	sleep(2);
	removeMessageQueue(msgid);
	////removeSem(semid);
	//removeSem(semid, 1);
	printf("[Print server] end & good-bye!\n");
	return 0;
}