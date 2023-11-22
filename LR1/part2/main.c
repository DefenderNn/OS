#include <pthread.h>
#include <stdio.h>

struct ThreadParams {
    char* name;
    char* str;
    int num;
};


void* threadFunction(void* arg) {
    struct ThreadParams* params = (struct ThreadParams*)arg;

    for (int i = 1; i <= params->num; ++i) {
        printf("Thread %s. %s %d\n", params->name, params->str, i);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[4];

    struct ThreadParams threadParams[4] = {
            {"Thread1", "BaseStr1", 3},
            {"Thread2", "BaseStr2", 4},
            {"Thread3", "BaseStr3", 2},
            {"Thread4", "BaseStr4", 5}
    };

    for (int i = 0; i < 4; ++i) {
        int result = pthread_create(&threads[i], NULL, threadFunction, (void*)&threadParams[i]);
        if (result != 0) {
            fprintf(stderr, "Error creating thread %d\n", i + 1);
            return 1;
        }
    }

    for (int i = 0; i < 4; ++i) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
