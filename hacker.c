#include "messageTools.h"

int main() {
	int msgid = attachMessageQueue(PROJ_MSG);
	int me = 100;
	printf("[Hacker] attached to msgid = %d successfully. Let's Hack!!!\n", msgid);
	char buf[MAXSIZE];
	while (1) {
		printf("[Hacker] ");
		fflush(stdout);
		ssize_t s = read(0, buf, sizeof(buf));
		if (s > 0) {
			buf[s] = '\0';
			sendMessagePrint(msgid, 99, buf);
		}
	}
	return 0;
}