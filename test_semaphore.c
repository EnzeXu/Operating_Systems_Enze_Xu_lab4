#include "semaphoreTools.h"

int main()
{
	int semid = createSemid(2);
	printf("%d\n", semid);
	initSem(semid, 0, 1);
	initSem(semid, 1, 2);
	pid_t id = fork();
	int z = 100;
	if (id == 0) {//child
		int semid = attachSemid(0);
		while (z--)
		{
			P(semid, 1, -1);
			printf("A");
			fflush(stdout);
			//usleep(10000);
			//printf("A");
			//fflush(stdout);
			usleep(10000);
			V(semid, 1, 1);
		}
	}
	else {//father
		while (z--)
		{
			P(semid, 1, -1);
			//usleep(10000);
			printf("B");
			fflush(stdout);
			usleep(10000);
			//printf("B");
			//fflush(stdout);
			//usleep(10000);
			V(semid, 1, 1);
		}
		if (waitpid(id, NULL, 0) < 0)
		{
			perror("waitpid");
			return -1;
		}

	}
	removeSem(semid, 0);
	removeSem(semid, 1);
	return 0;
}
