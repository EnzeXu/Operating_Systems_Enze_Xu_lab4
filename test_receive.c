#include "tools.h"

int main()
{
	int msgid = CreateMsgQueue();
	char sbuf[MAXSIZE];
	while(1)
	{
		sbuf[0] = 0;
		RecvMsg(msgid,CLIENT_TYPE,sbuf);
		printf("client# %s\n",sbuf);
 
		printf("Please Enter# ");
		fflush(stdout);
		ssize_t s = read(0,sbuf,sizeof(sbuf));
		printf("receive buffer = \"%s\"\n", sbuf);
		if(s > 0)
		{
			sbuf[s - 1] = 0;
			SendMsg(msgid,SERVER_TYPE,sbuf);
			printf("send done, wait recv ...\n");
		}
	}
	DestroyMsgQueue(msgid);
	return 0;
}
