#include "tools.h"

int main()
{
	int msgid = createMessageQueue();
	printf("creating msgid = %d successfully\n", msgid);
	// char sbuf[MAXSIZE];
	int z = 3;
	for (int i = 1; i <= z; ++i) {
		printf("waiting...\n");
		struct msgbuf sbuf;
		receiveMessage(msgid, REQUEST, &sbuf);
		printf("receive[%d]: %d %d %d\n", i, sbuf.mtype, sbuf.source, sbuf.snum);
	}
	removeMessageQueue(msgid);
	return 0;
}
