#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc > 2) {
        printf("Usage: %s [variable_name]\n", argv[0]);
        return 1;
    }

    if (argc == 2) {
        const char *variable_name = argv[1];
        int unsetenv_result = unsetenv(variable_name);

        if (unsetenv_result != 0) {
            printf("Error unsetting environment variable.\n");
            return 1;
        }
    } else {
        int clearenv_result = clearenv();

        if (clearenv_result != 0) {
            printf("Error clearing environment.\n");
            return 1;
        }
    }

    extern char** environ;
    printf("Current Environment:\n");
    for (char **env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }
    return 0;
}
