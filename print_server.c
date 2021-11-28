#include "messageTools.h"
#include "semaphoreTools.h"

int main(int argc, char *argv[]) {
	int N = atoi(argv[1]);
	printf("There are %d nodes in the network\n", N);
	int me = 99;
	printf("Print server is node %d\n", me);
	int msgid = createMessageQueue(PROJ_MSG);
	printf("creating msgid = %d successfully\n", msgid);
	int semid = createSemid(2, PROJ_SEM_1);
	// int semid_2 = createSemid(1, PROJ_SEM_2);
	printf("creating semid_1 = %d successfully\n", semid_1);
	//printf("creating semid_2 = %d successfully\n", semid_2);
	removeMessageQueue(msgid);
	system("/usr/bin/ipcs");
	removeSem(semid_1, 0);
	system("/usr/bin/ipcs");
	removeSem(semid_1, 1);
	system("/usr/bin/ipcs");
	return 0;
}