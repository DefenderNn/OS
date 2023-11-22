#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *childThreadFunction() {
    for (int i = 0; i <= 9; i++) {
        printf("Child thread. Iteration: %d\n", i+1);
        sleep(rand() % 5);
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    
    pthread_t childThread;

    if (pthread_create(&childThread, NULL, childThreadFunction, NULL)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    for (int i = 0; i <= 9; i++) {
        printf("Main thread. Iteration: %d\n", i+1);
        sleep(rand() % 5);
    }

    if (pthread_join(childThread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }

    return 0;
}
