#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
 
#define PATHNAME "."
#define PROJ_ID 0x6666
 
#define SERVER_TYPE 1
#define CLIENT_TYPE 2
 
struct msgbuf
{
	long mtype;
	char mtext[1024];
};
int CreateMsgQueue();//创建消息队列
int GetMsgQueue();//接受消息队列
int DestroyMsgQueue(int msgid);//销毁消息队列
int SendMsg(int msgid,int who,char* msg);//发送消息
int RecvMsg(int msgid,int recvType,char out[]);//接受消息



 
//success > 0    failed == -1
 
static int CommMsgQueue(int flags)
{
	key_t key = ftok(PATHNAME,PROJ_ID);
	if(key < 0)
	{
		perror("ftok");
		return -1;
	}
	int msgid = msgget(key,flags);
	if(msgid < 0)
	{
		perror("msgget");
	}
	return msgid;
}
int CreateMsgQueue()
{
	return CommMsgQueue(IPC_CREAT | IPC_EXCL | 0666);
}
int GetMsgQueue()
{
	return CommMsgQueue(IPC_CREAT);
}
int DestroyMsgQueue(int msgid)
{
	if(msgctl(msgid,IPC_RMID,NULL) < 0)
	{
		perror("msgctl");
		return -1;
	}
	return 0;
}
int SendMsg(int msgid,int who,char* msg)
{
	struct msgbuf buf;
	buf.mtype = who;
	strcpy(buf.mtext,msg);
	if(msgsnd(msgid,(void*)&buf,sizeof(buf.mtext),0) < 0)
	{
		perror("msgsnd");
		return -1;
	}
	return 0;
}
int RecvMsg(int msgid,int recvType,char out[])
{
	struct msgbuf buf;
	if(msgrcv(msgid,(void*)&buf,sizeof(buf.mtext),recvType,0) < 0)
	{
		perror("msgrcv");
		return -1;
	}
	strcpy(out,buf.mtext);
	return 0;
}