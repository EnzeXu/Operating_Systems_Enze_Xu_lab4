#include "tools.h"

int main()
{
	int msgid = attachMessageQueue();
	printf("attaching to msgid = %d successfully\n", msgid);
	//char sbuf[MAXSIZE];
	int z = 10;
	for (int i = 1; i <= z; ++i) {
		printf("send[%d]: ", i);
		int n;
		scanf("%d", &n);
		printf("n = %d\n", n);
		//struct msgbuf sbuf;

		sendMessage(msgid, REQUEST, n, n);
		printf("finish sending\n");
		if (n == 0) break;
	}
	return 0;
}
