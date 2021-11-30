#include "basicTools.h"

int CreateShm(int size);
int DestroyShm(int shmid);
int GetShm(int size);

static int CommonShm(int size, int flags, int proj)
{
	key_t key;
	int shmid = 0;
	
	if((key = ftok(".", proj)) < 0){
		perror("ftok");
		return -1;
	}
	
	if((shmid = shmget(key,size,flags)) < 0){
		perror("shnget");
		return -2;
	}
	
	return shmid;
}

//创建共享内存
int CreateShm(int size, int proj) {
	return CommonShm(size, IPC_CREAT | IPC_EXCL | 0666, proj);
}

//删除共享内存
int DestroyShm(int shmid) {
	if(shmctl(shmid, IPC_RMID, NULL) < 0){
		perror("shmctl");
		return -1;
	}
	return 0;
}


//已存在共享内存，获取shmid
int GetShm(int size)
{
	return CommonShm(size, IPC_CREAT);
}
