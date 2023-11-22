#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct ThreadParams {
    char* name;
    char* str;
    int num;
    int range_start;
    int range_end;
    int target_random_number;
};

void* printString(void* arg) {
    struct ThreadParams* params = (struct ThreadParams*)arg;

    for (int i = 1; i <= params->num; ++i) {
        printf("%s %s %d\n", params->name, params->str, i);
        sleep(1);
    }

    pthread_exit(NULL);
}

void* printRandomNumbers(void* arg) {
    struct ThreadParams* params = (struct ThreadParams*)arg;

    for (int i = 1; i <= params->num; ++i) {
        int random_number = rand() % (params->range_end - params->range_start + 1) + params->range_start;
        printf("%s Random Number %d: %d\n", params->name, i, random_number);

        if (random_number == params->target_random_number) {
            printf("%s Target random number %d found. Exiting.\n", params->name, params->target_random_number);
            pthread_exit(NULL);
        }

        sleep(1);
    }

    pthread_exit(NULL);
}

int main() {
    srand((unsigned int)time(NULL));

    pthread_t threads[2];

    struct ThreadParams threadParams[2] = {
            {"Thread1", "Welcome", 3, 0, 0, 0},
            {"Thread2", "", 5, 1, 10, 7}
    };

    for (int i = 0; i < 2; ++i) {
        int result;
        if (i == 0) {
            result = pthread_create(&threads[i], NULL, printString, (void*)&threadParams[i]);
        } else {
            result = pthread_create(&threads[i], NULL, printRandomNumbers, (void*)&threadParams[i]);
        }

        if (result != 0) {
            fprintf(stderr, "Error creating thread %d\n", i + 1);
            return 1;
        }
    }

    for (int i = 0; i < 2; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("Main thread: All child threads have finished.\n");

    return 0;
}
