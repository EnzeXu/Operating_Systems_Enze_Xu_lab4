#include "test_tools.h"

int main()
{
	int msgid = attachMessageQueue();
	printf("attaching to msgid = %d successfully\n", msgid);
	char sbuf[MAXSIZE];
	int z = 3;
	for (int i = 1; i <= z; ++i) {
		printf("send[%d]: ", i);
		fflush(stdout);
		ssize_t s = read(0, sbuf, sizeof(sbuf));
		if (s > 0) {
			sbuf[s - 1] = 0;
			sendMessage(msgid, REQUEST, sbuf);
		}
	}
	return 0;
}
