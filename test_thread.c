#include "messageTools.h"
#include "semaphoreTools.h"

int k;

void *fun(void *arg) {
	int node = *(int *)arg;
	for (int i = 0; i < 10; ++i) {
		k++;
		printf("%d: %d\n", node, k);
		usleep(1);
	}
	return (void *)0;
}

int main() {
	pthread_t thread1, thread2, thread3;
	int a = 1, b = 2, c = 3;
	k = 0;
	pthread_create(&thread1, NULL, fun, &a);
	pthread_create(&thread2, NULL, fun, &b);
	pthread_create(&thread3, NULL, fun, &c);
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