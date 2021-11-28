#include "test_tools.h"

int main()
{
	int msgid = createMessageQueue();
	printf("creating msgid = %d successfully\n", msgid);
	char sbuf[MAXSIZE];
	int z = 3;
	for (int i = 1; i <= z; ++i) {
		printf("waiting...\n");
		receiveMessage(msgid, REQUEST, sbuf);
		printf("receive[%d]: %s\n", i, sbuf);
	}
	removeMessageQueue(msgid);
	return 0;
}
