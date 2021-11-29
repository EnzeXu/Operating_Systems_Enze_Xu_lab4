#include "tools.h"

int main()
{
	int msgid = createMessageQueue();
	printf("creating msgid = %d successfully\n", msgid);
	// char sbuf[MAXSIZE];
	int z = 10;
	for (int i = 1; i <= z; ++i) {
		printf("waiting...\n");
		struct msgbuf sbuf;
		receiveMessage(msgid, REQUEST, &sbuf);
		printf("finish receiving\n");
		printf("receive[%d]: %d %d %d\n", i, sbuf.mtype, sbuf.source, sbuf.snum);
		if (sbuf.source == 0) break;
	}
	removeMessageQueue(msgid);
	return 0;
}
