#include "messageTools.h"
#include "semaphoreTools.h"

int k;

struct threadParam {
	int node;
	int x;
}

void *fun(void *arg) {
	//int node = *(int *)arg;
	struct threadParam *pt;
	pt = (struct threadParam *) arg;
	for (int i = 0; i < 10; ++i) {
		k++;
		printf("%d(%d): %d\n", pt->node, pt->x, k);
		usleep(1);
	}
	return (void *)0;
}

int main() {
	pthread_t thread1, thread2, thread3;
	int a = 1, b = 2, c = 3;
	k = 0;
	struct threadParam tp1, tp2, tp3;
	tp1.node = 1;
	tp1.x = 111;
	tp2.node = 2;
	tp2.x = 222;
	tp3.node = 3;
	tp3.x = 333;
	pthread_create(&thread1, NULL, fun, &tp1);
	pthread_create(&thread2, NULL, fun, &tp2);
	pthread_create(&thread3, NULL, fun, &tp3);
	/*
	if (pthread_create(&thread1, NULL, fun, NULL) < 0) {
		perror("pthread_create");
		exit(1);
	}
	if (pthread_create(&thread2, NULL, fun, NULL) < 0) {
		perror("pthread_create");
		exit(1);
	}
	if (pthread_create(&thread3, NULL, fun, NULL) < 0) {
		perror("pthread_create");
		exit(1);
	}
	*/
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	printf("finished!\n");
	return 0;
}