#include <stdio.h>
#include <stdlib.h>

int main() {
    extern char** environ;

    printf("Environment Variables:\n");
    for (char **env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }

    return 0;

}
