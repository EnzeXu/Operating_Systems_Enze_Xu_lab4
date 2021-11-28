#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <error.h>

#define  PATHNAME "."
#define  PROJ_ID  0

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *arry;
	struct seminfo *__buf;
};
//信号量是创建还是获取在于semget函数参数flag的设置
static int CommSemid(int nums, int flags);
//创建信号量
int CreatSemid(int nums);
//获取已经创建的信号量
int GetSemid(int nums);
//初始化信号量
int InitSem(int semid, int which, int _val);
//PV操作在于它_op的值
static int SemPV(int semid, int which, int _op);
//P操作
int P(int semid, int which, int _op);
//V操作
int V(int semid, int which, int _op);
//由于（System V通信方式）信号量生命周期随内核,所以要销毁信号量
int Destory(int semid);


static int CommSemid(int nums, int flags)
{
	key_t _key = ftok(PATHNAME, PROJ_ID);
	if (_key>0)
	{
		return semget(_key, nums, flags);
	}
	else
	{
		perror("CommSemid");
		return -1;
	}
}

int CreatSemid(int nums)
{
	return CommSemid(nums, IPC_CREAT | IPC_EXCL | 0666);
}
// int semctl(int semid, int semnum, int cmd, ...);

int GetSemid(int nums)
{
	return CommSemid(nums, IPC_CREAT);
}
int Destory(int semid)
{
	if (semctl(semid, 0, IPC_RMID)>0)
	{

		return 0;
	}
	else
	{
		perror("Destory");
		return -1;
	}
}

int InitSem(int semid, int which, int _val)
{

	union semun _semun;
	_semun.val = _val;
	if (semctl(semid, which, SETVAL, _semun)<0)
	{
		perror("InitSem");
		return -1;
	}
	return 0;
}
static int SemPV(int semid, int which, int _op)
{
	struct sembuf _sf;
	_sf.sem_num = which;
	_sf.sem_op = _op;
	_sf.sem_flg = 0;
	return semop(semid, &_sf, 1);
}

int P(int semid, int which, int _op)
{
	if (SemPV(semid, which, _op)<0)
	{
		perror("P");
		return -1;
	}
	return 0;
}

int V(int semid, int which, int _op)
{
	if (SemPV(semid, which, _op)<0)
	{
		perror("V");
		return -1;
	}
	return 0;
}
	