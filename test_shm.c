#include "sharedMemoryTools.h"

int main() {
	int shmid;
	char *addr;
	int i = 0;
	shmid = GetShm(1024, 0x0001);
	addr = shmat(shmid, NULL, 0);
	
	pid_t pid1 = fork();
	if (pid1 == 0) {
		/*
		for (int i = 0; i < 10; ++i) {
			printf("");
		}
		*/
		int shmid;
		char *addr;
		int i = 0;
		
		
		shmid = GetShm(1024, 0x0001);
		addr = shmat(shmid, NULL, 0);
		int z = 10;
		while (z--) {
			addr[i] = 'Z' - i;
			i++;
			addr[i] = 0;
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
	int z = 10;
	while (z--) {
		printf("parent: %s\n", addr);
		sleep(1);
	}
	
	shmdt(addr);
	int status1, status2; 
	waitpid(pid1, &status1, 0); 
	DestroyShm(shmid);
	
	//waitpid(pid2, &status2, 0); 
	return 0;
}