#include "tools.h"

int main()
{
	int msgid = attachMessageQueue();
	printf("attaching to msgid = %d successfully\n", msgid);
	char sbuf[MAXSIZE];
	int z = 3;
	for (int i = 1; i <= z; ++i) {
		sbuf[0] = 0;
		printf("send[%d]: ", i);
		fflush(stdout);
		ssize_t s = read(0, sbuf, sizeof(sbuf));
		if (s > 0) {
			sbuf[s - 1] = 0;
			sendMessage(msgid, CLIENT_TYPE, sbuf);
		}
	}
	return 0;
}
