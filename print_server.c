#include "messageTools.h"
#include "semaphoreTools.h"

int main(int argc, char *argv[]) {
	char empty[MAXSIZE];
	empty[0] = '\0';
	int N = atoi(argv[1]);
	printf("[Print server] there are %d nodes in the network\n", N);
	int me = 99;
	srand(time(0) + me);
	printf("[Print server] print server is node %d\n", me);
	int msgid = createMessageQueue(PROJ_MSG);
	printf("[Print server] created msgid = %d successfully\n", msgid);
	
	// broadcast to each node the N
	printf("[Print server] broadcasting there are %d nodes in the network\n", N);
	for (int i = 1; i <= N; ++i) {
		sendMessage(msgid, 150 + i, me, N, empty);
	}
	
	// wait here until every node says he is ready
	printf("[Print server] waiting for every node ready...\n");
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
	printf("[Print server] all nodes are ready!\n");
	
	// broadcast to each node that they could start
	int z = randomInt(1000);
	for (int i = 1; i <= N; ++i) {
		sendMessage(msgid, 100 + ((z + i) % N) + 1, me, N, empty);
	}
	printf("[Print server] finished telling each node they can start\n");
	int times = 0;
	while(times < N * MAXREQUEST) {
		struct msgbuf sbuf;
		receiveMessage(msgid, 99, &sbuf);
		printf("%s", sbuf.mtext);
		if (sbuf.snum == -1) times++;
	}
	
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
	printf("[Print server] nodes and I finished all the job. Good-bye!\n");
	return 0;
}