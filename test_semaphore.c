#include "semaphoreTools.h"

int main()
{
	int semid = CreatSemid(1);
	printf("%d\n", semid);
	InitSem(semid, 0, 1);
	pid_t id = fork();
	if (id == 0)
	{//child
		int semid = GetSemid(0);
		while (1)
		{
			P(semid, 0, -1);
			printf("A");
			fflush(stdout);
			usleep(10000);
			printf("A");
			fflush(stdout);
			usleep(20000);
			V(semid, 0, 1);
		}
	}
	else
	{//father
		while (1)
		{
			P(semid, 0, -1);
			usleep(30000);
			printf("B");
			fflush(stdout);
			usleep(8000);
			printf("B");
			fflush(stdout);
			usleep(20000);
			V(semid, 0, 1);
		}
		if (waitpid(id, NULL, 0) < 0)
		{
			perror("waitpid");
			return -1;
		}

	}
	Destory(semid);
	return 0;
}
