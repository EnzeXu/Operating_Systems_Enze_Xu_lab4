#include "tools.h"

int main()
{
	int msgid = attachMessageQueue();
	printf("attaching to msgid = %d successfully\n", msgid);
	//char sbuf[MAXSIZE];
	int z = 3;
	for (int i = 1; i <= z; ++i) {
		sbuf[0] = 0;
		printf("send[%d]: ", i);
		int n;
		scanf("%d", &n);
		//struct msgbuf sbuf;

		sendMessage(msgid, REQUEST, n, n);
	}
	return 0;
}
