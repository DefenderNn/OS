#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <variable_name> <variable_value>\n", argv[0]);
        return 1;
    }

    char *variable_name = argv[1];
    char *variable_value = argv[2];

    int setenv_result = setenv(variable_name, variable_value, 1);

    if (setenv_result != 0) {
        printf("Error setting environment variable.\n");
        return 1;
    }

    printf("Environment Variable Set: %s=%s\n", variable_name, getenv(variable_name));
    return 0;
}
