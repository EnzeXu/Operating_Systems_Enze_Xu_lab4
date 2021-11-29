#include "messageTools.h"
#include "semaphoreTools.h"

void *listenRequest();
void *listenReply();
int sendRequest(void);

int me; /* my node number */
int N; /* number of nodes */
int request_number; /* nodes sequence number */
int highest_request_number; /* highest request number seen */
int outstanding_reply; /* # of outstanding replies */
int request_CS; /* true when node requests critical section */
int reply_deferred[MAXN]; /* reply_deferred[i] is true when node defers reply to node i */
int msgid;
int semid;

void *listenRequest() {
	printf("[Node %d] listenRequest thread is set up\n", me);
	char empty[MAXSIZE];
	empty[0] = '\0';
	int z = (N - 1) * MAXREQUEST;
	while(z--) {
		struct msgbuf sbuf_listen_request;
		receiveMessage(msgid, 10 * me, &sbuf_listen_request);
		int k = sbuf_listen_request.snum; // k is the sequence number being requested 
		int i = sbuf_listen_request.source; // i is the node making the request
		printf("[Node %d] a request comes from node %d, sequence_number = %d ", me, i, k);
		int defer_it; // true if request must be deferred 
		if (k > highest_request_number) highest_request_number = k;
		P(semid, 0, -1); // P(mutex);
		defer_it = (request_CS) && ((k > request_number) || ( k == request_number && i > me));
		if (defer_it) printf("(I will defer it as my (request_CS, request_number) = (%d, %d))\n", request_CS, request_number);
		else printf("(I will reply it immediately as my (request_CS, request_number) = (%d, %d))\n", request_CS, request_number);
		V(semid, 0, 1); // V(mutex);
		// defer_it is true if we have priority 
		if (defer_it) reply_deferred[i] = TRUE;
		else sendMessage(msgid, i * 10 + 1, me, 0, empty); // send(REPLY, i);
	}
	return (void *)0;
}

void *listenReply() {
	printf("[Node %d] listenReply thread is set up\n", me);
	int z = (N - 1) * MAXREQUEST;
	while(z--) {
		struct msgbuf sbuf_listen_reply;
		receiveMessage(msgid, 10 * me + 1, &sbuf_listen_reply);
		printf("[Node %d] a reply comes from node %d\n", me, sbuf_listen_reply.source);
		printf("[Node %d] outstanding_reply goes from %d to %d\n", me, outstanding_reply, outstanding_reply - 1);
		outstanding_reply--;
		V(semid, 1, 1); // V(wait_sem);
	}
	return (void *)0;
}

int sendRequest(void) {
	char empty[MAXSIZE];
	empty[0] = '\0';
	//usleep(randomInt(500000));
	P(semid, 0, -1); // P(mutex);
	request_CS = TRUE;
	request_number = ++highest_request_number;
	V(semid, 0, 1); // V(mutex);
	outstanding_reply = N - 1;
	printf("[Node %d] outstanding_reply is reset to %d\n", me, outstanding_reply);
	for (int i = 1; i <= N; i++) {
		if (i != me) {
			sendMessage(msgid, i * 10, me, request_number, empty);
			printf("[Node %d] I sent a request to node %d\n", me, i);
		}
	}
	// wait for replies 
	while (outstanding_reply != 0) {
		P(semid, 1, -1); // P(wait_sem);
		// printf("In sendRequest, now outstanding_reply = %d\n", outstanding_reply);
	}
	
	//CRITICAL SECTION !!!!!!
	printf("[Node %d] I am now in the CRITICAL SECTION. I will send some lines to the print server\n", me);
	
	char str_start[MAXSIZE];
	sprintf(str_start, "### START OUTPUT FOR NODE %d ###\n", me);
	sendMessage(msgid, 99, me, 0, str_start);
	usleep(randomInt(300000));
	
	int sentence_num = randomInt(10) + 2;
	for (int i = 1; i <= sentence_num; ++i) {
		char str_tmp[MAXSIZE];
		sprintf(str_tmp, "%d: This is line %d!\n", me, i);
		sendMessage(msgid, 99, me, 0, str_tmp);
		usleep(randomInt(300000));
	}
	
	char str_end[MAXSIZE];
	sprintf(str_end, "--- END OUTPUT FOR NODE %d ---\n", me);
	sendMessage(msgid, 99, me, -1, str_end);
	usleep(randomInt(300000));
	
	printf("[Node %d] I want to quit the CRITICAL SECTION\n", me);
	//P(semid, 0, -1); // P(mutex);
	request_CS = FALSE;
	//V(semid, 0, 1); // V(mutex);
	for (int i = 1; i <= N; i++) {
		if (i == me) continue;
		if (reply_deferred[i]) {
			reply_deferred[i] = FALSE;
			sendMessage(msgid, i * 10 + 1, me, request_number, empty); //send(REPLY, i);
		}
	}
	return 0;
}

int main(int argc, char *argv[]) {
	char empty[MAXSIZE];
	empty[0] = '\0';
	//N = atoi(argv[1]);
	me = atoi(argv[1]);
	printf("[Node %d] I am node %d\n", me, me);
	msgid = attachMessageQueue(PROJ_MSG);
	printf("[Node %d] attached to msgid = %d successfully\n", me, msgid);
	struct msgbuf sbuf_broadcast_n;
	receiveMessage(msgid, 150 + me, &sbuf_broadcast_n);
	N = sbuf_broadcast_n.snum;
	printf("[Node %d] print server told me there are %d nodes in the network\n", me, N);
	semid = createSemid(2, me);
	initSem(semid, 0, 1); //0: semaphore mutex; /* for mutual exclusion to shared variables */
	initSem(semid, 1, 1); //1: semaphore wait_sem; /* used to wait for all requests */
	printf("[Node %d] created semid = %d successfully\n", me, semid);
	
	pthread_t thread_listen_request, thread_listen_reply;
	pthread_create(&thread_listen_request, NULL, listenRequest, NULL);
	pthread_create(&thread_listen_reply, NULL, listenReply, NULL);
	
	srand(time(0) * me);
	
	request_number = 0;
	highest_request_number = 0;
	outstanding_reply = -1;
	request_CS = 0;
	memset(reply_deferred, 0, sizeof(reply_deferred));
	
	sendMessage(msgid, 99, me, 0, empty);
	printf("[Node %d] finished sending ready message, waiting for the starting signal from print server (node 99)...\n", me);
	struct msgbuf sbuf_start;
	receiveMessage(msgid, 100 + me, &sbuf_start);
	printf("[Node %d] print server(node 99) told me I can start!\n", me);
	
	for (int i = 0; i < MAXREQUEST; ++i) {
		sendRequest();
	}
	pthread_join(thread_listen_request, NULL);
	pthread_join(thread_listen_reply, NULL);
	printf("[Node %d] ", me);
	fflush(stdout);
	removeSem(semid);
	//say good bye to print server
	sendMessage(msgid, 100 + 99, me, 0, empty);
	printf("[Node %d] I finished all the job. Good-bye!\n", me);
	return 0;
}