#include "sharedMemoryTools.h"

int main() {
	int shmid = GetShm(128, 0x0001);
	char *addr = (char*)shmat(shmid, NULL, 0);
	printf("Shared Memory: %p\n", addr);     
	printf("checkpoint1\n");
	addr[0] = '\0';
	pid_t pid1 = fork();
	if (pid1 == 0) {
		/*
		for (int i = 0; i < 10; ++i) {
			printf("");
		}
		*/
		printf("checkpoint2\n");
		int shmid;
		char *addr;
		int i = 0;
		//shmid = GetShm(1024, 0x0001);
		//addr = shmat(shmid, NULL, 0);
		int z = 10;
		while (z--) {
			printf("checkpoint2.5\n");
			addr[i] = 'Z' - i;
			i++;
			addr[i] = '\0';
			sleep(1);
		}
		shmdt(addr);
		exit(0);
	}
	/*
	pid_t pid2 = fork(); 
	if(pid2 == 0) { 
		for (int i = 0; i < 10; ++i) {
			printf("");
		}
		return 0;
	}
	*/
	printf("checkpoint3\n");
	int z = 10;
	while (z--) {
		printf("checkpoint3.5\n");
		printf("parent: %s\n", addr);
		sleep(1);
	}
	printf("checkpoint4\n");
	int status1, status2; 
	waitpid(pid1, &status1, 0); 
	shmdt(addr);
	DestroyShm(shmid);
	printf("checkpoint5\n");
	//waitpid(pid2, &status2, 0); 
	return 0;
}