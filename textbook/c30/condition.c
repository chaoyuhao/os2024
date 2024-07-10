
#include <stdio.h>
#include <pthread.h>

void *child(void *arg) {
	printf("child\n");
	return NULL;
}

int main() {

	printf("parent: begin\n");

	pthread_t c;
	pthread_create(&c, NULL, child, NULL);


	return 0;
}
