#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int num_handlers = 0;

void handler(int sig) {
    static int count = 0;
    if (count < num_handlers) {
        printf("Обробник %d активовано\n", count + 1);
        sleep(1);
        count++;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Використання: %s <кількість обробників>\n", argv[0]);
        return 1;
    }

    num_handlers = atoi(argv[1]);
    signal(SIGINT, handler);


    while (1) {
        pause();
    }

    return 0;
}
