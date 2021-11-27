#include "tools2.h"

int main()
{
	int msgid = GetMsgQueue();
	char sbuf[MAXSIZE];
	while(1)
	{
		sbuf[0] = 0;
		printf("Please Enter# ");
		fflush(stdout);
		ssize_t s = read(0, sbuf, sizeof(sbuf));
		printf("send buffer = \"%s\"\n", sbuf);
		if (s > 0) {
			sbuf[s - 1] = 0;
			SendMsg(msgid,CLIENT_TYPE,sbuf);
			printf("send done,wait recv ...\n");
		}
 
		RecvMsg(msgid,SERVER_TYPE,sbuf);
    	printf("server# %s\n",sbuf);
	}
	return 0;
}
