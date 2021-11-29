#include "messageTools.h"
#include "semaphoreTools.h"

void *fun() {
	for (int i = 0; i < 10; ++i) {
		printf("%d ", i);
		usleep(10000);
	}
	return ((void *)0);
}

int main() {
	pthread_t thread1, thread2;
	if (pthread_create(&thread1, NULL, fun, NULL) < 0) {
		perror("pthread_create");
		exit(1);
	}
	if (pthread_create(&thread2, NULL, fun, NULL) < 0) {
		perror("pthread_create");
		exit(1);
	}
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("finished!\n");
	return 0;
}