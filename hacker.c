#include "messageTools.h"
#include "semaphoreTools.h"

int main() {
	int msgid = attachMessageQueue();
	int me = 100;
	printf("[Hacker] attached to msgid = %d successfully. Let's Hack!!!\n", msgid);
	char buf[MAXSIZE];
	while (1) {
		printf("[Hacker] ", i);
		fflush(stdout);
		ssize_t s = read(0, buf, sizeof(buf));
		if (s > 0) {
			sbuf[s] = '\0';
			sendMessage(msgid, 99, me, 0, buf);
		}
	}
	return 0;
}