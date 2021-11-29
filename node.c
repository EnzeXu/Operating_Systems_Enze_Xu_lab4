#include "messageTools.h"
#include "semaphoreTools.h"

int me; /* my node number */
int N; /* number of nodes */
int request_number; /* nodes sequence number */
int highest_request_number; /* highest request number seen */
int outstanding_reply; /* # of outstanding replies */
int request_CS; /* true when node requests critical section */
int reply_deferred[MAXN]; /* reply_deferred[i] is true when node defers reply to node i */
//semaphore mutex; /* for mutual exclusion to shared variables */
//semaphore wait_sem; /* used to wait for all requests */

int msgid;
int semid;
/*
int receiveRequest(int k, int i) {
	// k is the sequence number being requested 
	// i is the node making the request 
	int defer_it //* true if request must be deferred 
	if (k > highest_request_number) highest_request_number = k;
	P(mutex);
	defer_it = (request_CS) && ((k > request_number) || ( k == request_number && i > me));
	V(mutex);
	// defer_it is true if we have priority 
	if (defer_it) reply_deferred[i] = TRUE;
	else send(REPLY, i);
	return 0;
}

int receiveReply(int k, int i) {
	outstanding_reply--;
	V(wait_sem);
}

int sendRequest() {
	P(mutex);
	request_CS = TRUE;
	request_number = ++highest_request;
	V(mutex);
	outstanding_reply = N-1;
	for (int i = 1; i <= N; i++) {
		if (i != me) sendMessage(msgid, i * 10, me, request_number);
	}
	// wait for replies 
	while (outstanding_reply != 0) P(wait_sem);
	//CRITICAL SECTION;
	printf("node %d is now in its CRITICAL SECTION\n", me);
	request_CS = FALSE;
	for (int i = 1; i <= N; i++) {
		if (i == me) continue;
		if (reply_deferred[i]) {
			reply_deferred[i] = FALSE;
			sendMessage(msgid, i * 10 + 1, me, request_number); //send(REPLY, i);
		}
	return 0;
}
*/
int main(int argc, char *argv[]) {
	N = atoi(argv[1]);
	printf("[I] There are %d nodes in the network\n", N);
	me = atoi(argv[2]);
	printf("I am node %d\n", me);
	msgid = attachMessageQueue(PROJ_MSG);
	printf("[I] node %d attaching to msgid = %d successfully\n", me, msgid);
	//semid = createSemid(2);
	//request_number = 0;
	//highest_request_number = 0;
	sendMessage(msgid, 90, me, 0);
	printf("[Node 99] finished sending ready message, waiting for the starting signal from print server...\n");
	struct msgbuf sbuf_start;
	receiveMessage(msgid, 100 + me, &sbuf_start);
	printf("[Node 99] print server told me I can start!\n");
	
	return 0;
}